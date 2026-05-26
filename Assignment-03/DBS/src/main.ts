import { Chart, LineController, LineElement, PointElement, LinearScale, CategoryScale, Filler, Tooltip } from 'chart.js';
import type { ChartConfiguration } from 'chart.js';

Chart.register(LineController, LineElement, PointElement, LinearScale, CategoryScale, Filler, Tooltip);

type Mode = 'AUTOMATIC' | 'MANUAL' | 'UNCONNECTED' | 'NOT_AVAILABLE';

interface AppState {
  mode: Mode;
  valveActual: number;
  valvePending: number;
  measurements: number[];
  N: number;
  startTime: number;
}

const STATE: AppState = {
  mode: 'AUTOMATIC',
  valveActual: 34,
  valvePending: 34,
  measurements: [],
  N: 20,
  startTime: Date.now()
};

const TOTAL_MEASUREMENTS = 200;

// Generate synthetic history
(function seedData(): void {
  let level = 120;
  for (let i = 0; i < TOTAL_MEASUREMENTS; i++) {
    level += (Math.random() - 0.46) * 12;
    level = Math.max(10, Math.min(300, level));
    STATE.measurements.push(Math.round(level * 10) / 10);
  }
})();

let chart: Chart | undefined;

/**
 * Displays the data as a line chart
 * @param data The information to display
 */
function buildChart(data: number[]): void {
  const ctx = document.getElementById('levelChart') as HTMLCanvasElement;
  const labels = data.map((_, i) => `T-${data.length - 1 - i}`);

  const gradient = ctx.getContext('2d')!.createLinearGradient(0, 0, 0, 280);
  gradient.addColorStop(0, 'rgba(61,159,255,0.35)');
  gradient.addColorStop(1, 'rgba(61,159,255,0.0)');

  const config: ChartConfiguration<'line', number[], string> = {
    type: 'line',
    data: {
      labels,
      datasets: [{
        label: 'Level (mm)',
        data,
        borderColor: '#3d9fff',
        borderWidth: 2,
        backgroundColor: gradient,
        fill: true,
        tension: 0.38,
        pointRadius: 3,
        pointBackgroundColor: '#3d9fff',
        pointBorderColor: '#0a0e14',
        pointBorderWidth: 1.5,
        pointHoverRadius: 5,
      }],
    },
    options: {
      responsive: true,
      maintainAspectRatio: false,
      animation: { duration: 500 },
      plugins: {
        legend: { display: false },
        tooltip: {
          backgroundColor: '#181e2c',
          borderColor: 'rgba(255,255,255,0.1)',
          borderWidth: 1,
          titleColor: '#687090',
          bodyColor: '#e4eaf6',
          titleFont: { family: "'IBM Plex Mono'", size: 10 },
          bodyFont: { family: "'IBM Plex Mono'", size: 12 },
          callbacks: {
            label: (ctx) => ` ${(ctx.raw as number).toFixed(1)} mm`,
          },
        },
      },
      scales: {
        x: {
          grid: { color: 'rgba(255,255,255,0.04)' },
          ticks: {
            color: '#687090',
            font: { family: "'IBM Plex Mono'", size: 9 },
            maxTicksLimit: 8,
            autoSkip: true,
          },
          border: { color: 'rgba(255,255,255,0.06)' },
        },
        y: {
          grid: { color: 'rgba(255,255,255,0.05)' },
          ticks: {
            color: '#687090',
            font: { family: "'IBM Plex Mono'", size: 10 },
            callback: (v) => v + ' mm',
          },
          border: { color: 'rgba(255,255,255,0.06)' },
        },
      },
    },
  };

  chart = new Chart(ctx, config);
}

function getSlice(): number[] {
  return STATE.measurements.slice(-STATE.N);
}

function updateChart(): void {
  if (!chart) return;
  const data = getSlice();
  const labels = data.map((_, i) => `T-${data.length - 1 - i}`);
  chart.data.labels = labels;
  chart.data.datasets[0].data = data;
  chart.update('none');
  updateStats(data);
}

function updateStats(data: number[]): void {
  const cur = data[data.length - 1];
  const avg = data.reduce((s, v) => s + v, 0) / data.length;
  const peak = Math.max(...data);
  document.getElementById('stat-current')!.innerHTML = cur.toFixed(1) + '<span class="stat-unit"> mm</span>';
  document.getElementById('stat-avg')!.innerHTML = avg.toFixed(1) + '<span class="stat-unit"> mm</span>';
  document.getElementById('stat-peak')!.innerHTML = peak.toFixed(1) + '<span class="stat-unit"> mm</span>';
}

function setGauge(pct: number): void {
  pct = Math.max(0, Math.min(100, pct));
  const ARC_LEN = 190;
  const fill = (pct / 100) * ARC_LEN;

  (document.querySelector('#gauge-fill') as SVGPathElement).style.strokeDashoffset = String(ARC_LEN - fill);
  const angle = -90 + (pct / 100) * 180;
  (document.querySelector('#gauge-needle') as SVGLineElement).style.transform = `rotate(${angle}deg)`;
  document.getElementById('gauge-display')!.innerHTML = Math.round(pct) + '<span class="gauge-pct">%</span>';

  const hue = pct < 40 ? '#1ecbc8' : pct < 75 ? '#f5a623' : '#e85555';
  (document.querySelector('#gauge-fill') as SVGPathElement).setAttribute('stroke', hue);
  (document.querySelector('#gauge-needle') as SVGLineElement).setAttribute('stroke', hue);
}

function setMode(mode: Mode): void {
  if (STATE.mode === 'NOT_AVAILABLE' || STATE.mode === 'UNCONNECTED') return;
  STATE.mode = mode;
  applyUIForMode(mode);
  showToast(mode === 'AUTOMATIC' ? 'Switched to AUTOMATIC mode' : 'Switched to MANUAL mode');
}

function applyUIForMode(mode: Mode): void {
  const btnAuto = document.getElementById('btn-auto') as HTMLButtonElement;
  const btnManual = document.getElementById('btn-manual') as HTMLButtonElement;
  const valveCtrl = document.getElementById('valve-ctrl') as HTMLElement;
  const applyBtn = document.getElementById('apply-btn') as HTMLButtonElement;
  const pill = document.getElementById('status-pill') as HTMLElement;
  const dot = document.getElementById('status-dot') as HTMLElement;
  const label = document.getElementById('status-label') as HTMLElement;

  btnAuto.className = 'mode-btn';
  btnManual.className = 'mode-btn';

  pill.className = 'status-pill status-' + mode.replace(' ', '_');
  dot.className = 'status-dot dot-' + mode.replace(' ', '_');
  label.textContent = mode === 'NOT_AVAILABLE' ? 'NOT AVAILABLE' : mode;

  const inoperable = mode === 'NOT_AVAILABLE' || mode === 'UNCONNECTED';
  btnAuto.disabled = inoperable;
  btnManual.disabled = inoperable;

  if (mode === 'AUTOMATIC') {
    btnAuto.classList.add('active-auto');
    valveCtrl.classList.add('disabled');
    applyBtn.disabled = true;
    const infoCus = document.getElementById('info-cus') as HTMLElement;
    infoCus.textContent = 'Connected';
    infoCus.className = 'info-val ok';
    const infoWcs = document.getElementById('info-wcs') as HTMLElement;
    infoWcs.textContent = 'Connected';
    infoWcs.className = 'info-val ok';
  } else if (mode === 'MANUAL') {
    btnManual.classList.add('active-manual');
    valveCtrl.classList.remove('disabled');
    applyBtn.disabled = false;
  } else if (mode === 'UNCONNECTED') {
    valveCtrl.classList.add('disabled');
    applyBtn.disabled = true;
    const infoCus = document.getElementById('info-cus') as HTMLElement;
    infoCus.textContent = 'Disconnected';
    infoCus.className = 'info-val warn';
  } else if (mode === 'NOT_AVAILABLE') {
    valveCtrl.classList.add('disabled');
    applyBtn.disabled = true;
    const infoCus = document.getElementById('info-cus') as HTMLElement;
    infoCus.textContent = 'Unreachable';
    infoCus.className = 'info-val error';
    const infoWcs = document.getElementById('info-wcs') as HTMLElement;
    infoWcs.textContent = 'Unreachable';
    infoWcs.className = 'info-val error';
  }
}

// ── Slider ─────────────────────────────────────────────
function onSliderInput(val: string): void {
  STATE.valvePending = parseInt(val, 10);
  (document.getElementById('slider-readout') as HTMLElement).textContent = val + '%';
}

function applyValve(): void {
  STATE.valveActual = STATE.valvePending;
  setGauge(STATE.valveActual);
  showToast(`Valve set to ${STATE.valveActual}% — command sent to WCS`);
}

// ── N select ───────────────────────────────────────────
(document.getElementById('n-select') as HTMLSelectElement).addEventListener('change', function (this: HTMLSelectElement) {
  STATE.N = parseInt(this.value, 10);
  (document.getElementById('chart-subtitle') as HTMLElement).textContent = `Last ${STATE.N} measurements · live feed`;
  updateChart();
});

// ── Clock & live feed ──────────────────────────────────
function pad(n: number): string {
  return n.toString().padStart(2, '0');
}

function updateClock(): void {
  const d = new Date();
  (document.getElementById('clock') as HTMLElement).textContent =
    pad(d.getHours()) + ':' + pad(d.getMinutes()) + ':' + pad(d.getSeconds());
}

function updateUptime(): void {
  const s = Math.floor((Date.now() - STATE.startTime) / 1000);
  const h = Math.floor(s / 3600);
  const m = Math.floor((s % 3600) / 60);
  const sec = s % 60;
  (document.getElementById('info-uptime') as HTMLElement).textContent =
    pad(h) + ':' + pad(m) + ':' + pad(sec);
}

function addMeasurement(): void {
  const last = STATE.measurements[STATE.measurements.length - 1];
  let next = last + (Math.random() - 0.46) * 12;
  next = Math.max(10, Math.min(300, next));
  STATE.measurements.push(Math.round(next * 10) / 10);
  if (STATE.measurements.length > 500) STATE.measurements.shift();

  if (STATE.mode === 'AUTOMATIC') {
    STATE.valveActual = Math.round(Math.min(100, Math.max(0, (next / 300) * 100)));
    setGauge(STATE.valveActual);
  }

  updateChart();
  const now = new Date();
  (document.getElementById('info-update') as HTMLElement).textContent =
    pad(now.getHours()) + ':' + pad(now.getMinutes()) + ':' + pad(now.getSeconds());
}

let toastTimer: ReturnType<typeof setTimeout> | undefined;

function showToast(msg: string): void {
  const t = document.getElementById('toast') as HTMLElement;
  t.textContent = msg;
  t.classList.add('show');
  clearTimeout(toastTimer);
  toastTimer = setTimeout(() => t.classList.remove('show'), 2800);
}

buildChart(getSlice());
updateStats(getSlice());
setGauge(STATE.valveActual);
(document.getElementById('valve-slider') as HTMLInputElement).value = String(STATE.valveActual);
(document.getElementById('slider-readout') as HTMLElement).textContent = STATE.valveActual + '%';
applyUIForMode('AUTOMATIC');

setInterval(updateClock, 1000);
setInterval(updateUptime, 1000);
setInterval(addMeasurement, 2000);
updateClock();

export { setMode, onSliderInput, applyValve };
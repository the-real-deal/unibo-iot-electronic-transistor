import { Chart, LineController, LineElement, PointElement, LinearScale, CategoryScale, Filler, Tooltip } from 'chart.js';
import type { ChartConfiguration } from 'chart.js';
import type { AppState, Mode, ServerData, WaterLevel } from './data';
import { pad } from './utility';
import { getUpdatedData } from './api';


const btnAuto = document.getElementById('btn-auto') as HTMLButtonElement;
const btnManual = document.getElementById('btn-manual') as HTMLButtonElement;
const valveCtrl = document.getElementById('valve-ctrl') as HTMLElement;
const applyBtn = document.getElementById('apply-btn') as HTMLButtonElement;
const pill = document.getElementById('status-pill') as HTMLElement;
const dot = document.getElementById('status-dot') as HTMLElement;
const label = document.getElementById('status-label') as HTMLElement;

const infoCus = document.getElementById('info-cus') as HTMLElement;
const infoWcs = document.getElementById('info-wcs') as HTMLElement;

Chart.register(LineController, LineElement, PointElement, LinearScale, CategoryScale, Filler, Tooltip);

const STATE: AppState = {
  mode: 'automatic',
  valveActual: 34,
  valvePending: 34,
  measurements: [],
  N: 20,
  startTime: Date.now()
};

const TOTAL_MEASUREMENTS = 200;

// Generate flat starter graph
(function seedData(): void {
  for (let i = 0; i < TOTAL_MEASUREMENTS; i++) {
    STATE.measurements.push({ value: 0, measurementTime: Date.now.toString() });
  }
})();

let chart: Chart | undefined;

/**
 * Displays the data as a line chart
 * @param data The information to display
 */
function buildChart(data: WaterLevel[]): void {
  const ctx = document.getElementById('levelChart') as HTMLCanvasElement;
  const labels = data.map(val => `${val.measurementTime}`);
  const values = data.map(val => val.value);

  const gradient = ctx.getContext('2d')!.createLinearGradient(0, 0, 0, 280);
  gradient.addColorStop(0, 'rgba(61,159,255,0.35)');
  gradient.addColorStop(1, 'rgba(61,159,255,0.0)');

  const config: ChartConfiguration<'line', number[], string> = {
    type: 'line',
    data: {
      labels,
      datasets: [{
        label: 'Level (mm)',
        data: values,
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

/**
 * Updates the chart with the data in the global state object
 * Does nothing if the chart is not initialized
 */
function updateChart(): void {
  if (!chart) return;
  const data = STATE.measurements.slice(-STATE.N);
  const labels = data.map((_, i) => `${data[i].measurementTime}`);
  chart.data.labels = labels;
  const values = data.map((_, i) => data[i].value);
  chart.data.datasets[0].data = values;
  chart.update('none');
  updateStats(values);
}

/**
 * Updates the stats under the chart
 * @param data The array of values currently displayed in the chart
 */
function updateStats(data: number[]): void {
  const cur = data[data.length - 1];
  const avg = data.reduce((s, v) => s + v, 0) / data.length;
  const peak = Math.max(...data);
  document.getElementById('stat-current')!.innerHTML = cur.toFixed(1) + '<span class="stat-unit"> mm</span>';
  document.getElementById('stat-avg')!.innerHTML = avg.toFixed(1) + '<span class="stat-unit"> mm</span>';
  document.getElementById('stat-peak')!.innerHTML = peak.toFixed(1) + '<span class="stat-unit"> mm</span>';
}

/**
 * Changes the valve level display based on the given number
 * @param pct The opening percentage of the valve
 */
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

/**
 * Changes the system mode.
 * @param mode The state to switch to
 * Does not change the mode if the current state is unconnected or not available
 */
function setMode(mode: Mode): void {
  if (STATE.mode === 'not_available' || STATE.mode === 'unconnected') return;
  STATE.mode = mode;
  applyUIForMode(mode);
  showToast(mode === 'automatic' ? 'Switched to AUTOMATIC mode' : 'Switched to MANUAL mode');
}

/**
 * Updates the UI based on the given state
 * @param mode the state
 */
function applyUIForMode(mode: Mode): void {
  btnAuto.className = 'mode-btn';
  btnManual.className = 'mode-btn';

  pill.className = 'status-pill status-' + mode.replace(' ', '_');
  dot.className = 'status-dot dot-' + mode.replace(' ', '_');
  label.textContent = mode === 'not_available' ? 'NOT AVAILABLE' : mode.toUpperCase();

  const inoperable = mode === 'not_available' || mode === 'unconnected';
  btnAuto.disabled = inoperable;
  btnManual.disabled = inoperable;

  if (mode === 'automatic') {
    btnAuto.classList.add('active-auto');
    valveCtrl.classList.add('disabled');
    applyBtn.disabled = true;
    infoCus.textContent = 'Connected';
    infoCus.className = 'info-val ok';
    infoWcs.textContent = 'Connected';
    infoWcs.className = 'info-val ok';
  } else if (mode === 'manual') {
    btnManual.classList.add('active-manual');
    valveCtrl.classList.remove('disabled');
    applyBtn.disabled = false;
  } else if (mode === 'unconnected') {
    valveCtrl.classList.add('disabled');
    applyBtn.disabled = true;
    infoCus.textContent = 'Disconnected';
    infoCus.className = 'info-val warn';
  } else if (mode === 'not_available') {
    valveCtrl.classList.add('disabled');
    applyBtn.disabled = true;
    infoCus.textContent = 'Unreachable';
    infoCus.className = 'info-val error';
    infoWcs.textContent = 'Unreachable';
    infoWcs.className = 'info-val error';
  }
}

/**
 * Sets the value to send to the server
 * @param val the slider value
 */
function onSliderInput(val: string): void {
  STATE.valvePending = parseInt(val, 10);
  (document.getElementById('slider-readout') as HTMLElement).textContent = val + '%';
}

/**
 * Changes the valve level
 */
function applyValve(): void {
  STATE.valveActual = STATE.valvePending;
  setGauge(STATE.valveActual);
  // call api post
  showToast(`Valve set to ${STATE.valveActual}% — command sent to WCS`);
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

function addMeasurement(waterReading: WaterLevel): void {
  const last = STATE.measurements[STATE.measurements.length - 1].value;
  let next = last + (Math.random() - 0.46) * 12;
  next = Math.max(10, Math.min(300, next));
  STATE.measurements.push({ value: Math.round(next * 10) / 10, measurementTime: Date.now.toString() });
  if (STATE.measurements.length > 500) STATE.measurements.shift();


}

async function updateUI() {
  try {
    const data: ServerData = await getUpdatedData();
    addMeasurement({ value: data.waterLevel, measurementTime: data.sampleTimestamp });
    setGauge(data.valveLevel);



    const now = new Date();
    (document.getElementById('info-update') as HTMLElement).textContent =
      pad(now.getHours()) + ':' + pad(now.getMinutes()) + ':' + pad(now.getSeconds());
  } catch (error) {
    STATE.mode = 'not_available';
  }
  updateChart();
}

let toastTimer: ReturnType<typeof setTimeout> | undefined;

function showToast(msg: string): void {
  const t = document.getElementById('toast') as HTMLElement;
  t.textContent = msg;
  t.classList.add('show');
  clearTimeout(toastTimer);
  toastTimer = setTimeout(() => t.classList.remove('show'), 2800);
}

buildChart(STATE.measurements.slice(-STATE.N));
updateStats(STATE.measurements.slice(-STATE.N).map((reading) => reading.value));
setGauge(STATE.valveActual);
(document.getElementById('valve-slider') as HTMLInputElement).value = String(STATE.valveActual);
(document.getElementById('slider-readout') as HTMLElement).textContent = STATE.valveActual + '%';
applyUIForMode('automatic');

setInterval(updateClock, 1000);
setInterval(updateUptime, 1000);
setInterval(updateUI, 2000);
updateClock();

export { setMode, onSliderInput, applyValve, addMeasurement, setGauge };
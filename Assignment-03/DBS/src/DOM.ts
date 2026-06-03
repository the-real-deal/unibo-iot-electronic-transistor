import { setMode, onSliderInput, applyValve } from "./main";
import type { Mode } from "./data";

const btnAuto = document.getElementById('btn-auto') as HTMLButtonElement;
const btnManual = document.getElementById('btn-manual') as HTMLButtonElement;
const valveCtrl = document.getElementById('valve-ctrl') as HTMLElement;
const applyBtn = document.getElementById('apply-btn') as HTMLButtonElement;
const pill = document.getElementById('status-pill') as HTMLElement;
const dot = document.getElementById('status-dot') as HTMLElement;
const label = document.getElementById('status-label') as HTMLElement;

const infoCus = document.getElementById('info-cus') as HTMLElement;
const infoWcs = document.getElementById('info-wcs') as HTMLElement;

document.getElementById('btn-auto')?.addEventListener('click', () => {
    setMode('automatic');
});

document.getElementById('btn-manual')?.addEventListener('click', () => {
    setMode('manual');
});

const slider: HTMLInputElement = (document.getElementById('valve-slider')! as HTMLInputElement);

slider.addEventListener('change', () => {
    onSliderInput(slider.value);
});

document.getElementById('apply-btn')?.addEventListener('click', () => {
    applyValve();
});

// (document.getElementById('n-select') as HTMLSelectElement).addEventListener('change', function (this: HTMLSelectElement) {
//     STATE.N = parseInt(this.value, 10);
//     (document.getElementById('chart-subtitle') as HTMLElement).textContent = `Last ${STATE.N} measurements · live feed`;
//     updateChart();
//   });


/**
 * Updates the UI based on the given state
 * @param mode the state
 */
export function applyUIForMode(mode: Mode): void {
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
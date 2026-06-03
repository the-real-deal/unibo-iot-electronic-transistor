import { setMode, onSliderInput, applyValve } from "./main";

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
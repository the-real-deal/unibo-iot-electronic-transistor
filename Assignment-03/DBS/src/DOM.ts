import { setMode, onSliderInput, applyValve } from "./main";

document.getElementById('btn-auto')?.addEventListener('click', () => {
    setMode('AUTOMATIC');
});

document.getElementById('btn-manual')?.addEventListener('click', () => {
    setMode('MANUAL');
});

const slider: HTMLInputElement = (document.getElementById('valve-slider')! as HTMLInputElement);

slider.addEventListener('change', () => {
    onSliderInput(slider.value);
});

document.getElementById('apply-btn')?.addEventListener('click', () => {
    applyValve();
});
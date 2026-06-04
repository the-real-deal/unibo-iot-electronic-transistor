import type { Mode } from "./data";

const VALID_MODES: Mode[] = ['automatic', 'manual', 'unconnected', 'not_available'];

/**
 * Checks if the string value is a valid state
 * @param value The string literal
 * @returns true if the string is a valid mode
 */
export function isMode(value: string): value is Mode {
    return VALID_MODES.includes(value as Mode);
}

/**
 * Used to display dates and time stamps
 * @param n 
 * @returns 
 */
export function pad(n: number): string {
    return n.toString().padStart(2, '0');
}
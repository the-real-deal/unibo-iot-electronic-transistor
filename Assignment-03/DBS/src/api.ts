import type { Mode, ServerData } from "./data";

const server = "http://localhost:8080";

/**
 * Fetches the data from the server
 * @returns a ServerData object
 *{
 *  "waterLevel":"1",
 *  "sampleTimestamp":"19:00",
 *  "currentState":"unconnected",
 *  "valveLevel":"30%"
 * } 
 */
export async function getUpdatedData() {
    const res = await fetch(`${server}/updateUI`);
    if (!res.ok) throw new Error(`HTTP error: ${res.status}`);
    return await res.json() as ServerData;
}

/**
 * Signals a state change to the server.
 * Does nothing if posting the states unconnected or not_available
 * @param state the new state
 */
export async function changeState(state: Mode) {
    if (state === 'not_available' || state === 'unconnected') return;
    const res = await
        fetch(`${server}/interaction/state`, {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ currentState: state })
        });
    if (!res.ok) throw new Error(`HTTP error: ${res.status}`);
}

/**
 * Signals the server to change the valve opening level.
 * Does nothing if the valve level is not between 0 and 100
 * @param state the new state
 */
export async function changeValveLevel(level: number) {
    if (level < 0 || level > 100) return;
    const res = await
        fetch(`${server}/interaction/valve`, {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ valveLevel: level })
        });
    if (!res.ok) throw new Error(`HTTP error: ${res.status}`);
}
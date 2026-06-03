export type Mode = 'automatic' | 'manual' | 'unconnected' | 'not_available';

export interface AppState {
    mode: Mode;
    valveActual: number;
    valvePending: number;
    measurements: WaterLevel[];
    N: number;
    startTime: number;
}

export interface WaterLevel {
    value: number,
    measurementTime: string
}

export interface ServerData {
    waterLevel: number;
    sampleTimestamp: string;
    currentState: string;
    valveLevel: number;
}
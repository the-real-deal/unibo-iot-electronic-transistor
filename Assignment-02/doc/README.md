# Assignment #02 – Smart Drone Hangar
### Embedded Systems and IoT – ISI LT – a.y. 2025/2026

---

**Authors:** Gioele Foschi, Matteo Tonelli, Manuel Benagli  
**Student IDs:**
**Date:**

---

## 1. System Overview

Brief description of the system and its purpose.

> The *Smart Drone Hangar* is an embedded system composed of two subsystems: the **Drone Hangar** (Arduino-based) and the **Drone Remote Unit** (PC-based), communicating over a serial line.

---

## 2. Parameter Choices

The following values were chosen for the configurable parameters:

| Parameter | Value | Description |
|-----------|-------|-------------|
| `D1` | 1cm | Distance threshold for drone exit detection |
| `D2` | 1cm | Distance threshold for drone landing detection |
| `T1` | 5s | Time the distance must exceed D1 to confirm exit |
| `T2` | 5s | Time the distance must stay below D2 to confirm landing |
| `T3` | 5s | Time above Temp1 before entering pre-alarm |
| `T4` | 5s | Time above Temp2 before entering full alarm |
| `Temp1` | 27 °C | Pre-alarm temperature threshold |
| `Temp2` | 30 °C | Full alarm temperature threshold |

---

## 3. Architecture
### 3.1 Finite State Machines

![FSMDiagram](Assignment#2-State.png)

| State | Description | Transitions |
|-------|-------------|-------------|
| `Idle` | Drone at rest inside hangar. L1 on. | `TakeOff` cmd → `TakingOff` |
| `TakingOff` | Door open, waiting for drone to exit. L2 blinks. | dist > D1 for T1 s → `Operating` |
| `Operating` | Drone outside, door closed. | `Land` cmd + DPD detected → `Landing` |
| `Landing` | Door open, waiting for drone to land. L2 blinks. | dist < D2 for T2 s → `Idle` |
| `Stopped` | All ops suspended. | Wait for *security state* **reset** |
| `Normal` | Normal behaviour | dist < D2 for T2 s → `Idle` |
| `Warning` | High temp detected; new ops suspended. | temp < Temp1 → ``; temp ≥ Temp2 for T4 s → `Alarm` |
| `Danger` | Full alarm. L3 on. All ops suspended. | `RESET` pressed → `Normal` |

The system relies on a main handler class (`Context`) that maintains the two concurrent states:
- `HangarState` (`Idle`, `Operating`, `TakeOff`, `Landing`)
- `Security State` (`Normal`, `Warning`, `Danger`)


#### 3.1.1 Hangar States
> The hangar states are only able to iterate between each other in a loop:
- `Idle`,  `TakeOff`, `Operating`, `Landing`, `Idle`, etc...

Upon entering in one state, the state itself adds to the scheduler the tasks it needs to operate.
- E.g. `IdleState` adds the temperature reading task and the `DRUReceiver`.
- The state keeps track of the tasks it created by adding the task id to a list, so they can be identified and removed later.

Once the tasks are initialized, the states starts checking for the condition to change state.
After the condition are met, the current states it signals to the scheduler to remove the tasks it added and calls for a context switch.

#### 3.1.2 Security States
> The security states iterates between each other but are able to change the hangar state.

If for some reason the security state becomes `Danger` the security state changes the hangar state (whatever it is) to be the stopped state, where everything is halted.security state

Security states have a special function: `canReceiveMessage`.
- This function is called every time the arduino receives a message, if the current states allows new oncoming messages then it will return `true`, `false` otherwise.

### 3.2 Task-Based Architecture (Arduino)
The Arduino software is structured around the following concurrent tasks:

| Task | Period | Description |
|------|--------|-------------|
| `TaskDPD` | Every Scheduler Tick | Reads the PIR sensor (Drone Presence Detector) |
| `TaskDDD` | Every Scheduler Tick | Reads the sonar (Drone Distance Detector) |
| `TaskTemp` | Every Scheduler Tick | Reads the temperature sensor |
| `TaskServo` | Every Scheduler Tick | Controls the servo motor (Hangar Door) |
| `LEDBLink` | 500 ms | Makes a specific led blink |
| `TaskSerial` | 50 ms | Handles serial communication with the DRU |
| `DRUDistance` | 400 ms | Sends to the DRU the current distance from the drone |
| `ButtonTask` | Every Scheduler Tick | Checks if a button is pressed |

Some task are special task, these task can trigger a context switch, these task have a special parameter in its constructor:
- `ContextType`, an `enum` class that indicates wich state should be called for the context switch check.

## 5. Hardware Schema

![Breadboard Schema](./Assignment#2.png)


## 8. Demo Video

> See `doc/Assignment#02.mp4`

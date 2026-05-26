# Arduino for IoT – Group Project  
**Computer Science and Engineering – University of Bologna (UniBO)**  
**Academic Year 2024/2025**

---

## 📘 Overview
This repository contains the work developed for the **Arduino for IoT** group project, part of the *Computer Science and Engineering* program at the **University of Bologna (UniBO)**, A.Y. 2024/25.

The project focuses on the design and implementation of **embedded systems** and **Internet of Things (IoT)** applications using **Arduino-based hardware**, with the goal of combining hardware prototyping and cloud integration.

---

## 👥 Group Information
- [Benagli Manuel](https://github.com/MmanuBen)
- [Foschi Gioele](https://github.com/delpiter)  
- [Tonelli Matteo](https://github.com/MatteoTonelli05)  

---

## 🧩 Assignments
The project is structured into three main assignments, progressively covering different aspects of Arduino-based IoT systems.

| Assignment | Description | Link |
|-------------|--------------|------|
| **Assignment 01** | First phase of the project – hardware setup and basic sensor interaction. | [![github](https://img.shields.io/badge/GitHub-000000?style=for-the-badge&logo=GitHub&logoColor=white)](https://github.com/pslab-unibo/esiot-2025-2026/blob/master/assignments/assignment-01.md) |
| **Assignment 02** | Second phase – OOP and Final State Machines. | [![github](https://img.shields.io/badge/GitHub-000000?style=for-the-badge&logo=GitHub&logoColor=white)](https://github.com/pslab-unibo/esiot-2025-2026/blob/master/assignments/assignment-02.md) |
| **Assignment 03** | Third phase – advanced IoT integration and cloud connectivity. | [![github](https://img.shields.io/badge/GitHub-000000?style=for-the-badge&logo=GitHub&logoColor=white)](https://github.com/pslab-unibo/esiot-2025-2026/blob/master/assignments/assignment-03.md) |

Each assignment has its own directory containing source code, documentation, and a brief report.

---

## ⚙️ Repository Structure
```
├── Assignment-01
│   ├── platformio.ini
│   ├── src
│   │   ├── main.cpp
│   │   ├── model
│   │   │   ├── TournOnSequence.cpp
│   │   │   └── TournOnSequence.h
│   │   ├── utils.cpp
│   └── test
│       └── README
├── Assignment-02
│   ├── doc
│   │   └── README.md
│   ├── droneHangar
│   │   ├── platformio.ini
│   │   └── src
│   │       ├── config.h
│   │       ├── devices
│   │       ├── kernel
│   │       ├── main.cpp
│   │       └── model
│   └── droneRemoteUnit
│       └── src
│           └── esiot
│               └── serial
│                   └── DroneRemoteUnitGUI.java
├── Assignment-03
│   ├── CUS
│   │   ├── build.gradle.kts
│   │   ├── gradle
│   │   └── src
│   │       └── main
│   │           └── java
│   │               └── it
│   │                   └── unibo
│   │                       └── iot
│   │                           └── Server.java
│   │
│   ├── DBS
│   │   └── index.html
│   ├── doc
│   │   └── README.md
│   ├── TMS
│   │   ├── platformio.ini
│   │   └── src
│   │       └── main.cpp
│   └── WCS
│       ├── platformio.ini
│       └── src
│           └── main.cpp
└── README.md ← (this file)
```

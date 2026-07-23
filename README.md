# TurtleBot3 Navigation2 Offloading with YOLO

> ROS 2 Jazzy 기반 TurtleBot3 자율주행 프로젝트  
> Navigation2와 YOLO를 이용해 물체를 인식하고 목표 위치까지 자율주행하는 시스템을 구현했다.

---

## Overview

이 프로젝트는 DGIST Nav2gather 프로젝트를 기반으로 진행한 Navigation2 실습 프로젝트이다.

기존에는 사용자가 RViz에서 직접 목적지를 지정해야 했지만,
YOLO 객체 인식을 이용해 로봇이 물체를 인식하고 목표 위치를 생성하여
Navigation2를 통해 자율주행하도록 구현했다.

모든 Navigation 연산은 Remote PC에서 수행하고,
TurtleBot3는 LiDAR, Camera, Motor만 담당하는 Offloading 구조를 사용했다.

---

## Demo

### Navigation2

- SLAM Mapping
- Map Saving
- AMCL Localization
- Navigation2 Autonomous Navigation

### Vision

- USB Webcam (Logitech C920)
- ROS2 Camera Driver
- YOLO Object Detection
- Camera TF

### Behavior

- YOLO Detection Subscriber
- Object Position Estimation
- Goal Generation
- Nav2 Simple Commander
- Automatic Navigation

---

## System Architecture

```text
           Remote PC
 ┌─────────────────────────────┐
 │ Navigation2                 │
 │ RViz2                       │
 │ YOLO                        │
 │ Behavior                    │
 └──────────────▲──────────────┘
                │ ROS 2 DDS
────────────────┼────────────────
                │
 ┌──────────────┴──────────────┐
 │ TurtleBot3 Burger           │
 │                             │
 │ LiDAR                       │
 │ USB Webcam                  │
 │ OpenCR                      │
 │ Motor Controller            │
 └─────────────────────────────┘
```

---

## Project Flow

```text
Bringup
   ↓
SLAM
   ↓
Map Save
   ↓
Navigation2
   ↓
USB Webcam
   ↓
YOLO Detection
   ↓
Target Position Estimation
   ↓
Goal Generation
   ↓
Autonomous Navigation
```

---

## Development Environment

### Hardware

- TurtleBot3 Burger
- Raspberry Pi 4
- OpenCR
- LDS LiDAR
- Logitech C920 Webcam

### Software

- Ubuntu 24.04
- ROS 2 Jazzy
- Navigation2
- Cartographer
- RViz2
- YOLO ROS

---

## Implemented Features

- ✔ TurtleBot3 Bringup
- ✔ Keyboard Teleoperation
- ✔ Cartographer SLAM
- ✔ Map Generation
- ✔ Navigation2
- ✔ USB Webcam Integration
- ✔ YOLO Object Detection
- ✔ Camera TF Configuration
- ✔ Object Position Estimation
- ✔ Automatic Goal Generation
- ✔ Nav2 Simple Commander
- ✔ Autonomous Navigation

---

## Repository

```
docs/
 ├── guidebook.md
 └── troubleshooting.md

turtlebot3_ws/

yolo_ws/
 └── src/
      ├── nav2_behavior
      └── ...
```

---

## Results

- Navigation2를 이용한 실내 자율주행
- YOLO 기반 실시간 객체 인식
- Webcam 기반 영상 송수신
- Camera TF 구성
- 객체 좌표 생성
- Navigation Goal 자동 생성
- 객체 위치까지 자율주행

---

## Documentation

프로젝트 설치 과정과 Troubleshooting은 아래 문서에 정리했다.

- docs/guidebook.md
- docs/troubleshooting.md

---

## Future Work

- LiDAR + Camera Fusion
- Multiple Object Navigation
- Behavior Tree 기반 의사결정
- Multi-Robot Navigation

# TurtleBot3 Navigation2 Offloading with YOLO

> ROS 2 Jazzy · Navigation2 · TurtleBot3 · YOLO · Autonomous Navigation

Navigation2 기반 TurtleBot3 자율주행 프로젝트이다.

TurtleBot3 Burger에서 센서 데이터만 수집하고, Navigation2와 YOLO 연산은 Remote PC에서 수행하는 **Offloading Architecture**를 적용하였다.

USB Webcam으로 객체를 인식하고, YOLO Detection 결과를 Navigation Goal로 변환하여 로봇이 목표 위치까지 스스로 이동하도록 구현하였다.

> DGIST Nav2gather Summer Internship Project

## Features

- Navigation2 기반 자율주행
- Cartographer SLAM
- AMCL Localization
- USB Webcam Streaming
- YOLO Object Detection
- Camera TF Configuration
- Object Position Estimation
- Goal Generation
- Nav2 Simple Commander
- Autonomous Object Navigation

## System Architecture

```text
             Remote PC
    ┌────────────────────────┐
    │ Navigation2            │
    │ Cartographer           │
    │ RViz2                  │
    │ YOLO                   │
    │ Behavior               │
    └──────────▲─────────────┘
               │ ROS 2 DDS
───────────────┼────────────────
               │
    ┌──────────┴─────────────┐
    │ TurtleBot3 Burger      │
    │                        │
    │ Raspberry Pi 4         │
    │ OpenCR                 │
    │ LDS LiDAR              │
    │ USB Webcam             │
    └────────────────────────┘
```

## Project Pipeline

```text
Bringup
    │
    ▼
SLAM Mapping
    │
    ▼
Map Saving
    │
    ▼
Navigation2
    │
    ▼
USB Webcam
    │
    ▼
YOLO Detection
    │
    ▼
Object Position Estimation
    │
    ▼
Goal Generation
    │
    ▼
Autonomous Navigation
```

## Tech Stack

| Category | Stack |
|----------|-------|
| OS | Ubuntu 24.04 |
| Middleware | ROS 2 Jazzy |
| Robot | TurtleBot3 Burger |
| Navigation | Navigation2, Cartographer |
| Vision | USB Webcam, YOLO ROS |
| Visualization | RViz2 |
| Language | Python, C++ |

## Repository

```text
.
├── docs
│   ├── guidebook.md
│   └── troubleshooting.md
├── turtlebot3_ws
├── yolo_ws
│   └── src
│       ├── nav2_behavior
│       ├── cup_localizer.py
│       └── ...
└── README.md
```

## Results

- Navigation2 Offloading 성공
- SLAM Mapping 및 Localization 완료
- USB Webcam ROS2 연동
- YOLO 실시간 객체 인식
- Camera TF 구성
- 객체 좌표 추정
- Navigation Goal 자동 생성
- 목표 위치까지 자율주행

## Documentation

프로젝트를 처음부터 재현할 수 있도록 설치 과정과 실행 방법을 정리하였다.

- Guidebook
- Troubleshooting

## Future Work

- Multi Object Navigation
- LiDAR-Camera Sensor Fusion
- Behavior Tree 기반 의사결정
- Multi Robot Navigation

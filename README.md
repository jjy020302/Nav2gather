# ROS 2 Navigation2 기반 객체 인식 자율주행 시스템 구현

> DGIST CPS Lab 하계 인턴십 프로젝트

ROS 2 Navigation2와 YOLO를 결합하여 TurtleBot3가 실내 환경에서 물병을
인식하고 자율적으로 이동하는 시스템을 구현하였다.

> **대표 이미지 삽입**
>
> `docs/images/main_demo.png`

## 프로젝트 목표

-   Cartographer 기반 SLAM
-   Navigation2 기반 자율주행
-   YOLO 기반 물병 인식
-   객체 위치 추정 및 TF 좌표 변환
-   Behavior 기반 객체 탐색 및 접근
-   Frontier Exploration 연동 구조 구성

## 시스템 구성

> **시스템 구성도 삽입**
>
> `docs/images/system_architecture.png`

``` text
USB Webcam
    │
GStreamer
    │
Remote PC
 ├─ YOLO ROS
 ├─ Object Localizer
 ├─ Navigation2
 └─ Behavior
    │
ROS 2 Network
    │
Raspberry Pi
    │
TurtleBot3
```

## 개발 환경

  항목         내용
  ------------ ----------------------
  Robot        TurtleBot3 Burger
  SBC          Raspberry Pi 4
  OS           Ubuntu 22.04 / 24.04
  ROS          ROS 2 Jazzy
  SLAM         Cartographer
  Navigation   Navigation2
  Detection    YOLO ROS
  Camera       Logitech C920
  Language     Python 3

## 주요 기능

### SLAM

Cartographer를 이용하여 실내 지도를 생성하고 저장하였다.

> `docs/images/slam_mapping.png`

### Navigation2

생성한 지도를 기반으로 목표 지점까지 자율주행을 수행하였다.

> `docs/images/navigation2_result.png`

### YOLO Object Detection

USB 웹캠 영상을 이용하여 물병을 실시간으로 인식하였다.

> `docs/images/yolo_detection.png`

### Object Localization

YOLO와 LiDAR 데이터를 이용하여 객체의 위치를 추정하였다.

> `docs/images/object_localization.png`

### TF Transformation

객체 좌표를 `camera_optical_frame`에서 `map` 좌표계로 변환하였다.

> `docs/images/tf_tree.png`

### Behavior

> `docs/images/behavior_flow.png`

``` text
SEARCHING
    ↓
ALIGNING
    ↓
COLLECTING
    ↓
NAVIGATING
    ↓
COOLDOWN
```

동작 과정

1.  물병 탐색
2.  객체 정렬
3.  좌표 평균화
4.  Navigation2 목표 생성
5.  물병 앞으로 이동
6.  방문 객체 저장
7.  다음 물병 탐색

## 실행 결과

> **시연 GIF 삽입**
>
> `docs/images/behavior_demo.gif`

  기능                   상태
  ---------------------- ------------
  TurtleBot3 Bringup     ✅
  Cartographer SLAM      ✅
  Navigation2            ✅
  YOLO Detection         ✅
  Object Localization    ✅
  TF Transformation      ✅
  Behavior               ✅
  Multi-object Search    ✅
  Frontier Integration   ✅
  Frontier Validation    🔄 진행 중

## 프로젝트 구조

``` text
Nav2gather/
├── README.md
├── docs/
│   ├── 01_Installation.md
│   ├── 02_SLAM_Navigation.md
│   ├── 03_Webcam_Setup.md
│   ├── 04_YOLO_Localizer.md
│   ├── 05_Behavior.md
│   ├── troubleshooting.md
│   └── images/
├── nav2_behavior/
└── maps/
```

## 향후 계획

-   Frontier Exploration 실환경 검증
-   Recovery Behavior 추가
-   객체 위치 추정 정확도 향상
-   다양한 객체 탐색 지원
-   동적 장애물 대응

## 참고 문서

-   `docs/01_Installation.md`
-   `docs/02_SLAM_Navigation.md`
-   `docs/03_Webcam_Setup.md`
-   `docs/04_YOLO_Localizer.md`
-   `docs/05_Behavior.md`
-   `docs/troubleshooting.md`

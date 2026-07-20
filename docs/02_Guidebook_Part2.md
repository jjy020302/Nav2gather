# 02_Guidebook_Part2

## Part 2. SLAM 및 Navigation2 자율주행

본 문서에서는 Cartographer를 이용하여 TurtleBot3 주변 환경의 지도를 생성하고, 생성한 지도를 기반으로 Navigation2를 이용한 자율주행을 수행하는 과정을 설명한다.

SLAM을 통해 생성한 지도에서 AMCL(Localization)을 이용하여 현재 위치를 추정하고, Navigation2를 이용하여 목표 지점까지 자율주행을 수행한다.

이 문서를 완료하면 TurtleBot3가 생성한 지도를 기반으로 현재 위치를 추정하고, 목표 지점까지 자율주행하는 과정을 구현할 수 있다.

## 목차

1. [SLAM을 이용한 지도 생성](#1-slam을-이용한-지도-생성)
2. [Navigation2 실행](#2-navigation2-실행)
3. [Localization](#3-localization)
4. [목표 지점 설정 및 자율주행](#4-목표-지점-설정-및-자율주행)

---

## 1. SLAM을 이용한 지도 생성

SLAM(Simultaneous Localization and Mapping)은 로봇이 주변 환경을 탐색하면서 자신의 위치를 추정하고 지도를 생성하는 기술이다. TurtleBot3에서는 Cartographer 패키지를 이용하여 LiDAR 센서 데이터를 기반으로 SLAM을 수행한다.

본 단계에서는 TurtleBot3 Bringup을 실행한 후 Cartographer를 이용하여 지도를 생성하고, Teleoperation으로 로봇을 이동시키며 주변 환경을 탐색한다. 지도 생성이 완료되면 Navigation2에서 사용할 수 있도록 지도를 저장한다.

### 1.1 TurtleBot3 Bringup 실행

먼저 Raspberry Pi에서 TurtleBot3 Bringup을 실행한다.

**실행 위치:** 🍓 Raspberry Pi (SSH 접속 후)

```bash
export TURTLEBOT3_MODEL=burger

ros2 launch turtlebot3_bringup robot.launch.py
```

Bringup이 정상적으로 실행되면 LiDAR, IMU, OpenCR 및 모터 제어 노드가 활성화되며 TurtleBot3의 센서 데이터와 제어 Topic이 생성된다.

### 1.2 Cartographer 실행

새 터미널을 열어 Remote PC에서 Cartographer를 실행한다.

**실행 위치:** 💻 Remote PC

```bash
export TURTLEBOT3_MODEL=burger

ros2 launch turtlebot3_cartographer cartographer.launch.py
```

RViz가 실행되며 TurtleBot3 주변 환경의 지도를 실시간으로 생성할 수 있다.

### 1.3 Teleoperation으로 지도 생성

새 터미널을 열어 Teleoperation을 실행한 후 TurtleBot3를 천천히 이동시키며 주변 환경을 탐색한다.

**실행 위치:** 💻 Remote PC

```bash
export TURTLEBOT3_MODEL=burger

ros2 run turtlebot3_teleop teleop_keyboard
```

로봇을 벽과 장애물을 따라 천천히 이동시키면 LiDAR 데이터를 기반으로 지도가 생성된다. 시작 위치와 탐색이 끝난 위치가 최대한 일치하도록 이동하면 보다 정확한 지도를 생성할 수 있다.

<p align="center">
  <img src="../images/part2/slam_mapping.png" width="700">
</p>

<p align="center">
그림 2-1. Cartographer를 이용한 지도 생성
</p>

### 1.4 지도 저장

지도 생성이 완료되면 Navigation2에서 사용할 수 있도록 지도를 저장한다.

**실행 위치:** 💻 Remote PC

```bash
ros2 run nav2_map_server map_saver_cli -f ~/map
```

명령이 정상적으로 실행되면 홈 디렉터리에 다음 파일이 생성된다.

```text
~/map.pgm
~/map.yaml
```

생성된 `map.yaml`과 `map.pgm` 파일은 이후 Navigation2에서 사용할 지도 파일이다.

## 2. Navigation2 실행

Navigation2는 저장한 지도를 기반으로 TurtleBot3의 현재 위치를 추정하고, 목표 지점까지 자율주행을 수행하는 ROS 2 패키지이다.

본 단계에서는 저장한 지도를 불러와 Navigation2를 실행하고, RViz에서 지도와 Navigation2 노드가 정상적으로 로드되는지 확인한다. Raspberry Pi에서는 Bringup을 계속 실행한 상태를 유지하며, Navigation2는 Remote PC에서 실행한다.

### 2.1 Navigation2 실행

새 터미널을 열어 TurtleBot3 모델을 설정한 후 Navigation2를 실행한다.

**실행 위치:** 💻 Remote PC

```bash
export TURTLEBOT3_MODEL=burger

ros2 launch turtlebot3_navigation2 navigation2.launch.py map:=$HOME/map.yaml
```

실행이 완료되면 RViz가 실행되며 저장한 지도와 Navigation2 관련 노드가 함께 로드된다.

이 단계에서는 Raspberry Pi에서 Bringup을 종료하지 않고 계속 실행한 상태를 유지해야 한다.

<p align="center">
  <img src="../images/part2/navigation2_rviz.png" width="700">
</p>

<p align="center">
그림 2-2. Navigation2 실행 화면
</p>

## 3. Localization

Localization은 저장한 지도와 LiDAR 센서 데이터를 이용하여 TurtleBot3의 현재 위치를 추정하는 과정이다. Navigation2에서는 AMCL(Adaptive Monte Carlo Localization)을 이용하여 로봇의 위치를 지속적으로 추정한다.

자율주행을 시작하기 전에 현재 위치를 정확하게 인식할 수 있도록 초기 위치를 설정한다.

### 3.1 초기 위치 설정

RViz 상단 메뉴에서 **2D Pose Estimate**를 선택한다.

현재 TurtleBot3가 위치한 지점을 클릭한 후 로봇이 바라보는 방향으로 드래그하여 초기 자세를 설정한다.

초기 위치가 정상적으로 설정되면 LiDAR Scan과 저장된 지도가 서로 일치하며, 현재 위치가 안정적으로 추정된다.

<p align="center">
  <img src="../images/part2/2d_pose_estimate.png" width="700">
</p>

<p align="center">
그림 2-3. RViz에서 2D Pose Estimate를 이용한 초기 위치 설정
</p>

## 4. 목표 지점 설정 및 자율주행

Navigation2는 사용자가 지정한 목표 지점까지 최적의 경로를 생성하고, 장애물을 회피하며 자율주행을 수행한다.

본 단계에서는 RViz에서 목표 위치를 지정하고 TurtleBot3가 생성된 경로를 따라 목적지까지 이동하는지 확인한다.

### 4.1 Nav2 Goal 설정

RViz 상단 메뉴에서 **Nav2 Goal**을 선택한다.

이동하려는 위치를 클릭한 후 이동 방향으로 드래그하여 목표 자세를 지정한다.

목표가 설정되면 Navigation2가 자동으로 경로를 생성하며 TurtleBot3가 목표 지점까지 자율주행을 시작한다.

<p align="center">
  <img src="../images/part2/nav2_goal.png" width="700">
</p>

<p align="center">
그림 2-4. Nav2 Goal을 이용한 목표 지점 설정
</p>

### 4.2 자율주행 확인

자율주행이 정상적으로 수행되면 다음과 같은 과정을 확인할 수 있다.

- AMCL을 이용하여 현재 위치가 지속적으로 업데이트된다.
- 목표 지점까지의 이동 경로(Path)가 생성된다.
- 장애물을 회피하며 생성된 경로를 따라 이동한다.
- 목표 지점에 도착하면 Navigation이 종료된다.

<p align="center">
  <img src="../images/part2/navigation_result.png" width="700">
</p>

<p align="center">
그림 2-5. Navigation2를 이용한 자율주행 결과
</p>

이상으로 Cartographer를 이용한 지도 생성부터 Localization, Navigation2를 이용한 자율주행까지의 전체 과정을 완료하였다. 생성한 지도는 이후 카메라 및 YOLO 기반 객체 인식과 Behavior Tree를 이용한 자율주행에서 활용된다.

## 실행 결과 확인

다음 항목을 모두 만족하면 Part 2를 정상적으로 완료한 것이다.

- [ ] Cartographer를 이용하여 지도를 생성하였다.
- [ ] `map.yaml`과 `map.pgm` 파일이 생성되었다.
- [ ] Navigation2가 정상적으로 실행되었다.
- [ ] 2D Pose Estimate를 이용하여 초기 위치를 설정하였다.
- [ ] Nav2 Goal을 이용하여 목표 지점까지 자율주행을 수행하였다.

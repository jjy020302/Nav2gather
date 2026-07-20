# 04_Troubleshooting

본 문서에서는 TurtleBot3 Bringup, Navigation2, Camera 및 YOLO 환경을 구축하는 과정에서 실제로 발생했던 주요 오류와 해결 방법을 정리하였다.

각 오류의 증상, 원인 및 해결 방법을 순서대로 제시하여 동일한 문제가 발생했을 때 빠르게 해결할 수 있도록 하였다.

## 오류 요약

| # | 문제 | 주요 원인 | 해결 방법 |
|:---:|---|---|---|
| 1 | OpenCR Firmware 업로드 실패 | Firmware 파일 경로 오류 | Firmware 파일의 절대경로 지정 |
| 2 | OpenCR Firmware 업로더 실행 오류 | 32비트 ARM 라이브러리 미설치 | `armhf` 아키텍처 및 `libc6:armhf` 설치 |
| 3 | TurtleBot3 Bringup 패키지를 찾을 수 없는 문제 | Workspace 빌드 또는 환경 적용 문제 | TurtleBot3 Workspace 환경 다시 적용 |
| 4 | Teleoperation 실행 시 TurtleBot3가 움직이지 않는 문제 | Teleoperation 실행 위치 오류 | Remote PC에서 Teleoperation 실행 |
| 5 | Raspberry Pi IP 주소 변경으로 SSH 및 ROS 2 통신 실패 | IP 주소 변경 및 `ROS_STATIC_PEERS` 불일치 | 현재 IP 확인 후 환경 변수 수정 |
| 6 | GStreamer 영상 수신 실패 | `udpsink host`에 이전 Remote PC IP 주소 사용 | 현재 Remote PC IP 주소로 송출 주소 변경 |
| 7 | Navigation2에서 Goal이 Abort되는 문제 | TF, Localization 또는 Navigation2 실행 상태 문제 | TF와 초기 위치를 확인한 후 Navigation2 재실행 |

---

## 1. OpenCR Firmware 업로드 실패

### 증상

Firmware 업로드 중 다음과 같은 오류가 발생한다.

```text
[NG] Unable to open burger.opencr
```

### 원인

Firmware 파일을 상대경로로 지정하여 `update.sh`가 `burger.opencr` 파일을 찾지 못한 경우이다.

### 해결 방법

Firmware 파일의 절대경로를 지정하여 다시 실행한다.

**실행 위치:** 💻 Remote PC

```bash
./update.sh $OPENCR_PORT ~/opencr_update/burger.opencr
```

Firmware 업로드가 정상적으로 완료되는 것을 확인한다.

## 2. OpenCR Firmware 업로더 실행 오류

### 증상

Firmware 업로드 중 다음과 같은 오류가 발생한다.

```text
./opencr_ld_shell_arm: cannot execute: required file not found
```

### 원인

Ubuntu 24.04(64-bit) 환경에서 OpenCR 업로더 실행에 필요한 32비트 ARM 라이브러리가 설치되어 있지 않은 경우 발생한다.

### 해결 방법

32비트 ARM 아키텍처와 라이브러리를 설치한 후 Firmware 업로드를 다시 수행한다.

**실행 위치:** 💻 Remote PC

```bash
sudo dpkg --add-architecture armhf
sudo apt update
sudo apt install libc6:armhf
```

설치가 완료되면 Firmware 업로드 명령을 다시 실행한다.

```bash
./update.sh $OPENCR_PORT ~/opencr_update/burger.opencr
```

Firmware 업로드가 정상적으로 완료되는 것을 확인한다.

## 3. TurtleBot3 Bringup 패키지를 찾을 수 없는 문제

### 증상

Bringup 실행 시 다음과 같은 오류가 발생한다.

```text
Package 'turtlebot3_bringup' not found
```

### 원인

다음과 같은 경우에 발생할 수 있다.

- TurtleBot3 Workspace가 정상적으로 빌드되지 않은 경우
- TurtleBot3 Workspace 환경이 현재 터미널에 적용되지 않은 경우

### 해결 방법

먼저 TurtleBot3 Workspace 환경을 다시 적용한다.

**실행 위치:** 🍓 Raspberry Pi (SSH 접속 후)

```bash
source ~/turtlebot3_ws/install/setup.bash
```

환경이 정상적으로 적용되었는지 확인한다.

```bash
echo $AMENT_PREFIX_PATH
```

정상적으로 적용되면 TurtleBot3 Workspace 경로와 ROS 2 경로가 함께 출력된다.

```text
/home/csilab/turtlebot3_ws/install/turtlebot3_bringup
...
/opt/ros/jazzy
```

TurtleBot3 Workspace 경로가 출력되지 않는 경우 Workspace를 다시 빌드한다.

```bash
cd ~/turtlebot3_ws

colcon build --symlink-install
```

빌드가 완료되면 환경을 다시 적용한다.

```bash
source ~/turtlebot3_ws/install/setup.bash
```

이후 TurtleBot3 모델을 설정하고 Bringup을 실행한다.

```bash
export TURTLEBOT3_MODEL=burger

ros2 launch turtlebot3_bringup robot.launch.py
```

Bringup이 정상적으로 실행되고 TurtleBot3 관련 Topic이 생성되는지 확인한다.

```bash
ros2 topic list
```

## 4. Teleoperation 실행 시 TurtleBot3가 움직이지 않는 문제

### 증상

Teleoperation 화면에서는 `linear velocity`와 `angular velocity` 값이 정상적으로 변경되지만 TurtleBot3가 움직이지 않는다.

### 원인

Teleoperation 노드를 SSH로 Raspberry Pi에 접속한 터미널에서 실행한 경우 발생하였다.

TurtleBot3의 Bringup은 Raspberry Pi에서 실행하고, Teleoperation은 Remote PC에서 실행해야 한다.

### 해결 방법

Raspberry Pi에서는 Bringup을 실행한 상태로 유지한다.

**실행 위치:** 🍓 Raspberry Pi (SSH 접속 후)

```bash
export TURTLEBOT3_MODEL=burger

ros2 launch turtlebot3_bringup robot.launch.py
```

Remote PC의 별도 로컬 터미널에서 Teleoperation을 실행한다.

**실행 위치:** 💻 Remote PC

```bash
export TURTLEBOT3_MODEL=burger

ros2 run turtlebot3_teleop teleop_keyboard
```

키보드 입력에 따라 TurtleBot3가 정상적으로 이동하는지 확인한다.

## 5. Raspberry Pi IP 주소 변경으로 SSH 및 ROS 2 통신이 되지 않는 문제

### 증상

기존에 사용하던 SSH 명령으로 Raspberry Pi에 접속되지 않는다.

```bash
ssh csilab@10.8.141.26
```

다음과 같은 오류가 발생할 수 있다.

```text
ssh: connect to host 10.8.141.26 port 22: No route to host
```

또는 다음과 같이 출력될 수 있다.

```text
Connection timed out
```

SSH 접속은 가능하지만 Camera 또는 YOLO Topic이 나타나지 않는 경우도 있다.

```bash
ros2 topic list | grep camera
```

```bash
ros2 topic list | grep yolo
```

위 명령을 실행해도 아무 결과가 출력되지 않는다.

### 원인

Raspberry Pi는 DHCP를 통해 IP 주소를 자동으로 할당받는다.

전원을 다시 켜거나 네트워크에 재연결하면 Raspberry Pi의 IP 주소가 변경될 수 있다.

```text
기존 IP 주소: 10.8.141.26
변경된 IP 주소: 10.8.141.194
```

Raspberry Pi의 IP 주소가 변경되면 기존 IP 주소를 사용한 SSH 접속이 실패한다.

또한 Remote PC의 `ROS_STATIC_PEERS`에 이전 Raspberry Pi IP 주소가 저장되어 있으면 ROS 2 Discovery가 정상적으로 이루어지지 않아 Camera 및 YOLO Topic이 검색되지 않는다.

### 해결 방법

Raspberry Pi에서 현재 IP 주소를 확인한다.

**실행 위치:** 🍓 Raspberry Pi

```bash
hostname -I
```

또는 다음 명령으로 네트워크 인터페이스 정보를 확인한다.

```bash
ip addr
```

확인한 IP 주소를 사용하여 다시 SSH로 접속한다.

**실행 위치:** 💻 Remote PC

```bash
ssh csilab@10.8.141.194
```

Remote PC에서 현재 ROS 환경 변수를 확인한다.

```bash
env | grep ROS
```

`ROS_STATIC_PEERS`에 이전 Raspberry Pi IP 주소가 설정되어 있다면 현재 IP 주소로 변경한다.

```bash
export ROS_STATIC_PEERS=10.8.141.194
```

적용 여부를 확인한다.

```bash
echo $ROS_STATIC_PEERS
```

ROS 2 Daemon을 재시작한다.

```bash
ros2 daemon stop
ros2 daemon start
```

설정을 영구적으로 적용하기 위해 `.bashrc` 파일을 수정한다.

```bash
nano ~/.bashrc
```

기존 `ROS_STATIC_PEERS` 설정을 현재 Raspberry Pi의 IP 주소로 변경한다.

```bash
export ROS_STATIC_PEERS=10.8.141.194
```

설정을 현재 터미널에 적용한다.

```bash
source ~/.bashrc
```

Remote PC의 IP 주소가 변경된 경우에는 Raspberry Pi의 `ROS_STATIC_PEERS`도 현재 Remote PC의 IP 주소로 수정해야 한다.

먼저 Remote PC의 IP 주소를 확인한다.

**실행 위치:** 💻 Remote PC

```bash
hostname -I
```

Remote PC의 IP 주소를 확인한 후 Raspberry Pi의 `.bashrc` 파일을 수정한다.

**실행 위치:** 🍓 Raspberry Pi (SSH 접속 후)

```bash
nano ~/.bashrc
```

`ROS_STATIC_PEERS`를 현재 Remote PC의 IP 주소로 설정한다.

```bash
export ROS_STATIC_PEERS=10.8.133.189
```

설정을 적용한다.

```bash
source ~/.bashrc
```

양쪽 장치의 `ROS_DOMAIN_ID`가 동일한지도 확인한다.

```bash
echo $ROS_DOMAIN_ID
```

Remote PC와 Raspberry Pi 모두 동일한 값이 출력되어야 한다.

```text
30
```

이후 Topic 목록을 다시 확인한다.

```bash
ros2 topic list
```

## 6. Remote PC의 IP 주소 변경으로 GStreamer 영상이 수신되지 않는 문제

### 증상

Remote PC에서 카메라 영상이 표시되지 않거나 YOLO가 영상을 인식하지 못한다.

### 원인

GStreamer 송출 명령의 `udpsink host`에 이전 Remote PC의 IP 주소가 설정되어 있었다.

```text
udpsink host=10.8.141.25
```

Remote PC의 IP 주소가 변경되었음에도 기존 주소로 영상을 전송하여 영상이 정상적으로 수신되지 않았다.

### 해결 방법

Remote PC의 현재 IP 주소를 확인한다.

**실행 위치:** 💻 Remote PC

```bash
hostname -I
```

확인한 IP 주소를 GStreamer 송출 명령의 `udpsink host`에 적용한다.

**실행 위치:** 🍓 Raspberry Pi (SSH 접속 후)

```bash
gst-launch-1.0 v4l2src device=/dev/video0 ! \
image/jpeg,width=640,height=480,framerate=15/1 ! \
jpegparse ! \
rtpjpegpay ! \
udpsink host=10.8.133.189 port=5000
```

Remote PC에서 GStreamer 수신 명령을 실행한 후 영상이 정상적으로 표시되는지 확인한다.

## 7. Navigation2에서 Goal이 Abort되는 문제

### 증상

RViz에서 Nav2 Goal을 지정하면 경로가 생성되지만 로봇이 짧게 이동한 후 멈추거나, 주행 중 Goal이 Abort되며 자율주행이 중단된다.

다음과 같은 로그가 출력될 수 있다.

```text
Unable to transform robot pose into global plan's frame
```

```text
Controller failed
```

```text
Goal aborted
```

또는 다음과 같이 `odom` Frame을 찾을 수 없다는 메시지가 출력될 수 있다.

```text
Timed out waiting for transform from base_footprint to odom
```

```text
Invalid frame ID "odom"
```

### 원인

다음과 같은 경우에 발생할 수 있다.

- TurtleBot3 Bringup이 정상적으로 실행되지 않은 경우
- `map → odom → base_footprint` TF 연결이 정상적으로 생성되지 않은 경우
- RViz에서 초기 위치가 정확하게 설정되지 않은 경우
- AMCL Localization이 완료되지 않은 상태에서 Goal을 지정한 경우
- Navigation2 실행 중 센서 데이터 또는 TF의 시간 정보가 일치하지 않는 경우

### 해결 방법

먼저 Raspberry Pi에서 Bringup이 정상적으로 실행되고 있는지 확인한다.

**실행 위치:** 🍓 Raspberry Pi (SSH 접속 후)

```bash
export TURTLEBOT3_MODEL=burger

ros2 launch turtlebot3_bringup robot.launch.py
```

Remote PC에서 `/odom`, `/scan`, `/tf` Topic이 생성되는지 확인한다.

**실행 위치:** 💻 Remote PC

```bash
ros2 topic list
```

다음 Topic이 출력되는지 확인한다.

```text
/odom
/scan
/tf
/tf_static
```

`odom`과 `base_footprint` 사이의 TF를 확인한다.

```bash
ros2 run tf2_ros tf2_echo odom base_footprint
```

Translation과 Rotation 값이 지속적으로 출력되면 TF가 정상적으로 생성되고 있는 것이다.

Navigation2를 실행한다.

```bash
export TURTLEBOT3_MODEL=burger

ros2 launch turtlebot3_navigation2 navigation2.launch.py map:=$HOME/map.yaml
```

RViz에서 `2D Pose Estimate`를 선택한 후 지도상의 실제 로봇 위치와 방향을 다시 설정한다.

초기 위치 설정 후 로봇 주변의 LaserScan과 지도상의 장애물 위치가 일치하는지 확인한다.

TF 전체 연결 상태도 확인할 수 있다.

```bash
ros2 run tf2_ros tf2_monitor
```

다음과 같은 TF 연결이 정상적으로 유지되어야 한다.

```text
map → odom → base_footprint → base_link → base_scan
```

설정이 완료되면 RViz에서 Nav2 Goal을 다시 지정한다.

문제가 계속 발생하는 경우 Navigation2와 Bringup을 종료한 후 다음 순서로 다시 실행한다.

1. Raspberry Pi에서 TurtleBot3 Bringup 실행
2. Remote PC에서 Navigation2 실행
3. RViz에서 `2D Pose Estimate` 설정
4. Localization 상태 확인
5. Nav2 Goal 지정

TF와 Localization이 정상적으로 적용되면 Goal이 Abort되지 않고 목표 지점까지 자율주행이 수행된다.

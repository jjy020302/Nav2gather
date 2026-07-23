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
| 8 | 목표 지점보다 멀리서 도착 판정이 되는 문제 | `xy_goal_tolerance`와 `stop_distance`가 함께 적용됨 | Goal Checker와 Behavior 파라미터를 함께 조정 |

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

SSH 접속은 가능하지만 Remote PC에서 TurtleBot3의 Topic이 나타나지 않을 수도 있다.

**실행 위치:** 💻 Remote PC

```bash
ros2 topic list
```

정상적인 경우 Raspberry Pi에서 발행되는 다음과 같은 Topic이 표시되어야 한다.

```text
/battery_state
/imu
/joint_states
/odom
/scan
/sensor_state
/tf
/tf_static
```

하지만 통신에 문제가 있는 경우 다음과 같이 기본 Topic만 표시될 수 있다.

```text
/parameter_events
/rosout
```

또는 다음 명령을 실행해도 아무 결과가 출력되지 않는다.

```bash
ros2 topic list | grep -E "scan|odom|battery"
```

카메라와 YOLO를 실행한 상태에서도 관련 Topic이 나타나지 않을 수 있다.

```bash
ros2 topic list | grep camera
```

```bash
ros2 topic list | grep yolo
```

> Camera와 YOLO 노드는 주로 Remote PC에서 실행된다. 따라서 ROS 2 장치 간 통신 문제를 확인할 때는 Camera와 YOLO Topic보다 Raspberry Pi에서 발행되는 `/scan`, `/odom`, `/battery_state` Topic을 먼저 확인하는 것이 정확하다.

### 원인

Raspberry Pi와 Remote PC는 DHCP를 통해 IP 주소를 자동으로 할당받는다.

장치의 전원을 다시 켜거나 다른 네트워크에 연결하면 IP 주소가 변경될 수 있다.

예를 들어 Raspberry Pi의 IP 주소가 다음과 같이 변경될 수 있다.

```text
기존 Raspberry Pi IP: 10.8.141.26
변경된 Raspberry Pi IP: 10.8.141.194
```

Raspberry Pi의 IP 주소가 변경되면 기존 주소를 사용한 SSH 접속이 실패한다.

또한 Remote PC의 `ROS_STATIC_PEERS`에 이전 Raspberry Pi IP 주소가 저장되어 있으면 ROS 2 Discovery가 정상적으로 이루어지지 않는다.

반대로 Remote PC의 IP 주소가 변경되었는데 Raspberry Pi의 `ROS_STATIC_PEERS`에 이전 Remote PC IP 주소가 저장되어 있는 경우에도 같은 문제가 발생한다.

이외에도 다음 설정이 서로 다르면 ROS 2 통신이 되지 않을 수 있다.

* Remote PC와 Raspberry Pi의 `ROS_DOMAIN_ID`가 서로 다른 경우
* `ROS_LOCALHOST_ONLY=1`로 설정된 경우
* 두 장치가 서로 다른 네트워크에 연결된 경우
* `.bashrc`를 수정한 후 `source ~/.bashrc`를 실행하지 않은 경우
* 변경 전 환경을 사용 중인 ROS 2 Daemon이 계속 실행 중인 경우

### 해결 방법

#### 1. Raspberry Pi의 현재 IP 주소 확인

Raspberry Pi에 모니터와 키보드를 연결할 수 있다면 Raspberry Pi 터미널에서 현재 IP 주소를 확인한다.

**실행 위치:** 🍓 Raspberry Pi

```bash
hostname -I
```

출력 예시는 다음과 같다.

```text
10.8.141.194
```

여러 주소가 출력된다면 Remote PC와 같은 네트워크 대역에 있는 주소를 사용한다.

예를 들어 Remote PC의 주소가 `10.8.133.xxx` 또는 `10.8.141.xxx`라면 Raspberry Pi에서도 같은 네트워크에서 할당된 주소를 선택한다.

네트워크 인터페이스를 자세히 확인하려면 다음 명령을 사용한다.

```bash
ip addr
```

일반적으로 무선 네트워크를 사용하는 경우 `wlan0` 항목의 `inet` 주소를 확인한다.

예시:

```text
wlan0:
    inet 10.8.141.194/24
```

---

#### 2. 변경된 IP 주소로 SSH 접속

확인한 Raspberry Pi IP 주소를 사용하여 Remote PC에서 다시 SSH로 접속한다.

**실행 위치:** 💻 Remote PC

```bash
ssh csilab@10.8.141.194
```

정상적으로 접속되면 프롬프트가 다음과 같이 변경된다.

```text
csilab@turtle-jeong:~$
```

SSH 접속 전 네트워크 연결 상태를 먼저 확인하려면 다음 명령을 사용할 수 있다.

```bash
ping -c 4 10.8.141.194
```

정상 연결된 경우 다음과 같이 응답이 출력된다.

```text
64 bytes from 10.8.141.194
```

`Destination Host Unreachable` 또는 응답 시간 초과가 발생하면 두 장치가 같은 네트워크에 연결되어 있는지 확인한다.

#### 3. Remote PC의 ROS 환경 변수 확인

SSH 접속 터미널이 아닌 Remote PC의 새 터미널에서 ROS 관련 환경 변수를 확인한다.

**실행 위치:** 💻 Remote PC

```bash
env | grep ROS
```

다음 항목을 확인한다.

```text
ROS_DOMAIN_ID=30
ROS_LOCALHOST_ONLY=0
ROS_STATIC_PEERS=10.8.141.194
```

`ROS_STATIC_PEERS`에 이전 Raspberry Pi IP 주소가 설정되어 있다면 현재 IP 주소로 변경한다.

```bash
export ROS_STATIC_PEERS=10.8.141.194
```

ROS 2 통신이 로컬 장치로 제한되지 않도록 다음 값도 확인한다.

```bash
export ROS_LOCALHOST_ONLY=0
```

적용 여부를 확인한다.

```bash
echo $ROS_STATIC_PEERS
echo $ROS_DOMAIN_ID
echo $ROS_LOCALHOST_ONLY
```

출력 예시는 다음과 같다.

```text
10.8.141.194
30
0
```

#### 4. Remote PC 설정 영구 적용

터미널을 다시 열어도 설정이 유지되도록 `.bashrc` 파일을 수정한다.

**실행 위치:** 💻 Remote PC

```bash
nano ~/.bashrc
```

파일 하단의 기존 설정을 확인한다.

```bash
export ROS_DOMAIN_ID=30
export ROS_LOCALHOST_ONLY=0
export ROS_STATIC_PEERS=10.8.141.26
```

이전 Raspberry Pi IP 주소를 현재 주소로 변경한다.

```bash
export ROS_DOMAIN_ID=30
export ROS_LOCALHOST_ONLY=0
export ROS_STATIC_PEERS=10.8.141.194
```

저장 후 설정을 적용한다.

```bash
source ~/.bashrc
```

적용 결과를 확인한다.

```bash
env | grep ROS
```

#### 5. Remote PC의 현재 IP 주소 확인

Raspberry Pi에도 Remote PC의 현재 IP 주소가 등록되어 있어야 한다.

Remote PC에서 현재 IP 주소를 확인한다.

**실행 위치:** 💻 Remote PC

```bash
hostname -I
```

출력 예시는 다음과 같다.

```text
10.8.133.189
```

여러 주소가 출력된다면 Raspberry Pi와 실제로 연결된 네트워크 인터페이스의 주소를 사용한다.

자세한 네트워크 정보를 확인하려면 다음 명령을 사용한다.

```bash
ip addr
```

#### 6. Raspberry Pi의 ROS 환경 변수 수정

변경된 주소로 SSH 접속한 후 Raspberry Pi의 ROS 환경 변수를 확인한다.

**실행 위치:** 🍓 Raspberry Pi — SSH 접속 후

```bash
env | grep ROS
```

다음과 같이 Remote PC의 이전 IP 주소가 저장되어 있다면 수정해야 한다.

```text
ROS_STATIC_PEERS=10.8.133.100
```

우선 현재 터미널에 새로운 Remote PC IP 주소를 적용한다.

```bash
export ROS_STATIC_PEERS=10.8.133.189
export ROS_LOCALHOST_ONLY=0
export ROS_DOMAIN_ID=30
```

설정 영구 적용을 위해 `.bashrc`를 연다.

```bash
nano ~/.bashrc
```

파일 하단의 ROS 설정을 다음과 같이 수정한다.

```bash
export ROS_DOMAIN_ID=30
export ROS_LOCALHOST_ONLY=0
export ROS_STATIC_PEERS=10.8.133.189
```

저장 후 설정을 적용한다.

```bash
source ~/.bashrc
```

적용 결과를 확인한다.

```bash
echo $ROS_STATIC_PEERS
echo $ROS_DOMAIN_ID
echo $ROS_LOCALHOST_ONLY
```

정상 출력 예시는 다음과 같다.

```text
10.8.133.189
30
0
```

> `ROS_STATIC_PEERS`에는 자기 장치의 IP가 아니라 상대 장치의 IP를 입력한다.
>
> * Remote PC의 `ROS_STATIC_PEERS`: Raspberry Pi IP
> * Raspberry Pi의 `ROS_STATIC_PEERS`: Remote PC IP

#### 7. 양쪽 장치의 ROS 설정 비교

Remote PC와 Raspberry Pi에서 각각 다음 명령을 실행한다.

```bash
echo $ROS_DOMAIN_ID
echo $ROS_LOCALHOST_ONLY
```

두 장치 모두 다음과 같이 동일하게 출력되어야 한다.

```text
30
0
```

`ROS_DOMAIN_ID`가 서로 다르면 같은 ROS 2 네트워크에 참여할 수 없다.

`ROS_LOCALHOST_ONLY`가 `1`이면 외부 장치와 통신하지 않고 현재 장치 내부의 노드만 검색한다.

#### 8. ROS 2 Daemon 재시작

이전 IP 주소와 Discovery 정보가 ROS 2 Daemon에 남아 있을 수 있으므로 양쪽 장치에서 Daemon을 재시작한다.

**실행 위치:** 💻 Remote PC

```bash
ros2 daemon stop
ros2 daemon start
```

**실행 위치:** 🍓 Raspberry Pi — SSH 접속 후

```bash
ros2 daemon stop
ros2 daemon start
```

Daemon이 자동으로 다시 실행되므로 `start` 명령에서 별도 출력이 없더라도 문제가 아닐 수 있다.

필요하면 현재 터미널을 모두 닫고 새 터미널을 연 뒤 환경을 다시 적용한다.

**Remote PC**

```bash
source /opt/ros/jazzy/setup.bash
source ~/yolo_ws/install/setup.bash
```

**Raspberry Pi**

```bash
source /opt/ros/jazzy/setup.bash
source ~/turtlebot3_ws/install/setup.bash
```

#### 9. TurtleBot3 Bringup 재실행

Raspberry Pi에서 TurtleBot3 Bringup을 다시 실행한다.

**실행 위치:** 🍓 Raspberry Pi — SSH 접속 후

```bash
export TURTLEBOT3_MODEL=burger
ros2 launch turtlebot3_bringup robot.launch.py
```

Bringup 터미널은 종료하지 않고 계속 실행해 둔다.

---

#### 10. Remote PC에서 ROS 2 통신 확인

Remote PC의 새 터미널에서 Topic 목록을 확인한다.

**실행 위치:** 💻 Remote PC

```bash
ros2 topic list
```

다음 Topic이 표시되면 Raspberry Pi와 Remote PC의 ROS 2 통신이 정상적으로 복구된 것이다.

```text
/battery_state
/imu
/joint_states
/odom
/scan
/sensor_state
/tf
/tf_static
```

주요 Topic만 확인하려면 다음 명령을 사용한다.

```bash
ros2 topic list | grep -E "scan|odom|battery"
```

출력 예시는 다음과 같다.

```text
/battery_state
/odom
/scan
```

실제 데이터가 수신되는지도 확인한다.

```bash
ros2 topic echo /battery_state --once
```

```bash
ros2 topic echo /scan --once
```

```bash
ros2 topic echo /odom --once
```

Topic 이름은 보이지만 데이터가 출력되지 않는다면 Raspberry Pi의 Bringup 실행 상태와 네트워크 연결을 다시 확인한다.

---

#### 11. Camera 및 YOLO Topic 재확인

TurtleBot3 Topic이 정상적으로 검색되는 것을 확인한 후 Camera 수신 노드와 YOLO 노드를 다시 실행한다.

Camera Topic을 확인한다.

```bash
ros2 topic list | grep camera
```

정상 출력 예시는 다음과 같다.

```text
/camera/camera_info
/camera/image_raw
```

YOLO Topic을 확인한다.

```bash
ros2 topic list | grep yolo
```

정상 출력 예시는 다음과 같다.

```text
/yolo/detections
/yolo/dbg_image
```

YOLO 검출 데이터가 발행되는지 확인한다.

```bash
ros2 topic echo /yolo/detections --once
```

Camera와 YOLO Topic이 나타나지 않는 경우에는 ROS 2 장치 간 통신뿐만 아니라 다음 항목도 별도로 확인해야 한다.

* Raspberry Pi의 카메라 송출 명령이 실행 중인지
* Remote PC의 GStreamer 또는 `gscam` 수신 노드가 실행 중인지
* YOLO 노드가 실행 중인지
* `~/yolo_ws/install/setup.bash`가 적용되어 있는지
* UDP 송수신 포트가 서로 동일한지

---

### 정상 확인 기준

다음 조건을 모두 만족하면 문제가 해결된 것이다.

1. 변경된 Raspberry Pi IP로 SSH 접속이 된다.
2. Remote PC와 Raspberry Pi의 `ROS_DOMAIN_ID`가 모두 `30`이다.
3. 양쪽 장치의 `ROS_LOCALHOST_ONLY`가 모두 `0`이다.
4. 양쪽 장치의 `ROS_STATIC_PEERS`에 상대 장치의 현재 IP 주소가 설정되어 있다.
5. Remote PC에서 `/scan`, `/odom`, `/battery_state` Topic이 표시된다.
6. `/scan`, `/odom`, `/battery_state`에서 실제 메시지가 수신된다.
7. Camera와 YOLO 실행 후 `/camera/image_raw`, `/yolo/detections` Topic이 표시된다.

---

### 주의 사항

Raspberry Pi 또는 Remote PC의 IP 주소가 다시 변경되면 양쪽 장치의 `ROS_STATIC_PEERS` 설정을 모두 확인해야 한다.

```text
Remote PC ROS_STATIC_PEERS = Raspberry Pi의 현재 IP
Raspberry Pi ROS_STATIC_PEERS = Remote PC의 현재 IP
```

`.bashrc` 파일을 수정한 뒤에는 반드시 다음 명령을 실행하거나 새 터미널을 열어야 한다.

```bash
source ~/.bashrc
```

또한 SSH 접속에 사용하는 Raspberry Pi IP 주소와 Remote PC의 `ROS_STATIC_PEERS`에 입력하는 Raspberry Pi IP 주소는 동일해야 한다.

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

## 8. 목표 지점보다 멀리서 도착 판정이 되는 문제

### 증상

Navigation2를 이용하여 자율주행을 수행하면 TurtleBot3가 목표 지점까지 이동하지 않고 약 30~50 cm 떨어진 위치에서 정지하였다.

Behavior 코드에서 다음과 같이 `stop_distance`를 변경하여도 실제 정지 위치가 크게 달라지지 않았다.

```python
self.stop_distance = 0.20
```

Navigation2에서는 Goal을 성공으로 판단하지만 실제 TurtleBot3는 목표 지점과 거리가 남아 있었다.

### 원인

최종 정지 위치는 Behavior 코드의 `stop_distance`만으로 결정되지 않는다.

Navigation2의 Goal Checker에서 사용하는 `xy_goal_tolerance`도 함께 적용된다.

기본 설정은 다음과 같다.

```yaml
goal_checker:
  xy_goal_tolerance: 0.25
```

즉, 목표 지점으로부터 **25 cm 이내**에 진입하면 Goal에 도착한 것으로 판단하여 Navigation이 종료된다.

따라서 `stop_distance`만 변경하면 원하는 거리까지 이동하지 않을 수 있다.

### 해결 방법

먼저 현재 Goal Checker의 허용 오차를 확인한다.

**실행 위치:** 💻 Remote PC

```bash
ros2 param get /controller_server goal_checker.xy_goal_tolerance
```

다음과 같이 출력되면 기본 설정이 적용된 상태이다.

```text
Double value is: 0.25
```

허용 오차를 줄여 보다 정확한 위치까지 이동하도록 변경한다.

```bash
ros2 param set /controller_server goal_checker.xy_goal_tolerance 0.05
```

영구적으로 적용하려면 Navigation2 설정 파일(`burger.yaml`)을 수정한다.

```yaml
goal_checker:
  xy_goal_tolerance: 0.05
```

Behavior 코드에서도 원하는 정지 거리를 함께 설정한다.

```python
self.stop_distance = 0.20
```

설정을 변경한 후 Navigation2를 다시 실행한다.

`xy_goal_tolerance`와 `stop_distance`를 함께 조정하면 TurtleBot3가 목표 위치까지 더욱 정확하게 접근하는 것을 확인할 수 있다.

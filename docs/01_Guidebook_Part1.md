# 01_Guidebook_Part1

## Part 1. 개발 환경 구축 및 기본 동작 확인

본 문서에서는 TurtleBot3 Burger를 이용한 자율주행 프로젝트의 개발 환경을 구축하고 기본 동작을 확인하는 과정을 설명한다.

Remote PC와 Raspberry Pi에 필요한 소프트웨어를 설치하고 OpenCR Firmware를 업로드한 후 Bringup과 Teleoperation을 수행하여 ROS 2 통신이 정상적으로 이루어지는지 확인한다.

이 문서를 완료하면 SLAM 및 Navigation2 기반 자율주행을 수행하기 위한 환경이 준비된다.

## 목차

1. [Remote PC 환경 구축](#1-remote-pc-환경-구축)
2. [ROS 2 Jazzy 설치](#2-ros-2-jazzy-설치)
3. [Navigation2 설치](#3-navigation2-설치)
4. [TurtleBot3 패키지 설치](#4-turtlebot3-패키지-설치)
5. [Raspberry Pi Imager 설치](#5-raspberry-pi-imager-설치)
6. [Ubuntu Server 24.04 설치](#6-ubuntu-server-2404-설치)
7. [SSH 접속](#7-ssh-접속)
8. [Raspberry Pi 패키지 설치](#8-raspberry-pi-패키지-설치)
9. [OpenCR Firmware 업로드](#9-opencr-firmware-업로드)
10. [TurtleBot3 Bringup](#10-turtlebot3-bringup)
11. [TurtleBot3 Teleoperation](#11-turtlebot3-teleoperation)

---

## 1. Remote PC 환경 구축

Ubuntu 24.04 LTS를 설치하여 ROS 2 Jazzy와 Navigation2를 실행하기 위한 개발 환경을 구축한다.

### 1.1 Ubuntu 24.04 설치

ROS 2 Jazzy와 Navigation2를 실행하기 위한 Ubuntu 24.04 LTS를 설치한다.

#### 1. Ubuntu 24.04 LTS 다운로드

Ubuntu 공식 홈페이지에서 **Ubuntu 24.04 LTS Desktop** ISO 파일을 다운로드한다.

#### 2. 부팅 USB 생성

Windows 사용자는 **Rufus**, Linux 또는 macOS 사용자는 **balenaEtcher**를 이용하여 Ubuntu 설치 USB를 생성한다.

#### 3. BIOS 진입

노트북을 재부팅한 후 BIOS 또는 Boot Menu에 진입하여 USB로 부팅한다.

#### 4. Ubuntu 설치

Ubuntu 설치 마법사를 따라 설치를 진행한다.

설치 시 다음 항목을 권장한다.

- Install Ubuntu
- Normal Installation
- Download updates while installing Ubuntu
- Install third-party software (선택)

#### 5. 시스템 업데이트

Ubuntu 설치가 완료되면 최신 패키지로 업데이트한다.

**실행 위치:** 💻 Remote PC

```bash
sudo apt update
sudo apt upgrade -y
```

업데이트가 완료되면 시스템을 재부팅한다.

#### 확인

Ubuntu가 정상적으로 설치되었는지 확인한다.

**실행 위치:** 💻 Remote PC

```bash
lsb_release -a
```

다음과 같이 Ubuntu 24.04 LTS 정보가 출력되면 정상적으로 설치된 것이다.

```text
Distributor ID: Ubuntu
Description: Ubuntu 24.04 LTS
Release: 24.04
Codename: noble
```

## 2. ROS 2 Jazzy 설치

ROS 2 Jazzy는 TurtleBot3와 Navigation2를 실행하기 위한 ROS 2 LTS 버전이다. Ubuntu 24.04 LTS 환경에서 설치를 진행한다.

### 2.1 Locale 설정

ROS 2는 UTF-8 Locale 환경을 사용한다.

**실행 위치:** 💻 Remote PC

현재 Locale을 확인한다.

```bash
locale
```

Locale 패키지를 설치하고 UTF-8 Locale을 생성한다.

```bash
sudo apt update
sudo apt install locales

sudo locale-gen en_US en_US.UTF-8

sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8

export LANG=en_US.UTF-8
```

#### 확인

Locale이 정상적으로 설정되었는지 확인한다.

**실행 위치:** 💻 Remote PC

```bash
locale
```

다음과 같이 `LANG`와 `LC_ALL`이 `en_US.UTF-8`로 출력되면 정상적으로 설정된 것이다.

```text
LANG=en_US.UTF-8
LC_ALL=en_US.UTF-8
```

### 2.2 Universe Repository 활성화

ROS 2 설치에 필요한 Ubuntu Universe Repository를 활성화한다.

**실행 위치:** 💻 Remote PC

```bash
sudo apt install software-properties-common
sudo add-apt-repository universe
```

Repository 추가 여부를 묻는 메시지가 나타나면 **Enter**를 눌러 진행한다.

### 2.3 ROS 2 Repository 등록

ROS 2 패키지를 설치하기 위해 **ROS 2 공식 APT Repository**를 등록한다.

**실행 위치:** 💻 Remote PC

```bash
sudo apt update
sudo apt install curl -y
```

최신 ROS Repository 패키지를 다운로드한다.

```bash
export ROS_APT_SOURCE_VERSION=$(curl -s https://api.github.com/repos/ros-infrastructure/ros-apt-source/releases/latest | grep -F "tag_name" | awk -F'"' '{print $4}')

curl -L -o /tmp/ros2-apt-source.deb \
"https://github.com/ros-infrastructure/ros-apt-source/releases/download/${ROS_APT_SOURCE_VERSION}/ros2-apt-source_${ROS_APT_SOURCE_VERSION}.$(. /etc/os-release && echo ${UBUNTU_CODENAME:-${VERSION_CODENAME}})_all.deb"
```

Repository를 설치한다.

```bash
sudo dpkg -i /tmp/ros2-apt-source.deb
```

### 2.4 ROS 2 Jazzy 설치

새롭게 등록한 ROS Repository의 패키지 목록을 갱신한다.

**실행 위치:** 💻 Remote PC

```bash
sudo apt update
sudo apt upgrade
```

Remote PC는 RViz2, Gazebo 등을 사용하므로 Desktop 버전을 설치한다.

```bash
sudo apt install ros-jazzy-desktop
```

### 2.5 ROS 환경 설정

현재 터미널에서 ROS 2 환경을 활성화한다.

**실행 위치:** 💻 Remote PC

```bash
source /opt/ros/jazzy/setup.bash
```

자동으로 적용되도록 `.bashrc`에 등록한다.

```bash
echo "source /opt/ros/jazzy/setup.bash" >> ~/.bashrc
source ~/.bashrc
```

### 2.6 설치 확인

ROS 2 Jazzy가 정상적으로 설치되었는지 확인한다.

ROS에서 제공하는 Demo Node를 실행하여 Publisher와 Subscriber가 정상적으로 통신하는지 테스트한다.

#### Terminal 1 실행

**실행 위치:** 💻 Remote PC

```bash
ros2 run demo_nodes_cpp talker
```

#### Terminal 2 실행

**실행 위치:** 💻 Remote PC

```bash
ros2 run demo_nodes_py listener
```

#### 정상 실행 결과

**Terminal 1**

```text
[INFO] Publishing: 'Hello World: 1'
[INFO] Publishing: 'Hello World: 2'
...
```

**Terminal 2**

```text
[INFO] I heard: 'Hello World: 1'
[INFO] I heard: 'Hello World: 2'
...
```

위와 같이 `talker`에서 전송한 메시지를 `listener`가 정상적으로 수신하면 ROS 2가 올바르게 설치된 것이다.

## 3. Navigation2 설치

Navigation2(Nav2)는 ROS 2 기반 자율주행 프레임워크이다. Remote PC에 Navigation2를 설치하여 경로 계획(Path Planning), 위치 추정(Localization), 자율주행(Navigation) 기능을 사용할 수 있는 환경을 구축한다.

### 3.1 Navigation2 설치

Navigation2의 핵심 패키지와 Bringup 패키지를 설치한다.

**실행 위치:** 💻 Remote PC

```bash
sudo apt update
sudo apt install ros-jazzy-navigation2
sudo apt install ros-jazzy-nav2-bringup
```

`navigation2`는 Navigation2의 핵심 기능을 제공하며, `nav2_bringup`은 Launch 파일과 기본 설정을 포함한다.

### 3.2 TurtleBot3 Gazebo 패키지 설치

Navigation2 예제를 실행하기 위한 TurtleBot3 패키지를 설치한다.

**실행 위치:** 💻 Remote PC

```bash
sudo apt install ros-jazzy-nav2-minimal-tb*
```

해당 패키지에는 TurtleBot3 Description, Gazebo Simulation, Navigation2 예제가 포함되어 있다.

### 3.3 설치 확인

Navigation2 패키지가 정상적으로 설치되었는지 확인한다.

**실행 위치:** 💻 Remote PC

```bash
ros2 pkg list | grep nav2
```

다음과 같이 Navigation2 관련 패키지가 출력되면 정상적으로 설치된 것이다.

```text
nav2_amcl
nav2_behavior_tree
nav2_bringup
nav2_bt_navigator
nav2_controller
...
```

## 4. TurtleBot3 패키지 설치 (Remote PC)

Remote PC에 TurtleBot3 관련 ROS 2 패키지를 설치하고 Workspace를 생성하여 TurtleBot3 개발 및 시뮬레이션 환경을 구축한다.

### 4.1 Gazebo Harmonic 설치

ROS 2 Jazzy에서는 Gazebo Classic 대신 **Gazebo Harmonic**을 사용한다.

**실행 위치:** 💻 Remote PC

```bash
sudo apt update
sudo apt install curl lsb-release gnupg

sudo curl https://packages.osrfoundation.org/gazebo.gpg \
--output /usr/share/keyrings/pkgs-osrf-archive-keyring.gpg

echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/pkgs-osrf-archive-keyring.gpg] http://packages.osrfoundation.org/gazebo/ubuntu-stable $(lsb_release -cs) main" | sudo tee /etc/apt/sources.list.d/gazebo-stable.list > /dev/null

sudo apt update
sudo apt install gz-harmonic
```

Gazebo Harmonic은 TurtleBot3 시뮬레이션과 Navigation2 실행 환경을 제공한다.

### 4.2 Cartographer 설치

Cartographer는 LiDAR를 이용하여 지도를 생성하는 SLAM 패키지이다.

**실행 위치:** 💻 Remote PC

```bash
sudo apt install ros-jazzy-cartographer
sudo apt install ros-jazzy-cartographer-ros
```

### 4.3 TurtleBot3 Workspace 생성

TurtleBot3 패키지를 관리하기 위한 ROS 2 Workspace를 생성한다.

**실행 위치:** 💻 Remote PC

```bash
mkdir -p ~/turtlebot3_ws/src
cd ~/turtlebot3_ws/src
```

### 4.4 TurtleBot3 패키지 다운로드

ROBOTIS GitHub 저장소에서 TurtleBot3 관련 패키지를 다운로드한다.

**실행 위치:** 💻 Remote PC

```bash
git clone -b jazzy https://github.com/ROBOTIS-GIT/DynamixelSDK.git
git clone -b jazzy https://github.com/ROBOTIS-GIT/turtlebot3_msgs.git
git clone -b jazzy https://github.com/ROBOTIS-GIT/turtlebot3.git
```

### 4.5 Colcon 설치

Workspace를 빌드하기 위해 Colcon을 설치한다.

**실행 위치:** 💻 Remote PC

```bash
sudo apt install python3-colcon-common-extensions
```

### 4.6 TurtleBot3 Workspace Build

다운로드한 TurtleBot3 패키지를 빌드한다.

**실행 위치:** 💻 Remote PC

```bash
cd ~/turtlebot3_ws
colcon build --symlink-install
```

### 4.7 Workspace 환경 등록

새로운 터미널에서도 TurtleBot3 Workspace가 자동으로 적용되도록 `.bashrc`에 등록한다.

**실행 위치:** 💻 Remote PC

```bash
echo 'source ~/turtlebot3_ws/install/setup.bash' >> ~/.bashrc
source ~/.bashrc
```

### 4.8 ROS Domain ID 설정

Remote PC와 Raspberry Pi가 동일한 ROS 2 네트워크에서 통신할 수 있도록 Domain ID를 설정한다.

**실행 위치:** 💻 Remote PC

```bash
echo 'export ROS_DOMAIN_ID=30 # TURTLEBOT3' >> ~/.bashrc
source ~/.bashrc
```

### 4.9 설치 확인

Workspace가 정상적으로 빌드되었는지 확인한다.

**실행 위치:** 💻 Remote PC

```bash
ros2 pkg list | grep turtlebot3
```

다음과 같이 TurtleBot3 관련 패키지가 출력되면 정상적으로 설치된 것이다.

```text
turtlebot3
turtlebot3_bringup
turtlebot3_description
turtlebot3_navigation2
turtlebot3_node
turtlebot3_teleop
...
```

## 5. SBC Setup - Raspberry Pi Imager 설치

Raspberry Pi에서 사용할 **Ubuntu Server 24.04 LTS** 이미지를 microSD 카드에 설치하기 위해 Raspberry Pi Imager를 설치한다.

### 5.1 Raspberry Pi Imager 다운로드

공식 Raspberry Pi 홈페이지에서 **Raspberry Pi Imager**를 다운로드한다.

#### 다운로드 순서

1. Raspberry Pi 공식 홈페이지에 접속한다.
2. **Raspberry Pi Imager**를 선택한다.
3. 운영체제에 맞는 **Download for Linux (x86_64)** 를 선택하여 다운로드한다.

> **Figure 5-1. Raspberry Pi Imager 다운로드**

### 5.2 Raspberry Pi Imager 설치

다운로드한 `.deb` 파일이 있는 Downloads 폴더로 이동한다.

**실행 위치:** 💻 Remote PC

```bash
cd ~/Downloads
```

다운로드한 Raspberry Pi Imager를 설치한다.

```bash
sudo dpkg -i imager_*.deb
```

설치 중 의존성 오류가 발생하면 다음 명령어를 실행한다.

```bash
sudo apt install -f
```

Raspberry Pi Imager는 Raspberry Pi용 운영체제를 microSD 카드에 기록(Flash)하는 공식 프로그램이다. 이후 Ubuntu Server 24.04 LTS 이미지를 선택하여 microSD 카드에 기록한다.

## 6. Ubuntu Server 24.04 설치 (Raspberry Pi)

Raspberry Pi에서 사용할 **Ubuntu Server 24.04 LTS**를 microSD 카드에 설치하고, SSH 및 네트워크를 미리 설정하여 원격으로 접속할 수 있는 환경을 구성한다.

### 6.1 Raspberry Pi Imager 실행

터미널에서 Raspberry Pi Imager를 실행한다.

**실행 위치:** 💻 Remote PC

```bash
rpi-imager
```

### 6.2 Ubuntu Server 이미지 선택

Raspberry Pi Imager에서 아래 순서대로 운영체제를 선택한다.

1. **CHOOSE DEVICE** → **Raspberry Pi 4**
2. **CHOOSE OS**
3. **Other general-purpose OS**
4. **Ubuntu**
5. **Ubuntu Server 24.04.2 LTS (64-bit)** 선택
   - **Desktop이 아닌 Server 버전**을 선택한다.
6. **CHOOSE STORAGE** → microSD 카드 선택
7. **Next** 클릭

> **주의**
>
> **Ubuntu Desktop이 아닌 Ubuntu Server를 선택한다.**
>
> TurtleBot3는 SSH를 이용하여 원격으로 제어하므로 GUI가 포함된 Desktop 버전이 필요하지 않다.

### 6.3 Raspberry Pi 초기 설정

**Edit Settings**를 선택한 후 다음 항목을 설정한다.

#### General

- Hostname 설정
- Username 설정
- Password 설정

#### Services

- **Enable SSH** 활성화
- **Use password authentication** 선택

#### Network

- Wi-Fi SSID 입력
- Wi-Fi Password 입력
- Wireless LAN Country 설정 (KR)

설정을 완료한 후 **Save**를 선택한다.

### 6.4 Ubuntu Server 이미지 기록

설정을 확인한 후 **YES**를 눌러 microSD 카드에 Ubuntu Server 이미지를 기록한다.

이미지 기록(Write)과 검증(Verify)이 완료될 때까지 기다린다.

### 6.5 Raspberry Pi 부팅

기록이 완료되면 microSD 카드를 Raspberry Pi에 삽입한다.

다음 순서대로 전원을 연결한다.

1. microSD 카드 장착
2. LAN 또는 Wi-Fi 연결
3. 전원 연결

약 1~2분 정도 기다리면 Ubuntu Server가 부팅된다.

## 7. SSH 접속

Remote PC에서 SSH를 이용하여 Raspberry Pi에 원격 접속한다.

### 7.1 Remote PC에서 SSH 접속

터미널을 실행한 후 다음 명령어를 입력하여 Raspberry Pi에 접속한다.

**실행 위치:** 💻 Remote PC

```bash
ssh <username>@<Raspberry Pi IP Address>
```

예를 들어 사용자 계정이 `csilab`이고 Raspberry Pi의 IP 주소가 `10.8.141.26`인 경우 다음과 같이 입력한다.

```bash
ssh csilab@10.8.141.26
```

실제 환경에서는 자신의 Raspberry Pi 사용자 계정과 IP 주소를 입력하여 사용한다.

### 7.2 최초 접속

처음 접속하는 경우 아래와 같은 메시지가 출력된다.

```text
The authenticity of host '10.8.141.26' can't be established.
Are you sure you want to continue connecting (yes/no)?
```

`yes`를 입력한 후 **Enter**를 누른다.

```text
yes
```

이후 Raspberry Pi의 비밀번호를 입력한다.

Linux에서는 비밀번호를 입력해도 화면에 표시되지 않으며, 입력이 완료되면 **Enter**를 누른다.

### 7.3 접속 확인

로그인이 완료되면 터미널 프롬프트가 다음과 같이 표시된다.

```text
csilab@turtle-jeong:~$
```

위와 같이 표시되면 Raspberry Pi에 정상적으로 접속된 것이다.

이후부터 입력하는 모든 명령어는 **Raspberry Pi에서 실행되는 명령어**이다.

## 8. Raspberry Pi 패키지 설치

Ubuntu Server와 ROS 2 Jazzy 설치가 완료된 Raspberry Pi에 TurtleBot3 실행을 위한 패키지를 설치하고 Workspace를 구성한다. 또한 OpenCR과의 통신을 위한 USB 규칙과 ROS 환경을 설정한다.

이 장의 모든 명령어는 **SSH로 Raspberry Pi에 접속한 터미널**에서 실행한다.

### 8.1 TurtleBot3 의존성 패키지 설치

TurtleBot3를 실행하고 빌드하기 위해 필요한 ROS 2 패키지와 라이브러리를 설치한다.

**실행 위치:** 🍓 Raspberry Pi (SSH 접속 후)

```bash
sudo apt install python3-argcomplete python3-colcon-common-extensions libboost-system-dev build-essential
sudo apt install ros-jazzy-hls-lfcd-lds-driver
sudo apt install ros-jazzy-turtlebot3-msgs
sudo apt install ros-jazzy-dynamixel-sdk
sudo apt install ros-jazzy-xacro
sudo apt install libudev-dev
```

### 8.2 TurtleBot3 Workspace 생성

TurtleBot3 관련 패키지를 관리하기 위한 Workspace를 생성한다.

**실행 위치:** 🍓 Raspberry Pi (SSH 접속 후)

```bash
mkdir -p ~/turtlebot3_ws/src
cd ~/turtlebot3_ws/src
```

### 8.3 TurtleBot3 패키지 다운로드

ROBOTIS GitHub 저장소에서 TurtleBot3 관련 패키지를 다운로드한다.

**실행 위치:** 🍓 Raspberry Pi (SSH 접속 후)

```bash
git clone -b jazzy https://github.com/ROBOTIS-GIT/turtlebot3.git
git clone -b jazzy https://github.com/ROBOTIS-GIT/ld08_driver.git
git clone -b jazzy https://github.com/ROBOTIS-GIT/coin_d4_driver.git
```

### 8.4 사용하지 않는 패키지 제거

본 프로젝트에서는 Navigation2와 Cartographer를 Remote PC에서 실행하므로 Raspberry Pi에서는 해당 패키지를 제거하여 빌드 시간을 줄인다.

**실행 위치:** 🍓 Raspberry Pi (SSH 접속 후)

```bash
cd ~/turtlebot3_ws/src/turtlebot3

rm -r turtlebot3_cartographer turtlebot3_navigation2
```

### 8.5 TurtleBot3 Workspace 빌드

다운로드한 TurtleBot3 패키지를 ROS 2에서 사용할 수 있도록 빌드한다.

**실행 위치:** 🍓 Raspberry Pi (SSH 접속 후)

```bash
cd ~/turtlebot3_ws

colcon build --symlink-install --parallel-workers 1
```

Raspberry Pi는 메모리가 제한적이므로 `--parallel-workers 1` 옵션을 사용하여 하나의 패키지씩 빌드한다.

### 8.6 Workspace 환경 등록

새로운 터미널에서도 Workspace가 자동으로 적용되도록 `.bashrc`에 등록한다.

**실행 위치:** 🍓 Raspberry Pi (SSH 접속 후)

```bash
echo 'source ~/turtlebot3_ws/install/setup.bash' >> ~/.bashrc

source ~/.bashrc
```

### 8.7 OpenCR USB Port 설정

OpenCR을 Raspberry Pi가 정상적으로 인식할 수 있도록 udev Rule을 등록한다.

**실행 위치:** 🍓 Raspberry Pi (SSH 접속 후)

OpenCR udev Rule을 복사한다.

```bash
sudo cp $(ros2 pkg prefix turtlebot3_bringup)/share/turtlebot3_bringup/script/99-turtlebot3-cdc.rules /etc/udev/rules.d/
```

규칙을 다시 불러온다.

```bash
sudo udevadm control --reload-rules
```

새 규칙을 적용한다.

```bash
sudo udevadm trigger
```

### 8.8 ROS Domain ID 설정

Remote PC와 Raspberry Pi가 동일한 ROS 2 DDS Domain에서 통신할 수 있도록 Domain ID를 설정한다.

**실행 위치:** 🍓 Raspberry Pi (SSH 접속 후)

```bash
echo 'export ROS_DOMAIN_ID=30 # TURTLEBOT3' >> ~/.bashrc

source ~/.bashrc
```

설정이 완료되었는지 확인한다.

```bash
echo $ROS_DOMAIN_ID
```

정상적으로 설정되었다면 다음과 같이 출력된다.

```text
30
```

### 8.9 LiDAR(LDS) 모델 설정

TurtleBot3에 장착된 LiDAR 모델을 ROS 환경 변수로 등록한다. 사용하는 LiDAR 모델에 맞는 값을 설정해야 TurtleBot3가 올바른 드라이버를 사용하여 센서 데이터를 수신할 수 있다.

본 프로젝트에서는 **LDS-02** 모델을 사용하였다.

**실행 위치:** 🍓 Raspberry Pi (SSH 접속 후)

LDS 모델을 설정한다.

```bash
echo 'export LDS_MODEL=LDS-02' >> ~/.bashrc

source ~/.bashrc
```

설정이 완료되었는지 확인한다.

```bash
echo $LDS_MODEL
```

정상적으로 설정되었다면 다음과 같이 출력된다.

```text
LDS-02
```

## 9. OpenCR Firmware 업로드

OpenCR은 TurtleBot3의 Dynamixel 모터와 각종 센서를 제어하는 컨트롤러이다.

로봇을 정상적으로 구동하기 위해서는 사용 중인 TurtleBot3 모델에 맞는 OpenCR Firmware를 업로드해야 한다. 본 프로젝트에서는 **TurtleBot3 Burger** 모델을 사용하였다.

OpenCR Firmware 업로드는 **OpenCR을 USB로 Remote PC에 연결한 상태**에서 진행한다.

> **Figure 9-1. OpenCR과 Remote PC 연결**

### 9.1 OpenCR 환경 변수 설정

OpenCR이 연결된 포트와 TurtleBot3 모델을 설정한다.

**실행 위치:** 💻 Remote PC

```bash
export OPENCR_PORT=/dev/ttyACM0
export OPENCR_MODEL=burger
```

### 9.2 Firmware 다운로드

기존에 다운로드한 파일이 있다면 삭제한 후 최신 OpenCR Firmware를 다운로드한다.

**실행 위치:** 💻 Remote PC

```bash
cd ~

rm -rf opencr_update.tar.bz2

wget https://github.com/ROBOTIS-GIT/OpenCR-Binaries/raw/master/turtlebot3/ROS2/latest/opencr_update.tar.bz2
```

### 9.3 Firmware 압축 해제

다운로드한 Firmware를 압축 해제한다.

**실행 위치:** 💻 Remote PC

```bash
tar -xvf opencr_update.tar.bz2
```

압축을 해제하면 `~/opencr_update` 디렉터리가 생성된다.

### 9.4 Firmware 업로드

압축을 해제한 디렉터리로 이동하여 Firmware를 업로드한다.

**실행 위치:** 💻 Remote PC

```bash
cd ~/opencr_update

./update.sh $OPENCR_PORT ~/opencr_update/burger.opencr
```

### 9.5 업로드 완료 확인

다음과 같이 모든 항목이 **`[OK]`**로 출력되면 Firmware 업로드가 정상적으로 완료된 것이다.

**실행 위치:** 💻 Remote PC

```text
OpenCR Update Start..

[OK] Open port
[OK] flash_erase
[OK] flash_write
[OK] CRC Check
[OK] Download
[OK] jump_to_fw
```

업로드가 완료되면 OpenCR이 자동으로 재시작되며, TurtleBot3의 모터와 센서를 정상적으로 사용할 수 있다.

## 10. TurtleBot3 Bringup

TurtleBot3의 기본 노드를 실행하여 OpenCR, LiDAR, IMU, 모터 및 ROS 2 노드를 활성화한다.

Bringup이 정상적으로 완료되면 Remote PC와 TurtleBot3 간의 ROS 2 통신이 가능해진다.

### 10.1 Raspberry Pi 원격 접속 (SSH)

Remote PC에서 SSH를 이용하여 Raspberry Pi에 접속한다.

**실행 위치:** 💻 Remote PC

```bash
ssh <username>@<Raspberry Pi IP Address>
```

비밀번호를 입력하여 Raspberry Pi에 로그인한다.

실제 환경에서는 Raspberry Pi의 IP 주소와 사용자 계정에 맞게 변경하여 사용한다.

### 10.2 TurtleBot3 모델 설정

사용 중인 TurtleBot3 모델을 환경 변수로 설정한다.

본 프로젝트에서는 **TurtleBot3 Burger**를 사용하였다.

**실행 위치:** 🍓 Raspberry Pi (SSH 접속 후)

```bash
export TURTLEBOT3_MODEL=burger
```

환경 변수가 정상적으로 설정되었는지 확인한다.

```bash
echo $TURTLEBOT3_MODEL
```

정상적으로 설정되면 다음과 같이 출력된다.

```text
burger
```

### 10.3 TurtleBot3 Bringup 실행

TurtleBot3 Bringup을 실행한다.

**실행 위치:** 🍓 Raspberry Pi (SSH 접속 후)

```bash
ros2 launch turtlebot3_bringup robot.launch.py
```

Bringup이 실행되면 Robot State Publisher, OpenCR, LiDAR Driver, IMU, Odometry 등의 노드가 함께 실행된다.

### 10.4 Bringup 실행 확인

Bringup이 정상적으로 완료되면 아래와 같은 로그가 출력된다.

```text
Succeeded to open the port(/dev/ttyACM0)!
Succeeded to change the baudrate!

Start Calibration of Gyro
Calibration End

Add Motors
Add Wheels
Add Sensors

Succeeded to create battery state publisher
Succeeded to create imu publisher
Succeeded to create sensor state publisher
Succeeded to create joint state publisher

Run!

[diff_drive_controller]: Init Odometry
[diff_drive_controller]: Run!
```

위 로그가 출력되면 OpenCR과의 통신, LiDAR, IMU, 모터 초기화 및 ROS 2 Bringup이 정상적으로 완료된 것이다.

Bringup을 실행한 터미널은 이후 Teleoperation, SLAM 및 Navigation2를 수행할 때까지 종료하지 않고 계속 유지한다.

### 10.5 ROS 2 Topic 확인

Bringup이 정상적으로 실행되었는지 확인하기 위해 새로운 터미널을 열고 Raspberry Pi에 다시 SSH로 접속한다.

**실행 위치:** 💻 Remote PC

```bash
ssh <username>@<Raspberry Pi IP Address>
```

접속 후 Topic을 확인한다.

**실행 위치:** 🍓 Raspberry Pi (SSH 접속 후)

```bash
ros2 topic list
```

정상적으로 실행되면 다음과 같은 Topic이 생성된다.

```text
/battery_state
/cmd_vel
/imu
/joint_states
/magnetic_field
/odom
/parameter_events
/robot_description
/rosout
/scan
/sensor_state
/tf
/tf_static
```

다음 Topic이 정상적으로 생성되는 것을 확인하였다.

- `/scan` : LiDAR 데이터
- `/odom` : Odometry 데이터
- `/imu` : IMU 데이터
- `/cmd_vel` : 이동 명령
- `/tf` : 좌표계(Transform) 정보

### 10.6 ROS 2 Service 확인

Bringup이 정상적으로 실행되면 ROS 2 Service가 생성되었는지 확인한다.

**실행 위치:** 🍓 Raspberry Pi (SSH 접속 후)

```bash
ros2 service list
```

정상적으로 실행되면 다음과 같은 Service를 확인할 수 있다.

```text
/diff_drive_controller/...
/ld08_driver/...
/motor_power
/reset
/reset_odometry
/robot_state_publisher/...
/sound
/turtlebot3_node/...
```

`motor_power`, `reset`, `reset_odometry`, `sound`, `ld08_driver`, `turtlebot3_node` 등의 Service가 생성되면 OpenCR, LiDAR Driver 및 TurtleBot3 Node가 정상적으로 실행되고 있음을 확인할 수 있다.

## 11. TurtleBot3 Teleoperation

Remote PC에서 키보드 입력을 통해 TurtleBot3를 원격 제어한다.

이를 통해 Remote PC와 Raspberry Pi 간의 ROS 2 통신이 정상적으로 이루어지는지 확인하고, TurtleBot3의 기본 주행 기능을 점검한다.

Bringup(`ros2 launch turtlebot3_bringup robot.launch.py`)이 실행 중인 상태에서 진행한다.

### 11.1 Teleoperation 실행

새 터미널을 실행한 후 TurtleBot3 모델을 설정한다.

**실행 위치:** 💻 Remote PC

```bash
export TURTLEBOT3_MODEL=burger
```

Teleoperation 노드를 실행한다.

**실행 위치:** 💻 Remote PC

```bash
ros2 run turtlebot3_teleop teleop_keyboard
```

### 11.2 TurtleBot3 원격 제어

Teleoperation이 정상적으로 실행되면 다음과 같은 화면이 출력된다.

```text
Control Your TurtleBot3
---------------------------
Moving around:
        w
   a    s    d
        x

w/x : increase/decrease linear velocity
a/d : increase/decrease angular velocity

space key, s : force stop

CTRL-C to quit
```

키보드를 이용하여 TurtleBot3를 전진, 후진, 좌회전, 우회전시키며 정상적으로 주행하는지 확인한다.

### 11.3 LiDAR 및 Odometry Topic 확인

새 터미널을 실행하여 LiDAR Topic을 확인한다.

**실행 위치:** 💻 Remote PC

```bash
ros2 topic echo /scan
```

새 터미널을 하나 더 열어 Odometry Topic을 확인한다.

**실행 위치:** 💻 Remote PC

```bash
ros2 topic echo /odom
```

`/scan` Topic에서는 LiDAR 센서 데이터(`sensor_msgs/msg/LaserScan`)가 지속적으로 출력되는 것을 확인할 수 있다.

`/odom` Topic에서는 TurtleBot3의 위치(Position), 자세(Orientation), 속도(Velocity)를 포함한 오도메트리 데이터(`nav_msgs/msg/Odometry`)가 지속적으로 출력되는 것을 확인할 수 있다.

## 실행 결과 확인

다음 항목을 모두 만족하면 Part 1을 정상적으로 완료한 것이다.

- [ ] Remote PC에 Ubuntu 24.04 LTS를 설치하였다.
- [ ] Remote PC에 ROS 2 Jazzy를 설치하였다.
- [ ] Navigation2 및 TurtleBot3 패키지를 설치하였다.
- [ ] Raspberry Pi에 Ubuntu Server를 설치하였다.
- [ ] SSH를 이용하여 Raspberry Pi에 원격 접속하였다.
- [ ] Raspberry Pi에 ROS 2 Jazzy 및 TurtleBot3 패키지를 설치하였다.
- [ ] OpenCR Firmware를 정상적으로 업로드하였다.
- [ ] TurtleBot3 Bringup을 실행하여 센서와 모터가 정상적으로 동작하는 것을 확인하였다.
- [ ] Teleoperation을 이용하여 TurtleBot3를 원격으로 제어하였다.
- [ ] Remote PC와 Raspberry Pi 간의 ROS 2 통신이 정상적으로 이루어지는 것을 확인하였다.

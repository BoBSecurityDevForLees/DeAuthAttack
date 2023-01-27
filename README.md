# DeAuthAttack
이경문 멘토님의 심화교육 과정 3번째 과제 DeAuthAttack과제 입니다.

## 필요 라이브러리
1. Pcap: 네트워크 패킷을 잡기 위한 Lib
각종 네트워크 패킷을 잡을 수 있다.

## 프로젝트 빌드 방법
1. 필요 라이브러리를 설치한다.
    - libpcap
2. git clone https://github.com/arad4228/DeAuthAttack.git
3. cd DeAuthAttack
4. mkdir cmake-temp && mkdir build
5. cd cmake-temp
6. cmake ../src/ && cmake --build .
7. sudo ../build/DeAuthAttack < Network InterFaceName > < AP MacAddress > ( < Station MacAddress> < -auth > )

## 참고
- 가상 인터페이스 만들기
sudo modprobe mac80211_hwsim [radios=2]

## Authentication
wlan.addr == 3E:E0:7B:48:18:F7  
AuthPacket은 Deauth에 보임.

## Deauthentication
wlan.addr == 72:96:DB:5B:57:81

# bash ==> Drive PX2에서 재부팅 후 x11vnc가 해상도가 설정되어 있지 않아서
#          아래 스크립트를 실행해야 한다
# /lib/systemd/system/x11vnc.service


export DISPLAY=:0

# Headless 컴퓨터이므로 이런식으로 초기 해상도를 설정해줘야 한다
xrandr --fb 1920x1080

sudo systemctl stop x11vnc
sudo systemctl daemon-reload
sudo systemctl enable x11vnc
sudo systemctl start x11vnc

systemctl status x11vnc

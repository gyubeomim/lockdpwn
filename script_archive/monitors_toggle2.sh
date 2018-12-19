# bash ==> 3 monitors controller ON/OFF toggle

case $1 in
    off)
       # 중앙 모니터만 ON 나머지는 OFF
       xrandr --output eDP-1-1 --off --output VGA-1-1 --mode 1920x1080R --pos 0x0 --output HDMI-1-1 --off
        ;;
    *)
       # 3개 모니터를 전부 ON
       xrandr --output eDP-1-1 --mode 1920x1080 --pos 0x0 --primary --output VGA-1-1 --mode 1920x1080R --pos 1920x0 --output HDMI-1-1 --mode 1920x1080 --rotate right --pos 3840x0
        ;;
esac

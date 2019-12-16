# bash ==> 3 monitors controller ON/OFF toggle

case $1 in
    off)
       # 중앙 모니터만 ON 나머지는 OFF
       xrandr --output eDP1 --off --output VGA1 --mode 1920x1080R --pos 0x0 --output HDMI1 --off
        ;;
    three1)
       # 3개 모니터를 전부 Horizontal하게 ON
       xrandr --output eDP1 --mode 1920x1080 --pos 0x0 --primary --output VGA1 --mode 1920x1080R --pos 1920x0 --output HDMI1 --mode 1920x1080 --pos 3840x0
        ;;
    three2)
		# 3개 모니터를 전부 ON (제일 오른쪽 모니터는 Vertical)
       xrandr --output eDP1 --mode 1920x1080 --pos 0x0 --primary --output VGA1 --mode 1920x1080R --pos 1920x0 --output HDMI1 --rotate right --mode 1920x1080 --pos 3840x0
        ;;
    two)
		# 2개 모니터를 ON (Notebook 모니터는 끔)
       xrandr --output VGA1 --primary --mode 1920x1080R --pos 1920x0 --output HDMI1 --mode 1920x1080 --pos 3840x0
        ;;
    atlas1)
		# 다중 모니터 ON
       xrandr --output DVI-D-1 --mode 2560x1440 --pos 0x0 --primary --output DVI-I-1 --mode 2560x1440 --pos 2560x0
       # xrandr --output DVI-I-1 --mode 1920x1080 --pos 1920x594 --output DVI-D-0 --mode 1920x1080 --pos 0x1080 --primary --output HDMI-0 --mode 1920x1080 --pos 0x0
        ;;
    off_atlas1)
		# 1개 모니터만 켠다 
       xrandr --output DVI-D-1 --primary --mode 2560x1440 --pos 0x0  --output DVI-I-1 --off 
        ;;
esac

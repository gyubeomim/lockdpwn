if [ ! -z "$1" ] 
then
	read -p "[+] enter the boosting speed you want : " speed
	speed=1/${speed}
	ffmpeg -i $1 -acodec mp2 -filter:v "setpts=${speed}*PTS" ${HOME}/Downloads/output-$(date +%Y%m%d_%H%M%S).mp4
	echo "[+] Boosted file is saved in ~/Downloads/"
else
	echo "[-] No Input argument is contained! use ./mp4_speed.sh {filename}"
fi

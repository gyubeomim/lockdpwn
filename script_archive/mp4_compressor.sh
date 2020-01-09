read -p "[+] enter width : " width
ffmpeg -i $1 -acodec mp2 -vf scale=$width:-1 ${HOME}/Downloads/output-$(date +%Y%m%d_%H%M).mp4
echo "[+] Compressed file is saved in ~/Downloads/"

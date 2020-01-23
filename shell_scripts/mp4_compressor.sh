if [ ! -z "$1" ] 
then
	read -p "[+] enter width : " width
	ffmpeg -i $1 -acodec mp2 -vf scale=$width:-1 ${HOME}/Downloads/output-$(date +%Y%m%d_%H%M%S).mp4
	echo "[+] Compressed file is saved in ~/Downloads/"
else
	echo "[-] No Input argument is contained! use ./mp4_compressor.sh {filename}"
fi

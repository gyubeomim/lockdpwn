if [ ! -z "$1" ] 
then
	ffmpeg -i $1 -ss $2 -to $3 -c copy ${HOME}/Downloads/output-$(date +%Y%m%d_%H%M).mp4
	echo "[+] Trimmed file is saved in ~/Downloads/"
else
	echo "[-] No Input argument is contained! use ./mp4_compressor.sh {filename} {from} {to}, format: 00:00:00"
fi

git add . -A
git commit -m "$(date +%Y%m%d) : $(lsb_release -sd)" 
git push origin master

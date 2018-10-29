git add . -A
if [ -z "$1" ]
then
	git commit -m "$(date +%Y%m%d) : $(lsb_release -sd)" 
else
	git commit -m "$1" 
fi
git push origin master

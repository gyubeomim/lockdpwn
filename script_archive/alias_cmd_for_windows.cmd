@echo off
REM doskey 명령어를 사용해 cmd에서 bash 같은 alias 명령어를 사용하는 코드

doskey uptime=powershell uptime2.ps1

doskey ls=dir
doskey ll=dir /w
doskey l=dir /w

doskey gr=cd e:\gitrepo 
doskey g1=cd e:\gitrepo\lockdpwn 
doskey g2=cd e:\gitrepo\ims_ros
doskey g3=cd e:\gitrepo\ims_carto

doskey up=cd c:\Users\edward 
doskey down=cd c:\Users\edward\Downloads 

doskey ipy=cd e:\gitrepo\lockdpwn\python_archive\ipython
doskey ml=cd e:\gitrepo\lockdpwn\python_archive\machineLearning

doskey tf=activate tf
doskey vi=cd c:\Program Files (x86)\Vim 

doskey notebook=ipython notebook
doskey qt=ipython qtconsole

socat TCP-LISTEN:4000,reuseaddr,fork EXEC:../cc_archive/bof3 2>/dev/null &
python aslr.py 

# bash ==> Ctrl <--> Caps Lock 

case $1 in
    original)
        dconf write /org/gnome/desktop/input-sources/xkb-options "['']"
        dconf read /org/gnome/desktop/input-sources/xkb-options
        ;;
    *)
        dconf write /org/gnome/desktop/input-sources/xkb-options "['ctrl:swapcaps']"
        dconf read /org/gnome/desktop/input-sources/xkb-options
        ;;
esac

#!/bin/bash
set -e

## 버전을 변경하고 싶으시면 아래 코드를 변경하면 됩니다.
readonly version="26.1"

# install dependencies
sudo apt-get install -y stow build-essential libx11-dev xaw3dg-dev \
     libjpeg-dev libpng12-dev libgif-dev libtiff4-dev libncurses5-dev \
     libxft-dev librsvg2-dev libmagickcore-dev libmagick++-dev \
     libxml2-dev libgpm-dev libghc-gconf-dev libotf-dev libm17n-dev \
     libgnutls-dev

# download source package
if [[ ! -d emacs-"$version" ]]; then
   wget http://ftp.gnu.org/gnu/emacs/emacs-"$version".tar.xz
   tar xvf emacs-"$version".tar.xz
fi

# buil and install (do not use stow)
# if [ ! -d /usr/local/stow ]; then
#      sudo mkdir /usr/local/stow
# fi

cd emacs-"$version"
./configure \
    --with-xft \
    --with-x-toolkit=lucid
make
sudo make install prefix=/usr/local/stow/emacs-"$version"

# cd /usr/local/stow
# sudo stow emacs-"$version"

#!/bin/bash
set -e

# set the version to want to install.
readonly version="26.3"

# install dependencies.
sudo apt-get install -y stow build-essential libx11-dev xaw3dg-dev \
     libjpeg-dev libpng-dev libgif-dev libtiff5-dev libncurses5-dev \
     libxft-dev librsvg2-dev libmagickcore-dev libmagick++-dev \
     libxml2-dev libgpm-dev libotf-dev libm17n-dev libgnutls28-dev

# download source package.
if [[ ! -d emacs-"$version" ]]; then
   wget http://ftp.gnu.org/gnu/emacs/emacs-"$version".tar.xz
   tar xvf emacs-"$version".tar.xz
fi

cd emacs-"$version"
./configure --with-x-toolkit=lucid

make -j

# install emacs into machine. To use "Add to Favorites" feature in Launcher bar.
sudo make install 


# Deprecated(2020.07)==========================
# buil and install (do not use stow)
# if [ ! -d /usr/local/stow ]; then
#      sudo mkdir /usr/local/stow
# fi

#sudo make install prefix=/usr/local/stow/emacs-"$version"
# cd /usr/local/stow
# sudo stow emacs-"$version"

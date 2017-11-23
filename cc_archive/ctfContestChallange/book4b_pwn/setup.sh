#!/bin/sh
sudo apt-get install build-essential gcc-multilib git gdb nasm libc6:i386
git clone https://github.com/zachriggle/peda.git ~/peda
echo "source ~/peda/peda.py" >> ~/.gdbinit
export PATH=$HOME/bin:$PATH
mkdir $HOME/bin
wget https://github.com/downloads/0vercl0k/rp/rp-lin-x64 -O $HOME/bin/rp
chmod +x $HOME/bin/rp
wget https://github.com/slimm609/checksec.sh/archive/1.6.tar.gz
tar zxvf 1.6.tar.gz
cp checksec.sh-1.6/checksec $HOME/bin/checksec.sh

#!/bin/bash
sudo apt update
sudo apt install -y git cmake make g++ libpcap-dev
git clone https://github.com/seladb/PcapPlusPlus.git
cd PcapPlusPlus
./configure-linux.sh
make all
sudo make install

#!/bin/bash
sudo apt update
sudo apt install -y git cmake make g++ libpcap-dev python3 python3-pip

if [ ! -d "PcapPlusPlus" ]; then
  git clone https://github.com/seladb/PcapPlusPlus.git
fi
cd PcapPlusPlus
./configure-linux.sh
make all
sudo make install

pip3 install scapy

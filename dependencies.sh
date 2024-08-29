#!/bin/bash
sudo apt update
sudo apt install -y git cmake make g++ libpcap-dev libssl-dev python3 python3-pip python3-scapy

if [ ! -d "PcapPlusPlus" ]; then
  git clone https://github.com/seladb/PcapPlusPlus.git
fi

cd PcapPlusPlus
mkdir -p build
cd build
cmake ..
make
sudo make install

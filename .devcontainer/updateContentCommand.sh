#!/bin/bash
set -e

export DEBIAN_FRONTEND=noninteractive
sudo apt-get update -y

sudo apt-get install -y clang-format

pip install cmake-format

pushd $(mktemp -d)
# v1.9.8 latest as of 2023-09-26
wget https://github.com/doxygen/doxygen/releases/download/Release_1_9_8/doxygen-1.9.8.linux.bin.tar.gz
tar -xzf doxygen-1.9.8.linux.bin.tar.gz
sudo mv doxygen-1.9.8/bin/doxygen /usr/local/bin/
rm -rf "$PWD"
popd

sudo rm -rf /var/lib/apt/lists/*

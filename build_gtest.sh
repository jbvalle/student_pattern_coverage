#!/bin/bash

apt-get update -y
apt-get install -y build-essential cmake libpthread-stubs0-dev libgtk-3-dev
cd googletest/ && mkdir -p build && cd $_ && rm -rf * && cmake .. && make



#!/bin/bash
mkdir -p out
mkdir -p out/img
./bin/fluid
ffmpeg -framerate 60 -i "out/img/%05d.png" -y "out/video.mp4"
rm -f out/img/*.png

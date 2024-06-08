#!/bin/bash
mkdir -p out
mkdir -p out/img
./bin/maelstrom
ffmpeg -i "out/img/%05d.png" -y "out/video.mp4" -framerate 60
rm -f out/img/*.png

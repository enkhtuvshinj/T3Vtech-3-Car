#!/bin/bash
# script for automated creation of DEB packages

cd ..
rm -rf 80s-racing
mkdir 80s-racing
mkdir 80s-racing/bin
mkdir 80s-racing/DEBIAN
mkdir 80s-racing/usr
mkdir 80s-racing/usr/games
mkdir 80s-racing/usr/games/80s-racing
cp -r assets/ 80s-racing/usr/games/80s-racing
cp -r settings/ 80s-racing/usr/games/80s-racing
cp -r shaders/ 80s-racing/usr/games/80s-racing
cp car-racing 80s-racing/usr/games/80s-racing/
mv 80s-racing/usr/games/80s-racing/car-racing 80s-racing/usr/games/80s-racing/80s-racing
cp ../scripts/debian-package-data/80s-racing 80s-racing/bin/
cp ../scripts/debian-package-data/control 80s-racing/DEBIAN/
dpkg-deb --build 80s-racing
#!/bin/bash
#script for creation for creating a Zip file for the Linux build

echo "building ZIP Linux build"

cd ../..
rm -rf 80s-racing
mkdir 80s-racing

echo "copying game files"
cp -r assets 80s-racing/
cp -r settings 80s-racing/
cp -r shaders 80s-racing/
cp 80s-racing 80s-racing/80s-racing

echo "zipping directory"
zip -r 80s-racing-linux.zip 80s-racing
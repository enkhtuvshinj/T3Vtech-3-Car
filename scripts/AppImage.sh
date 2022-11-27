#!/bin/bash
#script for creation of an AppDir for an AppImage

ARCH=x86_64
export ARCH

cd ..
rm -rf AppDir
mkdir AppDir
mkdir AppDir/usr
mkdir AppDir/usr/lib
mkdir AppDir/usr/bin

#create .desktop
echo "[Desktop Entry]" >> AppDir/80s-racing.desktop
echo "Name=5PM" >> AppDir/80s-racing.desktop
echo "Exec=5PM" >> AppDir/80s-racing.desktop
echo "Icon=5PM" >> AppDir/80s-racing.desktop
echo "Type=Application" >> AppDir/80s-racing.desktop
echo "Categories=Utility;" >> AppDir/80s-racing.desktop
chmod +x AppDir/80s-racing.desktop

#copy game data to the AppDir
cd AppDir
#ln -s usr/bin/80s-racing AppRun
cd ..

cp scripts/AppDir-data/AppRun AppDir/AppRun
cp ../meta-data/icon_red.png AppDir/80s-racing.png

cp infinity-maze AppDir/usr/bin/80s-racing
cp -r assets/ AppDir/usr/bin
cp -r settings/ AppDir/usr/bin
cp -r shaders/ AppDir/usr/bin

#adding dependencies
cp "$(find /usr/lib -name libc.so)" AppDir/usr/lib
#find /usr/lib -name *libc.so* -exec cp {} AppDir/usr/lib \;
find /usr/lib -name *libm.so* -exec cp {} AppDir/usr/lib \;
find /usr/lib -name *SDL2.so* -exec cp {} AppDir/usr/lib \;
find /usr/lib -name *SDL2_ttf.so* -exec cp {} AppDir/usr/lib \;
find /usr/lib -name *GLEW.so* -exec cp {} AppDir/usr/lib \;
find /usr/lib -name *openal.so* -exec cp {} AppDir/usr/lib \;
find /usr/lib -name *libstdc++.so* -exec cp {} AppDir/usr/lib \;

find /usr/lib -name *libsndio.so* -exec cp {} AppDir/usr/lib \;

#build AppImage
chmod +x scripts/appimagetool-x86_64.AppImage
./scripts/appimagetool-x86_64.AppImage AppDir/
chmod +x 80s-racing-x86_64.AppImage

unset ARCH
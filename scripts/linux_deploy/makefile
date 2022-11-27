CC=g++

SRC=../../../
SRC_C:=$(shell find $(SRC)src $(SRC)vendor/T3Vtech-3/src/engine -name *.c)
SRC_CPP:=$(shell find $(SRC)src $(SRC)vendor/T3Vtech-3/src/engine -name *.cpp)
SRC_CSV=$(SRC)vendor/csv-io/src/csv_data.cpp

AL_CFLAGS=/usr/include/AL/
TTF_CFLAGS=/usr/include/SDL2/
SDL_CFLAGS:= $(shell sdl2-config --cflags --libs)
CFLAGS=-I$(SRC)vendor/T3Vtech-3/src/engine/ -I$(SRC)vendor/T3Vtech-3/vendor/stb -I$(SRC)vendor/T3Vtech-3/vendor/Tlib/ -I$(SRC)vendor/csv-io/include/ -I$(AL_CFLAGS) -I$(TTF_CFLAGS) $(SDL_CFLAGS) -lpthread -lGL -lGLEW -lm -lopenal -lSDL2_ttf -o build/5PM -fpermissive
#CFLAGS_all=-Isrc/kosmonaut/ -Isrc/game/game/ -lSDL2 -lGL -lGLEW -lm -lnng -lpthread -o SBC -g -pg -fno-common
#CFLAGS=-Isrc/kosmonaut/ -Isrc/game/game/ libkosmonaut.a -lSDL2 -lGL -lGLEW -lm -lnng -lpthread -o SBC -g -pg -fno-common
#CFLAGS_lib= -Isrc/kosmonaut/ -lSDL2 -lGL -lGLEW -lm -lnng -lpthread -c -g -pg -fno-common
#CFLAGS_win=-mwindows -Isrc/kosmonaut/ -Isrc/game/game/ -Iwindows/include/  -Lwindows/lib/ windows/nng.dll -lglew32 -lglew32mx -lSDL2 -lSDL2main -lopengl32 -lmingw32 -lm -o SBC.exe -g -pg

main: $(SRC)
	rm -rf build
	mkdir build
	$(CC) $(SRC_C) $(SRC_CPP) $(SRC_CSV) $(CFLAGS)
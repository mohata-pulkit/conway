CC = gcc
CFLAGS = -g -Wall -Wextra -std=c99 -pedantic -O3
LDFLAGS = -lm -lSDL2 -lSDL2_image

# Path: src
SRC = $(wildcard src/*.c)
HDR = $(wildcard src/*.h)

# Path: bin
TARGET = bin/cgol

all: compile run ffmpeg

data: compile run

compile:
	mkdir -p bin
	mkdir -p data/imgs
	mkdir -p data/vids
	rm -f $(TARGET)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(SRC) $(HDR)

run:
	rm -f ./data/imgs/*.png
	rm -f ./data/vids/*.mp4
	./$(TARGET)

ffmpeg:
	ffmpeg -framerate 12 -i ./data/imgs/%d.png ./data/vids/12.mp4
	ffmpeg -framerate 30 -i ./data/imgs/%d.png ./data/vids/30.mp4
	ffmpeg -framerate 60 -i ./data/imgs/%d.png ./data/vids/60.mp4
	ffmpeg -framerate 120 -i ./data/imgs/%d.png ./data/vids/120.mp4

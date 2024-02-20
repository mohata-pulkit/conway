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
	rm -f $(TARGET)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(SRC) $(HDR)

run:
	rm -f ./data/imgs/*.png
	rm -f ./data/vids/*.mp4
	./$(TARGET)

ffmpeg:
	ffmpeg -framerate 12 -i ./data/imgs/%d.png -vf scale=800:800 -sws_flags neighbor ./data/vids/12.mp4
	ffmpeg -framerate 30 -i ./data/imgs/%d.png -vf scale=800:800 -sws_flags neighbor ./data/vids/30.mp4
	ffmpeg -framerate 60 -i ./data/imgs/%d.png -vf scale=800:800 -sws_flags neighbor ./data/vids/60.mp4
	ffmpeg -framerate 120 -i ./data/imgs/%d.png -vf scale=800:800 -sws_flags neighbor ./data/vids/120.mp4
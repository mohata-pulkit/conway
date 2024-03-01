CC = gcc
CFLAGS = -g -Wall -Wextra -std=c99 -pedantic -O3
LDFLAGS = -lm -lSDL2 -lSDL2_image

# Path: src
SRC = $(wildcard src/*.c)
HDR = $(wildcard src/*.h)

# Path: bin
TARGET = bin/cgol
IMAGE = ./in/campbell.png

glider: clean compile run-glider ffmpeg

campbell: clean compile run-image ffmpeg

random: clean compile run-random ffmpeg

compile:
	mkdir -p bin
	mkdir -p data/imgs
	mkdir -p data/vids
	rm -f $(TARGET)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET)  $(SRC) $(HDR)

clean:
	rm -f ./data/imgs/*.png
	rm -f ./data/vids/*.mp4
	rm -f ./data/*.txt

run-glider:
	./$(TARGET)

run-image:
	./$(TARGET) $(IMAGE)

run-random:
	./$(TARGET) 100 100	

ffmpeg:
	ffmpeg -framerate 12 -i ./data/imgs/%d.png -vf "scale='max(1200,iw)':'max(1200,ih)'" -sws_flags neighbor ./data/vids/12.mp4
	ffmpeg -framerate 30 -i ./data/imgs/%d.png -vf "scale='max(1200,iw)':'max(1200,ih)'" -sws_flags neighbor ./data/vids/30.mp4
	ffmpeg -framerate 60 -i ./data/imgs/%d.png -vf "scale='max(1200,iw)':'max(1200,ih)'" -sws_flags neighbor ./data/vids/60.mp4
	ffmpeg -framerate 120 -i ./data/imgs/%d.png -vf "scale='max(1200,iw)':'max(1200,ih)'" -sws_flags neighbor ./data/vids/120.mp4
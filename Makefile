CC = gcc
CFLAGS = -g -Wall -Wextra
LIBS = -lm

TARGET = bin/spiro

all: $(TARGET) plot push

bin/spiro: src/spiro.c
	$(CC) $(CFLAGS) -o bin/spiro src/spiro.c $(LIBS)

.PHONY: clean push plot

clean:
	$(RM) $(TARGET)

plot:
	./bin/spiro 9 5 5 1 1 1 1 | ./jgraph/jgraph -P | ps2pdf - | convert -units PixelsPerInch - -transparent white -density 900 images/graph1.png
	./bin/spiro 9 5 2.5 1 1 1 1 | ./jgraph/jgraph -P | ps2pdf - | convert -units PixelsPerInch - -transparent white -density 900 images/graph2.png
	./bin/spiro 29 7 6 1 1 1 1 | ./jgraph/jgraph -P | ps2pdf - | convert -units PixelsPerInch - -transparent white -density 900 images/graph3.png
	./bin/spiro 29 21 18 1 1 1 1 | ./jgraph/jgraph -P | ps2pdf - | convert -units PixelsPerInch - -transparent white -density 900 images/graph4.png
	./bin/spiro 17 23 23 1 1 1 1 | ./jgraph/jgraph -P | ps2pdf - | convert -units PixelsPerInch - -transparent white -density 900 images/graph5.png
	
push:
	git add src/spiro.c
	git add README.md
	git add Makefile
	git add jgraph
	git add images
	git commit -m "changing spiro or README"
	git push -u origin main

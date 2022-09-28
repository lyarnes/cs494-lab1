CC = gcc
CFLAGS = -g -Wall -Wextra
LIBS = -lm

TARGET = bin/spiro

all: $(TARGET)

bin/spiro: src/spiro.c
	mkdir bin
	$(CC) $(CFLAGS) -o bin/spiro src/spiro.c $(LIBS)

.PHONY: clean push plot

clean:
	$(RM) $(TARGET)

plot:
	./bin/spiro 6 5 5 0 1 0 1 | ./jgraph/jgraph -P | ps2pdf - | convert -units PixelsPerInch - -transparent white -density 900 graph1.png
	./bin/spiro 6 5 2.5 0 1 0 1 | ./jgraph/jgraph -P | ps2pdf - | convert -units PixelsPerInch - -transparent white -density 900 graph2.png
	./bin/spiro 15 6 4.3 0 1 0 1 | ./jgraph/jgraph -P | ps2pdf - | convert -units PixelsPerInch - -transparent white -density 900 graph3.png
	./bin/spiro 15 14 12 0 1 0 1 | ./jgraph/jgraph -P | ps2pdf - | convert -units PixelsPerInch - -transparent white -density 900 graph4.png
	./bin/spiro 13 19 16 0 1 0 1 | ./jgraph/jgraph -P | ps2pdf - | convert -units PixelsPerInch - -transparent white -density 900 graph5.png
	
push:
	git add src/spiro.c
	git add README.md
	git add Makefile
	git add jgraph
	git add images
	git commit -m "changing spiro or README"
	git push -u origin main

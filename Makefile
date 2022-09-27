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
	./bin/spiro 11 1 1 | ./jgraph/jgraph -P | ps2pdf - > gen/graph1.pdf
	./bin/spiro 11 2 1 | ./jgraph/jgraph -P | ps2pdf - > gen/graph2.pdf
	./bin/spiro 11 3 1 | ./jgraph/jgraph -P | ps2pdf - > gen/graph3.pdf
	./bin/spiro 11 4 1 | ./jgraph/jgraph -P | ps2pdf - > gen/graph4.pdf
	./bin/spiro 11 5 1 | ./jgraph/jgraph -P | ps2pdf - > gen/graph5.pdf
	./bin/spiro 11 6 1 | ./jgraph/jgraph -P | ps2pdf - > gen/graph6.pdf
	./bin/spiro 11 7 1 | ./jgraph/jgraph -P | ps2pdf - > gen/graph7.pdf
	./bin/spiro 11 8 1 | ./jgraph/jgraph -P | ps2pdf - > gen/graph8.pdf
	./bin/spiro 11 9 1 | ./jgraph/jgraph -P | ps2pdf - > gen/graph9.pdf
	./bin/spiro 11 10 1 | ./jgraph/jgraph -P | ps2pdf - > gen/graph11df
	
push:
	git add -A
	git commit -m "message"
	git push -u origin main

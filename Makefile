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
	./bin/spiro $(PARAM1) $(PARAM2) $(PARAM3) > gen/g.txt
	./jgraph/jgraph -P gen/g.txt | ps2pdf - > gen/graph.pdf

push:
	git add -A
	git commit -m "message"
	git push -u origin main

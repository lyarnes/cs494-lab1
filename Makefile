CC = gcc
CFLAGS = -g -Wall -Wextra
LIBS = -lm

TARGET = spiro

all: $(TARGET) plot push

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(LIBS)

.PHONY: clean push plot

clean:
	$(RM) $(TARGET)

plot:
	./spiro 3 5 > g.txt
	./jgraph/jgraph -P g.txt | ps2pdf - > graph.pdf

push:
	git add -A
	git commit -m "message"
	git push -u origin main

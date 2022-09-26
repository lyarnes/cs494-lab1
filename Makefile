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
	./bin/spiro $(PARAM1) $(PARAM2) 0.1 | ./jgraph/jgraph -P | ps2pdf - > gen/graph1.pdf
	./bin/spiro $(PARAM1) $(PARAM2) 0.2 | ./jgraph/jgraph -P | ps2pdf - > gen/graph2.pdf
	./bin/spiro $(PARAM1) $(PARAM2) 0.3 | ./jgraph/jgraph -P | ps2pdf - > gen/graph3.pdf
	./bin/spiro $(PARAM1) $(PARAM2) 0.4 | ./jgraph/jgraph -P | ps2pdf - > gen/graph4.pdf
	./bin/spiro $(PARAM1) $(PARAM2) 0.5 | ./jgraph/jgraph -P | ps2pdf - > gen/graph5.pdf
	./bin/spiro $(PARAM1) $(PARAM2) 0.6 | ./jgraph/jgraph -P | ps2pdf - > gen/graph6.pdf
	./bin/spiro $(PARAM1) $(PARAM2) 0.7 | ./jgraph/jgraph -P | ps2pdf - > gen/graph7.pdf
	./bin/spiro $(PARAM1) $(PARAM2) 0.8 | ./jgraph/jgraph -P | ps2pdf - > gen/graph8.pdf
	./bin/spiro $(PARAM1) $(PARAM2) 0.9 | ./jgraph/jgraph -P | ps2pdf - > gen/graph9.pdf
	./bin/spiro $(PARAM1) $(PARAM2) 1 | ./jgraph/jgraph -P | ps2pdf - > gen/graph10.pdf
	
push:
	git add -A
	git commit -m "message"
	git push -u origin main

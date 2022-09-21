CC = gcc
CFLAGS = -g -Wall -Wextra

TARGET = spiro

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

.PHONY: clean push

clean:
	$(RM) $(TARGET)

push:
	git add -A
	git commit -m "message"
	git push -u origin main

CC = gcc
CFLAGS = -g -Wall -Wextra

TARGET = spiro

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET)

CC = g++
CFLAGS = -Wall -Wextra -Werror -Wconversion -pedantic -std=c++11
TARGET = chesspp

all: main.cpp
	$(CC) $(CFLAGS) -o $(TARGET) main.cpp	

clean:
	rm -f $(TARGET)
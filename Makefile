CC = gcc
TARGET = main
SRC = $(wildcard *.c)
CFLAGS = -Wall -Wextra -flto -O2

$(TARGET) : $(SRC)
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS)
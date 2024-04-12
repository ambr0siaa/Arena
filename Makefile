CC = gcc
TARGET = main
SRC = $(wildcard *.c)
CFLAGS = -Wall -Wextra -g3 -ggdb

$(TARGET) : $(SRC)
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS)
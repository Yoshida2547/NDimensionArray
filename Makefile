BUILD = build
SRC = src
INCLUDE = include
OBJS = objs

TARGET = $(BUILD)/a.out

CFILES = $(wildcard $(SRC)/*c)
OFILES = $(patsubst $(SRC)/%.c, $(OBJS)/%.o, $(CFILES))

CC = gcc
CFLAGS = -Wall -g

all: $(TARGET)
	@$^

$(TARGET): $(OFILES)
	$(CC) -o $@ $^

$(OBJS)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c -o $@ $^

clear:
	rm $(TARGET) $(OFILES)



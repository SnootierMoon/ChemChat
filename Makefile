SRC_DIR=src
INCLUDE_DIR=include
TARGET=out

SRCS=$(shell find $(SRC_DIR) -name "*.c")
INCLUDES=$(shell find $(INCLUDE_DIR) -name "*.h")

FLAGS=-Wall -I.

$(TARGET): $(SRCS) $(INCLUDES)
	gcc $(SRCS) -o$(TARGET) $(FLAGS)



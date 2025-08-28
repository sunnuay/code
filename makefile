SRC_DIR := others
OBJ_DIR := build
TARGET := main.exe

SRC := $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%.o,$(SRC))

all: $(TARGET)
	./$^

$(TARGET): $(OBJ)
	g++ $^ -o $@

$(OBJ_DIR)/%.c.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	gcc $< -o $@ -c -g -std=c23

$(OBJ_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	g++ $< -o $@ -c -g -std=c++23

$(OBJ_DIR):
	mkdir $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
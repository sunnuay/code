SOURCE = sorting_algorithm
TARGET = main.exe

DIRECTORY = $(SOURCE)_o
OBJECTS := $(patsubst $(SOURCE)/%.c,$(DIRECTORY)/%.o,$(wildcard $(SOURCE)/*.c))
OBJECTS += $(patsubst $(SOURCE)/%.cpp,$(DIRECTORY)/%.o,$(wildcard $(SOURCE)/*.cpp))

all: $(DIRECTORY) $(TARGET)

$(DIRECTORY):
	mkdir $@

$(TARGET): $(OBJECTS)
	g++ $^ -o $@

$(DIRECTORY)/%.o: $(SOURCE)/%.c
	g++ $< -o $@ -c -g

$(DIRECTORY)/%.o: $(SOURCE)/%.cpp
	g++ $< -o $@ -c -g -I .

clean:
	rm -rf $(DIRECTORY) $(TARGET)

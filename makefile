SOURCE = usb
FOLDER = .build
TARGET = 666.exe
OBJECTS := $(patsubst $(SOURCE)/%.c,$(FOLDER)/%.o,$(wildcard $(SOURCE)/*.c))
OBJECTS += $(patsubst $(SOURCE)/%.cpp,$(FOLDER)/%.o,$(wildcard $(SOURCE)/*.cpp))

all: $(FOLDER) $(TARGET)
	./$(TARGET)

$(FOLDER):
	mkdir $@

$(TARGET): $(OBJECTS)
	g++ $^ -o $@ -mwindows

$(FOLDER)/%.o: $(SOURCE)/%.c
	g++ $< -o $@ -c -g

$(FOLDER)/%.o: $(SOURCE)/%.cpp
	g++ $< -o $@ -c -g -mwindows

clean:
	rm -rf $(FOLDER) $(TARGET)

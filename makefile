# SOURCE
FOLDER = .build
TARGET = .main
OBJECTS := $(patsubst $(SOURCE)/%.c,$(FOLDER)/%.o,$(wildcard $(SOURCE)/*.c))
OBJECTS += $(patsubst $(SOURCE)/%.cpp,$(FOLDER)/%.o,$(wildcard $(SOURCE)/*.cpp))

all: $(FOLDER) $(TARGET)
	./$(TARGET)

$(FOLDER):
	mkdir $@

$(TARGET): $(OBJECTS)
	g++ $^ -o $@

$(FOLDER)/%.o: $(SOURCE)/%.c
	gcc $< -o $@ -c -g

$(FOLDER)/%.o: $(SOURCE)/%.cpp
	g++ $< -o $@ -c -g

clean:
	rm -rf $(FOLDER) $(TARGET)

SOURCE = sorting_algorithm
FOLDER = .build
TARGET = .main
OBJECTS := $(patsubst $(SOURCE)/%.c,$(FOLDER)/%.o,$(wildcard $(SOURCE)/*.c))
OBJECTS += $(patsubst $(SOURCE)/%.cpp,$(FOLDER)/%.o,$(wildcard $(SOURCE)/*.cpp))

a: $(FOLDER) $(TARGET)

$(FOLDER):
	mkdir $@

$(TARGET): $(OBJECTS)
	g++ $^ -o $@

$(FOLDER)/%.o: $(SOURCE)/%.c
	g++ $< -o $@ -c -g

$(FOLDER)/%.o: $(SOURCE)/%.cpp
	g++ $< -o $@ -c -g

r:
	./$(TARGET)

c:
	rm -rf $(FOLDER) $(TARGET)

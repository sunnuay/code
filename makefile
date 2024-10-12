FOLDER = .build
TARGET = .main
OBJECTS := $(patsubst $(src)/%.c,$(FOLDER)/%.o,$(wildcard $(src)/*.c))
OBJECTS += $(patsubst $(src)/%.cpp,$(FOLDER)/%.o,$(wildcard $(src)/*.cpp))

all: $(FOLDER) $(TARGET)
	./$(TARGET)

$(FOLDER):
	mkdir $@

$(TARGET): $(OBJECTS)
	g++ $^ -o $@

$(FOLDER)/%.o: $(src)/%.c
	gcc $< -o $@ -c -g

$(FOLDER)/%.o: $(src)/%.cpp
	g++ $< -o $@ -c -g

clean:
	rm -rf $(FOLDER) $(TARGET)

SOURCE = 
TARGET = .main
FOLDER = .build
DIRECTORY = $(FOLDER)/$(SOURCE)
OBJECTS := $(patsubst $(SOURCE)/%.c,$(DIRECTORY)/%.o,$(wildcard $(SOURCE)/*.c))
OBJECTS += $(patsubst $(SOURCE)/%.cpp,$(DIRECTORY)/%.o,$(wildcard $(SOURCE)/*.cpp))

all: $(FOLDER) $(DIRECTORY) $(TARGET)

$(FOLDER):
	mkdir $@

$(DIRECTORY):
	cd $(FOLDER) && mkdir $(SOURCE)

$(TARGET): $(OBJECTS)
	g++ $^ -o $@

$(DIRECTORY)/%.o: $(SOURCE)/%.c
	g++ $< -o $@ -c -g

$(DIRECTORY)/%.o: $(SOURCE)/%.cpp
	g++ $< -o $@ -c -g

clean:
	rm -rf $(FOLDER) $(TARGET)

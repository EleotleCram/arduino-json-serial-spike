
PROJECT_NAME=$(shell basename $${PWD})

CXXFLAGS=-std=c++0x -I3rdparty
CC=g++

TARGET=target

C_SOURCES=$(shell find * -type f -name "*.c" | grep -v test | sed 's/^/$(TARGET)\//')
C_OBJECTS=$(C_SOURCES:.c=.o)

CXX_SOURCES=$(shell find * -type f -name "*.cpp" | grep -v test | sed 's/^/$(TARGET)\//')
CXX_OBJECTS=$(CXX_SOURCES:.cpp=.o)

OBJECTS=$(C_OBJECTS) $(CXX_OBJECTS)

BIN=$(TARGET)/$(PROJECT_NAME).bin

.PHONY: all clean %.dir

all: $(BIN)

clean:
	rm -rf $(TARGET)

$(BIN): $(OBJECTS)
	g++ $(LDFLAGS) -o $@ $(OBJECTS)

$(TARGET)/%.o: %.cpp $(TARGET)/%.dir
	$(CC) $(CXXFLAGS) -o $@ -c $<

$(TARGET)/%.o: %.c $(TARGET)/%.dir
	$(CC) $(CXXFLAGS) -o $@ -c $<

$(TARGET)/%.dir:
	mkdir -p `dirname $@`

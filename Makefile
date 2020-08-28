CXX      	:= -c++
CXXFLAGS 	:= -pedantic-errors -Wall -Wextra
BUILD_DIR   := ./build
OBJ_DIR  	:= $(BUILD_DIR)/objects
TARGET   	:= GameEngine
INCLUDES 	:= -Isrc/include/
LIBRARIES 	:= -L./src/lib/
SRC      	:=           		 \
	$(wildcard src/*.cpp) 		 \
	

OBJECTS  := $(SRC:%.cpp=$(OBJ_DIR)/%.o)
LINKER_LIBS := -lglfw3 -lGLEW -ldl -lm -lX11 -lpthread -lGL

all: build $(BUILD_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LIBRARIES) $(LINKER_LIBS) -c $< -o $@

$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/$(TARGET) $^ $(LIBRARIES) $(LINKER_LIBS)

PHONY: all build clean debug release

build:
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(BUILD_DIR)/*
LINKER_LIBS := -lglfw3 -lGLEW -ldl -lm -lX11 -lpthread -lGL
INCLUDES = -Isrc/include/
LIBRARIES = -L./src/lib

build/GameEngine: build/main.o
	g++ -o build/GameEngine $(LIBRARIES) build/main.o $(LINKER_LIBS)
build/main.o: src/main.cpp
	g++ -std=c++11 -c src/main.cpp $(INCLUDES) -o ./build/main.o

clean:
	rm -rf build/*.o
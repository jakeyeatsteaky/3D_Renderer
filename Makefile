build:
	g++ -std=c++17 -Wall -Werror -Iinclude -I/usr/local/include src/*.cpp -g main.cpp -o 3DRenderer -lGL -lGLEW -lSDL2

build_and_run:
	g++ -std=c++17 -Wall -Werror -Iinclude -I/usr/local/include src/*.cpp -g main.cpp -o 3DRenderer -lGL -lGLEW -lSDL2
	./3DRenderer

clean:
	rm 3DRenderer
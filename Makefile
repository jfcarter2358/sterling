.PHONY: build debug

build:
	rm main || true
	g++ src/*.cpp -o main -lSDL2 -Iinclude
	chmod +x main

debug:
	rm main || true
	g++ -g src/*.cpp -o main -lSDL2 -Iinclude
	chmod +x main
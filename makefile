EXEC = bin/shogi
CC = g++
FLAGS = -Wall -g

all: $(EXEC)

$(EXEC): main.o Partie.o ConfigJeu.o Piece.o Vec2.o
	$(CC) $(FLAGS) obj/main.o obj/Partie.o obj/ConfigJeu.o obj/Piece.o obj/Vec2.o -o $(EXEC)

main.o: src/main.cpp src/Partie.h src/ConfigJeu.h src/Piece.h src/Vec2.h
	$(CC) $(FLAGS) -c src/main.cpp -o obj/main.o

Partie.o: src/Partie.cpp src/Partie.h src/ConfigJeu.h src/Piece.h src/Vec2.h
	$(CC) $(FLAGS) -c src/Partie.cpp -o obj/Partie.o

ConfigJeu.o: src/ConfigJeu.cpp src/ConfigJeu.h src/Piece.h src/Vec2.h
	$(CC) $(FLAGS) -c src/ConfigJeu.cpp -o obj/ConfigJeu.o

Piece.o: src/Piece.cpp src/Piece.h src/Vec2.h
	$(CC) $(FLAGS) -c src/Piece.cpp -o obj/Piece.o

Vec2.o: src/Vec2.cpp src/Vec2.h
	$(CC) $(FLAGS) -c src/Vec2.cpp -o obj/Vec2.o

clean:
	rm -f obj/*
	rm -f bin/*
less_clean:
	rm -f obj/*.o
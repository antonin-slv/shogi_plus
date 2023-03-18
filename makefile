EXEC = bin/shogi
CC = g++
FLAGS = -Wall -g

all: $(EXEC)

$(EXEC): main.o ConfigJeu.o Partie.o Piece.o Vec2.o
	$(CC) $(FLAGS) obj/main.o obj/Plateau.o obj/Piece.o -o $(EXEC)

main.o: src/main.cpp src/ConfigJeu.h src/Partie.h src/Piece.h src/Vec2.h
	$(CC) $(FLAGS) -c src/main.cpp -o obj/main.o

ConfigJeu.o: src/ConfigJeu.cpp src/ConfigJeu.h src/Partie.h src/Piece.h src/Vec2.h
	$(CC) $(FLAGS) -c src/ConfigJeu.cpp -o obj/ConfigJeu.o

Partie.o: src/Partie.cpp src/Partie.h Piece.o Vec2.o
	$(CC) $(FLAGS) -c src/Partie.cpp -o obj/Partie.o

Piece.o: src/Piece.cpp src/Piece.h Vec2.h
	$(CC) $(FLAGS) -c src/Piece.cpp -o obj/Piece.o

Vec2.o: src/Vec2.cpp src/Vec2.h
	$(CC) $(FLAGS) -c src/Vec2.cpp -o obj/Vec2.o

clean:
	rm -f obj/*
	rm -f bin/*
less_clean:
	rm -f obj/*.o
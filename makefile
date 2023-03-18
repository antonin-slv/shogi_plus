EXEC = bin/shogi
CC = g++
FLAGS = -Wall -g

all: $(EXEC)

$(EXEC): main.o Plateau.o Piece.o
	$(CC) $(FLAGS) obj/main.o obj/Plateau.o obj/Piece.o -o $(EXEC)

main.o: src/main.cpp src/Plateau.h src/Piece.h src/Partie.h src/ConfigJeu.h
	$(CC) $(FLAGS) -c src/main.cpp -o obj/main.o

ConfigJeu.o: src/ConfigJeu.cpp src/ConfigJeu.h
	$(CC) $(FLAGS) -c src/ConfigJeu.cpp -o obj/ConfigJeu.o

Partie.o: src/Jeu.cpp src/Jeu.h src/Partie.h
	$(CC) $(FLAGS) -c src/Partie.cpp -o obj/Partie.o

Piece.o: src/Piece.cpp src/Piece.h
	$(CC) $(FLAGS) -c src/Piece.cpp -o obj/Piece.o

clean:
	rm -f obj/*
	rm -f bin/*
less_clean:
	rm -f obj/*.o
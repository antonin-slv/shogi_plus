EXEC = bin/shogi
CC = g++
FLAGS = -Wall -g

ISFML = -I/usr/include/SFML
LIBSFML= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all: $(EXEC)

$(EXEC): main.o Partie.o ConfigJeu.o Piece.o Vec2.o Affichage.o Bot.o
	$(CC) $(FLAGS) obj/main.o obj/Partie.o obj/ConfigJeu.o obj/Piece.o obj/Affichage.o obj/Vec2.o obj/Bot.o $(LIBSFML) -o $(EXEC)

main.o: src/main.cpp src/Partie.h src/ConfigJeu.h src/Piece.h src/Vec2.h src/Affichage.h src/Bot.h
	$(CC) $(FLAGS) -c src/main.cpp $(ISFML) -o obj/main.o

Affichage.o: src/Affichage.cpp src/Affichage.h src/Partie.h src/ConfigJeu.h src/Piece.h src/Vec2.h
	$(CC) $(FLAGS) -c src/Affichage.cpp $(ISFML) -o obj/Affichage.o

Bot.o: src/Bot.cpp src/Bot.h src/Partie.h src/ConfigJeu.h src/Piece.h src/Vec2.h
	$(CC) $(FLAGS) -c src/Bot.cpp -o obj/Bot.o

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
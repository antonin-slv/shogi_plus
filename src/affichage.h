#ifndef _AFFICHAGE_
#define _AFFICHAGE_

#include "ConfigJeu.h"
#include "Piece.h"
#include "Vec2.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
using namespace sf;


class Afficheur
{   public :

    vector<Sprite> pieces_b;
    vector<Sprite> pieces_n;

    Texture pion_b;
    Texture pion_n;

    Texture pion;
    Texture tour;
    Texture lance;
    Texture cavalier;
    Texture fou;
    Texture gen_or;
    Texture gen_arg;
    Texture roi;


    Sprite ban;
    Texture damier;

    //fonctions d'initialisation
    Afficheur();
    void init_sprites();
    
    //on récupère la configuration du jeu
    void lier(const ConfigurationJeu& cj);

    //affiche le jeu sur la fenètre (sans actualiser)
    void dessiner(RenderWindow& fenetre);

};

#endif
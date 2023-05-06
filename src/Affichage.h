#ifndef _Affichage_
#define _Affichage_

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
    Texture amelioration_text;

    Sprite amelioration_sprite;
    Sprite ban;
    Texture damier;
    sf::Font font;
    sf::Text text_temp;

    //fonctions d'initialisation
    Afficheur();
    void init_sprites();

    //affiche le jeu sur la fenètre (sans actualiser, ni clear)
    void dessiner(RenderWindow& fenetre,const ConfigurationJeu& cj);

    void selection_coup_SFML(RenderWindow & win,ConfigurationJeu const & GAME, Coup & coup);

};

void jeutxt_aff(ConfigurationJeu const & GAME);

void selection_coup_TXT(ConfigurationJeu const & GAME, Coup & coup);
#endif
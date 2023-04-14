#ifndef _AFFICHAGE_
#define _AFFICHAGE_

#include "ConfigurationJeu.h"
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


class Affichage
{   vector<sprite> pieces_b;
    vector<sprite> pieces_n;

    sprite damier;
}
   
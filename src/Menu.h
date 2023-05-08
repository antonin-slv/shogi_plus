#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <string>

using namespace std;
using namespace sf;


struct Parametre {
    bool blanc_bot;//true si le joueur blanc est un bot
    bool noir_bot;
    int prof_blanc;//profondeur de l'algo
    int prof_noir;
    int algo_blanc;//code de l'algo
    int algo_noir;
    bool quit;//true si on quitte le jeu
    int mode=0; //0:shogi 1:variante  
};

class Menu {
    private :
    Font font;
    public :
    Parametre m_param;
    Menu();
    void afficher();
    void saisir();
    Parametre getParam() const;

    Parametre & boucleMenuPrincipal(sf::RenderWindow & win);
    bool boucleMenuJouer(sf::RenderWindow & win);
    bool boucleMenuSimulation(sf::RenderWindow & win);
};


#endif
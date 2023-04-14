#include "Affichage.h"

Afficheur::Afficheur()
{   pion_b.loadFromFile("data/img/pion_blanc.png");
    pion_n.loadFromFile("data/img/pion_noir.png");
    damier.loadFromFile("data/img/plateau.png");
}

void Afficheur::init_sprites()
{   ban.setTexture(damier);
    for(int i=0; i<20; i++)
    {   pieces_b.push_back(Sprite(pion_b));
        pieces_n.push_back(Sprite(pion_n));
    }
}

void Afficheur::lier(const ConfigurationJeu& cj)
{   for(int i=0; i<20; i++)
    {   pieces_b[i].setPosition(cj.getPiece((TypePiece) i, BLANC).getPos().x*95+10, cj.getPiece((TypePiece) i, BLANC).getPos().y*100+5);
        pieces_n[i].setPosition(cj.getPiece((TypePiece) i, NOIR).getPos().x*95+10, cj.getPiece((TypePiece) i, NOIR).getPos().y*100+5);
    }
}

void Afficheur::dessiner(RenderWindow& fenetre)
{   fenetre.clear();
    fenetre.draw(ban);
    for(int i=0; i<20; i++)
    {   fenetre.draw(pieces_b[i]);
        fenetre.draw(pieces_n[i]);
    }
}
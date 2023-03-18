#ifndef _PARTIE_H_
#define _PARTIE_H_

#include "Plateau.h"
#include "Piece.h"
#include "Joueur.h"

class Partie
{   private : 
        Plateau * plat;
        Joueur j1;
        Joueur j2;

    public :
        
        Partie ();
        Partie (Plateau * p, Joueur j1, Joueur j2);
        Partie (const Partie & p);
        Partie (const Partie * p);

        Plateau * getPlateau();
        Joueur getJoueur1();
        Joueur getJoueur2();

};

#endif
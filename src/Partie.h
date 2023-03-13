#ifndef _PARTIE_H_
#define _PARTIE_H_

#include "Plateau.h"
#include "Piece.h"

class Partie
{   private : 
        Plateau * plat;
        Joueur j1;
        Joueur j2;

    public :
        
        Partie();
        Partie(Plateau * p, Joueur j1, Joueur j2);
        Partie(const Parties & p);
        Partie(const Parties * p);

        Plateau * getPlateau();
        Joueur getJoueur1();
        Joueur getJoueur2();
*/

};

#endif
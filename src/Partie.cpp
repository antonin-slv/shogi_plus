#include "Partie.h"

Partie::Partie()
{
    plat = new Plateau();
    j1 = new Joueur();
    j2 = new Joueur();
}

Partie::Partie(Plateau * p, Joueur j1, Joueur j2)
{
    plat = p;
    j1 = j1;
    j2 = j2;
}

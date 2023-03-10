#include "Joueur.h"

Joueur::Joueur()
{
    humain = false;
}

Joueur::Joueur(bool ordi)
{
    humain = !ordi;
}

#ifndef _BOT_
#define _BOT_

#include "ConfigJeu.h"
#include "Piece.h"
#include "Vec2.h"

//algorithme min_max
struct MinMax
{

	Coup coup;
	float score;
	MinMax(Coup c, float s):coup(c),score(s){}
};


MinMax min_max_final(ConfigurationJeu cj, int profondeur); //fonction récursive mal optimisée qui calcule le meilleur coup possible

float evaluateur_branche(ConfigurationJeu cj, int n); //fonction récursive qui calcule le score maximal des branches d'une configuration

Coup min_max(ConfigurationJeu cj, int n); //appel la fonction evaluateur_branche (récusrive) et renvoie le coup associé au meilleur score



#endif
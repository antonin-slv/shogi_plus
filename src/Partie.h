#ifndef _PARTIE_H_
#define _PARTIE_H_

#include "Plateau.h"
#include "Piece.h"
#include "Joueur.h"

class Partie
{
public:
	Partie();
	
	int nbEtape() const;
	const ConfigurationJeu& getIemeEtape(int ) const;
	void ajouterEtape(const ConfigrationJeu& cj);

	Coup coupJouerAEtapeN(int n);				// renvoie le coup jouer Ã  l'Ã©tape N de la partie. n doit Ãªtre plus petit strictement que le nombre d'Ã©tape.
	void crop(int debut, int fin);				// coupe tous les coups avant debut et aprÃ¨s fin
	
	void ecriture(ofstream& f);
	void lecture(ofstream& f);
	// OU
	ostream& operator<<(ostream& , const Partie& p) 
	istream& operator<<(istream& , const Partie& p) 

	
	static void testRegression() const;
private:
	std::vector<ConfigrationJeu> m_etapes;			// les N Ã©tapes d'une partie. Entre 2 Ã©tapes il s'est passÃ© un "Coup", mais on stocke la configuration en entier. Stocker les coups auraient Ã©tÃ© possible aussi.
};


// un coup=dÃ©place la piÃ¨ce de la case 'pos" vers 'pos+depl'
struct Coup
{
	Vec2 pos;
	Vec2 deplacement;
	Coup(const Vec2& p=Vec2(0,0), const Vec2& d=Vec2(0,0));
};

#endif
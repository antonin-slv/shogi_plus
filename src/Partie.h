#ifndef _PARTIE_H_
#define _PARTIE_H_

#include "Vec2.h"
#include "Piece.h"
#include "ConfigJeu.h"

#include <vector>
#include <fstream>
#include <iostream>

using namespace std;
class Partie
{	private:
		std::vector<ConfigurationJeu> m_etapes;	

	public:
		Partie();
		
		int nbEtape() const;
		const ConfigurationJeu& getIemeEtape(int ) const;
		void ajouterEtape(const ConfigurationJeu& cj);

		Coup coupJouerAEtapeN(int n);				// renvoie le coup jouer Ã  l'Ã©tape N de la partie. n doit Ãªtre plus petit strictement que le nombre d'Ã©tape.
		void crop(int debut, int fin);				// coupe tous les coups avant debut et aprÃ¨s fin
		
		void ecriture(ofstream& f);
		void lecture(ofstream& f);
		// OU
		/*
		ostream& operator<<(ostream& , const Partie& p) ;
		istream& operator<<(istream& , const Partie& p) ;
		*/

		
		//static void testRegression() const;
		// les N Ã©tapes d'une partie. Entre 2 Ã©tapes il s'est passÃ© un "Coup", mais on stocke la configuration en entier. Stocker les coups auraient Ã©tÃ© possible aussi.
};


#endif
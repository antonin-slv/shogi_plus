#ifndef _PARTIE_H_
#define _PARTIE_H_

#include "ConfigJeu.h"
#include "Piece.h"
#include "Affichage.h"
#include "Bot.h"
#include "Menu.h"
#include <iostream>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <iostream>

using namespace std;

class Partie : public ConfigurationJeu
{	private:
		std::vector<ConfigurationJeu> m_etapes;	
		int etapeActuelle;
	public:
		ConfigurationJeu GAME;
		Partie();

		void boucle_Jeu(Afficheur& TABS, RenderWindow& win,Parametre & param);


		
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
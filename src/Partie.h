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

struct Stats
{
	int nbParties;
	int nbVictoires_Blanc;
	int nbDefaites_Blancs;
	int nbNuls;//après 250 coups (sauf si changés)
	int nbForfait_Blanc;
	int nbForfait_Noir;

	//les temps de jeu/de calcul
	float temps_Blanc;
	float temps_Noir;
};

class Partie
{	private:
		//std::vector<ConfigurationJeu> m_etapes;	
		//int etapeActuelle;
		
	public:
		Stats statistiques;
		ConfigurationJeu GAME;
		Partie();

		Stats & boucle_Jeu(Afficheur& TABS, RenderWindow& win,Parametre & param);


		/*
		int nbEtape() const;
		const ConfigurationJeu& getIemeEtape(int ) const;
		void ajouterEtape(const ConfigurationJeu& cj);

		Coup coupJouerAEtapeN(int n);				// renvoie le coup jouer à l'étape N de la partie. n doit Ãªtre plus petit strictement que le nombre d'étape.
		void crop(int debut, int fin);				// coupe tous les coups avant debut et après fin
		
		void ecriture(ofstream& f);
		void lecture(ofstream& f);
		// OU
		
		ostream& operator<<(ostream& , const Partie& p) ;
		istream& operator<<(istream& , const Partie& p) ;
		*/

		
		//static void testRegression() const;
		// les N étapes d'une partie. Entre 2 étapes il s'est passé un "Coup", mais on stocke la configuration en entier. Stocker les coups auraient été possible aussi.
};


#endif
#include "Partie.h"
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
using namespace sf;

// --> Vec, TypePiece, Couleur, IdPiece,  Piece, ConfigrationJeu

int main()
{	
	Partie jeu;
	Afficheur TABS;
	RenderWindow win(VideoMode(1920,1080),"Shogi",Style::Fullscreen);
	Menu menu;
	menu.boucleMenuPrincipal(win);
	while(!menu.m_param.quit) {
		jeu.boucle_Jeu(TABS, win, menu.m_param);
		menu.boucleMenuPrincipal(win);
	}
	win.close();

	/*
	if (!continu) cout<<"Partie terminée par l'utilisateur"<<endl;
	else if (jeu.partieTerminee())
	{ 	if(jeu.vainqueur()==BLANC) cout<<"Partie terminée par victoire du joueur Blanc"<<endl;
		else if(jeu.vainqueur()==NOIR) cout<<"Partie terminée par victoire du joueur Noir"<<endl;
		else cout<<"Partie terminée par match nul"<<endl;
	}
	else cout<<"Partie terminée par erreur"<<endl;
	cin>>continu;
	//win.close();
	*/
	return 0;
}

/* --> Vec, TypePiece, Couleur, IdPiece,  Piece, ConfigrationJeu, Partie, DictionnaireParties
class GestionDictionnairePartiesSDL
{
public:
	GestionDictionnaireSDL();
	
	void boucle();
private:
	JeuSDL m_jeu;
	DictionnaireParties m_dictParties;
	
	Widget m_ihm;
	
	void Affichage() const;
};
*/


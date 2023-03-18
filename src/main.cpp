#include "Partie.h"
#include "ConfigJeu.h"
#include "Piece.h"
#include "Joueur.h"

#include <iostream>

using namespace std; 


class JeuTxt
{
public:
	JeuTxt();
	
	void boucle();
private:
	ConfigurationJeu m_cj;
	
	void affichage() const;
};



// --> Vec, TypePiece, Couleur, IdPiece,  Piece, ConfigrationJeu
class JeuSDL
{
public:
	JeuSDL();
	
	void boucle();											// la boucle est IMPORTANTE
private:
	ConfigurationJeu m_cj;
	/*
	Image m_damier;											// les images sont IMPORTANTES
	Image m_pieces_blanc[TYPEPIECE_MAX];
	Image m_pieces_noir[TYPEPIECE_MAX];
	*/
	void affichage() const;
	Vec2 clicSourie(int mouseX, int mouseY);
};



//

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
	
	void affichage() const;
};
*/
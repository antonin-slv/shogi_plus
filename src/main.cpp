#include "Partie.h"
#include "ConfigJeu.h"
#include "Piece.h"

#include <iostream>
#include <fstream>

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



int main()
{	Vec2 v1(1,2);
	Vec2 v2(3,4);
	v1 += v2;
	cout << v1.x << " " << v1.y << endl;
	

	Piece P1(ROI, BLANC, Vec2(1,2));
	Piece P2(LANCE1, NOIR, Vec2(3,4));
	
	ofstream f("data/test.txt");
	cout<<P1.m_couleur<<endl;
	P1.ecriture(f);
	f.close();

	ifstream g("data/test.txt");
	P2.lecture(g);
	cout<<P2.m_couleur<<endl;
	g.close();

	//test jeu base
	bool continu = true;
	ConfigurationJeu GAME;
	std::vector<Coup> listeCoups;
	Couleur joueur=BLANC;

	Coup coup;


	GAME.init();
	do {
		//affichage des pièces
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				cout<<GAME.getIdPiece(Vec2(j,i)).type<<" ";
			}
			cout<<endl;
		}

		//selection de la pièce
		if (joueur == BLANC) cout<<endl<<"Joueur Blanc (bas)"<<endl;
		else cout<<endl<<"Joueur Noir (haut)"<<endl;
		cout<< "selectionner une piece : (x, y)"<<endl;
		cin>> coup.pos.x >> coup.pos.y;

		//cacul et affichage des déplacements possibles
		listeCoups=GAME.calculTousLesCoupsPossibles(coup.pos);
		cout<<"deplacment possibles :"<<endl;
		for (auto it = listeCoups.begin(); it != listeCoups.end(); ++it)
		{
			cout<<it->deplacement.x<<" "<<it->deplacement.y<<endl;
		}

		//selection du déplacement
		cout<<"selectionner un déplacement : (x, y)"<<endl;
		cin>> coup.deplacement.x >> coup.deplacement.y;

		//test du coup 
		cout<<GAME.getPiece(coup.pos).m_type<<" "<<GAME.getPiece(coup.pos).m_type<<endl;
		if (GAME.jouerCoup(coup))
		{	
			cout<<GAME.getPiece(coup.pos).m_type<<" "<<GAME.getPiece(coup.pos).m_type<<endl;
			
			joueur = (joueur == BLANC) ? NOIR : BLANC;
		}
		else {
			cout<<"Coup invalide, liste des coups possibles pour cette pièce:"<<endl;
			for (auto it = listeCoups.begin(); it != listeCoups.end(); ++it)
			{
				cout<<it->pos.x<<" "<<it->pos.y<<" "<<it->deplacement.x<<" "<<it->deplacement.y<<endl;
			}
			cout<<endl;
		}

		//propose de quitter
		cout<<"0 pour s'arrêter, 1 pour continuer : "<<endl;
		cin>>continu;
		cout<<endl;
	} while (continu);

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
	
	void affichage() const;
};
*/


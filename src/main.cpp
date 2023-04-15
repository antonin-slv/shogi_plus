#include "Partie.h"
#include "ConfigJeu.h"
#include "Piece.h"
#include "Affichage.h"

#include <iostream>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <iostream>

using namespace std; 
using namespace sf;

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

void jeutxt_aff(ConfigurationJeu const & GAME)
{	IdPiece idtemp;
	cout<<endl<<"    0  1  2  3  4  5  6  7  8"<<endl<<endl;
	for (int i = 0; i < 9; i++)
	{	cout << i << "  ";
		for (int j = 0; j < 9; j++)
		{	idtemp=GAME.getIdPiece(Vec2(j,i));
			if(idtemp.type<10 && idtemp.type>=0) cout<<' '<<idtemp.type<<" ";
			else if (idtemp.type==VIDE) cout<<"   ";
			else cout<<idtemp.type<<" ";
		}
		cout<<endl;
		if (i == -1) cout<<endl;
	}
}

void selection_piece(ConfigurationJeu const & GAME, Vec2 & pos)
{	do {
		cout<<endl<<"selectionner une piece : (x, y)"<<endl;
		cin>> pos.x >> pos.y;
	} while(GAME.getIdPiece(pos).type==VIDE||GAME.getIdPiece(pos).coul==UNDEFINED);
}

//algorithme min_max


std::vector<Coup> CalculEnsembleCoups(ConfigurationJeu const & cj)
{	std::vector<Coup> listeCoups;
	for (int i=0; i<9; i++)
	{  for (int j=0; j<9; j++)
		{  	if (cj.getIdPiece(Vec2(i,j)).coul!=cj.joueurSuivant() && cj.getIdPiece(Vec2(i,j)).type!=VIDE)
			{  	std::vector<Coup> listeCoupsTemp=cj.calculCoupsPossibles(Vec2(i,j));
				listeCoups.insert(listeCoups.end(), listeCoupsTemp.begin(), listeCoupsTemp.end());
			}
		}
	}
	return listeCoups;
}

float evaluateur_branche(ConfigurationJeu cj, int n)
{	//breakpoint de fin
	if (n<=0 || cj.partieTerminee()) return cj.evaluer();
   	else
   	{  	//calcul des coups possibles.
		std::vector<Coup> listeCoups=CalculEnsembleCoups(cj);
		//calcul des scores
		float score=cj.evaluer();
		ConfigurationJeu cjtemp;
		int i=0;
		for (auto it = listeCoups.begin(); it != listeCoups.end(); ++it)
		{  	
			//on copie le jeu
			cjtemp=cj;
			//on joue chaque coup
			cjtemp.jouerCoup(*it);
			float scoretemp=evaluateur_branche(cjtemp, n-1);
			scoretemp-=listeCoups.at(i++).deplacement.y/2;
			scoretemp+=(rand()%10-5)/5;
			//si le joueur suivant est le joueur max, on prend le max
			if (cj.joueurSuivant()!=BLANC)
			{	if (scoretemp>score) score=scoretemp;
			}
			//sinon on prend le min
			else
			{	if (scoretemp<score) score=scoretemp;
			}
		}
		return score;
	}
}
Coup min_max(ConfigurationJeu cj, int n)
{  	//calcul des coups possibles.
	std::vector<Coup> listeCoups=CalculEnsembleCoups(cj);
	Coup rslt;
	//calcul des scores
	float score=cj.evaluer();

	ConfigurationJeu cjtemp;

	bool premier=true;
	int i=0;
	for (auto it = listeCoups.begin(); it != listeCoups.end(); ++it)
	{  	
		//on copie le jeu
		cjtemp=cj;
		//on joue chaque coup
		cjtemp.jouerCoup(*it);
		float scoretemp=evaluateur_branche(cjtemp, n);

		scoretemp-=listeCoups.at(i).deplacement.y/2;
		scoretemp+=(rand()%10-5)/5;
		if(premier)
		{	premier=false;
			score=scoretemp;
		}
		//si le joueur actuel est blanc, on prend le max, sinon le min
		if (cj.joueurSuivant()==NOIR)
		{  	if (scoretemp>=score)
			{	score=scoretemp;
				rslt=*it;
			}
		}
		else
		{  	if (scoretemp<=score)
			{	score=scoretemp;
				rslt=*it;
			}
		}
		i++;
	}
	return rslt;
}


int main()
{	
	//test jeu base
	bool continu = true;
	ConfigurationJeu GAME;
	std::vector<Coup> listeCoups;
	Couleur joueur=BLANC;

	Coup coup;

	//initialisation
	RenderWindow win(VideoMode(1000,1000),"Shogi");
	Afficheur TABS;
	TABS.init_sprites();
	GAME.init();
	

	do {
		//affichage des pièces
		TABS.lier(GAME);
		TABS.dessiner(win);
		win.display();
		jeutxt_aff(GAME);
		if (joueur == BLANC && false)
		{	//selection de la pièce
			if (joueur == BLANC) cout<<endl<<"Joueur Blanc (bas)"<<endl;
			else cout<<endl<<"Joueur Noir (haut)"<<endl;
			selection_piece(GAME, coup.pos);

			//cacul et affichage des déplacements possibles
			listeCoups=GAME.calculCoupsPossibles(coup.pos);
			cout<<"deplacment possibles :"<<endl;
			for (auto it = listeCoups.begin(); it != listeCoups.end(); ++it)
			{
				cout<<it->deplacement.x<<" "<<it->deplacement.y<<endl;
			}

			//selection du déplacement
			cout<<"selectionner un déplacement : (x, y)"<<endl;
			cin>> coup.deplacement.x >> coup.deplacement.y;
		}
		else if(joueur == BLANC) coup=min_max(GAME, 1);
		else coup=min_max(GAME,3);
		cout<<'('<<coup.pos.x<<','<<coup.pos.y<<") vers ("<<coup.deplacement.x+coup.pos.x<<','<<coup.deplacement.y+coup.pos.y<<')'<<endl;
		//test du coup 
		//cout<<GAME.getPiece(coup.pos).m_type<<" "<<GAME.getPiece(coup.pos).m_type<<endl;
		if (GAME.jouerCoup(coup))
		{	
			//cout<<GAME.getPiece(coup.pos).m_type<<" "<<GAME.getPiece(coup.pos).m_type<<endl;
			
			joueur = (joueur == BLANC) ? NOIR : BLANC;
		}
		else
		{ 	cout<<'('<<coup.pos.x<<','<<coup.pos.y<<") vers ("<<coup.deplacement.x+coup.pos.x<<','<<coup.deplacement.y+coup.pos.y<<')'<<" impossible"<<endl;	
			std::vector<Coup> possibilite=CalculEnsembleCoups(GAME);
			for (int i=0;i<possibilite.size();++i)
			{
				cout<<'('<<possibilite.at(i).pos.x<<','<<possibilite.at(i).pos.y<<") vers ("<<possibilite.at(i).deplacement.x+possibilite.at(i).pos.x<<','<<possibilite.at(i).deplacement.y+possibilite.at(i).pos.y<<')'<<" prop"<<endl;			

			}
			continu=false;
		}
		/*
		//propose de quitter
		cout<<"0 pour s'arrêter, 1 pour continuer : "<<endl;
		cin>>continu;
		cout<<endl; */
	} while (continu&&!GAME.partieTerminee());

	if (!continu) cout<<"Partie terminée par l'utilisateur"<<endl;
	else if (GAME.partieTerminee())
	{ 	if(GAME.vainqueur()==BLANC) cout<<"Partie terminée par victoire du joueur Blanc"<<endl;
		else if(GAME.vainqueur()==NOIR) cout<<"Partie terminée par victoire du joueur Noir"<<endl;
		else cout<<"Partie terminée par match nul"<<endl;
	}
	else cout<<"Partie terminée par erreur"<<endl;
	cout<<endl<<"presser n'importe quelle touche pour sortir";
	cin>>continu;
	
	//delete win;
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


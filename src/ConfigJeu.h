#ifndef _CONFIGJEU_H_
#define _CONFIGJEU_H_

#include "Piece.h"
#include "Vec2.h"

#include <iostream>
#include <vector>


// un coup=dÃ©place la piÃ¨ce de la case 'pos" vers 'pos+depl'
struct Coup
{
	Vec2 pos;
	Vec2 deplacement;
	Coup(const Vec2& p=Vec2(0,0), const Vec2& d=Vec2(0,0));
};

class ConfigurationJeu
{	
	private:

		// Avec juste ces 2 tableaux, on peut tout faire mais pour trouver une piÃ¨ces Ã  partir d'une position 
		// il faut parcourir les 2 tableaux de pièces. Pas optimal mais ca marche.	
		// Surement qu'un tableau de 40 pièces serait un peu plus optimal, ici
		Piece m_piecesB[20];						// toutes les piÃ¨ces blanches
		Piece m_piecesN[20];						// toutes les piÃ¨ces noires
		Piece m_vide;								// un piÃ¨ce vide (correspond Ã  une case vide)
		// IMPORTANT : il faut ajouter un tableau comme ceci, qui fait double emploi avec les 2 tableaux de 2x16 pieces,
		// mais selon l'algo parfois on a besoin d'avoir la piÃ¨ce et parfois on a besoin du damier !
		IdPiece m_damier[9][9];					// le damier, chaque case sera soit un TypePiece associÃ© Ã  une couleur
												// remarque : dans ce code j'Ã©vite les pointeur et travaille avec des 
												// identitifiants (plus pratique et moins sujet Ã  bug), mais les pointeurs auraient Ã©tÃ© possible aussi
		
		Couleur m_joueurSuivant;				// La couleur du joueur qui doit jouer
	


	public :
		const Piece& getPiece(TypePiece type, Couleur col) const; 		// trouve la piÃ¨ce Ã  partir de son "nom", par exemple getPiece(FOU1, BLANC);
		ConfigurationJeu();						// Appel init : 
		void init();							// Place toutes les piÃ¨ces et range toutes les infos dont identifiant. Appeler au dÃ©but ou Ã  chaque nouvelle partie

		//ok
		bool coupValide(const Coup& c) const;									// indique si un dÃ©placement 'depl' d'une piÃ¨ce (repÃ©rÃ© avec sa position 'pos') est possible
		std::vector<Coup> calculTousLesCoupsPossibles(const Vec2& pos) const;	// construit un tableau de tous les dÃ©placement possible pour une piÃ¨ce
		
		bool jouerCoup(const Coup& c);											// joue un coup=déplace la piÃ¨ce de la case 'pos" vers 'pos+depl' si le coup est possible. Renvoie faux si le coup n'est pas valide
		
		//normalement ok
		const Piece& getPiece(const Vec2& pos) const;							// trouve la pièce à  partir de sa position.
		const Piece& getPiece(const IdPiece& id) const;						// trouve la pièce à  partir d'identifiant
		const IdPiece& getIdPiece(const Vec2& pos) const;							// trouve l'ID de la piÃ¨ce Ã  partir de sa position.
		

		
		bool partieTerminee() const;										// renvoie vrai si un joueur a gagné
		Couleur vainqueur() const;											// renvoie NOIR, BLANC. ATTENTION : valide seulement si la partie est terminÃ©e, 
																			// sinon renvoie la couleur qui a le score le plus Ã©levÃ© (voir f ci-dessus et ci-dessous)
		
		float points() const;				// renvoie la valeur du plateau : positif tend vers le joueur blanc, nÃ©gatif vers le joueur noir

		float distance(ConfigurationJeu cj);		// renvoie un rÃ©el indiquant si les deux configurations sont proches : 0 indique indentique, un grand nombre=trÃ¨s diffÃ©rentes
		
		void ecriture(ofstream& f);
		void lecture(ofstream& f);
		// OU
		/*
		ostream& operator<<(ostream& , const ConfigurationJeu& p) ;
		istream& operator<<(istream& , const ConfigurationJeu& p) ;
		
		static void testRegression() const;
		*/
	bool testRegression();

};




#endif
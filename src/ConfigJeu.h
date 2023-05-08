#ifndef _CONFIGJEU_H_
#define _CONFIGJEU_H_

#include "Piece.h"
#include "Vec2.h"

#include <iostream>
#include <vector>


// un coup = déplace la pièce de la case 'pos" vers 'pos+depl'
struct Coup
{
	Vec2 pos;
	Vec2 deplacement;
	bool promotion=false;
	Coup(const Vec2& p=Vec2(0,0), const Vec2& d=Vec2(0,0), bool prom=false);
	bool operator!=(const Coup& c) const;
};

class ConfigurationJeu
{	
	private:

		// Avec juste ces 2 tableaux, on peut tout faire mais pour trouver une pièces à partir d'une position 
		// il faut parcourir les 2 tableaux de pièces. Pas optimal mais ca marche.	
		// Surement qu'un tableau de 40 pièces serait un peu plus optimal, ici
		Piece m_piecesB[20];						// toutes les pièces blanches
		Piece m_piecesN[20];						// toutes les pièces noires
		Piece m_vide;								// un pièce vide (correspond à une case vide)
		// IMPORTANT : il faut ajouter un tableau comme ceci, qui fait double emploi avec les 2 tableaux de 2x16 pieces,
		// mais selon l'algo parfois on a besoin d'avoir la pièce et parfois on a besoin du damier !
		IdPiece m_damier[9][9];					// le damier, chaque case sera soit un TypePiece associé à une couleur
												// remarque : dans ce code j'évite les pointeur et travaille avec des 
												// identitifiants (plus pratique et moins sujet à bug), mais les pointeurs auraient été possible aussi
		
		Couleur m_joueurSuivant;				// La couleur du joueur qui doit jouer
	


	public :
		const Piece& getPiece(TypePiece type, Couleur col) const; 		// trouve la pièce à partir de son "nom", par exemple getPiece(FOU1, BLANC);
		ConfigurationJeu();						// Appel init : 
		void init();							// Place toutes les pièces et range toutes les infos dont identifiant. Appeler au début ou à chaque nouvelle partie
		void init2();						// Place toutes les pièces et range toutes les infos dont identifiant. Appeler au début ou à chaque nouvelle partie pour la variante

		//ok
		bool coupValide(const Coup& c) const;									// indique si un déplacement 'depl' d'une pièce (repéré avec sa position 'pos') est possible
		std::vector<Coup> calculCoupsPossibles(const Vec2& pos) const;	// construit un tableau de tous les déplacement possible pour une pièce
		std::vector<Coup> CalculEnsembleCoups() const;					// construit un tableau de tous les déplacement possible pour toutes les pièces du joueur courant


		bool jouerCoup(const Coup& c);											// joue un coup=déplace la pièce de la case 'pos" vers 'pos+depl' si le coup est possible. Renvoie faux si le coup n'est pas valide
		
		//normalement ok
		const Piece& getPiece(const Vec2& pos) const;							// trouve la pièce à  partir de sa position.
		const Piece& getPiece(const IdPiece& id) const;						// trouve la pièce à  partir d'identifiant
		const IdPiece& getIdPiece(const Vec2& pos) const;							// trouve l'ID de la pièce à partir de sa position.
		

		Couleur joueurSuivant() const;											// renvoie la couleur du joueur qui jouera au tour prochain
		bool partieTerminee() const;										// renvoie vrai si un joueur a gagné
		Couleur vainqueur() const;											// renvoie NOIR, BLANC. ATTENTION : valide seulement si la partie est terminée, 
																			// sinon renvoie la couleur qui a le score le plus élevé (voir f ci-dessus et ci-dessous)
		
		float evaluer() const;				// renvoie la valeur du plateau : positif tend vers le joueur blanc, négatif vers le joueur noir

		//float distance(ConfigurationJeu cj);		// renvoie un réel indiquant si les deux configurations sont proches : 0 indique indentique, un grand nombre=très différentes
		
		//void ecriture(ofstream& f);
		//void lecture(ofstream& f);
		// OU
		/*
		ostream& operator<<(ostream& , const ConfigurationJeu& p) ;
		istream& operator<<(istream& , const ConfigurationJeu& p) ;
		
		static void testRegression() const;
		*/
	bool testRegression();

};




#endif
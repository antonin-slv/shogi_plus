#ifndef _PIECE_H_
#define _PIECE_H_

#include "Vec2.h"


#include <iostream>
#include <fstream>

using namespace std;

class ConfigurationJeu;

enum TypePiece 
{ 
	VIDE=-1, 
	PION1=0, PION2=1, PION3=2, PION4=3, PION5=4, PION6=5, PION7=6, PION8=7, PION9=8,
	FOU=9, TOUR=10, 
    GENERALOR1=11,GENERALOR2=12,  
    GENERALARGENT1=13,GENERALARGENT2=14,
    CAVALIER1=15, CAVALIER2=16,
	LANCE1=17,LANCE2=18,
    ROI=19,
};

enum Couleur { BLANC, NOIR, UNDEFINED};

class Piece
{
    //private:
    public :
        TypePiece m_type;							// type de la piÃ¨ce(un enum=un int, qui sert Ã©galement pour accÃ¨der Ã  la case du tableau de piÃ¨ces blanche 
                                                    // ou noir de ConfigurationJeu
        Couleur m_couleur;							// BLANC ou NOIR 
        Vec2 m_pos;									// Position sur le damier, valide uniquement si le bool m_enJeu est vrai
        bool m_enJeu;								// Prise ou en jeu
        float m_importance;							// une estimation empirique de la valeur d'une piÃ¨ce, indÃ©pendament de sa position dans une partie


        //fait jet 1
        bool coupValidePerm(const ConfigurationJeu& conf,const Vec2& depl);	// contrÃ´le si le dÃ©placement est possible, de manière générale
        
        bool coupValidePion(const ConfigurationJeu&, Vec2 depl);
        bool coupValideRoi(const ConfigurationJeu&, Vec2 depl);		
        bool coupValideFou(const ConfigurationJeu&, Vec2 depl);		
        bool coupValideCavalier(const ConfigurationJeu&, Vec2 depl);		
        bool coupValideTour(const ConfigurationJeu&, Vec2 depl);	
        bool coupValideGeneralArgent(const ConfigurationJeu&, Vec2 depl);
        bool coupValideGeneralOr(const ConfigurationJeu&, Vec2 depl);
        bool coupValideLance(const ConfigurationJeu&, Vec2 depl);

    public:
        Piece();
        Piece( TypePiece typ, Couleur coul, const Vec2& pos);	// Normalement ici, il n'y aura jamis VIDE dans le type
        void deplacement(Vec2 dep);								// dÃ©place la piÃ¨ce du vecteur 'dep' : ne fait aucun contrôle du damier
        void prise();											// change la piÃ¨ce Ã  prise
        

        //fait jet 1
        bool coupValide(const ConfigurationJeu&, Vec2 depl);		// un switch qui appelle une des fonctions coupValideXXX oÃ¹ XXX dÃ©pend du type de piÃ¨ce, voir en private
        bool enJeu() const;										// renvoie vrai si la pièce est en jeu
        //fait
        void ecriture(ofstream& f);								// operator<< serait surement mieux
        void lecture(ifstream& f);	
        /*							// operator>> serait surement mieux
        ostream& operator<<(ostream& , const Piece& p) ;
        istream& operator<<(istream& , const Piece& p) ;
        
        */
        void testRegression() const;
    
};

struct IdPiece		
{
    TypePiece type;
    Couleur coul;
    IdPiece(int t=-1, Couleur c=BLANC);
};


#endif
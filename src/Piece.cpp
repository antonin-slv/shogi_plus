#include "Piece.h"
#include "ConfigJeu.h"

#include <iostream>
Piece::Piece( TypePiece typ, Couleur coul, const Vec2& pos)
{
    m_type = typ;
    m_couleur = coul;
    m_pos = pos;
    m_enJeu = false;
    m_importance = 0;
}
Piece::Piece()
{   m_type = VIDE;
    m_couleur = BLANC;
    m_pos = Vec2(-1,-1);
    m_enJeu = false;
    m_importance = 0;
}


IdPiece::IdPiece(int t, Couleur c)
{
    type = (TypePiece) t;
    coul = c;
}


void Piece::deplacement(Vec2 dep) { m_pos += dep;}

void Piece::prise() { m_enJeu = false; }





void Piece::ecriture(ofstream& f)
{   
    f << (int)m_type << " " << m_couleur << " " << m_pos.x << " "<< m_pos.y << " " << m_enJeu << " " << m_importance << endl;
}
void Piece::lecture(ifstream& f)
{   int a;
    bool col;
    f >> a >> col >> m_pos.x >> m_pos.y >> m_enJeu >> m_importance;
    m_type = (TypePiece)a;
    m_couleur = (Couleur) col;
}


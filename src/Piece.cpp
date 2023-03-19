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

//private
bool DansJeu(const Vec2& pos)
{   return (pos.x >= 0 && pos.x < 9 && pos.y >= 0 && pos.y < 9);
}

bool Piece::coupValidePion(const ConfigurationJeu& conf,Vec2 depl)
{   IdPiece idarrive = conf.getIdPiece(depl+m_pos);
    if (idarrive.coul == m_couleur)
    {   if(idarrive.type != -1) return false;
    }

    if (m_couleur == BLANC)
    {   return (depl.y == -1 && depl.x == 0);
    }
    else
    {   return (depl.y == 1 && depl.x == 0);
    }   
}

bool Piece::coupValideTour(const ConfigurationJeu& conf,Vec2 depl)
{   IdPiece idarrive = conf.getIdPiece(depl+m_pos);
    if (idarrive.coul == m_couleur)
    {   if(idarrive.type != -1) return false;
    }
    return (depl.x == 0 || depl.y == 0);
}

bool Piece::coupValideCavalier(const ConfigurationJeu& conf,Vec2 depl)
{   IdPiece idarrive = conf.getIdPiece(depl+m_pos);
    if (idarrive.coul == m_couleur)
    {   if(idarrive.type != -1) return false;
    }

    if (depl.x == 1 || depl.x == -1)
    {   if (m_couleur == BLANC)
        { return depl.y == -2;
        }
        else
        { return depl.y == 2;
        }
    }
    return false;
}

bool Piece::coupValideFou(const ConfigurationJeu& conf,Vec2 depl)
{   IdPiece idarrive = conf.getIdPiece(depl+m_pos);
    if (idarrive.coul == m_couleur)
    {   if(idarrive.type != -1) return false;
    }
    return (depl.x == depl.y || depl.x == -depl.y);
}
/*
bool ConfigurationJeu::coupValideReine(const ConfigurationJeu& conf,Vec2 depl)
{   IdPiece idarrive = conf.getIdPiece(depl);
    if (idarrive.coul == Couleur)
    {   if(idarrive.type != -1) return false;
    }
    return (depl.x == depl.y || depl.x == -depl.y || depl.x == 0 || depl.y == 0)
}*/

bool Piece::coupValideRoi(const ConfigurationJeu& conf,Vec2 depl)
{   IdPiece idarrive = conf.getIdPiece(depl+m_pos);
    if (idarrive.coul == m_couleur)
    {   if(idarrive.type != -1) return false;
    }
    
    return ( abs(depl.x) <= 1 && abs(depl.y) <= 1);
}

bool Piece::coupValideLance(const ConfigurationJeu& conf,Vec2 depl)
{   IdPiece idarrive = conf.getIdPiece(depl+m_pos);
    if (idarrive.coul == m_couleur)
    {   if(idarrive.type != -1) return false;
    }
    
    if (m_couleur == BLANC)
    {   return (depl.y >= 0 && depl.x == 0);
    }
    else
    {   return (depl.y <= 0 && depl.x == 0);
    }

}
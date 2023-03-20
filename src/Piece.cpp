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

bool Piece::coupValide(const ConfigurationJeu& conf, Vec2 depl)
{   if (!coupValidePerm(conf,depl)) return false;
    if (m_type >= PION1 && m_type <= PION9) return coupValidePion(conf,depl);
    if (m_type >= GENERALOR1 && m_type <= GENERALOR2) return coupValideGeneralOr(conf,depl);
    if (m_type >= GENERALARGENT1 && m_type <= GENERALARGENT2) return coupValideGeneralArgent(conf,depl);
    switch (m_type)
    {   case ROI: return coupValideRoi(conf,depl);
        case FOU: return coupValideFou(conf,depl);
        case CAVALIER1: return coupValideCavalier(conf,depl);
        case CAVALIER2: return coupValideCavalier(conf,depl);
        case TOUR: return coupValideTour(conf,depl);
        case LANCE1: return coupValideLance(conf,depl);
        case LANCE2: return coupValideLance(conf,depl);
        default: return false;
    }
}

//private
bool Piece::coupValidePerm(const ConfigurationJeu& conf,const Vec2& depl)
{   if (m_pos.x+depl.x < 0 || m_pos.x+depl.x >= 9 || m_pos.y+depl.y <0 || m_pos.y+depl.y >= 9) return false;
    IdPiece idarrive = conf.getIdPiece(depl+m_pos);
    if (idarrive.coul == m_couleur)
    {   if(idarrive.type != -1) return false;
    }
    return true;
}

bool Piece::coupValidePion(const ConfigurationJeu& conf,Vec2 depl)
{   if (m_couleur == BLANC)
    {   return (depl.y == -1 && depl.x == 0);
    }
    else
    {   return (depl.y == 1 && depl.x == 0);
    }   
}

bool Piece::coupValideTour(const ConfigurationJeu& conf,Vec2 depl)
{   return (depl.x == 0 || depl.y == 0);
}

bool Piece::coupValideCavalier(const ConfigurationJeu& conf,Vec2 depl)
{   if (depl.x == 1 || depl.x == -1)
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
{  return (depl.x == depl.y || depl.x == -depl.y);
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
{  
    return ( abs(depl.x) <= 1 && abs(depl.y) <= 1);
}

bool Piece::coupValideLance(const ConfigurationJeu& conf,Vec2 depl)
{   if (m_couleur == BLANC)
    {   return (depl.y <= 0 && depl.x == 0);
    }
    else
    {   return (depl.y >= 0 && depl.x == 0);
    }

}

bool Piece::coupValideGeneralOr(const ConfigurationJeu& conf,Vec2 depl)
{   if (m_couleur == BLANC)
    {   return ((depl.y==0 || depl.y == -1) && abs(depl.x) <= 1)|| (depl.y == 1 && depl.x == 0);
    }
    else
    {   return ((depl.y==0 || depl.y == 1) && abs(depl.x) <= 1)|| (depl.y == -1 && depl.x == 0);
    }
}

bool Piece::coupValideGeneralArgent(const ConfigurationJeu& conf,Vec2 depl)
{   if (m_couleur == BLANC)
    {   return (depl.y == -1 && abs(depl.x) <= 1) || (depl.y == 1 && abs(depl.x) == 1);
    }
    else 
    {   return (depl.y == 1 && abs(depl.x) <= 1) || (depl.y == -1 && abs(depl.x) == 1);
    }
}
#include "Piece.h"
#include "ConfigJeu.h"
#include <math.h>
#include <iostream>


float importance(TypePiece typ, Couleur coul, bool promue)
{   float m_importance = 0;
    if(typ == TOUR) m_importance = 20;
    else if(typ == FOU) m_importance = 22;
    else if(typ == LANCE1 || typ == LANCE2)m_importance = 10;
    else if(typ == CAVALIER1 || typ == CAVALIER2)m_importance = 18;
    else if(typ == GENERALOR1 || typ == GENERALOR2)m_importance = 14;
    else if(typ == GENERALARGENT1 || typ == GENERALARGENT2)m_importance = 12;
    else if(typ == ROI)m_importance = 200;
    else if(typ >= PION1 && typ <= PION9 )m_importance = 8;
    
    if(coul == NOIR) m_importance *= -1;

    return m_importance;
}

Piece::Piece( TypePiece typ, Couleur coul, const Vec2& pos)
{
    m_type = typ;
    m_couleur = coul;
    m_pos = pos;
    m_enJeu = true;
    m_importance = importance(typ, coul,false);
    m_promue = false;
}

Piece::Piece()
{   m_type = VIDE;
    m_couleur = UNDEFINED;
    m_pos = Vec2(-1,-1);
    m_enJeu = true;
    m_importance = 0;
    m_promue = false;
}

IdPiece::IdPiece(int t, Couleur c)
{
    type = (TypePiece) t;
    coul = c;
}

void Piece::deplacement(Vec2 dep) {
    m_pos += dep;
}

Vec2 const Piece::getPos() const {
    return m_pos;
}

void Piece::prise() {
    m_enJeu = false;
    m_pos = Vec2(-1,-1);
}

bool Piece::enJeu() const {
    return m_enJeu;
}

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
{   
    if (m_promue) return coupValideGeneralOr(conf,depl);
    else if (m_couleur == BLANC) return (depl.y == -1 && depl.x == 0);
    else return (depl.y == 1 && depl.x == 0);

}

bool Piece::coupValideTour(const ConfigurationJeu& conf,Vec2 depl)
{   if (depl.x == 0 && depl.y == 0) return false;
    //vérifie pas de pièce sur chemin en foncition de la direction
    if (depl.y == 0) 
    {   if (depl.x > 0) for (int i = 1; i < depl.x; i++)
        {   if (conf.getIdPiece(m_pos+Vec2(i,0)).type != -1) return false;
        }
        else for (int i = 1; i < -depl.x; i++)
        {   if (conf.getIdPiece(m_pos+Vec2(-i,0)).type != -1) return false;
        }
        return true;    
    }
    else if (depl.x == 0) 
    {   if (depl.y > 0) for (int i = 1; i < depl.y; i++)
            {   if (conf.getIdPiece(m_pos+Vec2(0,i)).type != -1) return false;
            }
        else for (int i = 1; i < -depl.y; i++)
            {   if (conf.getIdPiece(m_pos+Vec2(0,-i)).type != -1) return false;
            }
        return true;
    }
    if (m_promue) return (abs(depl.x) == 1 && abs(depl.y) == 1);
    return false;
}

bool Piece::coupValideCavalier(const ConfigurationJeu& conf,Vec2 depl)
{   
    if (m_promue) return coupValideGeneralOr(conf,depl);
    else if (depl.x == 1 || depl.x == -1)
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
{  

    if ((depl.x == depl.y || depl.x == -depl.y)&& depl.x != 0)
    {   //vérifie pas de pièce sur chemin
        //PREND SIGNES DES D2PLACMEENT
        int sx, sy;
        if (depl.x > 0) sx = 1;
        else sx = -1;
        if (depl.y > 0) sy = 1;
        else sy = -1;
        for (int i = 1; i < abs(depl.x); i++)
        {   if (conf.getIdPiece(m_pos+Vec2(sx*i,sy*i)).type != -1) return false;
        }
        return true;
    }
    if (m_promue)
    {   if (depl.y==0 && (depl.x == 1 || depl.x == -1)) return true;
        if (depl.x==0 && (depl.y == 1 || depl.y == -1)) return true;
    }
    return false;
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
{   return (abs(depl.x) <= 1 && abs(depl.y) <= 1 && (depl.x != 0 || depl.y != 0));
}

bool Piece::coupValideLance(const ConfigurationJeu& conf,Vec2 depl)
{   if (m_promue) return coupValideGeneralOr(conf,depl);
    if (m_couleur == BLANC)
    {   
        if (depl.y < 0 && depl.x == 0)
        {   for (int i = -1; i > depl.y; i--)
            {   if (conf.getIdPiece(m_pos+Vec2(0,i)).type != -1) return false;
            }
            return true;
        }
        else return false;
        
    }
    else
    {   if (depl.y > 0 && depl.x == 0)
        {   for(int i = 1; i < depl.y; i++)
            {   if (conf.getIdPiece(m_pos+Vec2(0,i)).type != -1) return false; }
            return true;
        }
        return false;
    }
}

bool Piece::coupValideGeneralOr(const ConfigurationJeu& conf,Vec2 depl)
{   
    if (depl == Vec2(0,0)) return false;
    if (m_couleur == BLANC)
    {   return ((depl.y==0 || depl.y == -1) && abs(depl.x) <= 1)|| (depl.y == 1 && depl.x == 0);
    }
    else
    {   return ((depl.y==0 || depl.y == 1) && abs(depl.x) <= 1)|| (depl.y == -1 && depl.x == 0);
    }
}

bool Piece::coupValideGeneralArgent(const ConfigurationJeu& conf,Vec2 depl)
{   if (m_promue) return coupValideGeneralOr(conf,depl);
    if (m_couleur == BLANC)
    {   return (depl.y == -1 && abs(depl.x) <= 1) || (depl.y == 1 && abs(depl.x) == 1);
    }
    else 
    {   return (depl.y == 1 && abs(depl.x) <= 1) || (depl.y == -1 && abs(depl.x) == 1);
    }
}
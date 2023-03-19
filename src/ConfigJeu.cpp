#include "ConfigJeu.h"
#include <cassert>

#include "Piece.h"

Coup::Coup(const Vec2& p, const Vec2& d)
{   pos=p;
    deplacement=d;
}
//privée
const Piece& ConfigurationJeu::getPiece(TypePiece type, Couleur col) const
{   if (col==BLANC)
    {   for (int i=0; i<20; i++)
        {   if (m_piecesB[i].m_type==type)
            {   return m_piecesB[i];
            }
        }
    }
    else
    {   for (int i=0; i<16; i++)
        {   if (m_piecesN[i].m_type==type)
            {   return m_piecesN[i];
            }
        }
    }

    return m_vide; // si on arrive ici, c'est qu'on a pas trouvÃ© la piÃ¨ce
}

//publique
const Piece& ConfigurationJeu::getPiece(const Vec2& pos) const
{   for (int i=0; i<20; i++)
    {   if (m_piecesB[i].m_pos==pos)
        {   return m_piecesB[i];
        }
    }
    for (int i=0; i<20; i++)
    {   if (m_piecesN[i].m_pos==pos)
        {   return m_piecesN[i];
        }
    }
    return m_vide;
}

const Piece& ConfigurationJeu::getPiece(const IdPiece& id) const
{   return getPiece(id.type, id.coul);
}

const IdPiece& ConfigurationJeu::getIdPiece(const Vec2& pos) const
{   return m_damier[pos.x][pos.y];
}




ConfigurationJeu::ConfigurationJeu()
{   for (int x=0;x<9;x++)
    {   for (int y=0;y<9;y++)
        {   m_damier[x][y]=IdPiece();
        }
    }

    for (int i=0; i<20; i++)
    {   
        m_piecesB[i]=Piece(TypePiece(i), BLANC, Vec2(0,0));
        m_piecesN[i]=Piece(TypePiece(i), NOIR, Vec2(0,0));
    }

    m_vide=Piece(VIDE, BLANC, Vec2(-1,-1));

    m_joueurSuivant=BLANC;
}



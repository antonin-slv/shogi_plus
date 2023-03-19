#include "ConfigJeu.h"
#include <cassert>

#include "Piece.h"


Coup::Coup(const Vec2& p=Vec2(0,0), const Vec2& d=Vec2(0,0))
{   m_pos=p;
    m_depl=d;
}

const Piece& ConfigurationJeu::getPiece(IdPiece idp, Couleur col)
{   if (col==BLANC)
    {   for (int i=0; i<16; i++)
        {   if (m_piecesBlanc[i].m_idp==idp)
            {   return m_piecesB[i];
            }
        }
    }
    else
    {   for (int i=0; i<16; i++)
        {   if (m_piecesNoir[i].m_idp==idp)
            {   return m_piecesN[i];
            }
        }
    }

    assert(false); // si on arrive ici, c'est qu'on a pas trouvÃ© la piÃ¨ce
}


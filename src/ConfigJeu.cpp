#include "ConfigJeu.h"
#include <cassert>

#include "Piece.h"


Coup::Coup(const Vec2& p, const Vec2& d)
{   pos=p;
    deplacement=d;
}

const Piece& ConfigurationJeu::getPiece(TypePiece type, Couleur col)
{   if (col==BLANC)
    {   for (int i=0; i<16; i++)
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

    assert(false); // si on arrive ici, c'est qu'on a pas trouvÃ© la piÃ¨ce
}


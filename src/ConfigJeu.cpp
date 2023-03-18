#include "Plateau.h"
#include <cassert>

Plateau::Plateau()
{   dimx = 0;
    dimy = 0;
    nb_pieces = 0;
    tab_piece.clear();
    tab_piece.resize(0);
}

Plateau::Plateau(unsigned int x, unsigned int y, unsigned int nb_p)
{   dimx = x;
    dimy = y;
    nb_pieces = nb_p;
    tab_piece.clear();
    tab_piece.resize(dimx);
    for(unsigned int i = 0; i < dimx; i++)
    {   tab_piece[i].resize(dimy);
    }
}

unsigned int Plateau::getDimx() { return dimx; }
unsigned int Plateau::getDimy() { return dimy; }
unsigned int Plateau::getNbPieces() { return nb_pieces; }

Piece * Plateau::getPiece(unsigned int x, unsigned int y) const
{   assert((x < dimx) && (y < dimy));
    return tab_piece[x][y];
}


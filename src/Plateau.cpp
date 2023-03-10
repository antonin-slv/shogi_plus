#include "Plateau.h"
#include <cassert>

unsigned int Plateau::getDimx() { return dimx; }
unsigned int Plateau::getDimy() { return dimy; }
unsigned int Plateau::getNbPieces() { return nb_pieces; }

Piece * Plateau::getPiece(unsigned int x, unsigned int y)
{   assert((x < dimx) && (y < dimy));
    return &tab_piece[x][y]; 
}


#include "Piece.h"

Piece::Piece()
{
    type = PION;
    couleur = 0;
}
Piece::Piece(typePiece t, bool c)
{
    type = t;
    couleur = c;
}

typePiece Piece::getType() { return type; }
bool Piece::getCouleur() { return couleur; }
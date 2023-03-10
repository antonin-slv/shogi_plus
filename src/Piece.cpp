#include "Piece.h"

Piece::Piece()
{
    type = NONDEF;
    couleur = 0;
}
Piece::Piece(typePiece t, bool c)
{
    type = t;
    couleur = c;
}
Piece::Piece(const Piece & p)
{
    type = p.type;
    couleur = p.couleur;
}

Piece::Piece(const Piece * p)  
{
    type = p->type;
    couleur = p->couleur;
}

typePiece Piece::getType() const { return type; }
bool Piece::getCouleur() const{ return couleur; }
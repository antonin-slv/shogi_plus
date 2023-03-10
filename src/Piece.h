#ifndef _PIECE_H_
#define _PIECE_H_


enum typePiece {PION, TOUR, CAVALIER, FOU, REINE, ROI,NONDEF};

class Piece
{   private :
        typePiece type;
        bool couleur;//0 = noir, 1 = blanc
    public :
        Piece();
        Piece(typePiece t, bool c);
        Piece(const Piece & p);
        Piece(const Piece * p);

        typePiece getType() const;
        bool getCouleur() const;
};

#endif
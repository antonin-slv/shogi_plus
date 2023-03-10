#ifndef _PIECE_H_
#define _PIECE_H_


enum typePiece {PION, TOUR, CAVALIER, FOU, REINE, ROI};

class Piece
{   private :
        typePiece type;
        bool couleur;//0 = noir, 1 = blanc
    public :
        Piece();
        Piece(typePiece t, bool c);
        
        typePiece getType();
        bool getCouleur();
};

#endif
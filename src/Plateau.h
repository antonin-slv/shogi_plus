#ifndef _PLATEAU_H_
#define _PLATEAU_H_

#include "Piece.h"
#include <vector>


using namespace std;

class Plateau
{   private :
        unsigned int dimx;
        unsigned int dimy;
        vector<vector<Piece>> tab_piece;
        unsigned int nb_pieces;
    public :
        unsigned int getDimx();
        unsigned int getDimy();
        unsigned int getNbPieces();
        Piece * getPiece(unsigned int x,  unsigned int y);
};


#endif
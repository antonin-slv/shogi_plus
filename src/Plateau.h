#ifndef _PLATEAU_H_
#define _PLATEAU_H_

#include "Piece.h"
#include <vector>


using namespace std;

class Plateau
{   private :
        unsigned int dimx;
        unsigned int dimy;
        vector<vector<Piece *>> tab_piece;
        unsigned int nb_pieces;

    public :

        Plateau();
        Plateau(unsigned int x, unsigned int y,unsigned int nb_p=0);
        Plateau(const Plateau & p);
        Plateau(const Plateau * p);

        unsigned int getDimx();
        unsigned int getDimy();
        unsigned int getNbPieces();
        Piece * getPiece(unsigned int x,  unsigned int y) const;
};


#endif
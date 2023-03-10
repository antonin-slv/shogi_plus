#ifndef _JOUEUR_
#define _JOUEUR_

class Joueur
{   private :
        bool humain;
        
    public :
        Joueur();
        Joueur(bool ordi);

        bool isHumain() const;
};

#endif
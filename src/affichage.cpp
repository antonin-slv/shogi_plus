#include "Affichage.h"

Afficheur::Afficheur()
{   pion_b.loadFromFile("data/img/pion_blanc.png");
    pion_n.loadFromFile("data/img/pion_noir.png");

    pion.loadFromFile("data/img/pion.png");
    tour.loadFromFile("data/img/tour.png");
    lance.loadFromFile("data/img/lance.png");
    cavalier.loadFromFile("data/img/cavalier.png");
    fou.loadFromFile("data/img/fou.png");
    gen_or.loadFromFile("data/img/gen_or.png");
    gen_arg.loadFromFile("data/img/gen_argent.png");
    roi.loadFromFile("data/img/roi.png");

    damier.loadFromFile("data/img/plateau.png");
}



void Afficheur::init_sprites()
{   ban.setTexture(damier);
    ban.setOrigin(ban.getScale().x/2, ban.getScale().y/2);
    TypePiece i=ROI;
    Sprite s_temp;
    Texture * t_temp;
    bool error=false;
    for(int j=0; j < 20; j++)
    {   i=(TypePiece) j;
        
        if(i == TOUR)t_temp = &tour;
        else if(i == FOU)t_temp = &fou;
        else if(i == LANCE1 || i== LANCE2)t_temp = &lance;
        else if(i == CAVALIER1 || i == CAVALIER2)t_temp = &cavalier;
        else if(i == GENERALOR1 || i == GENERALOR2)t_temp = &gen_or;
        else if(i == GENERALARGENT1 || i == GENERALARGENT2)t_temp = &gen_arg;
        else if(i == ROI)t_temp = &roi;
        else if(i >= PION1 && i<= PION9 )t_temp = &pion;
        else t_temp=nullptr;
        if (t_temp != nullptr)
        {   s_temp = Sprite(*t_temp);
            s_temp.setOrigin(t_temp->getSize().x/2, t_temp->getSize().y/2);
            s_temp.rotate(180);
            s_temp.setOrigin(t_temp->getSize().x, t_temp->getSize().y);
            pieces_n.push_back(s_temp);
            pieces_b.push_back(Sprite(*t_temp));
        }
        cout<<"i="<<i<<endl;  
    }
    
    //delete t_temp;
}

void Afficheur::lier(const ConfigurationJeu& cj)
{   for(int i=0; i<20; i++)
    {   pieces_b[i].setPosition(cj.getPiece((TypePiece) i, BLANC).getPos().x*95+10, cj.getPiece((TypePiece) i, BLANC).getPos().y*100+5);
        pieces_n[i].setPosition(cj.getPiece((TypePiece) i, NOIR).getPos().x*95+10, cj.getPiece((TypePiece) i, NOIR).getPos().y*100+5);
    }
}

void Afficheur::dessiner(RenderWindow& fenetre)
{   fenetre.clear();
    fenetre.draw(ban);
    for(int i=0; i<20; i++)
    {   fenetre.draw(pieces_b[i]);
        fenetre.draw(pieces_n[i]);
    }
}
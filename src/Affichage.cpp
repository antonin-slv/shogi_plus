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
        //cout<<"i="<<i<<endl;
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

void jeutxt_aff(ConfigurationJeu const & GAME)
{	IdPiece idtemp;
	cout<<endl<<"    0  1  2  3  4  5  6  7  8"<<endl<<endl;
	for (int i = 0; i < 9; i++)
	{	cout << i << "  ";
		for (int j = 0; j < 9; j++)
		{	idtemp=GAME.getIdPiece(Vec2(j,i));
			if(idtemp.type<10 && idtemp.type>=0) cout<<' '<<idtemp.type<<" ";
			else if (idtemp.type==VIDE) cout<<"   ";
			else cout<<idtemp.type<<" ";
		}
		cout<<endl;
		if (i == -1) cout<<endl;
	}
}

void selection_coup_TXT(ConfigurationJeu const & GAME, Coup & coup)
{	do {
		cout<<endl<<"selectionner une piece : (x, y)"<<endl;
		cin>> coup.pos.x >> coup.pos.y;
	} while(GAME.getIdPiece(coup.pos).type==VIDE||GAME.getIdPiece(coup.pos).coul==UNDEFINED);
    vector<Coup> listeCoups;
    listeCoups=GAME.calculCoupsPossibles(coup.pos);
    //cacul et Affichage des déplacements possibles
    listeCoups=GAME.calculCoupsPossibles(coup.pos);
    cout<<"deplacment possibles :"<<endl;
    for (auto it = listeCoups.begin(); it != listeCoups.end(); ++it)
    {
        cout<<it->deplacement.x<<" "<<it->deplacement.y<<endl;
    }

    //selection du déplacement
    cout<<"selectionner un déplacement : (x, y)"<<endl;
    cin>> coup.deplacement.x >> coup.deplacement.y;
}

void Afficheur::selection_coup_SFML(RenderWindow & win,ConfigurationJeu const & GAME, Coup & coup){
    bool continu=true;
    Piece piece;
    Coup coup_prec=coup;
    
    Vec2 div(damier.getSize().x/9,damier.getSize().y/9);//taille d'une case
    do {

        Event event;
        while (win.pollEvent(event))
        {   if (event.type == Event::Closed) {
                continu=false;   
            }
        }
        //on récupère la position de la souris
        Vector2i pos_souris = Mouse::getPosition();
        //on map la position au damier
        coup.pos.x = pos_souris.x/div.x;
        coup.pos.y = pos_souris.y/div.y;
        
        dessiner(win);

        //rectangle de selection
        RectangleShape rectangle(Vector2f(div.x, div.y));
        rectangle.setFillColor(Color(200, 150, 255, 0));
        rectangle.setOutlineThickness(2);
        rectangle.setOutlineColor(Color(180, 120, 255, 255));
        rectangle.setPosition(coup.pos.x*div.x, coup.pos.y*div.y);
        win.draw(rectangle);
        win.display();
        if (coup.pos.x<0||coup.pos.x>8||coup.pos.y<0||coup.pos.y>8) piece=Piece();
        else
        {   
            if (coup_prec.pos!=coup.pos)
            {   cout<<"x :"<<coup.pos.x<<" y :"<<coup.pos.y<<endl;
                coup_prec=coup;
                piece= GAME.getPiece(coup.pos);
                if (piece.m_couleur==UNDEFINED||piece.m_type==VIDE) piece=Piece();
                
            }

        }
    }while (piece.m_couleur==UNDEFINED||piece.m_type==VIDE||continu);   
}
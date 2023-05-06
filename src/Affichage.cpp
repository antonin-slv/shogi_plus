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

    font.loadFromFile("data/Consolas.ttf");
    text_temp.setFont(font);
    cout<<"Afficheur créé"<<endl;

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

    bool piece_selectionne=false;

    Piece piece;
    
    Vec2 div(damier.getSize().x/9,damier.getSize().y/9);//taille d'une case
    //rectangle autour de la case sélectionné
    RectangleShape rect_select(Vector2f(div.x, div.y));
    rect_select.setFillColor(Color(200, 150, 255, 0));
    rect_select.setOutlineThickness(2);
    rect_select.setOutlineColor(Color(180, 120, 255, 255));

    //rectangle autour des cases possibles
    RectangleShape rect_poss(Vector2f(div.x, div.y));
    rect_poss.setOutlineColor(Color(50,100,255));
    rect_poss.setOutlineThickness(2);
    rect_poss.setFillColor(Color(0,0,0,50));

    text_temp.setCharacterSize(50);
    text_temp.setFillColor(Color::White);
    text_temp.setOrigin(0,0);
    text_temp.setPosition(0,0);


    vector<Coup> listeCoups;//liste des coups possibles si une pièce est sélectionné
    Clock last_click;//dernier click de souris
    do {

        Event event;
        while (win.pollEvent(event))
        {   if (event.type == Event::Closed) {
                continu=false;   
            }
            //annule la selection en appuyant sur echap
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                piece_selectionne=false;
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
                coup.promotion=!coup.promotion;
            }
        }


        //quand on clique sur une case
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            //on récupère la position de la souris
            Vector2i pos_souris = Mouse::getPosition();
            Vec2 case_souris(pos_souris.x/div.x, pos_souris.y/div.y);//case de la souris


            if (last_click.getElapsedTime().asMilliseconds()<100) continue;//si le dernier click est trop récent, on ne fait rien
            last_click.restart();
            
            //si on clique hors du  terrain :
            if (case_souris.x<0 || case_souris.x>8 || case_souris.y<0 || case_souris.y>8) {
                piece_selectionne=false;//on annule la selection
                listeCoups.clear();
                continue;
            }
            piece= GAME.getPiece(case_souris);//la pièce sur laquelle on clique.
            //si on clique sur une de nos pièces
            if (piece.m_couleur== ((GAME.joueurSuivant()==BLANC) ? NOIR : BLANC)) {
                //on sélectionne cette pièce à la place de l'ancienne
                piece_selectionne=false;
                listeCoups.clear();
            }
            
            if(!piece_selectionne) {//si on doit sélectionner une pièce
                if (piece.m_couleur==UNDEFINED||piece.m_type==VIDE) {//si la case est vide ou n'existe pas
                    piece=Piece();
                    rect_select.setPosition(Vector2f(-2,-2));
                    listeCoups.clear();
                }
                else { // si la case contient une pièce
                    piece_selectionne=true;
                    coup.pos=case_souris;
                    //mise a jour du rectangle de selection
                    rect_select.setPosition(coup.pos.x*div.x, coup.pos.y*div.y);
                    //calcul et Affichage des déplacements possibles
                    listeCoups=GAME.calculCoupsPossibles(coup.pos);
                }
            }
            else if (piece_selectionne) {
                coup.deplacement=case_souris-coup.pos;
                //on vérifie si le déplacement est possible
                for (auto it = listeCoups.begin(); it != listeCoups.end(); ++it) {
                    if (it->deplacement==coup.deplacement) {
                        return;//si le déplacement est possible, on sort de la fonction avec le coup
                    }
                }
                //si le déplacement n'est pas possible, on continue sans rien faire
                piece_selectionne=false;
                listeCoups.clear();
                rect_select.setPosition(Vector2f(-100,-100));
            }
        }
        dessiner(win);
        //indiquer qu'on promeut
        if (coup.promotion) {
            text_temp.setString("coup + promotion");
            text_temp.setPosition(ban.getLocalBounds().width,10);
            //affichage des déplacements possibles
            for (auto it = listeCoups.begin(); it != listeCoups.end(); ++it)
            {   if (!it->promotion) continue;
                rect_poss.setPosition((coup.pos.x+it->deplacement.x)*div.x, (coup.pos.y+it->deplacement.y)*div.y);
                win.draw(rect_poss);
            }
        }
        else {
            text_temp.setString("Entrer pour promouvoir en bougeant");
            text_temp.setPosition(ban.getLocalBounds().width,10);
         
            //affichage des déplacements possibles
            for (auto it = listeCoups.begin(); it != listeCoups.end(); ++it) {   
                if (it->promotion) continue;
                rect_poss.setPosition((coup.pos.x+it->deplacement.x)*div.x, (coup.pos.y+it->deplacement.y)*div.y);
                win.draw(rect_poss);
            }
        }
        win.draw(text_temp);

        win.draw(rect_select);
        win.display();
    } while (piece.m_couleur==UNDEFINED||piece.m_type==VIDE||continu);   
}
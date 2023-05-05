#include "Partie.h"


Partie :: Partie() : ConfigurationJeu()
{
    etapeActuelle = 0;
}

void Partie::boucle_Jeu(Afficheur& TABS, RenderWindow& win,Parametre & param) {
    srand(time(NULL));
    //test jeu base
    bool continu = true;
    std::vector<Coup> listeCoups;
    Couleur joueur=BLANC;

    Coup coup;
    sf::Clock clock;
    //initialisation
    TABS.init_sprites();
    int v_b=0,v_n=0;
    float tp_B=0,tp_N=0;
    for (int i=0;i<20;++i)	
    {
        GAME.init();
        int nombre_etape=0;
        
        do {
            //Affichage des pièces
            TABS.lier(GAME);
            TABS.dessiner(win);
            win.display();
            //jeutxt_aff(GAME);
            //cout<<"etape : "<<nombre_etape<<endl;
            clock.restart();
            if (joueur == BLANC && false)
            {	//selection de la pièce
                if (joueur == BLANC) cout<<endl<<"Joueur Blanc (bas)"<<endl;
                else cout<<endl<<"Joueur Noir (haut)"<<endl;
                selection_piece(GAME, coup.pos);

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
            else if(joueur == BLANC)
            {	coup=alphabeta(GAME,1);
                tp_B+=clock.restart().asSeconds();
                //Coup coup2=min_max(GAME,2);
                //if (coup2!=coup) cout<<"not ok"<<endl;
            }
            else
            {	coup=alphabeta(GAME,2);
                tp_N+=clock.restart().asSeconds();
            }
            nombre_etape++;
            //cout<<joueur<<'('<<coup.pos.x<<','<<coup.pos.y<<") vers ("<<coup.deplacement.x+coup.pos.x<<','<<coup.deplacement.y+coup.pos.y<<")"<<endl;
            //test du coup 

            if (GAME.jouerCoup(coup))
            {	
                joueur = (joueur == BLANC) ? NOIR : BLANC;
            }
            else
            { 	cout<<'('<<coup.pos.x<<','<<coup.pos.y<<") vers ("<<coup.deplacement.x+coup.pos.x<<','<<coup.deplacement.y+coup.pos.y<<')'<<" impossible"<<endl;	
                std::vector<Coup> possibilite=GAME.CalculEnsembleCoups();
                for (int i=0;i<possibilite.size();++i)
                {
                    cout<<'('<<possibilite.at(i).pos.x<<','<<possibilite.at(i).pos.y<<") vers ("<<possibilite.at(i).deplacement.x+possibilite.at(i).pos.x<<','<<possibilite.at(i).deplacement.y+possibilite.at(i).pos.y<<')'<<" prop"<<endl;			

                }
                continu=false;
            }
            /*
            //propose de quitter
            cout<<"0 pour s'arrêter, 1 pour continuer : "<<endl;
            cin>>continu;
            cout<<endl; */

        } while (continu&&!GAME.partieTerminee()&&nombre_etape<250);
        if (GAME.vainqueur()==BLANC) v_b++;
        else if (GAME.vainqueur()==NOIR) v_n++;
        jeutxt_aff(GAME);
        cout<<"temps de calcul blanc : "<<tp_B<<endl;
        cout<<"temps de calcul noir  : "<<tp_N<<endl;
        cout<<"victoire blanc : "<<v_b<<endl;
        cout<<"victoire noir  : "<<v_n<<endl;
    }
}
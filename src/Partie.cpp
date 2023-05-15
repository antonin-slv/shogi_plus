#include "Partie.h"


Partie :: Partie()
{

}



Stats & Partie::boucle_Jeu(Afficheur& TABS, RenderWindow& win,Parametre & param) {
    srand(time(NULL));
    //test jeu base
    bool continu = true;
    std::vector<Coup> listeCoups;
    Couleur joueur=BLANC;

    Coup coup;
    sf::Clock clock;
    //initialisation
    TABS.init_sprites();
    int victoire_b=0,victoire_n=0;
    float temps_B=0,temps_N=0;
    for (int i=0;i<1;++i)	
    {
        if (param.mode==1) GAME.init2();
        else GAME.init();
        int nombre_etape=0;
        
        do {
            //Affichage des pièces
            win.clear();
            TABS.dessiner(win,GAME);
            win.display();
            //jeutxt_aff(GAME);
            //cout<<"etape : "<<nombre_etape<<endl;
            clock.restart();
            if (joueur == BLANC) {
                if (param.blanc_bot) {
                    if (param.algo_blanc!=0) coup=alphabeta(GAME,param.prof_blanc);
                    else coup=min_max(GAME,param.prof_blanc);
                }
                else {            
                    //selection de la pièce
                    TABS.selection_coup_SFML(win,GAME, coup);
                }
                temps_B+=clock.restart().asSeconds();
            }
            else
            {	if (param.noir_bot) {
                    if (param.algo_noir!=0) coup=alphabeta(GAME,param.prof_noir);
                    else coup=min_max(GAME,param.prof_noir);
                }
                else { TABS.selection_coup_SFML(win,GAME, coup); }
                temps_N+=clock.restart().asSeconds();
            }
            nombre_etape++;
            //cout<<joueur<<'('<<coup.pos.x<<','<<coup.pos.y<<") vers ("<<coup.deplacement.x+coup.pos.x<<','<<coup.deplacement.y+coup.pos.y<<")"<<endl;
            //test du coup 

            if (GAME.jouerCoup(coup))
            {	
                joueur = (joueur == BLANC) ? NOIR : BLANC;
            }
            else // montre les possibilités
            { 	cout<<'('<<coup.pos.x<<','<<coup.pos.y<<") vers ("<<coup.deplacement.x+coup.pos.x<<','<<coup.deplacement.y+coup.pos.y<<')'<<" impossible"<<endl;	
                std::vector<Coup> possibilite=GAME.CalculEnsembleCoups();
                for (int i=0;i<possibilite.size();++i)
                {
                    cout<<'('<<possibilite.at(i).pos.x<<','<<possibilite.at(i).pos.y<<") vers ("<<possibilite.at(i).deplacement.x+possibilite.at(i).pos.x<<','<<possibilite.at(i).deplacement.y+possibilite.at(i).pos.y<<')'<<" prop"<<endl;			

                }
                continu=false;
            }
        } while (continu&&!GAME.partieTerminee()&&nombre_etape<250);
        if (GAME.vainqueur()==BLANC) victoire_b++;
        else if (GAME.vainqueur()==NOIR) victoire_n++;
        jeutxt_aff(GAME);
        cout<<"temps de calcul blanc : "<<temps_B<<endl;
        cout<<"temps de calcul noir  : "<<temps_N<<endl;
        cout<<"victoire blanc : "<<victoire_b<<endl;
        cout<<"victoire noir  : "<<victoire_n<<endl;
    }
}
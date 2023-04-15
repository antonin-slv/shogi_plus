#include "Bot.h"

MinMax min_max_final(ConfigurationJeu cj, int profondeur)
{	
	MinMax rslt(Coup(Vec2(-1,-1),Vec2(0,0)),cj.evaluer());
	if (profondeur>=0 && !cj.partieTerminee())
	{	//cout<<profondeur<<" ";
		std::vector<Coup> listeCoups=cj.CalculEnsembleCoups();
		ConfigurationJeu cjtemp;
		for (auto it = listeCoups.begin(); it != listeCoups.end(); ++it)
		{	cjtemp=cj;
			cjtemp.jouerCoup(*it);
			MinMax MMtemp=min_max_final(cjtemp, profondeur-1);
			MMtemp.score-=MMtemp.coup.deplacement.y/2;
			MMtemp.score+=(rand()%10-5)/3;
			if (cj.joueurSuivant()==BLANC)
			{	if (MMtemp.score<=rslt.score)
				{	rslt.score=MMtemp.score;
					rslt.coup=*it;
				}
			}
			else
			{	if (MMtemp.score>=rslt.score)
				{	rslt.score=MMtemp.score;
					rslt.coup=*it;
				}
			}
		}
	}
	return rslt;

}

float evaluateur_branche(ConfigurationJeu cj, int n)
{	//breakpoint de fin
	if (n<=0 || cj.partieTerminee()) return cj.evaluer();
   	else
   	{  	//calcul des coups possibles.
		std::vector<Coup> listeCoups=cj.CalculEnsembleCoups();
		//calcul des scores
		float score=cj.evaluer();
		ConfigurationJeu cjtemp;
		int i=0;
		for (auto it = listeCoups.begin(); it != listeCoups.end(); ++it)
		{  	
			//on copie le jeu
			cjtemp=cj;
			//on joue chaque coup
			cjtemp.jouerCoup(*it);
			float scoretemp=evaluateur_branche(cjtemp, n-1);
			scoretemp-=listeCoups.at(i++).deplacement.y;
			scoretemp+=(rand()%10-5)/3;
			//si le joueur suivant est le joueur max, on prend le max
			if (cj.joueurSuivant()!=BLANC)
			{	if (scoretemp>score) score=scoretemp;
			}
			//sinon on prend le min
			else
			{	if (scoretemp<score) score=scoretemp;
			}
		}
		return score;
	}
}
Coup min_max(ConfigurationJeu cj, int n)
{  	//calcul des coups possibles.
	std::vector<Coup> listeCoups=cj.CalculEnsembleCoups();
	Coup rslt;
	//calcul des scores
	float score=cj.evaluer();

	ConfigurationJeu cjtemp;

	bool premier=true;
	int i=0;
	for (auto it = listeCoups.begin(); it != listeCoups.end(); ++it)
	{  	
		//on copie le jeu
		cjtemp=cj;
		//on joue chaque coup
		cjtemp.jouerCoup(*it);
		float scoretemp=evaluateur_branche(cjtemp, n);

		scoretemp-=listeCoups.at(i).deplacement.y;
		scoretemp+=(rand()%10-5)/3;
		if(premier)
		{	premier=false;
			score=scoretemp;
		}
		//si le joueur actuel est blanc, on prend le max, sinon le min
		if (cj.joueurSuivant()==NOIR)
		{  	if (scoretemp>=score)
			{	score=scoretemp;
				rslt=*it;
			}
		}
		else
		{  	if (scoretemp<=score)
			{	score=scoretemp;
				rslt=*it;
			}
		}
		i++;
	}
	return rslt;
}

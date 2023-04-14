#include "ConfigJeu.h"
#include <cassert>

#include "Piece.h"

Coup::Coup(const Vec2& p, const Vec2& d)
{   
    pos=p;
    deplacement=d;
}
//privée
const Piece& ConfigurationJeu::getPiece(TypePiece type, Couleur col) const
{   if (col==BLANC)
    {   
        for (int i=0; i<=20; i++)
        {   
            if (m_piecesB[i].m_type==type)
            {   return m_piecesB[i];
            }
        }
    }
    else {   
        for (int i=0; i<=20; i++)
        {   
            if (m_piecesN[i].m_type==type)
            {   
                return m_piecesN[i];
            }
        }
    }

    return m_vide; // si on arrive ici, c'est qu'on a pas trouvÃ© la piÃ¨ce
}

//publique

bool ConfigurationJeu::coupValide(const Coup& coup) const
{   
    ////cout<<"on teste le coup : "<<coup.pos.x<<","<<coup.pos.y<<" vers "<<coup.pos.x+coup.deplacement.x<<","<<coup.pos.y+coup.deplacement.y<<endl;
    
    //vérification de sélection de la pièce
    if (coup.pos.x<0 || coup.pos.x>8 || coup.pos.y<0 || coup.pos.y>8) return false;
    
    IdPiece Id=getIdPiece(coup.pos);
    ////cout<<"id de la piece : "<<Id.type<<" "<<Id.coul<<" et j suivant :"<<m_joueurSuivant<<endl;
    if (Id.coul == m_joueurSuivant) return false;
    if (Id.type == VIDE) return false;

    //validation du déplacement
    Piece piece = getPiece(Id);
    ////cout<<"la pièce est ; type :"<<piece.m_type<<" ,col :"<<piece.m_couleur<<" ,en ("<<piece.m_pos.x<<','<<piece.m_pos.y<<")"<<endl;
    return piece.coupValide(*this, coup.deplacement);
}

std::vector<Coup> ConfigurationJeu::calculCoupsPossibles(const Vec2& pos) const
{  std::vector<Coup> coups;
    Coup coup= Coup(pos, Vec2(0,0));
    
    if (getIdPiece(pos).coul == m_joueurSuivant ||getIdPiece(pos).type == VIDE)
    {   //cout<<"mauvaise couleur"<<endl;
           cout<<"taille :"<<coups.size()<<endl;
           return coups;
    }
    for (int x=0; x<9; x++)
    {   for (int y=0; y<9; y++)
        {   coup.deplacement=Vec2(x,y)-coup.pos;
            if (coupValide(coup))
            {   coups.push_back(coup);
            }
        }
    }
    //cout<<"c_test";
    return coups;
}

bool ConfigurationJeu::jouerCoup(const Coup& coup)
{   if (coupValide(coup))
    {   int i=0,j=0;
        if (m_joueurSuivant==BLANC)//donc joueur noir
        {   // on cherche les numeros des pièces dans les tableaux de pièces
            //cout<<"NOIR  ";
            for (i=0; i<=20; i++)
            {   if (m_piecesN[i].m_pos==coup.pos) break;
            }
            for (j=0; j<=20; j++)
            {   if (m_piecesB[j].m_pos==coup.pos+coup.deplacement) break;
            }

            // on supprime la pièce prise si il y en a une
            if (m_damier[coup.pos.x+coup.deplacement.x][coup.pos.y+coup.deplacement.y].type!=VIDE)
            {   m_piecesB[j].prise();
            }
            // on déplace la pièce
            m_piecesN[i].deplacement(coup.deplacement);

            // on met à jour le damier
            m_damier[coup.pos.x+coup.deplacement.x][coup.pos.y+coup.deplacement.y]=IdPiece(m_piecesN[i].m_type,m_piecesN[i].m_couleur);
            m_damier[coup.pos.x][coup.pos.y]=IdPiece(VIDE, UNDEFINED);
        }
        else //joueur blanc
        {   //cout<<"joueur blanc joue";
            for (i=0; i<=20; i++)
            {   if (m_piecesB[i].m_pos==coup.pos) break;
            }
            for (j=0; j<=20; j++)
            {   if (m_piecesN[j].m_pos==coup.pos+coup.deplacement) break;
            }

            // on supprime la pièce prise si il y en a une
            if (m_damier[coup.pos.x+coup.deplacement.x][coup.pos.y+coup.deplacement.y].type!=VIDE)
            {   m_piecesN[j].prise();
            }

            // on déplace la pièce
            m_piecesB[i].deplacement(coup.deplacement);

            // on met à jour le damier
            m_damier[coup.pos.x+coup.deplacement.x][coup.pos.y+coup.deplacement.y]=IdPiece(m_piecesB[i].m_type,m_piecesB[i].m_couleur);
            m_damier[coup.pos.x][coup.pos.y]=IdPiece(VIDE, UNDEFINED);
        }
        // on change de joueur
        m_joueurSuivant = (m_joueurSuivant==BLANC) ? NOIR : BLANC;
        return true;
    }
    return false;
}


const Piece& ConfigurationJeu::getPiece(const Vec2& pos) const
{   for (int i=0; i<=20; i++)
    {   if (m_piecesB[i].m_pos==pos)
        {   return m_piecesB[i];
        }
    }
    for (int i=0; i<=20; i++)
    {   if (m_piecesN[i].m_pos==pos)
        {   return m_piecesN[i];
        }
    }
    return m_vide;
}

const Piece& ConfigurationJeu::getPiece(const IdPiece& id) const
{   return getPiece(id.type, id.coul);
}

const IdPiece& ConfigurationJeu::getIdPiece(const Vec2& pos) const
{   return m_damier[pos.x][pos.y];
}

ConfigurationJeu::ConfigurationJeu()
{   for (int x=0;x<9;x++)
    {   
        for (int y=0;y<9;y++)
        {   m_damier[x][y]=IdPiece();
        }
    }

    for (int i=0; i<=20; i++)
    {   
        m_piecesB[i]=Piece(TypePiece(i), BLANC, Vec2(0,0));
        m_piecesN[i]=Piece(TypePiece(i), NOIR, Vec2(0,0));
    }

    m_vide=Piece(VIDE, BLANC, Vec2(-1,-1));

    m_joueurSuivant=NOIR;
}

//renvoie vrai si un roi manque
bool ConfigurationJeu::partieTerminee() const
{
    if (getPiece(ROI, BLANC).enJeu()==false)
    {   //cout<<"no roi blanc"<<endl;
        return true;
    }
    else if(getPiece(ROI, NOIR).enJeu()==false)
    {   //cout<<"no roi noir"<<endl;
        return true;
    }
    return false;
}

//renvoie la couleur du joueur gagnant
Couleur ConfigurationJeu::vainqueur() const
{   if (getPiece(ROI, BLANC).enJeu())
    {   //cout<<"Roi blanc."<<endl;
        return BLANC;
    }
    else if (getPiece(ROI, NOIR).enJeu())
    {   //cout <<"Roi noir."<<endl;
        return NOIR;
    }
    //cout<<"Partie nulle."<<endl;
    return UNDEFINED;
}

float ConfigurationJeu::evaluer() const
{   float points=0;
    for (int i=0; i<=20; i++)
    {   if (m_piecesB[i].enJeu())
        {   points+=m_piecesB[i].m_importance;
        }
        if (m_piecesN[i].enJeu())
        {   points+=m_piecesN[i].m_importance;
        }
    }
    return points;
}

Couleur ConfigurationJeu::joueurSuivant() const
{   return m_joueurSuivant;
}

void ConfigurationJeu::init()
{   
    ConfigurationJeu();
    
    for (int i=0; i<9; i++)
    {   //init Pion NOIR
        m_piecesN[i]=Piece(TypePiece(i), NOIR, Vec2(i,2));
        m_damier[i][2]=IdPiece(TypePiece(i), NOIR);

        //init Pion BLANC
        m_piecesB[i]=Piece(TypePiece(i), BLANC, Vec2(i,9-1-2));
        m_damier[i][9-1-2]=IdPiece(TypePiece(i), BLANC);
    }

    //init TOUR et FOU
    m_piecesN[9]=Piece(TypePiece(9), NOIR, Vec2(7,1));
    m_damier[7][1]=IdPiece(TypePiece(9), NOIR);

    m_piecesN[10]=Piece(TypePiece(10), NOIR, Vec2(1,1));
    m_damier[1][1]=IdPiece(TypePiece(10), NOIR);

    m_piecesB[9]=Piece(TypePiece(9), BLANC, Vec2(1,7));
    m_damier[1][7]=IdPiece(TypePiece(9), BLANC);

    m_piecesB[10]=Piece(TypePiece(10), BLANC, Vec2(7,7));
    m_damier[7][7]=IdPiece(TypePiece(10), BLANC);

    //init General OR
    m_piecesN[11]=Piece(TypePiece(11), NOIR, Vec2(3,0));
    m_piecesN[12]=Piece(TypePiece(12), NOIR, Vec2(5,0));
    m_damier[3][0]=IdPiece(TypePiece(11), NOIR);
    m_damier[5][0]=IdPiece(TypePiece(12), NOIR);

    m_piecesB[11]=Piece(TypePiece(11), BLANC, Vec2(3,9-1));
    m_piecesB[12]=Piece(TypePiece(12), BLANC, Vec2(5,9-1));
    m_damier[3][9-1]=IdPiece(TypePiece(11), BLANC);
    m_damier[5][9-1]=IdPiece(TypePiece(12), BLANC);

    //init General ARGENT
    m_piecesN[13]=Piece(TypePiece(13), NOIR, Vec2(2,0));
    m_piecesN[14]=Piece(TypePiece(14), NOIR, Vec2(6,0));
    m_damier[2][0]=IdPiece(TypePiece(13), NOIR);
    m_damier[6][0]=IdPiece(TypePiece(14), NOIR);

    m_piecesB[13]=Piece(TypePiece(13), BLANC, Vec2(2,9-1));
    m_piecesB[14]=Piece(TypePiece(14), BLANC, Vec2(6,9-1));
    m_damier[2][9-1]=IdPiece(TypePiece(13), BLANC);
    m_damier[6][9-1]=IdPiece(TypePiece(14), BLANC);

    //init Cavalier
    m_piecesN[15]=Piece(TypePiece(15), NOIR, Vec2(1,0));
    m_piecesN[16]=Piece(TypePiece(16), NOIR, Vec2(7,0));
    m_damier[1][0]=IdPiece(TypePiece(15), NOIR);
    m_damier[7][0]=IdPiece(TypePiece(16), NOIR);

    m_piecesB[15]=Piece(TypePiece(15), BLANC, Vec2(1,9-1));
    m_piecesB[16]=Piece(TypePiece(16), BLANC, Vec2(7,9-1));
    m_damier[1][9-1]=IdPiece(TypePiece(15), BLANC);
    m_damier[7][9-1]=IdPiece(TypePiece(16), BLANC);

    //init LANCE
    m_piecesN[17]=Piece(TypePiece(17), NOIR, Vec2(0,0));
    m_piecesN[18]=Piece(TypePiece(18), NOIR, Vec2(8,0));
    m_damier[0][0]=IdPiece(TypePiece(17), NOIR);
    m_damier[8][0]=IdPiece(TypePiece(18), NOIR);

    m_piecesB[17]=Piece(TypePiece(17), BLANC, Vec2(0,9-1));
    m_piecesB[18]=Piece(TypePiece(18), BLANC, Vec2(8,9-1));
    m_damier[0][9-1]=IdPiece(TypePiece(17), BLANC);
    m_damier[8][9-1]=IdPiece(TypePiece(18), BLANC);

    //init ROI
    m_piecesN[19]=Piece(TypePiece(19), NOIR, Vec2(4,0));
    m_damier[4][0]=IdPiece(TypePiece(19), NOIR);

    m_piecesB[19]=Piece(TypePiece(19), BLANC, Vec2(4,9-1));
    m_damier[4][9-1]=IdPiece(TypePiece(19), BLANC);
}

bool ConfigurationJeu::testRegression()
{   Vec2 v1(1,2);
	Vec2 v2(3,4);
	v1 += v2;
	//cout << v1.x << " " << v1.y << endl;
	

	Piece P1(ROI, BLANC, Vec2(1,2));
	Piece P2(LANCE1, NOIR, Vec2(3,4));
	
	ofstream f("data/test.txt");
	//cout<<P1.m_couleur<<endl;
	P1.ecriture(f);
	f.close();

	ifstream g("data/test.txt");
	P2.lecture(g);
	//cout<<P2.m_couleur<<endl;
	g.close();
    return true;
}
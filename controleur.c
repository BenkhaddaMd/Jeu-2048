#include "graphics.h"
#define LONGUEUR 700
#define HAUTEUR 400

enum DIRECTION{ HAUTE, BAS, DROITE, GAUCHE};
typedef enum DIRECTION DIRECTION;

typedef struct indice{int x,y;} INDICE;

int plateau[8][8];

/////////// MODELE ////////////

int calcule_score()
{
    int score, i, j;

    score = 0;
    for ( i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
            score += plateau[i][j];
        
    }
    return score;
}

void ajoute_aleatoire(int nbEssais, BOOL estDifficile)
{
    int i ,j, k, nbFusionVertical, nbFusionHorizontal;

    nbFusionVertical = 0;
    nbFusionHorizontal = 0;
    i = alea_int(8);
    j = alea_int(8);
    
    if(plateau[i][j] != 0)
        ajoute_aleatoire(0, estDifficile);
    else if(estDifficile)
    {
        plateau[i][j] = 2;    

        k = j+1;
        while(k < 8 && plateau[i][k] == 0)
            k++;
        if(plateau[i][j] == plateau[i][k] && k!=8)
            nbFusionVertical += 1;

        k = j+1;
        while(k < 8 && plateau[k][i] == 0)
            k++;
        if(plateau[j][i] == plateau[k][i] && k!=8)
            nbFusionHorizontal += 1;
        
        if((nbFusionHorizontal != 0 || nbFusionVertical != 0) && nbEssais < 10)
        {
            plateau[i][j] = 0;
            ajoute_aleatoire(nbEssais+1, estDifficile); 
        }
    }
    else
        plateau[i][j] = 2;
}

void init_plateau(BOOL estDifficile)
{
    int i, j;

    for(i = 0; i < 8; i++)
    {   
        for ( j = 0; j < 8; j++)
            plateau[i][j] = 0;
    }

    ajoute_aleatoire(0, estDifficile);
    ajoute_aleatoire(0, estDifficile);
}

void ecrase_case(INDICE src, INDICE dest)
{
    int valeur;

    valeur = plateau[src.x][src.y];
    plateau[src.x][src.y] = 0;
    plateau[dest.x][dest.y] = valeur;
}

void fusion_deux_cases(INDICE src, INDICE dest)
{
    plateau[dest.x][dest.y] += plateau[src.x][src.y];
    plateau[src.x][src.y] = 0;
}

BOOL applique_fusion_simple(int dir, BOOL estTotal)
{
    int i, j, k, n;
    BOOL estFusion;
    INDICE p1, p2;
	enum DIRECTION{ HAUTE, BAS, DROITE, GAUCHE};

    estFusion = FALSE;
    if(estTotal)    n = 64;
    else            n = 8;
    if(dir == GAUCHE)
    {
        for(i = 0; i < 8; i++)
        {
            for(j = 0; j < n; j++){
                if(plateau[i][j%8] != 0)
                {
                    for(k = j%8-1; k >= 0; k--)
                    {
                        if(plateau[i][k] == 0)
                            continue;
                        else if(plateau[i][k] == plateau[i][j%8])
                        {
                            p1.x = i;   p1.y = j%8;
                            p2.x = i;   p2.y = k;
                            fusion_deux_cases(p1, p2);
                            estFusion = TRUE;
                        }
                        else
                            break;
                    }                    
                }
            }
        }
    }
    else if(dir == DROITE)
    {
        for(i = 0; i < 8; i++)
        {
            for(j = n-1; j >= 0; j--){
                if(plateau[i][j%8] != 0)
                {
                    for(k = j%8+1; k < 8; k++)
                    {
                        if(plateau[i][k] == 0)
                            continue;
                        else if(plateau[i][k] == plateau[i][j%8])
                        {
                            p1.x = i;   p1.y = j%8;
                            p2.x = i;   p2.y = k;
                            fusion_deux_cases(p1, p2);
                            estFusion = TRUE;
                        }
                        else
                            break;
                    }
                }
            }
        }
    }
    else if(dir == HAUTE)
    {
        for(i = 0; i < 8; i++)
        {
            for(j = n-1; j >= 0; j--){
                if(plateau[j%8][i] != 0)
                {
                    for(k = j%8+1; k < 8; k++)
                    {
                        if(plateau[k][i] == 0)
                            continue;
                        else if(plateau[k][i] == plateau[j%8][i])
                        {
                            p1.x = j%8;   p1.y = i;
                            p2.x = k;   p2.y = i;
                            fusion_deux_cases(p1, p2);
                            estFusion = TRUE;
                        }
                        else
                            break;
                    }
                }
            }
        }
    }
    else
    {
        for(i = 0; i < 8; i++)
        {
            for(j = 0; j < n; j++){
                if(plateau[j%8][i] != 0)
                {
                    for(k = j%8-1; k >= 0; k--)
                    {
                        if(plateau[k][i] == 0)
                            continue;
                        else if(plateau[k][i] == plateau[j%8][i])
                        {
                            p1.x = j%8;   p1.y = i;
                            p2.x = k;   p2.y = i;
                            fusion_deux_cases(p1, p2);
                            estFusion = TRUE;
                        }
                        else
                            break;
                    }
                }
            }
        }
    }

    return estFusion;
}

void deplace_brique_bas(BOOL estDifficile, BOOL avecAjoute, BOOL avecFusionTotal)
{
    int i, j, k;
    BOOL estDeplace;
    INDICE p1, p2;

    estDeplace = FALSE;

    estDeplace = applique_fusion_simple(BAS, avecFusionTotal);

    for(i = 0; i < 8; i++)
        {
            for(j = 0; j < 8; j++){
                if(plateau[j][i] != 0)
                {
                    k = j-1;
                    while(k >= 0 && plateau[k][i] == 0 )
                        k--;
                    k++;

                    p1.x = j;   p1.y = i;
                    p2.x = k;   p2.y = i;
                    ecrase_case(p1, p2);
                    if(j != k)
                        estDeplace = TRUE;
                }
            }
        }
    if(estDeplace && avecAjoute)
        ajoute_aleatoire(0, estDifficile);
}

void deplace_brique_droite(BOOL estDifficile, BOOL avecAjoute, BOOL avecFusionTotal)
{
    int i, j, k;
    BOOL estDeplace;
    INDICE p1, p2;

    estDeplace = FALSE;

    estDeplace = applique_fusion_simple(DROITE, avecFusionTotal);

    for(i = 0; i < 8; i++)
        {
            for(j = 7; j >= 0; j--){
                if(plateau[i][j] != 0)
                {
                    k = j+1;
                    while( k < 8 && plateau[i][k] == 0)
                        k++;
                    k--;
                    
                    p1.x = i;   p1.y = j;
                    p2.x = i;   p2.y = k;
                    ecrase_case(p1, p2);
                    if(j != k)
                        estDeplace = TRUE;
                }
            }
        }
    if(estDeplace && avecAjoute)
        ajoute_aleatoire(0, estDifficile);
}

void deplace_brique_gauche(BOOL estDifficile, BOOL avecAjoute, BOOL avecFusionTotal)
{
    int i, j, k;
    BOOL estDeplace;
    INDICE p1, p2;

    estDeplace = FALSE;

    estDeplace = applique_fusion_simple(GAUCHE, avecFusionTotal);

        for(i = 0; i < 8; i++)
        {
            for(j = 0; j < 8; j++){
                if(plateau[i][j] != 0)
                {
                    k = j-1;
                    while(k >= 0 && plateau[i][k] == 0)
                        k--;
                    k++;
                    
                    p1.x = i;   p1.y = j;
                    p2.x = i;   p2.y = k;
                    ecrase_case(p1, p2);
                    if(j != k)
                        estDeplace = TRUE;
                }
            }
        }
    if(estDeplace && avecAjoute)
        ajoute_aleatoire(0, estDifficile);
}

void deplace_brique_haute(BOOL estDifficile, BOOL  avecAjoute, BOOL avecFusionTotal)
{
    int i, j, k;
    BOOL estDeplace;
    INDICE p1, p2;

    estDeplace = FALSE;

    estDeplace = applique_fusion_simple(HAUTE, avecFusionTotal);

    for(i = 0; i < 8; i++)
        {
            for(j = 7; j >= 0; j--){
                if(plateau[j][i] != 0)
                {
                    k = j+1;
                    while( k < 8 && plateau[k][i] == 0)
                        k++;
                    k--;
                    
                    p1.x = j;   p1.y = i;
                    p2.x = k;   p2.y = i;
                    ecrase_case(p1, p2);
                    if(j != k)
                        estDeplace = TRUE;
                }
            }
        }
    if(estDeplace && avecAjoute)
        ajoute_aleatoire(0, estDifficile);
}

int nombre_fusion()
{
    int i, j, k, nbFusionVertical, nbFusionHorizontal;
    
    nbFusionVertical = 0;
    nbFusionHorizontal = 0;
    for(i = 0; i < 8; i++)
    {
        for(j = 0; j < 7; j++)
        {
            if(plateau[i][j] != 0)
            {
                k = j+1;
                while(k < 8 && plateau[i][k] == 0)
                    k++;
                if(k == 8)
                    continue;
                else if(plateau[i][j] == plateau[i][k])
                {
                    nbFusionVertical += 1;
                    j = k+1;
                }
            }

        }
    }
    
    for(i = 0; i < 8; i++)
    {
        for(j = 0; j < 7; j++)
        {
            if(plateau[j][i] != 0)
            {
                k = j+1;
                while(k < 8 && plateau[k][i] == 0)
                    k++;
                if(k == 8)
                    continue;
                else if(plateau[j][i] == plateau[k][i])
                {
                    nbFusionHorizontal += 1;
                    j = k+1;
                }
            }

        }
    }
    if(nbFusionHorizontal >= nbFusionVertical)   return nbFusionHorizontal;
    else                                         return nbFusionVertical;
    return 0;
}

int aide_direction()
{
    int i, j, k, nbFusionGauche, nbFusionDroite,nbFusionBas, nbFusionHaute;
    int plateauBackup[8][8];

    nbFusionDroite = 0;
    nbFusionGauche = 0;
    nbFusionBas = 0;
    nbFusionHaute = 0;
    for ( i = 0; i < 8; i++)
    {
        for ( j = 0; j < 8; j++)
            plateauBackup[i][j] = plateau[i][j];
    }
    
    for(i = 0; i < 8; i++)
    {
        for(j = 0; j < 7; j++)
        {
            if(plateau[i][j] != 0)
            {
                k = j+1;
                while(k < 8 && plateau[i][k] == 0)
                    k++;
                if(k == 8)
                    continue;
                else if(plateau[i][j] == plateau[i][k])
                {
                    nbFusionDroite += 1;
                    j = k+1;
                }
            }

        }
    }

    for(i = 0; i < 8; i++)
    {
        for(j = 7; j >= 0 ; j--)
        {
            if(plateau[i][j] != 0)
            {
                k = j-1;
                while(k >= 8 && plateau[i][k] == 0)
                    k--;
                if(k == -1)
                    continue;
                else if(plateau[i][j] == plateau[i][k])
                {
                    nbFusionGauche += 1;
                    j = k-1;
                }
            }

        }
    }
    
    for(i = 0; i < 8; i++)
    {
        for(j = 0; j < 7; j++)
        {
            if(plateau[j][i] != 0)
            {
                k = j+1;
                while(k < 8 && plateau[k][i] == 0)
                    k++;
                if(k == 8)
                    continue;
                else if(plateau[j][i] == plateau[k][i])
                {
                    nbFusionBas += 1;
                    j = k+1;
                }
            }

        }
    }

    for(i = 0; i < 8; i++)
    {
        for(j = 7; j >= 0; j--)
        {
            if(plateau[j][i] != 0)
            {
                k = j-1;
                while(k >= 0 && plateau[k][i] == 0)
                    k--;
                if(k == -1)
                    continue;
                else if(plateau[j][i] == plateau[k][i])
                {
                    nbFusionHaute += 1;
                    j = k-1;
                }
            }

        }
    }

    for ( i = 0; i < 8; i++)
    {
        for ( j = 0; j < 8; j++)
            plateau[i][j] = plateauBackup[i][j];
    }

    if(nbFusionDroite >= nbFusionGauche && nbFusionDroite >= nbFusionHaute && nbFusionDroite >= nbFusionBas)
        return 2;
    else if(nbFusionGauche >= nbFusionDroite && nbFusionGauche >= nbFusionHaute && nbFusionGauche >= nbFusionBas)
        return 3;
    else if(nbFusionHaute >= nbFusionDroite && nbFusionHaute >= nbFusionGauche && nbFusionHaute >= nbFusionBas)
        return 0;
    else
        return 1;
    return -1;
}

BOOL selecte_boutton(INDICE p1, INDICE p2, INDICE pSelectionne)
{
    if(pSelectionne.x >= p1.x && pSelectionne.x <= p2.x && pSelectionne.y <= p1.y && pSelectionne.y >= p2.y)
        return TRUE;
    return FALSE;
}

int determine_direction(INDICE pSelectionne)
{
    INDICE p1, p2;

    p1.x = 515;	p1.y = 200;
	p2.x = 585;	p2.y = 130;
    if(selecte_boutton(p1, p2, pSelectionne))
        return 0;

    p1.x = 515;	p1.y = 120;
	p2.x = 585;	p2.y = 50;
    if(selecte_boutton(p1, p2, pSelectionne))
        return 1;

    p1.x = 595;	p1.y = 200;
	p2.x = 650;	p2.y = 50;
    if(selecte_boutton(p1, p2, pSelectionne))
        return 2;
    
    p1.x = 450;	p1.y = 200;
	p2.x = 505;	p2.y = 50;
    if(selecte_boutton(p1, p2, pSelectionne))
        return 3;

    p1.x = 590; p1.y = 280;
    p2.x = 650; p2.y = 230;
    if(selecte_boutton(p1, p2, pSelectionne))
        return 4;
    return -1;
}

BOOL est_remplie()
{
    int i, j;

    for ( i = 0; i < 8; i++)
    {
        for ( j = 0; j < 8; j++)
        {
            if(plateau[i][j] == 0)
                return 0;
        }
    }
    return 1;
}

int etat_jeu(int scoreDiminue)
{
    if(est_remplie() && nombre_fusion() == 0)
        return 0;
    else if(calcule_score(scoreDiminue) == 2048)
        return 1;
    else
        return 2;
}

int determine_option(INDICE pSelectionne)
{
    INDICE p1, p2;

    p1.x = 280; p1.y = 250;
    p2.x = 310; p2.y = 220;
    if(selecte_boutton(p1, p2, pSelectionne))
        return 3;

    p1.x = 430; p1.y = 250;
    p2.x = 460; p2.y = 220;
    if(selecte_boutton(p1, p2, pSelectionne))
        return 4;

    p1.x = 400; p1.y = 210;
    p2.x = 440; p2.y = 170;
    if(selecte_boutton(p1, p2, pSelectionne))
        return 2;

    p1.x = 400; p1.y = 160;
    p2.x = 440; p2.y = 120;
    if(selecte_boutton(p1, p2, pSelectionne))
        return 1;

    p1.x = 400; p1.y = 110;
    p2.x = 440; p2.y = 70;
    if(selecte_boutton(p1, p2, pSelectionne))
        return 0;

    p1.x = 250; p1.y = 50;
    p2.x = 450; p2.y = 20;
    if(selecte_boutton(p1, p2, pSelectionne))
        return 5;

    return -1;
}

int fin_jeu_option(INDICE pSelectionne)
{
    INDICE p1, p2;
    
    p1.x = 250; p1.y = 50;
    p2.x = 340; p2.y = 20;
    if(selecte_boutton(p1, p2, pSelectionne))
        return 0;
   
    p1.x = 360; p1.y = 50;
    p2.x = 450; p2.y = 20;
    if(selecte_boutton(p1, p2, pSelectionne))
        return 1;
    return -1;
}

//////////// VUE //////////////

void colore_case(POINT p, COULEUR couleur)
{
    POINT p1, p2;
    p1.x = p.x + 2;    p1.y = p.y + 2;
    p2.x = p.x + 47;    p2.y = p.y + 47;
    draw_fill_rectangle(p1, p2, couleur);
}

void efface_case(POINT p)
{
	colore_case(p, argent);
}

void affiche_case(int nombre, POINT p)
{
	COULEUR couleur;
	POINT pTexte;
	int i,j;
	double colors[11] = {0x0000FF, 0x000080, 0x00FF00, 0x00FFFF, 0xFF00FF, 0x808080, 0xFFFF00, 0x800000, 0x008000, 0x800080, 0xD2691E};
	
	couleur = colors[0];
	pTexte.x = p.x + 20;
	pTexte.y = p.y + 30;
	j = nombre; i = 0;

    if( nombre > 128)
    {
        pTexte.x -= 5;
    }

	while(j != 1)
	{
		j = j / 2;
        i++;
	}
    i--;
	couleur = colors[i];

	colore_case(p, couleur);
	aff_int(nombre, 12, pTexte, blanc);
}

void dessine_background(COULEUR color)
{
    POINT p1, p2;
    p1.x = 0;	p1.y = 0;
	p2.x = LONGUEUR;	p2.y = HAUTEUR;
	draw_fill_rectangle(p1, p2, color);
}

void dessine_plateau()
{
	POINT p1;
	int i, j;

	for(i = 0; i < 8; i++)
	{
		for(j = 0; j < 8; j++)
		{
			p1.y = 50*i;	p1.x = 50*j;
			if(plateau[i][j] != 0)
				affiche_case(plateau[i][j], p1);
			else
				efface_case(p1);

		}
	}
}

void dessine_score(int scoreDiminue)
{
	POINT p1, p2;
	int score;

	p1.x = 450;	p1.y = 350;
	p2.x = 650;	p2.y = 300;
	draw_fill_rectangle(p1, p2, blanc);
	p1.x += 45;	
	score = calcule_score() - scoreDiminue;
    if(calcule_score() == 4)
    {
        score = 0;
    }
	aff_int(score, 35, p1, 0x9C551A);
    p1.x -= 20;	p1.y += 35;
    aff_pol("Votre Score", 25, p1, blanc);

}

void dessine_aide(BOOL avecAide)
{
	POINT p1, p2;

    p1.x = 590; p1.y = 280;
    p2.x = 650; p2.y = 230;
    draw_fill_rectangle(p1, p2, blanc);
    if(avecAide)
    {
        p1.x += 10; p1.y -= 10;
        p2.x -= 10; p2.y += 10;
        draw_fill_rectangle(p1, p2, vert); 
    } 
    p1.x = 490; p1.y = 265;
    aff_pol("-> Aide :", 15, p1, blanc);


}

void dessine_fleches()
{
    POINT p1, p2;

    p1.x = 450;	p1.y = 200;
	p2.x = 505;	p2.y = 50;
	draw_fill_rectangle(p1, p2, blanc);
    draw_rectangle(p1, p2, gris);
    p1.x += 10;	p1.y -= 40;
	aff_pol("<", 50, p1, 0x9C551A);
    
    p1.x = 595;	p1.y = 200;
	p2.x = 650;	p2.y = 50;
	draw_fill_rectangle(p1, p2, blanc);
    draw_rectangle(p1, p2, gris);
    p1.x += 10;	p1.y -= 40;
    aff_pol(">", 50, p1, 0x9C551A);

    p1.x = 515;	p1.y = 200;
	p2.x = 585;	p2.y = 130;
	draw_fill_rectangle(p1, p2, blanc);
    draw_rectangle(p1, p2, gris);
	p1.x += 15;	p1.y -= 10;
	aff_pol("^", 50, p1, 0x9C551A);

    p1.x = 515;	p1.y = 120;
	p2.x = 585;	p2.y = 50;
	draw_fill_rectangle(p1, p2, blanc);
    draw_rectangle(p1, p2, gris);
    p1.x += 23;	p1.y -= 10;
	aff_pol("v", 45, p1, 0x9C551A);
}

void flash_fleche_haute()
{
    POINT p1, p2;

    p1.x = 515;	p1.y = 200;
	p2.x = 585;	p2.y = 130;
	draw_fill_rectangle(p1, p2, vert);
    draw_rectangle(p1, p2, gris);
	p1.x += 15;	p1.y -= 10;
	aff_pol("^", 50, p1, 0x9C551A);
}

void flash_fleche_droite()
{
    POINT p1, p2;

    p1.x = 595;	p1.y = 200;
	p2.x = 650;	p2.y = 50;
	draw_fill_rectangle(p1, p2, vert);
    draw_rectangle(p1, p2, gris);
    p1.x += 10;	p1.y -= 40;
    aff_pol(">", 50, p1, 0x9C551A);
}

void flash_fleche_gauche()
{
    POINT p1, p2;

    p1.x = 450;	p1.y = 200;
	p2.x = 505;	p2.y = 50;
	draw_fill_rectangle(p1, p2, vert);
    draw_rectangle(p1, p2, gris);
    p1.x += 10;	p1.y -= 40;
	aff_pol("<", 50, p1, 0x9C551A);
}

void flash_fleche_bas()
{
    POINT p1, p2;

    p1.x = 515;	p1.y = 120;
	p2.x = 585;	p2.y = 50;
	draw_fill_rectangle(p1, p2, vert);
    draw_rectangle(p1, p2, gris);
    p1.x += 23;	p1.y -= 10;
	aff_pol("v", 45, p1, 0x9C551A);
}

void dessine_graphique_1(int scoreDiminue, BOOL avecAide)
{
    dessine_background(0xE3CBB8);
	dessine_plateau();
	dessine_score(scoreDiminue);
    dessine_aide(avecAide);
    dessine_fleches();
}

void dessine_graphique_2(int scoreDiminue, BOOL avecAide)
{
    dessine_background(noir);
	dessine_plateau();
	dessine_score(scoreDiminue);
    dessine_aide(avecAide);
    dessine_fleches();
}

void affiche_menu_accueil(BOOL estGraphique, BOOL avecFusionTotal, BOOL avecAide, BOOL estDifficile)
{
    POINT p1, p2;

    p1.x = 250; p1.y = 400;
    aff_pol("2048", 74, p1, blanc);

    p1.x = 260; p1.y = 300;
    aff_pol("-> Type graphique :", 15, p1, noir);

    p1.x = 280; p1.y = 250;
    p2.x = 310; p2.y = 220;
    draw_fill_rectangle(p1, p2, blanc);
    if(estGraphique)
    {
        p1.x += 10; p1.y -= 10;
        p2.x -= 10; p2.y += 10;
        draw_fill_rectangle(p1, p2, vert); 
    }     
    p1.x = 260; p1.y = 242;
    aff_pol("1", 12, p1, noir);

    p1.x = 430; p1.y = 250;
    p2.x = 460; p2.y = 220;
    draw_fill_rectangle(p1, p2, blanc);
    if(!estGraphique)
    {
        p1.x += 10; p1.y -= 10;
        p2.x -= 10; p2.y += 10;
        draw_fill_rectangle(p1, p2, vert); 
    }     
    p1.x = 410; p1.y = 242;
    aff_pol("2", 12, p1, noir);

    p1.x = 260; p1.y = 200;
    aff_pol("-> Fusion totale :", 15, p1, noir);
    p1.x = 400; p1.y = 210;
    p2.x = 440; p2.y = 170;
    draw_fill_rectangle(p1, p2, blanc);
    if(avecFusionTotal)
    {
        p1.x += 10; p1.y -= 10;
        p2.x -= 10; p2.y += 10;
        draw_fill_rectangle(p1, p2, vert); 
    }     

    p1.x = 260; p1.y = 150;
    aff_pol("-> Aide :", 15, p1, noir);
    p1.x = 400; p1.y = 160;
    p2.x = 440; p2.y = 120;
    draw_fill_rectangle(p1, p2, blanc);
    if(avecAide)
    {
        p1.x += 10; p1.y -= 10;
        p2.x -= 10; p2.y += 10;
        draw_fill_rectangle(p1, p2, vert); 
    } 

    p1.x = 260; p1.y = 100;
    aff_pol("-> Mode difficile :", 15, p1, noir);
    p1.x = 400; p1.y = 110;
    p2.x = 440; p2.y = 70;
    draw_fill_rectangle(p1, p2, blanc);
    if(estDifficile)
    {
        p1.x += 10; p1.y -= 10;
        p2.x -= 10; p2.y += 10;
        draw_fill_rectangle(p1, p2, vert); 
    } 

    p1.x = 250; p1.y = 50;
    p2.x = 450; p2.y = 20;
    draw_fill_rectangle(p1, p2, blanc);
    draw_rectangle(p1, p2, noir);
    p1.x += 65; p1.y -= 2;
    aff_pol("JOUER", 20, p1, noir);
}

void dessine_fin_jeu(BOOL estGagne)
{
    POINT p1, p2;

    dessine_background(0xE3CBB8);

    p1.x = 210; p1.y = 350;
    aff_pol("FIN DU JEU", 50, p1, noir);
    p1.x -= 0; p1.y -= 65;
    if(estGagne)
        aff_pol("Vous avez gagne ! ", 16, p1, noir);
    else    
        aff_pol("Vous avez perdu ", 16, p1, noir);
    p1.x -= 0; p1.y -= 40;
    if(estGagne)
        aff_pol("Vous avez attient la case 2048", 16, p1, noir);
    else
        aff_pol("Aucune case n'est libre sur le plateau", 16, p1, noir);
    p1.x -= 0; p1.y -= 45;
    if(estGagne)
        aff_pol("Bien Joue", 16, p1, noir);
    else
        aff_pol("Plus aucune fusion n'est possible", 16, p1, noir);
    p1.x -= 0; p1.y -= 35;
    aff_pol("Votre score est : ", 16, p1, noir);
    p1.x += 150;
    aff_int(calcule_score(), 16, p1, noir);

    p1.x = 250; p1.y = 50;
    p2.x = 340; p2.y = 20;
    draw_fill_rectangle(p1, p2, blanc);
    p1.x += 7; p1.y -= 2;
    aff_pol("REJOUER", 17, p1, noir);

    p1.x = 360; p1.y = 50;
    p2.x = 450; p2.y = 20;
    draw_fill_rectangle(p1, p2, blanc);
    p1.x += 7; p1.y -= 2;
    aff_pol("SORTIR", 17, p1, noir);
}

int main()
{
    int dir, aide, scoreDiminue;
    POINT p;
    INDICE pSelectionne;
    BOOL estDifficile, avecFusionTotal, estGraphique1, avecAide, estGagne, rejoue;

    scoreDiminue = 0; aide = -1; estDifficile = FALSE;   avecFusionTotal = FALSE;    avecAide = FALSE;   rejoue = FALSE; estGraphique1 = FALSE;

    init_graphics(LONGUEUR,HAUTEUR);
	
    while(1)
    {
        if(!rejoue)
        {
            dessine_background(0xE3CBB8);
            affiche_menu_accueil(estGraphique1, avecFusionTotal, avecAide, estDifficile);
            while (1)
            {
                int option;
                p = wait_clic();
                pSelectionne.x = p.x;   pSelectionne.y = p.y;
                option = determine_option(pSelectionne);
                if(option == 0)
                    estDifficile = !estDifficile;
                else if(option == 1)
                    avecAide = !avecAide;
                else if(option == 2)
                    avecFusionTotal = !avecFusionTotal;
                else if(option == 3)
                    estGraphique1 = TRUE;
                else if(option == 4)
                    estGraphique1 = FALSE;
                else if(option == 5)
                    break;
                affiche_menu_accueil(estGraphique1, avecFusionTotal, avecAide, estDifficile);
            }
        }
        init_plateau(estDifficile);
        if(estGraphique1)
            dessine_graphique_1(scoreDiminue, avecAide);
        else
            dessine_graphique_2(scoreDiminue, avecAide);

        while(true)
        {
            if(etat_jeu(scoreDiminue) == 0 || etat_jeu(scoreDiminue) == 1)
            {
                estGagne = etat_jeu(scoreDiminue);
                break;
            }

            if(avecAide)
            {
                aide = aide_direction();
                if(aide == HAUTE)
                    flash_fleche_haute();
                else if(aide == BAS)
                    flash_fleche_bas();
                else if(aide == GAUCHE)
                    flash_fleche_gauche();
                else if(aide == DROITE)
                    flash_fleche_droite();
            }

            p = wait_clic();
            dessine_fleches();
            pSelectionne.x = p.x;   pSelectionne.y = p.y;
            dir = determine_direction(pSelectionne);
            if(dir == 4)
            {
                avecAide = !avecAide;
                dessine_aide(avecAide);
            }
            if(aide == dir && avecAide)
                scoreDiminue++;
            switch (dir)
            {
            case HAUTE:
                deplace_brique_haute(estDifficile, TRUE, avecFusionTotal);
                break;
            case BAS:
                deplace_brique_bas(estDifficile, TRUE, avecFusionTotal);
                break;
            case DROITE:
                deplace_brique_droite(estDifficile, TRUE, avecFusionTotal);
                break;
            case GAUCHE:
                deplace_brique_gauche(estDifficile, TRUE, avecFusionTotal);
                break;
            }

            if(dir != -1)
            {
                dessine_plateau();
                dessine_score(scoreDiminue);
            }
        }
        dessine_fin_jeu(estGagne);
        while(1)
        {
            int option;
            p = wait_clic();
            pSelectionne.x = p.x;   pSelectionne.y = p.y;
            option = fin_jeu_option(pSelectionne);
            if(option == 0)  
            {
                rejoue = true;
                break;
            }
            else if (option == 1)
            {
                rejoue = false;
                break;
            }
        }
    }
    
    wait_escape();
    
    return 0;
}

#include "graphics.h"
#define LONGUEUR 700
#define HAUTEUR 400

int plateau[8][8];

/////////// MODELE ////////////

void ajoute_aleatoire()
{
    int i ,j;

    i = alea_int(8);
    j = alea_int(8);

    if(plateau[i][j] != 0)
        ajoute_aleatoire();
    else
        plateau[i][j] = 2;
}

void init_plateau()
{
    int i, j;

    for(i = 0; i < 8; i++)
    {   
        for ( j = 0; j < 8; j++)
            plateau[i][j] = 0;
    }

    ajoute_aleatoire();
    ajoute_aleatoire();
}

// Est ce que c'est acceptable d'utiliser la structure POINT 
// juste pour passer 2 args a la place de 4 args ?
void ecrase_case(POINT p1, POINT p2)
{
    int valeur;

    valeur = plateau[p1.x][p1.y];
    plateau[p1.x][p1.y] = 0;
    plateau[p2.x][p2.y] = valeur;
}

void fusion_deux_cases(POINT p1, POINT p2)
{
    plateau[p2.x][p2.y] += plateau[p1.x][p1.y];
    plateau[p1.x][p1.y] = 0;
}

void applique_fusion(int dir)
{
    int i, j, k;
    POINT p1, p2;
	enum DIRECTION{ HAUTE, BAS, DROITE, GAUCHE};

    if(dir == GAUCHE)
    {
        for(i = 0; i < 8; i++)
        {
            for(j = 0; j < 8; j++){
                if(plateau[i][j] != 0)
                {
                    for(k = j-1; k >= 0; k--)
                    {
                        if(plateau[i][k] == 0)
                            continue;
                        else if(plateau[i][k] == plateau[i][j])
                        {
                            p1.x = i;   p1.y = j;
                            p2.x = i;   p2.y = k;
                            fusion_deux_cases(p1, p2);
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
            for(j = 7; j >= 0; j--){
                if(plateau[i][j] != 0)
                {
                    for(k = j+1; k < 8; k++)
                    {
                        if(plateau[i][k] == 0)
                            continue;
                        else if(plateau[i][k] == plateau[i][j])
                        {
                            p1.x = i;   p1.y = j;
                            p2.x = i;   p2.y = k;
                            fusion_deux_cases(p1, p2);
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
            for(j = 7; j >= 0; j--){
                if(plateau[j][i] != 0)
                {
                    for(k = j+1; k < 8; k++)
                    {
                        if(plateau[k][i] == 0)
                            continue;
                        else if(plateau[k][i] == plateau[j][i])
                        {
                            p1.x = j;   p1.y = i;
                            p2.x = k;   p2.y = i;
                            fusion_deux_cases(p1, p2);
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
            for(j = 0; j < 8; j++){
                if(plateau[j][i] != 0)
                {
                    for(k = j-1; k >= 0; k--)
                    {
                        if(plateau[k][i] == 0)
                            continue;
                        else if(plateau[k][i] == plateau[j][i])
                        {
                            p1.x = j;   p1.y = i;
                            p2.x = k;   p2.y = i;
                            fusion_deux_cases(p1, p2);
                        }
                        else
                            break;
                    }
                }
            }
        }
    }

}

void deplace_brique(int dir)
{
    int i, j, k;
    BOOL est_deplace;
    POINT p1, p2;
	enum DIRECTION{ HAUTE, BAS, DROITE, GAUCHE};

    est_deplace = FALSE;

    applique_fusion(dir);
    if(dir == GAUCHE)
    {
        for(i = 0; i < 8; i++)
        {
            for(j = 0; j < 8; j++){
                if(plateau[i][j] != 0)
                {
                    for(k = j-1; k >= 0; k--)
                    {
                        if(plateau[i][k] != 0)
                            break;
                    }
                    k++;
                    
                    p1.x = i;   p1.y = j;
                    p2.x = i;   p2.y = k;
                    ecrase_case(p1, p2);
                    if(j != k)
                        est_deplace = TRUE;
                }
            }
        }
    }
    else if(dir == DROITE)
    {
        for(i = 0; i < 8; i++)
        {
            for(j = 7; j >= 0; j--){
                if(plateau[i][j] != 0)
                {
                    for(k = j+1; k < 8; k++)
                    {
                        if(plateau[i][k] != 0)
                            break;
                    }
                    k--;
                    
                    p1.x = i;   p1.y = j;
                    p2.x = i;   p2.y = k;
                    ecrase_case(p1, p2);
                    if(j != k)
                        est_deplace = TRUE;
                }
            }
        }
    }
    else if(dir == HAUTE)
    {
        for(i = 0; i < 8; i++)
        {
            for(j = 7; j >= 0; j--){
                if(plateau[j][i] != 0)
                {
                    for(k = j+1; k < 8; k++)
                    {
                        if(plateau[k][i] != 0)
                            break;
                    }
                    k--;
                    
                    p1.x = j;   p1.y = i;
                    p2.x = k;   p2.y = i;
                    ecrase_case(p1, p2);
                    if(j != k)
                        est_deplace = TRUE;
                }
            }
        }
    }
    else
    {
        for(i = 0; i < 8; i++)
        {
            for(j = 0; j < 8; j++){
                if(plateau[j][i] != 0)
                {
                    for(k = j-1; k >= 0; k--)
                    {
                        if(plateau[k][i] != 0)
                            break;
                    }
                    k++;

                    p1.x = j;   p1.y = i;
                    p2.x = k;   p2.y = i;
                    ecrase_case(p1, p2);
                    if(j != k)
                        est_deplace = TRUE;
                }
            }
        }
    }

    if(est_deplace)
        ajoute_aleatoire();
}

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

int aide_direction(); 

int est_gagne();

//////////// VUE //////////////

void affiche_plateau();
void affiche_score();

BOOL selecte_boutton(POINT p1, POINT p2)
{
    POINT p;
    p = wait_clic();
    if(p.x >= p1.x && p.x <= p2.x && p.y <= p1.y && p.y >= p2.y )
        return true;
    return false;
}

void affiche_menu_accueil()
{
	POINT p1, p2;
	//BOOL avecAide, avecFusionTotale;

	// dessine menu
	p1.x = 100;	p1.y = 350;
	p2.x = 300;	p2.y = 300;
	draw_fill_rectangle(p1, p2, blanc);
	p1.x += 60;	p1.y -= 10;
	aff_pol("MENU", 25, p1, noir);

	// dessiner fusion & aide
	p1.x = 110;	p1.y = 250;
	aff_pol("Fusion Totale", 15, p1, blanc);
	p1.x = 240;	p1.y = 260;
	p2.x = 280;	p2.y = 220;
	draw_fill_rectangle(p1, p2, blanc);

	p1.x = 110;	p1.y = 200;
	aff_pol("Aide", 15, p1, blanc);
	p1.x = 240;	p1.y = 210;
	p2.x = 280;	p2.y = 170;
	draw_fill_rectangle(p1, p2, blanc);

	// dessiner boutton
	p1.x = 100;	p1.y = 50;
	p2.x = 190;	p2.y = 20;
	draw_fill_rectangle(p1, p2, blanc);
	p1.x += 7;	p1.y -= 2;
	aff_pol("JOUER", 20, p1, noir);

	p1.x = 210;	p1.y = 50;
	p2.x = 300;	p2.y = 20;
	draw_fill_rectangle(p1, p2, blanc);
	p1.x += 7;	p1.y -= 2;
	aff_pol("SCORE", 20, p1, noir);

	while (true)
	{

		attendre(300);

		printf(" bool is : %d \n",selecte_boutton(p1, p2));
	}
	
	
}


void colore_case(POINT p, COULEUR couleur)
{
    POINT p1, p2;
    p1.x = p.x + 2;    p1.y = p.y + 2;
    p2.x = p.x + 47;    p2.y = p.y + 47;
    draw_fill_rectangle(p1, p2, couleur);
}

void efface_case(POINT p)
{
	colore_case(p, gris);
}

void affiche_case(int nombre, POINT p)
{
	COULEUR couleur;
	POINT pTexte;
	int i,j;
	double colors[13] = {0x0000FF, 0x000080, 0x00FF00, 0x00FFFF, 0xFF00FF, 0x808080, 0xFFFF00, 0x800000, 0x008000, 0x800080, 0xD2691E};
	
	couleur = colors[0];
	pTexte.x = p.x + 20;
	pTexte.y = p.y + 30;
	j = 0;
	for(i = 2; i <= 2048; i*=2)
	{
		if(nombre == i)
		{
			couleur = colors[j];
			break;
		}
		j++;
	}

	colore_case(p, couleur);
	aff_int(nombre, 12, pTexte, blanc);
}

void dessine_tab()
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

void dessine_score()
{
	POINT p1, p2;
	int score;
	p1.x = 450;	p1.y = 350;
	p2.x = 650;	p2.y = 300;

	draw_fill_rectangle(p1, p2, blanc);
	draw_fill_circle(p1, 10, background_color);
	p1.x += 10;	p1.y -= 10;
	draw_fill_circle(p1, 11, blanc);
	draw_fill_circle(p2, 10, background_color);
	p2.x -= 10;	p2.y += 10;
	draw_fill_circle(p2, 11, blanc);

	p1.x += 45;	p1.y += 5;
	score = calcule_score();
	aff_int(score, 35, p1, 0x9C551A);

}

int main()
{
	POINT p1, p2;
	enum DIRECTION{ HAUTE, BAS, DROITE, GAUCHE};

    init_graphics(LONGUEUR,HAUTEUR);
	init_plateau();

	p1.x = 0;	p1.y = 0;
	p2.x = LONGUEUR;	p2.y = HAUTEUR;
	draw_fill_rectangle(p1, p2, background_color);

	dessine_tab();
	dessine_score();

	while(true)
	{
		attendre(200);
		p1 = get_arrow();
		if(p1.x > 0)
			deplace_brique(DROITE);
		else if(p1.x < 0)
			deplace_brique(GAUCHE);
		if(p1.y > 0)
			deplace_brique(HAUTE); 
		else if(p1.y < 0)
			deplace_brique(BAS);
		if(p1.x != 0 || p1.y != 0)
		{
			dessine_tab();
			dessine_score();
		}
	}
	

    wait_escape();
    
    return 0;
}

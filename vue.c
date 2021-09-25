#define LONGUEUR 400
#define HAUTEUR 400
#include "modele.c"
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
	colore_case(p, noir);
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

void dessine_tab(int *plateau)
{
	POINT p1, p2;
	int i, j;

	for(i = 0; i < 8; i++)
	{
		for(j = 0; j < 8; j++)
		{
			p1.y = 50*i;	p1.x = 50*j;
			if(*(plateau+i*8+j) != 0)
				affiche_case(*(plateau+i*8+j), p1);
			else
				efface_case(p1);

		}
	}
}

void dessine_score(int *plateau)
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

	p1.x += 25;	p1.y += 5;
	score = calcule_score(plateau);
	aff_int(score, 35, p1, 0x9C551A);

}
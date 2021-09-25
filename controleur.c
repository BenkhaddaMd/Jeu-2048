#include "graphics.h"
#include "vue.c"
#define LONGUEUR 700
#define HAUTEUR 400

int plateau[8][8];

int main()
{
	POINT p1, p2;
	enum DIRECTION{ HAUTE, BAS, DROITE, GAUCHE};

    init_graphics(LONGUEUR,HAUTEUR);
	affiche_auto_on();
	//affiche_menu_accueil();
	init_plateau(&plateau[0][0]);

	p1.x = 0;	p1.y = 0;
	p2.x = LONGUEUR;	p2.y = HAUTEUR;
	draw_fill_rectangle(p1, p2, background_color);

	dessine_tab(&plateau[0][0]);
	dessine_score(&plateau[0][0]);

	while(true)
	{
		attendre(100);
		p1 = get_arrow();
		if(p1.x > 0)
			deplace_brique(&plateau[0][0], DROITE);
		else if(p1.x < 0)
			deplace_brique(&plateau[0][0], GAUCHE);
		if(p1.y > 0)
			deplace_brique(&plateau[0][0], HAUTE); 
		else if(p1.y < 0)
			deplace_brique(&plateau[0][0], BAS);
		if(p1.x != 0 || p1.y != 0)
		{
			dessine_tab(&plateau[0][0]);
			dessine_score(&plateau[0][0]);
		}
	}
	

    wait_escape();
    
    return 0;
}

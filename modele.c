
void ajoute_aleatoire(int *plateau)
{
    int i ,j;

    i = alea_int(8);
    j = alea_int(8);

    if(*(plateau+i*8+j) != 0)
        ajoute_aleatoire(plateau);
    else
        *(plateau+i*8+j) = 2;
}

void init_plateau(int *plateau)
{
    int i, j;

    for(i = 0; i < 8; i++)
    {   
        for ( j = 0; j < 8; j++)
            *(plateau+i*8+j) = 0;
    }

    ajoute_aleatoire(plateau);
    ajoute_aleatoire(plateau);
}

void ecrase_case(POINT p1, POINT p2, int *plateau)
{
    int valeur;

    valeur = *(plateau+p1.x+p1.y*8);
    *(plateau+p1.x+p1.y*8) = 0;
    *(plateau+p2.x+p2.y*8) = valeur;

}

void fusion_deux_cases(POINT p1, POINT p2, int *plateau)
{
    *(plateau+p2.x+p2.y*8) += *(plateau+p1.x+p1.y*8);
    *(plateau+p1.x+p1.y*8) = 0;
}

void applique_fusion(int *plateau, int dir)
{
    int i, j, k;
    POINT p1, p2;
    enum DIRECTION{ HAUTE, BAS, DROITE, GAUCHE};

    if(dir == BAS)
    {
        for(i = 0; i < 8; i++)
        {
            for(j = 0; j < 8; j++){
                if(*(plateau+i+j*8) != 0)
                {
                    for(k = j-1; k >= 0; k--)
                    {
                        if(*(plateau+i+k*8) == 0)
                            continue;
                        else if(*(plateau+i+k*8) == *(plateau+i+j*8))
                        {
                            p1.x = i;   p1.y = j;
                            p2.x = i;   p2.y = k;
                            fusion_deux_cases(p1, p2, plateau);
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
                if(*(plateau+i+j*8) != 0)
                {
                    for(k = j+1; k < 8; k++)
                    {
                        if(*(plateau+i+k*8) == 0)
                            continue;
                        else if(*(plateau+i+k*8) == *(plateau+i+j*8))
                        {
                            p1.x = i;   p1.y = j;
                            p2.x = i;   p2.y = k;
                            fusion_deux_cases(p1, p2, plateau);
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
                if(*(plateau+j+i*8) != 0)
                {
                    for(k = j+1; k < 8; k++)
                    {
                        if(*(plateau+k+i*8) == 0)
                            continue;
                        else if(*(plateau+k+i*8) == *(plateau+j+i*8))
                        {
                            p1.x = j;   p1.y = i;
                            p2.x = k;   p2.y = i;
                            fusion_deux_cases(p1, p2, plateau);
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
                if(*(plateau+j+i*8) != 0)
                {
                    for(k = j-1; k >= 0; k--)
                    {
                        if(*(plateau+k+i*8) == 0)
                            continue;
                        else if(*(plateau+k+i*8) == *(plateau+j+i*8))
                        {
                            p1.x = j;   p1.y = i;
                            p2.x = k;   p2.y = i;
                            fusion_deux_cases(p1, p2, plateau);
                        }
                        else
                            break;
                    }
                }
            }
        }
    }

}

void deplace_brique(int *plateau, int dir)
{
    int i, j, k;
    BOOL est_deplace;
    POINT p1, p2;
    enum DIRECTION{ HAUTE, BAS, DROITE, GAUCHE};

    est_deplace = FALSE;

    applique_fusion(plateau, dir);
    if(dir == BAS)
    {
        for(i = 0; i < 8; i++)
        {
            for(j = 0; j < 8; j++){
                if(*(plateau+i+j*8) != 0)
                {
                    for(k = j-1; k >= 0; k--)
                    {
                        if(*(plateau+i+k*8) != 0)
                            break;
                    }
                    k++;
                    
                    p1.x = i;   p1.y = j;
                    p2.x = i;   p2.y = k;
                    ecrase_case(p1, p2, plateau);
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
                if(*(plateau+i+j*8) != 0)
                {
                    for(k = j+1; k < 8; k++)
                    {
                        if(*(plateau+i+k*8) != 0)
                            break;
                    }
                    k--;
                    
                    p1.x = i;   p1.y = j;
                    p2.x = i;   p2.y = k;
                    ecrase_case(p1, p2, plateau);
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
                if(*(plateau+j+i*8) != 0)
                {
                    for(k = j+1; k < 8; k++)
                    {
                        if(*(plateau+k+i*8) != 0)
                            break;
                    }
                    k--;
                    
                    p1.x = j;   p1.y = i;
                    p2.x = k;   p2.y = i;
                    ecrase_case(p1, p2, plateau);
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
                if(*(plateau+j+i*8) != 0)
                {
                    for(k = j-1; k >= 0; k--)
                    {
                        if(*(plateau+k+i*8) != 0)
                            break;
                    }
                    k++;

                    p1.x = j;   p1.y = i;
                    p2.x = k;   p2.y = i;
                    ecrase_case(p1, p2, plateau);
                    if(j != k)
                        est_deplace = TRUE;
                }
            }
        }
    }

    if(est_deplace)
        ajoute_aleatoire(plateau);
}

int calcule_score(int *plateau)
{
    int score, i, j;

    score = 0;
    for ( i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
            score += *(plateau+i+j*8);
        
    }
    return score;
}

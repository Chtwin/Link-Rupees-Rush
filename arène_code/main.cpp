/*
Equipe: Lubrisoft
Jeu: Link Rupees Rush
*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <math.h>
// #define TOURNOIS // Cette valeur est à utiliser en conditions réelles de tournois, seulement le jour J
#define DEBUG // Permet de ne pas avoir le jeu en plein écran
#include "constantes.h"

#ifdef TOURNOIS

#include "ias/ia_3.cpp"
#include "ias/ia_9.cpp"

#define NB_PLAYER 2
#define IAS {ia_3, ia_9}

#endif

int main(int argc, char *argv[])
{
    srand(time(NULL));
    SDL_Surface *screen = NULL, *menu = NULL;
    Mix_Music *intro;
    SDL_Rect positionMenu;
    SDL_Event event;
    int continuer = 1;
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS,1042) == -1)
    {
        fprintf(stderr, "Erreur SDL_mixer : %s\n", Mix_GetError());
        exit(EXIT_FAILURE);
    }
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur SDL :%s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_WM_SetIcon(SDL_LoadBMP("icone-zelda.bmp"), NULL);
#ifdef DEBUG
    screen = SDL_SetVideoMode(1920,HAUTEUR_FENETRE,COULEUR, SDL_HWSURFACE | SDL_DOUBLEBUF);
#else
    screen = SDL_SetVideoMode(1920,HAUTEUR_FENETRE,COULEUR, SDL_FULLSCREEN | SDL_DOUBLEBUF);
#endif
    if (screen == NULL)
    {
        fprintf(stderr, "Impossible de charger video : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_WM_SetCaption("The Legend Of Zelda: Battle Royale", NULL);
    menu = SDL_LoadBMP("acchd.bmp");
    positionMenu.x=0;
    positionMenu.y=0;
    SDL_BlitSurface(menu, NULL, screen, &positionMenu);
    intro = Mix_LoadMUS("intro_ost.flac");
    Mix_VolumeMusic(VOLUME);
    Mix_PlayMusic(intro, 1);
    fprintf(stdout, "Starting\n");
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_SPACE:
                        fprintf(stdout, "SPACE PRESSED\n");
                        Mix_FreeMusic(intro);
                        continuer = play(screen);
                        break;
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                    default:
                        break;
                }
        }
        SDL_BlitSurface(menu, NULL, screen, &positionMenu);
        SDL_Flip(screen);
    }
    Mix_CloseAudio();
    Mix_FreeMusic(intro);
    SDL_FreeSurface(menu);
    SDL_Quit();
    return EXIT_SUCCESS;
}

/*
Fonction qui lance le jeu:
*/
int play (SDL_Surface* screen)
{
    fprintf(stdout, "play()\n");

    ia_ptr ias[NB_PLAYER] = IAS;

    if (NB_PLAYER < 2) {
        fprintf(stderr, "Erreur : pas assez d'ia !\n");
        exit(EXIT_FAILURE);
    }

    int i = 0, continuer = 1, j = 0, k= 0, time = 0, lastTime = 0, stime = 0, mtime = 0, points = 0, tours = 0, bonus = 0;
    Mix_AllocateChannels(4);
    char temps[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    char score[6] = {0,0,0,0,0,0};
    int maps[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR], maps_ia[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR];
    for (i=0;i<NB_BLOCS_LARGEUR;i++)
    {
        for (j=0;j<NB_BLOCS_HAUTEUR;j++)
        {
            maps[i][j]= VIDE;
        }
    }
    for (i=MINY; i<MAXY; i++)
    {
        maps[MINX][i] = MUR;
        maps[MAXX][i] = MUR;
    }
    for (i=MINX; i<MAXX; i++)
    {
        maps [i][MINY]=MUR;
        maps [i][MAXY]=MUR;
    }
    for (i=0;i<4;i++)
    {
        Mix_Volume(i,VOLUME);
    }

    SDL_Surface *rauru[4] = {NULL},*ruto[4] = {NULL},*sheik[4] = {NULL},*saria[4] = {NULL},*nayru[4] = {NULL},*oldman[4] = {NULL},*maple[4] = {NULL},*koume[4] = {NULL},*granma[4] = {NULL},*daruina[4] = {NULL},*skull[4] = {NULL}, *guard[16] = {NULL}, *link[21] = {NULL}, *rupees[3] = {NULL}, *zelda[6] = {NULL}, *bombes[10] = {NULL}, *ganon[5] ={NULL},*vide = NULL, *wall = NULL, *linkNow = NULL, *background = NULL, *scoreboard, *texte = NULL, *p_points = NULL, *ganonNow = NULL;
    TTF_Font *police = NULL, *police2 = NULL;
    Mix_Music *gerudo;
    Mix_Chunk *s_ruppes, *s_sword, *s_degat;
    SDL_Rect position, positionBackground, positionScoreboard;
    SDL_Event event;
    positionBackground.x=0;
    positionBackground.y=0;
    positionScoreboard.x= 1280;
    positionScoreboard.y= 0;
    background = IMG_Load("arene_beta_13.bmp");
    scoreboard = IMG_Load("scoreboard2.bmp");
    setup_pictures(link, rupees,ganon, zelda, guard, skull,daruina,granma,koume,maple,oldman,nayru,saria,sheik,ruto,rauru, bombes);
    //setup_map(maps);
    linkNow = link[DOWN];
    police = TTF_OpenFont("triforce.ttf", 35);
    police2 = TTF_OpenFont("triforce.ttf", 15);
    SDL_Color couleurNoire = {0, 0, 0};
    SDL_Color couleurJaune = {255, 255, 0};
    s_ruppes = Mix_LoadWAV("get_rupee.wav");
    s_sword = Mix_LoadWAV("link_sword1.wav");
    gerudo = Mix_LoadMUS("gerudo_ost.flac");
    s_degat = Mix_LoadWAV("degat.wav");
    Mix_VolumeMusic(VOLUME);
    Mix_PlayMusic(gerudo, -1);
    Player *links = (Player*) malloc(sizeof(Player) * NB_PLAYER);
    Item bombe[100];

    setup_ia(maps, &links);
    ganonNow = ganon[DOWN];

    while (continuer)
    {
        SDL_BlitSurface(background, NULL, screen, &positionBackground);
        //SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 17, 206, 112));
        SDL_BlitSurface(scoreboard, NULL, screen, &positionScoreboard);
        tours++;
        for (i=0;i<NB_PLAYER;i++)
        {
            if (links[i].classement == -1)
            {
                for (j=0;j<NB_BLOCS_LARGEUR;j++)
                {
                    for(k=0;k<NB_BLOCS_HAUTEUR;k++)
                    {
                        maps_ia[j][k]= maps[j][k];
                    }
                }
                maps[links[i].x][links[i].y] = IA;
                links[i].bouclier = false;
                position.x =links[i].x;
                position.y =links[i].y;
                SDL_PollEvent(&event);  ///SDL_WaitEvent
                switch(event.type)
                {
                    case SDL_QUIT:
                        continuer = 0;
                        break;
                    case SDL_KEYDOWN:
                        if(event.key.keysym.sym == SDLK_ESCAPE)
                        {
                            continuer = 0;
                        }
                        break;
                    default:
                        switch(ias[i](maps_ia, links[i].x, links[i].y, links[i].points, links[i].item, tours))
                        {
                            case HAUT:
                                linkNow = link[UP];
                                links[i].orientation = UP;
                                bonus += movePlayer(maps, &position, UP, s_ruppes);
                                break;
                            case BAS:
                                linkNow = link[DOWN];
                                links[i].orientation = DOWN;
                                bonus += movePlayer(maps, &position, DOWN, s_ruppes);
                                break;
                            case DROITE:
                                linkNow = link[RIGHT];
                                links[i].orientation = RIGHT;
                                bonus += movePlayer(maps, &position, RIGHT, s_ruppes);
                                break;
                            case GAUCHE:
                                linkNow = link[LEFT];
                                links[i].orientation = LEFT;
                                bonus += movePlayer(maps, &position, LEFT, s_ruppes);
                                break;
                            case EPEE_HAUT:
                                if (tours > 80)
                                {
                                    linkNow = link[HIT_UP];
                                    links[i].orientation = UP;
                                    damage(maps, links, i);
                                    Mix_PlayChannel(1, s_sword, 0);
                                }
                                break;
                            case EPEE_BAS:
                                if (tours > 80)
                                {
                                    links[i].orientation = DOWN;
                                    linkNow = link[HIT_DOWN];
                                    damage(maps, links, i);
                                    Mix_PlayChannel(1, s_sword, 0);
                                }
                                break;
                            case EPEE_DROITE:
                                if (tours > 80)
                                {
                                    links[i].orientation = RIGHT;
                                    linkNow = link[HIT_RIGHT];
                                    damage(maps, links, i);
                                    Mix_PlayChannel(1, s_sword, 0);
                                }
                                break;
                            case EPEE_GAUCHE:
                                if (tours > 80)
                                {
                                    links[i].orientation = LEFT;
                                    linkNow = link[HIT_LEFT];
                                    damage(maps, links, i);
                                    Mix_PlayChannel(1, s_sword, 0);
                                }
                                break;
                            case PARER:
                                linkNow = link[SHIELD];
                                links[i].bouclier = true;
                                break;
                            case BOMBE:
                                if (tours > 80 && links[i].item > 0)
                                {
                                    links[i].item--;

                                    if(links[i].y != NB_BLOCS_HAUTEUR-1)
                                    {
                                        int b;
                                        for(b=0; b<100; b++)
                                        {
                                            if(bombe[b].active == 0)
                                            {
                                                bombe[b].x = links[i].x;
                                                bombe[b].y = links[i].y + 1;
                                                bombe[b].active = 1;
                                                bombe[b].joueur = i;
                                                bombe[b].tours = 0;
                                                maps[links[i].x][links[i].y + 1] = BOMBE_MAP;
                                                break;
                                            }
                                        }
                                    }
                                }
                                break;
                        }
                        break;
                }
                if (bonus == 100)
                {
                    links[i].item+=1;
                }
                else
                {
                    links[i].points+=bonus;
                }
                bonus = 0;
                links[i].x = position.x;
                links[i].y = position.y;
                position.x*= TAILLE_BLOC;
                position.y*= TAILLE_BLOC;
                maps[links[i].x][links[i].y] = IA;
                SDL_BlitSurface(linkNow, NULL, screen, &position);
                ///
                position.y -= 25 ;
                position.x += 4;
                sprintf(score, "J%d",i+1);
                p_points = TTF_RenderText_Blended(police2, score, couleurJaune);
                SDL_BlitSurface(p_points, NULL, screen, &position);
            }
            position.x = (i > 16) ? 1650 : 1400;
            position.y = (i > 16) ? 397 + (i-17)*25 : 397 + i*25;
            SDL_BlitSurface((links[i].classement == -1) ? rupees[GREEN_RUPEE] : rupees[RED_RUPEE], NULL, screen, &position);
            position.x = (i > 16) ? 1730 : 1480;
            position.y = (i > 16) ? 397 + (i-17)*25 : 397 + i*25;
            SDL_BlitSurface(bombes[1], NULL, screen, &position);
            SDL_Color couleurRouge = {255,0 , 0};
            position.x = (i > 16) ? 1675 : 1425;
            position.y = (i > 16) ? 400 + (i-17)*25 : 400 + i*25;

            if (links[i].points < 10)
            {
                sprintf(score, "X 00%d        X %d \tJ%d",links[i].points,links[i].item, i+1);
            }
            else if (links[i].points < 100)
            {
                sprintf(score, "X 0%d        X %d \tJ%d",links[i].points,links[i].item,i+1);
            }
            else
            {
                sprintf(score, "X %d        X %d \tJ%d",links[i].points,links[i].item,i+1);
            }

            p_points = TTF_RenderText_Blended(police2, score, (links[i].classement == -1) ? couleurJaune : couleurRouge);

            SDL_BlitSurface(p_points, NULL, screen, &position);
        }
        if(tours > 80)
        {
            item(maps,links,tours,bombe); //S'execute tout les tours
        }
        sprintf(score, "%s %d","Tours:",tours);
        p_points = TTF_RenderText_Blended(police, score, couleurNoire);
        position.x = 1025;
        position.y = 30;
        SDL_BlitSurface(p_points, NULL, screen, &position);
        time = SDL_GetTicks();
        if (time - lastTime >= 1000)
        {
            stime++;
            if (stime == 60)
            {
                mtime++;
                stime = 0;
            }
            lastTime = time;
        }
        if (tours%150==0)
        {
            setup_map(maps);
        }
        timer(temps,score,time,lastTime,stime,mtime,points);
        texte = TTF_RenderText_Blended(police, temps, couleurNoire);
        blit_items(maps,screen,rupees,bombes);
        ganon_move(maps, s_degat , links, &position, tours);
        SDL_BlitSurface(ganonNow, NULL, screen, &position);
        animation(screen, zelda, skull,daruina,granma,koume,maple,oldman,nayru,saria,sheik,ruto,rauru,tours);
        position.x = 70;
        position.y = 25; //30
        SDL_BlitSurface(texte, NULL, screen, &position);
        //SDL_BlitSurface(ganonNow, NULL, screen, &position);
        garde(screen,guard, tours);
        SDL_Flip(screen);
        continuer = win(test_class(maps, links), screen, gerudo, links, continuer, tours);
    }
    SDL_FreeSurface(wall);
    SDL_FreeSurface(texte);
    SDL_FreeSurface(p_points);
    SDL_FreeSurface(vide);
    Mix_FreeChunk(s_sword);
    Mix_FreeChunk(s_ruppes);
    SDL_FreeSurface(*saria);
    SDL_FreeSurface(*nayru);
    SDL_FreeSurface(*oldman);
    SDL_FreeSurface(*maple);
    SDL_FreeSurface(*koume);
    SDL_FreeSurface(*granma);
    SDL_FreeSurface(*daruina);
    SDL_FreeSurface(*skull);
    SDL_FreeSurface(*guard);
    SDL_FreeSurface(*link);
    SDL_FreeSurface(*rupees);
    SDL_FreeSurface(*zelda);
    SDL_FreeSurface(*ganon);
    SDL_FreeSurface(vide);
    SDL_FreeSurface(linkNow);
    SDL_FreeSurface(background);
    SDL_FreeSurface(scoreboard);
    SDL_FreeSurface(texte);
    SDL_FreeSurface(p_points);
    SDL_FreeSurface(ganonNow);
    for (i = 0 ; i < 21 ; i++)
    {
        SDL_FreeSurface(link[i]);
    }
    TTF_CloseFont(police);
    TTF_CloseFont(police2);
    TTF_Quit();
    Mix_PauseMusic();
    return 0;
}

/*
Fonction qui initialise la carte avec les rubis et les cases vides.
*/
void setup_map (int maps[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR])
{
    int i,j, nb = 0;
    for (i = MINX + 27; i < MAXX - 27 ; i++)
    {
        for (j = MINY + 13; j < MAXY - 13 ; j++)
        {
            nb = rand()%325;
            switch (nb)
            {
                case 5:
                    maps[i][j]= GREEN_RUPEE;
                    break;
                case 2:
                    maps[i][j]= BLUE_RUPEE;
                    break;
                case 4:
                    maps[i][j]= RED_RUPEE;
                    break;
            }
        }
    }
    for (i = MINX + 27; i < MAXX - 27; i++)
    {
        for (j = MINY + 13; j < MAXY - 13; j++)
        {
            if(rand()%850 == 1)
            {
                maps[i][j] = POT;
            }
        }
    }
}

/*
Fonction qui initialise les paramètres des IAs.
*/
void setup_ia(int maps[][NB_BLOCS_HAUTEUR], Player **links_ptr)
{
    Player *links = *links_ptr;
    fprintf(stdout, "setup_ia for %d IAS (hauteur=%d, largeur=%d)\n", NB_PLAYER, NB_BLOCS_HAUTEUR, \
        NB_BLOCS_LARGEUR);
    fflush(stdout);
    int i;
    if (NB_PLAYER == 2)
    {
        links[0].x = 43;
        links[0].y = 50;
        links[1].x = 83;
        links[1].y = 50;
        for (i=0;i<NB_PLAYER;i++)
        {
            links[i].points = 25 + rand()%3;
            links[i].orientation = DOWN;
            links[i].classement = -1;
            links[i].item = 0;
            maps[links[i].x][links[i].y] = IA;
        }

    }
    else if (NB_PLAYER == 3)
    {
        float z=0.2;
        int rayon =22;
        for (i=0;i<NB_PLAYER;i++)
        {
            links[i].points = 30 + rand()%3;
            links[i].orientation = DOWN;
            links[i].classement = -1;
            links[i].item = 0;
            links[i].x = CENTRE_CERCLE_X+5 + rayon*cosf(z*3.14);
            links[i].y = CENTRE_CERCLE_Y+10 + rayon*sinf(z*3.14);
            maps[links[i].x][links[i].y] = IA;
            z+=0.66;
        }
    }
    else if (NB_PLAYER == 26)
    {
        float z=0.0;
        int rayon =22;
        for (i=0;i<NB_PLAYER;i++)
        {
            links[i].points = 30 + rand()%3;
            links[i].orientation = DOWN;
            links[i].classement = -1;
            links[i].item = 0;
            links[i].x = CENTRE_CERCLE_X+4 + rayon*cosf(z*3.14);
            links[i].y = CENTRE_CERCLE_Y+7 + rayon*sinf(z*3.14);
            maps[links[i].x][links[i].y] = IA;
            z+=0.077;
        }
    }
    else
    {
        for (i=0;i<NB_PLAYER;i++)
        {
            links[i].points = 20;
            links[i].orientation = DOWN;
            links[i].classement = -1;
            links[i].item = 0;
            links[i].x = 20 + rand()%80;
            links[i].y = 30 + rand()%40;
            maps[links[i].x][links[i].y] = IA;
        }
    }
}

/*
Fonction qui permet de gérer le chronométre du jeu.
*/
void timer (char temps[20],char score[6],int time,int lastTime,int stime,int mtime,int points)
{
    if (stime < 10)
    {
        sprintf(temps, "Timer : %d : 0%d",mtime,stime);
    }
    else
    {
        sprintf(temps, "Timer : %d : %d",mtime,stime);
    }
}


/*
Fonction qui permet aux IAs de se déplacer.
*/
int movePlayer (int maps[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR], SDL_Rect *position, int direction, Mix_Chunk *s_ruppes)
{
    int i, bonus = 0;
    int *aroundCase[4], *currentCase = NULL;
    switch (direction)
    {
        case UP:
            if (position->y - 1 < MINY + 1 || maps[position->x][position->y - 1] == BOMBE_MAP || maps[position->x][position->y - 1] == IA || maps[position->x][position->y - 1] == BOMBE_DEFLAG)
                break;

            maps[position->x][position->y] = VIDE;
            position->y--;
            break;


        case DOWN:
            if (position->y + 1 > MAXY - 1 || maps[position->x][position->y + 1] == BOMBE_MAP || maps[position->x][position->y + 1] == IA || maps[position->x][position->y + 1] == BOMBE_DEFLAG)
                break;

            maps[position->x][position->y] = VIDE;
            position->y++;

            break;

        case RIGHT:
            if (position->x + 1 > MAXX - 1|| maps[position->x + 1][position->y] == BOMBE_MAP || maps[position->x + 1][position->y] == IA || maps[position->x + 1][position->y] == BOMBE_DEFLAG)
                break;

            maps[position->x][position->y] = VIDE;
            position->x++;

            break;

        case LEFT:
            if (position->x - 1 < MINX + 1 || maps[position->x - 1][position->y] == BOMBE_MAP || maps[position->x - 1][position->y] == IA || maps[position->x - 1][position->y] == BOMBE_DEFLAG)
                break;

            maps[position->x][position->y] = VIDE;
            position->x--;

            break;
    }

    aroundCase[0] = &maps[position->x][position->y];
    aroundCase[1] = &maps[position->x - 1][position->y];
    aroundCase[2] = &maps[position->x - 1][position->y - 1];
    aroundCase[3] = &maps[position->x][position->y - 1];

    for (i = 0; i < 4; i++)
    {
        if ((*aroundCase[i]) != VIDE &&(*aroundCase[i]) != IA)
        {
            currentCase = aroundCase[i];
            break;
        }
    }

    if (currentCase != NULL)
    {
        switch (*currentCase)
        {
            case GREEN_RUPEE:
                bonus++;
                Mix_PlayChannel(1, s_ruppes, 0);
                break;
            case BLUE_RUPEE:
                bonus += BLUE_BONUS;
                Mix_PlayChannel(1, s_ruppes, 0);
                 break;
            case RED_RUPEE:
                bonus += RED_BONUS;
                Mix_PlayChannel(1, s_ruppes, 0);
                break;
            case POT:
                if(rand()%10 == 5)
                {
                    bonus += 25;
                    Mix_PlayChannel(1, s_ruppes, 0);
                }
                else if(rand()%2 == 1)
                {
                    bonus+= 100;
                }
                else
                {
                    bonus+=5;
                    Mix_PlayChannel(1, s_ruppes, 0);
                }
                break;

        }

        if ((*currentCase) != IA && (*currentCase) != BOMBE_MAP && (*currentCase) != MUR)
            (*currentCase) = VIDE;

    }
    return bonus;
}

void item(int maps[][NB_BLOCS_HAUTEUR], Player links[], int tours, Item bombes [100])
{
    int i,j,l,z;
    if(tours == 2){
        for (i=0; i<100; i++){
            Item item;
            item.x = -1;
            item.y = -1;
            item.active = 0;
            item.joueur = -1;
            bombes[i] = item;
        }
    }
    for (i=MINX+1 ; i<MAXX; i++)  // parcours les bombes sur la map
    {
        for (j=MINY+1; j<MAXY; j++) // parcours les bombes sur la map
        {
            if(maps[i][j] != BOMBE_MAP  && maps[i][j] != BOMBE_DEFLAG)
            {
                continue;
            }
            for (z=0; z<100; z++)
            {
                // Parcour tout le tableau de bombe
                // a la recherche du struct de la bombe a ces meme coordonée
                if(bombes[z].x != i || bombes[z].y != j || bombes[z].active == false)
                { 
                    continue;
                }
                //si la bombe est active alors
                if(bombes[z].tours > 17)
                {
                    //Remise a 0 de la bombe
                    bombes[z].x = -1;
                    bombes[z].y = -1;
                    bombes[z].active = false;
                    bombes[z].joueur = -1;
                    maps[i][j] = VIDE;
                    bombes[z].tours = 0;

                }
                else if (bombes[z].tours >= 15)// Si une bombe explose alors
                {
                    for (l=0; l<NB_PLAYER; l++)//pour tout les joueurs
                    {
                        int dans_rayon_g = bombes[z].x - RAYON_BOMBE < links[l].x;
                        int dans_rayon_d = links[l].x < bombes[z].x + RAYON_BOMBE;
                        int dans_rayon_b = bombes[z].y + RAYON_BOMBE > links[l].y;
                        int dans_rayon_h = links[l].y > bombes[z].y - RAYON_BOMBE;
                        if (dans_rayon_g && dans_rayon_b && dans_rayon_d && dans_rayon_h && \
                                                      links[l].classement == - 1) //Dans le rayon de la deflagration
                        {
                            links[l].points -= DEGAT_BOMBE;// Mettre un degat au joueur
                            if (links[bombes[z].joueur].classement == -1)
                            {
                                links[bombes[z].joueur].points +=RECUP_DEGAT_BOMBE;
                            }
                        }
                    }
                    maps[i][j] = BOMBE_DEFLAG;
                    bombes[z].tours+=1; // On incremente de 1 les tours pour faire exploser la bombe
                }
                else
                {
                    bombes[z].tours+=1; // On incremente de 1 les tours pour faire exploser la bombe
                }
                break; // on n'explose qu'une seule bombe par tour
            }
        }
    }
}

void damage(int maps[][NB_BLOCS_HAUTEUR], Player links[], int playernow)
{
int j=0;
    switch (links[playernow].orientation)
    {
        case UP :
            for (j=0; j<NB_PLAYER; j++)
            {
                if(links[j].x == links[playernow].x && links[j].y == links[playernow].y-1 && links[j].classement == -1 && links[j].bouclier != true){
                    links[j].points -= DEGAT_EPEE;
                    links[playernow].points += RECUP_RUBIS;
                    break;
                }
            }
            break;
        case DOWN :
            for (j=0; j<NB_PLAYER; j++)
            {
                if(links[j].x == links[playernow].x && links[j].y == links[playernow].y+1 && links[j].classement == -1 && links[j].bouclier != true){
                    links[j].points -= DEGAT_EPEE;
                    links[playernow].points += RECUP_RUBIS;
                    break;
                }
            }
            break;
        case LEFT :
            for (j=0; j<NB_PLAYER; j++)
            {
                if(links[j].x == links[playernow].x-1 && links[j].y == links[playernow].y && links[j].classement == -1 && links[j].bouclier != true){
                    links[j].points -= DEGAT_EPEE;
                    links[playernow].points += RECUP_RUBIS;
                    break;
                }
            }
        case RIGHT :
            for (j=0; j<NB_PLAYER; j++)
            {
                if(links[j].x == links[playernow].x+1 && links[j].y == links[playernow].y && links[j].classement == -1 && links[j].bouclier != true){
                    links[j].points -= DEGAT_EPEE;
                    links[playernow].points += RECUP_RUBIS;
                    break;
                }
            }
            break;
    }
}

void ganon_move_internal(Player *link, int *ganonx, int *ganony)
{
    int x = link->x * TAILLE_BLOC;
    int y = link->y * TAILLE_BLOC;
    int decalx = *ganonx - x;
    int decaly = *ganony - y;
    if (decalx > 0)
    {
        *ganonx -= decalx >= 10 ? 10 : decalx;
    }
    else if (decalx < 0)
    {
        *ganonx += decalx <= -10 ? 10 : decalx;
    }
    if (decaly > 0)
    {
        *ganony -= decaly >= 10 ? 10 : decaly;
    }
    else if (decaly < 0)
    {
        *ganony += decaly <= -10 ? 10 : decaly;
    }
}

/*
Fonction qui permet à Ganon de se déplacer.
*/
void ganon_move(int maps[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR], Mix_Chunk *s_degat, Player links[], SDL_Rect *position, int tours)
{
    int i = 0; // , direction_ganon;
    static int research = 1;
    static int bestlink = 0;
    static int ganonx = LARGEUR_FENETRE / 2 - 50;
    static int ganony = HAUTEUR_FENETRE / 2;
    static int delay = 180;
    if (tours <= delay)
    {
        position->x = ganonx;
        position->y = ganony;
        return;
    }

    if (research == 1)
    {
        for(i = 0; i < NB_PLAYER; i++)
        {
            if(links[bestlink].points < links[i].points)
            {
                bestlink = i;
            }
        }
        research = 0;
    }

    ganon_move_internal(&links[bestlink], &ganonx, &ganony);

    int x = links[bestlink].x * TAILLE_BLOC;
    int y = links[bestlink].y * TAILLE_BLOC;
    int decalx = ganonx - x;
    int decaly = ganony - y;

    if (decalx == 0 && decaly == 0)
    {
        printf("dégats: %d\n", links[bestlink].points);
        links[bestlink].points -= 35;
        ganonx = LARGEUR_FENETRE / 2 - 50;
        ganony = HAUTEUR_FENETRE / 2 ;
        research = 1;
        Mix_PlayChannel(2, s_degat, 0);
        delay = tours + 160;
    }
    position->x = ganonx;
    position->y = ganony;
}

/*
Fonction qui classe les joueurs.
*/
bool test_class(int maps[][NB_BLOCS_HAUTEUR], Player links[])
{
    int i = 0;
    static int num = NB_PLAYER;
    for(i=0;i<NB_PLAYER;i++)
    {
        if (links[i].points <= 0 && links[i].classement == -1 && num != 1)
        {
            links[i].classement = num;
            maps[links[i].x][links[i].y] = VIDE;
            links[i].points = 0;
            num--;
        }
    }
    if (num == 1)
    {
        for(i=0;i<NB_PLAYER;i++)
        {
            if (links[i].classement == -1)
            {
                if (links[i].points < 0)
                    links[i].points = 0;
                links[i].classement = 1;
            }
        }
        return true;
    }
    return false;
}

/*
Fonction qui détérmine quand il y a un vainqeur.
*/
int win(bool survivant, SDL_Surface* screen, Mix_Music *gerudo, Player links[], int continuer, int tours)
{
    if (survivant == true || tours == 2000)
    {
        int i, j;
        if (tours == 2000)
        {
            int nb_survive = 0, max = NB_PLAYER, vtemp;
            int tab_survive[NB_PLAYER];
            for (i=0;i<NB_PLAYER;i++)
            {
                if (links[i].classement == -1)
                {
                    tab_survive[nb_survive] = i;
                    nb_survive++;
                }
                else if (links[i].classement < max && links[i].classement>0) max = links[i].classement;
            }
            max--;
            for (i=0; i<nb_survive; i++)
            {
                for(j=i; j<nb_survive; j++)
                {
                    if(links[tab_survive[j]].points < links[tab_survive[i]].points)
                        {
                            vtemp = tab_survive[i];
                            tab_survive[i] = tab_survive[j];
                            tab_survive[j] = vtemp;
                        }
                }
            }
            for(i=0;i<nb_survive;i++)
            {
                links[tab_survive[i]].classement = max;
                max--;
            }
        }
        Mix_PauseMusic();
        char winner[35] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        TTF_Font *police = NULL;
        police = TTF_OpenFont("triforce.ttf", 22);
        SDL_Color couleurJaune = {255, 255, 0};
        SDL_Surface *background = NULL, *texte = NULL;
        SDL_Rect positionBackground, position;
        SDL_Event event;
        positionBackground.x = 0;
        positionBackground.y = 0;
        position.x = 110;
        position.y = 110;
        background = IMG_Load("score.bmp");
        SDL_BlitSurface(background, NULL, screen, &positionBackground);
        sprintf(winner, "Classement:");
        texte = TTF_RenderText_Blended(police, winner, couleurJaune);
        SDL_BlitSurface(texte, NULL, screen, &position);
        for(i=0;i<NB_PLAYER;i++)
        {
            position.x = 150;
            position.y = 180 + 22*links[i].classement - 1;
            sprintf(winner, "J%d a %d points et est a la %d position",i+1,links[i].points,links[i].classement);
            texte = TTF_RenderText_Blended(police, winner, couleurJaune);
            SDL_BlitSurface(texte, NULL, screen, &position);
        }
        SDL_Flip(screen);
        while (continuer)
        {
            SDL_WaitEvent(&event);
            switch(event.type)
            {
                case SDL_QUIT:
                    continuer = 0;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        Mix_PauseMusic();
                        continuer = 0;
                        return 0;
                    }
            }
        }
        TTF_CloseFont(police);
    }
    return continuer;
}

/*
Fonction qui gère les déplacements des pnjs.
*/
void animation(SDL_Surface* screen, SDL_Surface *zelda[6], SDL_Surface *skull[4],SDL_Surface *daruina[4],SDL_Surface *granma[4],SDL_Surface *koume[4],SDL_Surface *maple [4],SDL_Surface *oldman[4],SDL_Surface *nayru[4],SDL_Surface *saria[4],SDL_Surface *sheik[4], SDL_Surface *ruto[4], SDL_Surface *rauru[4], int tours)
{
    static int tour = 0;
    SDL_Rect pnj[16];
    int x = 1197, y = 385, x1 = 1225, y2 = 387,boucle, i;
    for (boucle=0;boucle<2;boucle++)
    {
        for (i=0;i<8;i++)
        {
                pnj[i].x = x;
                pnj[i].y = y + ECART * i;
                pnj[i+8].x = x1;
                pnj[i+8].y = y2 + ECART * i;
        }

        tour%= 4;
        SDL_BlitSurface(rauru[tour], NULL, screen, &pnj[0]);
        SDL_BlitSurface(skull[tour], NULL, screen, &pnj[1]);
        SDL_BlitSurface(daruina[tour], NULL, screen, &pnj[2]);
        SDL_BlitSurface(granma[tour], NULL, screen, &pnj[3]);
        SDL_BlitSurface(koume[tour], NULL, screen, &pnj[4]);
        SDL_BlitSurface(maple[tour], NULL, screen, &pnj[5]);
        SDL_BlitSurface(oldman[tour], NULL, screen, &pnj[6]);
        SDL_BlitSurface(saria[tour], NULL, screen, &pnj[7]);
        ///
        SDL_BlitSurface(nayru[tour], NULL, screen, &pnj[8]);
        SDL_BlitSurface(oldman[tour], NULL, screen, &pnj[9]);
        SDL_BlitSurface(maple[tour], NULL, screen, &pnj[10]);
        SDL_BlitSurface(koume[tour], NULL, screen, &pnj[11]);
        SDL_BlitSurface(granma[tour], NULL, screen, &pnj[12]);
        SDL_BlitSurface(daruina[tour], NULL, screen, &pnj[13]);
        SDL_BlitSurface(skull[tour], NULL, screen, &pnj[14]);
        SDL_BlitSurface(sheik[tour], NULL, screen, &pnj[15]);
        ///
        x = 35;
        y = 385;
        x1 = 60;
        y2 = 387;
    }
    if (tours%15==0)
    {
        tour++;
    }
}


/*
Fonction qui permet aux pnjs gardes de patrouiller autour de l'arène.
*/
void garde(SDL_Surface* screen, SDL_Surface *guard[16], int tours)
{
    static int tour = ANIM_DOWN1;
    static int y = 5;
    SDL_Rect positionGarde;
    if (y == 5)
    {
        positionGarde.x = 15;
        positionGarde.y = 5;
    }
    else
    {
        positionGarde.x = 15;
        positionGarde.y = y;
    }
    SDL_BlitSurface(guard[tour], NULL, screen, &positionGarde);
    if (tours%4==0)
    {
        if (tour%ANIM_DOWN3==0)
        {
            tour = ANIM_UP3;
        }
        tour++;
        y+=3;
    }
}

/*
Fonction qui permet d'afficher les items dans l'arène.
*/
void blit_items(int maps[][NB_BLOCS_HAUTEUR], SDL_Surface* screen, SDL_Surface* rupees[3], SDL_Surface *bombes[10])
{
    int i, j;
    SDL_Rect position;
    for (i = MINX - 10 ; i < MAXX + 10 ; i++)
    {
        for (j = MINY - 10 ; j < MAXY + 10; j++)
        {
            position.x = i*TAILLE_BLOC + 10;
            position.y = j*TAILLE_BLOC + 10;
            switch(maps[i][j])
            {
                case GREEN_RUPEE:
                    SDL_BlitSurface(rupees[GREEN_RUPEE], NULL, screen, &position);
                    break;
                case BLUE_RUPEE:
                    SDL_BlitSurface(rupees[BLUE_RUPEE], NULL, screen, &position);
                    break;
                case RED_RUPEE:
                    SDL_BlitSurface(rupees[RED_RUPEE], NULL, screen, &position);
                    break;
                case POT:
                    SDL_BlitSurface(bombes[0], NULL, screen, &position);
                    break;
                case BOMBE_MAP:
                    SDL_BlitSurface(bombes[1], NULL, screen, &position);
                    break;
                case BOMBE_DEFLAG :
                    position.x -= 31;
                    position.y -= 31;
                    SDL_BlitSurface(bombes[2], NULL, screen, &position);
                    break;
            }
        }
    }
}

/*
Fonction qui permet de charger toutes les images du dossier.
*/
void setup_pictures (SDL_Surface *link[21],SDL_Surface *rupees[3],SDL_Surface *ganon[5], SDL_Surface *zelda[6], SDL_Surface *guard[16], SDL_Surface *skull[4],SDL_Surface *daruina[4],SDL_Surface *granma[4],SDL_Surface *koume[4],SDL_Surface *maple [4],SDL_Surface *oldman[4],SDL_Surface *nayru[4],SDL_Surface *saria[4],SDL_Surface *sheik[4], SDL_Surface *ruto[4], SDL_Surface *rauru[4],SDL_Surface *bombes[10])
{
    link[UP] = IMG_Load("link_up.bmp");
    SDL_SetColorKey(link[UP], SDL_SRCCOLORKEY, SDL_MapRGB((*link)->format, 0, 0, 255));
    link[DOWN] = IMG_Load("link_down.bmp");
    SDL_SetColorKey(link[DOWN], SDL_SRCCOLORKEY, SDL_MapRGB((*link)->format, 0, 0, 255));
    link[RIGHT] = IMG_Load("link_right.bmp");
    SDL_SetColorKey(link[RIGHT], SDL_SRCCOLORKEY, SDL_MapRGB((*link)->format, 0, 0, 255));
    link[LEFT] = IMG_Load("link_left.bmp");
    SDL_SetColorKey(link[LEFT], SDL_SRCCOLORKEY, SDL_MapRGB((*link)->format, 0, 0, 255));
    link[HIT_UP] = IMG_Load("up_hit.bmp");
    SDL_SetColorKey(link[HIT_UP], SDL_SRCCOLORKEY, SDL_MapRGB((*link)->format, 0, 0, 255));
    link[HIT_DOWN] = IMG_Load("down_hit.bmp");
    SDL_SetColorKey(link[HIT_DOWN], SDL_SRCCOLORKEY, SDL_MapRGB((*link)->format, 0, 0, 255));
    link[HIT_RIGHT] = IMG_Load("right_hit.bmp");
    SDL_SetColorKey(link[HIT_RIGHT], SDL_SRCCOLORKEY, SDL_MapRGB((*link)->format, 0, 0, 255));
    link[HIT_LEFT] = IMG_Load("left_hit.bmp");
    SDL_SetColorKey(link[HIT_LEFT], SDL_SRCCOLORKEY, SDL_MapRGB((*link)->format, 0, 0, 255));
    link[SHIELD] = IMG_Load("shield_link.bmp");
    SDL_SetColorKey(link[SHIELD], SDL_SRCCOLORKEY, SDL_MapRGB((*link)->format, 0, 0, 255));
    //link[DOWN_ANIM] = IMG_Load("link_down_floor.bmp");
    //SDL_SetColorKey(link[DOWN_ANIM], SDL_SRCCOLORKEY, SDL_MapRGB((*link)->format, 0, 0, 255));
    ///
    bombes[0] = IMG_Load("pot2.bmp");
    SDL_SetColorKey(bombes[0], SDL_SRCCOLORKEY, SDL_MapRGB((*link)->format, 0, 0, 255));
    bombes[1] = IMG_Load("bombe2.bmp");
    SDL_SetColorKey(bombes[1], SDL_SRCCOLORKEY, SDL_MapRGB((*link)->format, 0, 0, 255));
    bombes[2] = IMG_Load("last_deflag.bmp");
    SDL_SetColorKey(bombes[2], SDL_SRCCOLORKEY, SDL_MapRGB((*link)->format, 0, 0, 255));
    ///
    rupees[GREEN_RUPEE] = IMG_Load("green_rupee1.bmp");
    SDL_SetColorKey(rupees[GREEN_RUPEE], SDL_SRCCOLORKEY, SDL_MapRGB((*rupees)->format, 0, 0, 255));
    rupees[BLUE_RUPEE] = IMG_Load("blue_rupee.bmp");
    SDL_SetColorKey(rupees[BLUE_RUPEE], SDL_SRCCOLORKEY, SDL_MapRGB((*rupees)->format, 0, 0, 255));
    rupees[RED_RUPEE] = IMG_Load("red_rupee.bmp");
    SDL_SetColorKey(rupees[RED_RUPEE], SDL_SRCCOLORKEY, SDL_MapRGB((*rupees)->format, 0, 0, 255));
    ///
    ganon[UP] = IMG_Load("ganon_V6.bmp");
    SDL_SetColorKey(ganon[UP], SDL_SRCCOLORKEY, SDL_MapRGB((*ganon)->format, 0, 0, 255));
    ganon[DOWN] = IMG_Load("ganon_V6.bmp");
    SDL_SetColorKey(ganon[DOWN], SDL_SRCCOLORKEY, SDL_MapRGB((*ganon)->format, 0, 0, 255));
    ganon[LEFT] = IMG_Load("ganon_V6.bmp");
    SDL_SetColorKey(ganon[LEFT], SDL_SRCCOLORKEY, SDL_MapRGB((*ganon)->format, 0, 0, 255));
    ganon[RIGHT] = IMG_Load("ganon_V6.bmp");
    SDL_SetColorKey(ganon[RIGHT], SDL_SRCCOLORKEY, SDL_MapRGB((*ganon)->format, 0, 0, 255));
    //ganon[FIGHT] = IMG_Load("ganon_V6.bmp");
    //SDL_SetColorKey(ganon[], SDL_SRCCOLORKEY, SDL_MapRGB((*ganon)->format, 0, 0, 255));
    ///
    zelda[UP] = IMG_Load("zelda_for_gradin1.bmp");
    SDL_SetColorKey(zelda[UP], SDL_SRCCOLORKEY, SDL_MapRGB((*zelda)->format, 0, 0, 255));
    zelda[DOWN] = IMG_Load("zelda_for_gradin2.bmp");
    SDL_SetColorKey(zelda[DOWN], SDL_SRCCOLORKEY, SDL_MapRGB((*zelda)->format, 0, 0, 255));
    zelda[LEFT] = IMG_Load("zelda_for_gradin3.bmp");
    SDL_SetColorKey(zelda[LEFT], SDL_SRCCOLORKEY, SDL_MapRGB((*zelda)->format, 0, 0, 255));
    zelda[RIGHT] = IMG_Load("zelda_for_gradin4.bmp");
    SDL_SetColorKey(zelda[RIGHT], SDL_SRCCOLORKEY, SDL_MapRGB((*zelda)->format, 0, 0, 255));
    zelda[ANIM_UP1] = IMG_Load("zelda_for_gradin5.bmp");
    SDL_SetColorKey(zelda[ANIM_UP1], SDL_SRCCOLORKEY, SDL_MapRGB((*zelda)->format, 0, 0, 255));
    zelda[ANIM_UP2] = IMG_Load("zelda_for_gradin6.bmp");
    SDL_SetColorKey(zelda[ANIM_UP2], SDL_SRCCOLORKEY, SDL_MapRGB((*zelda)->format, 0, 0, 255));
    ///
    guard[UP] = IMG_Load("guard_rotation1.bmp");
    SDL_SetColorKey(guard[UP], SDL_SRCCOLORKEY, SDL_MapRGB ((*guard)->format,0,0,255));
    guard[DOWN]=IMG_Load("guard_rotation2.bmp");
    SDL_SetColorKey(guard[DOWN], SDL_SRCCOLORKEY, SDL_MapRGB ((*guard)->format,0,0,255));
    guard[RIGHT]=IMG_Load("guard_rotation4.bmp");
    SDL_SetColorKey(guard[RIGHT], SDL_SRCCOLORKEY, SDL_MapRGB ((*guard)->format,0,0,255));
    guard[LEFT]=IMG_Load("guard_rotation3.bmp");
    SDL_SetColorKey(guard[LEFT], SDL_SRCCOLORKEY, SDL_MapRGB ((*guard)->format,0,0,255));
    guard[ANIM_UP1]=IMG_Load("guard_up1.bmp");
    SDL_SetColorKey(guard[ANIM_UP1], SDL_SRCCOLORKEY, SDL_MapRGB ((*guard)->format,0,0,255));
    guard[ANIM_UP2]=IMG_Load("guard_up2.bmp");
    SDL_SetColorKey(guard[ANIM_UP2], SDL_SRCCOLORKEY, SDL_MapRGB ((*guard)->format,0,0,255));
    guard[ANIM_UP3]=IMG_Load("guard_up3.bmp");
    SDL_SetColorKey(guard[ANIM_UP3], SDL_SRCCOLORKEY, SDL_MapRGB ((*guard)->format,0,0,255));
    guard[ANIM_DOWN1]=IMG_Load("guard_down1.bmp");
    SDL_SetColorKey(guard[ANIM_DOWN1], SDL_SRCCOLORKEY, SDL_MapRGB ((*guard)->format,0,0,255));
    guard[ANIM_DOWN2]=IMG_Load("guard_down2.bmp");
    SDL_SetColorKey(guard[ANIM_DOWN2], SDL_SRCCOLORKEY, SDL_MapRGB ((*guard)->format,0,0,255));
    guard[ANIM_DOWN3]=IMG_Load("guard_down3.bmp");
    SDL_SetColorKey(guard[ANIM_DOWN3], SDL_SRCCOLORKEY, SDL_MapRGB ((*guard)->format,0,0,255));
    guard[ANIM_LEFT1]=IMG_Load("guard_left1.bmp");
    SDL_SetColorKey(guard[ANIM_LEFT1], SDL_SRCCOLORKEY, SDL_MapRGB ((*guard)->format,0,0,255));
    guard[ANIM_LEFT2]=IMG_Load("guard_left2.bmp");
    SDL_SetColorKey(guard[ANIM_LEFT2], SDL_SRCCOLORKEY, SDL_MapRGB ((*guard)->format,0,0,255));
    guard[ANIM_LEFT3]=IMG_Load("guard_left3.bmp");
    SDL_SetColorKey(guard[ANIM_LEFT3], SDL_SRCCOLORKEY, SDL_MapRGB ((*guard)->format,0,0,255));
    guard[ANIM_RIGHT1]=IMG_Load("guard_rigth1.bmp");
    SDL_SetColorKey(guard[ANIM_RIGHT1], SDL_SRCCOLORKEY, SDL_MapRGB ((*guard)->format,0,0,255));
    guard[ANIM_RIGHT2]=IMG_Load("guard_rigth2.bmp");
    SDL_SetColorKey(guard[ANIM_RIGHT2], SDL_SRCCOLORKEY, SDL_MapRGB ((*guard)->format,0,0,255));
    guard[ANIM_RIGHT3]=IMG_Load("guard_rigth3.bmp");
    SDL_SetColorKey(guard[ANIM_RIGHT3], SDL_SRCCOLORKEY, SDL_MapRGB ((*guard)->format,0,0,255));
    ///
    skull[UP] = IMG_Load("skull_up.bmp");
    SDL_SetColorKey(skull[UP], SDL_SRCCOLORKEY, SDL_MapRGB((*skull)->format, 0, 0, 255));
    skull[DOWN] = IMG_Load("skull_down.bmp");
    SDL_SetColorKey(skull[DOWN], SDL_SRCCOLORKEY, SDL_MapRGB((*skull)->format, 0, 0, 255));
    skull[RIGHT] = IMG_Load("skull_right.bmp");
    SDL_SetColorKey(skull [RIGHT], SDL_SRCCOLORKEY, SDL_MapRGB((*skull)->format, 0, 0, 255));
    skull[LEFT] = IMG_Load("skull_left.bmp");
    SDL_SetColorKey(skull[LEFT], SDL_SRCCOLORKEY, SDL_MapRGB((*skull)->format, 0, 0, 255));

                    /* IMAGE SKULL */
    skull[UP] = IMG_Load("skull_up.bmp");
    SDL_SetColorKey(skull[UP], SDL_SRCCOLORKEY, SDL_MapRGB((*skull)->format, 0, 0, 255));
    skull[DOWN] = IMG_Load("skull_down.bmp");
    SDL_SetColorKey(skull[DOWN], SDL_SRCCOLORKEY, SDL_MapRGB((*skull)->format, 0, 0, 255));
    skull[RIGHT] = IMG_Load("skull_right.bmp");
    SDL_SetColorKey(skull [RIGHT], SDL_SRCCOLORKEY, SDL_MapRGB((*skull)->format, 0, 0, 255));
    skull[LEFT] = IMG_Load("skull_left.bmp");
    SDL_SetColorKey(skull[LEFT], SDL_SRCCOLORKEY, SDL_MapRGB((*skull)->format, 0, 0, 255));

                    /* IMAGE DARUINA */
    daruina[UP]=IMG_Load("daruina1.bmp");
    SDL_SetColorKey(daruina[UP], SDL_SRCCOLORKEY, SDL_MapRGB((*daruina)->format,0,0,255));
    daruina[DOWN]=IMG_Load("daruina2.bmp");
    SDL_SetColorKey(daruina[DOWN], SDL_SRCCOLORKEY, SDL_MapRGB((*daruina)->format,0,0,255));
    daruina[RIGHT]=IMG_Load("daruina3.bmp");
    SDL_SetColorKey(daruina[RIGHT], SDL_SRCCOLORKEY, SDL_MapRGB((*daruina)->format,0,0,255));
    daruina[LEFT]=IMG_Load("daruina4.bmp");
    SDL_SetColorKey(daruina[LEFT], SDL_SRCCOLORKEY, SDL_MapRGB((*daruina)->format,0,0,255));

                    /* IMAGE GRANMA */
    granma[UP] = IMG_Load("granma_up.bmp");
    SDL_SetColorKey(granma[UP], SDL_SRCCOLORKEY, SDL_MapRGB((*granma)->format, 0, 0, 255));
    granma[DOWN] = IMG_Load("granma_down.bmp");
    SDL_SetColorKey(granma[DOWN], SDL_SRCCOLORKEY, SDL_MapRGB((*granma)->format, 0, 0, 255));
    granma[RIGHT] = IMG_Load("granma_right.bmp");
    SDL_SetColorKey(granma[RIGHT], SDL_SRCCOLORKEY, SDL_MapRGB((*granma)->format, 0, 0, 255));
    granma[LEFT] = IMG_Load("granma_left.bmp");
    SDL_SetColorKey(granma[LEFT], SDL_SRCCOLORKEY, SDL_MapRGB((*granma)->format, 0, 0, 255));

                    /* IMAGE KOUME */
    koume[UP] = IMG_Load("koume_up.bmp");
    SDL_SetColorKey(koume[UP], SDL_SRCCOLORKEY, SDL_MapRGB((*koume)->format, 0, 0, 255));
    koume[DOWN] = IMG_Load("koume_down.bmp");
    SDL_SetColorKey(koume[DOWN], SDL_SRCCOLORKEY, SDL_MapRGB((*koume)->format, 0, 0, 255));
    koume[RIGHT] = IMG_Load("koume_right.bmp");
    SDL_SetColorKey(koume [RIGHT], SDL_SRCCOLORKEY, SDL_MapRGB((*koume)->format, 0, 0, 255));
    koume[LEFT] = IMG_Load("koume_left.bmp");
    SDL_SetColorKey(koume[LEFT], SDL_SRCCOLORKEY, SDL_MapRGB((*koume)->format, 0, 0, 255));

                    /* IMAGE MAPLE */
    maple[UP] = IMG_Load("maple_up.bmp");
    SDL_SetColorKey(maple[UP], SDL_SRCCOLORKEY, SDL_MapRGB((*maple)->format, 0, 0, 255));
    maple[DOWN] = IMG_Load("maple_down.bmp");
    SDL_SetColorKey(maple[DOWN], SDL_SRCCOLORKEY, SDL_MapRGB((*maple)->format, 0, 0, 255));
    maple[RIGHT] = IMG_Load("maple_right.bmp");
    SDL_SetColorKey(maple[RIGHT], SDL_SRCCOLORKEY, SDL_MapRGB((*maple)->format, 0, 0, 255));
    maple[LEFT] = IMG_Load("maple_left.bmp");
    SDL_SetColorKey(maple [LEFT], SDL_SRCCOLORKEY, SDL_MapRGB((*maple)->format, 0, 0, 255));

                        /* IMAGE OLDMAN */
    oldman[UP] = IMG_Load("oldman_up.bmp");
    SDL_SetColorKey(oldman[UP], SDL_SRCCOLORKEY, SDL_MapRGB((*oldman)->format, 0, 0, 255));
    oldman[DOWN] = IMG_Load("oldman_down.bmp");
    SDL_SetColorKey(oldman[DOWN], SDL_SRCCOLORKEY, SDL_MapRGB((*oldman)->format, 0, 0, 255));
    oldman[RIGHT] = IMG_Load("oldman_right.bmp");
    SDL_SetColorKey(oldman [RIGHT], SDL_SRCCOLORKEY, SDL_MapRGB((*oldman)->format, 0, 0, 255));
    oldman[LEFT] = IMG_Load("oldman_left.bmp");
    SDL_SetColorKey(oldman[LEFT], SDL_SRCCOLORKEY, SDL_MapRGB((*oldman)->format, 0, 0, 255));

                        /* IMAGE NAYRU */
    nayru[UP] = IMG_Load("nayru_up.bmp");
    SDL_SetColorKey(nayru[UP], SDL_SRCCOLORKEY, SDL_MapRGB((*nayru)->format, 0, 0, 255));
    nayru[DOWN] = IMG_Load("nayru_down.bmp");
    SDL_SetColorKey(nayru[DOWN], SDL_SRCCOLORKEY, SDL_MapRGB((*nayru)->format, 0, 0, 255));
    nayru[RIGHT] = IMG_Load("nayru_right.bmp");
    SDL_SetColorKey(nayru [RIGHT], SDL_SRCCOLORKEY, SDL_MapRGB((*nayru)->format, 0, 0, 255));
    nayru[LEFT] = IMG_Load("nayru_left.bmp");
    SDL_SetColorKey(nayru[LEFT], SDL_SRCCOLORKEY, SDL_MapRGB((*nayru)->format, 0, 0, 255));

                        /* IMAGE SARIA */
    saria[UP] = IMG_Load("saria_up.bmp");
    SDL_SetColorKey(saria[UP], SDL_SRCCOLORKEY, SDL_MapRGB((*saria)->format, 0, 0, 255));
    saria[DOWN] = IMG_Load("saria_down.bmp");
    SDL_SetColorKey(saria[DOWN], SDL_SRCCOLORKEY, SDL_MapRGB((*saria)->format, 0, 0, 255));
    saria[RIGHT] = IMG_Load("saria_right.bmp");
    SDL_SetColorKey(saria [RIGHT], SDL_SRCCOLORKEY, SDL_MapRGB((*saria)->format, 0, 0, 255));
    saria[LEFT] = IMG_Load("saria_left.bmp");
    SDL_SetColorKey(saria[LEFT], SDL_SRCCOLORKEY, SDL_MapRGB((*saria)->format, 0, 0, 255));

                        /* IMAGE SHEIK */
    sheik[UP] = IMG_Load("sheik_up.bmp");
    SDL_SetColorKey(sheik[UP], SDL_SRCCOLORKEY, SDL_MapRGB((*sheik)->format, 0, 0, 255));
    sheik[DOWN] = IMG_Load("sheik_down.bmp");
    SDL_SetColorKey(sheik[DOWN], SDL_SRCCOLORKEY, SDL_MapRGB((*sheik)->format, 0, 0, 255));
    sheik[RIGHT] = IMG_Load("sheik_right.bmp");
    SDL_SetColorKey(sheik [RIGHT], SDL_SRCCOLORKEY, SDL_MapRGB((*sheik)->format, 0, 0, 255));
    sheik[LEFT] = IMG_Load("sheik_left.bmp");
    SDL_SetColorKey(sheik[LEFT], SDL_SRCCOLORKEY, SDL_MapRGB((*sheik)->format, 0, 0, 255));

                        /* IMAGE RUTO */
    ruto[UP] = IMG_Load("ruto_up.bmp");
    SDL_SetColorKey(ruto[UP], SDL_SRCCOLORKEY, SDL_MapRGB((*ruto)->format, 0, 0, 255));
    ruto[DOWN] = IMG_Load("ruto_down.bmp");
    SDL_SetColorKey(ruto[DOWN], SDL_SRCCOLORKEY, SDL_MapRGB((*ruto)->format, 0, 0, 255));
    ruto[RIGHT] = IMG_Load("ruto_right.bmp");
    SDL_SetColorKey(ruto [RIGHT], SDL_SRCCOLORKEY, SDL_MapRGB((*ruto)->format, 0, 0, 255));
    ruto[LEFT] = IMG_Load("ruto_left.bmp");
    SDL_SetColorKey(ruto[LEFT], SDL_SRCCOLORKEY, SDL_MapRGB((*ruto)->format, 0, 0, 255));

                        /* IMAGE RAURU */
    rauru[UP]=IMG_Load("rauru_anim1.bmp");
    SDL_SetColorKey(rauru[UP], SDL_SRCCOLORKEY, SDL_MapRGB((*rauru)->format,0,0,255));
    rauru[DOWN]=IMG_Load("rauru_anim2.bmp");
    SDL_SetColorKey(rauru[DOWN], SDL_SRCCOLORKEY, SDL_MapRGB((*rauru)->format,0,0,255));
    rauru[LEFT]=IMG_Load("rauru_anim3.bmp");
    SDL_SetColorKey(rauru[LEFT], SDL_SRCCOLORKEY, SDL_MapRGB((*rauru)->format,0,0,255));
    rauru[RIGHT]=IMG_Load("rauru_anim4.bmp");
    SDL_SetColorKey(rauru[RIGHT], SDL_SRCCOLORKEY, SDL_MapRGB((*rauru)->format,0,0,255));
}

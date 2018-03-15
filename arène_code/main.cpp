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
#include "constantes.h"

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
        //fprintf(stderr, "Erreur SDL_mixer : %s\n", Mix_GetError());
        exit(EXIT_FAILURE);
    }
    if(TTF_Init() == -1)
    {
        //fprintf(stderr, "Erreur TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        //fprintf(stderr, "Erreur SDL :%s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_WM_SetIcon(SDL_LoadBMP("icone-zelda.bmp"), NULL);
    screen = SDL_SetVideoMode(LARGEUR_FENETRE,HAUTEUR_FENETRE,COULEUR,SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (screen == NULL)
    {
        //fprintf(stderr, "Impossible de charger video : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_WM_SetCaption("The Legend Of Zelda: Battle Royale", NULL);
    menu = SDL_LoadBMP("score.bmp");
    positionMenu.x=0;
    positionMenu.y=0;
    SDL_BlitSurface(menu, NULL, screen, &positionMenu);
    intro = Mix_LoadMUS("intro_ost.flac");
    Mix_VolumeMusic(VOLUME);
    Mix_PlayMusic(intro, 1);
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
                        Mix_FreeMusic(intro);
                        continuer = play(screen);
                        break;
                    case SDLK_ESCAPE:
                        continuer = 0;
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
    int i = 0;
    Mix_AllocateChannels(4);
    for (i=0;i<4;i++)
    {
        Mix_Volume(i,VOLUME);
    }
    SDL_Surface *rauru[4] = {NULL},*ruto[4] = {NULL},*sheik[4] = {NULL},*saria[4] = {NULL},*nayru[4] = {NULL},*oldman[4] = {NULL},*maple[4] = {NULL},*koume[4] = {NULL},*granma[4] = {NULL},*daruina[4] = {NULL},*skull[4] = {NULL}, *guard[16] = {NULL}, *link[6] = {NULL}, *rupees[3] = {NULL}, *zelda[6] = {NULL}, *ganon[5] ={NULL},*vide = NULL, *wall = NULL, *linkNow = NULL, *background = NULL, *texte = NULL, *p_points = NULL, *ganonNow = NULL;
    TTF_Font *police = NULL, *police2 = NULL;
    Mix_Music *gerudo;
    Mix_Chunk *s_ruppes, *s_sword, *s_degat;
    Mix_AllocateChannels(4);
    SDL_Rect position, positionPlayer, positionGanon, positionBackground;
    SDL_Event event;
    positionBackground.x=0;
    positionBackground.y=0;
    int continuer = 1, j = 0, time = 0, lastTime = 0, stime = 0, mtime = 0, points = 0;
    char temps[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    char score[6] = {0,0,0,0,0,0};
    int maps[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};
    background = IMG_Load("arene_beta_13.bmp");
    setup_pictures(link, rupees,ganon, zelda, guard, skull,daruina,granma,koume,maple,oldman,nayru,saria,sheik,ruto,rauru);
    setup_map(maps);
    ganonNow = ganon[UP];
    linkNow = link[DOWN];
    police = TTF_OpenFont("triforce.ttf", 35);
    police2 = TTF_OpenFont("triforce.ttf", 15);
    SDL_Color couleurNoire = {0, 0, 0};
    SDL_Color couleurJaune = {255, 255, 0};
    positionPlayer.x = NB_BLOCS_LARGEUR / 6;
    positionPlayer.y = NB_BLOCS_HAUTEUR / 6 +20;
    positionGanon.x = LARGEUR_FENETRE / 2 - 50;
    positionGanon.y = HAUTEUR_FENETRE / 2 - 55;
    s_ruppes = Mix_LoadWAV("get_rupee.wav");
    s_sword = Mix_LoadWAV("link_sword1.wav");
    gerudo = Mix_LoadMUS("gerudo_ost.flac");
    s_degat = Mix_LoadWAV("degat.wav");
    Mix_VolumeMusic(VOLUME);
    Mix_PlayMusic(gerudo, -1);
    ///SDL_EnableKeyRepeat(20000, 20000);
    while (continuer)
    {
    SDL_PollEvent(&event);  ///SDL_WaitEvent
    switch(event.type)
    {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    continuer = 0;
                    break;
                case SDLK_UP:
                    linkNow = link[UP];
                    points += movePlayer(maps, &positionPlayer, UP, s_ruppes);
                    break;
                case SDLK_DOWN:
                    linkNow = link[DOWN];
                    points += movePlayer(maps, &positionPlayer, DOWN, s_ruppes);
                    break;
                case SDLK_RIGHT:
                    linkNow = link[RIGHT];
                    points += movePlayer(maps, &positionPlayer, RIGHT, s_ruppes);
                    break;
                case SDLK_LEFT:
                    linkNow = link[LEFT];
                    points += movePlayer(maps, &positionPlayer, LEFT, s_ruppes);
                    break;
              //  case SDLK_SPACE:
                //    linkNow = link[HIT];
                  //  Mix_PlayChannel(1, s_sword, 0);
                    //break;
                case SDLK_TAB:
                    if(Mix_PausedMusic() == 1)
                    {
                        Mix_ResumeMusic();
                    }
                    else
                    {
                        Mix_PauseMusic();
                    }
                    break;
            }
            break;
    }
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
    timer(temps,score,time,lastTime,stime,mtime,points);
    p_points = TTF_RenderText_Blended(police2, score, couleurJaune);
    texte = TTF_RenderText_Blended(police, temps, couleurNoire);
    position.x = positionPlayer.x * TAILLE_BLOC;
    position.y = positionPlayer.y * TAILLE_BLOC;
    SDL_BlitSurface(background, NULL, screen, &positionBackground);
    SDL_BlitSurface(linkNow, NULL, screen, &position);
    if (time%1==0)
    {
        points -= ganon_move(maps, &positionGanon, &positionPlayer, s_degat ,points);
        animation(screen, zelda, skull,daruina,granma,koume,maple,oldman,nayru,saria,sheik,ruto,rauru);
    }
    for (i = MINX ; i < MAXX ; i++)
    {
        for (j = MINY ; j < MAXY ; j++)
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
            }
        }
    }
    position.x = 1000;
    position.y = 25;
    SDL_BlitSurface(rupees[GREEN_RUPEE], NULL, screen, &position);
    position.x = 70;
    position.y = 25; //30
    SDL_BlitSurface(texte, NULL, screen, &position);
    position.x = 1025;
    position.y = 30;//78
    SDL_BlitSurface(p_points, NULL, screen, &position);
    position.x = positionGanon.x; //* TAILLE_BLOC;
    position.y = positionGanon.y; //* TAILLE_BLOC;
    SDL_BlitSurface(ganonNow, NULL, screen, &position);
    garde(screen,guard);
    SDL_Flip(screen);
    continuer = win(points, screen, gerudo);
    }
    SDL_EnableKeyRepeat(0, 0);
    SDL_FreeSurface(wall);
    SDL_FreeSurface(texte);
    SDL_FreeSurface(p_points);
    SDL_FreeSurface(vide);
    Mix_FreeChunk(s_sword);
    Mix_FreeChunk(s_ruppes);
    for (i = 0 ; i < 6 ; i++)
    {
        SDL_FreeSurface(link[i]);
    }
    TTF_CloseFont(police);
    TTF_Quit();
    Mix_PauseMusic();
    return 0;
}

/*
Fonction qui permet de charger toutes les images du dossier.
*/
void setup_pictures (SDL_Surface *link[6],SDL_Surface *rupees[3],SDL_Surface *ganon[5], SDL_Surface *zelda[6], SDL_Surface *guard[16], SDL_Surface *skull[4],SDL_Surface *daruina[4],SDL_Surface *granma[4],SDL_Surface *koume[4],SDL_Surface *maple [4],SDL_Surface *oldman[4],SDL_Surface *nayru[4],SDL_Surface *saria[4],SDL_Surface *sheik[4], SDL_Surface *ruto[4], SDL_Surface *rauru[4])
{
    link[UP] = IMG_Load("link_up.bmp");
    SDL_SetColorKey(link[UP], SDL_SRCCOLORKEY, SDL_MapRGB((*link)->format, 0, 0, 255));
    link[DOWN] = IMG_Load("link_down.bmp");
    SDL_SetColorKey(link[DOWN], SDL_SRCCOLORKEY, SDL_MapRGB((*link)->format, 0, 0, 255));
    link[RIGHT] = IMG_Load("link_right.bmp");
    SDL_SetColorKey(link[RIGHT], SDL_SRCCOLORKEY, SDL_MapRGB((*link)->format, 0, 0, 255));
    link[LEFT] = IMG_Load("link_left.bmp");
    SDL_SetColorKey(link[LEFT], SDL_SRCCOLORKEY, SDL_MapRGB((*link)->format, 0, 0, 255));
//    link[HIT] = IMG_Load("link_hit.bmp");
//   SDL_SetColorKey(link[HIT], SDL_SRCCOLORKEY, SDL_MapRGB((*link)->format, 0, 0, 255));
//    link[DOWN_ANIM] = IMG_Load("link_down_floor.bmp");
//    SDL_SetColorKey(link[DOWN_ANIM], SDL_SRCCOLORKEY, SDL_MapRGB((*link)->format, 0, 0, 255));
    ///
    rupees[GREEN_RUPEE] = IMG_Load("green_rupee.bmp");
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

/*
Fonction qui initialise la carte avec les rubis et les cases vides.
*/
void setup_map (int maps[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR])
{
    int i,j, nb = 0;
    for (i = MINX ; i < MAXX ; i++)
    {
        for (j = MINY ; j < MAXY ; j++)
        {
            nb = rand()%500;
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
                default:
                    maps[i][j]= VIDE;
                    break;
            }
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
    if (points < 10)
    {
        sprintf(score, "X 00%d",points);
    }
    else if (points < 100)
    {
        sprintf(score, "X 0%d",points);
    }
    else
    {
        sprintf(score, "X %d",points);
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
            if (position->y - 1 < MINY)
                break;

            position->y--;

            break;

        case DOWN:
            if (position->y + 1 >= MAXY)
                break;

            position->y++;

            break;

        case RIGHT:
            if (position->x + 1 >= MAXX)
                break;

            position->x++;

            break;

        case LEFT:
            if (position->x - 1 < MINX)
                break;

            position->x--;

            break;
    }

    aroundCase[0] = &maps[position->x][position->y];
    aroundCase[1] = &maps[position->x - 1][position->y];
    aroundCase[2] = &maps[position->x - 1][position->y - 1];
    aroundCase[3] = &maps[position->x][position->y - 1];

    for (i = 0; i < 4; i++)
    {
        if ((*aroundCase[i]) != VIDE)
        {
            currentCase = aroundCase[i];
            break;
        }
    }

    if (currentCase != NULL)
    {
        switch (*currentCase)
        {
            case GREEN_RUPEE:   bonus++; break;
            case BLUE_RUPEE:    bonus += BLUE_BONUS; break;
            case RED_RUPEE:     bonus += RED_BONUS; break;
        }

        (*currentCase) = VIDE;

        Mix_PlayChannel(1, s_ruppes, 0);
    }

    return bonus;
}


/*
Fonction qui permet à Ganon de se déplacer.
*/
int ganon_move(int maps[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR], SDL_Rect *positionGanon, SDL_Rect *positionPlayer, Mix_Chunk *s_degat, int malus)
{
    int x = positionPlayer->x * TAILLE_BLOC;
    int y = positionPlayer->y * TAILLE_BLOC;
    int i = 0, j = 0, decalx = positionGanon->x - x, decaly = positionGanon->y - y ;
    if (decalx > 0)
    {
        if (decalx>5)
        {
            positionGanon->x -= 5;
        }
        else
        {
            positionGanon->x -=decalx;
        }
    }
    else if (decalx < 0)
    {
        if (decalx > -5)
        {
            positionGanon->x +=decalx;
        }
        else
        {
            positionGanon->x += 5;
        }
    }
    if (decaly > 0)
    {
        if (decaly < 5)
        {
            positionGanon->y -=decaly;
        }
        else
        {
            positionGanon->y -= 5;
        }
    }
    else if (decaly < 0)
    {
        if (decaly > -5)
        {
            positionGanon->y +=decaly;
        }
        else
        {
            positionGanon->y += 5;
        }
    }
    decalx = positionGanon->x - x;
    decaly = positionGanon->y - y;
    if ((decalx == 0) && (decaly == 0))
    {
        positionGanon->x = LARGEUR_FENETRE / 2 - 50;
        positionGanon->y = HAUTEUR_FENETRE / 2 ;
        Mix_PlayChannel(1, s_degat, 1);
        Mix_PlayChannel(2, s_degat, 0);
        return 50;
    }
    return 0;
}


/*
Fonction qui détérmine quand il y a un vainqeur.
*/
int win(int points, SDL_Surface* screen, Mix_Music *gerudo)
{
    if (points > 99)
    {
        Mix_PauseMusic();
        int continuer = 1;
        char winner[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        TTF_Font *police = NULL;
        police = TTF_OpenFont("triforce.ttf", 45);
        SDL_Color couleurJaune = {255, 255, 0};
        SDL_Surface *background = NULL, *texte = NULL;
        SDL_Rect positionBackground, position;
        SDL_Event event;
        positionBackground.x = 0;
        positionBackground.y = 0;
        position.x = 110;
        position.y = 110;
        background = IMG_Load("score.bmp");
        sprintf(winner, "Link gagne avec %d",points);
        texte = TTF_RenderText_Blended(police, winner, couleurJaune);
        while (continuer)
        {
            SDL_PollEvent(&event);
            switch(event.type)
            {
                case SDL_QUIT:
                    continuer = 0;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_SPACE)
                    {
                        Mix_PauseMusic();
                        continuer = 0;
                        return 0;
                    }
            }
            SDL_BlitSurface(background, NULL, screen, &positionBackground);
            SDL_BlitSurface(texte, NULL, screen, &position);
            SDL_Flip(screen);
        }
    }
    else if (points < 0)
    {
        Mix_PauseMusic();
        Mix_FreeMusic(gerudo);
        Mix_Chunk *over;
        SDL_Delay(100);
        over = Mix_LoadWAV("game_overv2.wav");
        Mix_PlayChannel(2, over, 0);
        int continuer = 1;
        TTF_Font *police = NULL;
        police = TTF_OpenFont("triforce.ttf", 120);
        SDL_Color couleurJaune = {255, 255, 0};
        SDL_Surface *background = NULL, *texte = NULL;
        SDL_Rect positionBackground, position;
        SDL_Event event;
        positionBackground.x = 0;
        positionBackground.y = 0;
        position.x = LARGEUR_FENETRE / 2 - 200;
        position.y = HAUTEUR_FENETRE / 2;
        background = IMG_Load("score.bmp");
        texte = TTF_RenderText_Blended(police, "Link a perdu", couleurJaune);
        while (continuer)
        {
            SDL_PollEvent(&event);
            switch(event.type)
            {
                case SDL_QUIT:
                    continuer = 0;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_SPACE)
                    {
                        Mix_PauseMusic();
                        continuer = 0;
                        return 0;
                    }
            }
            SDL_BlitSurface(background, NULL, screen, &positionBackground);
            SDL_BlitSurface(texte, NULL, screen, &position);
            SDL_Flip(screen);
        }
    }
    return 1;
}

/*
Fonction qui gère les déplacements des pnjs. (pas du tout optimisé)
*/
void animation(SDL_Surface* screen, SDL_Surface *zelda[6], SDL_Surface *skull[4],SDL_Surface *daruina[4],SDL_Surface *granma[4],SDL_Surface *koume[4],SDL_Surface *maple [4],SDL_Surface *oldman[4],SDL_Surface *nayru[4],SDL_Surface *saria[4],SDL_Surface *sheik[4], SDL_Surface *ruto[4], SDL_Surface *rauru[4])
{
    static int tour = 0;
    SDL_Rect a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r;
    int x = 1197, y = 385, x1 = 1225, y2 = 387,boucle;
    for (boucle=0;boucle<2;boucle++)
    {
        a.x = x;
        a.y = y;
        b.x = x;
        b.y = y + ECART;
        c.x = x;
        c.y = y + 2*ECART;
        d.x = x;
        d.y = y + 3*ECART;
        e.x = x;
        e.y = y + 4*ECART;
        f.x = x;
        f.y = y + 5*ECART;
        g.x = x;
        g.y = y + 6*ECART;
        h.x = x;
        h.y = y + 7*ECART;
        ///
        i.x = x1;
        i.y = y2;
        j.x = x1;
        j.y = y2 + ECART;
        k.x = x1;
        k.y = y2 + 2*ECART;
        l.x = x1;
        l.y = y2 + 3*ECART;
        m.x = x1;
        m.y = y2 + 4*ECART;
        n.x = x1;
        n.y = y2 + 5*ECART;
        o.x = x1;
        o.y = y2 + 6*ECART;
        p.x = x1;
        p.y = y2 + 7*ECART;
        tour%= 4;
        SDL_BlitSurface(rauru[tour], NULL, screen, &a);
        SDL_BlitSurface(skull[tour], NULL, screen, &b);
        SDL_BlitSurface(daruina[tour], NULL, screen, &c);
        SDL_BlitSurface(granma[tour], NULL, screen, &d);
        SDL_BlitSurface(koume[tour], NULL, screen, &e);
        SDL_BlitSurface(maple[tour], NULL, screen, &f);
        SDL_BlitSurface(oldman[tour], NULL, screen, &g);
        SDL_BlitSurface(saria[tour], NULL, screen, &h);
        ///
        SDL_BlitSurface(nayru[tour], NULL, screen, &i);
        SDL_BlitSurface(oldman[tour], NULL, screen, &j);
        SDL_BlitSurface(maple[tour], NULL, screen, &k);
        SDL_BlitSurface(koume[tour], NULL, screen, &l);
        SDL_BlitSurface(granma[tour], NULL, screen, &m);
        SDL_BlitSurface(daruina[tour], NULL, screen, &n);
        SDL_BlitSurface(skull[tour], NULL, screen, &o);
        SDL_BlitSurface(sheik[tour], NULL, screen, &p);
        ///
        x = 35;
        y = 385;
        x1 = 60;
        y2 = 387;
        }
    if (SDL_GetTicks()%20==0)
    {
        tour++;
    }
}


/*
Fonction qui permet aux pnjs gardes de patrouiller autour de l'arène.
*/
void garde(SDL_Surface* screen, SDL_Surface *guard[16])
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
    if (SDL_GetTicks()%5==0)
    {
        if (tour%ANIM_DOWN3==0)
        {
            tour = ANIM_UP3;
        }
        tour++;
        y+=3;
    }
}

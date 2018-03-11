#ifndef DEF_CONSTANTES
#define DEF_CONSTANTES

#define COULEUR 32
#define CASE   10
#define TAILLE_BLOC         10
#define LARGEUR_FENETRE     1280
#define HAUTEUR_FENETRE     900
#define NB_BLOCS_LARGEUR    LARGEUR_FENETRE / TAILLE_BLOC
#define NB_BLOCS_HAUTEUR    HAUTEUR_FENETRE/ TAILLE_BLOC
#define MINY    TAILLE_BLOC*2 + 7
#define MINX    TAILLE_BLOC + 7
#define MAXY    NB_BLOCS_HAUTEUR - TAILLE_BLOC - 4
#define MAXX    NB_BLOCS_LARGEUR - TAILLE_BLOC - 8
#define VOLUME  5 //15
#define BLUE_BONUS  5
#define RED_BONUS   20
#define ECART 33

enum {UP, DOWN, LEFT, RIGHT,ANIM_UP1,ANIM_UP2,ANIM_UP3,ANIM_DOWN1,ANIM_DOWN2,ANIM_DOWN3,ANIM_LEFT1,ANIM_LEFT2,ANIM_LEFT3,ANIM_RIGHT1,ANIM_RIGHT2,ANIM_RIGHT3};
enum{GREEN_RUPEE,BLUE_RUPEE,RED_RUPEE,VIDE};
enum {VIDES, MUR,JOUEUR};
int play (SDL_Surface* screen);
int movePlayer (int maps[][NB_BLOCS_HAUTEUR], SDL_Rect *position, int direction, Mix_Chunk *s_ruppes);
void SDL_Delay(Uint32 ms);
Uint32 SDL_GetTicks(void);
int Mix_OpenAudio(int frequency, Uint16 format, int channels, int chunksize);
int Mix_PlayMusic(Mix_Music *music, int loops);
int ganon_move(int maps[][NB_BLOCS_HAUTEUR], SDL_Rect *positionGanon, SDL_Rect *positionLink, Mix_Chunk *s_degat, int points);
void setup_pictures (SDL_Surface *link[6],SDL_Surface *rupees[3],SDL_Surface *ganon[5], SDL_Surface *zelda[6], SDL_Surface *guard[16], SDL_Surface *skull[4],SDL_Surface *daruina[4],SDL_Surface *granma[4],SDL_Surface *koume[4],SDL_Surface *maple [4],SDL_Surface *oldman[4],SDL_Surface *nayru[4],SDL_Surface *saria[4],SDL_Surface *sheik[4], SDL_Surface *ruto[4], SDL_Surface *rauru[4]);
void setup_map (int maps[][NB_BLOCS_HAUTEUR]);
void timer (char temps[],char score[],int time,int lastTime,int stime,int mtime,int points);
int win (int points, SDL_Surface* screen, Mix_Music *gerudo);
void animation(SDL_Surface* screen, SDL_Surface *zelda[6], SDL_Surface *skull[4],SDL_Surface *daruina[4],SDL_Surface *granma[4],SDL_Surface *koume[4],SDL_Surface *maple [4],SDL_Surface *oldman[4],SDL_Surface *nayru[4],SDL_Surface *saria[4],SDL_Surface *sheik[4], SDL_Surface *ruto[4], SDL_Surface *rauru[4]);
void garde(SDL_Surface* screen, SDL_Surface *guard[16]);

#endif

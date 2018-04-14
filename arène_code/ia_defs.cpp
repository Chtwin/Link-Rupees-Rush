#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "constantes.h"
#define MAX_IA 99
int NB_PLAYER = 2; // calculé à la volée, ne pas modifier

int ia_1(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_2(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_3(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_4(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_5(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_6(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_7(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_8(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_9(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_10(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_11(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_12(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_13(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_14(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_15(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_16(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_17(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_18(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_19(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_20(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_21(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_22(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_23(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_24(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_25(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_26(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_27(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_28(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_29(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_30(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_31(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_32(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_33(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_34(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_35(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_36(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_37(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_38(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_39(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_40(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_41(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_42(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_43(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_44(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_45(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_46(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_47(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_48(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_49(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_50(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_51(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_52(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_53(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_54(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_30(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_31(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_32(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_33(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_34(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_35(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_36(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_37(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_38(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_39(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_40(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_41(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_42(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_43(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_44(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_45(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_46(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_47(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_48(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_49(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_50(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_51(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_52(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_53(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_54(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_55(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_56(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_57(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_58(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_59(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_60(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_61(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_62(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_63(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_64(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_65(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_66(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_67(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_68(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_69(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_70(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_71(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_72(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_73(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_74(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_75(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_76(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_77(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_78(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_79(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_80(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_81(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_82(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_83(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_84(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_85(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_86(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_87(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_88(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_89(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_90(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_91(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_92(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_93(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_94(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_95(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_96(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_97(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_98(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));
int ia_99(int maps_ia[][NB_BLOCS_HAUTEUR], int x, int y, int points, int item, int tours) __attribute__((weak));

// cf macro @a
ia_ptr IAS[MAX_IA] = {ia_1, ia_2, ia_3, ia_4, ia_5, ia_6, ia_7, ia_8, ia_9, ia_10, ia_11, ia_12, ia_13, ia_14, ia_15, ia_16, ia_17, ia_18, ia_19, ia_20, ia_21, ia_22, ia_23, ia_24, ia_25, ia_26, ia_27, ia_28, ia_29, ia_30, ia_31, ia_32, ia_33, ia_34, ia_35, ia_36, ia_37, ia_38, ia_39, ia_40, ia_41, ia_42, ia_43, ia_44, ia_45, ia_46, ia_47, ia_48, ia_49, ia_50, ia_51, ia_52, ia_53, ia_54, ia_55, ia_56, ia_57, ia_58, ia_59, ia_60, ia_61, ia_62, ia_63, ia_64, ia_65, ia_66, ia_67, ia_68, ia_69, ia_70, ia_71, ia_72, ia_73, ia_74, ia_75, ia_76, ia_77, ia_78, ia_79, ia_80, ia_81, ia_82, ia_83, ia_84, ia_85, ia_86, ia_87, ia_88, ia_89, ia_90, ia_91, ia_92, ia_93, ia_94, ia_95, ia_96, ia_97, ia_98, ia_99};

ia_ptr * get_ias (int *player_count) {
  fprintf(stdout, "count_ias()\n");
  int i;
  *player_count = 0;
  for (i = 0; i < MAX_IA; i++) {
    if (IAS[i]) {
      fprintf(stdout, "found ia_%d\n", i + 1);
      (*player_count)++;
    }
  }

  ia_ptr *ias = (ia_ptr*) malloc(sizeof(ia_ptr) * (*player_count));
  int current_player = 0;
  
  for (i = 0; i < MAX_IA; i++) {
    if (IAS[i]) {
      ias[current_player] = IAS[i];
      current_player++;
    }
  }

  return ias;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  int width;
  int height;
} rectangle;

int compare_scores(const void* score_a, const void* score_b){
  int a = *(int*)score_a;
  int b = *(int*)score_b;
  return a - b;
}

int compare_areas(const void* a, const void* b){
//primeiro converte os ponteiros para o tipo corrato
  rectangle* ra = (rectangle*)a;
  rectangle* rb = (rectangle*)b;
//depois calcule a area
  int area_a = (ra->width * ra->height);
  int area_b = (rb->width * rb->height);
//depois use o truque de subtracao
  return area_a - area_b;
}

int compare_names(const void* a, const void* b){
//Uma string e um ponteiro para um char, então os ponteiros utilizados são ponteiros para ponteiros
  char** sa = (char**)a;
  char** sb = (char**)b;
  return strcmp(*sa, *sb);
}

int compare_names_desc(const void* a, const void* b){
  compare_names(b, a);
}

int compare_scores_desc(const void* score_a, const void* score_b){
  compare_scores(score_b, score_a);
}

int compare_areas_desc(const void* a, const void* b){
  compare_areas(b, a);
}

int main(){

  int scores[] = {543, 323, 32, 5544, 11, 3, 112};
  int i;
//passe o array seu tamanho o tamanho de cada item e uma funcao que converte e compara 
  qsort(scores,7,sizeof(int),compare_scores_desc);
  puts("These are the scores in order: ");
  for(i = 0; i < 7; i++){
    printf("Score = %d\n", scores[i]);
  }

  char* names[]= {"Karen","Mark","Brett","Molly","Gabriel","Melissa"};
//passe o array seu tamanho o tamanho de cada item e uma funcao que converte e compara 
  qsort(names,6,sizeof(char*),compare_names_desc);
  puts("These are the names in order: ");
  for(i = 0; i < 6; i++){
    printf("%s\n", names[i]);
  }
}
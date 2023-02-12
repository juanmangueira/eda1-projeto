#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>


struct av{
    char data[8];
    int avaliacao;
    int total;
    double media;
};

typedef struct av review;

void selectionsort(review v[], int tam);
int hash(char ch);
char hash_inverso(int n);

int main(void){

    clock_t inicioT = clock();

    FILE *f;
    f = fopen("reviews.csv", "r");
    char s[100];
    int i, j, k;
    int lin, col, conta_aval;
    review *reviews;
    char ch1, ch2;
    char str[80];

    int matriz_avaliacoes[36][36];
    int matriz_total[36][36];

    for(i=0; i<36; i++)
        for(j=0; j<36; j++){
            matriz_avaliacoes[i][j] = -1;
            matriz_total[i][j] = 0;
        }


    fscanf(f, "%s", s);
    while(fscanf(f, "%s", s) != EOF){
        //printf(s);
        // encontra a posicao da primeira virgula da linha
        for(i=0; s[i] != ','; ++i);

        lin = hash(s[i-7]);
        col = hash(s[i-6]);


        if(matriz_avaliacoes[lin][col] == -1){

            //if(s[i+4] == '0')

            // if(s[strlen(s)-1] == '1'){
            //     matriz_avaliacoes[lin][col] = 1;
            // } else if(s[strlen(s)-1] == '2'){
            //     matriz_avaliacoes[lin][col] = 2;
            // }else if(s[strlen(s)-1] == '3'){
            //     matriz_avaliacoes[lin][col] = 3;
            // }else if(s[strlen(s)-1] == '4'){
            //     matriz_avaliacoes[lin][col] = 4;
            // } else{
            //     matriz_avaliacoes[lin][col] = 5;
            // }

            if(s[i-6] == '1'){
                matriz_avaliacoes[lin][col] = s[strlen(s)-1];
            } else if(s[i-6] == '2'){
                matriz_avaliacoes[lin][col] = s[strlen(s)-1];
            } else if(s[i-6] == '3'){
                matriz_avaliacoes[lin][col] = s[strlen(s)-1];
            } else if(s[i-6] == '4'){
                matriz_avaliacoes[lin][col] = s[strlen(s)-1];
            } else if(s[i-6] == '5'){
                matriz_avaliacoes[lin][col] = s[strlen(s)-1];
            } else if(s[i-6] == '6'){
                matriz_avaliacoes[lin][col] = s[strlen(s)-1];
            } else if(s[i-6] == '7'){
                matriz_avaliacoes[lin][col] = s[strlen(s)-1];
            }
        }
        else
            matriz_avaliacoes[lin][col] += s[strlen(s)-1] - '0';

        // contabiliza total avaliações
        matriz_total[lin][col]++;

    }
    fclose(f);




/*
    for(i=0; i<36; i++){
        for(j=0; j<36; j++)
            printf("%d ", matriz_total[i][j]);
        putchar('\n');
    }
*/

    conta_aval = 0;

    // contbiliza total de cias
    for(i=0; i<36; i++)
        for(j=0; j<36; j++)
            if(matriz_avaliacoes[i][j] != -1)
                conta_aval++;

    reviews = (review*) malloc(sizeof(review) * conta_aval);

    k = 0;

    clock_t inicioM = clock();

    for(i=0; i<36; i++)
        for(j=0; j<36; j++){
            if(matriz_avaliacoes[i][j] != -1){
                reviews[k].avaliacao = matriz_avaliacoes[i][j];
                reviews[k].total = matriz_total[i][j];
                reviews[k].media = (double)reviews[k].avaliacao/reviews[k].total;

                ch1 = hash_inverso(i);
                ch2 = hash_inverso(j);

                reviews[k].data[0] = ch1;
                reviews[k].data[1] = ch2;
                reviews[k].data[2] = '\0';

                k++;
            }
        }

    clock_t fimM = clock();

        for(i=0; i< conta_aval; i++){
            printf("%s_2022, avaliacoes: %d, total: %d, media: %lf\n", reviews[i].data,
                                                                reviews[i].avaliacao,
                                                                reviews[i].total,
                                                                reviews[i].media);
        }

        clock_t inicioSS = clock();

        selectionsort(reviews, conta_aval);

        clock_t fimSS = clock();

        putchar('\n');
        for(i=0; i< conta_aval; i++){
            printf("%s_2022, avaliacoes: %d, total: %d, media: %lf\n", reviews[i].data,
                                                                reviews[i].avaliacao,
                                                                reviews[i].total,
                                                                reviews[i].media);
        }

        f = fopen("saida.csv", "w");
        for(i=0; i< conta_aval; i++)
            fprintf(f, "%s,%lf\n", reviews[i].data, reviews[i].media);
        fclose(f);

    clock_t fimT = clock();

    double tempoT = (double)(fimT - inicioT) / CLOCKS_PER_SEC;
    double tempoM = (double)(fimM - inicioM) / CLOCKS_PER_SEC;
    double tempoSS = (double)(fimSS - inicioSS) / CLOCKS_PER_SEC;

    printf("\nTempo de execução: %fs\nTempo de média: %fs\nTempo de sort: %fs\n",tempoT, tempoM, tempoSS);

    return 0;
}


void selectionsort(review v[], int tam){
    int i, j, indice;
    double min;
    review tmp;

    for(i = 0; i<tam-1; ++i){

        min = v[i].media; indice = i;

        for(j=i+1; j<tam; ++j){
            if(v[j].media < min){
                min = v[j].media;
                indice = j;
            }
        }
        tmp = v[i];
        v[i] = v[indice];
        v[indice] = tmp;
    }
}

int hash(char ch){
    if(isalpha(ch))
        return ch - 'A';
    else
        return ch - '0' + 26;
}

char hash_inverso(int n){
    if(0 <= n && n <= 25)
        return n + 'A';
    else
        return n - 26 + '0';
}


//------------------------------------------------------

int verificarNumero(char *entrada) {
  int i;

  for (i = 0; entrada[i] != '\0'; i++){
    if (entrada[i] != '/' && !isdigit(entrada[i])){
      return 0;
    }
  }

  return 1;
}

int verificarData(char *entrada){
  const char substring[3] = "//";

  if (strstr(entrada, substring) != NULL){
    return 0;
  }

  int i = 0;
  long data[3];
  const char delimitador[2] = "/";
  char *token = strtok(entrada, delimitador);

  // Alimenta o vetor de inteiros
  while (token != NULL){
    data[i++] = strtol(token, NULL, 10);
    token = strtok(NULL, delimitador);
  }

  // Realize suas validações. Se alguma não for atingida, retorne '0'

  printf("Dia: %ld\n", data[0]);
  printf("Mes: %ld\n", data[1]);
  printf("Ano: %ld\n", data[2]);

  // Caso contrário, retorne '1'

  return 1;
}
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
    int i, j, k, l;
    char m[10];
    int lin, col, conta_aval, ano[4];
    review *reviews;
    char ch1, ch2;

    int matriz_avaliacoes[36][36];
    int matriz_total[36][36];

    for(i=0; i<36; i++)
        for(j=0; j<36; j++){
            matriz_avaliacoes[i][j] = -1;
            matriz_total[i][j] = 0;
        }


    fscanf(f, "%s", s);
    while(fscanf(f, "%s", s) != EOF){
        // encontra a posicao da primeira virgula da linha
        for(i=0; s[i] != ','; ++i);

        lin = hash(s[i-7]);
        col = hash(s[i-6]);
        ano[0] = hash(s[i-4] - 26);
        ano[1] = hash(s[i-3] - 26);
        ano[2] = hash(s[i-2] - 26);
        ano[3] = hash(s[i-1] - 26);



        if(matriz_avaliacoes[lin][col] == -1){

            if( s[i-6] == '1' || 
                s[i-6] == '2' || 
                s[i-6] == '3' || 
                s[i-6] == '4' ||
                s[i-6] == '5' || 
                s[i-6] == '6' || 
                s[i-6] == '7' || 
                s[i-6] == '8' ||
                s[i-6] == '9' || 
                (s[i-7] == '1' && s[i-6] == '0') || 
                (s[i-7] == '1' && s[i-6] == '1') || 
                (s[i-7] == '1' && s[i-6] == '2')){
                matriz_avaliacoes[lin][col] = s[strlen(s)-1];
            }
        }
        else
            matriz_avaliacoes[lin][col] += s[strlen(s)-1] - '0';

        // contabiliza total avaliações
        matriz_total[lin][col]++;

    }
    fclose(f);

    conta_aval = 0;

    // contbiliza avaliações a cada mes
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
                reviews[k].avaliacao = matriz_avaliacoes[i][j] - 48;
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
            printf("%s_%d%d%d%d, avaliacoes: %d, total: %d, media: %lf\n", reviews[i].data,
                                                                ano[0],
                                                                ano[1],
                                                                ano[2],
                                                                ano[3],
                                                                reviews[i].avaliacao,
                                                                reviews[i].total,
                                                                reviews[i].media);
        }

        clock_t inicioSS = clock();

        selectionsort(reviews, conta_aval);

        clock_t fimSS = clock();

        putchar('\n');
        for(i=0; i< conta_aval; i++){
            printf("%s_%d%d%d%d, avaliacoes: %d, total: %d, media: %lf\n", reviews[i].data,
                                                                ano[0],
                                                                ano[1],
                                                                ano[2],
                                                                ano[3],
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
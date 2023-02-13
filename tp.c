#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

#define QTD_MESES_ANO 12
#define TAMANHO_MAX_LINHA 25

struct av {
    char ano[5];
    char mes[3];
    int avaliacaoSoma;
    int total;
    double media;
};

typedef struct av avaliacaoMensal;

void selectionSortDesc(avaliacaoMensal avaliacoes[], int tam);

void escreverArquivoSaida(const avaliacaoMensal *reviews, int tam);

void imprimeDadosAvaliacoes(const avaliacaoMensal *reviews, int tam);

int main(void) {
    clock_t inicioT = clock();

    FILE *arquivoCSV = fopen("reviews.csv", "r");
    char linha[TAMANHO_MAX_LINHA];
    avaliacaoMensal *reviews;

    // aloca espaco para 12 revisoes, uma para cada mes do ano
    reviews = (avaliacaoMensal *) malloc(sizeof(avaliacaoMensal) * QTD_MESES_ANO);

    // descarta o cabecalho do CSV
    fgets(linha, TAMANHO_MAX_LINHA, arquivoCSV);
    while (fgets(linha, TAMANHO_MAX_LINHA, arquivoCSV) != NULL){
        // recupera substring até o caracter ','
        char *strTime = strtok(linha, ",");

        // recupera substring até o caracter ',' or fim de linha
        char *strRating = strtok(NULL, ",");
        int rating = atoi(strRating);

        // recupera substring do inicio até o caracter '-'
        char *strAno = strtok(strTime, "-");
        char *strMes = strtok(NULL, "-");
        int mes = atoi(strMes);

        // mes comeca do 1(janeiro) mas o index do array comeca do 0
        int index = mes - 1;

        strcpy(reviews[index].ano, strAno);
        strcpy(reviews[index].mes, strMes);

        reviews[index].avaliacaoSoma += rating;
        reviews[index].total++;
        reviews[index].media = (double) reviews[index].avaliacaoSoma / reviews[index].total;
    }
    for (int index = 0; index < QTD_MESES_ANO; index++){
        reviews[index].media = (double) reviews[index].avaliacaoSoma / reviews[index].total;
    }
    fclose(arquivoCSV);

    printf("Lista ordenada por mês(crescente): \n");
    imprimeDadosAvaliacoes(reviews, QTD_MESES_ANO);

    clock_t inicioOrdenacao = clock();
    // ordena as avaliacoes em ordem decrescente
    selectionSortDesc(reviews, QTD_MESES_ANO);
    clock_t fimOrdenacao = clock();

    putchar('\n');

    printf("Lista ordenada por media(decrescente): \n");
    imprimeDadosAvaliacoes(reviews, QTD_MESES_ANO);

    escreverArquivoSaida(reviews, QTD_MESES_ANO);

    clock_t fimT = clock();

    double tempoT = (double) (fimT - inicioT) / CLOCKS_PER_SEC;
    double tempoSS = (double) (fimOrdenacao - inicioOrdenacao) / CLOCKS_PER_SEC;

    printf("\nTempo de execução: %fs\nTempo de sort: %fs\n", tempoT, tempoSS);

    return 0;
}

void imprimeDadosAvaliacoes(const avaliacaoMensal *reviews, int tam) {
    for (int i = 0; i < tam; i++) {
        if (strcmp(reviews[i].ano, "") != 0) { // nao imprimir se o ano estiver vazio pq toda a struct estara vazia
            printf("%s_%s, avaliacoes: %d, soma: %d, media: %lf\n", reviews[i].ano, reviews[i].mes,
                   reviews[i].total,
                   reviews[i].avaliacaoSoma,
                   reviews[i].media);
        }
    }
}

void escreverArquivoSaida(const avaliacaoMensal *reviews, int tam) {
    FILE *arquivoCSV = fopen("saida.csv", "w");
    fprintf(arquivoCSV, "Mes,Avaliacao_Media\n");
    for (int i = 0; i < tam; i++) { // nao escreve linha se o ano estiver vazio pq toda a struct estara vazia
        if (strcmp(reviews[i].ano, "") != 0) {
            fprintf(arquivoCSV, "%s_%s,%lf\n", reviews[i].ano, reviews[i].mes, reviews[i].media);
        }
    }
    fclose(arquivoCSV);
}

void selectionSortDesc(avaliacaoMensal avaliacoes[], int tam) {
    int i, j, indice;
    double max;
    avaliacaoMensal tmp;

    for (i = 0; i < tam-1; ++i) {
        max = avaliacoes[i].media;
        indice = i;

        for (j = i + 1; j < tam; ++j) {
            if (avaliacoes[j].media > max) {
                max = avaliacoes[j].media;
                indice = j;
            }
        }
        tmp = avaliacoes[i];
        avaliacoes[i] = avaliacoes[indice];
        avaliacoes[indice] = tmp;
    }
}

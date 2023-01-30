#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000
#define MAX_FIELDS 100

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selectionSort(int arr[], int n) {
    int i, j, min_idx;
    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(&arr[min_idx], &arr[i]);
    }
}

int main() {
    char line[MAX_LINE_LENGTH];
    char *field;
    int fields[MAX_FIELDS];
    int field_count;

    FILE *fp = fopen("arquivo.csv", "r");
    if (fp == NULL) {
        perror("Não foi possível abrir o arquivo");
        return 1;
    }

    FILE *fp2 = fopen("arquivo_ordenado.csv", "w");
    if (fp2 == NULL) {
        perror("Não foi possível criar o arquivo de saída");
        return 1;
    }

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        field = strtok(line, ",");
        field_count = 0;
        while (field != NULL) {
            fields[field_count++] = atoi(field);
            field = strtok(NULL, ",");
        }

        selectionSort(fields, field_count);

        for (int i = 0; i < field_count; i++) {
            fprintf(fp2, "%d,", fields[i]);
        }
        fseek(fp2, -1, SEEK_CUR);
        fprintf(fp2, "\n");
    }

    fclose(fp);
    fclose(fp2);
    return 0;
}
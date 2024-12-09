#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Funcoes.h"
#define TAM 256
#define tam_maximo_linha 1000

void OrdenarStr(char string[TAM][TAM], int scont);
void Ordenaint(int num[], int intcont);
void OrdenaFloat(float num[], int fcont);
void OrdenaPonto(float ponto[TAM][2], float distancia[], int pcont);

int main()
{
    FILE *saida = fopen("L0Q2.out", "w");
    FILE *entrada = fopen("L0Q2.in", "r");



    if (entrada == NULL || saida == NULL)
    {
        printf("Erro ao abrir os arquivos.");
        return 0;
    }

    char *linha = malloc(sizeof(char) * tam_maximo_linha);

    while (fgets(linha, tam_maximo_linha, entrada) != NULL)
    {
        int i[TAM];
        int intcont = 0;
        float f[TAM];
        int fcont = 0;
        float ponto[TAM][2];
        float distancia[TAM];
        int pcont = 0;
        char string[TAM][TAM];
        int scont = 0;

        // char str[] = "maria 3 5 jose 3.15 -1 (7,9.7) 4";
        char *token = strtok(linha, " ");

        while (token != NULL)
        {
            if (isdigit(token[0]) || token[0] == '-')
            {
                if (strchr(token, '.') != NULL){
                    f[fcont] = atof (token);
                    //sscanf(token, "%f", &f[fcont]);
                    fcont++;
                }
                else
                { // integer
                    i[intcont] = atoi(token);
                    intcont++;
                }
            }
            else if (strchr(token, '(') != NULL)
            {                                                                  // 2D point
                sscanf(token, "(%f, %f)", &ponto[pcont][0], &ponto[pcont][1]); // x e y

                pcont++;
            }
            else
            { // string
                strcpy(string[scont], token);
                scont++;
            }
            token = strtok(NULL, " ");
        }

        OrdenarStr(string, scont);
        Ordenaint(i, intcont);
        OrdenaFloat(f, fcont);
        OrdenaPonto(ponto, distancia, pcont);

        fprintf(saida,"str:");
        for (int icont = 0; icont < scont; icont++)
            fputs(string[icont], saida);

        fprintf(saida, "int:");
        for (int icont = 0; icont < intcont; icont++)
            fprintf(saida, "%d", i[icont]);

        fprintf(saida, "float:");
        for (int icont = 0; icont < fcont; icont++)
            fprintf(saida, "%.2f", f[icont]);

        fprintf(saida, "p:");
        for (int icont = 0; icont < fcont; icont++)
            fprintf(saida, "(%.1f,%.1f)", ponto[icont][0], ponto[icont][1]);
            
    }
    
    fclose(entrada);
    fclose(saida);
    return 0;
}
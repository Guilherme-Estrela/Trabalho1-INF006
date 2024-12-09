#include <stdio.h> 
#include <string.h> 
#include <ctype.h>
#define TAM 256

void OrdenarStr(char str[TAM][TAM], int size) {
    int icont, jcont, min_idx;
    char temp[TAM];

    for (icont = 0; icont < size - 1; icont++) {
        min_idx = icont;
        for (jcont = icont + 1; jcont < size; jcont++) {
            if (strcmp(str[jcont], str[min_idx]) < 0) {
                min_idx = jcont;
            }
        }
        if (min_idx != icont) {
            strcpy(temp, str[icont]);
            strcpy(str[icont], str[min_idx]);
            strcpy(str[min_idx], temp);
        }
    }
}

void  Ordenaint (int num[], int intcont){
    int icont, aux, jcont;
    
    for (icont = 1; icont < intcont; icont++) {
         aux = num[icont];
        jcont = icont - 1; 

        while (jcont >= 0 && num[jcont] >  aux) {
            num[jcont + 1] = num[jcont];
            jcont--;
        }

        num[jcont + 1] =  aux;
    }
}

void  OrdenaFloat (float num[], int fcont){
    int icont, jcont;
    float aux;
    
    for (icont = 1; icont < fcont; icont++) {
         aux = num[icont];
        jcont = icont - 1; 

        while (jcont >= 0 && num[jcont] >  aux) {
            num[jcont + 1] = num[jcont];
            jcont--;
        }

        num[jcont + 1] =  aux;
    }
}

void OrdenaPonto (float ponto[TAM][2], float distancia[], int pcont){
    // Calculando a distância ao quadrado para cada ponto
    for (int icont = 0; icont < pcont; icont++) {
        distancia[icont] = (ponto[icont][0]*ponto[icont][0] + ponto[icont][1]*ponto[icont][1]);
    }

    // Algoritmo de ordenação por inserção
    int icont, jcont;
    float aux, paux[2];
    
    for (icont = 1; icont < pcont; icont++) {
        aux = distancia[icont];
        paux[0] = ponto[icont][0];
        paux[1] = ponto[icont][1];

        jcont = icont - 1; 

        while (jcont >= 0 && distancia[jcont] > aux) {
            distancia[jcont + 1] = distancia[jcont];
            ponto[jcont + 1][0] = ponto[jcont][0]; 
            ponto[jcont + 1][1] = ponto[jcont][1]; 
            jcont--;
        }

        distancia[jcont + 1] = aux;
        ponto[jcont + 1][0] = paux[0];
        ponto[jcont + 1][1] = paux[1];
    }
}

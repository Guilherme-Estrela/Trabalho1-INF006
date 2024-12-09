#include <stdio.h>
#include <math.h>

// Estrutura para representar um ponto
typedef struct {
    double x;
    double y;
} Ponto;

// Função para calcular a distância euclidiana de um ponto até a origem
double distancia_origem(Ponto p) {
    return sqrt(p.x * p.x + p.y * p.y);
}

// Função para calcular a distância euclidiana entre dois pontos
double distancia_entre_pontos(Ponto p1, Ponto p2) {
    return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

// Função para ordenar os pontos pela distância da origem utilizando Bubble Sort
void ordenar_pontos(Ponto pontos[], int n) {
    int i, j;
    Ponto temp;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (distancia_origem(pontos[i]) > distancia_origem(pontos[j])) {
                // Troca os pontos
                temp = pontos[i];
                pontos[i] = pontos[j];
                pontos[j] = temp;
            }
        }
    }
}

// Função para calcular a distância total entre os pontos consecutivos
double distancia_total(Ponto pontos[], int n) {
    double total = 0;
    for (int i = 1; i < n; i++) {
        total += distancia_entre_pontos(pontos[i - 1], pontos[i]);
    }
    return total;
}

// Função para calcular a distância do "atalho", entre o primeiro e o último ponto
double atalho(Ponto pontos[], int n) {
    return distancia_entre_pontos(pontos[0], pontos[n - 1]);
}

// Função para ler os pontos do arquivo
int ler_pontos(const char *nome_arquivo, Ponto pontos[]) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return -1;
    }

    char linha[1000];
    int i = 0;

    // Lê os pontos
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (sscanf(linha, "points") == 0) continue; // ignora a linha com "points"
        
        // Lê os pontos da linha
        char *token = strtok(linha, " ");
        while (token != NULL) {
            double x, y;
            if (sscanf(token, "(%lf,%lf)", &x, &y) == 2) {
                pontos[i].x = x;
                pontos[i].y = y;
                i++;
            }
            token = strtok(NULL, " ");
        }
    }
    
    fclose(arquivo);
    return i;
}

// Função para escrever a saída no arquivo
void escrever_saida(const char *nome_arquivo, Ponto pontos[], int n, double distancia_total, double distancia_atalho) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de saída.\n");
        return;
    }

    fprintf(arquivo, "points ");
    for (int i = 0; i < n; i++) {
        fprintf(arquivo, "(%.2lf,%.2lf) ", pontos[i].x, pontos[i].y);
    }
    fprintf(arquivo, "distance %.2lf shortcut %.2lf\n", distancia_total, distancia_atalho);

    fclose(arquivo);
}

int main() {
    Ponto pontos[100]; // Considera que o máximo de pontos é 100
    int n = ler_pontos("L0Q1.in", pontos);
    if (n == -1) return 1; // Erro ao ler o arquivo

    ordenar_pontos(pontos, n); // Ordena os pontos pela distância da origem

    double dist_total = distancia_total(pontos, n); // Calcula a distância total
    double dist_atalho = atalho(pontos, n); // Calcula a distância do atalho

    escrever_saida("L0Q1.out", pontos, n, dist_total, dist_atalho); // Escreve o arquivo de saída

    return 0;
}


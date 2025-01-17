#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define TAM 256
#define tam_maximo_linha 1000

typedef struct NodeC NodeC;
struct NodeC{
            int Key;
            NodeC *Proximo;
};   

typedef struct Node2 Node2;
struct Node2{
            int Key;
            Node2 *Anterior;
            Node2 *Proximo;
            NodeC* Lista;
};

int main()
{
    FILE *saida = fopen("L0Q3.out", "w");
    FILE *entrada = fopen("L0Q3.in", "r");



    if (entrada == NULL || saida == NULL)
    {
        printf("Erro ao abrir os arquivos.");
        return 0;
    }

    char *linha = malloc(sizeof(char) * tam_maximo_linha);

    while (fgets(linha, tam_maximo_linha, entrada) != NULL)
    {

        Node2* primeiro2 = (Node2*)malloc(sizeof(Node2));
        primeiro2 = NULL;
        int le = 0;
        int li = 0;

        char *token = strtok(linha, " ");// separa os starts
        
        while (token != NULL)
        {
            if (token == "LE"){
                le = 1;
                li - 0;
                continue;
            }
            else if (token == "LI"){
                li = 1;
                le = 0;
                continue;
            }

            int value = atoi(token);

            if (le == 1){
                InserirNode2(primeiro2, value);
            }
            if (li == 1){
                Node2* listagem = primeiro2;

                while (listagem != NULL)
                {
                    if (value <= listagem->Key + 0.99 && value >= listagem->Key)
                        inserirNodeCOrdenado(listagem->Lista, value);
                    listagem = listagem->Proximo;
                }
            }





        }
            Node2* listagemPai = primeiro2;
            fprintf(saida, "[");
            while (listagemPai != NULL)
            {
                fprintf(saida, "%d", listagemPai->Key);
                fprintf(saida, "(");

                NodeC* listagemC = listagemPai->Lista;

                while(listagemC != NULL)
                {
                    if (listagemC->Proximo != NULL)
                        fprintf(saida, "%d->", listagemC->Key);
                    else
                        fprintf(saida, "%d", listagemC->Key);

                    listagemC = listagemC->Proximo;
                }
                
                if (listagemPai->Proximo != NULL)
                    fprintf(saida, ")->");
                else
                    fprintf(saida, ")");

                listagemPai = listagemPai->Proximo;
            }
            fprintf(saida, "]");

            //fprintf(saida, "start ");
            //fprintf(saida, "%d ", start[icont].vets[jcont]);
    }
    
    fclose(entrada);
    fclose(saida);
    return 0;
}

Node2* CriarNode2 (int key){
    Node2* novo = (Node2*)malloc(sizeof(Node2));
    novo->Key = key;
    novo->Anterior = NULL;
    novo->Proximo = NULL;
    novo->Lista = NULL;
    
    return novo;
}

void InserirNode2 (Node2 **Primeiro2, int key){
    Node2* novo = CriarNode2(key);
    Node2* ultimo = *Primeiro2;

    if (*Primeiro2 == NULL)
        *Primeiro2 = novo;
    
    while (ultimo->Proximo != NULL){
        ultimo = ultimo->Proximo;
    }

    ultimo->Proximo = novo;
    novo->Anterior = ultimo;

}

NodeC* CriarNodeC (int key){
    NodeC* novo = (NodeC*)malloc(sizeof(NodeC));
    novo->Key = key;
    novo->Proximo = NULL;
    
    return novo;
}

void inserirNodeCOrdenado(NodeC** primeiroC, int valor) {
    Node2* node = criarNo(valor);
    
    // Se a lista estiver vazia, o novo nó é o único e aponta para ele mesmo
    if (*primeiroC == NULL) {
        *primeiroC = node;
        node->Proximo = node;
        return;
    }

    NodeC* atual = *primeiroC;
    NodeC* anterior = NULL;

    // Se o valor do novo nó é menor que o valor do primeiro nó
    if (valor <= atual->Key) {
        // Encontramos o lugar para inserir: antes do primeiro nó
        while (atual->Proximo != *primeiroC) {
            anterior = atual;
            atual = atual->Proximo;
        }
        // Inserindo no início, antes do nó que seria o primeiro
        node->Proximo = *primeiroC;
        anterior->Proximo = node;
        *primeiroC = node;
        return;
    }

    // Caso contrário, percorre a lista até encontrar o lugar certo
    while (atual->Proximo != *primeiroC && atual->Key < valor) {
        anterior = atual;
        atual = atual->Proximo;
    }

    // Inserindo o novo nó entre 'anterior' e 'atual'
    anterior->Proximo = node;
    node->Proximo = atual;
}
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Estrutura do no da arvore
typedef struct No No;
struct No{
    struct No* pai; // ponteiro para o pai
    int folha; // se 1, no eh folha. Caso contrario, 0

    // Vetores de tamanho 10: 4 para as letras A,C,G,T + 6 para simbolos finais
    int inicio[10]; // vetor que guarda a posicao, na palavra, da primeia letra da aresta
    int fim[10]; // vetor que guarda a posicao, na palavra, da ultima letra da aresta
    struct No* filhos[10]; // filhos do no
    int indicador[10]; // vetor indicador
    struct No* links[10]; // vetor link
};

// Posicao da letra/simbolo nos vetores
int converte_letra_posicao(char letra){
    switch(letra){
        case 'A': return 0;
        case 'C': return 1;
        case 'G': return 2;
        case 'T': return 3;
        case '!': return 4;
        case '"': return 5;
        case '#': return 6;
        case '$': return 7;
        case '%': return 8;
        case '&': return 9;
    }
}

// Letra/simbolo de cada posicao nos vetores
char converte_posicao_letra(int posicao){
    switch(posicao){
        case 0: return 'A';
        case 1: return 'B';
        case 2: return 'C';
        case 3: return 'D';
        case 4: return '!';
        case 5: return '"';
        case 6: return '#';
        case 7: return '$';
        case 8: return '%';
        case 9: return '&';
    }
}

int main(){
    // Vetor de folhas no tamanho da palavra a ser inserida + uma folha para a raiz
    No* folhas[6];

    // Folha 6 eh a raiz
    folhas[5] = (No*)malloc(sizeof(No));
    folhas[5]->pai = NULL;
    folhas[5]->folha = 0;
    for(int i=0;i<10;i++){
        folhas[5]->filhos[i] = NULL;
        folhas[5]->indicador[i] = 0;
        folhas[5]->links[i] = NULL;
    }

    // Demais folhas
    for(int i=0;i<5;i++){
        folhas[i] = (No*)malloc(sizeof(No));
        folhas[i]->pai = folhas[5];
        folhas[i]->folha = 1;
        for(int j=0;j<10;j++){
            folhas[i]->filhos[j] = NULL;
            folhas[i]->indicador[j] = 0;
            folhas[i]->links[j] = NULL;
        }
    }

    // Palavra basica, sem repeticao de letra
    char palavra[5] = "ACGT!";

    // Comeca algoritmo de Weiner
    int posicao;
    for(int i=strlen(palavra)-1;i>=0;i--){
        posicao = converte_letra_posicao(palavra[i]);

        int tamanho = 0;
        No* aux = folhas[i+1];
        while(aux->indicador[posicao] == 0 && aux->pai != NULL) aux = aux->pai;
        No* v = aux;
        while(aux->links[posicao] != NULL && aux->pai != NULL){
            tamanho += (aux->fim[posicao] - aux->inicio[posicao] + 1);
            aux = aux->pai;
        }
        No * vlinha = aux;

        if(v == vlinha && v == folhas[5]){
            folhas[5]->inicio[posicao] = i;
            folhas[5]->fim[posicao] = strlen(palavra);
            folhas[5]->filhos[posicao] = folhas[i];

            // Printando aresta criada
            for(int j=folhas[5]->inicio[posicao];j<folhas[5]->fim[posicao];j++) printf("%c", palavra[j]);
            printf("\n");
        }

        folhas[i]->indicador[posicao] = 1;
    }
    return 0;
}

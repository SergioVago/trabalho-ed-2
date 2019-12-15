#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Tamanho da palavra + 1
#define N 9
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
    // Vetor de nos
    No* nos[N];
    for(int i=0;i<N;i++) nos[i] = NULL;
    int no = 0;
    // Vetor de folhas no tamanho da palavra a ser inserida + uma folha para a raiz
    No* folhas[N];
    
    // Folha 6 eh a raiz
    folhas[N-1] = (No*)malloc(sizeof(No));
    folhas[N-1]->pai = NULL;
    folhas[N-1]->folha = 0;
    for(int i=0;i<10;i++){
        folhas[N-1]->filhos[i] = NULL;
        folhas[N-1]->indicador[i] = 0;
        folhas[N-1]->links[i] = NULL;
    }

    // Demais folhas
    for(int i=0;i<N-1;i++){
        folhas[i] = (No*)malloc(sizeof(No));
        folhas[i]->pai = folhas[N-1];
        folhas[i]->folha = 1;
        for(int j=0;j<10;j++){
            folhas[i]->filhos[j] = NULL;
            folhas[i]->indicador[j] = 0;
            folhas[i]->links[j] = NULL;
        }
    }

    // Palavra basica, sem repeticao de letra
    char palavra[8] = "AGGACTA!";

    // Comeca algoritmo de Weiner
    int posicao;
    for(int i=strlen(palavra)-1;i>=0;i--){
        posicao = converte_letra_posicao(palavra[i]);
        int tamanho = 0;

        No* aux = folhas[i+1];
        while(aux->indicador[posicao] == 0 && aux->pai != NULL){
            aux->indicador[posicao] = 1;
            aux = aux->pai;
        }
        No* v = aux;
        while(aux->links[posicao] != NULL && aux->pai != NULL){
            tamanho += (aux->fim[posicao] - aux->inicio[posicao] + 1);
            aux = aux->pai;
        }
        No * vlinha = aux;

        if(v == vlinha && v == folhas[N-1] && v->indicador[posicao] == 0){
            vlinha->inicio[posicao] = i;
            vlinha->fim[posicao] = strlen(palavra);
            vlinha->filhos[posicao] = folhas[i];

            // Printando aresta criada
            //for(int j=folhas[N-1]->inicio[posicao];j<folhas[N-1]->fim[posicao];j++) printf("%c", palavra[j]);
            //printf("\n");
        }

        else if(v == vlinha && v == folhas[N-1] && v->indicador[posicao] == 1){
            // Salva no z
            No* z = vlinha->filhos[posicao];

            // Cria no interno
            No* novoNo = (No*)malloc(sizeof(No));
            novoNo->pai = vlinha;
            novoNo->folha = 0;
            for(int j=0;j<10;j++){
                novoNo->indicador[j] = z->indicador[j];
                novoNo->links[j] = z->links[j];
            }

            // Separa aresta antiga
            int novaPosicao = converte_letra_posicao(palavra[vlinha->inicio[posicao]+1]);
            novoNo->inicio[novaPosicao] = vlinha->inicio[posicao] + 1;
            novoNo->fim[novaPosicao] = vlinha->fim[posicao];
            novoNo->filhos[novaPosicao] = z;
            z->pai = novoNo;

            // Cria nova aresta e folha
            novaPosicao = converte_letra_posicao(palavra[i+tamanho+1]);
            novoNo->inicio[novaPosicao] = i + tamanho + 1;
            novoNo->fim[novaPosicao] = strlen(palavra)-1;
            novoNo->filhos[novaPosicao] = folhas[i];
            folhas[i]->pai = novoNo;

            // Ajusta intervalo de vlinha
            vlinha->filhos[posicao] = novoNo;
            vlinha->fim[posicao] = vlinha->inicio[posicao] + tamanho;
            vlinha->links[posicao] = novoNo;
            
            // Guardando no criado
            nos[no] = novoNo;
            no++;         
        }

        // Atualizando indicadores
        aux = folhas[i+1];
        while(aux!=NULL){
            aux->indicador[posicao] = 1;
            aux = aux->pai;
        }
    }

    // Printando indicadores
    for(int i=0;i<N;i++){
        if(nos[i]!=NULL){
            printf("\nIndicadores do no criado: ");
            for(int j=0;j<10;j++) printf("%d ", nos[i]->indicador[j]);
            printf("\n"); 
        } 
    }

    // Printando indicadores
    printf("\nIndicadores:\n");
    for(int i=0;i<N;i++){
        printf("Folha %d: ", i+1);
        for(int j=0;j<10;j++){
            printf("%d ", folhas[i]->indicador[j]);
        }
        printf("\n");
    }

    // Printando links
    printf("\nLinks:\n");
    for(int i=0;i<N;i++){
        printf("Folha %d: ", i+1);
        for(int j=0;j<10;j++){
            printf("%p ", folhas[i]->links[j]);
        }
        printf("\n");
    }
    return 0;
}
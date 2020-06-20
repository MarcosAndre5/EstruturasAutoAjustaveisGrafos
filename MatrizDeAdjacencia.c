#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int tamanhoGrafo; 

void zerar_Matriz(int grafo[][tamanhoGrafo]);  /* Função para limpar o lixo dentro todas as posições da 
						  matriz colocando todas as posições com o valor zero.  */

void obter_arestas(int grafo[][tamanhoGrafo], int ligacoes, int aresta);  /* Essa função adiciona as adjacências da matriz depois
									     de receber a informação de que um vértice é 
									     adjacênte a outro vértice.  */

void imprimir_Matriz(int grafo[][tamanhoGrafo]);  // Essa função imprime a Matriz de Adjacências.

int main() {
    int i, j, ligacoes = 0, aresta = 0;
    
    setlocale(LC_ALL, "Portuguese");  // Função da biblioteca locale.h para aceitar caracteres usados no Brasil.
    
    printf("\t OBTENDO A MATRIZ DE ADJACÊNCIA\n\n");
    printf("- Informe a quantidade de vétices do Grafo: ");
    scanf("%d", &tamanhoGrafo);
    
    int grafo[tamanhoGrafo][tamanhoGrafo];
    
    zerar_Matriz(grafo);
    
    obter_arestas(grafo, ligacoes, aresta);
    
    printf("\n\n\t MATRIZ DE ADJACÊNCIA\n");
    imprimir_Matriz(grafo);
    
    system("pause");  /* Função para pausear a aplicação antes de finalizar. Pode ser utilizada apenas no Windows. 
    getchar();	         Em outros Sistemas Operacionais pode ser usado o getchar() para exercer a mesma atividade do
			 system("pause") no Windiows, no próprio Windows também pode ser usado o getchar()
			 ao invés do system("pause"). */
    return 0;
}


void zerar_Matriz(int grafo[][tamanhoGrafo]) {
	int i, j;
	
	for (i = 1; i <= tamanhoGrafo; i++) {
        	for (j = 1; j <= tamanhoGrafo; j++) {
            		grafo[i][j] = 0;
        	}
    	}
}

void obter_arestas(int grafo[][tamanhoGrafo], int ligacoes, int aresta) {
	int i, j;
	
	for (i = 1; i <= tamanhoGrafo; i++) {
        	printf("\n===========================\n");
        	printf("\nVértice %d tem quantas vizinhos? ", i);
        	scanf("%d", &ligacoes);
        	for (j = 1; j <= ligacoes; j++) {
            		printf("\n%dº vizinho do vértice %d: ", j, i );
            		scanf("%d", &aresta);
            		grafo[i][aresta]++;
        	}
	}
}

void imprimir_Matriz(int grafo[][tamanhoGrafo]) {
	int i, j;
	
	for (i = 1; i <= tamanhoGrafo; i++) {
        	for (j = 1; j <= tamanhoGrafo; j++) {
                	printf("  %d", grafo[i][j]);
        	}
        	printf("\n");
    	}
}

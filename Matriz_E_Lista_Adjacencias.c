#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

////////////////////////////////////////////////////
// FUNÇÕES PARA MANIPULAR A MATRIZ DE ADAJACÊNCIA //
////////////////////////////////////////////////////
int tamanhoGrafo;
void zerar_Matriz(int grafo[][tamanhoGrafo]) {//Função para limpar o lixo dentro todas as posições da matriz colocando todas as posições com o valor zero.
	int i, j;
	
	for (i = 1; i <= tamanhoGrafo; i++) {
        for (j = 1; j <= tamanhoGrafo; j++) {
            grafo[i][j] = 0;
        }
    }
}

void obter_arestas(int grafo[][tamanhoGrafo], int ligacoes, int aresta) {//Essa função adiciona as adjacências da matriz depois de receber a informação de que um vértice é adjacênte a outro vértice.
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

void imprimir_Matriz(int grafo[][tamanhoGrafo]) {  // Essa função imprime a Matriz de Adjacências.
	int i, j;
	
	for (i = 1; i <= tamanhoGrafo; i++) {
        for (j = 1; j <= tamanhoGrafo; j++) {
            printf("  %d", grafo[i][j]);
        }
        printf("\n");
    }
}


///////////////////////////////////////////////////
// FUNÇÕES PARA MANIPULAR A LISTA DE ADAJACÊNCIA //
///////////////////////////////////////////////////
struct art{  // Estrutura das arestas
	int dest;
	struct art *prox;
};

struct vet{  // Estrutura dos vértice
	int id;
	struct art *art;
	struct vet *prox;
};

struct vet *inserir_v(struct vet *grafo, int id){
	struct vet *novo;
	struct vet *p = grafo;
	
	if(grafo == NULL){  // Se for a primeira insençao
		novo = (struct vet*)malloc(sizeof(struct vet));
		novo->id = id;
		novo->art = NULL;
		novo->prox = NULL;
		
		return novo;
	}
	
	while(p->prox != NULL){  // Indo para o final da fila
		p = p->prox;
	}
	
	// Adicionando o novo vértice
	novo = (struct vet*)malloc(sizeof(struct vet));
	novo->id = id;
	novo->art = NULL;
	novo->prox = NULL;
	
	p->prox = novo;
	
	return grafo;
}

struct vet *remover_a(struct vet *grafo, int vet_1, int vet_2){
	struct vet *p=grafo;  // Percorre lista de vértices
	struct art *q, *artant;  // Percorre lista de arestas
	
	while(p->id != vet_1){ // Buscando vet_1
		p = p->prox;
	}
	q = p->art;
	
	while(q->dest != vet_2){
		artant = q;
		q = q->prox;
	}
	
	if(q == p->art){  // Caso a aresta seja a primeira da lista
		p->art = q->prox;
	}else{
		artant->prox = q->prox;
	}
	
	free(q);
	
	// Restaurando variáveis
	p = grafo;
	q = NULL;
	
	while(p->id != vet_2){  // Buscando vet_2
		p = p->prox;
	}
	q = p->art;
	
	while(q->dest != vet_1){
		artant = q;
		q = q->prox;
	}
	
	if(q == p->art){  // Caso a aresta seja a primeira da lista
		p->art = q->prox;
	}else{
		artant->prox = q->prox;
	}
	
	free(q);
	
	return grafo;
}

struct vet *remover_v(struct vet *grafo, int id){
	struct vet *vet_r=grafo;  // vet a ser removido
	struct vet *p=grafo;  // Pecorre lista de vértices
	struct art *q;  // Percorre lista de arestas
	struct vet *antvet;  // Variável para elemento anterior
	int idart=-1;
	
	while(vet_r->id != id){  // Encontrando vet
		antvet = vet_r;
		vet_r = vet_r->prox;
	}
	
	// Remove aresta das listas dos outros vértices
	while(p != NULL){
		q = p->art;
		while(q != NULL){
			if(q->dest == id){
				idart = q->dest;
			}
			q = q->prox;
			if(idart != -1){
				grafo = remover_a(grafo, p->id,id);
				idart = -1;
			}
		}
		p =p->prox;
	}
	
	// Removendo o vértice
	if(vet_r == grafo){  // Caso seja o primeiro da lista
		grafo = grafo->prox;
	}else{
		antvet->prox = vet_r->prox;	
	}
	
	free(vet_r);
	
	return grafo;
}

struct vet *inserir_a(struct vet *grafo, int vet_1, int vet_2){
	struct vet *p=grafo;  // Percorrer lista de vértices
	struct art *nova,*q;  // (q)Percorrer lista de arestas
	
	while(p->id != vet_1){  // Encontrando vet_1
		p = p->prox;
	}
	q = p->art;
	
	nova = (struct art*)malloc(sizeof(struct art));
	nova->dest = vet_2;
	if(q == NULL){  // Caso não possua arestas
		nova->prox = NULL;
		p->art = nova;
	}else{
		while(q->prox != NULL){
			q = q->prox;
		}
		
		q->prox = nova;
		nova->prox = NULL;
	}
	
	// Restarando variáveis
	p = grafo;
	q = nova = NULL;
	
	// Alocando arestas no vértice 2
	while(p->id != vet_2){  // Encontrando vet_2
		p = p->prox;
	}
	q = p->art;
	
	nova = (struct art*)malloc(sizeof(struct art));
	nova->dest = vet_1;
	if(q == NULL){  // Caso não possua arestas
		nova->prox = NULL;
		p->art = nova;
	}else{
		while(q->prox != NULL){
			q = q->prox;
		}
		
		q->prox = nova;
		nova->prox = NULL;
	}
	
	return grafo;
}

void exibir(struct vet *grafo){
	struct art *p;
	
	if(grafo == NULL){
		printf("Lista Vazia.\n\n");
		return;
	}
	printf("Lista de Adjacência\n\n");
	
	while(grafo != NULL){
		printf("%d| ",grafo->id);
		p = grafo->art;
		while(p != NULL){
			printf("->%d ", p->dest);
			p = p->prox;
		}
		printf("\n");
		grafo = grafo->prox;
	}
	printf("----------------\n\n");	
}

////////////////////////
/// FUNÇÃO PRINCIPAL ///
////////////////////////

int main () {
	int opcao = 0;

	setlocale(LC_ALL, "Portuguese");  // Função da biblioteca locale.h para aceitar caracteres usados no Brasil.
	
	do {
		printf("\t TRABALHO DE GRAFOS\n\n");
		printf("Matriz de Adjacência e Lista de Adjacência\n\n");
		printf("Escolha qual das opções abaixo você deseja:\n");
		printf("- Digite '1' para Matriz de Adjacência\n");
		printf("- Digite '2' para Lista de Adjacência\n\n");
		scanf("%d", &opcao);
		
		if (opcao == 1) {
			
			int i, j, ligacoes = 0, aresta = 0;
		    
		    printf("\n----- Representacao de Grafos com Matriz de Adjacencia -----\n\n");
			printf("\t Desenvolvedores: Althierfson Tullio e Marcos André.\n\n");
		    printf("- Informe a quantidade de vértices do Grafo: ");
		    scanf("%d", &tamanhoGrafo);
		    
		    int grafo[tamanhoGrafo][tamanhoGrafo];
		    
		    zerar_Matriz(grafo);
		    
		    obter_arestas(grafo, ligacoes, aresta);
		    
		    printf("\n\n\t MATRIZ DE ADJACÊNCIA\n");
		    imprimir_Matriz(grafo);
		    
		    system("pause");
			
		} else if (opcao == 2) {
			
			struct vet *grafo=NULL;
			int ctr, vet, vet1;
			
			printf("\n----- Representacao de Grafos com Lista de Adjacencia -----\n\n");
			printf("\t Desenvolvedores: Althierfson Tullio e Marcos André.");
			do{
				printf("\n\n-- Lista de Adjacencia --\n\n");
				printf("\t -- Menu --\n1 - Adiciona Vértice\n2 - Adiciona Aresta\n3 - Remover Vértice\n4 - Remover Aresta\n5 - Exibir Lista\n6 - Sair do Programa\n\n");
				
				printf("Escolhar:");
				scanf("%d", &ctr);
				
				switch(ctr){
					case 1:
						printf("Digite o nome do vértice:");
						scanf("%d", &vet);
						
						grafo = inserir_v(grafo, vet);
						system("cls");
						printf("Vértice inserido com sucesso.\n\n");
						break;
					case 2:
						printf("Digite os vértices que receberam a aresta:\n");
						printf("Primeiro:"); scanf("%d", &vet);
						printf("Segundo:"); scanf("%d", &vet1);
						
						grafo = inserir_a(grafo, vet, vet1);
						system("cls");
						printf("Aresta inserida com sucesso.\n\n");
						break;
					case 3:
						printf("Digite o nome do vértice:");
						scanf("%d", &vet);
						
						grafo = remover_v(grafo, vet);
						system("cls");
						printf("Vértice removido com sucesso.\n\n");
						break;
					case 4:
						printf("Digite os vértices que terão a aresta removida:\n");
						printf("Primeiro:"); scanf("%d", &vet);
						printf("Segundo:"); scanf("%d", &vet1);
						
						grafo = remover_a(grafo, vet, vet1);
						system("cls");
						printf("Aresta removida com susseco.\n\n");
						break;
					case 5:
						system("cls");
						exibir(grafo);
						break;
					case 6:
						break;
				}
			}while(ctr < 6);	
				
		} else {
			printf("\n\nEssa opcão é Inválida!\n\n Tente Novamente.\n\n");
			system("pause");
			system("cls");
		}
	} while (opcao < 1 || opcao > 2);
	
	return 0;
}

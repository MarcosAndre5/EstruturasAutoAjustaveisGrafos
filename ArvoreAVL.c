#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "ArvoreAVL.h"

int main(){
	struct no *arvore = NULL;
	int i = 0, qtd_nos = 0, elemento = 0, opcao = 0;
	
	setlocale(LC_ALL, "Portuguese");
	
	printf("\t ÁRVORE BINARIA DE BUSCA\n\n");
	
	printf("Quantos elementos você deseja inserir na árvore? ");
	scanf("%d", &qtd_nos);
				
	for (i = 0; i < qtd_nos; i++) {
		printf("\n\n- Insira o %dº elemento na Árvore: ", i + 1);
		scanf("%d", &elemento);
		
		arvore = inserirNo(arvore, elemento);
		arvore = controle(arvore);
	}
	
	system("pause");
			
	printf("\n\n================================\n\n");
	
	printf("Árvore sendo percorrida em Pré-Ordem\n\n");			
	exibir_Pre_Ordem(arvore);
	
	printf("\n\n================================\n\n");
	
	printf("Árvore sendo percorrida em Ordem\n\n");
	exibir_Em_Ordem(arvore);
	
	printf("\n\n================================\n\n");
	
	printf("Árvore sendo percorrida em Pós-Ordem\n\n");
	exibir_Pos_Ordem(arvore);
	
	printf("\n\n================================\n\n");
	
	printf("\tRemoção de elementos\n\n");
	
	printf("Quantos elementos você deseja remover da árvore? ");
	scanf("%d", &qtd_nos);
				
	for (i = 0; i < qtd_nos; i++) {	
		printf("\n- Digite o elemento a ser removido da Árvore: ", i + 1);
		scanf("%d", &elemento);
		
		arvore = removerNo(arvore, elemento);
		arvore = controle(arvore);
	}
	
	system("pause");
	
	printf("\n\n================================\n\n");
	
	printf("Árvore sendo percorrida em Pré-Ordem\n\n");			
	exibir_Pre_Ordem(arvore);
	
	printf("\n\n================================\n\n");
	
	printf("Árvore sendo percorrida em Ordem\n\n");
	exibir_Em_Ordem(arvore);
	
	printf("\n\n================================\n\n");
	
	printf("Árvore sendo percorrida em Pós-Ordem\n\n");
	exibir_Pos_Ordem(arvore);
	
	printf("\n\n================================\n\n");
	
	return 0;
}

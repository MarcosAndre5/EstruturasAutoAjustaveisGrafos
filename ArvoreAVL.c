#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "ArvoreAVL.h"

int main(){
	struct no *arvore = NULL;
	int i = 0, qtd_nos = 0, elemento = 0, opcao = 0;
	
	setlocale(LC_ALL, "Portuguese");
	
	printf("\t �RVORE BINARIA DE BUSCA\n\n");
	
	printf("Quantos elementos voc� deseja inserir na �rvore? ");
	scanf("%d", &qtd_nos);
				
	for (i = 0; i < qtd_nos; i++) {
		printf("\n\n- Insira o %d� elemento na �rvore: ", i + 1);
		scanf("%d", &elemento);
		
		arvore = inserirNo(arvore, elemento);
		arvore = controle(arvore);
	}
	
	system("pause");
			
	printf("\n\n================================\n\n");
	
	printf("�rvore sendo percorrida em Pr�-Ordem\n\n");			
	exibir_Pre_Ordem(arvore);
	
	printf("\n\n================================\n\n");
	
	printf("�rvore sendo percorrida em Ordem\n\n");
	exibir_Em_Ordem(arvore);
	
	printf("\n\n================================\n\n");
	
	printf("�rvore sendo percorrida em P�s-Ordem\n\n");
	exibir_Pos_Ordem(arvore);
	
	printf("\n\n================================\n\n");
	
	printf("\tRemo��o de elementos\n\n");
	
	printf("Quantos elementos voc� deseja remover da �rvore? ");
	scanf("%d", &qtd_nos);
				
	for (i = 0; i < qtd_nos; i++) {	
		printf("\n- Digite o elemento a ser removido da �rvore: ", i + 1);
		scanf("%d", &elemento);
		
		arvore = removerNo(arvore, elemento);
		arvore = controle(arvore);
	}
	
	system("pause");
	
	printf("\n\n================================\n\n");
	
	printf("�rvore sendo percorrida em Pr�-Ordem\n\n");			
	exibir_Pre_Ordem(arvore);
	
	printf("\n\n================================\n\n");
	
	printf("�rvore sendo percorrida em Ordem\n\n");
	exibir_Em_Ordem(arvore);
	
	printf("\n\n================================\n\n");
	
	printf("�rvore sendo percorrida em P�s-Ordem\n\n");
	exibir_Pos_Ordem(arvore);
	
	printf("\n\n================================\n\n");
	
	return 0;
}

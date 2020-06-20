#include <stdio.h>
#include <stdlib.h>

struct no{
	int elemento, fator;
	struct no *direita;
	struct no *esquerda;
};

struct no* inserirNo(struct no *arvore, int elemento) {
	struct no *buscarNo = arvore;
	struct no *novo;
	int procurar = 0;
	
	novo = (struct no*) malloc (sizeof (struct no));
	novo -> elemento = elemento;
	novo -> fator = 0;
	novo -> direita = NULL;
	novo -> esquerda = NULL;
	
	if(buscarNo != NULL) {	// Começando rotina de buscar de posicionamento do novo nó
		while(procurar == 0) {
			if(novo -> elemento != buscarNo -> elemento) {	
				if(novo -> elemento > buscarNo -> elemento) {	
					if(buscarNo -> direita == NULL) {	
						procurar = 1;
					} else {
						buscarNo = buscarNo -> direita;	
					}
				} else {		
					if(buscarNo -> esquerda == NULL) {	
						procurar = -1;
					} else {	
						buscarNo = buscarNo -> esquerda;
					}
				}
			} else {
				printf("\n\n\tO elemento %d NÃO foi inserido pois já existe na árvore!\n", elemento);
				procurar = 2;
			}
		}
	}
	switch(procurar) {	// Posicionamento de novo elemento
		case 0:
			return novo;
			break;
		case -1:
			buscarNo -> esquerda = novo;
			break;
		case 1:
			buscarNo -> direita = novo;
			break;
		default:
			break;
	}
	return arvore;
}

void exibir_Pre_Ordem(struct no *arvore) {
	
	if(arvore != NULL) {	
		printf("%d ", arvore -> elemento);
		
		exibir_Pre_Ordem(arvore -> esquerda);
		exibir_Pre_Ordem(arvore -> direita);
	}
}

void exibir_Pos_Ordem(struct no *arvore){
	
	if(arvore != NULL){
		exibir_Pos_Ordem(arvore -> esquerda);
		exibir_Pos_Ordem(arvore -> direita);
		
		printf("%d ", arvore -> elemento);
	}
}

void exibir_Em_Ordem(struct no *arvore) {
	if(arvore != NULL) {
		exibir_Em_Ordem(arvore -> esquerda);
		
		printf("%d ", arvore -> elemento);
		
		exibir_Em_Ordem(arvore -> direita);
	}
}

struct no* removerNo(struct no *arvore, int elemento) {
	struct no *buscarNo = arvore;
	struct no *pai = NULL;
	struct no *m_esq, *p_m_esq = NULL;	
	 
	while(buscarNo != NULL && buscarNo -> elemento != elemento) { 	// Buscando Nó
			
		pai = buscarNo;
		
		if(elemento > buscarNo -> elemento) {
			buscarNo = buscarNo -> direita;
		} else {
			buscarNo = buscarNo -> esquerda;
		}
	}
	
	if(buscarNo == NULL) {
		printf("\n\nElemento não existe na arvore!\n\n");
		return arvore;
	} else {
		printf("\n\nElemento removido com sucesso!\n\n");
	}
	
	if(buscarNo -> direita != NULL && buscarNo -> esquerda != NULL) {	// Remover Nó e atualiza arvore
		
		m_esq = buscarNo -> direita;	// Nó com dois filhos
		
		while(m_esq -> esquerda != NULL) {	
			p_m_esq = m_esq;
			m_esq = m_esq -> esquerda;
		}
		
		if(pai != NULL) {
			if(pai -> elemento > buscarNo -> elemento) {
				pai -> esquerda = m_esq;
			} else {
				pai -> direita = m_esq;
			}	
		} else {
			arvore = m_esq;
		}
		
		if(p_m_esq == NULL) {
			m_esq -> esquerda = buscarNo -> esquerda;
		} else {
			p_m_esq -> esquerda = m_esq -> direita;
			m_esq -> direita = buscarNo -> direita;
			m_esq -> esquerda = buscarNo -> esquerda;
		}
	} else {	
		if(buscarNo -> direita != NULL || buscarNo -> esquerda != NULL) {
			if(pai != NULL) {
				if(pai -> elemento > buscarNo -> elemento) {
					if(buscarNo -> direita != NULL) {
						pai -> esquerda = buscarNo -> direita;
					} else {	
						pai -> esquerda = buscarNo -> esquerda;
					}
				} else {	
					if(buscarNo -> direita != NULL) {
						pai -> direita = buscarNo -> direita;
					} else {	
						pai -> direita = buscarNo -> esquerda;
					}
				}
			} else {	
				if(buscarNo -> direita != NULL) {
					arvore = buscarNo -> direita;
				} else {	
					arvore = buscarNo -> esquerda;
				}
			}
		} else {	
			if(pai == NULL) {
				arvore = NULL;
			} else {	
				if(pai -> elemento > buscarNo -> elemento) {
					pai -> esquerda = NULL;
				} else {
					pai -> direita = NULL;
				}
			}
		}
	}
	free(buscarNo);
	
	return arvore;
}

int calcular_Fator(struct no *arvore) {	// Funçoes de balaceamento
	if(arvore != NULL){	
		int arvore_Direita = 0, arvore_Esquerda = 0;
		
		arvore_Esquerda = calcular_Fator(arvore -> esquerda) + 1;
		arvore_Direita = calcular_Fator(arvore -> direita) + 1;
	
		arvore -> fator = arvore_Esquerda - arvore_Direita;
		
		if(arvore_Direita >= arvore_Esquerda) {
			return arvore_Direita;
		} else {
			return arvore_Esquerda;
		}	
	}
	return 0;
}

struct no* rotacao_Direita(struct no *arvore) {
	struct no *finho;
	int i = 0;
	
	finho = arvore -> esquerda;
	finho -> direita = arvore;
	arvore -> esquerda = NULL;
		
	return finho;
}

struct no* rotacao_Esquerda(struct no *arvore) {
	struct no *finho;
	
	finho = arvore -> direita;
	finho-> esquerda = arvore;
	arvore -> direita = NULL;
	
	return finho;
}

struct no *dupla_Rotacao_Direita(struct no *arvore) {
	arvore -> esquerda = rotacao_Esquerda(arvore -> esquerda);
	return rotacao_Direita(arvore);
}

struct no* dupla_Rotacao_Esquerda(struct no *arvore) {
	arvore -> direita = rotacao_Direita(arvore -> direita);
	return rotacao_Esquerda(arvore);
}

struct no* buscardesb(struct no *arvore) {
	if(arvore != NULL) {
		if(arvore -> fator == 2) {
			if(arvore -> esquerda -> fator == 2) {
				arvore -> esquerda = buscardesb(arvore -> esquerda);
			} else {
				if(arvore -> esquerda -> fator == 1) {
					printf("\n\nRotacao a direita em %d.\n\n", arvore -> elemento);
					return rotacao_Direita(arvore);
				} else {
					printf("\n\nRotacao a dupla a direita em %d.\n\n", arvore -> elemento);
					return dupla_Rotacao_Direita(arvore);
				}
			}
		}
		if(arvore -> fator == -2) {
			if(arvore -> direita -> fator == -2) {
				arvore -> direita = buscardesb(arvore -> direita);
			} else {
				if(arvore -> direita -> fator == -1) {
					printf("\n\nRotacao a esquerda em %d.\n\n", arvore -> elemento);
					return rotacao_Esquerda(arvore);
				} else {
					printf("\n\nRotacao dupla a esquerda em %d.\n\n", arvore -> elemento);
					return dupla_Rotacao_Esquerda(arvore);
				}
			}
		}
		calcular_Fator(arvore);
		arvore -> esquerda = buscardesb(arvore -> esquerda);
		arvore -> direita = buscardesb(arvore -> direita);
		
		return arvore;
	}
	return NULL;
}

struct no* controle(struct no *arvore) {
	calcular_Fator(arvore);
	arvore = buscardesb(arvore);
	return arvore;
}

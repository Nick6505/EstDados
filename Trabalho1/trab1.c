#include <stdio.h>
#include <stdlib.h>
//TRABALHO 1 DE ESTRUTURA DE DADOS

//Fun��o que vai juntar os vetores e ordenalos
void merge(int *vetor, int inicio, int meio, int fim){
	int *aux;
	int pos1, pos2, tamanho, i, j, k;
	int fim1 = 0, fim2 = 0;
	//pega o tamanho total do vetor
	tamanho = fim - inicio + 1;
	//posicao inicial
	pos1 = inicio;
	//posicao final
	pos2 = meio+1;
	aux = (int *) malloc(tamanho * sizeof(int)); //aloca o tamanho do vetor em um vetor tempor�rio auxiliar
	if (aux != NULL){ //verifica se o vetor � nulo
	//faz um loop do inicio ao fim do vetor
		for (i=0; i< tamanho; i++){ ;
		//verifica se j� chegou ao final dos dois vetores que est�o sendo unidos e ordenados
			if(!fim1 && !fim2){
				//verifica qual valor � menor
				//se a pos1 for menor, aloca ela primeiro no vetor tempor�rio vazio
				if(vetor[pos1] < vetor[pos2]){
				
					aux[i]= vetor[pos1++];
				//se a pos2 for menor, aloca ele primeiro
				}else{
					aux[i]= vetor[pos2++];
				//verifica se o primeiro vetor chegou no fim
				//se sim, vai de 0 para 1	
				}if(pos1 > meio){
					fim1 = 1;
				//verifica se j� chegou no fim do segundo vetor
				//se sim, vai de 0 para 1
				}if(pos2 > fim){
				
					fim2 = 1;
				}
			//se n�o chegou ao fim dos vetores, verifica qual dos dois ainda falta alocar os valores
			}else { 
				if(!fim1)
					aux[i] = vetor[pos1++];
				else
					aux[i] = vetor[pos2++];
			}
		}
		//ordena os valores no vetor original que est� em ponteiro
		for(j=0,k=inicio; j<tamanho; j++,k++){
			vetor[k] = aux[j];
		}
	}
	//Libera o aux
	free(aux); 
	
}

//Fun��o sort, fun��o recursiva que vai se chamar at� poder chamar a fun��o merge
void sort(int *vetor, int inicio, int final){
	int metade;
	//verifica se cada vetor tem 1 elemento
	if(inicio < final){
		metade = (inicio+final)/2; //divide o vetor no meio
		//Chama afun��o recursiva novamente para a primeira parte do vetor divido em 2
		sort(vetor, inicio, metade);
		//Chama a fun��o recursiva novamente para a segunda parte do vetor divido em 2
		sort(vetor, metade+1, final);
		//Chama a fun��o merge que ir� juntar os vetores separados enquanto ordena
		merge(vetor, inicio, metade, final);
	}
}

void imprimeVetor(int *vetor, int linha){
	int n;
	for(n=0;n<linha;n++){
		printf("%d\n", vetor[n]);
	}	
}

int main(int argc, char *argv[]) {
//Variavel x � o numero que ser� lido do teclado,*vetor � um ponteiro para guardar o vetor
	int x;
	//Iniciamos o vetor como NULL para depois realocar memoria para cada numero
	int *vetor;
	vetor = (int *) malloc(0 *sizeof(int));
	//Come�ando da linha 0, primeira, vamos aumentando para saber a quantidade de linhas
	int linha = 0;
	while (!feof(stdin)){
		if (scanf("%d",&x)==1){
			//Realocamos o vetor para caber mais um numero, ou criamos ele caso seja o primeiro, 
			//pois o primeiro realloc vai ser realloc(null,...) que � um malloc
			vetor = (int *)realloc(vetor, (linha+1)*sizeof(int));
			vetor[linha]=x;
			linha++;
		}
	}
	//Chama o sort passando vetor, o come�o 0 e o final do vetor
	sort(vetor, 0, linha-1);
	//Chama imprimeVetor que vai printar o vetor final
	imprimeVetor(vetor,linha);
}

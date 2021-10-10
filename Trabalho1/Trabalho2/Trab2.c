#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Trabalho 2 de Estruturas de Dados, aluno:Nicolas Padre de Lima DRE:118093872  */

/*Criei uma estrutura lista que contem: */
/*Uma chave que representa o vertice, um ponteiro para guardar os vertices adjascentes, */
/*E o tamAdj que guarda a quantidade de vertices guardados no ponteiro adj */
typedef struct lista{
	int chave;
	int *adj;
	int tamAdj;
	struct lista *prox;
}tno;

//Função que insere na lista um novo nó, minha lista começa com um nó com chave 0 já existente, uma cabeça
tno* Inserir(tno *ptlista, int index){
	tno *novo = (tno *) malloc(sizeof(tno));
	novo->chave=index;
	novo->prox=ptlista;
	return novo;
}

//Essa função eu usei muito pra tentar fazer o codigo funcionar, então deixei aqui
void Imprime(tno *lista) {
   	tno *atual;
   	for (atual = lista; atual!= NULL; atual = atual->prox){
      		printf ("%d\n", atual->chave);
	}
}
//Função que busca recurssivamente e retorna essa lista, dada uma chave x
tno* BuscaRecurssiva(tno *lista, int x){
   	if(lista == NULL){
		return NULL;
	}
   	if(lista->chave==x){
		return lista;
	}
   	return BuscaRecurssiva(lista->prox, x);
}

int main(){
	tno *ptLista, *listaBuscada;
	//Inicializamos a primeira chave 0 como cabeça da lista
	ptLista = (tno *) malloc(sizeof(tno));
	ptLista->chave = 0;
	ptLista->prox=NULL;

	char *linha = NULL;
	int vertices, arestas;//Guarda numero de vertices e numero de arestas
	int i, j; //Auxiliares
  	size_t tamLinha = 0;
	scanf("%d %d\n",&vertices, &arestas);//Pega o numero de vertices e arestas 
	//Cria um vetor grauEnt para contar o grau de entrada de todos os vertices
	//Tambem criamos um vetor para ordem final dos vertices
	//Zeramos esses vetores
	int ordem[vertices];
	int grauEnt[vertices];
	for (i=0;i<vertices;i++){
		grauEnt[i]=0;
		ordem[i]=0;
	}
	//Le cada vertice linha por linha
	for(int i = 1; i <= vertices; i++){
		//Pega a linha inteira
    		getline(&linha,&tamLinha,stdin);
    		int pos = 0;
    		int numLido = 0;
    		int numChars;
		//Cria um novo nó e inicia o adj
		ptLista=Inserir(ptLista, i);
		ptLista->adj=(int *)malloc(1*sizeof(int));
		ptLista->tamAdj=0;
		int count=0; //Esse contador vai contar quantos numeros tem no adj desse vertice
    		//Disseca a linha pegando numero por numero
    		while (sscanf(&linha[pos], " %d %n", &numLido, &numChars) > 0) {
      			pos += numChars;
      			if(strlen(linha) != 0){
				//Caso leu um numero, aumenta o tamanho do adj
				ptLista->adj = (int *)realloc(ptLista->adj, (count+1)*sizeof(int));
				ptLista->adj[count]=numLido;
				count++;//incrementa o contador para cada numero pego na linha    
      				grauEnt[numLido-1]++; //Incrementa o grau de entrada usando o numero lido
				
			}
    		}
		//Guarda a quantidade de vertices adjascentes que esse vertice tem
		ptLista->tamAdj=count;
  	}

	//Procura os vertices com Grau de entrada 0 e coloca no vetor ordem
	int pos = 0;
	int v;
	for(v=1;v<=vertices;v++){
		if(grauEnt[v-1]==0){
			ordem[pos]=v;
			pos++;
		}
	}

	//Desconta grau de entrada
	i=0;
	int vLido;//Auxiliar que vai guardar os vertices adjacentes
	int quantAdj;//auxiliar que vai guardar a conta de quantos adj aquele vertice tem
	while(i<pos){
		//Buscamos aquele vertice que ja foi colocado na ordem
		//Com o vertice em mãos acessamos seus adj
		listaBuscada = BuscaRecurssiva(ptLista, ordem[i]);
		quantAdj = listaBuscada->tamAdj;
		//Com a quantidade de vertices adjascentes em mãos, vamos fazer um loop para cada vertice adj
		for(j=0;j<quantAdj;j++){
			//lê cada vertice diminui o grau dele
			vLido = listaBuscada->adj[j];
			grauEnt[vLido-1]--;
			//Caso esse grau seja 0, colocamos na ordem
			if(grauEnt[vLido-1]==0){
				ordem[pos]=vLido;
				pos++;
			}
		}
		i++;
	}

	//Printa a ordem final preenchida =D
	for(i=0;i<vertices;i++){
		printf("%d ", ordem[i]);
	}
}
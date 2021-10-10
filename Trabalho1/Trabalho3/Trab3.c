#include <stdio.h>
#include <stdlib.h>

/*Trabalho 3 de Estrutura de dados */
/*Aluno: Nicolas Padre de Lima DRE: 118093872 */

//Definimos o tipo de estrutura arvore AVL
typedef struct arvore{
	int chave;
	int alt;
	struct arvore* esq;
	struct arvore* dir;
}tno;

tno* ptraiz; //Criamos uma variavel global que vai guardar o endereço para a raiz

//Funcao auxiliar para obter maior entre dois numeros
int maior(int x, int y){
	if(x<y) return y;
	return x;
}
//Funcao auxiliar get para obter altura
int getAltura(tno* ptraiz){
	if(ptraiz!=NULL) return ptraiz->alt;
	return 0;
}

//Funcao auxiliar para imprimir a arvore em pré ordem
void imprime(tno *ptraiz){
    if (ptraiz != NULL){
        printf("%d(%d) ", ptraiz->chave, getAltura(ptraiz));
        imprime(ptraiz->esq);
        imprime(ptraiz->dir);
    }
}
tno* rotacaoEsq(tno* ptraiz){
	tno* ptb = ptraiz->dir;
	ptraiz->dir = ptb->esq;
	ptb->esq=ptraiz;
	
	//Calcula as novas alturas
	ptraiz->alt = maior(getAltura(ptraiz->esq), getAltura(ptraiz->dir)) +1; 
    ptb->alt = maior(getAltura(ptb->esq), getAltura(ptb->dir)) +1;
    //retorna o ptb, que é agora a nova raiz
	return ptb;
}

tno* rotacaoDir(tno* ptraiz){
	tno* ptb = ptraiz->esq;
	ptraiz->esq= ptb->dir;
	ptb->dir = ptraiz;
	
	//Calcula as novas alturas
	ptraiz->alt = maior(getAltura(ptraiz->esq), getAltura(ptraiz->dir)) +1; 
    ptb->alt = maior(getAltura(ptb->esq), getAltura(ptb->dir)) +1;
    //retorna o ptb, que é agora a nova raiz
	return ptb;
	
}

tno* insere(tno* ptraiz, int x){
	int reg;//Regulador
	//Caso o ptraiz seja nulo, criamos esse nó
	if(ptraiz==NULL){
		ptraiz= (tno*)malloc(sizeof(tno));
		if(ptraiz==NULL) {
			puts("Falha ao alocar memoria para o ptraiz");
			return ptraiz;	
		}
		ptraiz->chave = x;
		ptraiz->alt=1;//Altura do novo nó criado é 1
		ptraiz->esq=NULL;
		ptraiz->dir=NULL;
		return ptraiz;
	}
	if(ptraiz->chave > x){
		ptraiz->esq = insere(ptraiz->esq, x);
	}
	else if(ptraiz->chave < x){
		ptraiz->dir = insere(ptraiz->dir, x);
	} else return ptraiz;
	
	reg = getAltura(ptraiz->esq) - getAltura(ptraiz->dir);
	if(reg==2 || reg==-2){
		//reg = 2 estamos no esquerda esquerda ou esquerda direita
		if(reg == 2){
			//Caso esquerda esquerda
			//Vamos precisar de uma rotacao para direita simples
			if(ptraiz->esq->chave > x){
				return rotacaoDir(ptraiz);
			}
			//caso esquerda direita, usamos duas rotacoes simples
			//Primeiro rotacionamos ptraiz->esq para esquerda e depois
			//a raiz para direita
			else if(ptraiz->esq->chave < x){
				ptraiz->esq = rotacaoEsq(ptraiz->esq);
				return rotacaoDir(ptraiz);
			}
		}
		
		//reg = -2 estamos no direita direita ou direita esquerda
		else{
			//Caso direita direita
			//Vamos precisar de uma rotacao para esquerda simples
			if(ptraiz->dir->chave < x){
				return rotacaoEsq(ptraiz);
			}
			//caso direita esquerda, usamos novamente duas rotacoes
			//Primeiro rotacionamos ptraiz->dir para direita e depois
			//rotacionamos a raiz para a esquerda
			else if(ptraiz->dir->chave > x){
				ptraiz->dir = rotacaoDir(ptraiz->dir);
				return rotacaoEsq(ptraiz);
			}
		}
	}else{
		//Caso não nescessite rotação, calcula a altura da raiz
		ptraiz->alt = maior(getAltura(ptraiz->esq), getAltura(ptraiz->dir)) +1;
	}
	return ptraiz;
}

int main(){
    int n;
    char letra[1];
    while(!feof(stdin)){
    	//Recebemos a letra do usuario e verificamos se é i ou p
        if(scanf("%s", letra) == 1){
        	//Caso insira, pegamos o numero e inserimos na arvore
        	if(letra[0] == 'i'){
                if(scanf("%d", &n) == 1){            
                    ptraiz = insere(ptraiz, n);
                }
            }
            //Caso pegarmos p, imprimimos a arvore
            if(letra[0] == 'p'){
                imprime(ptraiz);
		puts("");
            }
        }
    }
    return 0;
}


#include <stdlib.h>
#include <stdio.h>

typedef struct grafoM{ //grafo matriz
	int tam;
	int **mat;
}grafoM;

typedef struct grafol{ //grafo lista
    int vtc_adj;
    int peso;
    struct grafol *proximo;
}grafol;


// funções do grafo matriz
grafoM *criaGrafoM(int tamanho); // função de criação de um grafo matriz
void imprimeDIMACS(grafoM *grafo, int nvertices); // função para imprimir em DIMACS
void imprimeAxV(grafoM *grafo, int v); // aresta incidente a vertice
void imprimeAxA(grafoM *grafo, int aresta); // aresta adijacente a aresta
void imprimeVxV(grafoM *grafo, int v); // vertice adjacente a vertice
void imprimeVxA(grafoM *grafo, int aresta); // vertice incidente a aresta
void imprimeGrauDoVertice(grafoM *grafo, int grau); // imprime o grau do vertice informado 
int verificaAdjacenciaDeVertices(grafoM *grafo, int v1, int v2); // verifica se dois vertices sao adjacentes;
void substituiPesoAresta(grafoM *grafo, int peso, int novoPeso); // substitui o peso de uma aresta
void trocaDoisVertices(grafoM *grafo, int v1, int v2); // função que faz a troca de dois vertices


//funções do grafo lista

grafol **criaGrafo(int tamanho);
int inserelista(grafol **grafo, int pos,int vt,int p); // insere em um grafo lista
void imprimeGrafoLista(grafol **grafo, int tamanho); // imprime um grafo lista
int grauDoVerticeL(grafol **grafo,int v);// grau de um vertice em um grafo lista
void buscaProfundidade(grafol **grafo, int ini, int *visitado, int tamanho);// faz a busca em profundidade
void visitaProfundidade(grafol **grafo, int ini, int *visitado, int cont); //  função auxiliar para realizar a busca em profundidade
void buscaEmLargura(grafol **grafo, int ini, int *visitado, int tamanho);// faz a busca em largura 


int main(){
	
	int i, j, a, b, c, aux, user=0, numeroDeVertices, numeroDeArestas; 
    char vetaux[10];
	grafoM *grafom;
	FILE* file;
	file = fopen("grafo.txt", "r");
	
	if(file == NULL){
		printf("Arquivo não existe.");
		getchar();
		exit(0);
	}


	//abaixo esta a seção de interação com o usuario
	printf("----------MENU---------\n");
    printf("1- Ler um Grafo via DINMCS. \n");
    printf("2- Entrar com um Grafo. \n");
    printf("0- Sair\n\n");

	scanf("%d", &user);
	if(user == 1){
		//leitura de arquivo
		system("cls");
		fgets(vetaux, 10, file); //Pega primeira linha do arquivo
		
		numeroDeVertices = vetaux[0]-'0'; // converte char para inteiro
		numeroDeArestas = vetaux[2]-'0'; //  converte char para inteiro
		
		printf("O Grafo tem %d vertices e %d arestas.\n", numeroDeVertices, numeroDeArestas);
		
		grafom=criaGrafoM(numeroDeVertices);
		
		for(i=0;i<numeroDeArestas;i++){
			fgets(vetaux, 10, file);//lê a proxima linha do arquivo e entra com as variaveis
			a = vetaux[0]-'0'; 
			b = vetaux[2]-'0';  
			c = vetaux[4]-'0';  
					
		    grafom->mat[a][b]=c;
		}
		imprimeDIMACS(grafom, numeroDeVertices); // chama a função de impressão DIMACS
		int userAux=0;
		printf("\n\n\n---QUAL ACAO DESEJA TOMAR?\n\n");
		printf("1- Imprimir todas as arestas adjacentes a uma aresta\n");
		printf("2- Imprimir todos os vertices adjacentes a um vertice\n");
		printf("3- Imprimir todas as arestas incidentes a um vertice\n");
		printf("4- Imprimir todas os vertices incidentes a uma aresta\n");
		printf("5- Imprimir o grau do vertice\n");
		printf("6- Verificar a adjacencia de dois vertices\n");
		printf("7- Substituir um peso ja existente por um novo valor\n");
		printf("8- Trocar dois vertices\n");
		scanf("%d", &userAux);
		
		if(userAux==1){ // imprimir as arestas adjacentes a aresta
			system("cls");
			printf("Qual a aresta escolhida?\n"); 
			scanf("%d", &aux);
			imprimeAxA(grafom, aux);
		}else if(userAux==2){ // imprimir os vertices adjacentes
			system("cls");
			printf("Qual o vertice escolhido?\n");
			scanf("%d", &aux);
			imprimeVxV(grafom, aux);
		}else if(userAux==3){ // imprimir uma aresta incidente a um vertice
			system("cls");
			printf("Qual o vertice escolhido?\n");
			scanf("%d", &aux);
			imprimeAxV(grafom, aux);
		}else if(userAux==4){ // imprimir o vertice incidente a uma aresta
			system("cls");
			printf("Qual a aresta escolhida?\n");
			scanf("%d", &aux);
			imprimeVxA(grafom, aux);
		}else if(userAux==5){ // caso queira saber o grau de um determinado vertice
			system("cls");
			printf("Qual vertice deseja verificar o grau?\n");
			scanf("%d", &aux);
			imprimeGrauDoVertice(grafom, aux);
		}else if(userAux==6){ // caso for verificar a adjacencia de dois vertices
			int v1=0,v2=0;
			aux=0;
			system("cls");
			printf("Quais vertices deseja verificar a adjacencia?\n");
			scanf("%d", &v1);
			scanf("%d", &v2);
			aux = verificaAdjacenciaDeVertices(grafom, v1, v2);
			if(aux==1){
				printf("\n Os vertices escolhidos sao adjacentes");
			}else{
				printf("\n Os vertices escolhidos nao sao adjacentes");
			}
		}else if(userAux==7){ //caso for substituir peso
			system("cls");
			int p1=0,p2=0;
			printf("Informe o peso a ser substituido e o novo peso\n");
			scanf("%d", &p1);
			scanf("%d", &p2);
			substituiPesoAresta(grafom, p1, p2);
			imprimeDIMACS(grafom, numeroDeVertices); // chama a função de impressão DIMACS
		}else if(userAux==8){ // caso quiser trocar dois vertices
			system("cls");
			int v1=0,v2=0;
			printf("Informe os dois vertices a serem trocados\n");
			scanf("%d", &v1);
			scanf("%d", &v2);
			trocaDoisVertices(grafom, v1, v2);
			imprimeDIMACS(grafom, numeroDeVertices); // chama a função de impressão DIMACS
		}else{
			printf("\nValor invalido, o programa sera encerrado\n");
		}
		
	}else if(user == 2){ // entrando com os valores manualmente para comport um grafo lista
		//grafo lista
		int x, pos, v, peso;
		printf("Quantos vertices?\n");
		scanf("%d", &numeroDeVertices);
		grafol **grafo;
		grafo = criaGrafo(numeroDeVertices); // criando o grafo lista
		printf("Quantos elementos deseja inserir?\n");
		scanf("%d", &x);
		for(i=0;i<x;i++){
			printf("Entre com as posicoes e os pesos.\n");
			scanf("%d", &pos);
			scanf("%d", &v);
			scanf("%d", &peso);
			if(pos>numeroDeVertices || v>numeroDeVertices){
				printf("valor invalido\n");
				exit(0);
			}
			inserelista(grafo, pos,v,peso); // insere em um grafo lista
			system("cls"); //limpar a tela;
			printf("\n");
			imprimeGrafoLista(grafo, numeroDeVertices); // faz a impressao do grafo lista
		}
		system("cls"); //limpar a tela;
		printf("Grafo criado com sucesso\n\n");
		imprimeGrafoLista(grafo, numeroDeVertices); // faz a impressao do grafo lista
		
		int userAux=-1;
		while(userAux!=0){ // loop para realizar ambas as buscas
			printf("Oque deseja fazer?\n");
	 		printf("1- Busca em profundidade \n");
	    	printf("2- Busca em largura \n");
	    	printf("0- Sair\n");
	    	
	    	int visitado[numeroDeVertices];
	   		scanf("%d", &userAux);
	   		if(userAux==1){
	   			buscaProfundidade(grafo, 0, visitado, numeroDeVertices); // realiza a busca em prufundidade
			}else if(userAux==2){
				buscaEmLargura(grafo, 0, visitado, numeroDeVertices); // realiza a busca em largura
			}
		}
		
		
	}else if(user == 0){
		// sair
		printf("Saindo...");
	}
	
	
	return 0;
}
///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
////////////////////////////GRAFO MATRIZ
/////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

grafoM *criaGrafoM(int tamanho){ //cria o grafo
	
	grafoM *grafo;
	grafo = (grafoM*)malloc(sizeof(grafoM));
	grafo->mat = (int**)malloc(tamanho*sizeof(int*));
	
	int i, j;
	
	for(i=0;i<tamanho;i++){	
			grafo->mat[i] = (int*)malloc(tamanho*sizeof(int));
	}
	
	
	for(i=0;i<tamanho;i++){
		for(j=0;j<tamanho;j++){
			grafo->mat[i][j] = 0;
		}
	}
	grafo->tam = tamanho;
	return grafo;
}

void imprimeDIMACS(grafoM *grafo, int nvertices){ //essa função é responsável por imprimir o grafo em DIMACS
	int i,j;
	for(i=0;i<nvertices;i++){ // imprimir grafo
	        	for(j=0;j<nvertices;j++){
	        	    printf("%d ", grafo->mat[i][j]);
	        	}
	        	printf("\n");
	    	}
}

void imprimeAxA(grafoM *grafo, int aresta){ // aresta adjacente a aresta
	int i, j;
	
	for(i=0;i<grafo->tam;i++){	
		for(j=0;j<grafo->tam;j++){
			if(grafo->mat[i][j]==aresta){
				imprimeAxV(grafo, j);
			}	
		}
	}
}
void imprimeAxV(grafoM *grafo, int v){ // aresta incidente a vertice
	int i;
	
	printf("Aresta incidente a v%d: ", v);
	for(i=0;i<grafo->tam;i++){
		if(grafo->mat[v][i]!=0){
			printf("%d ", grafo->mat[v][i]);
		}
	}
}

void imprimeVxV(grafoM *grafo, int v){ // vertice adjacente a vertice
	int i;
	
	printf("\nVerices adjacentes a V%d: ", v);
	for(i=0;i<grafo->tam;i++){
		if(grafo->mat[v][i]!=0){
			printf("v%d ", i);
		}
	}
	
	
}
void imprimeVxA(grafoM *grafo, int aresta){ // vertice incidente a aresta
	int i, j;
	printf("vertice incidente a aresta %d: ", aresta);
	for(i=0;i<grafo->tam;i++){
		for(j=0;j<grafo->tam;j++){
			if(grafo->mat[i][j]==aresta){
				printf("v%d -> v%d", i,j);
			}
		}
	}
}

void imprimeGrauDoVertice(grafoM *grafo, int grau){ // imprime o grau do vertice informado 
	int i=0, cont = 0;
	
	for(i=0;i<grafo->tam;i++){
		if(grafo->mat[grau][i]!=0){
			cont++;
		}
	}
	printf("O grau do verice %d eh: %d\n", grau, cont);
}

int verificaAdjacenciaDeVertices(grafoM *grafo, int v1, int v2){ // função para verificar se dois vertices são adjacentes
	
	if(grafo->mat[v1][v2]!=0){
		return 1;
	}else if(grafo->mat[v2][v1]!=0){
		return 1;
	}else{
		return 0;
	}
}

void substituiPesoAresta(grafoM *grafo, int peso, int novoPeso){ // substitui o peso de uma aresta
	int i=0, j=0, cont=0;
	
	for(i=0;i<grafo->tam;i++){
		for(j=0;j<grafo->tam;j++){
			if(grafo->mat[i][j]==peso){
				grafo->mat[i][j]=novoPeso;
			}
		}
	}
}


void trocaDoisVertices(grafoM *grafo, int v1, int v2){ // função que faz a troca de dois vertices
	int i, aux[grafo->tam];
	
	for(i=0;i<grafo->tam;i++){
		aux[i]=grafo->mat[v1][i];
	}
	for(i=0;i<grafo->tam;i++){
		grafo->mat[v1][i] = grafo->mat[v2][i];
	}
	for(i=0;i<grafo->tam;i++){
		grafo->mat[v2][i] = aux[i];
	}
}


///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
////////////////////////////GRAFO LISTA
/////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////



grafol **criaGrafo(int tamanho){
	
	grafol **grafo;
	int i;
	
	grafo = (grafol**)malloc(tamanho*sizeof(grafol*));
	if(grafo!=NULL){
		for(i=0;i<tamanho;i++){
			grafo[i] = NULL;
		}
	}
	
	return grafo;
	
}

int inserelista(grafol **grafo, int pos,int vt,int p){
	
	if(grafo == NULL){
		return -1;
	}else{
		
		grafol *e1;
		e1= (grafol*)malloc(sizeof(grafol));
		if( e1 != NULL){
			e1->peso = p;
			e1->vtc_adj = vt;
			e1->proximo = NULL;
			if(grafo[pos] == NULL){
				grafo[pos] = e1;
				e1->proximo = NULL;
			}else{
				grafol *aux;
				aux = grafo[pos];
				while(aux->proximo != NULL){
					aux = aux->proximo;
				}
				aux->proximo = e1;
			}
			return 1;
			
			
			
		}else{
			return 0;
		}	
	}	
}

void imprimeGrafoLista(grafol **grafo, int tamanho){ // função usada para imprimir o grafo em lista
	
	grafol *aux;
	int i;
	
	for(i=0;i<tamanho;i++){
		
		if(grafo[i]!=NULL){
			printf("v%d->%d,%d", i, grafo[i]->vtc_adj, grafo[i]->peso);
			aux=grafo[i];
			while(aux->proximo!=NULL){
				printf("->%d,%d", aux->proximo->vtc_adj, aux->proximo->peso);
				aux=aux->proximo;
			}
			
			printf("\n");
		}else{
			printf("v%d->NULL\n", i);
		}
	}
}

void visitaProfundidade(grafol **grafo, int ini, int *visitado, int cont){//função auxiliar para realizar a busca em profundidade
	
	int i,x;
	visitado[ini]=cont;
	
	x=grauDoVerticeL(grafo,ini);
	
	grafol *aux;
	aux = grafo[ini];
	
	for(i=0;i<x;i++){
		if(!visitado[aux->vtc_adj]){
			visitaProfundidade(grafo, aux->vtc_adj, visitado, cont+1);
		}
		aux=aux->proximo;
	}
	
}

void buscaProfundidade(grafol **grafo, int ini, int *visitado, int tamanho){ //faz a busca em profundidade
	int i, cont=1;
	
	
	for(i=0;i<tamanho;i++){
		visitado[i]=0;
	}
	
	
	visitaProfundidade(grafo, ini, visitado, cont);
	
	for(i=0;i<tamanho;i++){
		visitado[i]--;
	}
	for(i=0;i<tamanho;i++){
		printf("A distancia de v0 ate v%d eh: %d\n", i, visitado[i]);
	}
	

}

int grauDoVerticeL(grafol **grafo,int v){ // função usada para obter o grau de um vertice no grafo lista
	
	int cont =0, x=1, i;
	
	grafol *aux;
	
	aux=grafo[v];
	
	if(grafo[v]!=NULL){
		while(aux->proximo!=NULL){
			x++;
			aux=aux->proximo;
		}
	}else{
		return 0;
	}
	return x;
	
	
}


void buscaEmLargura(grafol **grafo, int ini, int *visitado, int tamanho){ // função usado para busca em largura
	
	int i, finalFila=0, inicioFila=0, cont=1, vertice,x,z; 
	
	for(i=0;i<tamanho;i++){ 
		visitado[i]=0;
	}
	int *fila=(int*)malloc(tamanho*sizeof(int));
	finalFila++;
	fila[finalFila]=ini;
	visitado[ini]=cont;
	
	while(inicioFila!=finalFila){
		inicioFila=(inicioFila+1)%tamanho;
		vertice = fila[inicioFila];
		cont++;
		
		x=grauDoVerticeL(grafo,vertice);
		
		grafol *aux;
		aux=grafo[vertice];
		
		for(i=0;i<x;i++){
			if(!visitado[aux->vtc_adj]){
				finalFila=(finalFila+1)%tamanho;
				fila[finalFila]=aux->vtc_adj;
				visitado[aux->vtc_adj]=cont;
			}
			aux=aux->proximo;
		}
		
	}
	free(fila);
	
	for(i=0;i<tamanho;i++){
		visitado[i]--;
	}
	for(i=0;i<tamanho;i++){
		printf("a distancia do v0 ate o v%d eh de: %d\n", i, visitado[i]);
	}
	
	
	
}

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define Vertex int

Vertex n_cidades; /// apenas um tipo criado para melhor leitura do codigo, maior legibilidade
int custo, visitado[20], cidade_inicio;

int matrizPreFeita[10][10]={{0,2,4,12,13,9,2,1,3,7},
							{2,0,3,5,7,9,11,10,12,13},
							{4,3,0,8,4,1,18,20,14,7},
							{12,5,8,0,2,6,12,8,13,9},
							{13,7,4,2,0,23,6,8,2,1},
							{9,9,1,6,23,0,11,12,13,15},
							{2,11,18,12,6,11,0,9,1,16},
							{1,10,20,8,8,12,9,0,7,14},
							{3,12,14,13,2,13,1,7,0,2},
							{7,13,7,9,1,15,16,14,2,0}};

struct grafo{
    int V;
    int A; // soh guarda o numero de arestas
    int **adj_pesos; // matriz com os pesos das arestas
};

typedef struct grafo *Grafo; ///ponteiro para manipular melhor os dados

int **MATRIXint(int r, int val){ //  usada para as duas matrizes

    Vertex i,j;
    int **m=malloc(r*sizeof(int *));

        for(i=0;i<r;i++)
        {
            m[i]=malloc(r*sizeof(int));
        }
        for(i=0;i<r;i++)
        {
            for(j=0;j<=r;j++){
                m[i][j]= val;
            }
        }
    return m;
}

Grafo GrafoInit(int v){
    Grafo G = malloc(sizeof *G);
    G->V = v;
    G->A = 0;
    G->adj_pesos = MATRIXint(v,0);
    return G;
}

void GrafoInsert(Grafo G, Vertex v, Vertex w, int peso){ // funcao pra setar o peso das arestas
    if(G->adj_pesos[v][w] > peso){
        G->adj_pesos[v][w] = peso;
        G->A++;
    }
}

void GrafoShow(Grafo G){
    Vertex v,w;
    for(v = 0; v < G->V; v++){
        printf("%d:", v+1);

        for(w = 0; w < G->V; w++)
            printf(" %d ", G->adj_pesos[v][w]);
            printf("\n\n");
    }
}

///////////////////////////NEAREST_NEIGHBOR/////////////////////////////////////
int near_neighbor(Grafo G, int atual){

    int i, cc = 10000, menor_caminho = 10000, m_caminho;

	    for(i = 0; i < G->V; i++)
	    {
	        if(((G->adj_pesos[atual][i] != 0) && (G->adj_pesos[atual][i] != 666)) && (visitado[i] == 0)) ///foi estipulado o maior peso possivel ser maior que 666, mas isso é totalmente ajustavel
	        {
	            if(G->adj_pesos[atual][i] < menor_caminho)
	            {
	                menor_caminho = G->adj_pesos[atual][i]; ///novo valor pro menor caminho
	                m_caminho = G->adj_pesos[atual][i]; ///melhor caminho no momento
	                cc = i; ///valor que retorna a funcao
	            }
	        }
	    }
	    if(menor_caminho!=10000){
	        custo += m_caminho;
	    }
    return cc;
}

///////////////////////////MELHOR CAMINHO///////////////////////////////////////
void bestPath(Grafo G, int vertice){

    int escolha; ///variavel pra cidade de inicio que é transformada no indice real pra matriz de adjacentes
    int cidade_atual;

    escolha = (vertice-1);
    visitado[escolha] = 1;///seta que foi visitado

    printf("%d - ", vertice);
    cidade_atual = near_neighbor(G,escolha);

    if(cidade_atual == 10000){
        printf("%d", cidade_inicio);
        custo += G->adj_pesos[escolha][cidade_inicio-1];
        return;
    }
    bestPath(G, cidade_atual+1); ///<-- recursão aqui
}

///////////////////////////PRINCIPAL////////////////////////////////////////////
void principal(){

    int continua = 0, op = 0;
    int opMat;
    n_cidades = 0;
    custo = 0;
    Vertex i,j;
    int cidade_ini;

    while (continua == 0){

    	printf("Deseja inserir uma nova matriz, ou utilizar uma existente? \n\t1 - para inserir\n\t0 - para usar a pronta\n");
    	printf("Opcao: ");
    	scanf("%d", &opMat);

    	if(opMat == 1){
	 		n_cidades = 0;
	    	custo = 0;
		    printf("\n\nNumero de cidades(vertices): ");
		    scanf("%d", &n_cidades);
		    Grafo grafo1 = GrafoInit(n_cidades);/// inicializou o grafo e sua matriz de adj com '0'

		    printf("\nEntre com os pesos das arestas, por linha da matriz: \n");
			    for(i = 0; i < grafo1->V; i++)
			    {
			        printf("\nPesos relacionados ao vertice %d: \n", i+1);
			        for(j = 0; j < grafo1->V; j++)
			        {
			            scanf("%d", &grafo1->adj_pesos[i][j]);
			        }
			        visitado[i] = 0;
			    }
		    printf("\n\nA matriz de adjacencia de custos: \n\n");
		    GrafoShow(grafo1);

		    printf("\n\nCidade para comecar: ");
		    scanf("%d", &cidade_ini);
		    cidade_inicio = cidade_ini;
		    bestPath(grafo1,cidade_ini);

		    printf("\n\nCusto otimo: %d", custo);

		    printf("\n\nDeseja fazer outro calculo? 0 p/ Sim, ou 1 para Não\n");

		    scanf("%d", &op);

			if(op == 0)
				continua =0;
			else if(op == 1)
				continua = 1;
			else
				continua = 1;
			free(grafo1);
		}

		else if(opMat == 0){
			custo =0;
			Grafo grafo0 = GrafoInit(10); // porque é da matriz dada lá em cima

			for(i = 0; i < grafo0->V; i++)
		    {
		        for(j = 0; j < grafo0->V; j++)
		        {
		            grafo0->adj_pesos[i][j] = matrizPreFeita[i][j];
		        }
		        visitado[i] = 0;
		    }

		    printf("A matriz de adjacencia de custos: \n\n");
	    	GrafoShow(grafo0);
	    	printf("\n\nCidade para comecar: ");
	    	scanf("%d", &cidade_ini);
	    	cidade_inicio = cidade_ini;
	    	bestPath(grafo0,cidade_ini);

	    	printf("\n\nCusto otimo: %d\n", custo);

	    	printf("Deseja fazer outro calculo? 0 p/ Sim, ou 1 para Não\n");

	    	scanf("%d", &op);

			if(op == 0)
				continua =0;
			else if(op == 1)
				continua = 1;
			else
				continua = 1;
			free(grafo0);
			custo =0;
		}
	}
}

int main ()
{
    principal();
    return 0;
}

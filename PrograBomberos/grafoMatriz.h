#include <stdbool.h>
#include "Arbol.h"
typedef struct Vertice{
       int valor;
       bool visitado;
}Vertice;

struct Vertice* newVertice(int val){
    struct Vertice * v = malloc(sizeof(struct Vertice));
    if(v)
        v->valor = val;
        v->visitado = false;
    return v;
};

typedef struct grafoMatriz{
    int maximo;
    int matriz[100][100];
    int vertices[100];
    //bool visitados[100];
    int cantidadVertices;
    int destino;
    ArbolCaminos* arbol;
/*
//    prototipos
 int indexOfVertice(int);
 void agregarVertice(int);
 void agregarArista(int, int, int);
 void imprimir();
 int minVertex (int[]);
int* dijkstra(int ) ;
void limpiarVisitados();
void warshall_floyd();
*/
}grafoMatriz;

struct grafoMatriz* newgrafoMatriz(int destino){
    struct grafoMatriz * g = malloc(sizeof(struct grafoMatriz));
    if(g){
        g->destino = destino;
        g->maximo = 100;
        g->cantidadVertices = 0;
        // inicializa arreglos
        int i;
        for (i=0; i<100; i++)
        {
            g->vertices[i] = 0;
            //g->visitados[i] = 0;

            // para incializar matriz
            int j;
            for (j = 0; j < 100; j++)
            {
                g->matriz[i][j] = 0;
            }
        }
        return g;
    }
}

void crearArbolgrafoMatriz(grafoMatriz* g,int destino){
    g->arbol = newArbolCaminos(destino,g->cantidadVertices-1);
}

int  resolverArbolgrafoMatriz(grafoMatriz* g, int destino,NodoEsquina*actual, int rutas){
    //primero crea el arbol
    if (g->arbol == NULL){
        crearArbolgrafoMatriz(g,destino);
        actual = g->arbol->raiz;
    }
    if (actual->padre == NULL && buscarHijoValidoEngrafoMatriz(g,actual) == 0){
        return rutas;
    }
    else{
        //luego resuelve el arbol
        if(actual->dato == 1){
            imprimirRutaDesdeNodo(actual);
            actual = actual->padre;
            return resolverArbolgrafoMatriz(g,destino,actual,rutas+1);
        }else{
            if (buscarHijoValidoEngrafoMatriz(g,actual)==0){
                actual = actual->padre;
                return resolverArbolgrafoMatriz(g,destino,actual, rutas);
            }else{
                int hijo = buscarHijoValidoEngrafoMatriz(g,actual);
                insertarHijoNodoEsquina(actual,hijo);
                NodoEsquina * nodoHijo= buscarHijoEnNodoEsquina(actual, hijo);
                return resolverArbolgrafoMatriz(g, destino, nodoHijo,rutas);
            }
        }
    }
}

// agregar vertice
    void agregarVerticegrafoMatriz(struct grafoMatriz * g,int v)
    {
        int i;
        for (i = 0; i < g->cantidadVertices; i++)
        {

            if (g->vertices[i] == v){
                return 0;
            }

        }
         // si hay campo y v no est'a en el grafo
       if (g->cantidadVertices < g->maximo)// && indexOfVerticegrafoMatriz(g,v) == -1)
       {
            g->vertices[g->cantidadVertices] = v;
            g->cantidadVertices++;
       }
    }
// index de un vertice
 int indexOfVerticegrafoMatriz(struct grafoMatriz*g,int v)
    {
        int i;
        for (i = 0; i < g->cantidadVertices; i++) {
            if (g->vertices[i] == v)
                return i;
        }

        return -1;
    }
// agregar arista
void agregarAristagrafoMatriz(struct grafoMatriz *g,int origen, int destino, int peso)
{
        int orig = indexOfVerticegrafoMatriz(g,origen);
        int dest = indexOfVerticegrafoMatriz(g,destino);

        if (orig != -1 && dest != -1)
        {
            g->matriz[dest][orig] = peso;
        }
}

void agregarAristaDoblegrafoMatriz(struct grafoMatriz * g,int origen, int destino, int peso){
    agregarAristagrafoMatriz(g,origen,destino,peso);
    agregarAristagrafoMatriz(g,destino,origen,peso);
}

// imprimir

int buscarHijoValidoEngrafoMatriz(grafoMatriz*g, NodoEsquina*n){
    int i;
    int columna = n->dato-1;
    for (i = 0; i < g->cantidadVertices; i++){
        //recorriendo la columna
        if(g->matriz[i][columna] != 0){
            //ya encontro un hijo
            //pregunta si esta en lista de hijos
            int j;
            if (n->numHijos == 0 && !esAncestro(n,i+1))
                return i + 1;
            for (j=0; j< n->numHijos; j++){
                //n->hijos[j]->dato: hijo de la lista
                //i+1: hijo que lleva al nodo n
                NodoEsquina * hijoEnLista= buscarHijoEnNodoEsquina(n, i+1);
                //no esta en lista de hijos
                if (hijoEnLista == NULL && !esAncestro(n,i+1)){
                    return i+1;
                }
            }

        }
    }
    return 0;
}

 void imprimirgrafoMatriz(struct grafoMatriz *g)
    {
        printf(" \t");
        int i;
        for (i = 0; i < g->cantidadVertices; i++) {
            printf("%d",g->vertices[i]);
            printf(" \t");
        }
        printf("\n");
        for (i = 0; i < g->cantidadVertices; i++) {
            printf("%d",g->vertices[i]);
            printf(" \t");
            int j;
            for (j = 0; j < g->cantidadVertices; j++) {

                printf("%d",g->matriz[i][j]);
                printf(" \t");
            }
            printf("\n");
        }
    }

void leerArchivo(char archivoEntrada[]){
    printf("entra \n");
    FILE *archivo;
	int caracter;
	int caso = 1;

	archivo = fopen(archivoEntrada,"r");

	if (archivo == NULL)
        {
            printf("\nError de apertura del archivo. \n\n");
        }
        else
        {
             while((caracter = fgetc(archivo)) != EOF)
             {
                printf("\nCaso #");printf("%i",caso);printf("\n\n");    // Para saber la parte del archivo que estoy leyendo
                while(((caracter = fgetc(archivo)) != '0') || ((caracter = fgetc(archivo)) == EOF) )
                {
                printf("%c",caracter);
                }
                caracter = fgetc(archivo);                              // Para saltarme el otro cero
                caso += 1;
             }

        }
        fclose(archivo);
  }


//limpiar visitados
/*
void limpiarVisitadosgrafoMatriz(struct grafoMatriz*g)
{
    int i;
     for (i=0; i < g->cantidadVertices;i++)
         g->visitados[i] = false;
}
*/
 // min vertice
 /*
    int minVertexgrafoMatriz (struct grafoMatriz*g,int * distanciasCortas)
    {
        int x = 999999;
        int y = -1;
        // RECORRE EL ARREGLO DE DISTANCIAS CORTAS BUSCANDO EL MENOR NO VISITADO
        int i;
        for (i = 0; i < g->cantidadVertices; i++) {
            printf("%d",distanciasCortas[i]);
            printf("    ");
            // CONDICION PARA OBTENER NO VISITADO Y EL MENOS DE TODOS
            if (!g->visitados[i] && distanciasCortas[i] < x)
            {
                y = i;
                x = distanciasCortas[i];
            }
        }
        printf("min: %d",y);
        printf("  valor = %d",x);
        printf("\n");
        return y;// RETORNA LA POSICION DEL MENOR
    }*/

//-----------------------------------------
//dijkstra
/*
   int* dijkstragrafoMatriz(struct grafoMatriz *g,int v) {
        // arreglo para llevar los nodos visitados
        limpiarVisitadosgrafoMatriz(g);
        // arreglo que almacena las distancias más cortas desde el vertice
        int distanciasCortas[100];
        // obtiene el índice del vertice en la matriz
        int node = indexOfVerticegrafoMatriz(g,v);
        // coloca visitado el nodo inicial
        g->visitados[node] = true;
        //coloca pos node en cero, pues es el inicio
        distanciasCortas[node] = 0;
// desde 1, porque cero ya tiene valor cero,
// pues las distancia inicial es de x a x, = 0
// para cada posición en distancias cortas, va
// colocando el peso si hay arista entre el
// nodo inicial y los demás, sino, infinito
        int i;
        for (i = 1; i < g->cantidadVertices; i++) {
            if (g->matriz[i][node] != 0)
            // como sí hay camino, coloca el peso
                distanciasCortas[i] = g->matriz[i][node];
            else /// si no, infinito
                distanciasCortas[i] = 999999;
        }
        // no considera el primero pues es el primer nodo distancia = 0
        for (i = 0; i < (g->cantidadVertices - 1); i++){
            // obtiene el menor del arreglo,
            // mientras no visitado
            int next = minVertexgrafoMatriz(g,distanciasCortas);
            g->visitados[next] = true;
            //
            int j;
            for (j = 0; j < g->cantidadVertices; j++) {
                // calcula el ultimo más corto (NEXT)
                //  + cada arista ady a NEXT
                int d = distanciasCortas[next] + g->matriz[j][next];
// si en la pos del vertice no visitado y hay
// camino a la arista se coloca en distancias
// cortas de arista la suma del menor más el
// peso de arista, para ver cual es menor, si no
// quedo el más corto inicial
                if (distanciasCortas[j] > d && g->matriz[j][next] > 0) {
// como d es menor, se coloca ese valor, que es sumando
// el camino acumulado + arista adyacente a next
                    distanciasCortas[j] = distanciasCortas[next] + g->matriz[j][next];
                }
            }
        }
        for (i = 0; i < g->cantidadVertices; i++){
            printf("%d",distanciasCortas[i]);
            printf("   ");
        }
        printf("\n");
        return distanciasCortas;
    }

// warshall y floyd
    void warshall_floydgrafoMatriz(struct grafoMatriz*g)
    {



        int cn = g->cantidadVertices;
        int path[100][100];

        // convertir matriz a unos
        int i;
        for (i = 0; i < cn; i++) {
            int j;
            for (j = 0; j < cn; j++) {
                if (g->matriz[i][j] > 0)//peso
                    path[i][j] = g->matriz[i][j];
                else if (i==j)//diagonal
                    path[i][j] = 0;
                else // no hay -> infinito
                    path[i][j] = 9999;
                    //MAX_VALUE;
            }
        }

        // imprime matriz
        for(i = 0; i < cn; i++)
        {
                printf("\n");
                int j;
                for (j = 0; j < cn; j++){
                   printf("%d",path[i][j]);
                   printf("\t");
                   }

        }
        printf("\n");
    int k;
    for(k = 0; k < cn; k++){
        int i;
        for(i = 0; i < cn; i){
            int j;
            for(j = 0; j < cn; j++){
                int dt = path[i][k] + path[k][j];
                if(path[i][j] > dt)
                {
                    path[i][j] = dt;
                    //path[j][i] = dt;
                }
            }
        }
    }

// imprime matriz
        for(i = 0; i < cn; i++)
        {
                printf("\n");
                int j;
                for (j = 0; j < cn; j++){
                   printf("%d",path[i][j]);
                   printf("\t");
                }

        }
        printf("\n");


    }
*/



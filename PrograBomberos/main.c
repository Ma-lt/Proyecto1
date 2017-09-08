#include <stdio.h>
#include <stdlib.h>
#include "grafoMatriz.h"
#include "grafo.h"
#include "Arbol.h"
int main()
{
    int MAX_HIJOS = 5;//numero de nodos -1
    ArbolCaminos * a = newArbolCaminos(6,MAX_HIJOS);
    NodoEsquina * tmp = a->raiz;
    printf("%d",tmp->dato);
    printf("\n");
    insertarHijoNodoEsquina(tmp,5);
    insertarHijoNodoEsquina(tmp, 9);
    insertarHijoNodoEsquina(tmp, 2);
    imprimirHijosNodoEsquina(tmp);
    tmp = tmp->hijos[0];
    insertarHijoNodoEsquina(tmp, 1);
    tmp = tmp->hijos[0];
    bool x = esAncestro(tmp, 4);
    printf(x ? "true" : "false");
    printf("\n");

    /*
    Grafo * g = newGrafo();

    insertarVerticeGrafo(g,10);
    insertarVerticeGrafo(g,20);
    insertarVerticeGrafo(g,30);
    insertarVerticeGrafo(g,40);
    insertarVerticeGrafo(g,50);

    insertarAristaGrafo(g,30,20,0);
    insertarAristaGrafo(g,10,30,0);
    insertarAristaGrafo(g,10,40,0);
    insertarAristaGrafo(g,10,50,0);
    insertarAristaGrafo(g,20,10,0);
    insertarAristaGrafo(g,20,20,0);
    insertarAristaGrafo(g,20,30,0);
    insertarAristaGrafo(g,30,40,0);
    insertarAristaGrafo(g,40,50,0);
    insertarAristaGrafo(g,50,10,0);

    imprimirGrafo(g);

    borrarVerticeGrafo(g,10);
    imprimirGrafo(g);

    //profundidadGrafo(g);
    anchuraGrafo(g,g->vertices->primerNodo);


struct grafoMatriz * g1 = newgrafoMatriz();

agregarVerticegrafoMatriz(g1,10);
agregarVerticegrafoMatriz(g1,20);
agregarVerticegrafoMatriz(g1,30);
agregarVerticegrafoMatriz(g1,40);
agregarVerticegrafoMatriz(g1,50);
agregarVerticegrafoMatriz(g1,60);

imprimirgrafoMatriz(g1);
printf("\n");
//dijkstra
        agregarAristagrafoMatriz(g1,g1->vertices[0],g1->vertices[1],7);
        agregarAristagrafoMatriz(g1,g1->vertices[1],g1->vertices[0],7);
        agregarAristagrafoMatriz(g1,g1->vertices[0],g1->vertices[2],9);
        agregarAristagrafoMatriz(g1,g1->vertices[2],g1->vertices[0],9);
        agregarAristagrafoMatriz(g1,g1->vertices[0],g1->vertices[5],14);
        agregarAristagrafoMatriz(g1,g1->vertices[5],g1->vertices[0],14);
        agregarAristagrafoMatriz(g1,g1->vertices[1],g1->vertices[2],10);
        agregarAristagrafoMatriz(g1,g1->vertices[2],g1->vertices[1],10);
        agregarAristagrafoMatriz(g1,g1->vertices[1],g1->vertices[3],15);
        agregarAristagrafoMatriz(g1,g1->vertices[3],g1->vertices[1],15);
        agregarAristagrafoMatriz(g1,g1->vertices[2],g1->vertices[3],11);
        agregarAristagrafoMatriz(g1,g1->vertices[3],g1->vertices[2],11);
        agregarAristagrafoMatriz(g1,g1->vertices[2],g1->vertices[5],2);
        agregarAristagrafoMatriz(g1,g1->vertices[5],g1->vertices[2],2);
        agregarAristagrafoMatriz(g1,g1->vertices[3],g1->vertices[4],6);
        agregarAristagrafoMatriz(g1,g1->vertices[4],g1->vertices[3],6);
        agregarAristagrafoMatriz(g1,g1->vertices[5],g1->vertices[4],9);
        agregarAristagrafoMatriz(g1,g1->vertices[4],g1->vertices[5],9);
        imprimirgrafoMatriz(g1);

printf("\n");
dijkstragrafoMatriz(g1,10);
warshall_floydgrafoMatriz(g1);
printf("\n");
*/
        system("PAUSE");
    return EXIT_SUCCESS;
}


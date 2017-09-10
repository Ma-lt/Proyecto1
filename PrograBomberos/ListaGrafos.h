#ifndef LISTAGRAFOS_H_INCLUDED
#define LISTAGRAFOS_H_INCLUDED

#include "grafoMatriz.h"

//Nodo de ListaGrafos
typedef struct NodoGrafo{
    struct grafoMatriz * grafo;
    struct NodoGrafo * siguiente;
};

struct NodoGrafo* newNodoGrafo(struct grafoMatriz* g){//si es la raiz, el padre es nulo
    struct NodoGrafo * n = malloc(sizeof(struct NodoGrafo));
    if(n){
        n->grafo = g;
        n->siguiente = NULL;
    }
    return n;
}

//Lista de grafos del archivo
typedef struct ListaGrafos{
    struct NodoGrafo * primerNodo;
    struct NodoGrafo * ultimoNodo;
};

struct ListaGrafos* newListaGrafos(){//si es la raiz, el padre es nulo
    struct ListaGrafos * l = malloc(sizeof(struct ListaGrafos));
    if(l){
       l->primerNodo = NULL;
    }
    return l;
}

void insertarAlFinalListaGrafos (struct ListaGrafos* l, struct grafoMatriz* g)
{
     // si no hay elementos
     if (l->primerNodo == NULL)
     {
         // ambos apuntan al nuevo en memoria
         l->primerNodo = newNodoGrafo(g);
         l->ultimoNodo = l->primerNodo; // ambos apuntan al nuevo
     }
     else
     {
         // se crea el nuevo nodo
         struct NodoGrafo *nuevo = newNodoGrafo(g);
         // uN siguiente debe apuntar al nuevo nodo
         // uN debe apuntar al nuevo nodo enlazado
         l->ultimoNodo->siguiente = nuevo;
         l->ultimoNodo = nuevo;
         // el puntero nuevo deja de existir, no se libera
         // memoria porque se pierde la info
     }
}

void resolverListaGrafos(struct ListaGrafos * l){
    struct NodoGrafo * tmp = l->primerNodo;
    while (tmp != NULL){
        resolverArbolgrafoMatriz(tmp->grafo,tmp->grafo->destino,NULL);
        tmp = tmp->siguiente;
    }
}


#endif // LISTAGRAFOS_H_INCLUDED

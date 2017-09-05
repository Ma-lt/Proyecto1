#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


// estructura nodo para lista simple

// estructura arista para lista de aristas

typedef struct Arista {
       int dato; // parte de datos
       int peso;
       // int poblacion
       // int distancia
       //int.....
       struct Arista * siguiente;// puntero para enlazar nodos
}Arista;

struct Arista* newArista (int d, int p){
    struct Arista * a = malloc(sizeof(struct Arista));
     if (a) {
          a->dato = d;
          a->peso = p;
          a->siguiente = NULL;
     }
     return a;
}

void printArista(struct Arista* a){
    printf("%d",a->dato);
    printf("(%d", a->peso);
    printf(")");
}

typedef struct ListaAristas {
       // solo con pN es suficiente
       struct Arista *primerNodo, *ultimoNodo;

       // encabezados de funcion
       /*
       void insertarAlInicio (int dato, int peso);
       Arista* borrarAlInicio(void);
       void imprimir(void);
       void insertarAlFinal(int dato, int peso);
       Arista* borrarAlFinal(void);
       Arista* buscar (int dato);//
       int largo (void);//
       bool vacia(void);
       void borrarEnPosicion(int pos);
       int posicion (int);
       */
}ListaAristas;
struct ListaAristas* newListaAristas(){
    struct ListaAristas * l = malloc(sizeof(struct ListaAristas));
    if(l)
        l->primerNodo = l->ultimoNodo = NULL;
    return l;
}

typedef struct Nodo {
       int dato; // parte de datos
       struct ListaAristas * aristas;
       bool visitado;
       struct Nodo* siguiente;// puntero para enlazar nodos
       //void imprimir();

}Nodo;

struct Nodo * newNodo(int d){
    struct Nodo * n = malloc(sizeof(struct Nodo));
    if(n){
        n->dato = d;
        n->aristas = newListaAristas();
        n->visitado = false;
        n->siguiente = NULL;
    }
    return n;
};


typedef struct ListaSimple {
       // solo con pN es suficiente
       struct Nodo *primerNodo, *ultimoNodo;

}ListaSimple;

struct ListaSimple * newListaSimple(){
    struct ListaSimple * l = malloc(sizeof(struct ListaSimple));
    if(l)
        l->primerNodo = l->ultimoNodo = NULL;
    return l;
}

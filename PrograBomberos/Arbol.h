#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED
#include <stdbool.h>
//nodos del arbolcaminos
typedef struct NodoEsquina{
    struct NodoEsquina* padre;
    int dato;
    int MAX_HIJOS;
    int numHijos;//no lo pude poner const, pero no cambiar
    struct NodoEsquina* hijos[];//arreglo hijos
}NodoEsquina;

struct NodoEsquina* newNodoEsquina(NodoEsquina* nPadre,int MAX_HIJOS, int nodo){//si es la raiz, el padre es nulo
    struct NodoEsquina * e = malloc(sizeof(struct NodoEsquina)+ sizeof(NodoEsquina)*MAX_HIJOS);
    if(e){
        e->padre = nPadre;
        e->dato = nodo;
        e->MAX_HIJOS = MAX_HIJOS;
        e->numHijos = 0;
        int i;
        for (i=0; i<MAX_HIJOS; i++) e->hijos[i] = NULL;
    }
    return e;
}

void insertarHijoNodoEsquina(struct NodoEsquina*padre, int hijo){
    struct NodoEsquina * nuevo = newNodoEsquina(padre,padre->MAX_HIJOS-1,hijo);
    //el maximo de hijos va a ser 1 menos porque se gasta 1 nodo
    struct NodoEsquina * tmp = padre;
    padre->hijos[padre->numHijos] = nuevo;
    padre->numHijos++;
}

void imprimirHijosNodoEsquina(struct NodoEsquina * nodo){
    int i;
    for (i = 0; i < nodo->numHijos; i++){
        if (nodo->hijos[i] == NULL){
            printf("Es nulo el hijo\n");
            break;
        }
        printf("%d   ",nodo->hijos[i]->dato);
    }
    printf("\n");
}

bool esAncestro (struct NodoEsquina* nodo, int ancestro){
    if (nodo->padre == NULL)
        return false;
    if (nodo->padre->dato == ancestro)
        return true;
    return esAncestro(nodo->padre, ancestro);
}

//arbol que se crea con las soluciones
typedef struct ArbolCaminos{
    struct NodoEsquina * raiz;
}ArbolCaminos;

struct ArbolCaminos * newArbolCaminos(int n, int MAX_HIJOS){
    struct ArbolCaminos * a = malloc(sizeof(struct ArbolCaminos));
    if(a){
        a->raiz = newNodoEsquina(NULL,MAX_HIJOS, n);
    }
    return a;
}


#endif // ARBOL_H_INCLUDED

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
    int i = 0;
    while (tmp != NULL){
        i++;
        printf("CASO #%d",i);
        printf("\n");
        int r = resolverArbolgrafoMatriz(tmp->grafo,tmp->grafo->destino,NULL,0);
        printf("Hay %d", r);
        printf(" rutas desde la estacion de bomberos hasta la esquina %d", tmp->grafo->destino);
        printf("\n");
        tmp = tmp->siguiente;
    }
}

void leerArchivo2(char archivoEntrada[], struct ListaGrafos* l){
  FILE * archivo;
  char caracter;
  int resul = 0;

  archivo = fopen(archivoEntrada, "r");
  struct grafoMatriz * g;


  //leerArchivo
  if (archivo == NULL) {
      printf("\nError de apertura del archivo. \n\n");
  } else {


      while ((caracter = fgetc(archivo)) != EOF){
        //va a leer todo el archivo
        //leer por Casos
        while (caracter != '\n'){
          resul = resul*10 + (caracter-48);
          caracter = fgetc(archivo);

        }//lee el destiino
        g = newgrafoMatriz(resul);
        resul = 0;
        bool ceros = false;
        //lo demas
        while(!ceros){
          int valor1 = 0;
          int valor2 = 0;

          while((caracter = fgetc(archivo)) != ' '){
            valor1 = valor1 * 10 + (caracter-48);
          }//primer valor

          while((caracter = fgetc(archivo)) != '\n'){
            if(caracter == EOF){
                break;
            }
            valor2 = valor2 * 10 + (caracter-48);
          }//segundo valor

          if((valor1 == 0) && (valor2 == 0)){
            insertarAlFinalListaGrafos(l,g);
            ceros=true;
          }else{
            agregarVerticegrafoMatriz(g, valor1);
            agregarVerticegrafoMatriz(g, valor2);
            agregarAristaDoblegrafoMatriz(g,valor1, valor2,1);

          }

      }
      //caracter = fgetc(archivo);
    }
    fclose(archivo);
  }
}

#endif // LISTAGRAFOS_H_INCLUDED

#include "ListaAristas.c"
typedef struct Grafo
{
    struct ListaSimple * vertices;
}Grafo;

struct Grafo * newGrafo(){
    struct Grafo * g = malloc(sizeof(struct Grafo));
    if(g)
        g->vertices = newListaSimple();
    return g;
}

       // para insertar un vertice
void insertarVerticeGrafo(struct Grafo * g,int d)
{
    //valida que no exista
    struct Nodo * tmp = buscarListaSimple(g->vertices,d);
    // si es null no existe, lo inserta
    if (tmp == NULL){
        // solo llama a insertar de lista
        insertarAlFinalListaSimple(g->vertices,d);
    }
            else
            {
                printf("El nodo ",d,"ya existe\n");
            }
       }

void insertarAristaGrafo(struct Grafo*g,int origen, int destino, int peso)
{
    // si existe el vertice inserta
    struct Nodo * tmp = buscarListaSimple(g->vertices,origen);
    struct Nodo * tmpDest = buscarListaSimple(g->vertices,destino);
    if (tmp != NULL){
        if (tmpDest != NULL){
            // si la arista no existe
            struct Arista * arista = buscarListaSimple(tmp->aristas,destino);
            if (arista == NULL){
                insertarAlFinalListaAristas(tmp->aristas,destino,peso);
            }else{
                printf("Arista ya existe\n");
            }
        }else{
            printf("Destino no existe\n");
        }
    }else{
        printf("Nodo origen no existe\n");
    }
}


// IMPRIMIR IMPRIMIR IMPRIMIR
       void imprimirGrafo (struct Grafo * g)
       {
            struct Nodo * tmp = g->vertices->primerNodo;
            while (tmp != NULL)
            {
                 printf("%d",tmp->dato);
                 printf(": ");
                 imprimirListaAristas(tmp->aristas);
                 printf("\n");
                 tmp = tmp -> siguiente;
            }
            printf("\n");
       }
// BORRAR ARISTA  BORRAR ARISTA
void borrarAristaGrafo(struct Grafo *g,int origen, int destino)
{
     struct Nodo * tmp = buscarListaSimple(g->vertices,origen);

     if (tmp != NULL)
     {
        int posA = posicionListaAristas(tmp->aristas,destino);
        if (posA > -1)
        {
            borrarEnPosicionListaAristas(tmp->aristas,posA);
            printf("Eliminada arista %d",origen);
            printf("-%d",destino);
            printf("\n");
        }
        else
        {  }
     }

}



// BORRAR BORRAR BORRAR

void borrarVerticeGrafo (struct Grafo*g, int dato)
{
     // se usan las funciones de lista
     int posV = posicionListaAristas(g->vertices,dato);
     // si lo encontro, posV es <> -1
     if (posV > -1)
     {
        //recorre toda la lista de vertices
        // eliminando aristas a dato
        struct Nodo * tmp = g->vertices->primerNodo;
        while (tmp != NULL)
        {
              // usa borrar arista
              borrarAristaGrafo(g,tmp->dato, dato);
              tmp = tmp->siguiente;
        }
        // ya borro las aristas, ahora el vertice
        borrarEnPosicionListaSimple(g->vertices,posV);
     }
     else
     {
         printf("Vertice no existe\n");
     }
}

// visitar vertice
void visitarVerticeGrafo(struct Grafo*g,int dato)
{
     struct Nodo * tmp = buscarListaSimple(g->vertices,dato);
     if (tmp != NULL)
        tmp->visitado = true;
}

// visitar vertice
bool visitadoVerticeGrafo(struct Grafo*g,int dato)
{
     struct Nodo * tmp = buscarListaSimple(g->vertices,dato);
     if (tmp != NULL)
        return tmp->visitado;
     else
         return false;
}

// limpiar visitados
void limpiarVisitadosGrafo(struct Grafo*g)
{
     struct Nodo * tmp = g->vertices->primerNodo;
     while (tmp != NULL)
     {
           tmp->visitado = false;
           tmp = tmp->siguiente;
     }
}

// visitar Adyacentes

void visitarAdyacentesGrafo(struct Grafo*g,int nodo)
{
     // visita el nodo
     visitarVerticeGrafo(g,nodo);
     printf("%d",nodo);
     printf("-");
     // busca el vertice para recorrer aristas
     struct Nodo * tmp = buscarListaSimple(g->vertices,nodo);
     if (tmp != NULL)
     {
             // recorre las lista de adyacencia
        struct Arista * actual = tmp->aristas->primerNodo;
        while (actual!=NULL)
        {
              // si no esta visitado
            if (visitadoVerticeGrafo(g,actual->dato)==false)
            {
                visitarAdyacentesGrafo(g,actual->dato);
            }

            actual = actual->siguiente;
        }
     }
}

// PROFUNDIDAD - Recorrido por profundidad

void profundidadGrafo(struct Grafo * g)
{
     struct Nodo * tmp = g->vertices->primerNodo;
     // hace un while de n para recorrer todos
     // aun cuando el grafo es disconexo
     while (tmp != NULL)
     {
         if (tmp->visitado == false)
            visitarAdyacentesGrafo(g,tmp->dato);

         tmp = tmp->siguiente;
     }
     limpiarVisitadosGrafo(g);
}

// ANCHURA - recorrido anchura
//se le da el vertice de inicio
void anchuraGrafo(struct Grafo * g, struct Nodo * v)
{
     printf("%d",v->dato);
     printf("  ");
     visitarVerticeGrafo(g,v->dato);// marca el primer nodo
     struct ListaSimple * cola = newListaSimple();
     // mete a la cola los adyacentes del nodo inicial
     struct Arista * aristaTmp = v->aristas->primerNodo;
     while(aristaTmp != NULL)
     {
                     // encola
        encolarListaSimple(cola,aristaTmp->dato);
        // visita el nodo
        visitarVerticeGrafo(g,aristaTmp->dato);
        aristaTmp = aristaTmp -> siguiente;
     }
     // mientras no se vacíe la cola
    while(cola->primerNodo !=NULL)
    {
        // trabaja con el primero de la cola
        struct Nodo * actual = desencolarListaSimple(cola);
        visitarVerticeGrafo(g,actual->dato);
        // imprime el vertice
        printf("%d",actual->dato);
        printf("  ");
        // para cada arista del vertice en la cola
        // va a meter a la cola los adyacentes
        struct Nodo * nodoCola = buscarListaSimple(g->vertices,actual->dato);
        struct Arista * aristaTmp = nodoCola->aristas->primerNodo;

        while (aristaTmp != NULL)
        {
              // si no se ha visitado, se mete en cola
              if (visitadoVerticeGrafo(g,aristaTmp->dato) == false)
              {
                 visitarVerticeGrafo(g,aristaTmp->dato);
                 encolarListaSimple(cola,aristaTmp->dato);
              }
              aristaTmp = aristaTmp->siguiente;
        }
    }
    limpiarVisitadosGrafo(g);




}




// fin struct





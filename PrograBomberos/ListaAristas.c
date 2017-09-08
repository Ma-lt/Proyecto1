#include "ListaSimple.c"

// funcion que inserta un nodo nuevo en la lista
// entradas: el dato a guardar
// salidas: no tiene
void insertarAlInicioListaAristas (struct ListaAristas *l,int dato, int peso)
{
     // si no hay elementos
     if (l->primerNodo == NULL)
     {
         // ambos apuntan al nuevo en memoria
         l->primerNodo = newArista(dato, peso);
         l->ultimoNodo = l->primerNodo; // ambos apuntan al nuevo
     }
     else
     {
         struct Arista *nuevo = newArista(dato, peso);
         // a lo que apunta pN ahora es el segundo
         // por eso, nuevo->siguiente es pN
         nuevo->siguiente = l->primerNodo;
         // ahora devolvemos pN a que apunte al nuevo
         // y primero de las lista
         l->primerNodo = nuevo;
         // el puntero nuevo deja de existir, no se libera
         // memoria porque se pierde la info
     }
}

// funcion que elimina el primer elemento de las lista
// entradas: no tiene
// salidas: el puntero al primer nodo. Este puntero
// en siguiente apuntara a null. No se libera memoria

struct Arista* borrarAlInicioListaAristas(struct ListaAristas*l)
{
      // si no hay elementos, no borra nada, retorna null
      if (l->primerNodo == NULL)
      {
         return NULL;
      }
      else
      {
          // un puntero que apunta al nodo que se
          // "despegara" de la lista y se retorna
          struct Arista* borrado = l->primerNodo;
          // pN se pasa al segundo de la lista
          // porque el primero se eliminara
          l->primerNodo = l->primerNodo->siguiente;
          // el nodo borrado, se debe despegar
          // entonces siguiente apunta a null y no
          // al segundo de la lista que ahora es pN
          borrado->siguiente = NULL;
          // aca se deberia liberar la memoria si no se
          // retornara el borrado
          return borrado;
      }
}


// funcion que recorre toda la lista con pt tmp
// imprimiendo en consola cada dato de nodos
// entradas no tiene
// salidas: no tiene, solo imprime en consola
void imprimirListaAristas(struct ListaAristas*l)
{
     // puntero temporal que avanza
     // por toda la lista
     // apunta a los mismo que pN
     struct Arista *tmp = l->primerNodo;

     // mientras tmp no sea nulo, avanza
     while (tmp != NULL)
     {
           // imprime el dato del nodo en el que esta tmp
           printf("%d",tmp->dato);
           printf("  ");
           // tmp avanza al siguiente nodo
           // esto no puede faltar porque se encicla
           tmp = tmp->siguiente;
     }
}

// funcion que inserta un nodo nuevo al final de la lista
// entradas: el dato a guardar
// salidas: no tiene
void insertarAlFinalListaAristas (struct ListaAristas*l,int dato, int peso)
{
     // si no hay elementos
     if (l->primerNodo == NULL)
     {
         // ambos apuntan al nuevo en memoria
         l->primerNodo = newArista(dato,peso);
         l->ultimoNodo = l->primerNodo; // ambos apuntan al nuevo
     }
     else
     {
         // se crea el nuevo nodo
         struct Arista *nuevo = newArista(dato, peso);
         // uN siguiente debe apuntar al nuevo nodo
         // uN debe apuntar al nuevo nodo enlazado
         l->ultimoNodo->siguiente = nuevo;
         l->ultimoNodo = nuevo;
         // el puntero nuevo deja de existir, no se libera
         // memoria porque se pierde la info
     }
}



// funcion que retorna true si la lista es vacia
// entradas: ninguna
// salidas: true si es no tiene elmentos, false otro caso
bool vaciaListaAristas(struct ListaAristas*l)
{
     // si primerNodo es nulo, no hay elementos
     if (l->primerNodo == NULL)
        return true;
     else
         return false;
}



struct Arista* borrarAlFinalListaAristas(struct ListaAristas*l)
{
      if (vaciaListaAristas(l))
         return NULL;
      // este caso es cuando tiene un solo elemento
      else if (l->primerNodo->siguiente == NULL)
      {
            struct Arista* actual = l->primerNodo;
            l->primerNodo = l->ultimoNodo = NULL;
            return actual;
      }
      else
      {
            // referencia al primero para recorrer la lista
            struct Arista * actual = l->primerNodo;
            // recorre la lista hasta llegar al penultimo nodo
            //while (actual->siguiente != NULL)
            while (actual->siguiente->siguiente != NULL)
              actual = actual->siguiente;

            // al salir actual referencia al penultimo nodo
            // refencia nueva al ultimo nodo para despues retornarlo
            struct Arista* tmp = l->ultimoNodo;
            // ultimo nodo pasa al penultimo
            l->ultimoNodo = actual;
            //le quita el enlace al que era ultimo
            actual->siguiente = NULL;
            // retorna el que desenlazo al final
            return tmp;
        }
}

// LARGO LARGO LARGO
int largoListaAristas(struct ListaAristas*l)
{
    int contador = 0;
     // apunta a los mismo que pN
     struct Arista *tmp = l->primerNodo;

     // mientras tmp no sea nulo, avanza
     while (tmp != NULL)
     {
           contador++;
           // tmp avanza al siguiente nodo
           // esto no puede faltar porque se encicla
           tmp = tmp->siguiente;
     }
     return contador;
}

// BUSCAR BUSCAR BUSCAR
struct Arista * buscarListaAristas(struct ListaAristas*l,int valor)
{

       struct Arista * tmp = l->primerNodo;
       while (tmp!=NULL)
       {
             if (tmp->dato == valor)
                return tmp;

             tmp = tmp->siguiente;

       }

       return NULL;
}

// BORRAR POSICION BORRAR POSICION
// Funcion que elimina el elmento de la lista en una posicion
// esta funcion no retorna el nodo eliminado, por lo que
// si libera memoria
void borrarEnPosicionListaAristas(struct ListaAristas*l,int pos)
{
     // si esta vacia no borra
        if (vaciaListaAristas(l))
        { }
        // pos 0 borra el inicio
        else
        if (pos == 0)
        {
            // borrar al inicial no libera memoria, se hace
            // luego de llamar a la funcion
            struct Arista * borrado = borrarAlInicioListaAristas(l);

            if (borrado != NULL)
               free(borrado);

        }
        else
        {
            //recorre la lista hasta el nodo previo a eliminar
            struct Arista *actual = l->primerNodo;
            // deja el puntero en el nodo antes a eliminar
            int i;
            for (i=1; i < pos && actual->siguiente != NULL;i++)
                actual=actual->siguiente;

            // si es el ultimo borra el final
            if (actual->siguiente == NULL)
            {
                 // borrar al final no libera memoria, se hace
                 // luego de llamar a la funcion
                 struct Arista* borrado = borrarAlFinalListaAristas(l);
                 if (borrado != NULL)
                        free(borrado);
            }
            else
            {
                //referencia tmp que apunta al que se eliminara
                struct Arista *tmp = actual->siguiente;
                // anterior a borrar siguiente será el sig.sig
                actual->siguiente = actual->siguiente->siguiente;
                // el que se eliminara.sig sera null
                tmp->siguiente = NULL;
                free(tmp);
            }
        }
    }

// POSICION POSICION
int posicionListaAristas(struct ListaAristas*l,int valor)
{
    int pos = 0;
    struct Arista * tmp = l->primerNodo;
    while (tmp!=NULL)
    {
        if (tmp->dato == valor)
            return pos;

        pos++;
        tmp = tmp->siguiente;

    }

    return -1;
}




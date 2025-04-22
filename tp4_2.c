#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Tarea{
    int TareaID;            // Autoincremental, comienza en 1000
    char *Descripcion;
    int Duracion;           // Entre 10 y 100
}typedef Tarea;

struct Nodo {
    Tarea T;
    struct Nodo *Siguiente;
}typedef Nodo;

Tarea crearTarea(int *tareaId, char *descripcion){
    Tarea nueva;
    nueva.TareaID = (*tareaId)++;
    int longitud = strlen(descripcion) + 1;
    nueva.Descripcion = malloc(sizeof(char)*longitud);
    strcpy(nueva.Descripcion, descripcion);
    nueva.Duracion = 10 + rand()% 100;
    return nueva;
} 

void mostrarTarea(Tarea tarea){
    printf("Tarea numero: %d\n", tarea.TareaID);
    printf("Nombre : %s\n", tarea.Descripcion);
    printf("Duracion: %d\n", tarea.Duracion);
    printf("\n");
}

void agregarTarea(Nodo **lista, Tarea tarea){
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    nuevoNodo->T = tarea;
    nuevoNodo->Siguiente = *lista;
    *lista = nuevoNodo;
}

Nodo *crearNodo(Tarea tarea){
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    nuevoNodo->T = tarea;
    nuevoNodo->Siguiente = NULL;
    return nuevoNodo;
}

Nodo *crearListaVacia(){
    return NULL;
}

void insertarNodoEnLista(Nodo ** lista, Nodo *nodo){
    nodo->Siguiente = *lista;
    *lista = nodo;
}

bool esListaVacia(Nodo *lista){
    
    if (lista == NULL) {
        return true;
    } else {
        return false;
    }
}

void mostrarLista(Nodo *lista, char *nombre){
    if (esListaVacia(lista))
    {
        printf("Lista Vacia\n");
    }else
    {
        printf("\tListado de: %s\n", nombre);
        while (!esListaVacia(lista))
        {
            mostrarTarea(lista->T);
            lista = lista->Siguiente;
        }
    }
}

int longitudLista(Nodo *lista){
    int cantidad = 0;
    if (esListaVacia(lista))
    {
        return 0;
    }else
    {
        while (!esListaVacia(lista))
        {
            cantidad++;
            lista = lista->Siguiente;
        }
    }
    return cantidad;
    
    
}

int main (){
    int id = 1000;
    Nodo * lista = crearListaVacia();
    printf("Cantidad de nodos en la lista: %d\n", longitudLista(lista));
    mostrarLista(lista, "tareas");

    Tarea tarea1 = crearTarea(&id, "Carne");
    Tarea tarea2 = crearTarea(&id, "Pollo");
    Tarea tarea3 = crearTarea(&id, "Pescado");

    Nodo *nodo1 = crearNodo(tarea1);
    Nodo *nodo2 = crearNodo(tarea2);
    Nodo *nodo3 = crearNodo(tarea3);

    insertarNodoEnLista(&lista, nodo1);
    insertarNodoEnLista(&lista, nodo2);
    insertarNodoEnLista(&lista, nodo3);

    mostrarLista(lista, "tareas");
    printf("Cantidad de nodos en la lista: %d\n", longitudLista(lista));
    return 0;
}
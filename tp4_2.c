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

Tarea crearTarea(int *tareaId, char *descripcion, int duracion){
    Tarea nueva;
    nueva.TareaID = (*tareaId)++;
    int longitud = strlen(descripcion) + 1;
    nueva.Descripcion = malloc(sizeof(char)*longitud);
    strcpy(nueva.Descripcion, descripcion);
    nueva.Duracion = duracion;
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
        printf("\tListado de Tareas: %s\n", nombre);
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

void moverTareaRealizada(Nodo **pendiente,Nodo **realizada){
    int id;
    printf("Ingrese el id de la tarea para marcar como realizada: \n");
    scanf("%d", &id);
    while (id != 0)
    {
        Nodo *anterior = NULL;
        Nodo *actual = *pendiente;
        while (actual != NULL && actual->T.TareaID != id)
        {
            anterior = actual;
            actual = actual->Siguiente;
        }
        if (actual == NULL)
        {
            printf("No se encontró la tarea con ID %d.\n", id);
        }else{
            if (anterior == NULL)
            {
                *pendiente = actual->Siguiente;
            }else{
                anterior->Siguiente = actual->Siguiente;
            }
            insertarNodoEnLista(realizada, actual);
            printf("Tarea %d movida a realizadas\n", id);
        }
        printf("\nIngrese otro ID de tarea para marcar como realizada: \nIngrese 0 para salir\n");
        scanf("%d", &id);
    }
    
}

Nodo *buscarNodo(Nodo *lista, int id, char *clave){
    Nodo *aux = lista;
    while (aux != NULL)
    {
        if (aux->T.TareaID == id && id != -1)
        {
            return aux;
        }
        if (clave != NULL && strlen(clave) > 0 && strstr(aux->T.Descripcion, clave))
        {
            return aux;
        }
        aux = aux->Siguiente;
    }
    return NULL;
}

void liberarLista(Nodo *lista) {
    Nodo *aux;
    while (lista != NULL) {
        aux = lista;
        lista = lista->Siguiente;
        free(aux->T.Descripcion);
        free(aux);
    }
}

int main (){
    int id = 1000, seguir = 1, transferir, buscar, nuevoId = -1;
    char clave[50]="";
    Nodo * lista = crearListaVacia();
    printf("Cantidad de nodos en la lista: %d\n", longitudLista(lista));
    mostrarLista(lista, "tareas");

    while (seguir == 1)
    {
        char nombre[50];
        int tiempo;

        printf("Ingrese la descripcion de la tarea:\n");
        fflush(stdin);
        gets(nombre);
        nombre[strcspn(nombre, "\n")] = 0;

        do
        {
            printf("Ingrese la duracion de la tarea entre 10 y 100: \n");
            scanf("%d", &tiempo);
        } while (!(tiempo > 9 && tiempo < 101));
        
        Tarea nueva = crearTarea(&id, nombre, tiempo);
      
        Nodo *nodo = crearNodo(nueva);
        
        insertarNodoEnLista(&lista, nodo);
        printf("Desea ingresar otra tarea\n1-SI\n2-NO\n");
        scanf("%d", &seguir);
    }
    
    mostrarLista(lista, "Tareas");
    Nodo *listaRealizadas = crearListaVacia();
    printf("\nDesea transferir tareas a la lista de realizadas\n");
    printf("1-Si\n2-No\n");
    scanf("%d", &transferir);
    if (transferir == 1) {
        moverTareaRealizada(&lista, &listaRealizadas);
        mostrarLista(lista, "Pendientes");
        mostrarLista(listaRealizadas, "Realizadas");
    }else{
        mostrarLista(lista, "Pendientes");
    }

    printf("Quiere buscar por:\n1-Nombre\n2-Id");
    scanf("%d", &buscar);

    if (buscar == 1)
    {
        nuevoId = -1;
        printf("Ingrese el nombre:\n");
        fflush(stdin);
        gets(clave);

    }else{
        clave[0] = '\0';
        printf("Ingrese el id:\n");
        scanf("%d", &nuevoId);
    }
    Nodo *encontrar = buscarNodo(lista, nuevoId, clave);
    if (encontrar != NULL) {
        printf("Tarea encontrada en PENDIENTES:\n");
        mostrarTarea(encontrar->T);
    } else {
        encontrar = buscarNodo(listaRealizadas, nuevoId, clave);
        if (encontrar != NULL) {
            printf("Tarea encontrada en REALIZADAS:\n");
            mostrarTarea(encontrar->T);
        } else {
            printf("No se encontró la tarea.\n");
        }
    }
    

    liberarLista(lista);
    liberarLista(listaRealizadas);
   /* Tarea tarea1 = crearTarea(&id, "Carne");
    Tarea tarea2 = crearTarea(&id, "Pollo");
    Tarea tarea3 = crearTarea(&id, "Pescado");

    Nodo *nodo1 = crearNodo(tarea1);
    Nodo *nodo2 = crearNodo(tarea2);
    Nodo *nodo3 = crearNodo(tarea3);

    insertarNodoEnLista(&lista, nodo1);
    insertarNodoEnLista(&lista, nodo2);
    insertarNodoEnLista(&lista, nodo3);

    mostrarLista(lista, "tareas");
    printf("Cantidad de nodos en la lista: %d\n", longitudLista(lista));*/
    return 0;
}
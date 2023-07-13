#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tarea
{
    int TareaID; // Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
} Tarea;

typedef struct Nodo
{
    Tarea T;
    struct Nodo *siguiente;
} Nodo;

void ToDo();
void AgregarTarea(Nodo **L);
Nodo *CrearListaVacia();
Nodo *CrearNodo(Tarea tarea);
void InsertarNodo(Nodo **L, Tarea tarea);
void mostrarTareas(Nodo *L);
void EliminarNodo(Nodo **nodo, int id);
void LiberarNodo(Nodo *nodo);
Nodo *BuscarTareaPorId(Nodo *tareas, int id);
Nodo *BuscarTareaPorPalabra(Nodo *tareas, char *palabra);
void LiberarLista(Nodo *L);

int main()
{
    ToDo();

    return 0;
}

void ToDo()
{
    int realizada;
    Nodo *L, *TareasPendientes, *TareasRealizadas, *tarea;

    L = CrearListaVacia();
    TareasPendientes = CrearListaVacia();
    TareasRealizadas = CrearListaVacia();

    AgregarTarea(&L);

    puts("\n-LISTA DE TAREAS-\n");

    mostrarTareas(L);

    // Pasar todas las tareas a pendientes

    Nodo *auxL = L;

    while (auxL)
    {

        InsertarNodo(&TareasPendientes, auxL->T);
        auxL = auxL->siguiente;
    }

    // Preguntar si se realizo la tarea

    Nodo *auxP = TareasPendientes;

    while (auxP)
    {

        printf("\nSe realizo la tarea %d?  1.SI 2.NO:  ", auxP->T.TareaID);
        scanf("%d", &realizada);

        if (realizada == 1)
        {

            InsertarNodo(&TareasRealizadas, auxP->T);

            EliminarNodo(&TareasPendientes, auxP->T.TareaID);
        }

        auxP = auxP->siguiente;
    }

    puts("\n\nTAREAS REALIZADAS\n");

    mostrarTareas(TareasRealizadas);

    puts("\n\nTAREAS PENDIENTES\n");

    mostrarTareas(TareasPendientes);

    // Buscar Tarea

    int opcion;
    int id;
    char palabra[20];

    puts("\n\nBUSCAR TAREA\n");
    puts("1. Por Id");
    puts("2. Por Palabra");
    scanf("%d", &opcion);

    switch (opcion)
    {
    case 1:

        puts("\n\nBUSCAR TAREA \n");
        printf("Ingrese el ID: ");
        scanf("%d", &id);
        tarea = BuscarTareaPorId(L, id);
        if (tarea)
        {
            printf("\nTAREA %d\n", tarea->T.TareaID);
            printf("Descripcion: %s", tarea->T.Descripcion);
            printf("\nDuracion: %d", tarea->T.Duracion);
        }
        else
        {
            puts("\nNo se encuentra la tarea");
        }

        break;
    case 2:

        puts("\n\nBUSCAR TAREA POR PALABRA \n");
        printf("Ingrese la palabra: ");
        scanf("%s", palabra);
        tarea = BuscarTareaPorPalabra(L, palabra);
        if (tarea)
        {
            printf("\nTAREA %d\n", tarea->T.TareaID);
            printf("Descripcion: %s", tarea->T.Descripcion);
            printf("\nDuracion: %d", tarea->T.Duracion);
        }
        else
        {
            puts("\nNo se encuentra la tarea");
        }
        break;

    default:
        puts("\nOpcion incorrecta\n");
        break;
    }

    // Liberar memoria

    LiberarLista(L);
    LiberarLista(TareasPendientes);
    LiberarLista(TareasRealizadas);
    LiberarLista(tarea);

}

Nodo *CrearListaVacia()
{
    return NULL;
}

Nodo *CrearNodo(Tarea tarea)
{
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    nuevo->T = tarea;
    nuevo->siguiente = NULL;
    return nuevo;
}

void InsertarNodo(Nodo **L, Tarea tarea)
{
    Nodo *nuevo = CrearNodo(tarea);
    nuevo->siguiente = *L;
    *L = nuevo;
}

void AgregarTarea(Nodo **L)
{
    int add = 0, i = 0;

    printf("\nQuiere ingresar una tarea: 1.SI 2.NO: ");
    scanf("%d", &add);

    while (add == 1)
    {
        Tarea nueva;

        nueva.TareaID = i;

        printf("Tarea %d \n", nueva.TareaID);

        char cadena[50];
        puts("Ingrese la descripcion:");
        gets(cadena);

        nueva.Descripcion = malloc(sizeof(char) * (strlen(cadena) + 1));

        strcpy(nueva.Descripcion, cadena);

        puts("Ingrese la duracion:");
        scanf("%d", &nueva.Duracion);

        InsertarNodo(L, nueva);

        printf("Quiere ingresar otra tarea: 1.SI 2.NO: ");
        scanf("%d", &add);

        i++;
    }
}

void mostrarTareas(Nodo *L)
{
    Nodo *aux = L;
    while (aux != NULL)
    {
        printf("\nTAREA %d\n", aux->T.TareaID);
        printf("Descripcion: %s", aux->T.Descripcion);
        printf("\nDuracion: %d", aux->T.Duracion);

        aux = aux->siguiente;
    }
}

void EliminarNodo(Nodo **nodo, int id)
{
    int DatoBuscado = id;

    Nodo *Aux = *nodo;
    Nodo *AuxAnterior = *nodo;
    while (Aux && Aux->T.TareaID != DatoBuscado)
    {
        AuxAnterior = Aux;
        Aux = Aux->siguiente;
    }
    if (Aux)
    {
        if (Aux == *nodo)
        {
            *nodo = Aux->siguiente;
        }
        else
        {
            AuxAnterior->siguiente = Aux->siguiente;
        }

        LiberarNodo(Aux);
    }
}

void LiberarNodo(Nodo *nodo)
{
    if (nodo)
    {
        free(nodo);
    }
}

Nodo *BuscarTareaPorId(Nodo *tareas, int id)
{

    while (tareas)
    {

        if (tareas->T.TareaID == id)
        {

            return tareas;
        }
        tareas = tareas->siguiente;
    }

    return NULL;
}

Nodo *BuscarTareaPorPalabra(Nodo *tareas, char *palabra)
{

    while (tareas)
    {
        if (strstr(tareas->T.Descripcion, palabra) != NULL)
        {
            return tareas;
        }
        tareas = tareas->siguiente;
    }

    return NULL;
}

void LiberarLista(Nodo *L)
{
    Nodo *actual = L;
    Nodo *siguiente;

    while (actual)
    {
        siguiente = actual->siguiente;
        free(actual->T.Descripcion);
        free(actual);
        actual = actual->siguiente;
    }
}
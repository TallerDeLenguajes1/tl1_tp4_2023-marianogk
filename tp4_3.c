#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int TareaID; // Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
} Tarea;

typedef struct
{
    Tarea T;
    struct Nodo *siguiente;
} Nodo;

typedef Nodo *Lista;

void ToDo();
void AgregarTarea(Lista *L);
Lista CrearListaVacia();
Nodo *CrearNodo(Tarea tarea);
void InsertarNodo(Lista *L, Tarea tarea);
void mostrarTareas(Lista L);
void EliminarNodo(Lista *L, int id);
void LiberarNodo(Nodo *nodo);
Nodo *BuscarTareaPorId(Nodo *tareas, int id);
Nodo *BuscarTareaPorPalabra(Nodo *tareas, char *palabra);

int main()
{
    ToDo();

    return 0;
}

void ToDo()
{
    int realizada;
    Lista L, TareasPendientes, TareasRealizadas;

    L = CrearListaVacia();
    TareasPendientes = CrearListaVacia();
    TareasRealizadas = CrearListaVacia();

    AgregarTarea(&L);

    puts("\n-LISTA DE TAREAS-\n");

    mostrarTareas(L);

    // Pasar todas las tareas a pendientes

    Lista auxL = L;

    while (auxL)
    {

        InsertarNodo(&TareasPendientes, auxL->T);
        auxL = auxL->siguiente;
    }

    // Preguntar si se realizo la tarea

    Lista auxP = TareasPendientes;

    while (auxP)
    {

        printf("\nSe realizo la tarea %d?  1.SI 2.NO:  ", auxP->T.TareaID);
        scanf("%d", &realizada);

        if (realizada == 1)
        {

            InsertarNodo(&TareasRealizadas, auxP->T);

            // EliminarNodo(&TareasPendientes, auxP->T.TareaID);
        }

        auxP = auxP->siguiente;
    }

    puts("\n\nTAREAS REALIZADAS\n");

    mostrarTareas(TareasRealizadas);

    puts("\n\nTAREAS PENDIENTES\n");

    mostrarTareas(TareasPendientes);

    // Buscar Tarea

    // int opcion;
    // int id;
    // char palabra[20];

    // puts("\n\nBUSCAR TAREA\n");
    // puts("1. Por Id");
    // puts("2. Por Palabra");
    // scanf("%d", &opcion);

    // switch (opcion)
    // {
    // case 1:

    //     puts("\n\nBUSCAR TAREA \n");
    //     printf("Ingrese el ID: ");
    //     scanf("%d", &id);
    //     BuscarTareaPorId(L, id);
    //     break;
    // case 2:

    //     puts("\n\nBUSCAR TAREA POR PALABRA \n");
    //     printf("Ingrese la palabra: ");
    //     scanf("%s", palabra);
    //     BuscarTareaPorPalabra(L, palabra);
    //     break;

    // default:
    //     puts("\nOpcion incorrecta\n");
    //     break;
    // }

    // Liberar memoria

    // while (L || nodoPendientes || nodoRealizadas)
    // {
    //     LiberarNodo(L);
    //     LiberarNodo(nodoPendientes);
    //     LiberarNodo(nodoRealizadas);
    // }
    // free(nueva);
    // free(TareasPendientes);
    // free(TareasRealizadas);

    //     aux = listaPendiente
    // listaPendiente = listaPendiente-> siguiente
    // free(aux->tarea.descripcion)
    // free(aux)
}

Lista CrearListaVacia()
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

void InsertarNodo(Lista *L, Tarea tarea)
{
    Nodo *nuevo = CrearNodo(tarea);
    Nodo *Aux = *L;
    nuevo->siguiente = Aux;
    *L = nuevo;
}

void AgregarTarea(Lista *L)
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
        scanf("%s", cadena);

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

void mostrarTareas(Lista L)
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

void EliminarNodo(Lista *L, int id)
{
    int DatoBuscado = id;

    Nodo *Aux = L;
    Nodo *AuxAnterior = L;
    while (Aux && Aux->T.TareaID != DatoBuscado)
    {
        AuxAnterior = Aux;
        Aux = Aux->siguiente;
    }
    if (Aux)
    {
        AuxAnterior->siguiente = Aux->siguiente;
        free(Aux);
    }
}

void LiberarNodo(Nodo *nodo)
{
    if (!nodo)
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
            printf("\nTAREA %d\n", tareas->T.TareaID);
            printf("Descripcion: %s", tareas->T.Descripcion);
            printf("\nDuracion: %d", tareas->T.Duracion);
            return tareas;
        }
        else
        {
            puts("\nNo se encuentra la tarea");
        }
    }
}

Nodo *BuscarTareaPorPalabra(Nodo *tareas, char *palabra)
{

    while (tareas)
    {
        if (strstr(tareas->T.Descripcion, palabra) != NULL)
        {
            printf("\nTAREA %d\n", tareas->T.TareaID);
            printf("Descripcion: %s", tareas->T.Descripcion);
            printf("\nDuracion: %d", tareas->T.Duracion);
            return tareas;
        }
        else
        {
            puts("\nNo se encuentra la tarea");
        }
    }
}
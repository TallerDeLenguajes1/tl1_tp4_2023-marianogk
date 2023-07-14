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
void EliminarTarea(Tarea t, int id);
void MostrarDatos(Nodo *L);

int main()
{
    ToDo();

    return 0;
}

void ToDo()
{
    int realizada;
    Nodo *TareasEnProceso, *TareasPendientes, *TareasRealizadas, *tarea;

    int opcion = 1, id, opTarea;
    char palabra[20];

    TareasEnProceso = CrearListaVacia();
    TareasPendientes = CrearListaVacia();
    TareasRealizadas = CrearListaVacia();

    AgregarTarea(&TareasEnProceso);

    // puts("\n-LISTA DE TAREAS-\n");

    puts("\n\nTAREAS EN PROCESO\n");

    mostrarTareas(TareasEnProceso);
    MostrarDatos(TareasEnProceso);

    puts("\n\nTAREAS PENDIENTES\n");

    mostrarTareas(TareasPendientes);
    MostrarDatos(TareasPendientes);

    puts("\n\nTAREAS REALIZADAS\n");

    mostrarTareas(TareasRealizadas);
    MostrarDatos(TareasRealizadas);

    do
    {
        // Buscar Tarea

        puts("\n\nBUSCAR TAREA \n");
        printf("Ingrese el ID: ");
        scanf("%d", &id);
        tarea = BuscarTareaPorId(TareasEnProceso, id);
        if (tarea)
        {
            puts("Seleccione una opcion:\n");
            printf("1. Mover tarea a Pendientes\n");
            printf("2. Mover tarea a Realizadas\n");
            printf("3. Eliminar tarea\n");
            printf("4. No hacer nada\n");
            scanf("%d", &opTarea);
            switch (opTarea)
            {
            case 1:
                InsertarNodo(&TareasPendientes, tarea->T);
                EliminarNodo(&TareasRealizadas, id);
                break;
            case 2:
                InsertarNodo(&TareasRealizadas, tarea->T);
                EliminarNodo(&TareasPendientes, id);
                break;
            case 3:
                EliminarNodo(&TareasEnProceso, id);
                EliminarNodo(&TareasPendientes, id);
                EliminarNodo(&TareasRealizadas, id);
                tarea = NULL;
                break;
            default:
                break;
            }
        }
        else
        {
            puts("\nNo se encuentra la tarea");
        }

        printf("Desea modificar otra tarea? 1. Si | 2. No: ");
        scanf("%d", &opcion);

        puts("\n\nTAREAS EN PROCESO\n");

        mostrarTareas(TareasEnProceso);

        puts("\n\nTAREAS PENDIENTES\n");

        mostrarTareas(TareasPendientes);

        puts("\n\nTAREAS REALIZADAS\n");

        mostrarTareas(TareasRealizadas);

    } while (opcion == 1);

    // Liberar memoria

    LiberarLista(TareasEnProceso);
    LiberarLista(TareasPendientes);
    LiberarLista(TareasRealizadas);
    LiberarNodo(tarea);
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
        scanf("%s", &cadena);

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
        actual = siguiente;
    }
}

void MostrarDatos(Nodo *L)
{
    Nodo *Aux = L;
    int cantidad = 0, duracion = 0;
    while (Aux)
    {
        cantidad++;
        duracion += Aux->T.Duracion;
        Aux = Aux->siguiente;
    }
    printf("\n\nCantidad de tareas: %d\n", cantidad);
    printf("\nDuracion total: %d", duracion);
}
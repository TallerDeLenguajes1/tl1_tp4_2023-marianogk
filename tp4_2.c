#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct
{
    int TareaID; // Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
} typedef Tarea;

void ToDo();
Tarea BuscarTareaPorId(Tarea tarea[], int cant);
Tarea BuscarTareaPorPalabra(Tarea tarea[], int cant);

int main()
{
    ToDo();

    return 0;
}

void ToDo()
{
    int cant, realizada;

    printf("Ingrese cantidad de tareas: ");
    scanf("%d", &cant);

    Tarea **arreglo = (Tarea **)malloc(sizeof(Tarea *) * cant);
    Tarea **TareasPendientes = (Tarea **)malloc(sizeof(Tarea *) * cant);
    Tarea **TareasRealizadas = (Tarea **)malloc(sizeof(Tarea *) * cant);

    for (int i = 0; i < cant; i++)
    {
        arreglo[i] = malloc(sizeof(Tarea));

        arreglo[i]->TareaID = i;
        printf("Tarea %d \n", arreglo[i]->TareaID);

        char cadena[50];
        puts("Ingrese la descripcion:");
        scanf("%s", cadena);

        arreglo[i]->Descripcion = malloc(sizeof(char) * (strlen(cadena) + 1));

        strcpy(arreglo[i]->Descripcion, cadena);

        puts("Ingrese la duracion:");
        scanf("%d", &arreglo[i]->Duracion);
    }

    puts("\n-LISTA DE TAREAS-\n");
    int k = 0;

    for (int i = 0; i < cant; i++)
    {

        TareasPendientes[i] = arreglo[i];

        printf("\nTAREA %d\n", arreglo[i]->TareaID);
        printf("Descripcion:");
        puts(arreglo[i]->Descripcion);
        printf("Duracion: %d", arreglo[i]->Duracion);
        printf("\nSe realizo la tarea %d?  1.SI 2.NO:  ", arreglo[i]->TareaID);
        scanf("%d", &realizada);

        if (realizada == 1)
        {
            TareasRealizadas[k] = TareasPendientes[i];
            TareasPendientes[i] = NULL;
            k++;
        }
    }

    // puts("\n\nTAREAS REALIZADAS\n");

    // for (int i = 0; i < k; i++)
    // {
    //     if (TareasRealizadas[i] != NULL)
    //     {
    //         printf("\nTAREA %d\n", TareasRealizadas[i]->TareaID);
    //         printf("Descripcion: %s", TareasRealizadas[i]->Descripcion);
    //         printf("\nDuracion: %d", TareasRealizadas[i]->Duracion);
    //     }
    // }

    // puts("\n\nTAREAS PENDIENTES\n");

    // for (int i = 0; i < cant; i++)
    // {
    //     if (TareasPendientes[i] != NULL)
    //     {
    //         printf("\nTAREA %d\n", TareasPendientes[i]->TareaID);
    //         printf("Descripcion: %s", TareasPendientes[i]->Descripcion);
    //         printf("\nDuracion: %d", TareasPendientes[i]->Duracion);
    //     }
    // }

    // Buscar Tarea

    // BuscarTareaPorId(*arreglo,cant);

    BuscarTareaPorPalabra(*arreglo,cant);

    // Liberar memoria

    for (int i = 0; i < cant; i++)
    {
        free(arreglo[i]);
        free(TareasPendientes[i]);
        free(TareasRealizadas[i]);
    }
    free(arreglo);
    free(TareasPendientes);
    free(TareasRealizadas);
}

Tarea BuscarTareaPorId(Tarea tarea[],int cant)
{
    int id;

    puts("\n\nBUSCAR TAREA POR ID\n");
    printf("Ingrese el ID: ");
    scanf("%d",&id);

    for (int i = 0; i < cant; i++)
    {
        if (tarea[i].TareaID == id)
        {
            printf("\nTAREA %d\n", tarea[i].TareaID);
            printf("Descripcion: %s", tarea[i].Descripcion);
            printf("\nDuracion: %d", tarea[i].Duracion);
        }
    }
    
}

Tarea BuscarTareaPorPalabra(Tarea tarea[],int cant)
{
    char palabra[20];

    puts("\n\nBUSCAR TAREA POR PALABRA \n");
    printf("Ingrese la palabra: ");
    scanf("%s",palabra);

    for (int i = 0; i < cant; i++)
    {
        if (strstr(tarea[i].Descripcion,palabra) != NULL)
        {
            printf("\nTAREA %d\n", tarea[i].TareaID);
            printf("Descripcion: %s", tarea[i].Descripcion);
            printf("\nDuracion: %d", tarea[i].Duracion);
        } else
        {
            puts("\nNo se encuentra la tarea");
        }
        
    }
    
}
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
    Tarea **TareasPendientes = arreglo;
    Tarea **TareasRealizadas = arreglo;

    for (int i = 1; i <= cant; i++)
    {
        arreglo[i] = malloc(sizeof(Tarea));

        arreglo[i]->TareaID = i;
        printf("Tarea %d \n", arreglo[i]->TareaID);

        char cadena[50];
        puts("Ingrese la descripcion:");
        scanf("%s", &cadena);

        arreglo[i]->Descripcion = malloc(sizeof(char) * (strlen(cadena) + 1));

        strcpy(arreglo[i]->Descripcion, cadena);

        puts("Ingrese la duracion:");
        scanf("%d", &arreglo[i]->Duracion);
    }

    puts("\n-LISTA DE TAREAS-\n");

    for (int i = 1; i <= cant; i++)
    {
        
        TareasPendientes[i] = arreglo[i];

        printf("\nTAREA %d\n", arreglo[i]->TareaID);
        printf("Descripcion:");
        puts(arreglo[i]->Descripcion);
        printf("Duracion: %d", arreglo[i]->Duracion);
        printf("\nSe realizo la tarea %d?  1.SI 0.NO:  ", arreglo[i]->TareaID);
        scanf("%d", &realizada);

        for (int j = 1; j <= cant; j++)
        {
            if (realizada == 1)
            {

                TareasRealizadas[j] = TareasPendientes[i];
                TareasPendientes[i] = NULL;
            } else
            {
                TareasRealizadas[j] = NULL;
            }
            
        }
    }

    puts("\n\nTAREAS REALIZADAS\n");

    for (int i = 1; i <= cant; i++)
    {

        printf("\nTAREA %d\n", TareasRealizadas[i]->TareaID);
        printf("Descripcion: %s", TareasRealizadas[i]->Descripcion);
        printf("\nDuracion: %d", TareasRealizadas[i]->Duracion);
    }

    puts("\n\nTAREAS PENDIENTES\n");

    for (int i = 1; i <= cant; i++)
    {

        printf("\nTAREA %d\n", TareasPendientes[i]->TareaID);
        printf("Descripcion: %s", TareasPendientes[i]->Descripcion);
        printf("\nDuracion: %d", TareasPendientes[i]->Duracion);
    }
}

// al final

// for (int i = 0; i < cant; i++)
// {
//     free(arreglo[i]);
// }
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gotoxy.h"


typedef struct
{
    char nombre[30];
    char apellido [30];
    char domicilio [40];
    char telefono[15];
    char email[40];
    int idCliente;
    int bajaCliente;
    int contrasena;
} stCliente;

typedef struct
{
    char descPedido [240];
    float costoPedido;
    char fechaPedido[20];
    int idCliente;
    int idPedido;
    int pedidoAnulado;
} stPedido;

int ** pasarArrayMatriz (int i, int j, char contrasena[]); //Pasa la constraseña (arreglo) a matriz


int main()
{

    return 0;
}


int ** pasarArrayMatriz (int fil, int col, char contrasena[])
{
    int * * aux;
    int k=0;

    aux[i] = (int)malloc(fil*sizeof(int));

    for(i=0; i < fil; i++)
    {
        aux[i] = (int)malloc(col*sizeof(int));
        for(j = 0; j < col; j++)
        {
            aux[i][j] = contrasena[k];
            k++;
        }
    }
    return aux;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
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

char Menu();

int main()
{
    char opcion;
    do
    {
        switch(opcion = Menu())
        {
        case 1:
            system("cls");
            printf("Placeholder");
            system("pause");
            break;
        case 2:
            system("cls");
            printf("Placeholder");
            system("pause");
            break;
        }
    } while (opcion != '0');

    return 0;
}


int * * pasarArrayMatriz (int fil, int col, char contrasena[])
{
    int * * aux;
    int i = 0,j = 0,k=0;

    aux = (int *)malloc(fil*sizeof(int));

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

char Menu()
{
    char resp;
    do
    {
        system("cls");
        printf("============|-----Menu Principal-----|===========\n");
        printf("=\t\t\t\t\t\t=\n");
        printf("=   [ 1 ] Ingresar\t\t\t\t=\n");
        printf("=   [ 2 ] Crear Cuenta\t\t\t\t=\n");
        printf("=   [ 0 ] Salir\t\t\t\t\t=\n");
        printf("=\t\t\t\t\t\t=\n");
        printf("=================================================\n");
        fflush(stdin);
        resp = getche ();
    } while (resp < '0' && resp > '2');
    return resp;
}



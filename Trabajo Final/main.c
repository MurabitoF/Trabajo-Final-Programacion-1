#include <stdio.h>
#include <stdlib.h>
#include "gotoxy.h"
typedef struct
{
    char nombre[30];
    char apellido [30];
    char domicilio [40];
    char telefono;
    char email[40];
    int idCliente;
    int bajaCliente;
    int contrasena;
} stCliente

typedef struct
{
    char descPedido [240];
    float costoPedido;
    char fechaPedido[20];
    int idCliente;
    int idPedido;
    int pedidoAnulado;
} stPedido

int main()
{
    printf("Hello world!\n");
    printf ("hola");
    return 0;
}

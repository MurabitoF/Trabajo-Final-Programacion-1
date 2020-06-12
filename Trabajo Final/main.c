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

void logo();
void menuIngreso();
void menuCliente();
void menuPedido();


int main()
{
    char opcion;
    do
    {
        menuIngreso();
        fflush(stdin);
        opcion = getch();
        switch(opcion)
        {
        case '1':
            system("cls");
            printf("Placeholder");
            system("pause");
            break;
        case '2':
            system("cls");
            printf("Placeholder");
            system("pause");
            break;
        }
    }
    while (opcion != '0');

    return 0;
}

/////////////////////////////////Funciones de Interfaz/////////////////////////////////////////

void logo()
{
    printf("     _     _             _______  _                 _     _\n");
    printf("    | |   | |           (_______)(_)               | |   | |\n");
    printf("    | |___| |  ___   _   _  _     _   ____   ___   | |___| | _____\n");
    printf("    |_____  | / _ \\ | | | || |   | | / ___) /___)  |_____  |(____ |\n");
    printf("     _____| || |_| || |_| || |   | |( (___ |___ |   _____| |/ ___ |\n");
    printf("    (_______| \\___/ |____/ |_|   |_| \\____)(___/   (_______|\\_____|\n");
}
void menuIngreso()
{

    system("cls");
    logo();
    printf("============|-----Menu Principal-----|===========\n");
    printf("=\t\t\t\t\t\t=\n");
    printf("=   [ 1 ] Ingresar\t\t\t\t=\n");
    printf("=   [ 2 ] Crear Cuenta\t\t\t\t=\n");
    printf("=   [ 0 ] Salir\t\t\t\t\t=\n");
    printf("=\t\t\t\t\t\t=\n");
    printf("=================================================\n");
}

void menuCliente()
{
    printf("[ 1 ] Nombre y apellido\n");
    printf("[ 2 ] Domicilio\n");
    printf("[ 3 ] Numero de telefono\n");
    printf("[ 4 ] Direccion de email\n");
    printf("[ 0 ] Volver\n");
}

void menuPedido()
{
    printf("[ 1 ] ID del pedido\n");
    printf("[ 2 ] ID del Cliente\n");
    printf("[ 0 ] Volver\n");
}

int menuLogin (char nombreArchivo[])
{
    FILE * arch = NULL;

    arch = fopen(nombreArchivo, "rb");

    char email[40];
    char password[15];

    if (arch != NULL)
    {
        printf("Email: ");
        scanf("%s", &email);
        printf("Contrase%da: ", 164);
    }
}

//////////////////////////////Funciones de Carga/////////////////////////////////////////////

void registrarCliente(char nombreArchivo[], stCliente client)
{
    FILE * arch = NULL;

    arch = fopen(nombreArchivo,"ab");

    if(arch != NULL)
    {
        fwrite(&client,sizeof(stCliente),1,arch);
        fclose(arch);
    }
}

////////////////////////////////Funciones Busqueda////////////////////////////////////////


///////////////////////////////Funciones de Operacion////////////////////////////////////

int contadorId(char nombreArchivo[])
{
    FILE * arch = NULL;
    int cant = 0;

    arch = fopen(nombreArchivo, "rb");

    if(arch != NULL)
    {
        fseek(arch, 0, SEEK_END);
        cant = ftell(arch)/ sizeof(stCliente);
        fclose(arch);
    }

    return cant;
}

//////////////////////////////Funciones de Muestra//////////////////////////////////////
















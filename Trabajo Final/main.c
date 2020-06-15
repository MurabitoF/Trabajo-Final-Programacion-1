#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "gotoxy.h"

//Estructura de cliente
typedef struct
{
    char nombreApellido[40];
    char domicilio [40];
    char telefono[15];
    char email[40];
    int idCliente;
    int bajaCliente;
    int * password;
    int admin;
} stCliente;
//Estructura de pedidos
typedef struct
{
    char descPedido [20][50];
    float costoPedido;
    char fechaPedido[20];
    int idCliente;
    int idPedido;
    int productos;
    int pedidoAnulado;
} stPedido;
//Estructura de productos
typedef struct
{
    char descProd[50];
    float precioProd;
    int idProducto;
} stProducto;

/////////////////Funciones de Interfaz//////////////////////
void logo();

void menu();

//////////////////////////////Funciones de Carga/////////////////////////////////////////////
void crearCliente(char nombreArchivo[]);  //Ingresa los datos por teclado los datos para crear un cliente.

void registrarCliente(char nombreArchivo[], stCliente client); //Registra un cliente en un archivo.

void crearPedido(char nombreArchivo[], stProducto carro[], int cantProd, int idCliente); //Completa los datos para crear un pedido.

void registrarPedido(char nombreArchivo[], stPedido pedid);  //Registra un pedido en un archivo.

void crearProducto(char nombreArchivo[]);  //Ingresa por teclado los datos para crear un producto.

void registrarProducto(char nombreArchivo[], stProducto prod);  //Registra un producto en un archivo.

////////////////////////////////Funciones Busqueda////////////////////////////////////////
int encuentraCliente (char nombreArchivo[], char dato[]);  //Busca si existe un cliente en base a su email.

int encontroProducto(FILE * archivo, int idProd);  //Busca un producto en un archivo, si lo encuentra devuelve 1 en caso contrario 0.

///////////////////////////////Funciones de Operacion////////////////////////////////////
int contadorDatos(char nombreArchivo[], int byte); //Cuenta cuantos bloques de datos hay en un archivo y devuelve el valor.

void fechaHora(char * fecha[]); //Devuelve la fecha y la hora del sistema.

float totalCarrito(stProducto carro[], int cantProd);  //Cuenta el total del carrito de compras.

void llenarCarrito(char nombreArchivo[], stProducto carro[], int idProd, int cantProd); //Carga el carrito de compras con productos.

void encriptarPass(char password[], int encript[],int col);

void multMatrices(int col, int M1[3][3], int M2[3][col], int M3[3][col]);

void pasarArrayMatriz (int fil, int col, int mat[fil][col],char contrasena[]);

//////////////////////////////Funciones de Muestra//////////////////////////////////////
void mostrarCliente(stCliente client); //Muestra un cliente, con formato.

void mostrarPedido(stPedido pedido); //Muestra un pedido, con formato.

void mostrarProducto(stProducto product); //Muestra un productos, con formato.

void mostrarClientes(char nombreArchivo[]);  //Muestra todos los clientes en un archivo.

void mostrarPedidos(char nombreArchivo[]);  //Muestra todos los pedidos en un archivo.

void mostrarProductos(char nombreArchivo[]); //Muestra todos los productos en un archivo.

const char aClientes[] = {"clientes.dat"};
const char aPedidos[] = {"pedidos.dat"};
const char aProductos[] = {"productos.dat"};

int main()
{
    char opcion;
    do
    {
        menu();
        fflush(stdin);
        scanf("%c",&opcion);
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
    color(12);
    printf("     _     _             _______  _                 _     _\n");
    printf("    | |   | |           (_______)(_)               | |   | |\n");
    printf("    | |___| |  ___   _   _  _     _   ____   ___   | |___| | _____\n");
    printf("    |_____  | / _ \\ | | | || |   | | / ___) /___)  |_____  |(____ |\n");
    printf("     _____| || |_| || |_| || |   | |( (___ |___ |   _____| |/ ___ |\n");
    printf("    (_______| \\___/ |____/ |_|   |_| \\____)(___/   (_______|\\_____|\n");
    printf("\n\n");
    color(15);
}
void menu()
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

//////////////////////////////Funciones de Carga/////////////////////////////////////////////

void crearCliente(char nombreArchivo[])  //Ingresa los datos por teclado los datos para crear un cliente.
{
    stCliente client;
    int cant = 0;
    char pass[100];

    printf("Nombre: ");
    fflush(stdin);
    gets(client.nombreApellido);
    while(strlen(client.nombreApellido)>40)
    {
        printf("Error! Nombre muy largo.\n");
        printf("Nombre: ");
        fflush(stdin);
        gets(client.nombreApellido);
    }
    printf("Domicilio: ");
    fflush(stdin);
    gets(client.domicilio);
    while(strlen(client.domicilio)>40)
    {
        printf("Error! Domicilio muy largo\n");
        printf("Domicilio: ");
        fflush(stdin);
        gets(client.domicilio);
    }
    printf("Telefono: ");
    fflush(stdin);
    gets(client.telefono);
    while(strlen(client.telefono)>15)
    {
        printf("Error! Numero no apto.\n");
        printf("Nombre: ");
        fflush(stdin);
        gets(client.telefono);
    }
    printf("Email: ");
    fflush(stdin);
    scanf("%s", client.email);
    while(strlen(client.email)>40)
    {
        printf("Error! Email no apto.\n");
        printf("Email: ");
        fflush(stdin);
        gets(client.email);
    }

    printf("Contrase%ca: ",164);
    fflush(stdin);
    scanf("%s", &pass);
    cant = 1 + (strlen(pass) / 3);

    client.password = (int *)malloc((3*cant)*sizeof(int));

    encriptarPass(pass, client.password, cant);

    client.idCliente = contadorDatos(nombreArchivo, sizeof(stCliente)) + 1;
    printf("%d \n", client.idCliente);
    client.bajaCliente = 0;
    client.admin = 0;

    if(!encuentraCliente(nombreArchivo, client.email))
    {
        registrarCliente(nombreArchivo, client);
    }
    else
    {
        printf("El usuario ya esta registrado.\n");
        system("pause");
    }
}

void registrarCliente(char nombreArchivo[], stCliente client)  //Registra un cliente en un archivo.
{
    FILE * arch = NULL;

    arch = fopen(nombreArchivo,"ab");

    if(arch != NULL)
    {
        fwrite(&client,sizeof(stCliente),1,arch);
        fclose(arch);
    }
}

void crearPedido(char nombreArchivo[], stProducto carro[], int cantProd, int idCliente) //Completa los datos para crear un pedido.
{
    stPedido pedido;
    int i;

    pedido.idPedido = contadorDatos(nombreArchivo, sizeof(stPedido)) + 1;
    for(i = 0; i < cantProd; i++)
    {
        strcpy(pedido.descPedido[i],carro[i].descProd);
    }
    pedido.costoPedido = totalCarrito(carro, cantProd);
    pedido.idCliente = idCliente;
    pedido.pedidoAnulado = 0;
    fechaHora(&pedido.fechaPedido);
    pedido.productos = cantProd;

    registrarPedido(nombreArchivo, pedido);
}

void registrarPedido(char nombreArchivo[], stPedido pedid)  //Registra un pedido en un archivo.
{
    FILE * arch = NULL;

    arch = fopen(nombreArchivo,"ab");

    if(arch != NULL)
    {
        fwrite(&pedid,sizeof(stPedido),1,arch);
        fclose(arch);
    }
}

void crearProducto(char nombreArchivo[])  //Ingresa por teclado los datos para crear un producto
{
    stProducto produc;

    printf("Cargando Productos\n\n");
    printf("Ingrese una descripcion del producto: ");
    fflush(stdin);
    gets(produc.descProd);
    printf("Precio del producto: $");
    scanf("%f", &produc.precioProd);
    produc.idProducto = contadorDatos(nombreArchivo, sizeof(stProducto)) + 1;

    registrarProducto(nombreArchivo, produc);
}

void registrarProducto(char nombreArchivo[], stProducto prod)  //Registra un producto en un archivo.
{
    FILE * arch = NULL;

    arch = fopen(nombreArchivo,"ab");

    if(arch != NULL)
    {
        fwrite(&prod,sizeof(stProducto),1,arch);
        fclose(arch);
    }
}

////////////////////////////////Funciones Busqueda////////////////////////////////////////

int encuentraCliente (char nombreArchivo[], char dato[])  //Busca si existe un cliente en base a su email.
{
    int ctrl=0;
    stCliente cliente;

    FILE * archi = NULL;
    archi = fopen(nombreArchivo,"rb");

    if(archi != NULL)
    {
        while (fread(&cliente, sizeof(stCliente), 1, archi) > 0 && !ctrl)
        {
            if (strcmpi(cliente.email, dato) == 0)
            {
                ctrl=1;
            }
        }
        fclose(archi);
    }

    return ctrl;
}

int encontroProducto(FILE * archivo, int idProd)  //Busca un producto en un archivo, si lo encuentra devuelve 1 en caso contrario 0.
{
    int ctrl = 0;
    stProducto prod;

    while(fread(&prod, sizeof(stProducto), 1, archivo)>0 && !ctrl)
    {
        if(idProd == prod.idProducto)
        {
            ctrl = 1;
        }
    }

    if(ctrl && !feof(archivo))
    {
        fseek(archivo,-1*sizeof(stProducto),SEEK_CUR);
    }

    return ctrl;
}

///////////////////////////////Funciones de Operacion////////////////////////////////////

int contadorDatos(char nombreArchivo[], int byte) //Cuenta cuantos bloques de datos hay en un archivo y devuelve el valor.
{
    FILE * arch = NULL;
    int cant = 0;

    arch = fopen(nombreArchivo, "rb");

    if(arch != NULL)
    {
        fseek(arch, 0, SEEK_END);
        cant = ftell(arch)/ byte;
        fclose(arch);
    }

    return cant;
}

void fechaHora(char * fecha[]) //Devuelve la fecha y la hora del sistema.
{
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char formato[] = {"%d/%m/%y %H:%M"};

    strftime(fecha,20,formato,tlocal);
}

float totalCarrito(stProducto carro[], int cantProd)  //Cuenta el total del carrito de compras.
{
    float total = 0;
    int i;

    for(i = 0; i < cantProd; i++)
    {
        total += carro[i].precioProd;
    }

    return total;
}

void llenarCarrito(char nombreArchivo[], stProducto carro[], int idProd, int cantProd) //Carga el carrito de compras con productos.
{
    FILE * archi = NULL;
    archi = fopen(nombreArchivo,"rb");

    stProducto aux;

    if(archi != NULL)
    {
        if(encontroProducto(archi,idProd))
        {
            fseek(archi,-1*sizeof(stProducto),SEEK_CUR);
            fread(&aux,sizeof(stProducto),1,archi);
            carro[cantProd] = aux;
        }
        fclose(archi);
    }
}

void encriptarPass(char password[], int encript[],int col)
{
    int i,j,k=0;
    int codigo[3][3]=
    {
        {1,2,3},
        {0,1,2},
        {2,1,1},
    };
    int matriz[3][col];
    int encrip[3][col];

    pasarArrayMatriz(3,col,matriz,password);

    multMatrices(col,codigo,matriz,encrip);

    for(j = 0; j < col; j++)
    {
        for(i=0; i < 3; i++)
        {
            encript[k] = encrip[i][j];
            k++;
        }
    }
}

void multMatrices(int col, int M1[3][3], int M2[3][col], int M3[3][col])
{
    int i,j,k;
    int aux = 0;

    for(k = 0; k < 3; k++)
    {
        for(i = 0; i < col; i++)
        {
            aux = 0;
            for(j = 0; j < 3; j++)
            {
                aux += M1[k][j] * M2[j][i];
            }
            M3[k][i] = aux;
        }
    }
}

void pasarArrayMatriz (int fil, int col, int mat[fil][col],char contrasena[])
{
    int i,j,k=0;

    for(j = 0; j < col; j++)
    {
        for(i = 0; i < fil; i++)
        {
            if(k>strlen(contrasena))
            {
                mat[i][j] = 0;
            }
            else
            {
                mat[i][j] = contrasena[k];
                k++;
            }
        }
    }
}

//////////////////////////////Funciones de Muestra//////////////////////////////////////

void mostrarCliente(stCliente client) //Muestra un cliente, con formato.
{
    printf("ID:                %d\n", client.idCliente);
    printf("Nombre y Apellido: %s\n", client.nombreApellido);
    printf("Domicilio:         %s\n", client.domicilio);
    printf("Telefono:          %s\n", client.telefono);
    printf("Email:             %s\n", client.email);
    printf("\n");
}

void mostrarPedido(stPedido pedido) //Muestra un pedido, con formato.
{
    int i;

    printf("ID:               %d\n", pedido.idPedido);
    printf("Productos:        %d\n", pedido.productos);
    printf("Descripcion: ");
    for(i=0; i < pedido.productos; i++)
    {
        printf("%s", pedido.descPedido[i]);
        if(i < pedido.productos-1)
            printf(", ");
    }
    printf("\n");
    printf("Costo del Pedido: $%.2f\n", pedido.costoPedido);
    printf("Fecha:            %s\n", pedido.fechaPedido);
    printf("ID Cliente:       %d\n", pedido.idCliente);
    printf("\n");
}

void mostrarProducto(stProducto product) //Muestra un productos, con formato.
{
    printf("Menu: %d\t", product.idProducto);
    printf("%s\n", product.descProd);
    printf("Precio: $%.2f\n", product.precioProd);
    printf("\n");
}

void mostrarClientes(char nombreArchivo[])  //Muestra todos los clientes en un archivo.
{
    FILE * arch;
    stCliente aux;

    arch = fopen(nombreArchivo,"rb");

    if(arch != NULL)
    {
        while(fread(&aux,sizeof(stCliente),1,arch)>0)
        {
            if(aux.bajaCliente == 1)
            {
                mostrarCliente(aux);
            }
        }
        fclose(arch);
    }
}

void mostrarPedidos(char nombreArchivo[])  //Muestra todos los pedidos en un archivo.
{
    FILE * arch;
    stPedido aux;

    arch = fopen(nombreArchivo,"rb");

    if(arch != NULL)
    {
        while(fread(&aux,sizeof(stPedido),1,arch)>0)
        {
            if(aux.pedidoAnulado == 1)
            {
                mostrarPedido(aux);
            }
        }
        fclose(arch);
    }
}

void mostrarProductos(char nombreArchivo[]) //Muestra todos los productos en un archivo.
{
    FILE * arch;
    stProducto aux;

    arch = fopen(nombreArchivo,"rb");

    if(arch != NULL)
    {
        while(fread(&aux,sizeof(stProducto),1,arch)>0)
        {
            mostrarProducto(aux);
        }
        fclose(arch);
    }
}




















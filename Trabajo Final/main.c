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
    int password[30];
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

void menuBuscaCliente();

int menuLogin (stCliente * clienteLog, char nombreArchivo[]);

void menuPrincipal(stCliente clientLoged);

void menuOpciones(stCliente clientLoged);

//////////////////////////////Funciones de Carga/////////////////////////////////////////////
void crearCliente(char nombreArchivo[]);  //Ingresa los datos por teclado los datos para crear un cliente.

void registrarCliente(char nombreArchivo[], stCliente client); //Registra un cliente en un archivo.

void crearPedido(char nombreArchivo[], stProducto carro[], int cantProd, int idCliente); //Completa los datos para crear un pedido.

void registrarPedido(char nombreArchivo[], stPedido pedid);  //Registra un pedido en un archivo.

void crearProducto(char nombreArchivo[]);  //Ingresa por teclado los datos para crear un producto.

void registrarProducto(char nombreArchivo[], stProducto prod);  //Registra un producto en un archivo.

////////////////////////////////Funciones Busqueda////////////////////////////////////////
void busquedaCliente (stCliente cliente, char nombreArchivo[]); //Opcion para buscar clientes según datos varios

int encuentraCliente (char nombreArchivo[], char dato[]);  //Busca si existe un cliente en base a su email.

int encuentraNombreApellido (char nombreArchivo[], char dato[]);

int encuentraPassword (FILE * arch, int dato[], int cant);  //Encripta y compara la contraseña ingresada con la guardada

int encuentraEmail (char nombreArchivo[], char dato[]); //Busca un cliente con "x" email

int encuentraNombreApellido (char nombreArchivo[], char dato[]); //Busca si existe un cliente con "x" nombre y apellido

int encuentraDomicilio(char nombreArchivo[], char dato[]); //Busca un cliente con "x" domicilio

int encuentraTelefono (char nombreArchivo[], char dato[]); //Busca un cliente con "x" telefono

void buscaPedidoIdCliente (int idCliente, char nombreArchivo[]); //Busca los pedidos correspondientes a un cliente determinado

void buscaIdPedido (int idPedido, int idCliente, char nombreArchivo[]); // Busca un pedido según su id

int encontroProducto(FILE * archivo, int idProd);  //Busca un producto en un archivo, si lo encuentra devuelve 1 en caso contrario 0.

///////////////////////////////Funciones de Operacion////////////////////////////////////
int contadorDatos(char nombreArchivo[], int byte); //Cuenta cuantos bloques de datos hay en un archivo y devuelve el valor.

void fechaHora(char * fecha[]); //Devuelve la fecha y la hora del sistema.

float totalCarrito(stProducto carro[], int cantProd);  //Cuenta el total del carrito de compras.

void llenarCarrito(char nombreArchivo[], stProducto carro[], int idProd, int cantProd); //Carga el carrito de compras con productos.

void encriptarPass(char password[], int encript[]); //Encripta una contraseña.

void multMatrices(int col, int M1[3][3], int M2[3][col], int M3[3][col]); //Multiplica dos matrices.

void pasarArrayMatriz (int fil, int col, int mat[fil][col],char contrasena[]);  //Pasa un array de char a una matriz de int.

void pasarMatrizArray(int fil, int col, int mat[fil][col], int a[]); //Pasa una matriz de int a un array de int.

//////////////////////////////Funciones de Muestra//////////////////////////////////////
void mostrarCliente(stCliente client); //Muestra un cliente, con formato.

void mostrarPedido(stPedido pedido); //Muestra un pedido, con formato.

void mostrarProducto(stProducto product); //Muestra un productos, con formato.

void mostrarClientes(char nombreArchivo[]);  //Muestra todos los clientes en un archivo.

void mostrarPedidos(char nombreArchivo[]);  //Muestra todos los pedidos en un archivo.

void mostrarProductos(char nombreArchivo[]); //Muestra todos los productos en un archivo.

////////////////////////////Funciones de Modificacion////////////////////////// ¿Esta bien el apartado?
void modificarPedido (stPedido pedido, stCliente cliente, char nombreArchivo[]); //Compila, no se si tira errores

void modificarClienteV2(stCliente cliente, FILE * nombreArchivo); //Compila, no se si tira errores

void bajaCliente (stCliente cliente, char nombreArchivo[]); //Compila, no se si tira errores

const char aClientes[] = {"Datos\\clientes.dat"};
const char aPedidos[] = {"Datos\\pedidos.dat"};
const char aProductos[] = {"Datos\\productos.dat"};

int main()
{
    char opcion;
    stCliente clienteLoged;

    do
    {
        menu();
        fflush(stdin);
        scanf("%c",&opcion);
        switch(opcion)
        {
        case '1':
            system("cls");
            if (menuLogin(&clienteLoged, aClientes))
            {

                menuPrincipal(clienteLoged);
            }
            else
            {
                printf("El email o la contrase%ca no corresponden a un usario\n", 164);
            }
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

void menuBuscaCliente()
{
    printf("============|-----Busqueda de Clientes-----|===========\n");
    printf("[ 1 ] Nombre y apellido\n");
    printf("[ 2 ] Domicilio\n");
    printf("[ 3 ] Numero de telefono\n");
    printf("[ 4 ] Direccion de email\n");
    printf("[ 0 ] Volver\n");
    printf("=======================================================\n");
}

int menuLogin (stCliente * clienteLoged, char nombreArchivo[])
{
    FILE * arch = NULL;

    arch = fopen(nombreArchivo, "rb");

    char email[40];
    char password[30] = {0};

    int cant = 0;
    int control = 0;
    int fEmail = 0, fPass = 0;
    int passEncr[30] = {0};

    if (arch != NULL)
    {
        printf("Email: ");
        scanf("%s", &email);
        printf("Contrase%ca: ", 164);
        scanf("%s", &password);
        cant = strlen(password);
        encriptarPass(password, passEncr);

        fEmail = encuentraEmail(arch, email);
        fseek(arch, -2*sizeof(stCliente), SEEK_CUR);
        fPass = encuentraPassword(arch, passEncr, cant);

        if (fEmail != 0 && fPass != 0)
        {
            control = 1;
            fseek(arch, -2*sizeof(stCliente), SEEK_CUR);
            fread(clienteLoged, sizeof(stCliente), 1, arch);
        }
    }
    fclose(arch);
    return control;
}

void menuPrincipal(stCliente clientLoged)
{
    int i,op=0,cant=0,men=0;
    char menu;
    stProducto carrito[20];
    int idClint;

    do
    {

            system("cls");
            logo();
            printf("Bienvenido %s\n\n", clientLoged.nombreApellido);
            printf("1. Hacer un pedido\n");
            printf("2. Mis Pedidos\n");
            printf("3. Cancelar Pedido\n");
            printf("4. Opciones\n");
            if(clientLoged.admin)
            {
                printf("5. Listado de Clientes\n");
                printf("6. Buscar Cliente\n");
                printf("7. Agregar Producto\n");
                printf("8. Listado de Pedidos\n");
                printf("9. Buscar Pedido por ID del cliente\n");
            }
            printf("0. Salir\n");

            printf("Ingrese la opcion: ");
            scanf("%d",&op);

        switch(op)
        {
        case 1:
            system("cls");
            logo();
            cant = 0;
            mostrarProductos(aProductos);
            printf("Presione 0 para finalizar el pedido\n");
            do
            {
                printf("Menu: ");
                scanf("%d", &men);
                if(men > 0)
                {
                    llenarCarrito(aProductos,carrito,men,cant);
                }
                cant++;

            }
            while(men != 0);
            printf("Su Pedido es: \n");

            for(i = 0; i < cant-1; i++)
            {
                mostrarProducto(carrito[i]);
            }
            printf("Su pedido es correcto? s/n\n");
            fflush(stdin);
            scanf("%c",&menu);
            if(menu == 's')
            {
                crearPedido(aPedidos, carrito, cant-1,clientLoged.idCliente);
            }
            break;
        case 2:
            system("cls");
            buscaPedidoIdCliente(clientLoged.idCliente, aPedidos);
            break;
        case 3:

            break;
        case 4:
            menuOpciones(clientLoged);
            break;
        case 5:
            logo();
            mostrarClientes(aClientes);
            system("pause");
            break;
        case 6:
            logo();
            busquedaCliente(clientLoged, aClientes);
            break;
        case 7:
            logo();
            mostrarProductos(aProductos);
            printf("\nQuiere agregar un producto nuevo? s/n\n");
            fflush(stdin);
            scanf("%c", &menu);
            if(menu == 's')
                crearProducto(aProductos);
            break;
        case 8:
            logo();
            mostrarPedidos(aPedidos);
            break;
        case 9:
            logo();
            printf("Ingrese el id de un cliente");
            scanf("%d", &idClint);
            buscaPedidoIdCliente(idClint, aPedidos);
        }
    }
    while(op != 0);
}

void menuOpciones(stCliente clientLoged)
{
    int op = 0;
    char baja = 0;

    do
    {
        system("cls");
        logo();
        printf("\n1. Mis Datos\n");
        printf("2. Dar de baja\n");
        printf("0. Salir\n");
        printf("Ingrese su opcion: ");
        scanf("%d",&op);

        switch(op)
        {
        case 1:
            system("cls");
            logo();
            printf("\nSus datos son los siguientes: \n");
            mostrarCliente(clientLoged);
            system("pause");
            //funcion de modificar
            break;
        case 2:
            system("cls");
            logo();
            printf("\nEsta seguro de dar de baja? s/n");
            fflush(stdin);
            scanf("%c", &baja);
            if(baja == 's')
            {
                //funcion dar de baja;
            }
            break;
        }

    }
    while(op != 0);
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

    encriptarPass(pass, client.password);

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

void busquedaCliente (stCliente cliente, char nombreArchivo[]) //Funcion principal de busqueda de clientes
{
    char dato[60];
    char opcion;
    int pos = 0;
    char modific;
    char ctrlM = 's';

    FILE * bufferArch = fopen(nombreArchivo, "rb");

    if (bufferArch != NULL)
    {
        do
        {
            pos = 0;
            rewind(bufferArch);
            system("cls");
            menuBuscaCliente();
            fflush(stdin);
            opcion = getch();
            switch (opcion)
            {
            //Busca nombre y apellido
            case '1':
                system("cls");
                printf("Buscar: ");
                fflush(stdin);
                gets(&dato);
                pos = encuentraNombreApellido(bufferArch, dato) - 1;
                if (pos != 0 && cliente.bajaCliente == 1)
                {
                    rewind(bufferArch);
                    fseek(bufferArch, pos*sizeof(stCliente),SEEK_SET);
                    fread(&cliente, sizeof(stCliente), 1, bufferArch);
                    mostrarCliente(cliente);
                    printf(" Desea modificar sus datos? s/n: ");
                    fflush(stdin);
                    scanf("%c",&ctrlM);
                    if (ctrlM =='s')
                    {
                        bufferArch = fopen(nombreArchivo, "r+b");
                        modificarClienteV2(cliente, bufferArch);
                    }
                }
                else
                {
                    printf("No se encontro al cliente\n");
                }
                system("pause");
                break;

            //Busca domicilio
            case '2':
                system("cls");
                printf("Buscar: ");
                fflush(stdin);
                gets(&dato);
                pos = encuentraDomicilio(bufferArch, dato) - 1;
                if (pos != 0 && cliente.bajaCliente == 1)
                {
                    rewind(bufferArch);
                    fseek(bufferArch, pos*sizeof(stCliente),SEEK_SET);
                    fread(&cliente, sizeof(stCliente), 1, bufferArch);
                    mostrarCliente(cliente);
                    printf(" Desea modificar sus datos? s/n: ");
                    fflush(stdin);
                    scanf("%c",&ctrlM);
                    if (ctrlM =='s')
                    {
                        bufferArch = fopen(nombreArchivo, "r+b");
                        modificarClienteV2(cliente, bufferArch);
                    }
                }
                else
                {
                    printf("No se encontro al cliente\n");
                }
                system("pause");
                break;

            //Busca telefono
            case '3':
                system("cls");
                printf("Buscar: ");
                fflush(stdin);
                gets(&dato);
                pos = encuentraTelefono(bufferArch, dato) - 1;
                if (pos != 0 && cliente.bajaCliente == 1)
                {
                    rewind(bufferArch);
                    fseek(bufferArch, pos*sizeof(stCliente),SEEK_SET);
                    fread(&cliente, sizeof(stCliente), 1, bufferArch);
                    mostrarCliente(cliente);
                    printf(" Desea modificar sus datos? s/n: ");
                    fflush(stdin);
                    scanf("%c",&ctrlM);
                    if (ctrlM =='s')
                    {
                        bufferArch = fopen(nombreArchivo, "r+b");
                        modificarClienteV2(cliente, bufferArch);
                    }
                }
                else
                {
                    printf("No se encontro al cliente\n");
                }
                system("pause");
                break;

            //Busca email
            case '4':
                system("cls");
                printf("Buscar: ");
                fflush(stdin);
                gets(&dato);
                pos = encuentraEmail(bufferArch, dato) - 1;
                if (pos != 0 && cliente.bajaCliente == 1)
                {
                    rewind(bufferArch);
                    fseek(bufferArch, pos*sizeof(stCliente),SEEK_SET);
                    fread(&cliente, sizeof(stCliente), 1, bufferArch);
                    mostrarCliente(cliente);
                    printf(" Desea modificar sus datos? s/n: ");
                    fflush(stdin);
                    scanf("%c",&ctrlM);
                    if (ctrlM =='s')
                    {
                        bufferArch = fopen(nombreArchivo, "r+b");
                        modificarClienteV2(cliente, bufferArch);
                    }
                }
                else
                {
                    printf("No se encontro al cliente o esta dado de baja\n");
                }
                system("pause");
                break;
            }
        }
        while (opcion != '0');
    }
    else
    {
        printf("Error al abrir el archivo");
    }
    fclose(bufferArch);
}

int encuentraCliente (char nombreArchivo[], char dato[])  //Busca si existe un cliente en base a su email.
{
    int ctrl=0;
    stCliente cliente;

    FILE * archi = NULL;
    archi = fopen(nombreArchivo,"rb");

    if(archi != NULL)
    {
        while (fread(&cliente, sizeof(stCliente), 1, archi) > 0 && ctrl == 0)
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

int encuentraNombreApellido (char nombreArchivo[], char dato[])
{
    int ctrl=0;
    stCliente cliente;
    rewind(nombreArchivo);

    rewind(nombreArchivo);
    while (fread(&cliente, sizeof(stCliente), 1, nombreArchivo) > 0 && ctrl == 0)
    {
        if (strcmpi(cliente.nombreApellido, dato) == 0)
        {
            ctrl=ftell(nombreArchivo)/ sizeof(stCliente);
        }
    }
    return ctrl;
}

int encuentraEmail (char nombreArchivo[], char dato[])
{
    int ctrl=0;
    stCliente cliente;
    rewind(nombreArchivo);

    while (fread(&cliente, sizeof(stCliente), 1, nombreArchivo) > 0 && ctrl == 0)
    {
        if (strcmpi(cliente.email, dato) == 0)
        {
            ctrl=ftell(nombreArchivo)/ sizeof(stCliente);
        }
    }
    return ctrl;
}

int encuentraPassword (FILE * arch, int dato[], int cant)
{
    int ctrl=0;
    int i=0;
    stCliente cliente;

    while (fread(&cliente, sizeof(stCliente), 1, arch) > 0 && ctrl == 0)
    {
        while (cliente.password[i] == dato[i] && i<cant)
        {
            i++;
        }
        if (i == cant)
        {
            ctrl=ftell(arch)/ sizeof(stCliente);
        }
    }
    return ctrl;
}

int encuentraDomicilio (char nombreArchivo[], char dato[])
{
    int ctrl=0;
    stCliente cliente;
    rewind(nombreArchivo);

    while (fread(&cliente, sizeof(stCliente), 1, nombreArchivo) > 0 && ctrl == 0)
    {
        if (strcmpi(cliente.domicilio, dato) == 0)
        {
            ctrl=ftell(nombreArchivo)/ sizeof(stCliente);
        }
    }
    return ctrl;
}

int encuentraTelefono (char nombreArchivo[], char dato[])
{
    int ctrl=0;
    stCliente cliente;
    rewind(nombreArchivo);

    while (fread(&cliente, sizeof(stCliente), 1, nombreArchivo) > 0 && ctrl == 0)
    {
        if (strcmpi(cliente.telefono, dato) == 0)
        {
            ctrl=ftell(nombreArchivo)/ sizeof(stCliente);
        }
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

void buscaPedidoIdCliente (int idCliente, char nombreArchivo[])
{
    FILE * archi = NULL;
    archi = fopen(nombreArchivo, "rb");

    stPedido pedido;
    int idC = idCliente;
    int idP;
    int flag = 0;

    char control = 's';

    if (archi!=NULL)
    {
        do
        {
            system("cls");
            rewind(archi);
            while (!feof(archi))
            {
                if (fread(&pedido, sizeof(stPedido), 1, archi) > 0)
                {
                    if (pedido.idCliente == idC)
                    {
                        mostrarPedido(pedido);
                        flag = 1;
                    }
                }

            }
            if (flag == 1)
            {
                printf("\nDesea modificar algun pedido? s/n ");
                fflush(stdin);
                control = getch();
                if (control == 's')
                {
                    printf("Ingrese la id del pedido a modificar: ");
                    scanf("%d", &idP);
                    buscaIdPedido(idP, idC, archi);
                    printf("Desea continuar? s/n");
                    fflush(stdin);
                    control = getch();
                }
            }
            else
            {
                system("cls");
                printf("El cliente no tiene pedidos");
                printf("Desea continuar? s/n");
                fflush(stdin);
                control = getch();
            }
        }
        while (control == 's');
    }
}

void buscaIdPedido (int idPedido, int idCliente, char nombreArchivo[])
{
    int idP = idPedido;
    stPedido pedido;
    char opcion = 's';

    rewind(nombreArchivo);
    while (fread(&pedido, sizeof(stPedido), 1, nombreArchivo) > 0)
    {
        if (pedido.idPedido == idP && pedido.idCliente == idCliente)
        {
            do
            {
                mostrarPedido(pedido);
                printf("Queres modificar el pedido? s/n");
                fflush(stdin);
                opcion = getch();
                printf("Placeholder\n");
            }
            while (opcion == 's');
        }
        else
        {
            printf("No se pudo encontrar el pedido o no corresponde al cliente conectado");
        }
    }
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

void encriptarPass(char password[], int passEncript[]) //Ingresa una contraseña y la encripta mediante matrices
{
    //Devuelve una array de int como resultado.
    int fil = 3;
    int col = 10;
    int codigo[3][3]=
    {
        {1,2,3},
        {0,1,2},
        {2,1,1},
    };
    int matriz[fil][col];
    int encrip[fil][col];

    pasarArrayMatriz(fil,col,matriz,password);

    multMatrices(col,codigo,matriz,encrip);

    pasarMatrizArray(fil,col,encrip,passEncript);
}

void multMatrices(int col, int M1[3][3], int M2[3][col], int M3[3][col]) //Multiplica dos matrices.
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

void pasarArrayMatriz (int fil, int col, int mat[fil][col],char contrasena[]) //Pasa un array de char a una matriz de enteros.
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

void pasarMatrizArray(int fil, int col, int mat[fil][col], int a[]) //Pasa una matriz de enteros a un array.
{
    int i,j,k=0;

    for(j = 0; j < col; j++)
    {
        for(i=0; i < 3; i++)
        {
            a[k] = mat[i][j];
            k++;
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

//////////////////////////////Modificar Pedidos//////////////////////////////////////

void modificarClienteV2(stCliente cliente, FILE * nombreArchivo)
{
    char sON = 's';
    int menu;
    stCliente aux;
    aux = cliente;
        do
        {

            menuBuscaCliente();
            scanf("%d",&menu);
            fflush(stdin);

            switch (menu)
            {
            case 1:
                printf("Ingrese nuevo nombre y apellido\n");
                fflush(stdin);
                gets(aux.nombreApellido);
                break;
            case 2:
                printf("Ingrese nuevo Domicilio\n");
                gets(aux.domicilio);
                break;
            case 3:
                printf("Ingrese nuevo telefono\n");
                gets(aux.telefono);
                break;
            case 4:
                printf("Ingrese nuevo mail\n");
                gets(aux.email);
                break;
            case 0:
                printf("\n");
                break;
            }
        }
        while (menu!=0);
        printf("Sus nuevos datos son los siguientes: \n");
        mostrarCliente(aux);
        printf("\n Desea guardar los cambios? s/n");
        scanf("%c",&sON);
        if (sON=='s')
        {
            fseek(nombreArchivo,-1 * sizeof(stCliente), SEEK_CUR);
            if (fwrite(&aux, sizeof(stCliente),1, nombreArchivo)>0);
            {
                printf("Los cambios han sido guardados\n");
            }
        }
        else
        {
            printf("Los cambios han sido descartados.\n");
        }
}


void bajaCliente (stCliente cliente, char nombreArchivo[])
{
    stCliente aux;
    aux = cliente;
    char sON,sON2;
    FILE * archi=NULL;
    archi = fopen(nombreArchivo,"r+b");
    printf("Desea dar de baja la cuenta registrada a nombre de %c s/n ?",aux.nombreApellido);
    fflush(stdin);
    scanf("%c",&sON);
    if (sON=='s')
    {
        printf("Esta seguro? s/n");
        scanf("%c",&sON2);
        if (sON2=='s')
        {
            aux.bajaCliente=1;
            fseek(archi,-1 * sizeof(stCliente), SEEK_CUR);
            fwrite(&aux, sizeof(stCliente),1, archi);
            fclose(archi);

            printf("la cuenta ha sido dada de baja");
        }
    }
}

void modificarPedido (stPedido pedido, stCliente cliente, char nombreArchivo[]) // La idea es que funcione tanto para cliente como para admin, podrian ser dos funciones diferentes pero similares si la implementacion resulta problematica
{
    FILE * archi=NULL;
    archi = fopen(nombreArchivo,"r+b");
    stPedido aux;
    aux =pedido;
    int menu;
    char sON;

    do
    {
        if (cliente.admin==1)
        {
            printf(" 1 - Dar pedido de baja \n 2 - Modificar precio pedido \n 0 Salir y guardar cambios \n");
        }
        else
        {
            printf("1 Dar pedido de baja \n 0 Salir y guardar cambios \n");
        }
        scanf("%d",&menu);
        switch (menu)
        {
        case 1:
            printf("Desea dar de baja el pedido? s/n");
            fflush(stdin);
            scanf("%c",&sON);
            if (sON=='s')
            {
                aux.pedidoAnulado=1;
                printf("el pedido ha sido anulado");
            }
            break;
        case 2:
            if (cliente.admin==1)
            {
                printf(" Costo actual del pedido: %f \n Ingrese nuevo costo: \n",aux.costoPedido);
                scanf("%f",&aux.costoPedido);
            }
            break;
        case 0:
            break;
        }
    }
    while(menu!=0);
    printf("los cambios han sido guardados");
    fseek(archi,-1 * sizeof(stPedido), SEEK_CUR);
    fwrite(&aux, sizeof(stPedido),1, archi);
    fclose(archi);
}




















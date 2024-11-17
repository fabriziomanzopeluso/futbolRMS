#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "structs.h"

#define largo_cadena 100

char *archivo_usuarios_txt = "../src/usuarios.txt";
char *archivo_usuarios_bin = "../src/usuarios.dat";
char *archivo_jugadores_txt = "../src/jugadores.txt";
char *archivo_jugadores_bin = "../src/jugadores.dat";
char *archivo_roles_txt = "../src/roles.txt";
char *archivo_roles_bin = "../src/roles.dat";
char *archivo_permisos_txt = "../src/permisos.txt";
char *archivo_permisos_bin = "../src/permisos.dat";

#define MAX_USUARIOS 100
#define MAX_JUGADORES 100
#define MAX_ROLES 100
#define MAX_PERMISOS 100

Usuario usuarios[MAX_USUARIOS];
Jugador jugadores[MAX_JUGADORES];
Rol roles[MAX_ROLES];
Permiso permisos[MAX_PERMISOS];

int total_usuarios = 0;
int total_jugadores = 0;
int total_roles = 0;
int total_permisos = 0;

void menuPrincipal(int id_rol);
void iniciarSesion();
// carga datos
void cargarDatosUsuarios();
void cargarDatosJugadores();
void cargarDatosRoles();
void cargarDatosPermisos();

// guarda datos
void guardarUsuariosBin();

int obtenerRolUsuario(int id_usuario);
// abm USUARIO
void imprimirUsuarios();
void agregarUsuario();
void buscarUsuario();
void eliminarUsuario();
void modificarUsuario();
void menuUsuariosABM();
void mostrarDatosUsuario(int id_usuario);

// ABM JUGADOR
void buscarJugador();
void agregarJugador();
void modificarJugador();
void eliminarJugador();
void menuJugadoresABM();

// ABM PERMISO
void agregarPermiso();
void buscarPermiso();
void modificarPermiso();
void eliminarPermiso();
void abmPermisos();

// ABM ROLES
void abmRoles();
void agregarRol();
void buscarRol();
void modificarRol();
void eliminarRol();

// Funciones auxiliares
int asignarNumeroDeUsuario();
int validarCadenaSinNumeros(char *cadena);
int validarCadenaNumeros(char *cadena);
int validarMail(char *email);

int main()
{
    cargarDatosUsuarios();
    cargarDatosJugadores();
    cargarDatosRoles();
    cargarDatosPermisos();

    imprimirUsuarios();
    iniciarSesion();
    return 0;
}
// ---------------------------------------CARGA DATOS---------------------------------------
void guardarUsuariosBin()
{
    FILE *file_bin = fopen(archivo_usuarios_bin, "wb");
    if (file_bin == NULL)
    {
        perror("Error al abrir el archivo binario para guardar los datos");
        return;
    }

    if (fwrite(&total_usuarios, sizeof(int), 1, file_bin) != 1)
    {
        printf("Error al guardar el total de usuarios en el archivo binario.\n");
        fclose(file_bin);
        return;
    }

    if (fwrite(usuarios, sizeof(Usuario), total_usuarios, file_bin) != (size_t)total_usuarios)
    {
        printf("Error al guardar los datos de usuarios en el archivo binario.\n");
        fclose(file_bin);
        return;
    }

    printf("Datos guardados en el archivo binario '%s' con éxito.\n", archivo_usuarios_bin);
    fclose(file_bin);
}
void cargarUsuariosDesdeTxt()
{
    FILE *file_txt = fopen(archivo_usuarios_txt, "r");
    if (file_txt == NULL)
    {
        printf("No se pudo abrir el archivo de texto '%s'.\n", archivo_usuarios_txt);
        return;
    }

    total_usuarios = 0; // Reiniciar el contador de usuarios
    char linea[256];
    while (fgets(linea, sizeof(linea), file_txt))
    {
        Usuario temp;
        if (sscanf(linea, "%d;%49[^;];%49[^;];%49[^;];%49[^;];%d/%d/%d",
                   &temp.id_usuario,
                   temp.nombre,
                   temp.apellido,
                   temp.email,
                   temp.contrasenia,
                   &temp.fecha_creacion.dia,
                   &temp.fecha_creacion.mes,
                   &temp.fecha_creacion.anio) == 8)
        {
            if (total_usuarios < MAX_USUARIOS)
            {
                usuarios[total_usuarios++] = temp;
            }
            else
            {
                printf("Se alcanzó el límite máximo de usuarios (%d).\n", MAX_USUARIOS);
                break;
            }
        }
        else
        {
            printf("Formato incorrecto en la línea: %s", linea);
        }
    }
    fclose(file_txt);

    if (total_usuarios > 0)
    {
        printf("Datos cargados desde el archivo de texto '%s' con éxito.\n", archivo_usuarios_txt);
        guardarUsuariosBin();
    }
    else
    {
        printf("No se encontraron datos válidos en el archivo de texto '%s'.\n", archivo_usuarios_txt);
    }
}
void cargarDatosUsuarios()
{
    FILE *file_bin = fopen(archivo_usuarios_bin, "rb");

    if (file_bin != NULL)
    {
        // Cargar desde archivo binario
        if (fread(&total_usuarios, sizeof(int), 1, file_bin) != 1)
        {
            printf("Error al leer el total de usuarios desde el archivo binario.\n");
            fclose(file_bin);
            return;
        }

        if (total_usuarios > MAX_USUARIOS)
        {
            printf("Error: El archivo binario contiene más usuarios de los permitidos (%d).\n", MAX_USUARIOS);
            fclose(file_bin);
            return;
        }

        if (fread(usuarios, sizeof(Usuario), total_usuarios, file_bin) != (size_t)total_usuarios)
        {
            printf("Error al leer los datos de usuarios desde el archivo binario.\n");
            fclose(file_bin);
            return;
        }

        fclose(file_bin);
        printf("Datos cargados desde el archivo binario '%s' con éxito.\n", archivo_usuarios_bin);
    }
    else
    {
        printf("Archivo binario no encontrado. Cargando datos desde el archivo de texto...\n");
        cargarUsuariosDesdeTxt();
    }
}
void imprimirUsuarios()
{
    FILE *file = fopen(archivo_usuarios_bin, "rb"); // Abrir el archivo binario en modo lectura
    if (file == NULL)
    {
        printf("Error al abrir el archivo de usuarios.\n");
        return;
    }

    int total;
    if (fread(&total, sizeof(int), 1, file) != 1)
    {
        printf("Error al leer el total de usuarios desde el archivo binario.\n");
        fclose(file);
        return;
    }

    printf("\nUsuarios registrados:\n");
    printf("----------------------------------------------------------------------------------------------\n");
    printf("| ID   | Nombre      | Apellido    | Email                  | Contraseña        | Fecha      |\n");
    printf("----------------------------------------------------------------------------------------------\n");

    Usuario usuario;
    for (int i = 0; i < total; i++)
    {
        if (fread(&usuario, sizeof(Usuario), 1, file) != 1)
        {
            printf("Error al leer los datos del usuario.\n");
            fclose(file);
            return;
        }
        printf("| %-4d | %-11s | %-11s | %-22s | %-17s | %02d/%02d/%4d |\n",
               usuario.id_usuario,
               usuario.nombre,
               usuario.apellido,
               usuario.email,
               usuario.contrasenia,
               usuario.fecha_creacion.dia,
               usuario.fecha_creacion.mes,
               usuario.fecha_creacion.anio);
    }

    fclose(file);
    printf("----------------------------------------------------------------------------------------------\n");
}
int obtenerRolUsuario(int id_usuario)
{
    // Aquí deberías implementar la logica para obtener el rol del usuario
    for (int i = 0; i < total_usuarios; i++)
    {
        if (usuarios[i].id_usuario == id_usuario)
        {
            return 1; // Supongamos que el ID 1 es Admin
        }
    }
    return -1; // Retornar -1 si no se encuentra el rol
}
void cargarDatosJugadores()
{
    FILE *file = fopen(archivo_jugadores_txt, "r");
    if (file == NULL)
    {
        printf("Error al abrir el archivo de jugadores.\n");
        return;
    }

    while (fscanf(file, "%d;%d;%d;%[^;];%d;%d/%d/%d",
                  &jugadores[total_jugadores].id_jugador,
                  &jugadores[total_jugadores].id_usuario,
                  &jugadores[total_jugadores].id_equipo,
                  jugadores[total_jugadores].posicion,
                  &jugadores[total_jugadores].numero_creacion,
                  &jugadores[total_jugadores].fecha_creacion.dia,
                  &jugadores[total_jugadores].fecha_creacion.mes,
                  &jugadores[total_jugadores].fecha_creacion.anio) != EOF)
    {
        total_jugadores++;
    }
    fclose(file);
}
void cargarDatosRoles()
{
    FILE *file = fopen(archivo_roles_txt, "r");
    if (file == NULL)
    {
        printf("Error al abrir el archivo de roles.\n");
        return;
    }

    while (fscanf(file, "%d;%[^;];%[^;];%d/%d/%d",
                  &roles[total_roles].id_rol,
                  roles[total_roles].nombre_rol,
                  roles[total_roles].descripcion,
                  &roles[total_roles].fecha_creacion.dia,
                  &roles[total_roles].fecha_creacion.mes,
                  &roles[total_roles].fecha_creacion.anio) != EOF)
    {
        total_roles++;
    }
    fclose(file);
}

void cargarDatosPermisos()
{
    FILE *file = fopen(archivo_permisos_txt, "r");
    if (file == NULL)
    {
        printf("Error al abrir el archivo de permisos.\n");
        return;
    }

    while (fscanf(file, "%d;%[^;];%[^;];%d/%d/%d",
                  &permisos[total_permisos].id_permiso,
                  permisos[total_permisos].nombre_permiso,
                  permisos[total_permisos].descripcion,
                  &permisos[total_permisos].fecha_creacion.dia,
                  &permisos[total_permisos].fecha_creacion.mes,
                  &permisos[total_permisos].fecha_creacion.anio) != EOF)
    {
        total_permisos++;
    }
    fclose(file);
}
void iniciarSesion()
{
    cadena email;
    cadena contrasenia;
    int intentos = 0;
    while (intentos < 3)
    {
        printf("Ingrese su email: ");
        scanf("%s", email);
        printf("Ingrese su contrasenia: ");
        scanf("%s", contrasenia);

        for (int i = 0; i < total_usuarios; i++)
        {
            if (strcmp(usuarios[i].email, email) == 0 && strcmp(usuarios[i].contrasenia, contrasenia) == 0)
            {
                printf("Inicio de sesion exitoso. Bienvenido, %s!\n", usuarios[i].nombre);
                menuPrincipal(usuarios[i].id_usuario);
                return;
            }
        }
        intentos++;
        printf("Email o contrasenia incorrectos. Intento %d de 3.\n", intentos);
    }
    printf("Demasiados intentos fallidos. Saliendo...\n");
    exit(1);
}

void menuPrincipal(int id_usuario)

{
    int session_active = 1;                          // Indicar que la sesion esta activa
    int rol_usuario = obtenerRolUsuario(id_usuario); // Obtener rol del usuario

    do
    {
        printf("\n=== MENU PRINCIPAL ===\n");
        if (rol_usuario == 1)
        { // Supongamos que el rol 1 es Admin
            printf("1. ABM Usuarios\n");
            printf("2. ABM Jugadores\n");
            printf("3. ABM Roles\n");
            printf("4. ABM Permisos\n");
            printf("5. Salir\n");
        }
        else
        {
            printf("1. Ver Mis Datos\n");
            printf("2. Salir\n");
        }

        int opcion;
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            if (rol_usuario == 1)
            {
                menuUsuariosABM(); // Llamar a la funcion ABM Usuarios
            }
            else
            {
                mostrarDatosUsuario(id_usuario);
            }
            break;
        case 2:
            if (rol_usuario == 1)
            {
                menuJugadoresABM(); // Llamar a la funcion ABM Jugadores
            }
            else
            {
                printf("Saliendo...\n");
                session_active = 0; // Cerrar sesion
            }
            break;
        case 3:
            if (rol_usuario == 1)
            {
                abmRoles(); // Llamar a la funcion ABM Roles
            }
            else
            {
                printf("Saliendo...\n");
                session_active = 0; // Cerrar sesion
            }
            break;
        case 4:
            if (rol_usuario == 1)
            {
                abmPermisos(); // Llamar a la funcion ABM Permisos
            }
            else
            {
                printf("Saliendo...\n");
                session_active = 0; // Cerrar sesion
            }
            break;
        case 5:
            printf("Saliendo...\n");
            session_active = 0; // Cerrar sesion
            break;
        default:
            printf("Opcion no valida. Intente de nuevo.\n");
            break;
        }
    } while (session_active); // Mantener el menu hasta que se cierre la sesion
}

// --------------------------------------- ABM USUARIOS ---------------------------------------

void mostrarDatosUsuario(int id_usuario)
{
    for (int i = 0; i < total_usuarios; i++)
    {
        if (usuarios[i].id_usuario == id_usuario)
        {
            printf("\n=== DATOS DEL USUARIO ===\n");
            printf("ID: %d\n", usuarios[i].id_usuario);
            printf("Nombre: %s\n", usuarios[i].nombre);
            printf("Apellido: %s\n", usuarios[i].apellido);
            printf("Email: %s\n", usuarios[i].email);
            printf("Fecha de Creacion: %02d/%02d/%04d\n",
                   usuarios[i].fecha_creacion.dia,
                   usuarios[i].fecha_creacion.mes,
                   usuarios[i].fecha_creacion.anio);
            break;
        }
    }
}

void menuUsuariosABM()
{
    int opcion;
    do
    {
        printf("\n=== ABM Usuarios ===\n");
        printf("1. Agregar Usuario\n");
        printf("2. Buscar Usuario\n");
        printf("3. Listar Usuarios\n");
        printf("4. Modificar Usuario\n");
        printf("5. Eliminar Usuario\n");
        printf("6. Volver al Menu Principal\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            agregarUsuario();
            break;
        case 2:
            buscarUsuario();
            break;
        case 3:
            imprimirUsuarios();
            break;
        case 4:
            modificarUsuario();
            break;
        case 5:
            eliminarUsuario();
            break;
        case 6:
            printf("Volviendo al menu principal...\n");
            break;
        default:
            printf("Opcion no valida. Intente de nuevo.\n");
            break;
        }
    } while (opcion != 6);
}

void agregarUsuario()
{
    if (total_usuarios >= 100)
    {
        printf("Límite de usuarios alcanzado.\n");
        return;
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    Usuario nuevo;

    nuevo.id_usuario = asignarNumeroDeUsuario();
    printf("ID asignado: %d\n", nuevo.id_usuario);

    do
    {
        printf("Ingrese el nombre (sin números, máx %d caracteres): ", largo_cadena);
        scanf("%s", nuevo.nombre);
    } while (!validarCadenaSinNumeros(nuevo.nombre) || strlen(nuevo.nombre) > largo_cadena);

    do
    {
        printf("Ingrese el apellido (sin números, máx %d caracteres): ", largo_cadena);
        scanf("%s", nuevo.apellido);
    } while (!validarCadenaSinNumeros(nuevo.apellido) || strlen(nuevo.apellido) > largo_cadena);

    do
    {
        printf("Ingrese el email (formato válido, máx %d caracteres): ", largo_cadena);
        scanf("%s", nuevo.email);
    } while (!validarMail(nuevo.email) || strlen(nuevo.email) > largo_cadena);

    do
    {
        printf("Ingrese la contraseña (máx %d caracteres): ", largo_cadena);
        scanf("%s", nuevo.contrasenia);
    } while (strlen(nuevo.contrasenia) > largo_cadena);

    nuevo.fecha_creacion.dia = tm.tm_mday;
    nuevo.fecha_creacion.mes = tm.tm_mon + 1;
    nuevo.fecha_creacion.anio = tm.tm_year + 1900;

    usuarios[total_usuarios++] = nuevo;

    // abro el binario en modo lectura-escritura
    FILE *file = fopen(archivo_usuarios_bin, "rb+");
    if (file == NULL)
    {
        // Si no existe, crearlo y escribir
        file = fopen(archivo_usuarios_bin, "wb");
        if (file == NULL)
        {
            perror("Error al crear el archivo binario");
            return;
        }
        fwrite(&total_usuarios, sizeof(int), 1, file);
    }
    else
    {
        fseek(file, 0, SEEK_SET);
        fwrite(&total_usuarios, sizeof(int), 1, file);
    }

    fseek(file, 0, SEEK_END);
    if (fwrite(&nuevo, sizeof(Usuario), 1, file) != 1)
    {
        perror("Error al escribir el usuario en el archivo binario");
    }
    else
    {
        printf("Usuario agregado al archivo binario.\n");
    }

    fclose(file);

    printf("\n=== Usuario Agregado ===\n");
    printf("ID: %d\n", nuevo.id_usuario);
    printf("Nombre: %s\n", nuevo.nombre);
    printf("Apellido: %s\n", nuevo.apellido);
    printf("Email: %s\n", nuevo.email);
    printf("Fecha de Creación: %02d/%02d/%04d\n",
           nuevo.fecha_creacion.dia,
           nuevo.fecha_creacion.mes,
           nuevo.fecha_creacion.anio);
}

void buscarUsuario()
{
    int id_usuario;
    printf("Ingrese el ID del usuario a buscar: ");
    scanf("%d", &id_usuario);
    for (int i = 0; i < total_usuarios; i++)
    {
        if (usuarios[i].id_usuario == id_usuario)
        {
            printf("\n=== Usuario Encontrado ===\n");
            printf("ID: %d\n", usuarios[i].id_usuario);
            printf("Nombre: %s\n", usuarios[i].nombre);
            printf("Apellido: %s\n", usuarios[i].apellido);
            printf("Email: %s\n", usuarios[i].email);
            printf("Fecha de Creacion: %02d/%02d/%04d\n",
                   usuarios[i].fecha_creacion.dia,
                   usuarios[i].fecha_creacion.mes,
                   usuarios[i].fecha_creacion.anio);
            return;
        }
    }
    printf("Usuario no encontrado.\n");
}

void modificarUsuario()
{
    int id_usuario;
    printf("Ingrese el ID del usuario a modificar: ");
    scanf("%d", &id_usuario);
    for (int i = 0; i < total_usuarios; i++)
    {
        if (usuarios[i].id_usuario == id_usuario)
        {
            printf("Ingrese el nuevo nombre (actual: %s): ", usuarios[i].nombre);
            scanf("%s", usuarios[i].nombre);
            printf("Ingrese el nuevo apellido (actual: %s): ", usuarios[i].apellido);
            scanf("%s", usuarios[i].apellido);
            printf("Ingrese el nuevo email (actual: %s): ", usuarios[i].email);
            scanf("%s", usuarios[i].email);
            printf("Ingrese la nueva contrasenia (actual: %s): ", usuarios[i].contrasenia);
            scanf("%s", usuarios[i].contrasenia);
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            usuarios[i].fecha_creacion.dia = tm.tm_mday,
            usuarios[i].fecha_creacion.mes = tm.tm_mon + 1,
            usuarios[i].fecha_creacion.anio = tm.tm_year + 1900;
            printf("Usuario modificado con exito.\n");
            return;
        }
    }
    printf("Usuario no encontrado.\n");
}

void eliminarUsuario()
{
    int id_usuario;
    printf("Ingrese el ID del usuario a eliminar: ");
    scanf("%d", &id_usuario);
    for (int i = 0; i < total_usuarios; i++)
    {
        if (usuarios[i].id_usuario == id_usuario)
        {
            for (int j = i; j < total_usuarios - 1; j++)
            {
                usuarios[j] = usuarios[j + 1]; // Mover los elementos hacia atras
            }
            total_usuarios--; // Disminuir el contador de usuarios
            printf("Usuario eliminado con exito.\n");
            return;
        }
    }
    printf("Usuario no encontrado.\n");
}

// --------------------------------------- ABM JUGADORES ---------------------------------------

void menuJugadoresABM()
{
    int opcion;
    do
    {
        printf("\n=== ABM Jugadores ===\n");
        printf("1. Agregar Jugador\n");
        printf("2. Buscar Jugador\n");
        printf("3. Modificar Jugador\n");
        printf("4. Eliminar Jugador\n");
        printf("5. Volver al Menu Principal\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            agregarJugador();
            break;
        case 2:
            buscarJugador();
            break;
        case 3:
            modificarJugador();
            break;
        case 4:
            eliminarJugador();
            break;
        case 5:
            printf("Volviendo al menu principal...\n");
            break;
        default:
            printf("Opcion no valida. Intente de nuevo.\n");
            break;
        }
    } while (opcion != 5);
}

void agregarJugador()
{
    if (total_jugadores < 100)
    { // Comprobar límite de jugadores
        Jugador nuevo;
        printf("Ingrese el ID del jugador: ");
        scanf("%d", &nuevo.id_jugador);
        printf("Ingrese el ID del usuario: ");
        scanf("%d", &nuevo.id_usuario);
        printf("Ingrese el ID del equipo: ");
        scanf("%d", &nuevo.id_equipo);
        printf("Ingrese la posicion: ");
        scanf("%s", nuevo.posicion);
        printf("Ingrese el numero de creacion: ");
        scanf("%d", &nuevo.numero_creacion);
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        nuevo.fecha_creacion.dia = tm.tm_mday,
        nuevo.fecha_creacion.mes = tm.tm_mon + 1,
        nuevo.fecha_creacion.anio = tm.tm_year + 1900;
        // Agregar el nuevo jugador al arreglo
        jugadores[total_jugadores++] = nuevo;
        printf("Jugador agregado con exito.\n");
    }
    else
    {
        printf("Límite de jugadores alcanzado.\n");
    }
}

void buscarJugador()
{
    int id_jugador;
    printf("Ingrese el ID del jugador a buscar: ");
    scanf("%d", &id_jugador);
    for (int i = 0; i < total_jugadores; i++)
    {
        if (jugadores[i].id_jugador == id_jugador)
        {
            printf("\n=== Jugador Encontrado ===\n");
            printf("ID: %d\n", jugadores[i].id_jugador);
            printf("ID Usuario: %d\n", jugadores[i].id_usuario);
            printf("ID Equipo: %d\n", jugadores[i].id_equipo);
            printf("Posicion: %s\n", jugadores[i].posicion);
            printf("Numero de Creacion: %d\n", jugadores[i].numero_creacion);
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            jugadores[i].fecha_creacion.dia = tm.tm_mday,
            jugadores[i].fecha_creacion.mes = tm.tm_mon + 1,
            jugadores[i].fecha_creacion.anio = tm.tm_year + 1900;
            return;
        }
    }
    printf("Jugador no encontrado.\n");
}

void modificarJugador()
{
    int id_jugador;
    printf("Ingrese el ID del jugador a modificar: ");
    scanf("%d", &id_jugador);
    for (int i = 0; i < total_jugadores; i++)
    {
        if (jugadores[i].id_jugador == id_jugador)
        {
            printf("Ingrese el nuevo ID de usuario (actual: %d): ", jugadores[i].id_usuario);
            scanf("%d", &jugadores[i].id_usuario);
            printf("Ingrese el nuevo ID de equipo (actual: %d): ", jugadores[i].id_equipo);
            scanf("%d", &jugadores[i].id_equipo);
            printf("Ingrese la nueva posicion (actual: %s): ", jugadores[i].posicion);
            scanf("%s", jugadores[i].posicion);
            printf("Ingrese el nuevo numero de creacion (actual: %d): ", jugadores[i].numero_creacion);
            scanf("%d", &jugadores[i].numero_creacion);
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            jugadores[i].fecha_creacion.dia = tm.tm_mday,
            jugadores[i].fecha_creacion.mes = tm.tm_mon + 1,
            jugadores[i].fecha_creacion.anio = tm.tm_year + 1900;
            printf("Jugador modificado con exito.\n");
            return;
        }
    }
    printf("Jugador no encontrado.\n");
}

void eliminarJugador()
{
    int id_jugador;
    printf("Ingrese el ID del jugador a eliminar: ");
    scanf("%d", &id_jugador);
    for (int i = 0; i < total_jugadores; i++)
    {
        if (jugadores[i].id_jugador == id_jugador)
        {
            for (int j = i; j < total_jugadores - 1; j++)
            {
                jugadores[j] = jugadores[j + 1]; // Mover los elementos hacia atras
            }
            total_jugadores--; // Disminuir el contador de jugadores
            printf("Jugador eliminado con exito.\n");
            return;
        }
    }
    printf("Jugador no encontrado.\n");
}

// --------------------------------------- ABM ROLES ---------------------------------------

void abmRoles()
{
    // Similar a las funciones anteriores para manejar roles
    // Implementar ABM Roles aquí (Agregar, Buscar, Modificar, Eliminar)

    int opcion;
    do
    {
        printf("\n=== ABM Roles ===\n");
        printf("1. Agregar Rol\n");
        printf("2. Buscar Rol\n");
        printf("3. Modificar Rol\n");
        printf("4. Eliminar Rol\n");
        printf("5. Volver al Menu Principal\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            agregarRol();
            break;
        case 2:
            buscarRol();
            break;
        case 3:
            modificarRol();
            break;
        case 4:
            eliminarRol();
            break;
        case 5:
            printf("Volviendo al menu principal...\n");
            break;
        default:
            printf("Opcion no valida. Intente de nuevo.\n");
            break;
        }
    } while (opcion != 5);
}

void agregarRol()
{
    if (total_roles < 100)
    { // Comprobar límite de jugadores
        Rol nuevo;
        printf("Ingrese el ID del rol: ");
        scanf("%d", &nuevo.id_rol);
        printf("Ingrese el nombre del rol: ");
        scanf("%s", nuevo.nombre_rol);
        printf("Ingrese la descripcion del rol: ");
        scanf("%s", nuevo.descripcion);
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        nuevo.fecha_creacion.dia = tm.tm_mday,
        nuevo.fecha_creacion.mes = tm.tm_mon + 1,
        nuevo.fecha_creacion.anio = tm.tm_year + 1900;

        // Agregar el nuevo jugador al arreglo
        roles[total_roles++] = nuevo;
        printf("Rol agregado con exito.\n");
    }
    else
    {
        printf("Límite de roles alcanzado.\n");
    }
}

void buscarRol()
{
    int id_rol;
    printf("Ingrese el ID del rol a buscar: ");
    scanf("%d", &id_rol);
    for (int i = 0; i < total_roles; i++)
    {
        if (roles[i].id_rol == id_rol)
        {
            printf("\n=== Rol Encontrado ===\n");
            printf("Nombre del rol: %s\n", roles[i].nombre_rol);
            printf("Descripcion del rol: %s\n", roles[i].descripcion);
            printf("Fecha de Creacion: %02d/%02d/%04d\n",
                   roles[i].fecha_creacion.dia,
                   roles[i].fecha_creacion.mes,
                   roles[i].fecha_creacion.anio);
        }
        return;
    }
}

void modificarRol()
{
    int id_rol;
    printf("Ingrese el ID del rol a modificar: ");
    scanf("%d", &id_rol);
    for (int i = 0; i < total_roles; i++)
    {
        if (roles[i].id_rol == id_rol)
        {
            printf("Ingrese el nuevo ID de rol (actual: %d): ", roles[i].id_rol);
            scanf("%d", &roles[i].id_rol);
            printf("Ingrese el nuevo nombre de rol (actual: %s): ", roles[i].nombre_rol);
            scanf("%d", &jugadores[i].id_equipo);
            printf("Ingrese la nueva descripcion del rol (actual: %s): ", roles[i].descripcion);
            scanf("%s", jugadores[i].posicion);
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            jugadores[i].fecha_creacion.dia = tm.tm_mday,
            jugadores[i].fecha_creacion.mes = tm.tm_mon + 1,
            jugadores[i].fecha_creacion.anio = tm.tm_year + 1900;
            printf("Rol modificado con exito.\n");
            return;
        }
    }
    printf("Rol no encontrado.\n");
}

void eliminarRol()
{
    int id_rol;
    printf("Ingrese el ID del rol a eliminar: ");
    scanf("%d", &id_rol);
    for (int i = 0; i < total_roles; i++)
    {
        if (roles[i].id_rol == id_rol)
        {
            for (int j = i; j < total_roles - 1; j++)
            {
                roles[j] = roles[j + 1]; // Mover los elementos hacia atras
            }
            total_roles--; // Disminuir el contador de roles
            printf("Rol eliminado con exito.\n");
            return;
        }
    }
    printf("Rol no encontrado.\n");
}

// --------------------------------------- ABM PERMISOS ---------------------------------------

void abmPermisos()
{
    // Similar a las funciones anteriores para manejar permisos
    // Implementar ABM Permisos aquí (Agregar, Buscar, Modificar, Eliminar)
    int opcion;
    do
    {
        printf("\n=== ABM Permisos ===\n");
        printf("1. Agregar Permiso\n");
        printf("2. Buscar Permiso\n");
        printf("3. Modificar Permiso\n");
        printf("4. Eliminar Permiso\n");
        printf("5. Volver al Menu Principal\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            agregarPermiso();
            break;
        case 2:
            buscarPermiso();
            break;
        case 3:
            modificarPermiso();
            break;
        case 4:
            eliminarPermiso();
            break;
        case 5:
            printf("Volviendo al menu principal...\n");
            break;
        default:
            printf("Opcion no valida. Intente de nuevo.\n");
            break;
        }
    } while (opcion != 5);
}
void agregarPermiso()
{
    if (total_permisos < 100)
    { // Comprobar límite de jugadores
        Permiso nuevo;
        printf("Ingrese el ID del permiso: ");
        scanf("%d", &nuevo.id_permiso);
        printf("Ingrese el nombre del permiso: ");
        scanf("%s", nuevo.nombre_permiso);
        printf("Ingrese la descripcion del permiso: ");
        scanf("%s", nuevo.descripcion);
        printf("Ingrese la fecha de creacion (dd/mm/yyyy): ");
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        nuevo.fecha_creacion.dia = tm.tm_mday,
        nuevo.fecha_creacion.mes = tm.tm_mon + 1,
        nuevo.fecha_creacion.anio = tm.tm_year + 1900;

        // Agregar el nuevo permiso al arreglo
        permisos[total_permisos++] = nuevo;
        printf("Permiso agregado con exito.\n");
    }
    else
    {
        printf("Límite de permisos alcanzado.\n");
    }
}

void buscarPermiso()
{
    int id_permiso;
    printf("Ingrese el ID del permiso a buscar: ");
    scanf("%d", &id_permiso);
    for (int i = 0; i < total_permisos; i++)
    {
        if (permisos[i].id_permiso == id_permiso)
        {
            printf("\n=== Permiso Encontrado ===\n");
            printf("Nombre del permiso: %s\n", permisos[i].nombre_permiso);
            printf("Descripcion del permiso: %s\n", permisos[i].descripcion);
            printf("Fecha de Creacion: %02d/%02d/%04d\n",
                   permisos[i].fecha_creacion.dia,
                   permisos[i].fecha_creacion.mes,
                   permisos[i].fecha_creacion.anio);
        }
        return;
    }
}

void modificarPermiso()
{
    int id_permiso;
    printf("Ingrese el ID del permiso a modificar: ");
    scanf("%d", &id_permiso);
    for (int i = 0; i < total_permisos; i++)
    {
        if (permisos[i].id_permiso == id_permiso)
        {
            printf("Ingrese el nuevo ID de permiso (actual: %d): ", permisos[i].id_permiso);
            scanf("%d", &permisos[i].id_permiso);
            printf("Ingrese el nuevo nombre de permiso (actual: %s): ", permisos[i].nombre_permiso);
            scanf("%s", permisos[i].nombre_permiso);
            printf("Ingrese la nueva descripcion del permiso (actual: %s): ", permisos[i].descripcion);
            scanf("%s", permisos[i].descripcion);
            printf("Ingrese la nueva fecha de creacion (actual: %02d/%02d/%04d): ",
                   permisos[i].fecha_creacion.dia,
                   permisos[i].fecha_creacion.mes,
                   permisos[i].fecha_creacion.anio);
            scanf("%d/%d/%d", &permisos[i].fecha_creacion.dia,
                  &permisos[i].fecha_creacion.mes,
                  &permisos[i].fecha_creacion.anio);
            printf("Permiso modificado con exito.\n");
            return;
        }
    }
    printf("Permiso no encontrado.\n");
}

void eliminarPermiso()
{
    int id_permiso;
    printf("Ingrese el ID del permiso a eliminar: ");
    scanf("%d", &id_permiso);
    for (int i = 0; i < total_permisos; i++)
    {
        if (permisos[i].id_permiso == id_permiso)
        {
            for (int j = i; j < total_permisos - 1; j++)
            {
                permisos[j] = permisos[j + 1]; // Mover los elementos hacia atras
            }
            total_permisos--; // Disminuir el contador de permisos
            printf("Permiso eliminado con exito.\n");
            return;
        }
    }
    printf("Permiso no encontrado.\n");
}

// --------------------------------------- FUNCIONES AUXILIARES ---------------------------------------

int asignarNumeroDeUsuario()
{
    // buscar los número de usuario y devolver un número que no fue usado
    int id_disponible = 1;
    int id_encontrado = 0;
    while (!id_encontrado)
    {
        id_encontrado = 1;
        for (int i = 0; i < total_usuarios; i++)
        {
            if (usuarios[i].id_usuario == id_disponible)
            {
                id_disponible++;
                id_encontrado = 0;
                break;
            }
        }
    }
    return id_disponible;
}

int validarCadenaSinNumeros(char *cadena)
{
    for (size_t i = 0; i < strlen(cadena); i++)
    {
        if (isdigit(cadena[i]))
        {
            return 0;
        }
    }
    return 1;
}

int validarCadenaNumeros(char *cadena)
{
    for (size_t i = 0; i < strlen(cadena); i++)
    {
        if (!isdigit(cadena[i]))
        {
            return 0;
        }
    }
    return 1;
}

int validarMail(char *email)
{
    // Validar que el email tenga un formato correcto
    // Ejemplo: usuario@dominio.xxx
    // El email debe tener un @ y al menos un caracter antes y después
    int tiene_arroba = 0;
    int tiene_punto = 0;
    for (size_t i = 0; i < strlen(email); i++)
    {
        if (email[i] == '@')
        {
            tiene_arroba = 1;
        }
        if (email[i] == '.')
        {
            tiene_punto = 1;
        }
    }
    return tiene_arroba && tiene_punto;
}
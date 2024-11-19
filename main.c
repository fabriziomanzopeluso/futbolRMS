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
char *archivo_equipos_txt = "../src/equipos.txt";
char *archivo_equipos_bin = "../src/equipos.dat";

#define MAX_USUARIOS 100
#define MAX_JUGADORES 100
#define MAX_ROLES 100
#define MAX_PERMISOS 100
#define MAX_USUARIOS_JUGADORES 100
#define MAX_EQUIPOS 100

Usuario usuarios[MAX_USUARIOS];
Jugador jugadores[MAX_JUGADORES];
Rol roles[MAX_ROLES];
Permiso permisos[MAX_PERMISOS];
Usuario_Jugador usuarios_jugadores[MAX_USUARIOS_JUGADORES];
Equipo equipos[MAX_EQUIPOS];

int total_usuarios = 0;
int total_jugadores = 0;
int total_roles = 0;
int total_permisos = 0;
int total_usuarios_jugadores = 0;
int total_equipos = 0;

void menuPrincipal(int id_rol);
void iniciarSesion();
// carga datos
void cargarDatosUsuarios();
void cargarDatosJugadores();
void cargarDatosRoles();
void cargarDatosPermisos();
void cargarDatosEquipos();

// guarda datos
void guardarUsuariosBin();
void guardarJugadoresBin();
void guardarJugadorEnBinario(Jugador nuevo);
void guardarJugadorModificadoEnBinario();
void cargarJugadoresDesdeTxt();
void imprimirJugadores();
void guardarEquiposBin();
void guardarEquipoEnBinario(Equipo nuevo);
void cargarEquiposDesdeTxt();
void imprimirEquipos();

int obtenerRolUsuario(int id_usuario);
// abm USUARIO
void imprimirUsuarios();
void agregarUsuario();
void buscarUsuario();
void eliminarUsuario();
void modificarUsuario();
void menuUsuariosABM();
void mostrarDatosUsuario(int id_usuario);
void asociarUsuarioJugador(int id_usuario);
void mostrarDatosUsuarioJugador(int id_usuario);

// ABM JUGADOR
void buscarJugador();
void agregarJugador(int id_usuario);
void modificarJugador();
void eliminarJugador();
void menuJugadoresABM();
void imprimirEquiposDisponibles();
void imprimirPosicionesDisponibles();
void imprimirUsuariosDisponibles();
void listarJugadoresCompletos();

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

// ABM EQUIPOS
void menuEquiposABM();
void agregarEquipo();
void buscarEquipo();
void modificarEquipo();
void eliminarEquipo();

// Funciones auxiliares
int asignarNumeroDeUsuario();
int asignarPosicion(int id_posicion, char *posicion);
int validarCadenaSinNumeros(char *cadena);
int validarCadenaNumeros(char *cadena);
int validarMail(char *email);
void agregarUsuarioJugador(int id_usuario, int id_jugador);
int esUsuarioJugador(int id_usuario);
int asignarNumeroDeJugador();

int main()
{
    cargarDatosUsuarios();
    cargarDatosJugadores();
    cargarDatosRoles();
    cargarDatosPermisos();
    cargarDatosEquipos();

    imprimirUsuarios();
    imprimirJugadores();
    imprimirEquipos();
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

    printf("Datos guardados en el archivo binario '%s' con exito.\n", archivo_usuarios_bin);
    fclose(file_bin);
}
void guardarUsuarioEnBinario(Usuario nuevo)
{
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
        printf("Archivo binario de usuarios actualizado con exito.\n");
    }

    fclose(file);
}
void guardarUsuarioModificadoEnBinario()
{
    FILE *file = fopen(archivo_usuarios_bin, "rb+");
    if (file == NULL)
    {
        perror("Error al abrir el archivo binario");
        return;
    }

    fseek(file, 0, SEEK_SET);
    fwrite(&total_usuarios, sizeof(int), 1, file);

    for (int i = 0; i < total_usuarios; i++)
    {
        fwrite(&usuarios[i], sizeof(Usuario), 1, file);
    }

    fclose(file);
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
                printf("Se alcanzo el limite maximo de usuarios (%d).\n", MAX_USUARIOS);
                break;
            }
        }
        else
        {
            printf("Formato incorrecto en la linea: %s", linea);
        }
    }
    fclose(file_txt);

    if (total_usuarios > 0)
    {
        printf("Datos cargados desde el archivo de texto '%s' con exito.\n", archivo_usuarios_txt);
        guardarUsuariosBin();
    }
    else
    {
        printf("No se encontraron datos validos en el archivo de texto '%s'.\n", archivo_usuarios_txt);
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
            printf("Error: El archivo binario contiene mas usuarios de los permitidos (%d).\n", MAX_USUARIOS);
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
        printf("Datos cargados desde el archivo binario '%s' con exito.\n", archivo_usuarios_bin);
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
    printf("-----------------------------------------------------------------------------------------------\n");
    printf("| ID   | Nombre      | Apellido    | Email                  | Contrasenia        | Fecha      |\n");
    printf("-----------------------------------------------------------------------------------------------\n");

    Usuario usuario;
    for (int i = 0; i < total; i++)
    {
        if (fread(&usuario, sizeof(Usuario), 1, file) != 1)
        {
            printf("Error al leer los datos del usuario.\n");
            fclose(file);
            return;
        }
        printf("| %-4d | %-11s | %-11s | %-22s | %-18s | %02d/%02d/%4d |\n",
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
    // Aqui deberias implementar la logica para obtener el rol del usuario
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
    FILE *file_bin = fopen(archivo_jugadores_bin, "rb");

    if (file_bin != NULL)
    {
        // Cargar desde archivo binario
        if (fread(&total_jugadores, sizeof(int), 1, file_bin) != 1)
        {
            printf("Error al leer el total de jugadores desde el archivo binario.\n");
            fclose(file_bin);
            return;
        }

        if (total_jugadores > MAX_JUGADORES)
        {
            printf("Error: El archivo binario contiene mas jugadores de los permitidos (%d).\n", MAX_JUGADORES);
            fclose(file_bin);
            return;
        }

        if (fread(jugadores, sizeof(Jugador), total_jugadores, file_bin) != (size_t)total_jugadores)
        {
            printf("Error al leer los datos de jugadores desde el archivo binario.\n");
            fclose(file_bin);
            return;
        }

        fclose(file_bin);
        printf("Datos cargados desde el archivo binario '%s' con exito.\n", archivo_jugadores_bin);
    }
    else
    {
        printf("Archivo binario no encontrado. Cargando datos desde el archivo de texto...\n");
        cargarJugadoresDesdeTxt();
    }
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
            printf("5. ABM Equipos\n");
            printf("6. Salir\n");
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
            if (rol_usuario == 1)
            {
                menuEquiposABM(); // Llamar a la funcion ABM Equipos
            }
            else
            {
                printf("Saliendo...\n");
                session_active = 0; // Cerrar sesion
            }
            break;
        case 6:
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
        printf("6. Ver Datos Completos de Usuario\n");
        printf("7. Volver al Menu Principal\n");
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
            {
                int id_usuario;
                printf("Ingrese el ID del usuario: ");
                scanf("%d", &id_usuario);
                mostrarDatosUsuarioJugador(id_usuario);
            }
            break;
        case 7:
            printf("Volviendo al menu principal...\n");
            break;
        default:
            printf("Opcion no valida. Intente de nuevo.\n");
            break;
        }
    } while (opcion != 7);
}

void agregarUsuario()
{
    if (total_usuarios >= 100)
    {
        printf("Limite de usuarios alcanzado.\n");
        return;
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    Usuario nuevo;

    nuevo.id_usuario = asignarNumeroDeUsuario();
    printf("ID asignado: %d\n", nuevo.id_usuario);

    do
    {
        printf("Ingrese el nombre (sin numeros, max %d caracteres): ", largo_cadena);
        scanf("%s", nuevo.nombre);
    } while (!validarCadenaSinNumeros(nuevo.nombre) || strlen(nuevo.nombre) > largo_cadena);

    do
    {
        printf("Ingrese el apellido (sin numeros, max %d caracteres): ", largo_cadena);
        scanf("%s", nuevo.apellido);
    } while (!validarCadenaSinNumeros(nuevo.apellido) || strlen(nuevo.apellido) > largo_cadena);

    do
    {
        printf("Ingrese el email (formato valido, max %d caracteres): ", largo_cadena);
        scanf("%s", nuevo.email);
    } while (!validarMail(nuevo.email) || strlen(nuevo.email) > largo_cadena);

    do
    {
        printf("Ingrese la contrasenia (max %d caracteres): ", largo_cadena);
        scanf("%s", nuevo.contrasenia);
    } while (strlen(nuevo.contrasenia) > largo_cadena);

    nuevo.fecha_creacion.dia = tm.tm_mday;
    nuevo.fecha_creacion.mes = tm.tm_mon + 1;
    nuevo.fecha_creacion.anio = tm.tm_year + 1900;

    usuarios[total_usuarios++] = nuevo;

    guardarUsuarioEnBinario(nuevo);

    printf("\n=== Usuario Agregado ===\n");
    printf("ID: %d\n", nuevo.id_usuario);
    printf("Nombre: %s\n", nuevo.nombre);
    printf("Apellido: %s\n", nuevo.apellido);
    printf("Email: %s\n", nuevo.email);
    printf("Fecha de Creacion: %02d/%02d/%04d\n",
           nuevo.fecha_creacion.dia,
           nuevo.fecha_creacion.mes,
           nuevo.fecha_creacion.anio);

    char opcion;
    printf("¿Desea agregar un jugador asociado a este usuario? (s/n): ");
    scanf(" %c", &opcion);
    if (opcion == 's' || opcion == 'S')
    {
        agregarJugador(nuevo.id_usuario);
    }
}

void asociarUsuarioJugador(int id_usuario)
{
    if (total_jugadores >= 100)
    {
        printf("Limite de jugadores alcanzado.\n");
        return;
    }

    Jugador nuevo;
    nuevo.id_usuario = id_usuario;
    printf("Ingrese el ID del jugador: ");
    scanf("%d", &nuevo.id_jugador);
    printf("Ingrese el ID del equipo: ");
    scanf("%d", &nuevo.id_equipo);
    printf("Ingrese la posicion: ");
    scanf("%s", nuevo.posicion);
    printf("Ingrese el numero de camiseta: ");
    scanf("%d", &nuevo.numero_de_camiseta);
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    nuevo.fecha_creacion.dia = tm.tm_mday,
    nuevo.fecha_creacion.mes = tm.tm_mon + 1,
    nuevo.fecha_creacion.anio = tm.tm_year + 1900;

    jugadores[total_jugadores++] = nuevo;
    agregarUsuarioJugador(nuevo.id_usuario, nuevo.id_jugador);
    printf("Jugador asociado con exito.\n");
}

void mostrarDatosUsuarioJugador(int id_usuario)
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

            for (int j = 0; j < total_usuarios_jugadores; j++)
            {
                if (usuarios_jugadores[j].id_usuario == id_usuario)
                {
                    for (int k = 0; k < total_jugadores; k++)
                    {
                        if (jugadores[k].id_jugador == usuarios_jugadores[j].id_jugador)
                        {
                            printf("\n=== DATOS DEL JUGADOR ===\n");
                            printf("ID Jugador: %d\n", jugadores[k].id_jugador);
                            printf("ID Equipo: %d\n", jugadores[k].id_equipo);
                            printf("Posicion: %s\n", jugadores[k].posicion);
                            printf("Numero de Camiseta: %d\n", jugadores[k].numero_de_camiseta);
                            printf("Fecha de Creacion: %02d/%02d/%04d\n",
                                   jugadores[k].fecha_creacion.dia,
                                   jugadores[k].fecha_creacion.mes,
                                   jugadores[k].fecha_creacion.anio);
                            return;
                        }
                    }
                }
            }
            printf("Este usuario no esta asociado a ningun jugador.\n");
            return;
        }
    }
    printf("Usuario no encontrado.\n");
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

            guardarUsuarioModificadoEnBinario();

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
            // Eliminar jugador asociado si existe
            for (int j = 0; j < total_jugadores; j++)
            {
                if (jugadores[j].id_usuario == id_usuario)
                {
                    for (int k = j; k < total_jugadores - 1; k++)
                    {
                        jugadores[k] = jugadores[k + 1];
                    }
                    total_jugadores--;
                    printf("Jugador asociado eliminado con exito.\n");
                    break;
                }
            }

            // Eliminar usuario
            for (int j = i; j < total_usuarios - 1; j++)
            {
                usuarios[j] = usuarios[j + 1];
            }
            total_usuarios--;
            printf("Usuario eliminado con exito.\n");

            guardarUsuarioModificadoEnBinario();
            guardarJugadorModificadoEnBinario();
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
        printf("5. Listar Jugadores\n");
        printf("6. Volver al Menu Principal\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            {
                int id_usuario;
                printf("Ingrese el ID del usuario para asociar al jugador: ");
                scanf("%d", &id_usuario);
                agregarJugador(id_usuario);
            }
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
            listarJugadoresCompletos();
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

void listarJugadoresCompletos()
{
    printf("\nJugadores registrados (informacion completa):\n");
    printf("------------------------------------------------------------------------------------------------------\n");
    printf("| ID   | Nombre         | Apellido         | Nombre Equipo | Posicion      | Numero de Camiseta | Fecha      |\n");
    printf("------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < total_jugadores; i++)
    {
        char nombre_usuario[100] = "";
        char apellido_usuario[100] = "";
        char nombre_equipo[100] = "";

        for (int j = 0; j < total_usuarios; j++)
        {
            if (usuarios[j].id_usuario == jugadores[i].id_usuario)
            {
                strcpy(nombre_usuario, usuarios[j].nombre);
                strcpy(apellido_usuario, usuarios[j].apellido);
                break;
            }
        }

        for (int k = 0; k < total_equipos; k++)
        {
            if (equipos[k].id_equipo == jugadores[i].id_equipo)
            {
                strcpy(nombre_equipo, equipos[k].nombre_equipo);
                break;
            }
        }

        printf("| %-4d | %-14s | %-16s | %-13s | %-16s | %-19d | %02d/%02d/%4d |\n",
               jugadores[i].id_jugador,
               nombre_usuario,
               apellido_usuario,
               nombre_equipo,
               jugadores[i].posicion,
               jugadores[i].numero_de_camiseta,
               jugadores[i].fecha_creacion.dia,
               jugadores[i].fecha_creacion.mes,
               jugadores[i].fecha_creacion.anio);
    }

    printf("------------------------------------------------------------------------------------------------------\n");
}

void agregarJugador(int id_usuario)
{
    if (total_jugadores >= 100)
    {
        printf("Limite de jugadores alcanzado.\n");
        return;
    }

    imprimirUsuariosDisponibles();

    printf("Ingrese el ID del usuario para asociar al jugador: ");
    scanf("%d", &id_usuario);

    if (esUsuarioJugador(id_usuario))
    {
        printf("El usuario ya tiene un jugador asociado.\n");
        return;
    }

    Jugador nuevo;
    nuevo.id_usuario = id_usuario;
    nuevo.id_jugador = asignarNumeroDeJugador();
    printf("ID asignado al jugador: %d\n", nuevo.id_jugador);

    imprimirEquiposDisponibles();
    printf("Ingrese el ID del equipo: ");
    scanf("%d", &nuevo.id_equipo);

    imprimirPosicionesDisponibles();
    int id_posicion;
    printf("Ingrese el ID de la posicion: ");
    scanf("%d", &id_posicion);
    if (!asignarPosicion(id_posicion, nuevo.posicion))
    {
        printf("ID de posicion invalido.\n");
        return;
    }

    printf("Ingrese el numero de camiseta: ");
    scanf("%d", &nuevo.numero_de_camiseta);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    nuevo.fecha_creacion.dia = tm.tm_mday;
    nuevo.fecha_creacion.mes = tm.tm_mon + 1;
    nuevo.fecha_creacion.anio = tm.tm_year + 1900;

    jugadores[total_jugadores++] = nuevo;
    agregarUsuarioJugador(nuevo.id_usuario, nuevo.id_jugador);
    guardarJugadorEnBinario(nuevo);
    printf("Jugador asociado con exito.\n");
}

void imprimirUsuariosDisponibles()
{
    printf("\nUsuarios disponibles:\n");
    printf("-------------------------------------------------------------\n");
    printf("| ID   | Nombre      | Apellido    | Asociado a Jugador |\n");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < total_usuarios; i++)
    {
        int asociado = esUsuarioJugador(usuarios[i].id_usuario);
        printf("| %-4d | %-11s | %-11s | %-17s |\n",
               usuarios[i].id_usuario,
               usuarios[i].nombre,
               usuarios[i].apellido,
               asociado ? "Si" : "No");
    }

    printf("-------------------------------------------------------------\n");
}

int asignarNumeroDeJugador()
{
    int id_disponible = 1;
    int id_encontrado = 0;
    while (!id_encontrado)
    {
        id_encontrado = 1;
        for (int i = 0; i < total_jugadores; i++)
        {
            if (jugadores[i].id_jugador == id_disponible)
            {
                id_disponible++;
                id_encontrado = 0;
                break;
            }
        }
    }
    return id_disponible;
}

void imprimirEquiposDisponibles()
{
    FILE *file = fopen(archivo_equipos_bin, "rb");
    if (file == NULL)
    {
        printf("Error al abrir el archivo de equipos.\n");
        return;
    }

    int total;
    if (fread(&total, sizeof(int), 1, file) != 1)
    {
        printf("Error al leer el total de equipos desde el archivo binario.\n");
        fclose(file);
        return;
    }

    printf("\nEquipos disponibles:\n");
    printf("-----------------------------\n");
    printf("| ID   | Nombre del Equipo  |\n");
    printf("-----------------------------\n");

    Equipo equipo;
    for (int i = 0; i < total; i++)
    {
        if (fread(&equipo, sizeof(Equipo), 1, file) != 1)
        {
            printf("Error al leer los datos del equipo.\n");
            fclose(file);
            return;
        }
        printf("| %-4d | %-18s |\n", equipo.id_equipo, equipo.nombre_equipo);
    }

    fclose(file);
    printf("-----------------------------\n");
}

void imprimirPosicionesDisponibles()
{
    printf("\nPosiciones disponibles:\n");
    printf("1. Arquero\n");
    printf("2. Defensa\n");
    printf("3. Mediocampista\n");
    printf("4. Delantero\n");
}

int asignarPosicion(int id_posicion, char *posicion)
{
    switch (id_posicion)
    {
    case 1:
        strcpy(posicion, "Arquero");
        break;
    case 2:
        strcpy(posicion, "Defensa");
        break;
    case 3:
        strcpy(posicion, "Mediocampista");
        break;
    case 4:
        strcpy(posicion, "Delantero");
        break;
    default:
        return 0; // ID de posicion invalido
    }
    return 1; // ID de posicion valido
}

void agregarUsuarioJugador(int id_usuario, int id_jugador)
{
    if (total_usuarios_jugadores < MAX_USUARIOS_JUGADORES)
    {
        usuarios_jugadores[total_usuarios_jugadores].id_usuario = id_usuario;
        usuarios_jugadores[total_usuarios_jugadores].id_jugador = id_jugador;
        total_usuarios_jugadores++;
    }
    else
    {
        printf("Limite de usuarios-jugadores alcanzado.\n");
    }
}

int esUsuarioJugador(int id_usuario)
{
    for (int j = 0; j < total_jugadores; j++)
    {
        if (jugadores[j].id_usuario == id_usuario)
        {
            return 1; // El usuario ya es un jugador
        }
    }
    return 0; // El usuario no es un jugador
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
            printf("Numero de Camiseta: %d\n", jugadores[i].numero_de_camiseta);
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
            printf("Ingrese el nuevo numero de camiseta (actual: %d): ", jugadores[i].numero_de_camiseta);
            scanf("%d", &jugadores[i].numero_de_camiseta);
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
    // Implementar ABM Roles aqui (Agregar, Buscar, Modificar, Eliminar)

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
    { // Comprobar limite de jugadores
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
        printf("Limite de roles alcanzado.\n");
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
    // Implementar ABM Permisos aqui (Agregar, Buscar, Modificar, Eliminar)
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
    { // Comprobar limite de jugadores
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
        printf("Limite de permisos alcanzado.\n");
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

// --------------------------------------- ABM EQUIPOS ---------------------------------------

void cargarDatosEquipos()
{
    FILE *file_bin = fopen(archivo_equipos_bin, "rb");

    if (file_bin != NULL)
    {
        // Cargar desde archivo binario
        if (fread(&total_equipos, sizeof(int), 1, file_bin) != 1)
        {
            printf("Error al leer el total de equipos desde el archivo binario.\n");
            fclose(file_bin);
            return;
        }

        if (total_equipos > MAX_EQUIPOS)
        {
            printf("Error: El archivo binario contiene mas equipos de los permitidos (%d).\n", MAX_EQUIPOS);
            fclose(file_bin);
            return;
        }

        if (fread(equipos, sizeof(Equipo), total_equipos, file_bin) != (size_t)total_equipos)
        {
            printf("Error al leer los datos de equipos desde el archivo binario.\n");
            fclose(file_bin);
            return;
        }

        fclose(file_bin);
        printf("Datos cargados desde el archivo binario '%s' con exito.\n", archivo_equipos_bin);
    }
    else
    {
        printf("Archivo binario no encontrado. Cargando datos desde el archivo de texto...\n");
        cargarEquiposDesdeTxt();
    }
}

void guardarEquiposBin()
{
    FILE *file_bin = fopen(archivo_equipos_bin, "wb");
    if (file_bin == NULL)
    {
        perror("Error al abrir el archivo binario para guardar los datos");
        return;
    }

    if (fwrite(&total_equipos, sizeof(int), 1, file_bin) != 1)
    {
        printf("Error al guardar el total de equipos en el archivo binario.\n");
        fclose(file_bin);
        return;
    }

    if (fwrite(equipos, sizeof(Equipo), total_equipos, file_bin) != (size_t)total_equipos)
    {
        printf("Error al guardar los datos de equipos en el archivo binario.\n");
        fclose(file_bin);
        return;
    }

    printf("Datos guardados en el archivo binario '%s' con exito.\n", archivo_equipos_bin);
    fclose(file_bin);
}

void guardarEquipoEnBinario(Equipo nuevo)
{
    FILE *file = fopen(archivo_equipos_bin, "rb+");
    if (file == NULL)
    {
        // Si no existe, crearlo y escribir
        file = fopen(archivo_equipos_bin, "wb");
        if (file == NULL)
        {
            perror("Error al crear el archivo binario");
            return;
        }
        fwrite(&total_equipos, sizeof(int), 1, file);
    }
    else
    {
        fseek(file, 0, SEEK_SET);
        fwrite(&total_equipos, sizeof(int), 1, file);
    }

    fseek(file, 0, SEEK_END);
    if (fwrite(&nuevo, sizeof(Equipo), 1, file) != 1)
    {
        perror("Error al escribir el equipo en el archivo binario");
    }
    else
    {
        printf("Archivo binario de equipos actualizado con exito.\n");
    }

    fclose(file);
}

void cargarEquiposDesdeTxt()
{
    FILE *file_txt = fopen(archivo_equipos_txt, "r");
    if (file_txt == NULL)
    {
        printf("No se pudo abrir el archivo de texto '%s'.\n", archivo_equipos_txt);
        return;
    }

    total_equipos = 0; // Reiniciar el contador de equipos
    char linea[256];
    while (fgets(linea, sizeof(linea), file_txt))
    {
        Equipo temp;
        if (sscanf(linea, "%d;%99[^\n]", &temp.id_equipo, temp.nombre_equipo) == 2)
        {
            if (total_equipos < MAX_EQUIPOS)
            {
                equipos[total_equipos++] = temp;
            }
            else
            {
                printf("Se alcanzo el limite maximo de equipos (%d).\n", MAX_EQUIPOS);
                break;
            }
        }
        else
        {
            printf("Formato incorrecto en la linea: %s", linea);
        }
    }
    fclose(file_txt);

    if (total_equipos > 0)
    {
        printf("Datos cargados desde el archivo de texto '%s' con exito.\n", archivo_equipos_txt);
        guardarEquiposBin();
    }
    else
    {
        printf("No se encontraron datos validos en el archivo de texto '%s'.\n", archivo_equipos_txt);
    }
}

void imprimirEquipos()
{
    FILE *file = fopen(archivo_equipos_bin, "rb"); // Abrir el archivo binario en modo lectura
    if (file == NULL)
    {
        printf("Error al abrir el archivo de equipos.\n");
        return;
    }

    int total;
    if (fread(&total, sizeof(int), 1, file) != 1)
    {
        printf("Error al leer el total de equipos desde el archivo binario.\n");
        fclose(file);
        return;
    }

    printf("\nEquipos registrados:\n");
    printf("-----------------------------\n");
    printf("| ID   | Nombre del Equipo  |\n");
    printf("-----------------------------\n");

    Equipo equipo;
    for (int i = 0; i < total; i++)
    {
        if (fread(&equipo, sizeof(Equipo), 1, file) != 1)
        {
            printf("Error al leer los datos del equipo.\n");
            fclose(file);
            return;
        }
        printf("| %-4d | %-18s |\n", equipo.id_equipo, equipo.nombre_equipo);
    }

    fclose(file);
    printf("-----------------------------\n");
}

void menuEquiposABM()
{
    int opcion;
    do
    {
        printf("\n=== ABM Equipos ===\n");
        printf("1. Agregar Equipo\n");
        printf("2. Buscar Equipo\n");
        printf("3. Modificar Equipo\n");
        printf("4. Eliminar Equipo\n");
        printf("5. Volver al Menu Principal\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            agregarEquipo();
            break;
        case 2:
            buscarEquipo();
            break;
        case 3:
            modificarEquipo();
            break;
        case 4:
            eliminarEquipo();
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

void agregarEquipo()
{
    if (total_equipos >= 100)
    {
        printf("Limite de equipos alcanzado.\n");
        return;
    }

    Equipo nuevo;
    printf("Ingrese el ID del equipo: ");
    scanf("%d", &nuevo.id_equipo);
    printf("Ingrese el nombre del equipo: ");
    scanf("%s", nuevo.nombre_equipo);

    equipos[total_equipos++] = nuevo;
    guardarEquipoEnBinario(nuevo);
    printf("Equipo agregado con exito.\n");
}

void buscarEquipo()
{
    int id_equipo;
    printf("Ingrese el ID del equipo a buscar: ");
    scanf("%d", &id_equipo);
    for (int i = 0; i < total_equipos; i++)
    {
        if (equipos[i].id_equipo == id_equipo)
        {
            printf("\n=== Equipo Encontrado ===\n");
            printf("ID: %d\n", equipos[i].id_equipo);
            printf("Nombre del Equipo: %s\n", equipos[i].nombre_equipo);
            return;
        }
    }
    printf("Equipo no encontrado.\n");
}

void modificarEquipo()
{
    int id_equipo;
    printf("Ingrese el ID del equipo a modificar: ");
    scanf("%d", &id_equipo);
    for (int i = 0; i < total_equipos; i++)
    {
        if (equipos[i].id_equipo == id_equipo)
        {
            printf("Ingrese el nuevo nombre del equipo (actual: %s): ", equipos[i].nombre_equipo);
            scanf("%s", equipos[i].nombre_equipo);
            printf("Equipo modificado con exito.\n");

            guardarEquiposBin();
            return;
        }
    }
    printf("Equipo no encontrado.\n");
}

void eliminarEquipo()
{
    int id_equipo;
    printf("Ingrese el ID del equipo a eliminar: ");
    scanf("%d", &id_equipo);
    for (int i = 0; i < total_equipos; i++)
    {
        if (equipos[i].id_equipo == id_equipo)
        {
            for (int j = i; j < total_equipos - 1; j++)
            {
                equipos[j] = equipos[j + 1]; // Mover los elementos hacia atras
            }
            total_equipos--; // Disminuir el contador de equipos
            printf("Equipo eliminado con exito.\n");

            guardarEquiposBin();
            return;
        }
    }
    printf("Equipo no encontrado.\n");
}

// --------------------------------------- FUNCIONES AUXILIARES ---------------------------------------

int asignarNumeroDeUsuario()
{
    // buscar los numero de usuario y devolver un numero que no fue usado
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
    // El email debe tener un @ y al menos un caracter antes y despues
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
void guardarJugadoresBin()
{
    FILE *file_bin = fopen(archivo_jugadores_bin, "wb");
    if (file_bin == NULL)
    {
        perror("Error al abrir el archivo binario para guardar los datos");
        return;
    }

    if (fwrite(&total_jugadores, sizeof(int), 1, file_bin) != 1)
    {
        printf("Error al guardar el total de jugadores en el archivo binario.\n");
        fclose(file_bin);
        return;
    }

    if (fwrite(jugadores, sizeof(Jugador), total_jugadores, file_bin) != (size_t)total_jugadores)
    {
        printf("Error al guardar los datos de jugadores en el archivo binario.\n");
        fclose(file_bin);
        return;
    }

    printf("Datos guardados en el archivo binario '%s' con exito.\n", archivo_jugadores_bin);
    fclose(file_bin);
}

void guardarJugadorEnBinario(Jugador nuevo)
{
    FILE *file = fopen(archivo_jugadores_bin, "rb+");
    if (file == NULL)
    {
        // Si no existe, crearlo y escribir
        file = fopen(archivo_jugadores_bin, "wb");
        if (file == NULL)
        {
            perror("Error al crear el archivo binario");
            return;
        }
        fwrite(&total_jugadores, sizeof(int), 1, file);
    }
    else
    {
        fseek(file, 0, SEEK_SET);
        fwrite(&total_jugadores, sizeof(int), 1, file);
    }

    fseek(file, 0, SEEK_END);
    if (fwrite(&nuevo, sizeof(Jugador), 1, file) != 1)
    {
        perror("Error al escribir el jugador en el archivo binario");
    }
    else
    {
        printf("Archivo binario de jugadores actualizado con exito.\n");
    }

    fclose(file);
}

void guardarJugadorModificadoEnBinario()
{
    FILE *file = fopen(archivo_jugadores_bin, "rb+");
    if (file == NULL)
    {
        perror("Error al abrir el archivo binario");
        return;
    }

    fseek(file, 0, SEEK_SET);
    fwrite(&total_jugadores, sizeof(int), 1, file);

    for (int i = 0; i < total_jugadores; i++)
    {
        fwrite(&jugadores[i], sizeof(Jugador), 1, file);
    }

    fclose(file);
}

void cargarJugadoresDesdeTxt()
{
    FILE *file_txt = fopen(archivo_jugadores_txt, "r");
    if (file_txt == NULL)
    {
        printf("No se pudo abrir el archivo de texto '%s'.\n", archivo_jugadores_txt);
        return;
    }

    total_jugadores = 0; // Reiniciar el contador de jugadores
    char linea[256];
    while (fgets(linea, sizeof(linea), file_txt))
    {
        Jugador temp;
        if (sscanf(linea, "%d;%d;%d;%49[^;];%d;%d/%d/%d",
                   &temp.id_jugador,
                   &temp.id_usuario,
                   &temp.id_equipo,
                   temp.posicion,
                   &temp.numero_de_camiseta,
                   &temp.fecha_creacion.dia,
                   &temp.fecha_creacion.mes,
                   &temp.fecha_creacion.anio) == 8)
        {
            if (total_jugadores < MAX_JUGADORES)
            {
                jugadores[total_jugadores++] = temp;
            }
            else
            {
                printf("Se alcanzo el limite maximo de jugadores (%d).\n", MAX_JUGADORES);
                break;
            }
        }
        else
        {
            printf("Formato incorrecto en la linea: %s", linea);
        }
    }
    fclose(file_txt);

    if (total_jugadores > 0)
    {
        printf("Datos cargados desde el archivo de texto '%s' con exito.\n", archivo_jugadores_txt);
        guardarJugadoresBin();
    }
    else
    {
        printf("No se encontraron datos validos en el archivo de texto '%s'.\n", archivo_jugadores_txt);
    }
}
void imprimirJugadores()
{
    FILE *file = fopen(archivo_jugadores_bin, "rb"); // Abrir el archivo binario en modo lectura
    if (file == NULL)
    {
        printf("Error al abrir el archivo de jugadores.\n");
        return;
    }

    int total;
    if (fread(&total, sizeof(int), 1, file) != 1)
    {
        printf("Error al leer el total de jugadores desde el archivo binario.\n");
        fclose(file);
        return;
    }

    printf("\nJugadores registrados:\n");
    printf("------------------------------------------------------------------------------------\n");
    printf("| ID   | ID Usuario | ID Equipo | Posicion      | Numero de Camiseta  | Fecha      |\n");
    printf("------------------------------------------------------------------------------------\n");

    Jugador jugador;
    for (int i = 0; i < total; i++)
    {
        if (fread(&jugador, sizeof(Jugador), 1, file) != 1)
        {
            printf("Error al leer los datos del jugador.\n");
            fclose(file);
            return;
        }
        printf("| %-4d | %-10d | %-9d | %-13s | %-19d | %02d/%02d/%4d |\n",
               jugador.id_jugador,
               jugador.id_usuario,
               jugador.id_equipo,
               jugador.posicion,
               jugador.numero_de_camiseta,
               jugador.fecha_creacion.dia,
               jugador.fecha_creacion.mes,
               jugador.fecha_creacion.anio);
    }

    fclose(file);
    printf("----------------------------------------------------------------------------------------------\n");
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef char cadena[200];

typedef struct
{
    int dia;
    int mes;
    int anio;
} Fecha;

typedef struct
{
    int id_usuario;
    cadena nombre;
    cadena apellido;
    cadena email;
    cadena contrasenia;
    Fecha fecha_creacion;
} Usuario;

typedef struct
{
    int id_jugador;
    int id_usuario;
    int id_equipo;
    cadena posicion;
    int numero_creacion;
    Fecha fecha_creacion;
} Jugador;

typedef struct
{
    int id_rol;
    cadena nombre_rol;
    cadena descripcion;
    Fecha fecha_creacion;
} Rol;

typedef struct
{
    int id_usuario;
    int id_rol;
} Usuario_Role;

typedef struct
{
    int id_permiso;
    cadena nombre_permiso;
    cadena descripcion;
    Fecha fecha_creacion;
} Permiso;

typedef struct
{
    int id_rol;
    int id_permiso;
} Role_Permiso;

typedef struct
{
    int id_usuario;
    int id_permiso;
} Usuario_Permiso;

Usuario usuarios[100];
Jugador jugadores[100];
Rol roles[100];
Permiso permisos[100];

int total_usuarios = 0;
int total_jugadores = 0;
int total_roles = 0;
int total_permisos = 0;

void cargarDatosUsuarios();
void cargarDatosJugadores();
void cargarDatosRoles();
void cargarDatosPermisos();
void menuPrincipal(int id_rol);
void iniciarSesion();
void mostrarDatosUsuario(int id_usuario);
void abmUsuarios();
void abmJugadores();
void abmRoles();
void abmPermisos();

int main()
{
    cargarDatosUsuarios();
    cargarDatosJugadores();
    cargarDatosRoles();
    cargarDatosPermisos();

    iniciarSesion(); // Iniciar sesion al comenzar
    return 0;
}

void cargarDatosUsuarios()
{
    FILE *file = fopen("../usuarios.txt", "r");
    if (file == NULL)
    {
        printf("Error al abrir el archivo de usuarios.\n");
        return;
    }

    while (fscanf(file, "%d;%[^;];%[^;];%[^;];%[^;];%d/%d/%d",
                  &usuarios[total_usuarios].id_usuario,
                  usuarios[total_usuarios].nombre,
                  usuarios[total_usuarios].apellido,
                  usuarios[total_usuarios].email,
                  usuarios[total_usuarios].contrasenia,
                  &usuarios[total_usuarios].fecha_creacion.dia,
                  &usuarios[total_usuarios].fecha_creacion.mes,
                  &usuarios[total_usuarios].fecha_creacion.anio) != EOF)
    {
        total_usuarios++;
    }
    fclose(file);
}

void cargarDatosJugadores()
{
    FILE *file = fopen("../jugadores.txt", "r");
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
    FILE *file = fopen("../roles.txt", "r");
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
    FILE *file = fopen("../permisos.txt", "r");
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
    printf("Ingrese su email: ");
    scanf("%s", email);
    printf("Ingrese su contrasenia: ");
    scanf("%s", contrasenia);

    for (int i = 0; i < total_usuarios; i++)
    {
        if (strcmp(usuarios[i].email, email) == 0 && strcmp(usuarios[i].contrasenia, contrasenia) == 0)
        {
            printf("Inicio de sesion exitoso. Bienvenido, %s!\n", usuarios[i].nombre);
            menuPrincipal(usuarios[i].id_usuario); // Llamar al menu principal con el id del usuario
            return;
        }
    }
    printf("Email o contrasenia incorrectos.\n");
    exit(1); // Terminar el programa si la sesion falla
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
                abmUsuarios(); // Llamar a la funcion ABM Usuarios
            }
            else
            {
                mostrarDatosUsuario(id_usuario);
            }
            break;
        case 2:
            if (rol_usuario == 1)
            {
                abmJugadores(); // Llamar a la funcion ABM Jugadores
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

void abmUsuarios()
{
    int opcion;
    do
    {
        printf("\n=== ABM Usuarios ===\n");
        printf("1. Agregar Usuario\n");
        printf("2. Buscar Usuario\n");
        printf("3. Modificar Usuario\n");
        printf("4. Eliminar Usuario\n");
        printf("5. Volver al Menu Principal\n");
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
            modificarUsuario();
            break;
        case 4:
            eliminarUsuario();
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

void agregarUsuario()
{
    if (total_usuarios < 100)
    { // Comprobar limite de usuarios
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        Usuario nuevo;
        printf("Ingrese el ID de usuario: ");
        scanf("%d", &nuevo.id_usuario);
        printf("Ingrese el nombre: ");
        scanf("%s", nuevo.nombre);
        printf("Ingrese el apellido: ");
        scanf("%s", nuevo.apellido);
        printf("Ingrese el email: ");
        scanf("%s", nuevo.email);
        printf("Ingrese la contrasenia: ");
        scanf("%s", nuevo.contrasenia);
        nuevo.fecha_creacion.dia = tm.tm_mday,
        nuevo.fecha_creacion.mes = tm.tm_mon + 1,
        nuevo.fecha_creacion.anio = tm.tm_year + 1900;

        // Agregar el nuevo usuario al arreglo
        usuarios[total_usuarios++] = nuevo;
        printf("Usuario agregado con exito.\n");
    }
    else
    {
        printf("Limite de usuarios alcanzado.\n");
    }
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

void abmJugadores()
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
    { // Comprobar limite de jugadores

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
        printf("Limite de jugadores alcanzado.\n");
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
            printf("Fecha de Creacion: %02d/%02d/%04d\n",
                   jugadores[i].fecha_creacion.dia,
                   jugadores[i].fecha_creacion.mes,
                   jugadores[i].fecha_creacion.anio);
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

void abmRoles()
{
    // Similar a las funciones anteriores para manejar roles
    // Implementar ABM Roles aqui (Agregar, Buscar, Modificar, Eliminar)
}

void abmPermisos()
{
    // Similar a las funciones anteriores para manejar permisos
    // Implementar ABM Permisos aqui (Agregar, Buscar, Modificar, Eliminar)
}

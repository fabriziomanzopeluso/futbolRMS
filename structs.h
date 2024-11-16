// estructuras.h
#ifndef structs
#define structs

typedef char cadena[100]; // Si esta definición no está ya incluida en otro lado

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

#endif // structs

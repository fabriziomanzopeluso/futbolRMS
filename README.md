# Fútbol RMS

**Desarrolladores:** Rodríguez, Manzo, Solís  
**Fecha de inicio:** 1 de julio de 2024  
**Materia:** Estructuras y Bases de Datos - INSPT

## Visión General

Fútbol RMS es una aplicación web gratuita diseñada para colegios que permite gestionar múltiples torneos de fútbol. El objetivo es facilitar la organización y seguimiento de los torneos internos, promoviendo así la participación deportiva entre los estudiantes.

## Objetivos

1. **Facilitar la gestión de torneos:**
   - Permitir a los colegios crear y administrar múltiples torneos.
   - Facilitar la inscripción de equipos y jugadores.

2. **Organizar partidos y resultados:**
   - Proveer un calendario de partidos para cada torneo.
   - Registrar resultados y estadísticas de los partidos.

3. **Promover la participación estudiantil:**
   - Incentivar la práctica del deporte entre los estudiantes.
   - Ofrecer una plataforma accesible y fácil de usar.

4. **Generar reportes y estadísticas:**
   - Proporcionar estadísticas detalladas por torneo, equipo y jugador.
   - Generar reportes de rendimiento para los colegios.

## Especificaciones

### Módulos Principales

- **Gestión de Torneos:** 
  - Crear, editar y eliminar torneos.
  
- **Gestión de Equipos:** 
  - Registrar equipos y asignarlos a torneos.
  
- **Gestión de Jugadores:** 
  - Inscribir jugadores y asociarlos a equipos.
  
- **Gestión de Partidos:** 
  - Programar y registrar resultados de partidos.
  
- **Estadísticas y Reportes:** 
  - Visualizar estadísticas y generar reportes.

### Requisitos Técnicos

- **Base de Datos:** 
  - Relacional, soportando múltiples torneos y entidades relacionadas. Las tablas y relaciones han sido creadas en MySQL.
  
- **Accesibilidad:** 
  - Acceso multiusuario con roles específicos.

## Funcionalidad en C

Este proyecto incluye una implementación en C para la gestión de los siguientes módulos:

1. **ABM (Alta, Baja, Modificación) de Usuarios**
   - Permite crear, buscar, modificar y eliminar usuarios del sistema.

2. **ABM de Perfiles**
   - Permite gestionar perfiles de usuario, asignando roles y permisos específicos.

3. **ABM de Jugadores**
   - Facilita la inscripción de jugadores y su asociación a equipos.

4. **ABM de Roles**
   - Permite crear, buscar, modificar y eliminar roles de usuario.

5. **ABM de Permisos**
   - Permite crear, buscar, modificar y eliminar permisos asociados a los roles.

6. **ABM de Equipos**
   - Gestiona la creación y modificación de equipos, asignándolos a los torneos correspondientes.

### Acceso al Sistema

- El acceso se realiza a través de una interfaz de administración (`admin-admin`), donde pueden existir datos precargados para la simulación.


## Instalación

Para configurar y ejecutar la aplicación **Fútbol RMS**, sigue estos pasos:

### Requisitos Previos

- **Sistema Operativo:** Se recomienda Linux (Ubuntu o derivadas).
- **Compilador de C:** Asegúrate de tener instalado un compilador como `gcc`.
- **MySQL:** Debes tener instalado y configurado MySQL.

### Pasos de Instalación

1. **Clonar el Repositorio**
   ```bash
   git clone https://github.com/fabriziomanzopeluso/futbolRMS
   cd FutbolRMS
   ```

2. **Compilar el Proyecto**
   - Ejecuta el siguiente comando para compilar el código:
   ```bash
   gcc -o futbolRMS main.c
   ```
   
3. **Ejecutar la Aplicación**
   - Inicia la aplicación con el siguiente comando:
   ```bash
   ./futbolRMS
   ```

### Notas Adicionales

- Asegúrate de tener las credenciales correctas para acceder a la base de datos en el código.
- Para cualquier error durante la compilación o ejecución, revisa los mensajes en la consola y ajusta las configuraciones según sea necesario.

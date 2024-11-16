-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Servidor: localhost
-- Tiempo de generación: 16-08-2024 a las 00:19:59
-- Versión del servidor: 10.4.32-MariaDB
-- Versión de PHP: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `FutbolRMS`
--
CREATE DATABASE IF NOT EXISTS `FutbolRMS` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci;
USE `FutbolRMS`;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `Colegio`
--

DROP TABLE IF EXISTS `Colegio`;
CREATE TABLE `Colegio` (
  `id_colegio` int(11) NOT NULL,
  `nombre` varchar(255) NOT NULL,
  `direccion` varchar(255) DEFAULT NULL,
  `telefono` varchar(20) DEFAULT NULL,
  `email` varchar(255) DEFAULT NULL,
  `fecha_creacion` timestamp NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `Equipo`
--

DROP TABLE IF EXISTS `Equipo`;
CREATE TABLE `Equipo` (
  `id_equipo` int(11) NOT NULL,
  `nombre` varchar(255) NOT NULL,
  `id_torneo` int(11) DEFAULT NULL,
  `id_colegio` int(11) DEFAULT NULL,
  `foto_equipo` varchar(255) DEFAULT NULL,
  `fecha_creacion` timestamp NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `Estadistica`
--

DROP TABLE IF EXISTS `Estadistica`;
CREATE TABLE `Estadistica` (
  `id_estadistica` int(11) NOT NULL,
  `id_jugador` int(11) DEFAULT NULL,
  `id_partido` int(11) DEFAULT NULL,
  `goles` int(11) DEFAULT 0,
  `asistencias` int(11) DEFAULT 0,
  `tarjetas_amarillas` int(11) DEFAULT 0,
  `tarjetas_rojas` int(11) DEFAULT 0,
  `minutos_jugados` int(11) DEFAULT 0,
  `fecha_creacion` timestamp NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `Jugador`
--

DROP TABLE IF EXISTS `Jugador`;
CREATE TABLE `Jugador` (
  `id_jugador` int(11) NOT NULL,
  `id_usuario` int(11) DEFAULT NULL,
  `id_equipo` int(11) DEFAULT NULL,
  `posicion` varchar(50) DEFAULT NULL,
  `numero_camiseta` int(11) DEFAULT NULL,
  `fecha_creacion` timestamp NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `Partido`
--

DROP TABLE IF EXISTS `Partido`;
CREATE TABLE `Partido` (
  `id_partido` int(11) NOT NULL,
  `id_torneo` int(11) DEFAULT NULL,
  `equipo_local` int(11) DEFAULT NULL,
  `equipo_visitante` int(11) DEFAULT NULL,
  `fecha_partido` datetime DEFAULT NULL,
  `goles_local` int(11) DEFAULT 0,
  `goles_visitante` int(11) DEFAULT 0,
  `estado` enum('pendiente','jugado','cancelado') DEFAULT 'pendiente',
  `fecha_creacion` timestamp NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `Permiso`
--

DROP TABLE IF EXISTS `Permiso`;
CREATE TABLE `Permiso` (
  `id_permiso` int(11) NOT NULL,
  `nombre_permiso` varchar(100) NOT NULL,
  `descripcion` varchar(255) DEFAULT NULL,
  `fecha_creacion` timestamp NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `Rol`
--

DROP TABLE IF EXISTS `Rol`;
CREATE TABLE `Rol` (
  `id_rol` int(11) NOT NULL,
  `nombre_rol` varchar(50) NOT NULL,
  `descripcion` varchar(255) DEFAULT NULL,
  `fecha_creacion` timestamp NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `Role_Permiso`
--

DROP TABLE IF EXISTS `Role_Permiso`;
CREATE TABLE `Role_Permiso` (
  `id_rol` int(11) NOT NULL,
  `id_permiso` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `Torneo`
--

DROP TABLE IF EXISTS `Torneo`;
CREATE TABLE `Torneo` (
  `id_torneo` int(11) NOT NULL,
  `nombre` varchar(255) NOT NULL,
  `id_colegio` int(11) DEFAULT NULL,
  `fecha_inicio` date DEFAULT NULL,
  `fecha_fin` date DEFAULT NULL,
  `estado` enum('activo','finalizado','cancelado') DEFAULT 'activo',
  `fecha_creacion` timestamp NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `Usuario`
--

DROP TABLE IF EXISTS `Usuario`;
CREATE TABLE `Usuario` (
  `id_usuario` int(11) NOT NULL,
  `nombre` varchar(100) NOT NULL,
  `apellido` varchar(100) NOT NULL,
  `email` varchar(255) NOT NULL,
  `contraseña` varchar(255) NOT NULL,
  `fecha_creacion` timestamp NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `Usuario_Permiso`
--

DROP TABLE IF EXISTS `Usuario_Permiso`;
CREATE TABLE `Usuario_Permiso` (
  `id_usuario` int(11) NOT NULL,
  `id_permiso` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `Usuario_Role`
--

DROP TABLE IF EXISTS `Usuario_Role`;
CREATE TABLE `Usuario_Role` (
  `id_usuario` int(11) NOT NULL,
  `id_rol` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;




-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `Incidencia`
--

DROP TABLE IF EXISTS `Incidencia`;
CREATE TABLE `Incidencia` (
  `id_incidencia` int(11) NOT NULL,
  `minuto` int(11) NOT NULL,
  `id_partido` int(11) NOT NULL,
  `id_tipo_incidencia` int(11) NOT NULL,
  `id_jugador` int(11)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;




-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `Tipo_Incidencia`
--

DROP TABLE IF EXISTS `Tipo_Incidencia`;
CREATE TABLE `Tipo_Incidencia` (
  `id_tipo_incidencia` int(11) NOT NULL,
  `tipo_incidencia` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `Colegio`
--
ALTER TABLE `Colegio`
  ADD PRIMARY KEY (`id_colegio`);

--
-- Indices de la tabla `Equipo`
--
ALTER TABLE `Equipo`
  ADD PRIMARY KEY (`id_equipo`),
  ADD KEY `id_torneo` (`id_torneo`),
  ADD KEY `id_colegio` (`id_colegio`);

--
-- Indices de la tabla `Estadistica`
--
ALTER TABLE `Estadistica`
  ADD PRIMARY KEY (`id_estadistica`),
  ADD KEY `id_jugador` (`id_jugador`),
  ADD KEY `id_partido` (`id_partido`);

--
-- Indices de la tabla `Jugador`
--
ALTER TABLE `Jugador`
  ADD PRIMARY KEY (`id_jugador`),
  ADD KEY `id_usuario` (`id_usuario`),
  ADD KEY `id_equipo` (`id_equipo`);

--
-- Indices de la tabla `Partido`
--
ALTER TABLE `Partido`
  ADD PRIMARY KEY (`id_partido`),
  ADD KEY `id_torneo` (`id_torneo`),
  ADD KEY `equipo_local` (`equipo_local`),
  ADD KEY `equipo_visitante` (`equipo_visitante`);

--
-- Indices de la tabla `Permiso`
--
ALTER TABLE `Permiso`
  ADD PRIMARY KEY (`id_permiso`);

--
-- Indices de la tabla `Rol`
--
ALTER TABLE `Rol`
  ADD PRIMARY KEY (`id_rol`);

--
-- Indices de la tabla `Role_Permiso`
--
ALTER TABLE `Role_Permiso`
  ADD PRIMARY KEY (`id_rol`,`id_permiso`),
  ADD KEY `id_permiso` (`id_permiso`);

--
-- Indices de la tabla `Torneo`
--
ALTER TABLE `Torneo`
  ADD PRIMARY KEY (`id_torneo`),
  ADD KEY `id_colegio` (`id_colegio`);

--
-- Indices de la tabla `Usuario`
--
ALTER TABLE `Usuario`
  ADD PRIMARY KEY (`id_usuario`),
  ADD UNIQUE KEY `email` (`email`);

--
-- Indices de la tabla `Usuario_Permiso`
--
ALTER TABLE `Usuario_Permiso`
  ADD PRIMARY KEY (`id_usuario`,`id_permiso`),
  ADD KEY `id_permiso` (`id_permiso`);

--
-- Indices de la tabla `Usuario_Role`
--
ALTER TABLE `Usuario_Role`
  ADD PRIMARY KEY (`id_usuario`,`id_rol`),
  ADD KEY `id_rol` (`id_rol`);

--
-- Indices de la tabla `Incidencia`
--
ALTER TABLE `Incidencia`
  ADD PRIMARY KEY (`id_incidencia`);



--
-- Indices de la tabla `Tipo_Incidencia`
--
ALTER TABLE `Tipo_Incidencia`
  ADD PRIMARY KEY (`id_tipo_incidencia`);

--
-- AUTO_INCREMENT de las tablas volcadas
--

--
-- AUTO_INCREMENT de la tabla `Colegio`
--
ALTER TABLE `Colegio`
  MODIFY `id_colegio` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `Equipo`
--
ALTER TABLE `Equipo`
  MODIFY `id_equipo` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `Estadistica`
--
ALTER TABLE `Estadistica`
  MODIFY `id_estadistica` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `Jugador`
--
ALTER TABLE `Jugador`
  MODIFY `id_jugador` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `Partido`
--
ALTER TABLE `Partido`
  MODIFY `id_partido` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `Permiso`
--
ALTER TABLE `Permiso`
  MODIFY `id_permiso` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `Rol`
--
ALTER TABLE `Rol`
  MODIFY `id_rol` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `Torneo`
--
ALTER TABLE `Torneo`
  MODIFY `id_torneo` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `Usuario`
--
ALTER TABLE `Usuario`
  MODIFY `id_usuario` int(11) NOT NULL AUTO_INCREMENT;



--
-- AUTO_INCREMENT de la tabla `Incidencia`
--
ALTER TABLE `Incidencia`
  MODIFY `id_incidencia` int(11) NOT NULL AUTO_INCREMENT;


--
-- AUTO_INCREMENT de la tabla `Tipo_Incidencia`
--
ALTER TABLE `Tipo_Incidencia`
  MODIFY `id_tipo_incidencia` int(11) NOT NULL AUTO_INCREMENT;

--
-- Restricciones para tablas volcadas
--

--
-- Filtros para la tabla `Equipo`
--
ALTER TABLE `Equipo`
  ADD CONSTRAINT `Equipos_ibfk_1` FOREIGN KEY (`id_torneo`) REFERENCES `Torneo` (`id_torneo`) ON DELETE CASCADE,
  ADD CONSTRAINT `Equipos_ibfk_2` FOREIGN KEY (`id_colegio`) REFERENCES `Colegio` (`id_colegio`) ON DELETE CASCADE;

--
-- Filtros para la tabla `Estadistica`
--
ALTER TABLE `Estadistica`
  ADD CONSTRAINT `Estadisticas_ibfk_1` FOREIGN KEY (`id_jugador`) REFERENCES `Jugador` (`id_jugador`) ON DELETE CASCADE,
  ADD CONSTRAINT `Estadisticas_ibfk_2` FOREIGN KEY (`id_partido`) REFERENCES `Partido` (`id_partido`) ON DELETE CASCADE;

--
-- Filtros para la tabla `Jugador`
--
ALTER TABLE `Jugador`
  ADD CONSTRAINT `Jugadores_ibfk_1` FOREIGN KEY (`id_usuario`) REFERENCES `Usuario` (`id_usuario`) ON DELETE CASCADE,
  ADD CONSTRAINT `Jugadores_ibfk_2` FOREIGN KEY (`id_equipo`) REFERENCES `Equipo` (`id_equipo`) ON DELETE CASCADE;

--
-- Filtros para la tabla `Partido`
--
ALTER TABLE `Partido`
  ADD CONSTRAINT `Partidos_ibfk_1` FOREIGN KEY (`id_torneo`) REFERENCES `Torneo` (`id_torneo`) ON DELETE CASCADE,
  ADD CONSTRAINT `Partidos_ibfk_2` FOREIGN KEY (`equipo_local`) REFERENCES `Equipo` (`id_equipo`) ON DELETE CASCADE,
  ADD CONSTRAINT `Partidos_ibfk_3` FOREIGN KEY (`equipo_visitante`) REFERENCES `Equipo` (`id_equipo`) ON DELETE CASCADE;

--
-- Filtros para la tabla `Role_Permiso`
--
ALTER TABLE `Role_Permiso`
  ADD CONSTRAINT `Role_Permiso_ibfk_1` FOREIGN KEY (`id_rol`) REFERENCES `Rol` (`id_rol`) ON DELETE CASCADE,
  ADD CONSTRAINT `Role_Permiso_ibfk_2` FOREIGN KEY (`id_permiso`) REFERENCES `Permiso` (`id_permiso`) ON DELETE CASCADE;

--
-- Filtros para la tabla `Torneo`
--
ALTER TABLE `Torneo`
  ADD CONSTRAINT `Torneos_ibfk_1` FOREIGN KEY (`id_colegio`) REFERENCES `Colegio` (`id_colegio`);

--
-- Filtros para la tabla `Usuario_Permiso`
--
ALTER TABLE `Usuario_Permiso`
  ADD CONSTRAINT `Usuario_Permiso_ibfk_1` FOREIGN KEY (`id_usuario`) REFERENCES `Usuario` (`id_usuario`) ON DELETE CASCADE,
  ADD CONSTRAINT `Usuario_Permiso_ibfk_2` FOREIGN KEY (`id_permiso`) REFERENCES `Permiso` (`id_permiso`) ON DELETE CASCADE;

--
-- Filtros para la tabla `Usuario_Role`
--
ALTER TABLE `Usuario_Role`
  ADD CONSTRAINT `Usuario_Role_ibfk_1` FOREIGN KEY (`id_usuario`) REFERENCES `Usuario` (`id_usuario`) ON DELETE CASCADE,
  ADD CONSTRAINT `Usuario_Role_ibfk_2` FOREIGN KEY (`id_rol`) REFERENCES `Rol` (`id_rol`) ON DELETE CASCADE;
COMMIT;


--
-- Filtros para la tabla `Usuario_Role`
--
ALTER TABLE `Incidencia`
  ADD CONSTRAINT `Incidencia_ibfk_1` FOREIGN KEY (`id_partido`) REFERENCES `Partido` (`id_partido`) ON DELETE CASCADE,
  ADD CONSTRAINT `Incidencia_Role_ibfk_2` FOREIGN KEY (`id_tipo_incidencia`) REFERENCES `Tipo_Incidencia` (`id_tipo_incidencia`) ON DELETE CASCADE,
  ADD CONSTRAINT `Incidencia_Role_ibfk_3` FOREIGN KEY (`id_jugador`) REFERENCES `Jugador` (`id_jugador`) ON DELETE CASCADE;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

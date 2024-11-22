-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Nov 20, 2024 at 10:27 PM
-- Server version: 10.4.32-MariaDB
-- PHP Version: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `futbolrms`
--
CREATE DATABASE IF NOT EXISTS `futbolrms` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci;
USE `futbolrms`;

--
-- Dumping data for table `colegio`
--

INSERT INTO `colegio` (`id_colegio`, `nombre`, `direccion`, `telefono`, `email`, `fecha_creacion`) VALUES
(1, 'Colegio San Martín', 'Av. Libertador 1234', '1234567890', 'sanmartin@colegio.com', '2024-01-15 12:30:00'),
(2, 'Colegio Nacional', 'Av. Belgrano 5678', '987654321', 'nacional@colegio.com', '2024-02-10 13:15:00'),
(3, 'Colegio Mitre', 'Calle Mitre 2345', '1112223334', 'mitre@colegio.com', '2024-03-05 14:45:00'),
(4, 'Colegio Independencia', 'Calle Rivadavia 6789', '4445556667', 'independencia@colegio.com', '2024-04-20 15:30:00'),
(5, 'Colegio Sarmiento', 'Calle Sarmiento 1357', '5556667778', 'sarmiento@colegio.com', '2024-05-15 11:00:00');



--
-- Dumping data for table `torneo`
--

INSERT INTO `torneo` (`id_torneo`, `nombre`, `id_colegio`, `fecha_inicio`, `fecha_fin`, `estado`, `fecha_creacion`) VALUES
(1, 'Torneo Primavera', 3, '2024-09-01', '2024-09-30', 'activo', '2024-08-01 15:00:00'),
(2, 'Torneo Verano', 2, '2024-12-01', '2025-01-31', 'activo', '2024-09-15 15:00:00'),
(3, 'Torneo Otoño', 1, '2024-03-01', '2024-04-30', 'finalizado', '2024-01-15 15:00:00'),
(4, 'Torneo Invierno', 5, '2024-06-01', '2024-07-31', 'cancelado', '2024-04-10 15:00:00'),
(5, 'Torneo Regional', 4, '2024-05-01', '2024-06-30', 'activo', '2024-03-10 15:00:00');




--
-- Dumping data for table `equipo`
--

INSERT INTO `equipo` (`id_equipo`, `nombre`, `id_torneo`, `id_colegio`, `foto_equipo`, `fecha_creacion`) VALUES
(1, 'Leones de la Ciudad', 1, 1, 'leones_ciudad.jpg', '2024-01-15 12:30:00'),
(2, 'Tigres del Norte', 1, 1, 'tigres_norte.jpg', '2024-02-10 13:15:00'),
(3, 'Águilas de Oro', 2, 2, 'aguilas_oro.jpg', '2024-03-05 14:45:00'),
(4, 'Caballeros de la Luz', 2, 2, 'caballeros_luz.jpg', '2024-04-20 15:30:00'),
(5, 'Galácticos FC', 3, 3, 'galacticos_fc.jpg', '2024-05-15 11:00:00'),
(6, 'Dragones Rojos', 3, 4, 'dragones_rojos.jpg', '2024-06-10 17:00:00'),
(7, 'Gladiadores del Fútbol', 4, 5, 'gladiadores_futbol.jpg', '2024-07-25 19:15:00'),
(8, 'Rápidos de la Ciudad', 4, 3, 'rapidos_ciudad.jpg', '2024-08-12 12:45:00'),
(9, 'Vikings de la Liga', 5, 4, 'vikings_liga.jpg', '2024-09-01 14:00:00'),
(10, 'Campeones de la Esperanza', 5, 5, 'campeones_esperanza.jpg', '2024-09-15 16:30:00'),
(11, 'Falcones de la Montaña', 1, 1, 'falcones_montana.jpg', '2024-01-20 12:30:00'),
(12, 'Corsarios de la Bahía', 1, 1, 'corsarios_bahia.jpg', '2024-02-15 13:15:00'),
(13, 'Reyes de la Arena', 2, 2, 'reyes_arena.jpg', '2024-03-10 14:45:00'),
(14, 'Guerreros del Mar', 2, 2, 'guerreros_mar.jpg', '2024-04-25 15:30:00'),
(15, 'Estrellas del Fútbol', 3, 3, 'estrellas_futbol.jpg', '2024-05-20 11:00:00'),
(16, 'Caballos de Acero', 3, 4, 'caballos_acero.jpg', '2024-06-15 17:00:00'),
(17, 'Rombos de la Fortuna', 4, 5, 'rombos_fortuna.jpg', '2024-07-30 19:15:00'),
(18, 'Rugidos de la Selva', 4, 2, 'rugidos_selva.jpg', '2024-08-18 12:45:00'),
(19, 'Cachorros del Futuro', 5, 2, 'cachorros_futuro.jpg', '2024-09-10 14:00:00'),
(20, 'Leones del Oeste', 5, 1, 'leones_oeste.jpg', '2024-09-20 16:30:00'),
(21, 'Sombra de la Noche', 1, 1, 'sombra_noche.jpg', '2024-01-25 12:30:00'),
(22, 'Caras de la Luna', 1, 1, 'caras_luna.jpg', '2024-02-20 13:15:00'),
(23, 'Tiburones del Océano', 2, 2, 'tiburones_oceano.jpg', '2024-03-15 14:45:00'),
(24, 'Delfines del Río', 2, 2, 'delfines_rio.jpg', '2024-04-30 15:30:00'),
(25, 'Dragones Azules', 3, 3, 'dragones_azules.jpg', '2024-05-25 11:00:00'),
(26, 'Sirenas del Lago', 3, 4, 'sirenas_lago.jpg', '2024-06-20 17:00:00'),
(27, 'Piratas de la Costa', 4, 5, 'piratas_costa.jpg', '2024-07-15 19:15:00'),
(28, 'Guardianes del Clima', 4, 4, 'guardianes_clima.jpg', '2024-08-25 12:45:00'),
(29, 'Fuerza del Norte', 5, 2, 'fuerza_norte.jpg', '2024-09-05 14:00:00'),
(30, 'Guardianes del Tiempo', 5, 2, 'guardianes_tiempo.jpg', '2024-09-22 16:30:00'),
(31, 'Monarcas del Viento', 1, 1, 'monarcas_viento.jpg', '2024-01-30 12:30:00'),
(32, 'Centauros de la Pradera', 1, 1, 'centauros_pradera.jpg', '2024-02-28 13:15:00'),
(33, 'Thunder de la Tormenta', 2, 2, 'thunder_tormenta.jpg', '2024-03-20 14:45:00'),
(34, 'Rugientes de la Montaña', 2, 2, 'rugientes_montana.jpg', '2024-04-12 15:30:00'),
(35, 'Cazadores de la Noche', 3, 3, 'cazadores_noche.jpg', '2024-05-28 11:00:00'),
(36, 'Viento de la Libertad', 3, 4, 'viento_libertad.jpg', '2024-06-28 17:00:00'),
(37, 'Máscaras del Futuro', 4, 5, 'mascaras_futuro.jpg', '2024-07-30 19:15:00'),
(38, 'Héroes del Océano', 4, 2, 'heroes_oceano.jpg', '2024-08-30 12:45:00'),
(39, 'Gigantes del Fútbol', 5, 4, 'gigantes_futbol.jpg', '2024-09-15 14:00:00'),
(40, 'Cazadores de Utopías', 5, 1, 'cazadores_utopias.jpg', '2024-09-29 16:30:00');



--
-- Dumping data for table `usuario`
--

INSERT INTO `usuario` (`id_usuario`, `nombre`, `apellido`, `email`, `contraseña`, `fecha_creacion`) VALUES
(1, 'Robert', 'Howard', 'robert.howard@example.com', '6CaAos5q', '2023-03-02 03:00:00'),
(2, 'Haley', 'Hayden', 'haley.hayden@example.com', 'fT6Wt6CS', '2022-02-15 03:00:00'),
(3, 'Nicole', 'Baker', 'nicole.baker@example.com', '48RYyh0a', '2020-07-20 03:00:00'),
(4, 'Tonya', 'Long', 'tonya.long@example.com', '1Ud4BsiL', '2023-09-26 03:00:00'),
(5, 'Chris', 'Wang', 'chris.wang@example.com', 'j5dGwKTt', '2022-10-10 03:00:00'),
(6, 'Craig', 'Nelson', 'craig.nelson@example.com', 'J6hWs6Rx', '2021-10-26 03:00:00'),
(7, 'Kimberly', 'Trujillo', 'kimberly.trujillo@example.com', '92SRuyLe', '2022-08-11 03:00:00'),
(8, 'Lauren', 'Robertson', 'lauren.robertson@example.com', '91ATnvRa', '2020-10-14 03:00:00'),
(9, 'Katelyn', 'Cruz', 'katelyn.cruz@example.com', '4Ec30oat', '2023-07-17 03:00:00'),
(10, 'Stephen', 'Carpenter', 'stephen.carpenter@example.com', 'BfY8Q7eO', '2023-11-22 03:00:00'),
(11, 'Andrew', 'Kane', 'andrew.kane@example.com', '0K1iTZjG', '2022-06-17 03:00:00'),
(12, 'Ethan', 'Hall', 'ethan.hall@example.com', 'x6UTMxEy', '2022-01-15 03:00:00'),
(13, 'Joel', 'Morrow', 'joel.morrow@example.com', 'n1vELkdl', '2020-03-25 03:00:00'),
(14, 'Kevin', 'Barnes', 'kevin.barnes@example.com', 'a3YT0IsS', '2022-07-03 03:00:00'),
(15, 'John', 'Wheeler', 'john.wheeler@example.com', 'X50E9sNy', '2022-12-02 03:00:00'),
(16, 'Adrienne', 'Goodman', 'adrienne.goodman@example.com', '39LEBWcQ', '2020-06-12 03:00:00'),
(17, 'Ashley', 'Bonilla', 'ashley.bonilla@example.com', 'u1pGJkSo', '2020-08-22 03:00:00'),
(18, 'Brian', 'Grant', 'brian.grant@example.com', '6a2OCO1o', '2024-08-17 03:00:00'),
(19, 'Christine', 'Cole', 'christine.cole@example.com', 'usgJh9Mv', '2021-03-10 03:00:00'),
(20, 'Thomas', 'Wallace', 'thomas.wallace@example.com', 'WN7NMncv', '2023-05-31 03:00:00'),
(21, 'Michael', 'Mathis', 'michael.mathis@example.com', '1FwSLq3s', '2022-10-13 03:00:00'),
(22, 'Amanda', 'Levy', 'amanda.levy@example.com', 'L4cjhLzr', '2021-03-08 03:00:00'),
(23, 'Matthew', 'Martinez', 'matthew.martinez@example.com', '43zmPMNi', '2024-11-10 03:00:00'),
(24, 'Nicholas', 'Nguyen', 'nicholas.nguyen@example.com', '9BmJtM6h', '2024-07-30 03:00:00'),
(25, 'Stephanie', 'Anderson', 'stephanie.anderson@example.com', '25T8lgqG', '2021-01-15 03:00:00'),
(26, 'Lisa', 'Daniels', 'lisa.daniels@example.com', '7Zw4YqMH', '2021-05-24 03:00:00'),
(27, 'Annette', 'Clark', 'annette.clark@example.com', 'A00UOFEy', '2023-02-20 03:00:00'),
(28, 'Valerie', 'Cross', 'valerie.cross@example.com', '7GJowpUx', '2022-04-14 03:00:00'),
(29, 'Carol', 'Jones', 'carol.jones@example.com', '1IOZ7iRL', '2022-08-18 03:00:00'),
(30, 'Trevor', 'Reese', 'trevor.reese@example.com', '67JePHAg', '2021-04-15 03:00:00'),
(31, 'Chris', 'Lewis', 'chris.lewis@example.com', 'PVc0J1uE', '2023-01-13 03:00:00'),
(32, 'Lisa', 'Smith', 'lisa.smith@example.com', '0bDK8WGo', '2021-02-24 03:00:00'),
(33, 'Donald', 'Logan', 'donald.logan@example.com', '7D0VFHny', '2020-05-16 03:00:00'),
(34, 'Zachary', 'Morse', 'zachary.morse@example.com', '8LTnhjh5', '2023-03-26 03:00:00'),
(35, 'Brian', 'Martin', 'brian.martin@example.com', 'U3ClKGgl', '2023-05-06 03:00:00'),
(36, 'Gregory', 'Holloway', 'gregory.holloway@example.com', '8BJ1sJal', '2022-12-08 03:00:00'),
(37, 'Keith', 'Jackson', 'keith.jackson@example.com', '8oOiD0v1', '2023-06-17 03:00:00'),
(38, 'Jessica', 'Olson', 'jessica.olson@example.com', '633g1NeQ', '2022-10-23 03:00:00'),
(39, 'Kelsey', 'Silva', 'kelsey.silva@example.com', 'sGbK8pUm', '2023-01-26 03:00:00'),
(40, 'Corey', 'Cook', 'corey.cook@example.com', 'R37tgMUf', '2022-09-05 03:00:00'),
(41, 'Timothy', 'Perry', 'timothy.perry@example.com', 'R0FCk3Rq', '2024-08-30 03:00:00'),
(42, 'Darren', 'Harris', 'darren.harris@example.com', '6nJ98M7z', '2023-03-03 03:00:00'),
(43, 'Alexandra', 'Barr', 'alexandra.barr@example.com', 'Km8TIBnW', '2022-04-28 03:00:00'),
(44, 'Cynthia', 'Nelson', 'cynthia.nelson@example.com', 'yzk1OwFR', '2020-02-24 03:00:00'),
(45, 'Andrew', 'Marshall', 'andrew.marshall@example.com', 'B66OKSzh', '2024-07-05 03:00:00'),
(46, 'Stephen', 'Vasquez', 'stephen.vasquez@example.com', '5EegBxx7', '2021-06-14 03:00:00'),
(47, 'Chad', 'Wells', 'chad.wells@example.com', '1ZNATEmn', '2020-03-23 03:00:00'),
(48, 'William', 'Stewart', 'william.stewart@example.com', 'C6AbbB39', '2023-08-04 03:00:00'),
(49, 'Karen', 'Richardson', 'karen.richardson@example.com', 't13WZntP', '2021-04-11 03:00:00'),
(50, 'Abigail', 'Yang', 'abigail.yang@example.com', '3OsRcl8r', '2022-12-11 03:00:00'),
(51, 'Cody', 'Williams', 'cody.williams@example.com', '2DuBfptz', '2020-05-12 03:00:00'),
(52, 'Michelle', 'Brown', 'michelle.brown@example.com', '2rSaytAu', '2020-07-11 03:00:00'),
(53, 'Michael', 'Harris', 'michael.harris@example.com', '3VNFRkCe', '2023-02-20 03:00:00'),
(54, 'Pamela', 'Gonzales', 'pamela.gonzales@example.com', 'n3CDOInt', '2024-10-29 03:00:00'),
(55, 'Sheryl', 'Wheeler', 'sheryl.wheeler@example.com', '2TQKGhUv', '2022-04-08 03:00:00'),
(56, 'Craig', 'Vaughn', 'craig.vaughn@example.com', '5EXDiSXv', '2024-10-27 03:00:00'),
(57, 'Andrew', 'Jacobson', 'andrew.jacobson@example.com', '8U9jbcfj', '2020-09-04 03:00:00'),
(58, 'James', 'Hernandez', 'james.hernandez@example.com', '2Knp60bX', '2023-05-10 03:00:00'),
(59, 'Scott', 'Jackson', 'scott.jackson@example.com', 'D2ACYhzD', '2024-01-26 03:00:00'),
(60, 'Ryan', 'Riley', 'ryan.riley@example.com', 'jWD9zWsk', '2020-06-01 03:00:00'),
(61, 'Jessica', 'Mora', 'jessica.mora@example.com', 'Du5skT9l', '2021-08-25 03:00:00'),
(62, 'Tony', 'Dunn', 'tony.dunn@example.com', 'y7ZsYUkP', '2023-02-07 03:00:00'),
(63, 'Nicole', 'Norris', 'nicole.norris@example.com', '87FaGIdC', '2023-10-22 03:00:00'),
(64, 'Joshua', 'Villarreal', 'joshua.villarreal@example.com', 'oEH2IEMm', '2021-03-11 03:00:00'),
(65, 'Kevin', 'Lozano', 'kevin.lozano@example.com', '3w1lXyH8', '2023-04-07 03:00:00'),
(66, 'Crystal', 'Johnson', 'crystal.johnson@example.com', '2VAGUzeq', '2024-04-13 03:00:00'),
(67, 'Marie', 'Schmidt', 'marie.schmidt@example.com', 'Zgz2cZlb', '2022-02-27 03:00:00'),
(68, 'Chelsea', 'Jones', 'chelsea.jones@example.com', 'U6znhNnP', '2022-06-17 03:00:00'),
(69, 'Cameron', 'Alexander', 'cameron.alexander@example.com', 'T5oyVJww', '2022-11-03 03:00:00'),
(70, 'Sherri', 'Johnson', 'sherri.johnson@example.com', 'X62KsWbw', '2020-10-05 03:00:00'),
(71, 'Sarah', 'Rodriguez', 'sarah.rodriguez@example.com', 'I3AmX2y3', '2021-11-09 03:00:00'),
(72, 'Joseph', 'Johnston', 'joseph.johnston@example.com', '3Bq4SEvg', '2020-04-10 03:00:00'),
(73, 'Nathan', 'Sanders', 'nathan.sanders@example.com', '5DgWHvvN', '2021-09-01 03:00:00'),
(74, 'Jessica', 'Vargas', 'jessica.vargas@example.com', 'x8IdfvDd', '2023-03-22 03:00:00'),
(75, 'Bryan', 'Cardenas', 'bryan.cardenas@example.com', '2HwT5CJm', '2024-09-05 03:00:00'),
(76, 'Edward', 'Strong', 'edward.strong@example.com', '6OHHhyx2', '2021-09-16 03:00:00'),
(77, 'Tracy', 'Vazquez', 'tracy.vazquez@example.com', 'KHNv0nDz', '2021-03-29 03:00:00'),
(78, 'Lee', 'Jennings', 'lee.jennings@example.com', 'i8M0QcKo', '2021-10-10 03:00:00'),
(79, 'Joshua', 'Berry', 'joshua.berry@example.com', 'n3CRWuEm', '2023-02-12 03:00:00'),
(80, 'Alexandria', 'Parker', 'alexandria.parker@example.com', '08rZZwkX', '2021-08-04 03:00:00'),
(81, 'Erin', 'Thompson', 'erin.thompson@example.com', 'hTex2Min', '2024-07-14 03:00:00'),
(82, 'Kevin', 'Bishop', 'kevin.bishop@example.com', 'm2LiHv0f', '2024-06-01 03:00:00'),
(83, 'Toni', 'Pineda', 'toni.pineda@example.com', 'H1IuCWu7', '2021-05-25 03:00:00'),
(84, 'Felicia', 'Miller', 'felicia.miller@example.com', 'qEH9ZkKb', '2022-05-15 03:00:00'),
(85, 'Angela', 'Weaver', 'angela.weaver@example.com', '1GdPkkOc', '2023-12-14 03:00:00'),
(86, 'Joseph', 'Clay', 'joseph.clay@example.com', '44NQfLgw', '2020-12-22 03:00:00'),
(87, 'Teresa', 'Moore', 'teresa.moore@example.com', '4yJMkksc', '2024-10-01 03:00:00'),
(88, 'Sean', 'Mckenzie', 'sean.mckenzie@example.com', 'ry3YTLFn', '2020-04-29 03:00:00'),
(89, 'Ashley', 'Jackson', 'ashley.jackson@example.com', 'tI1MTFZk', '2022-02-18 03:00:00'),
(90, 'George', 'Tucker', 'george.tucker@example.com', '09TS5HTj', '2020-06-13 03:00:00'),
(91, 'Melissa', 'Bailey', 'melissa.bailey@example.com', 's5YKAloA', '2022-01-07 03:00:00'),
(92, 'Erika', 'Gonzales', 'erika.gonzales@example.com', 'o1ZjBTPq', '2020-02-27 03:00:00'),
(93, 'Richard', 'Holmes', 'richard.holmes@example.com', 'Wlb9SEYe', '2023-10-03 03:00:00'),
(94, 'Colleen', 'Collier', 'colleen.collier@example.com', '7ZHLYfiq', '2022-07-07 03:00:00'),
(95, 'Rachael', 'Oliver', 'rachael.oliver@example.com', 'xE80HFfi', '2022-06-10 03:00:00'),
(96, 'Caitlin', 'Stout', 'caitlin.stout@example.com', '91h03KUr', '2023-12-19 03:00:00'),
(97, 'Katherine', 'Harding', 'katherine.harding@example.com', '4AWbDMhm', '2023-08-23 03:00:00'),
(98, 'Peter', 'Munoz', 'peter.munoz@example.com', 'v3KxLPlU', '2024-01-03 03:00:00'),
(99, 'Douglas', 'Bell', 'douglas.bell@example.com', '7k0H05Oq', '2020-06-16 03:00:00'),
(100, 'Kelly', 'Mckinney', 'kelly.mckinney@example.com', 'beT36Ndh', '2023-08-04 03:00:00'),
(101, 'James', 'Hill', 'james.hill@example.com', 'k4eLbzMf', '2021-03-17 03:00:00'),
(102, 'Brian', 'Crawford', 'brian.crawford@example.com', '3ABxVLUk', '2020-08-28 03:00:00'),
(103, 'Kelly', 'Booth', 'kelly.booth@example.com', 'qVz1PAHk', '2021-10-02 03:00:00'),
(104, 'Daniel', 'Singh', 'daniel.singh@example.com', 'u4XF6dhO', '2021-09-28 03:00:00'),
(105, 'Thomas', 'Williams', 'thomas.williams@example.com', 'A1PA0onX', '2022-10-29 03:00:00'),
(106, 'Cynthia', 'Golden', 'cynthia.golden@example.com', 'gdW39mHx', '2022-12-31 03:00:00'),
(107, 'Brandi', 'Jones', 'brandi.jones@example.com', '4RuTzdpU', '2020-12-29 03:00:00'),
(108, 'Melissa', 'Young', 'melissa.young@example.com', 'u63qXzZK', '2024-03-30 03:00:00'),
(109, 'Monica', 'Taylor', 'monica.taylor@example.com', 'f7O4c0ud', '2021-03-31 03:00:00'),
(110, 'Kimberly', 'Schwartz', 'kimberly.schwartz@example.com', 'a7eoBJtb', '2020-07-03 03:00:00'),
(111, 'Rhonda', 'Brandt', 'rhonda.brandt@example.com', 'i0BWKKXk', '2023-08-14 03:00:00'),
(112, 'Michael', 'Lee', 'michael.lee@example.com', 'g2iPN2a5', '2022-02-12 03:00:00'),
(113, 'Nicole', 'Martinez', 'nicole.martinez@example.com', 'B5uRCPEg', '2023-10-26 03:00:00'),
(114, 'Elizabeth', 'Evans', 'elizabeth.evans@example.com', '35uMeq8j', '2023-10-12 03:00:00'),
(115, 'Jasmine', 'Thomas', 'jasmine.thomas@example.com', 'GQ4Go8Wo', '2023-05-17 03:00:00'),
(116, 'Kimberly', 'Ferguson', 'kimberly.ferguson@example.com', '5q66BWf8', '2020-11-26 03:00:00'),
(117, 'Melanie', 'Ho', 'melanie.ho@example.com', 'tq3tHajd', '2020-07-19 03:00:00'),
(118, 'Albert', 'Ramirez', 'albert.ramirez@example.com', '1Xabe9an', '2022-04-02 03:00:00'),
(119, 'Kyle', 'Williams', 'kyle.williams@example.com', 'oz4N1GJu', '2020-09-25 03:00:00'),
(120, 'Yolanda', 'Ellis', 'yolanda.ellis@example.com', 'C4BLFxmn', '2023-08-11 03:00:00'),
(121, 'Austin', 'Merritt', 'austin.merritt@example.com', '5Ta2lIEf', '2020-10-13 03:00:00'),
(122, 'Nicholas', 'Kelley', 'nicholas.kelley@example.com', 'foFI3X1o', '2023-04-12 03:00:00'),
(123, 'Jeremy', 'Rivera', 'jeremy.rivera@example.com', '5ZFdmDuL', '2024-06-04 03:00:00'),
(124, 'Carl', 'Hood', 'carl.hood@example.com', '9oe1fIza', '2021-01-01 03:00:00'),
(125, 'Joseph', 'Hickman', 'joseph.hickman@example.com', 'je6iUIvf', '2023-03-01 03:00:00'),
(126, 'Mark', 'Chavez', 'mark.chavez@example.com', 'g2L2z5Li', '2021-02-04 03:00:00'),
(127, 'Lauren', 'Evans', 'lauren.evans@example.com', 'dc7TWuhT', '2020-02-16 03:00:00'),
(128, 'Tim', 'Miranda', 'tim.miranda@example.com', 'g9LXiKaE', '2020-11-26 03:00:00'),
(129, 'Joy', 'Romero', 'joy.romero@example.com', '3KOC79sR', '2022-01-24 03:00:00'),
(130, 'Elizabeth', 'Murphy', 'elizabeth.murphy@example.com', 'LZ2EmLPJ', '2024-05-09 03:00:00'),
(131, 'Daniel', 'Howard', 'daniel.howard@example.com', 'v3VEiwMu', '2023-06-12 03:00:00'),
(132, 'Zachary', 'Brown', 'zachary.brown@example.com', 'eaD5Tu4V', '2020-09-23 03:00:00'),
(133, 'Joshua', 'Hall', 'joshua.hall@example.com', 'MimqN0De', '2022-01-13 03:00:00'),
(134, 'Christopher', 'Bell', 'christopher.bell@example.com', '9sAahtlR', '2020-01-14 03:00:00'),
(135, 'Carrie', 'Miller', 'carrie.miller@example.com', 'dzC1WPbF', '2024-07-31 03:00:00'),
(136, 'Carol', 'Jefferson', 'carol.jefferson@example.com', 'yo60jTmw', '2024-04-17 03:00:00'),
(137, 'Lauren', 'Smith', 'lauren.smith@example.com', '5JpaEaj9', '2023-10-26 03:00:00'),
(138, 'Peter', 'Morse', 'peter.morse@example.com', 'x6GHpArn', '2021-12-25 03:00:00'),
(139, 'Jessica', 'Marshall', 'jessica.marshall@example.com', 'w0o98UEs', '2022-12-22 03:00:00'),
(140, 'Brandy', 'West', 'brandy.west@example.com', 'tHs24ZLi', '2023-07-08 03:00:00'),
(141, 'Traci', 'Washington', 'traci.washington@example.com', '3Wyk25F5', '2020-05-18 03:00:00'),
(142, 'Kimberly', 'Washington', 'kimberly.washington@example.com', '5GqcgqGY', '2023-08-10 03:00:00'),
(143, 'Seth', 'Kaiser', 'seth.kaiser@example.com', 'g7C73wwW', '2020-10-26 03:00:00'),
(144, 'Marissa', 'George', 'marissa.george@example.com', 'TD62Xyg9', '2020-11-18 03:00:00'),
(145, 'Mario', 'Sullivan', 'mario.sullivan@example.com', 'FCnG28Lh', '2020-03-11 03:00:00'),
(146, 'Elizabeth', 'Larson', 'elizabeth.larson@example.com', '8N1lzKpk', '2021-08-08 03:00:00'),
(147, 'Tina', 'Lewis', 'tina.lewis@example.com', 'eP5XBxdm', '2022-02-14 03:00:00'),
(148, 'Holly', 'Ray', 'holly.ray@example.com', '37KXEceJ', '2021-09-25 03:00:00'),
(149, 'Erica', 'Hall', 'erica.hall@example.com', '8sRpP3qW', '2023-10-10 03:00:00'),
(150, 'Kevin', 'Vasquez', 'kevin.vasquez@example.com', 'Q7ABXUDx', '2020-11-16 03:00:00'),
(151, 'John', 'Ray', 'john.ray@example.com', 'A0L4khgf', '2023-11-12 03:00:00'),
(152, 'Dennis', 'Wilson', 'dennis.wilson@example.com', '5TyvxGOj', '2020-03-24 03:00:00'),
(153, 'Christina', 'Green', 'christina.green@example.com', 'L5Aj8Cp7', '2020-07-16 03:00:00'),
(154, 'Jacqueline', 'Johnson', 'jacqueline.johnson@example.com', '7MUUPHii', '2021-05-23 03:00:00'),
(155, 'Vincent', 'Jones', 'vincent.jones@example.com', '99LqvcKz', '2022-02-07 03:00:00'),
(156, 'Priscilla', 'Obrien', 'priscilla.obrien@example.com', 'p9cHmen0', '2024-09-06 03:00:00'),
(157, 'Patricia', 'Boone', 'patricia.boone@example.com', '4lkDT7nu', '2023-11-15 03:00:00'),
(158, 'Andres', 'Daugherty', 'andres.daugherty@example.com', 't9ZXKsK8', '2022-08-01 03:00:00'),
(159, 'Rita', 'Fischer', 'rita.fischer@example.com', '6j4ZaUmm', '2020-03-31 03:00:00'),
(160, 'Valerie', 'Allen', 'valerie.allen@example.com', 'P44MiKff', '2022-08-10 03:00:00'),
(161, 'Melissa', 'Hall', 'melissa.hall@example.com', '4iHGsfUN', '2023-08-15 03:00:00'),
(162, 'Antonio', 'Caldwell', 'antonio.caldwell@example.com', '0DjOznJ9', '2020-03-30 03:00:00'),
(163, 'Larry', 'Bennett', 'larry.bennett@example.com', 'ZB4VJRkl', '2023-06-14 03:00:00'),
(164, 'Gloria', 'Gonzales', 'gloria.gonzales@example.com', 'GpQY4VTy', '2020-08-04 03:00:00'),
(165, 'Christine', 'Wilson', 'christine.wilson@example.com', '7NroZuVQ', '2022-05-16 03:00:00'),
(166, 'Steven', 'Fields', 'steven.fields@example.com', 'c5ulvJUq', '2024-05-30 03:00:00'),
(167, 'Jacob', 'Vasquez', 'jacob.vasquez@example.com', '3iQKgpei', '2022-01-12 03:00:00'),
(168, 'Michael', 'Phillips', 'michael.phillips@example.com', '6KEOp12n', '2024-06-08 03:00:00'),
(169, 'Steven', 'Taylor', 'steven.taylor@example.com', '0aNBg6fJ', '2020-03-13 03:00:00'),
(170, 'Angela', 'Lane', 'angela.lane@example.com', 'u5Ix1WyV', '2020-04-16 03:00:00'),
(171, 'Kelli', 'Kennedy', 'kelli.kennedy@example.com', '9VP9rcfL', '2021-06-11 03:00:00'),
(172, 'James', 'Cox', 'james.cox@example.com', '5vkE1uxt', '2024-08-07 03:00:00'),
(173, 'Logan', 'Martinez', 'logan.martinez@example.com', 'o4tO6IxB', '2023-12-25 03:00:00'),
(174, 'Anthony', 'Johnson', 'anthony.johnson@example.com', '2RbReusc', '2020-12-19 03:00:00'),
(175, 'Jesse', 'Cross', 'jesse.cross@example.com', 'Quqk2Zu5', '2020-01-09 03:00:00'),
(176, 'Nicholas', 'Miller', 'nicholas.miller@example.com', 'b85u4IQh', '2023-02-16 03:00:00'),
(177, 'Michelle', 'Wilson', 'michelle.wilson@example.com', 'DsT951Lg', '2021-05-06 03:00:00'),
(178, 'Lisa', 'Hunt', 'lisa.hunt@example.com', 'c965oNPh', '2022-02-16 03:00:00'),
(179, 'Melanie', 'Lopez', 'melanie.lopez@example.com', 'r7Qxi8Vv', '2021-01-09 03:00:00'),
(180, 'Jennifer', 'Villanueva', 'jennifer.villanueva@example.com', 'V7iEUeMn', '2020-04-29 03:00:00'),
(181, 'Robert', 'Reese', 'robert.reese@example.com', 'D3QPd43a', '2023-10-21 03:00:00'),
(182, 'Mercedes', 'Trujillo', 'mercedes.trujillo@example.com', 'j0h5WvvB', '2023-06-13 03:00:00'),
(183, 'Christina', 'Foley', 'christina.foley@example.com', '7XUe0uhN', '2021-12-04 03:00:00'),
(184, 'Tonya', 'Hogan', 'tonya.hogan@example.com', 'o7SRoswH', '2023-05-04 03:00:00'),
(185, 'Jessica', 'Bradley', 'jessica.bradley@example.com', 'q1VyFbVl', '2023-04-04 03:00:00'),
(186, 'Carmen', 'Davis', 'carmen.davis@example.com', '11DKYriG', '2023-01-12 03:00:00'),
(187, 'William', 'Brennan', 'william.brennan@example.com', '0PhgcuBN', '2020-06-07 03:00:00'),
(188, 'Megan', 'Hudson', 'megan.hudson@example.com', 'J1BTb7jX', '2020-08-31 03:00:00'),
(189, 'Margaret', 'Bell', 'margaret.bell@example.com', '35EIDxgg', '2022-08-09 03:00:00'),
(190, 'Amy', 'Hill', 'amy.hill@example.com', 'W6em2Ipe', '2024-10-11 03:00:00'),
(191, 'Steven', 'Yoder', 'steven.yoder@example.com', '9RcKQZ65', '2024-01-26 03:00:00'),
(192, 'Juan', 'Stewart', 'juan.stewart@example.com', 'NN61Vduo', '2022-04-17 03:00:00'),
(193, 'Natasha', 'Lee', 'natasha.lee@example.com', 'GlN87Yvk', '2024-09-17 03:00:00'),
(194, 'Jacob', 'Hernandez', 'jacob.hernandez@example.com', '7KBCe7qj', '2022-05-28 03:00:00'),
(195, 'Andrea', 'Randall', 'andrea.randall@example.com', 'hH02PEvr', '2023-08-14 03:00:00'),
(196, 'Tara', 'Vaughn', 'tara.vaughn@example.com', '1S6P0Oqi', '2020-02-23 03:00:00'),
(197, 'Mark', 'Fleming', 'mark.fleming@example.com', 'MZ7YnyiO', '2020-03-08 03:00:00'),
(198, 'Eileen', 'Green', 'eileen.green@example.com', 'qD1UT2p0', '2020-01-30 03:00:00'),
(199, 'Tricia', 'Conner', 'tricia.conner@example.com', '8PP3ALog', '2022-11-12 03:00:00'),
(200, 'Stephen', 'Griffin', 'stephen.griffin@example.com', 'o777qLuB', '2020-04-10 03:00:00'),
(201, 'Eric', 'Jones', 'eric.jones@example.com', 'T0mGgc2m', '2023-02-22 03:00:00'),
(202, 'Eugene', 'Luna', 'eugene.luna@example.com', '005JJ8ci', '2023-05-28 03:00:00'),
(203, 'Heather', 'Jones', 'heather.jones@example.com', '1VFWiesR', '2023-03-06 03:00:00'),
(204, 'Jason', 'Vaughan', 'jason.vaughan@example.com', '27UlQte7', '2021-12-27 03:00:00'),
(205, 'Alicia', 'Larson', 'alicia.larson@example.com', '9j4HCXxR', '2023-04-06 03:00:00'),
(206, 'Douglas', 'Anderson', 'douglas.anderson@example.com', '5VIxlSjw', '2021-06-21 03:00:00'),
(207, 'Mary', 'Miles', 'mary.miles@example.com', 'P6xX2yEa', '2020-05-14 03:00:00'),
(208, 'Stephanie', 'Grimes', 'stephanie.grimes@example.com', 'v8sf6Dbw', '2023-10-17 03:00:00'),
(209, 'Jason', 'Schmidt', 'jason.schmidt@example.com', '2or9jSyn', '2020-05-24 03:00:00'),
(210, 'James', 'Peters', 'james.peters@example.com', 'tapim0Qm', '2023-09-15 03:00:00'),
(211, 'Ryan', 'Turner', 'ryan.turner@example.com', 'L6fkM8ud', '2020-10-02 03:00:00'),
(212, 'John', 'Galvan', 'john.galvan@example.com', 'ngG01ZWn', '2022-09-12 03:00:00'),
(213, 'Denise', 'Garcia', 'denise.garcia@example.com', '6tePc3sk', '2023-08-12 03:00:00'),
(214, 'Scott', 'Hansen', 'scott.hansen@example.com', 'L9OKLAz3', '2023-01-18 03:00:00'),
(215, 'Tina', 'Wright', 'tina.wright@example.com', 'I9KoJEuF', '2023-10-29 03:00:00'),
(216, 'Shannon', 'Campbell', 'shannon.campbell@example.com', 'IZU6ABsk', '2020-10-10 03:00:00'),
(217, 'Adam', 'Morgan', 'adam.morgan@example.com', 'C2cOqJGB', '2024-06-27 03:00:00'),
(218, 'Benjamin', 'Jennings', 'benjamin.jennings@example.com', 'YJ7yGTsU', '2024-11-11 03:00:00'),
(219, 'Nathan', 'Vaughn', 'nathan.vaughn@example.com', '3EYnZa5l', '2020-07-12 03:00:00'),
(220, 'Joshua', 'Steele', 'joshua.steele@example.com', '6FBAZHq5', '2023-11-13 03:00:00');




--
-- Dumping data for table `jugador`
--

INSERT INTO `jugador` (`id_jugador`, `id_usuario`, `id_equipo`, `posicion`, `numero_camiseta`, `fecha_creacion`) VALUES
(1, 1, 1, 'Delantero', 10, '2024-09-30 03:00:00'),
(2, 2, 2, 'Mediocampista', 8, '2024-09-30 03:00:00'),
(3, 3, 11, 'Defensor', 5, '2024-09-30 03:00:00'),
(4, 4, 12, 'Portero', 1, '2024-09-30 03:00:00'),
(5, 5, 21, 'Delantero', 9, '2024-09-30 03:00:00'),
(6, 6, 22, 'Mediocampista', 7, '2024-09-30 03:00:00'),
(7, 7, 7, 'Defensor', 6, '2024-09-30 03:00:00'),
(8, 8, 8, 'Portero', 2, '2024-09-30 03:00:00'),
(9, 9, 9, 'Delantero', 11, '2024-09-30 03:00:00'),
(10, 10, 10, 'Mediocampista', 3, '2024-09-30 03:00:00'),
(11, 11, 1, 'Defensor', 4, '2024-09-30 03:00:00'),
(12, 12, 2, 'Portero', 12, '2024-09-30 03:00:00'),
(13, 13, 11, 'Delantero', 14, '2024-09-30 03:00:00'),
(14, 14, 12, 'Mediocampista', 15, '2024-09-30 03:00:00'),
(15, 15, 21, 'Defensor', 13, '2024-09-30 03:00:00'),
(16, 16, 22, 'Portero', 16, '2024-09-30 03:00:00'),
(17, 17, 7, 'Delantero', 17, '2024-09-30 03:00:00'),
(18, 18, 8, 'Mediocampista', 19, '2024-09-30 03:00:00'),
(19, 19, 9, 'Defensor', 20, '2024-09-30 03:00:00'),
(20, 20, 10, 'Portero', 21, '2024-09-30 03:00:00'),
(21, 21, 1, 'Delantero', 22, '2024-09-30 03:00:00'),
(22, 22, 2, 'Mediocampista', 23, '2024-09-30 03:00:00'),
(23, 23, 11, 'Defensor', 24, '2024-09-30 03:00:00'),
(24, 24, 12, 'Portero', 25, '2024-09-30 03:00:00'),
(25, 25, 21, 'Delantero', 26, '2024-09-30 03:00:00'),
(26, 26, 22, 'Mediocampista', 27, '2024-09-30 03:00:00'),
(27, 27, 7, 'Defensor', 28, '2024-09-30 03:00:00'),
(28, 28, 8, 'Portero', 29, '2024-09-30 03:00:00'),
(29, 29, 9, 'Delantero', 30, '2024-09-30 03:00:00'),
(30, 30, 10, 'Mediocampista', 31, '2024-09-30 03:00:00'),
(31, 31, 1, 'Defensor', 32, '2024-09-30 03:00:00'),
(32, 32, 2, 'Portero', 33, '2024-09-30 03:00:00'),
(33, 33, 11, 'Delantero', 34, '2024-09-30 03:00:00'),
(34, 34, 12, 'Mediocampista', 35, '2024-09-30 03:00:00'),
(35, 35, 21, 'Defensor', 36, '2024-09-30 03:00:00'),
(36, 36, 22, 'Portero', 37, '2024-09-30 03:00:00'),
(37, 37, 7, 'Delantero', 38, '2024-09-30 03:00:00'),
(38, 38, 8, 'Mediocampista', 39, '2024-09-30 03:00:00'),
(39, 39, 9, 'Defensor', 40, '2024-09-30 03:00:00'),
(40, 40, 10, 'Portero', 41, '2024-09-30 03:00:00'),
(41, 41, 1, 'Delantero', 42, '2024-09-30 03:00:00'),
(42, 42, 2, 'Mediocampista', 43, '2024-09-30 03:00:00'),
(43, 43, 11, 'Defensor', 44, '2024-09-30 03:00:00'),
(44, 44, 12, 'Portero', 45, '2024-09-30 03:00:00'),
(45, 45, 21, 'Delantero', 46, '2024-09-30 03:00:00'),
(46, 46, 22, 'Mediocampista', 47, '2024-09-30 03:00:00'),
(47, 47, 7, 'Defensor', 48, '2024-09-30 03:00:00'),
(48, 48, 8, 'Portero', 49, '2024-09-30 03:00:00'),
(49, 49, 9, 'Delantero', 50, '2024-09-30 03:00:00'),
(50, 50, 10, 'Mediocampista', 51, '2024-09-30 03:00:00'),
(51, 51, 1, 'Defensor', 52, '2024-09-30 03:00:00'),
(52, 52, 2, 'Portero', 53, '2024-09-30 03:00:00'),
(53, 53, 11, 'Delantero', 54, '2024-09-30 03:00:00'),
(54, 54, 12, 'Mediocampista', 55, '2024-09-30 03:00:00'),
(55, 55, 21, 'Defensor', 56, '2024-09-30 03:00:00'),
(56, 56, 22, 'Portero', 57, '2024-09-30 03:00:00'),
(57, 57, 7, 'Delantero', 58, '2024-09-30 03:00:00'),
(58, 58, 8, 'Mediocampista', 59, '2024-09-30 03:00:00'),
(59, 59, 9, 'Defensor', 60, '2024-09-30 03:00:00'),
(60, 60, 10, 'Portero', 61, '2024-09-30 03:00:00'),
(61, 61, 1, 'Delantero', 62, '2024-09-30 03:00:00'),
(62, 62, 2, 'Mediocampista', 63, '2024-09-30 03:00:00'),
(63, 63, 11, 'Defensor', 64, '2024-09-30 03:00:00'),
(64, 64, 12, 'Portero', 65, '2024-09-30 03:00:00'),
(65, 65, 21, 'Delantero', 66, '2024-09-30 03:00:00'),
(66, 66, 22, 'Mediocampista', 67, '2024-09-30 03:00:00'),
(67, 67, 7, 'Defensor', 68, '2024-09-30 03:00:00'),
(68, 68, 8, 'Portero', 69, '2024-09-30 03:00:00'),
(69, 69, 9, 'Delantero', 70, '2024-09-30 03:00:00'),
(70, 70, 10, 'Mediocampista', 71, '2024-09-30 03:00:00'),
(71, 71, 1, 'Defensor', 72, '2024-09-30 03:00:00'),
(72, 72, 2, 'Portero', 73, '2024-09-30 03:00:00'),
(73, 73, 11, 'Delantero', 74, '2024-09-30 03:00:00'),
(74, 74, 12, 'Mediocampista', 75, '2024-09-30 03:00:00'),
(75, 75, 21, 'Defensor', 76, '2024-09-30 03:00:00'),
(76, 76, 22, 'Portero', 77, '2024-09-30 03:00:00'),
(77, 77, 7, 'Delantero', 78, '2024-09-30 03:00:00'),
(78, 78, 8, 'Mediocampista', 79, '2024-09-30 03:00:00'),
(79, 79, 9, 'Defensor', 80, '2024-09-30 03:00:00'),
(80, 80, 10, 'Portero', 81, '2024-09-30 03:00:00'),
(81, 81, 1, 'Delantero', 82, '2024-09-30 03:00:00'),
(82, 82, 2, 'Mediocampista', 83, '2024-09-30 03:00:00'),
(83, 83, 11, 'Defensor', 84, '2024-09-30 03:00:00'),
(84, 84, 12, 'Portero', 85, '2024-09-30 03:00:00'),
(85, 85, 21, 'Delantero', 86, '2024-09-30 03:00:00'),
(86, 86, 22, 'Mediocampista', 87, '2024-09-30 03:00:00'),
(87, 87, 7, 'Defensor', 88, '2024-09-30 03:00:00'),
(88, 88, 8, 'Portero', 89, '2024-09-30 03:00:00'),
(89, 89, 9, 'Delantero', 90, '2024-09-30 03:00:00'),
(90, 90, 10, 'Mediocampista', 91, '2024-09-30 03:00:00'),
(91, 91, 1, 'Defensor', 92, '2024-09-30 03:00:00'),
(92, 92, 2, 'Portero', 93, '2024-09-30 03:00:00'),
(93, 93, 11, 'Delantero', 94, '2024-09-30 03:00:00'),
(94, 94, 12, 'Mediocampista', 95, '2024-09-30 03:00:00'),
(95, 95, 21, 'Defensor', 96, '2024-09-30 03:00:00'),
(96, 96, 22, 'Portero', 97, '2024-09-30 03:00:00'),
(97, 97, 7, 'Delantero', 98, '2024-09-30 03:00:00'),
(98, 98, 8, 'Mediocampista', 99, '2024-09-30 03:00:00'),
(99, 99, 9, 'Defensor', 100, '2024-09-30 03:00:00'),
(100, 100, 10, 'Portero', 101, '2024-09-30 03:00:00'),
(101, 101, 1, 'Delantero', 102, '2024-09-30 03:00:00'),
(102, 102, 2, 'Mediocampista', 103, '2024-09-30 03:00:00'),
(103, 103, 11, 'Defensor', 104, '2024-09-30 03:00:00'),
(104, 104, 12, 'Portero', 105, '2024-09-30 03:00:00'),
(105, 105, 21, 'Delantero', 106, '2024-09-30 03:00:00'),
(106, 106, 22, 'Mediocampista', 107, '2024-09-30 03:00:00'),
(107, 107, 7, 'Defensor', 108, '2024-09-30 03:00:00'),
(108, 108, 8, 'Portero', 109, '2024-09-30 03:00:00'),
(109, 109, 9, 'Delantero', 110, '2024-09-30 03:00:00'),
(110, 110, 10, 'Mediocampista', 111, '2024-09-30 03:00:00'),
(111, 111, 1, 'Defensor', 112, '2024-09-30 03:00:00'),
(112, 112, 2, 'Portero', 113, '2024-09-30 03:00:00'),
(113, 113, 11, 'Delantero', 114, '2024-09-30 03:00:00'),
(114, 114, 12, 'Mediocampista', 115, '2024-09-30 03:00:00'),
(115, 115, 21, 'Defensor', 116, '2024-09-30 03:00:00'),
(116, 116, 22, 'Portero', 117, '2024-09-30 03:00:00'),
(117, 117, 7, 'Delantero', 118, '2024-09-30 03:00:00'),
(118, 118, 8, 'Mediocampista', 119, '2024-09-30 03:00:00'),
(119, 119, 9, 'Defensor', 120, '2024-09-30 03:00:00'),
(120, 120, 10, 'Portero', 121, '2024-09-30 03:00:00'),
(121, 121, 1, 'Delantero', 122, '2024-09-30 03:00:00'),
(122, 122, 2, 'Mediocampista', 123, '2024-09-30 03:00:00'),
(123, 123, 11, 'Defensor', 124, '2024-09-30 03:00:00'),
(124, 124, 12, 'Portero', 125, '2024-09-30 03:00:00'),
(125, 125, 21, 'Delantero', 126, '2024-09-30 03:00:00'),
(126, 126, 22, 'Mediocampista', 127, '2024-09-30 03:00:00'),
(127, 127, 7, 'Defensor', 128, '2024-09-30 03:00:00'),
(128, 128, 8, 'Portero', 129, '2024-09-30 03:00:00'),
(129, 129, 9, 'Delantero', 130, '2024-09-30 03:00:00'),
(130, 130, 10, 'Mediocampista', 131, '2024-09-30 03:00:00'),
(131, 131, 1, 'Defensor', 132, '2024-09-30 03:00:00'),
(132, 132, 2, 'Portero', 133, '2024-09-30 03:00:00'),
(133, 133, 11, 'Delantero', 134, '2024-09-30 03:00:00'),
(134, 134, 12, 'Mediocampista', 135, '2024-09-30 03:00:00'),
(135, 135, 21, 'Defensor', 136, '2024-09-30 03:00:00'),
(136, 136, 22, 'Portero', 137, '2024-09-30 03:00:00'),
(137, 137, 7, 'Delantero', 138, '2024-09-30 03:00:00'),
(138, 138, 8, 'Mediocampista', 139, '2024-09-30 03:00:00'),
(139, 139, 9, 'Defensor', 140, '2024-09-30 03:00:00'),
(140, 140, 10, 'Portero', 141, '2024-09-30 03:00:00'),
(141, 141, 1, 'Delantero', 142, '2024-09-30 03:00:00'),
(142, 142, 2, 'Mediocampista', 143, '2024-09-30 03:00:00'),
(143, 143, 11, 'Defensor', 144, '2024-09-30 03:00:00'),
(144, 144, 12, 'Portero', 145, '2024-09-30 03:00:00'),
(145, 145, 21, 'Delantero', 146, '2024-09-30 03:00:00'),
(146, 146, 22, 'Mediocampista', 147, '2024-09-30 03:00:00'),
(147, 147, 7, 'Defensor', 148, '2024-09-30 03:00:00'),
(148, 148, 8, 'Portero', 149, '2024-09-30 03:00:00'),
(149, 149, 9, 'Delantero', 150, '2024-09-30 03:00:00'),
(150, 150, 10, 'Mediocampista', 151, '2024-09-30 03:00:00'),
(151, 151, 1, 'Defensor', 152, '2024-09-30 03:00:00'),
(152, 152, 2, 'Portero', 153, '2024-09-30 03:00:00'),
(153, 153, 11, 'Delantero', 154, '2024-09-30 03:00:00'),
(154, 154, 12, 'Mediocampista', 155, '2024-09-30 03:00:00'),
(155, 155, 21, 'Defensor', 156, '2024-09-30 03:00:00'),
(156, 156, 22, 'Portero', 157, '2024-09-30 03:00:00'),
(157, 157, 7, 'Delantero', 158, '2024-09-30 03:00:00'),
(158, 158, 8, 'Mediocampista', 159, '2024-09-30 03:00:00'),
(159, 159, 9, 'Defensor', 160, '2024-09-30 03:00:00'),
(160, 160, 10, 'Portero', 161, '2024-09-30 03:00:00'),
(161, 161, 1, 'Delantero', 162, '2024-09-30 03:00:00'),
(162, 162, 2, 'Mediocampista', 163, '2024-09-30 03:00:00'),
(163, 163, 11, 'Defensor', 164, '2024-09-30 03:00:00'),
(164, 164, 12, 'Portero', 165, '2024-09-30 03:00:00'),
(165, 165, 21, 'Delantero', 166, '2024-09-30 03:00:00'),
(166, 166, 22, 'Mediocampista', 167, '2024-09-30 03:00:00'),
(167, 167, 7, 'Defensor', 168, '2024-09-30 03:00:00'),
(168, 168, 8, 'Portero', 169, '2024-09-30 03:00:00'),
(169, 169, 9, 'Delantero', 170, '2024-09-30 03:00:00'),
(170, 170, 10, 'Mediocampista', 171, '2024-09-30 03:00:00'),
(171, 171, 1, 'Defensor', 172, '2024-09-30 03:00:00'),
(172, 172, 2, 'Portero', 173, '2024-09-30 03:00:00'),
(173, 173, 11, 'Delantero', 174, '2024-09-30 03:00:00'),
(174, 174, 12, 'Mediocampista', 175, '2024-09-30 03:00:00'),
(175, 175, 21, 'Defensor', 176, '2024-09-30 03:00:00'),
(176, 176, 22, 'Portero', 177, '2024-09-30 03:00:00'),
(177, 177, 7, 'Delantero', 178, '2024-09-30 03:00:00'),
(178, 178, 8, 'Mediocampista', 179, '2024-09-30 03:00:00'),
(179, 179, 9, 'Defensor', 180, '2024-09-30 03:00:00'),
(180, 180, 10, 'Portero', 181, '2024-09-30 03:00:00'),
(181, 181, 1, 'Delantero', 182, '2024-09-30 03:00:00'),
(182, 182, 2, 'Mediocampista', 183, '2024-09-30 03:00:00'),
(183, 183, 11, 'Defensor', 184, '2024-09-30 03:00:00'),
(184, 184, 12, 'Portero', 185, '2024-09-30 03:00:00'),
(185, 185, 21, 'Delantero', 186, '2024-09-30 03:00:00'),
(186, 186, 22, 'Mediocampista', 187, '2024-09-30 03:00:00'),
(187, 187, 7, 'Defensor', 188, '2024-09-30 03:00:00'),
(188, 188, 8, 'Portero', 189, '2024-09-30 03:00:00'),
(189, 189, 9, 'Delantero', 190, '2024-09-30 03:00:00'),
(190, 190, 10, 'Mediocampista', 191, '2024-09-30 03:00:00'),
(191, 191, 1, 'Defensor', 192, '2024-09-30 03:00:00'),
(192, 192, 2, 'Portero', 193, '2024-09-30 03:00:00'),
(193, 193, 11, 'Delantero', 194, '2024-09-30 03:00:00'),
(194, 194, 12, 'Mediocampista', 195, '2024-09-30 03:00:00'),
(195, 195, 21, 'Defensor', 196, '2024-09-30 03:00:00'),
(196, 196, 22, 'Portero', 197, '2024-09-30 03:00:00'),
(197, 197, 7, 'Delantero', 198, '2024-09-30 03:00:00'),
(198, 198, 8, 'Mediocampista', 199, '2024-09-30 03:00:00'),
(199, 199, 9, 'Defensor', 200, '2024-09-30 03:00:00'),
(200, 200, 10, 'Portero', 201, '2024-09-30 03:00:00');



--
-- Dumping data for table `rol`
--

INSERT INTO `rol` (`id_rol`, `nombre_rol`, `descripcion`, `fecha_creacion`) VALUES
(1, 'Jugador', 'Tiene permisos limitados, acceso a estadisticas generales de su torneo', '2024-11-18 03:00:00'),
(2, 'Arbitro', 'Tiene permisos limitados, acceso a estadisticas generales de su torneo', '2024-11-18 03:00:00'),
(3, 'Personal Organizativo', 'Acceso a estadisticas de su propio torneo, ademas de poder administrarlo y tambien a sus partidos ', '2024-11-18 03:00:00'),
(4, 'Administrador', 'Tiene control absoluto, modera y administra la aplicacion', '2024-11-18 03:00:00');




--
-- Dumping data for table `permiso`
--

INSERT INTO `permiso` (`id_permiso`, `nombre_permiso`, `descripcion`, `fecha_creacion`) VALUES
(1, 'Ver estadísticas', 'Permite acceder a estadísticas generales del torneo.', '2023-03-02 03:00:00'),
(2, 'Administrar torneo', 'Permite gestionar el torneo y sus partidos.', '2022-02-15 03:00:00'),
(3, 'Administrar aplicación', 'Permite realizar tareas de administración global en la aplicación.', '2020-07-20 03:00:00'),
(4, 'Modificar partidos', 'Permite editar la información de partidos en el torneo.', '2023-09-26 03:00:00'),
(5, 'Ver estadísticas ampliadas', 'Permite ver estadísticas específicas y detalladas del torneo.', '2023-03-02 03:00:00');






--
-- Dumping data for table `role_permiso`
--

INSERT INTO `role_permiso` (`id_rol`, `id_permiso`) VALUES
(1, 1),
(2, 1),
(3, 1),
(3, 2),
(3, 4),
(4, 1),
(4, 2),
(4, 3),
(4, 4),
(4, 5);




--
-- Dumping data for table `usuario_permiso`
--

INSERT INTO `usuario_permiso` (`id_usuario`, `id_permiso`) VALUES
(1, 1),
(2, 1),
(3, 2),
(4, 3),
(4, 5);

--
-- Dumping data for table `usuario_role`
--

INSERT INTO `usuario_role` (`id_usuario`, `id_rol`) VALUES
(1, 1),
(2, 2),
(3, 3),
(4, 4),
(5, 3);
COMMIT;





--
-- Dumping data for table `partido`
--

INSERT INTO `partido` (`id_partido`, `id_torneo`, `equipo_local`, `equipo_visitante`, `fecha_partido`, `goles_local`, `goles_visitante`, `estado`, `fecha_creacion`) VALUES
(1, 1, 1, 2, '2024-10-20 16:00:00', 2, 1, '', '2024-11-18 03:00:00'),
(2, 1, 11, 12, '2024-10-21 18:00:00', 1, 0, '', '2024-11-18 03:00:00'),
(3, 1, 21, 22, '2024-10-22 14:30:00', 3, 2, '', '2024-11-18 03:00:00'),
(4, 1, 1, 11, '2024-10-23 19:00:00', 0, 0, 'pendiente', '2024-11-18 03:00:00'),
(5, 1, 1, 12, '2024-10-24 15:00:00', 0, 0, 'pendiente', '2024-11-18 03:00:00'),
(6, 1, 2, 21, '2024-10-25 13:00:00', 0, 0, 'pendiente', '2024-11-18 03:00:00'),
(7, 1, 2, 22, '2024-10-26 17:00:00', 0, 0, 'pendiente', '2024-11-18 03:00:00'),
(8, 1, 11, 21, '2024-10-27 12:00:00', 0, 0, 'pendiente', '2024-11-18 03:00:00'),
(9, 1, 12, 22, '2024-10-28 20:00:00', 0, 0, 'pendiente', '2024-11-18 03:00:00');



--
-- Dumping data for table `estadistica`
--

INSERT INTO `estadistica` (`id_estadistica`, `id_jugador`, `id_partido`, `goles`, `asistencias`, `tarjetas_amarillas`, `tarjetas_rojas`, `minutos_jugados`, `fecha_creacion`) VALUES
(1, 1, 1, 1, 0, 1, 0, 90, '2024-11-18 03:00:00'),
(2, 11, 1, 0, 1, 0, 0, 90, '2024-11-18 03:00:00'),
(3, 21, 1, 0, 0, 0, 0, 90, '2024-11-18 03:00:00'),
(4, 31, 1, 0, 0, 1, 0, 90, '2024-11-18 03:00:00'),
(5, 41, 1, 1, 1, 0, 0, 90, '2024-11-18 03:00:00'),
(6, 51, 1, 0, 0, 0, 0, 90, '2024-11-18 03:00:00'),
(7, 2, 1, 0, 1, 0, 0, 90, '2024-11-18 03:00:00'),
(8, 12, 1, 1, 0, 0, 0, 90, '2024-11-18 03:00:00'),
(9, 22, 1, 0, 0, 1, 0, 90, '2024-11-18 03:00:00'),
(10, 32, 1, 0, 0, 0, 0, 90, '2024-11-18 03:00:00'),
(11, 42, 1, 0, 0, 0, 0, 90, '2024-11-18 03:00:00'),
(12, 52, 1, 0, 0, 0, 0, 90, '2024-11-18 03:00:00'),
(13, 3, 2, 0, 0, 0, 0, 90, '2024-11-18 03:00:00'),
(14, 13, 2, 1, 0, 0, 0, 90, '2024-11-18 03:00:00'),
(15, 23, 2, 0, 1, 0, 0, 90, '2024-11-18 03:00:00'),
(16, 33, 2, 0, 0, 0, 0, 90, '2024-11-18 03:00:00'),
(17, 43, 2, 0, 0, 1, 0, 90, '2024-11-18 03:00:00'),
(18, 53, 2, 0, 0, 0, 0, 90, '2024-11-18 03:00:00'),
(19, 4, 2, 0, 0, 0, 0, 90, '2024-11-18 03:00:00'),
(20, 14, 2, 0, 0, 1, 0, 90, '2024-11-18 03:00:00'),
(21, 24, 2, 0, 0, 0, 0, 90, '2024-11-18 03:00:00'),
(22, 34, 2, 0, 1, 0, 0, 90, '2024-11-18 03:00:00'),
(23, 44, 2, 0, 0, 0, 0, 90, '2024-11-18 03:00:00'),
(24, 54, 2, 0, 0, 0, 0, 90, '2024-11-18 03:00:00'),
(25, 5, 3, 1, 0, 0, 0, 90, '2024-11-18 03:00:00'),
(26, 15, 3, 0, 1, 0, 0, 90, '2024-11-18 03:00:00'),
(27, 25, 3, 1, 0, 1, 0, 90, '2024-11-18 03:00:00'),
(28, 35, 3, 0, 0, 0, 0, 90, '2024-11-18 03:00:00'),
(29, 45, 3, 0, 0, 0, 0, 90, '2024-11-18 03:00:00'),
(30, 55, 3, 0, 0, 0, 0, 90, '2024-11-18 03:00:00'),
(31, 6, 3, 0, 0, 1, 0, 90, '2024-11-18 03:00:00'),
(32, 16, 3, 1, 0, 0, 0, 90, '2024-11-18 03:00:00'),
(33, 26, 3, 0, 1, 0, 0, 90, '2024-11-18 03:00:00'),
(34, 36, 3, 0, 0, 0, 0, 90, '2024-11-18 03:00:00'),
(35, 46, 3, 0, 0, 0, 0, 90, '2024-11-18 03:00:00'),
(36, 56, 3, 0, 0, 0, 0, 90, '2024-11-18 03:00:00');



--
-- Dumping data for table `tipo_incidencia`
--

INSERT INTO `tipo_incidencia` (`id_tipo_incidencia`, `tipo_incidencia`) VALUES
(1, 'Gol'),
(2, 'Asistencia'),
(3, 'Tarjeta Amarilla'),
(4, 'Tarjeta Roja | Expulsion'),
(5, ''),
(6, ''),
(7, '');



--
-- Dumping data for table `incidencia`
--

INSERT INTO `incidencia` (`id_incidencia`, `minuto`, `id_partido`, `id_tipo_incidencia`, `id_jugador`) VALUES
(1, 12, 1, 1, 1),
(2, 14, 1, 2, 11),
(3, 35, 1, 3, 31),
(4, 42, 1, 1, 41),
(5, 43, 1, 2, 41),
(6, 75, 1, 3, 22),
(7, 18, 2, 1, 13),
(8, 20, 2, 2, 23),
(9, 47, 2, 3, 43),
(10, 50, 2, 3, 14),
(11, 60, 2, 2, 34),
(12, 85, 3, 1, 5),
(13, 87, 3, 2, 15),
(14, 72, 3, 3, 25),
(15, 75, 3, 1, 16),
(16, 78, 3, 4, 6);






/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

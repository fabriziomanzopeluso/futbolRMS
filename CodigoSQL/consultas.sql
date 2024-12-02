--1) Saber el fixture del equipo (Águilas de Oro)
SELECT 
    p.fecha_partido,
    p.estado,
    p.goles_local,
    p.goles_visitante,
    CASE 
        WHEN p.equipo_local = eq.id_equipo THEN 'Local'
        WHEN p.equipo_visitante = eq.id_equipo THEN 'Visitante'
    END AS tipo_partido,
    CASE 
        WHEN p.equipo_local = eq.id_equipo THEN e_visitante.nombre
        WHEN p.equipo_visitante = eq.id_equipo THEN e_local.nombre
    END AS rival
FROM 
    Partido p
JOIN 
    Equipo eq ON (p.equipo_local = eq.id_equipo OR p.equipo_visitante = eq.id_equipo)
JOIN 
    Equipo e_local ON p.equipo_local = e_local.id_equipo
JOIN 
    Equipo e_visitante ON p.equipo_visitante = e_visitante.id_equipo
WHERE 
    eq.nombre = 'Leones de la Ciudad'
ORDER BY 
    p.fecha_partido;





--2) Saber tabla de goleadores
SELECT  
    u.nombre AS nombre,
    u.apellido AS apellido,
    eq.nombre AS equipo,
    j.posicion,
    SUM(e.goles) AS GOLES
FROM 
    Jugador j
JOIN 
    Estadistica e
ON 
    j.id_jugador = e.id_jugador
JOIN
    Usuario u
ON
    j.id_usuario = u.id_usuario
JOIN
    Equipo eq
ON
    j.id_equipo = eq.id_equipo
GROUP BY 
    u.nombre, 
    u.apellido, 
    eq.nombre, 
    j.posicion, 
    j.numero_camiseta
ORDER BY 
    GOLES DESC;





--3) Saber cuál es el jugador que más partidos jugó
SELECT 
    u.nombre,
    u.apellido, 
    COUNT(e.id_partido) AS total_partidos
FROM 
    Estadistica e
JOIN 
    Jugador j ON e.id_jugador = j.id_jugador
JOIN 
    Usuario u ON j.id_usuario = u.id_usuario
GROUP BY 
    u.nombre, u.apellido
ORDER BY 
    total_partidos DESC
LIMIT 1;







--4) Saber la tabla del fair play: Saber los equipos con menos amarillas y rojas
SELECT 
    eq.nombre AS equipo,
    (SUM(es.tarjetas_amarillas) * 1 + SUM(es.tarjetas_rojas) * 2) AS puntaje_tarjetas
FROM 
    Estadistica es
JOIN 
    Jugador j ON es.id_jugador = j.id_jugador
JOIN 
    Equipo eq ON j.id_equipo = eq.id_equipo
GROUP BY 
    eq.id_equipo, eq.nombre
ORDER BY 
    puntaje_tarjetas ASC;



--5) Saber la tabla de posiciones
SELECT 
    RANK() OVER (
        ORDER BY 
            SUM(CASE 
                    WHEN (p.equipo_local = eq.id_equipo AND p.goles_local > p.goles_visitante) OR 
                         (p.equipo_visitante = eq.id_equipo AND p.goles_visitante > p.goles_local)
                    THEN 3
                    WHEN (p.equipo_local = eq.id_equipo AND p.goles_local = p.goles_visitante) OR 
                         (p.equipo_visitante = eq.id_equipo AND p.goles_visitante = p.goles_local)
                    THEN 1
                    ELSE 0
                END) DESC, 
            SUM(CASE 
                    WHEN p.equipo_local = eq.id_equipo THEN p.goles_local
                    WHEN p.equipo_visitante = eq.id_equipo THEN p.goles_visitante
                    ELSE 0
                END) - 
            SUM(CASE 
                    WHEN p.equipo_local = eq.id_equipo THEN p.goles_visitante
                    WHEN p.equipo_visitante = eq.id_equipo THEN p.goles_local
                    ELSE 0
                END) DESC, 
            SUM(CASE 
                    WHEN p.equipo_local = eq.id_equipo THEN p.goles_local
                    WHEN p.equipo_visitante = eq.id_equipo THEN p.goles_visitante
                    ELSE 0
                END) DESC
    ) AS posicion,
    eq.nombre AS nombre_equipo,
    SUM(CASE 
            WHEN (p.equipo_local = eq.id_equipo AND p.goles_local > p.goles_visitante) OR 
                 (p.equipo_visitante = eq.id_equipo AND p.goles_visitante > p.goles_local)
            THEN 3
            WHEN (p.equipo_local = eq.id_equipo AND p.goles_local = p.goles_visitante) OR 
                 (p.equipo_visitante = eq.id_equipo AND p.goles_visitante = p.goles_local)
            THEN 1
            ELSE 0
        END) AS puntos,
    SUM(CASE 
            WHEN p.equipo_local = eq.id_equipo THEN p.goles_local
            WHEN p.equipo_visitante = eq.id_equipo THEN p.goles_visitante
            ELSE 0
        END) AS goles_a_favor,
    SUM(CASE 
            WHEN p.equipo_local = eq.id_equipo THEN p.goles_visitante
            WHEN p.equipo_visitante = eq.id_equipo THEN p.goles_local
            ELSE 0
        END) AS goles_en_contra,
    SUM(CASE 
            WHEN p.equipo_local = eq.id_equipo THEN p.goles_local - p.goles_visitante
            WHEN p.equipo_visitante = eq.id_equipo THEN p.goles_visitante - p.goles_local
            ELSE 0
        END) AS diferencia_gol
FROM 
    Equipo eq
LEFT JOIN 
    Partido p ON eq.id_equipo = p.equipo_local OR eq.id_equipo = p.equipo_visitante
WHERE 
    p.estado NOT IN ('cancelado', 'pendiente')
GROUP BY 
    eq.id_equipo, eq.nombre
ORDER BY 
    posicion;


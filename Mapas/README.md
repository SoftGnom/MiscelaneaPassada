# Estructura de Datos y Algoritmos - BallTree y Grafos

Este proyecto implementa estructuras de datos avanzadas y algoritmos de búsqueda eficiente, incluyendo BallTree para la búsqueda de puntos cercanos y Grafos para el cálculo de caminos óptimos.

## Estructura del Proyecto

### Principales Clases y Archivos

   - BallTree.h / BallTree.cpp: Implementación de la estructura de datos BallTree para optimizar la búsqueda de vecinos cercanos en un espacio bidimensional.

   - GrafSolucio.h / GrafSolucio.cpp: Implementación de un grafo dirigido con el algoritmo de Dijkstra para encontrar caminos más cortos.

   - MapaBase.h / MapaSolucio.h: Clases para representar un mapa con puntos de interés y caminos.

   - CamiBase.h / CamiSolucio.h / CamiSolucio.cpp: Representación y manipulación de caminos dentro del mapa.

   - ClasseCami.h: Métodos auxiliares para la clasificación de caminos en el mapa.

   - Common.h: Definiciones de estructuras y tipos de datos utilizados en el proyecto.

   - AvaluadorBallTree.h: Implementación de una plantilla para evaluar la estructura BallTree.

   - PuntDeInteresBase.h / PuntDeInteresBase.cpp: Definición e implementación de puntos de interés generales.

   - PuntDeInteresBotigaSolucio.h: Extensión de puntos de interés específicos para tiendas.

   - PuntDeInteresRestaurantSolucio.h: Extensión de puntos de interés específicos para restaurantes.

   - Util.h / Util.cpp: Funciones auxiliares para cálculos matemáticos y operaciones sobre coordenadas geográficas.

   - XML4OSMUtilModificat.h / XML4OSMUtilModificat.cpp: Procesamiento de datos en formato XML para mapas.

   - main.cpp: Código principal que ejecuta las pruebas del proyecto.

## Funcionalidad

### BallTree

El BallTree es una estructura de datos jerárquica para realizar búsquedas rápidas de puntos cercanos. Permite:

   - Construir un árbol de búsqueda eficiente con construirArbre().

   - Encontrar el punto más cercano a una coordenada con nodeMesProper().

   - Recorrer el árbol en diferentes órdenes con preOrdre(), inOrdre(), y postOrdre().

### Grafos y Rutas

El grafo permite modelar caminos y encontrar la ruta más corta entre dos puntos usando el algoritmo de Dijkstra. Métodos clave:

   - afegirNode(): Añadir un nodo al grafo.

   - afegirAresta(): Conectar dos nodos con una arista y su distancia.

   - Dijkstra(): Encontrar la ruta más corta entre dos puntos.

   - camiCurt(): Generar el camino óptimo entre dos nodos dados.

### Mapas y Puntos de Interés

   - MapaBase define la estructura general de un mapa.

   - MapaSolucio extiende MapaBase y combina BallTree y Grafos para optimizar la búsqueda de rutas.

   - Se pueden añadir puntos de interés como restaurantes y tiendas con PuntDeInteresBase y sus extensiones.

### Utilidades

   - Util: Contiene funciones auxiliares como cálculos de distancia con la fórmula de Haversine y transformación de coordenadas.

   - XML4OSMUtilModificat: Procesa datos en XML relacionados con OpenStreetMap para extraer información relevante sobre nodos y caminos.

## Objetivos del Proyecto

La segunda parte de este proyecto se centra en encontrar el camino más corto entre dos puntos de interés. Para lograrlo, se deben implementar las siguientes tareas:

1. Construcción del Grafo:

   - Los nodos representan las coordenadas de los caminos.

   - Las conexiones entre nodos se basan en la distancia Haversine.

   - Métodos recomendados: afegirNode(), afegirAresta().

2. Implementación del BallTree:

   - Estructura de datos para organizar los nodos camino de manera jerárquica.

   - Permite encontrar el nodo camino más cercano a un punto de interés.

   - Métodos clave: preOrdre(), inOrdre(), postOrdre().

3. Búsqueda del Nodo Camino más Cercano:

   - Se usa el algoritmo 1NN (K-Nearest Neighbor con K=1).

   - Método clave: nodeMesProper(Coordinate pdi, Coordinate& Q, Ball* bola_arrel).

4. Cálculo del Camino Más Corto:

   - Implementar el método buscaCamiMesCurt(PuntDeInteresBase* desde, PuntDeInteresBase* a), en MapaSolucio.

   - Se usa la implementación del grafo y el BallTree para encontrar la mejor ruta.
  


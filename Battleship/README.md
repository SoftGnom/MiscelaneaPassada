# Juego de Batalla Naval en Java

Este proyecto implementa el clásico juego de Batalla Naval en Java, utilizando una estructura basada en MVC (Modelo-Vista-Controlador).

## Estructura del Proyecto

### Clases Principales

   - Main.java: Punto de entrada del programa, inicia el menú principal.

   - Board.java: Representa el tablero del juego, permitiendo la colocación de barcos y la ejecución de disparos.

   - Game.java: Controla el flujo del juego, gestionando turnos y verificando condiciones de victoria.

   - Menu.java: Implementa un menú de opciones para iniciar el juego, ver el ranking y salir.

   - Player.java: Representa a los jugadores, almacenando sus tableros y nombres.

   - Ship.java: Define las propiedades de los barcos y su estado durante el juego.

   - Ranking.java: Gestiona el ranking de los jugadores almacenando los resultados de las partidas.

   - View.java: Maneja la interacción con el usuario, mostrando el tablero, recogiendo entradas y gestionando el menú.

### Clases Auxiliares y de Prueba

   - MockGame.java y MockRanking.java: Versiones simuladas para pruebas del juego y el ranking.

   - MockEditorFile.java: Implementación simulada de un archivo de ranking para pruebas.

   - MockView.java: Versión simulada de la vista para pruebas automatizadas.

   - Box.java: Interfaz que define el comportamiento de una casilla en el tablero.

   - BoxStates.java: Define constantes para los distintos estados de una casilla (WATER, HIDDEN, MIDDLE_OF_THE_SHIP, etc.).

   - PartOfShip.java: Representa una parte de un barco en el tablero.

   - Water.java: Representa una casilla de agua en el tablero.

   - Revealed.java: Indica que una casilla ha sido revelada tras un disparo.

   - Hidden.java: Representa una casilla oculta en el tablero.

   - EditorFile.java: Maneja la lectura y escritura del archivo de ranking.

   - OptionsMenu.java: Contiene constantes para gestionar las opciones del menú.

## Pruebas del Proyecto

Se han implementado pruebas unitarias con JUnit para verificar la correcta funcionalidad de cada componente del juego:

   - BoardTest.java: Prueba la creación del tablero, colocación de barcos y detección de impactos.

   - GameTest.java: Verifica el flujo del juego, cambios de turno y detección de disparos.

   - MenuTest.java: Prueba la correcta interacción del menú con las opciones de juego y ranking.

   - PlayerTest.java: Comprueba la gestión de tableros individuales y la actualización de estados de casillas.

   - RankingTest.java: Valida la lectura y escritura de datos en el ranking.

   - ShipTest.java: Evalúa la creación de barcos, su estado y si han sido hundidos.

   - EditorFileTest.java: Comprueba la creación, lectura y escritura de archivos de ranking.

   - HiddenTest.java: Verifica el comportamiento de las casillas ocultas.

   - PartOfShipTest.java: Evalúa la funcionalidad de las partes de los barcos y su estado de impacto.

   - RevealedTest.java: Testea la correcta revelación de casillas tras un disparo.

   - WaterTest.java: Asegura que las casillas de agua funcionan como esperado.

### Métodos de Testing Aplicados

Según el Informe de Test de Software Battleship, se aplicaron las siguientes técnicas de prueba:

   - Particiones Equivalentes: Se probaron casos de entrada representativos de cada categoría de datos.

   - Valores Límite y Frontera: Se evaluaron valores extremos para asegurar la robustez del sistema.

   - Pairwise Testing: Se generaron combinaciones óptimas de valores para reducir el número de pruebas.

   - Mock Objects: Se usaron objetos simulados para probar el comportamiento de módulos específicos.

   - Statement Coverage: Se aseguró que todas las líneas de código fueran ejecutadas durante los tests.

   - Decision Coverage: Se verificó que todas las decisiones en el código se ejecutaran al menos una vez.

   - Condition Coverage: Se probó cada condición booleana para evaluar su impacto.

   - Path Coverage: Se probaron todos los caminos posibles dentro de funciones críticas.

   - Loop Testing: Se evaluaron bucles con diferentes condiciones y límites.


## Funcionamiento del Juego

1. Inicio del Juego:

   - Se solicita el tamaño del tablero y el número de barcos.

   - Los jugadores introducen sus nombres y colocan sus barcos en el tablero.

2. Turnos de los Jugadores:

   - Cada jugador selecciona una casilla del tablero rival para disparar.

   - Se muestra el resultado del disparo (agua, impacto o hundimiento).

3. Condición de Victoria:

   - El juego finaliza cuando un jugador ha hundido todos los barcos del oponente.

   - Se muestra el ganador y se guarda el resultado en el ranking.
  
   

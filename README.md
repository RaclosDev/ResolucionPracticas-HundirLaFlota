
# Hundir la Flota en C

Este proyecto implementa un juego de hundir la flota en el lenguaje C.

## Instrucciones de juego

Para jugar, el usuario debe ingresar las coordenadas (fila y columna) donde desea lanzar un ataque. 
Si acierta a un barco, este se marcará con el símbolo del mismo y se le notificará al usuario. 
Si el ataque falla, se marcará con una 'X' y se le notificará al usuario. 
El juego continuará hasta que el usuario haya destruido todos los barcos o hasta que se hayan agotado los intentos permitidos.

## Requisitos de implementacion
-  El juego es una batalla entre el jugador y la computadora.
-  La computadora establece el tablero y ubica aleatoriamente los barcos.
-  El tamaño del tablero es ajustable mediante una constante simbólica, y se recomienda un tamaño de 20x20 como mínimo.
-  Los barcos a ubicar son: portaaviones (10x2 celdas), acorazado (5x2 celdas), destructor (5x1 celdas), submarino (4x1 celdas), y patrullero (3x1 celdas).
-  Los barcos se ubican aleatoriamente en el tablero, en sentido horizontal o vertical aleatoriamente.
-  Los barcos no pueden superponerse.
-  La computadora informa al usuario si las coordenadas especificadas corresponden al océano o a un barco, y si es un barco, informa el tipo de barco.
-  Cuando un barco es hundido completamente, la computadora informa al usuario.
-  El usuario tiene 100 intentos para ganar la partida. Cuando una coordenada especificada por el usuario acierta a un barco por primera vez, no se consume ningún intento.
- El juego termina cuando el usuario gasta todos sus intentos o cuando el usuario vence a la computadora.
- En cada tirada, se muestra al usuario el tablero de juego.

## Estructura de datos

Se utiliza una estructura de datos para representar cada barco, que incluye su tamaño, ancho, símbolo para representarlo en el tablero y una bandera para indicar si ha sido tocado o no. También se utiliza una matriz de caracteres para representar el tablero de juego, en la que se colocarán los barcos y se realizarán los ataques.

## Estructura del proyecto

El proyecto consta de un único archivo `main.c` que contiene las siguientes funciones:

- `mostrarTablero()`: muestra el tablero de juego actual, ocultando los barcos.
- `mostrarTableroBonito()`: muestra el tablero de juego actual con números en los ejes y ocultando los barcos.
- `mostrarTableroDebug()`: muestra el tablero de juego actual sin ocultar los barcos.
- `barcoCabe()`: verifica si un barco de determinadas dimensiones cabe en el tablero dado sus coordenadas, orientación y tamaño.
- `lugarDisponible()`: verifica si el barco que queremos generar, pisa las dimensiones de otro barco.
- `isBarcoHundido()`: recorre todo el tablero en busca del barco especificado para comprobar si está hundido
- `hasGanado()`: verifica no quedan barcos en el tablero, es decir, si has ganado
- `primeraVez()`:verifica si es la primera vez que disparas a un barco determinado
- `inicializarTablero()`: inicializa un tablero vacio
- `colocarBarco()`: coloca un barco en el tablero en las coordenadas y orientación especificadas.
- `atacar()`: realiza un ataque en las coordenadas especificadas y devuelve el resultado del mismo.
- `hundirLaFlota()`: juega una partida completa de hundir la flota.

## Requisitos

Para compilar y ejecutar el proyecto, se necesita tener instalado el compilador de C GCC.

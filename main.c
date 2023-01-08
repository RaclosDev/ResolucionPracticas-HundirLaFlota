#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Tamaño mínimo del tablero
#define MIN_TABLERO 15
// Tamaño máximo del tablero
#define MAX_TABLERO 20
// Número máximo de intentos
#define MAX_INTENTOS 100

// Estructura para representar un barco
struct Barco {
    int largo;  // Largo del barco
    int ancho; // Ancho del barco
    char simbolo; // Símbolo para representar el barco en el tablero
    bool tocado; //Se utiliza para saber si es la primera vez que damos a un barco
};

// Tablero de juego
char tablero[MAX_TABLERO][MAX_TABLERO];

// Barcos a colocar en el tablero
struct Barco barcos[5] = {
        {10, 2, 'P', false},    // Portaaviones (2x10)
        {5,  2, 'A', false},    // Acorazado    (2x5)
        {5,  1, 'D', false},    // Destructor   (1x5)
        {4,  1, 'S', false},    // Submarino    (1x4)
        {3,  1, 'p', false}     // Patrullero   (1x3)
};

// Función para mostrar el tablero de juego
void mostrarTablero() {

    for (int i = 0; i < MAX_TABLERO; i++) {
        for (int j = 0; j < MAX_TABLERO; j++) {
            if (tablero[i][j] == 'X') {
                printf("%3c ", tablero[i][j]);
            } else {
                printf("%3c ", ' ');
            }
        }
        printf("\n");
    }
}

void mostrarTableroBonito() {
    printf("     ");
    for (int i = 0; i < MAX_TABLERO; i++) {
        printf("%3d ", i);
    }
    printf("\n");
    for (int i = 0; i < MAX_TABLERO; i++) {
        printf("%3d ", i);
        for (int j = 0; j < MAX_TABLERO; j++) {
            if (tablero[i][j] == 'X') {
                printf("%3c ", tablero[i][j]);
            } else {
                printf("%3c ", ' ');
            }
        }
        printf("\n");
    }
}

// Función para mostrar el tablero de juego y que se vean los barcos
void mostrarTableroDebug() {
    printf("     ");
    for (int i = 0; i < MAX_TABLERO; i++) {
        printf("%3d ", i);
    }
    printf("\n");
    for (int i = 0; i < MAX_TABLERO; i++) {
        printf("%3d ", i);
        for (int j = 0; j < MAX_TABLERO; j++) {
            printf("%3c ", tablero[i][j]);
        }
        printf("\n");
    }
}

// Función para verificar si el barco cabe en el tablero dado sus coordenadas, orientación y tamaño
int barcoCabe(int x, int y, int orientacion, int largo, int ancho) {

    if (orientacion == 0) { // Si la orientación es horizontal, comprobamos que el barco cabe en la fila
        return x + largo <= MAX_TABLERO && y + ancho <= MAX_TABLERO;
    } else {    // Si la orientación es vertical, comprobamos que el barco cabe en la columna
        return y + largo <= MAX_TABLERO && x + ancho <= MAX_TABLERO;
    }
}

// Función para verificar si hay otro barco en el lugar donde queremos colocar el barco
int lugarDisponible(int x, int y, int orientacion, int largo, int ancho) {
    if (orientacion == 0) {// Si la orientación es horizontal, comprobamos que no hay otro barco en la fila
        for (int i = x; i < x + largo; i++) {
            for (int j = y; j < y + ancho; j++) {
                if (tablero[i][j] != ' ') {
                    return 0;
                }
            }
        }
    } else {// Si la orientación es vertical, comprobamos que no hay otro barco en la columna
        for (int i = y; i < y + largo; i++) {
            for (int j = x; j < x + ancho; j++) {
                if (tablero[j][i] != ' ') {
                    return 0;
                }
            }
        }
    }
    return 1;
}

//Funcion para comprobar si un barco ha sido totalmente hundido
void isBarcoHundido(int x, int y, char barco) {
    int contador = 0;   //Iniciamos un contador y recorremos todo el tablero
    for (int i = 0; i < MAX_TABLERO; i++) {
        for (int j = 0; j < MAX_TABLERO; j++) {
            if (tablero[i][j] == barco) {
                contador++;
            }
        }
    }
    //Si en el tablero habia algun char correspondiente al barco de esa tirada, significa que no esta hundido
    if (contador == 0) {//Si el contador está a 0 es que se ha hunido
        printf("Barco %c hundido\n", barco);
    }
}

//Funcion para comprobar si has ganado
bool hasGanado() {
    bool hasGanado = true;
    for (int i = 0; i < MAX_TABLERO; i++) { //Se recorre el tablero
        for (int j = 0; j < MAX_TABLERO; j++) {
            if (tablero[i][j] != ' ' && tablero[i][j] != 'X') {
                hasGanado = false;  //Si hay algun barco, se pone a false
            }
        }
    }
    return hasGanado;
}

//Funcion para comprobar si es la primera vez que damos a un barco (si ya estaba tocado)
bool primeraVez(char barco) {
    int numBarco = 0;
    for (int i = 0; i < 5; i++) {
        if (barcos[i].simbolo == barco) numBarco = i;
    }
    //Si no estaba tocado
    if (barcos[numBarco].tocado == false) {
        printf("No estaba tocado\n");
        barcos[numBarco].tocado = true;
        return true;
    }
    printf("Estaba tocado\n");
    return false;
}

// Inicializamos el tablero con espacios en blanco
void inicializarTablero() {
    for (int i = 0; i < MAX_TABLERO; i++) {
        for (int j = 0; j < MAX_TABLERO; j++) {
            tablero[i][j] = ' ';
        }
    }
}

void colocaBarco(int x, int y, int orientacion, int largo, int ancho, char simbolo) {
    // Colocamos el barco en el tablero
    if (orientacion == 0) {
        // Si la orientación es horizontal, colocamos el barco en las casillas de la fila
        for (int j = x; j < x + largo; j++) {
            for (int k = y; k < y + ancho; k++) {
                tablero[j][k] = simbolo;
            }
        }
    } else {
        // Si la orientación es vertical, colocamos el barco en las casillas de la columna
        for (int j = y; j < y + largo; j++) {
            for (int k = x; k < x + ancho; k++) {
                tablero[k][j] = simbolo;
            }
        }
    }
}

int atacar(int tiradas) {
    int x, y, intentos = tiradas;
    scanf("%d %d", &x, &y);
    //Comprobamos que pasa con las coordenadas
    if (x < 0 || x >= MAX_TABLERO || y < 0 || y >= MAX_TABLERO) {//Si esta fuera del tablero
        printf("Coordenadas fuera del tablero\n");
    }
    if (tablero[x][y] == 'X') { //Si ya habia una X es que ya habias disparado
        printf("Ya disparaste en estas coordenadas\n");
    } else if (tablero[x][y] == ' ') {  //Si esta vacio es que es oceano y has fallado
        printf("Oceano\n");
        tablero[x][y] = 'X';
    } else {
        printf("Barco %c\n", tablero[x][y]);    //Si no es ninguna de las anteriores es que hay un barco
        char barco = tablero[x][y]; //Cogemos la letra del barco
        tablero[x][y] = 'X';    //Marcamos la casilla como disparada
        if (primeraVez(barco)) {    //Comprobamos si es la primera vezx que hiteamos el barco
            intentos--; //Si es así la tirada nos sale gratis
        }
        isBarcoHundido(x, y, barco);    //Y despues comprobamos si el barco ha sido hundido por completo
    }
    intentos++;
    return intentos;
}

int main() {
    // Inicializamos el generador de números aleatorios
    srand(time(NULL));

    inicializarTablero();

    // Colocamos cada barco en el tablero
    for (int i = 0; i < 5; i++) {
        struct Barco barco = barcos[i];

        // Generamos coordenadas y orientación aleatorias para el barco
        int x = rand() % MAX_TABLERO;
        int y = rand() % MAX_TABLERO;
        int orientacion = rand() % 2;

        // Comprobamos si el barco cabe en el tablero y si hay lugar disponible en el tablero
        while (!barcoCabe(x, y, orientacion, barco.largo, barco.ancho) ||
               !lugarDisponible(x, y, orientacion, barco.largo, barco.ancho)) {
            // Si no cabe o no hay lugar disponible
            // Generamos nuevas coordenadas y orientación aleatorias hasta que las haya
            x = rand() % MAX_TABLERO;
            y = rand() % MAX_TABLERO;
            orientacion = rand() % 2;
        }
        colocaBarco(x, y, orientacion, barco.largo, barco.ancho, barco.simbolo);
    }
    // Bucle del juego
    int intentos = 0;
    while (intentos < MAX_INTENTOS) {
        mostrarTablero();
        printf("Te quedan %i intentos\n", MAX_INTENTOS - intentos);
        printf("Introduce coordenadas: ");

        intentos = atacar(intentos);

        if (hasGanado()) {  //Despues de cada tirada comprobamos si hemos ganado, es decir, no queda ningun barco
            printf("Has ganado\n");
            break;
        }

    }
    //Fin del bucle y fin del juego

    printf("Fin del juego\n");
    return 0;
}
#ifndef OTHELLO_H
#define OTHELLO_H
#define DIMENSION_TABLERO 8
#define MAX_NAMELEN 32

#include <stdbool.h>

// representa el color de una celda o turno de juego
typedef enum { VACIO = 0, BLANCO, NEGRO } Color;

// representa el resultado final de un juego
typedef enum {
  TERMINADO,
  INCOMPLETO_B,
  INCOMPLETO_N,
  ILEGAL_B,
  ILEGAL_N
} Estado_final;

// representa un tablero de othello en un array 2d
typedef struct {
  Color casillas[DIMENSION_TABLERO][DIMENSION_TABLERO];
} Tablero;

// representa un par de coordenadas cartesianas
typedef struct {
  int x;
  int y;
} Coord;

// representa los datos obtenidos al leer un juego de un archivo
typedef struct {
  char jugador_n[MAX_NAMELEN];
  char jugador_b[MAX_NAMELEN];
  char comienza;
  Coord *jugadas[100];
  int cant_jugadas;
} Datos_juego;

// void -> Tablero*
// retorna un apuntador a una direccion de memoria
// que contiene una estructura de Tablero
// recordar liberar esta memoria.
Tablero *inicializar_tablero(void);

// Coord* -> bool
// retorna 1 si la coordenada se encuentra dentro del tablero o 0 en caso
// contrario
bool es_coordenada_valida(Coord *coord);

// Tablero* -> void
// imprime el tablero a la consola, funcion utilizada para motivos de prueba
void print_tablero(Tablero *tablero);

// Tablero* , Coord*, Color -> bool
// toma un tablero, la coordenada del movimiento que se quiera realizar, y el
// color del jugador que realiza el movimiento, y retorna 1 si es un movimiento
// legal o 0 si no lo es
bool es_movimiento_legal(Tablero *tablero, Coord *coord, Color turno);

// Tablero* , Coord*, int, int, Color -> bool
// usada en la funcion es_movimiento_legal(), dado un tablero, una coordenada,
// direcciones x e y, y el color del jugador que mueve, determina si en esa
// direccion se efectuarian cambios sobre el tablero
bool es_recorrido_valido(Tablero *tablero, Coord *coord_inicio, int dx, int dy,
                         Color turno);

// Tablero*, Color -> bool
// dado un tablero y el color que mueve, determina si existen posibles
// movimientos legales para ese color; en caso contrario seria legal pasar y la
// funcion retorna 1
bool es_legal_pasar(Tablero *tablero, Color turno);

// Tablero*, Coord*, int (enum color) -> void
// Dado un tablero, una coordenada, y el color que toca mover aplica los cambios
// segun las reglas sobre el tablero indicado.
// Esta funcion cambia el estado del tablero y no verifica que el movimiento sea
// legal o no.
void aplicar_movimiento(Tablero *tablero, Coord *coord, Color turno);

// Tablero*,Datos_juego* -> int (enum estado_final)
// Dada una estructura de Datos_juego*, reproduce los movimientos indicados en
// la lista de jugadas sobre el tablero indicado, y retorna la condicion con la
// que termina el juego
Estado_final simular_juego(Tablero *tablero, Datos_juego *datos);

// Tablero* -> int
// Dado un tablero cuenta las fichas en el, y retorna la evaluacion del tablero
// segun las reglas del juego
// nota: una evaluacion mayor a 0 quiere decir que las blancas ganan por esa
// cantidad de puntos, y de manera similar una menor a 0 quiere decir que las
// negras ganan; una evaluacion == 0 es un empate.
int evaluar_tablero(Tablero *tablero);
#endif

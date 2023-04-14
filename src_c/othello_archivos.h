#ifndef OTHELLO_ARCHIVOS_H
#define OTHELLO_ARCHIVOS_H
#include "othello.h"

// char* -> Datos_juego*
// Lee un archivo en la direccion dada y retorna los datos como un apuntador
// a una estructura Datos_juego. En caso de leer datos erroneos, detiene el
// programa. Recordar liberar la memoria correspondiente a esta estructura;
Datos_juego *leer_juego(char *filename);

// char* -> Coord*
// Toma una cadena de caracteres con el formato esperado [A-H][1-8] y
// retorna un apuntador a una estructura Coord. Recordar liberar la memoria
// correspondiente a la estructura generada.
Coord *str_a_coord(char *str);

// Datos_juego* -> void
// Libera la memoria perteneciente al apuntador a una estructura Datos_juego
// Libera tambien la memoria de cada coordenada contenida en la lista de
// jugadas.
void liberar_juego(Datos_juego *datos);

// Tablero*, int, char* -> void
// Dados un tablero, un color como definido en othello.h, y una cadena de
// caracteres, vuelca estos datos en un archivo generado en la direccion de
// char* filename
void escribir_juego_a_archivo(Tablero *tablero, int turno, char *filename);

#endif

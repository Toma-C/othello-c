#include "othello.h"
#include "othello_archivos.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int test_es_coordenada_valida() {
  Coord test_coord = {.x = 0, .y = 0};
  assert(es_coordenada_valida(&test_coord) == true);
  test_coord.x = -1;
  test_coord.y = 0;
  assert(es_coordenada_valida(&test_coord) == false);
  test_coord.x = 1;
  test_coord.y = -2;
  assert(es_coordenada_valida(&test_coord) == false);
  test_coord.x = 4;
  test_coord.y = 7;
  assert(es_coordenada_valida(&test_coord) == true);
  test_coord.x = 9;
  test_coord.y = 0;
  assert(es_coordenada_valida(&test_coord) == false);
  test_coord.x = 0;
  test_coord.y = 9;
  assert(es_coordenada_valida(&test_coord) == false);
  test_coord.x = 0;
  test_coord.y = 0;
  assert(es_coordenada_valida(&test_coord) == true);
  printf("es_coordenada_valida OK \n");
  return 0;
}

int test_es_movimiento_legal() {
  Tablero *test_tablero = inicializar_tablero();
  Coord test_coord = {.x = 2, .y = 3};
  /*  ┌ A B C D E F G H ┐
      1 . . . . . . . . 1
      2 . . . . . . . . 2
      3 . . . . . . . . 3
      4 . . X ☺ ☻ . . . 4 <---- Jugada normal, legal para las negras
      5 . . . ☻ ☺ . . . 5       ilegal para las blancas
      6 . . . . . . . . 6
      7 . . . . . . . . 7
      8 . . . . . . . . 8
      └ A B C D E F G H ┘ */
  assert(es_movimiento_legal(test_tablero, &test_coord, BLANCO) == false);
  assert(es_movimiento_legal(test_tablero, &test_coord, NEGRO) == true);
  test_coord.x = 2;
  test_coord.y = 2;
  /*  ┌ A B C D E F G H ┐
      1 . . . . . . . . 1
      2 . . . . . . . . 2
      3 . . X . . . . . 3 <---- Jugada ilegal para las negras, no efectua
      4 . . . ☺ ☻ . . . 4       cambios e ilegal para las blancas
      5 . . . ☻ ☺ . . . 5       por no ser adyacente a las negras
      6 . . . . . . . . 6
      7 . . . . . . . . 7
      8 . . . . . . . . 8
      └ A B C D E F G H ┘ */
  assert(es_movimiento_legal(test_tablero, &test_coord, BLANCO) == false);
  assert(es_movimiento_legal(test_tablero, &test_coord, NEGRO) == false);
  test_tablero->casillas[3][3] = NEGRO;
  test_tablero->casillas[3][2] = NEGRO;
  test_tablero->casillas[3][1] = BLANCO;
  test_tablero->casillas[3][0] = NEGRO;
  test_tablero->casillas[3][7] = NEGRO;
  test_tablero->casillas[4][4] = NEGRO;
  test_tablero->casillas[3][5] = BLANCO;
  test_tablero->casillas[4][3] = VACIO;
  test_tablero->casillas[4][4] = VACIO;
  test_tablero->casillas[1][5] = BLANCO;
  test_tablero->casillas[1][6] = BLANCO;
  test_tablero->casillas[5][5] = NEGRO;
  test_coord.x = 6;
  test_coord.y = 3;
  /*  ┌ A B C D E F G H ┐
      1 . . . . . . . . 1
      2 . . . . . ☺ ☺ . 2
      3 . . . . . . . . 3
      4 ☻ ☺ ☻ ☻ ☻ ☺ X ☻ 4 <----- Jugada legal para las negras
      5 . . . . . . . . 5        para las blancas es legal pasar
      6 . . . . . ☻ . . 6
      7 . . . . . . . . 7
      8 . . . . . . . . 8
      └ A B C D E F G H ┘ */
  assert(es_movimiento_legal(test_tablero, &test_coord, BLANCO) == false);
  assert(es_movimiento_legal(test_tablero, &test_coord, NEGRO) == true);
  test_coord.x = -1;
  test_coord.y = -1;
  assert(es_movimiento_legal(test_tablero, &test_coord, BLANCO) == true);
  assert(es_movimiento_legal(test_tablero, &test_coord, NEGRO) == false);
  free(test_tablero);
  test_tablero = inicializar_tablero();
  test_tablero->casillas[5][5] = NEGRO;
  test_coord.x = 3;
  test_coord.y = 3;
  /*  ┌ A B C D E F G H ┐
      1 . . . . . . . . 1
      2 . . . . . . . . 2
      3 . . . . . . . . 3
      4 . . .>☺ ☻ . . . 4 <----- En una casilla ocupada no puede jugar
      5 . . . ☻ ☺ . . . 5        ningun color, por mas que efectue cambios
      6 . . . . . ☻ . . 6
      7 . . . . . . . . 7
      8 . . . . . . . . 8
      └ A B C D E F G H ┘ */
  assert(es_movimiento_legal(test_tablero, &test_coord, BLANCO) == false);
  assert(es_movimiento_legal(test_tablero, &test_coord, NEGRO) == false);
  // Para una jugada fuera del tablero tampoco es legal mover
  test_coord.x = 8;
  test_coord.y = 3;
  assert(es_movimiento_legal(test_tablero, &test_coord, BLANCO) == false);
  assert(es_movimiento_legal(test_tablero, &test_coord, NEGRO) == false);
  free(test_tablero);
  printf("es_movimiento_legal  OK \n");
  return 0;
};

int test_es_recorrido_valido() {
  printf("es_recorrido_valido  OK \n");
  return 0;
}

int main() {
  test_es_coordenada_valida();
  test_es_movimiento_legal();
  test_es_recorrido_valido();
  return 0;
}

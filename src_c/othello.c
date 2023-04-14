#include "othello.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Tablero *inicializar_tablero(void) {
  Tablero *tablero = malloc(sizeof(*tablero));
  // 0 = VACIO
  memset(tablero->casillas, 0,
         sizeof(Color) * DIMENSION_TABLERO * DIMENSION_TABLERO);
  tablero->casillas[3][3] = BLANCO;
  tablero->casillas[4][4] = BLANCO;
  tablero->casillas[4][3] = NEGRO;
  tablero->casillas[3][4] = NEGRO;
  return tablero;
}

bool es_coordenada_valida(Coord *coord) {
  return (coord->x >= 0) & (coord->y >= 0) & (coord->x < DIMENSION_TABLERO) &
         (coord->y < DIMENSION_TABLERO);
}

void print_tablero(Tablero *tablero) {
  printf("┌ A B C D E F G H ┐\n");
  for (int i = 0; i < DIMENSION_TABLERO; i++) {
    printf("%d ", i + 1);
    for (int ii = 0; ii < DIMENSION_TABLERO; ii++) {
      if (tablero->casillas[i][ii] == VACIO) {
        printf("%s", ". ");
      } else if (tablero->casillas[i][ii] == BLANCO) {
        printf("%s", "☺ ");
      } else if (tablero->casillas[i][ii] == NEGRO) {
        printf("%s", "☻ ");
      } else
        printf("q ");
    }
    printf("%d ", i + 1);
    printf("\n");
  }
  printf("└ A B C D E F G H ┘\n");
}

bool es_movimiento_legal(Tablero *tablero, Coord *coord, Color turno) {
  if (coord->x == -1 && coord->y == -1) {
    return es_legal_pasar(tablero, turno);
  } else if (!es_coordenada_valida(coord)) {
    return false;
  } else if (tablero->casillas[coord->y][coord->x] != VACIO) {
    return false;
  } else {
    for (int dx = -1; dx <= 1; dx++) {
      for (int dy = -1; dy <= 1; dy++) {
        if (!dx && !dy) {
          continue;
        }
        if (es_recorrido_valido(tablero, coord, dx, dy, turno)) {
          return true;
        }
      }
    }
    return false;
  }
}

bool es_recorrido_valido(Tablero *tablero, Coord *coord_inicio, int dx, int dy,
                         Color turno) {
  Coord coord_recorrido = {coord_inicio->x + dx, coord_inicio->y + dy};
  Color color_enemigo = (turno == BLANCO) ? NEGRO : BLANCO;
  bool color_enemigo_visto = false;
  while (es_coordenada_valida(&coord_recorrido)) {
    if (tablero->casillas[coord_recorrido.y][coord_recorrido.x] == VACIO) {
      return false;
    }
    if (tablero->casillas[coord_recorrido.y][coord_recorrido.x] == turno) {
      return color_enemigo_visto;
    }
    if (tablero->casillas[coord_recorrido.y][coord_recorrido.x] ==
        color_enemigo) {
      color_enemigo_visto = true;
    }
    coord_recorrido.x += dx;
    coord_recorrido.y += dy;
  }
  return false;
}

bool es_legal_pasar(Tablero *tablero, Color turno) {
  Coord coord;
  for (int y = 0; y < DIMENSION_TABLERO; y++) {
    coord.y = y;
    for (int x = 0; x < DIMENSION_TABLERO; x++) {
      coord.x = x;
      if (es_movimiento_legal(tablero, &coord, turno)) {
        return false;
      }
    }
  }
  return true;
}

void aplicar_movimiento(Tablero *tablero, Coord *coord, Color turno) {
  if (!(coord->x == -1 && coord->y == -1)) {
    for (int dx = -1; dx <= 1; dx++) {
      for (int dy = -1; dy <= 1; dy++) {
        if (!dx & !dy) {
          continue;
        }
        if (es_recorrido_valido(tablero, coord, dx, dy, turno)) {
          tablero->casillas[coord->y][coord->x] = turno;
          Coord c_recorrido = {coord->x + dx, coord->y + dy};
          while (tablero->casillas[c_recorrido.y][c_recorrido.x] != turno) {
            tablero->casillas[c_recorrido.y][c_recorrido.x] = turno;
            c_recorrido.x += dx;
            c_recorrido.y += dy;
          }
        } else {
          continue;
        }
      }
    }
  }
}

Estado_final simular_juego(Tablero *tablero, Datos_juego *datos) {
  Color turno_actual = (datos->comienza == 'N') ? NEGRO : BLANCO;
  int i = 0;
  while ((i < datos->cant_jugadas) &&
         es_movimiento_legal(tablero, datos->jugadas[i], turno_actual)) {
    aplicar_movimiento(tablero, datos->jugadas[i], turno_actual);
    turno_actual = (turno_actual == BLANCO) ? NEGRO : BLANCO;
    i++;
  }
  if (i == datos->cant_jugadas) {
    if (es_legal_pasar(tablero, BLANCO) && es_legal_pasar(tablero, NEGRO)) {
      return TERMINADO;
    } else {
      return (turno_actual == BLANCO) ? INCOMPLETO_B : INCOMPLETO_N;
    }
  } else {
    return (turno_actual == BLANCO) ? ILEGAL_B : ILEGAL_N;
  }
}

int evaluar_tablero(Tablero *tablero) {
  int score = 0;
  for (int y = 0; y < DIMENSION_TABLERO; y++) {
    for (int x = 0; x < DIMENSION_TABLERO; x++) {
      if (tablero->casillas[y][x] == BLANCO) {
        score++;
      } else if (tablero->casillas[y][x] == NEGRO) {
        score--;
      }
    }
  }
  return score;
}

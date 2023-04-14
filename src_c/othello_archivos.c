#include "othello_archivos.h"
#include "othello.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Datos_juego *leer_juego(char *filename) {
  Datos_juego *datos = malloc(sizeof(*datos));
  FILE *fp = fopen(filename, "r");
  if (!fp) {
    printf("no se pudo leer el archivo \n");
    exit(1);
  } else {
    for (int j = 0; j < 2; j++) {
      char buffer[MAX_NAMELEN + 2];
      if (!fgets(buffer, MAX_NAMELEN + 2, fp)) {
        printf("formato invalido \n");
        exit(1);
      }
      char jugador[MAX_NAMELEN];
      char color;
      if (sscanf(buffer, "%[^,] ,%c", jugador, &color) != 2) {
        printf("formato invalido \n");
        exit(1);
      }

      if (color == 'N') {
        strcpy(datos->jugador_n, jugador);
      } else {
        strcpy(datos->jugador_b, jugador);
      }
    }

    /*
    datos->comienza = getc(fp); // el caracter de quien comienza;
    getc(fp); // la ultima nueva linea antes de la lista de jugadas;
     */
    printf("jugador_n: %s \n", datos->jugador_n);
    printf("jugador_b: %s \n", datos->jugador_b);
    char buff[4];
    if (fgets(buff, 4, fp)) {
      datos->comienza = buff[0];
    } else {
      printf("formato invalido \n");
      exit(1);
    }
    printf("comienza: %c \n", datos->comienza);
    int k = 0;
    datos->cant_jugadas = k;
    while (fgets(buff, 4, fp)) {
      datos->jugadas[k] = str_a_coord(buff);
      datos->cant_jugadas = ++k;
    }
    fclose(fp);
  }
  return datos;
}
void liberar_juego(Datos_juego *datos) {
  int i = 0;
  while (i < datos->cant_jugadas) {
    // printf("[%d,%d]", datos->jugadas[i]->x, datos->jugadas[i]->y);
    free(datos->jugadas[i]);
    i++;
  }
  free(datos);
}

Coord *str_a_coord(char *str) {
  Coord *coordenada = malloc(sizeof(*coordenada));
  if (strlen(str) >= 2) {
    coordenada->x = (int)(str[0] - 65);
    coordenada->y = (int)(str[1] - 49);
  } else {
    coordenada->x = -1;
    coordenada->y = -1;
  }
  return coordenada;
}

void escribir_juego_a_archivo(Tablero *tablero, int turno, char *filename) {
  FILE *fp = fopen(filename, "w+");
  char caracter = 'X';
  for (int y = 0; y < DIMENSION_TABLERO; y++) {
    for (int x = 0; x < DIMENSION_TABLERO; x++) {
      switch (tablero->casillas[y][x]) {
      case VACIO:
        caracter = 'X';
        break;
      case BLANCO:
        caracter = 'B';
        break;
      case NEGRO:
        caracter = 'N';
        break;
      }
      fprintf(fp, "%c", caracter);
    }
    fprintf(fp, "\n");
  }
  caracter = (turno == BLANCO) ? 'B' : 'N';
  fprintf(fp, "%c\n", caracter);
  fclose(fp);
}

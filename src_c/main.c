#include "othello.h"
#include "othello_archivos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  if (argc <= 2) {
    printf("Por favor, indique la direccion de un archivo como argumento\n");
    printf("Ejemplo de uso: \n");
    printf("./main <archivo_juego> <archivo_salida> \n");
    printf("Puede usarse la opcion -t para indicar que se quiere ver los "
           "resultados de varios juegos sin generar archivos de salida \n");
    printf("./main -t <j1> <j2> <j3> <j4> ... \n");
    // comando usado para probar juegos en gran cantidad
    //./main -t ./juegos/*
    exit(0);
  } else {
    Estado_final resultado_juego;
    int eval;
    // en caso que NO se use la opcion -t
    if (strcmp(argv[1], "-t")) {
      char *archivo_entrada = argv[1];
      char *archivo_salida = argv[2];
      printf("leyendo: %s\n", archivo_entrada);

      Datos_juego *datos = leer_juego(archivo_entrada);
      Tablero *tablero = inicializar_tablero();
      // la funcion simular_juego(), ademas de indicar el estado final del
      // juego, modifica el tablero dado aplicando las jugadas en los datos
      resultado_juego = simular_juego(tablero, datos);
      eval = evaluar_tablero(tablero);

      switch (resultado_juego) {
      case TERMINADO:
        if (eval) {
          printf("Gana el jugador %s con las %s. \n",
                 eval > 0 ? datos->jugador_b : datos->jugador_n,
                 eval > 0 ? "blancas" : "negras");
        } else {
          printf("El juego termina en un empate. \n");
        }
        break;
      case INCOMPLETO_B:
        printf("El juego no fue terminado, volcando tablero a archivo\n");
        printf("Archivo de salida: %s\n", archivo_salida);
        escribir_juego_a_archivo(tablero, BLANCO, archivo_salida);
        break;
      case INCOMPLETO_N:
        printf("El juego no fue terminado, volcando tablero a archivo \n");
        printf("Archivo de salida: %s\n", archivo_salida);
        escribir_juego_a_archivo(tablero, NEGRO, archivo_salida);
        break;
      case ILEGAL_B:
      case ILEGAL_N:
        printf("El juego concluye por una jugada ilegal de %s\n",
               resultado_juego == ILEGAL_B ? datos->jugador_b
                                           : datos->jugador_n);
        break;
      }
      print_tablero(tablero);
      free(tablero);
      liberar_juego(datos);
    } else {
      // en caso que se use la opcion -t
      // esta opcion es ultilizada para probar un gran numero de juegos
      // en un solo uso del programa
      for (int i = 2; i < argc; i++) {
        printf("---------------------------------------------\n");
        printf("leyendo: %s\n", argv[i]);
        Datos_juego *datos = leer_juego(argv[i]);
        Tablero *tablero = inicializar_tablero();
        resultado_juego = simular_juego(tablero, datos);
        eval = evaluar_tablero(tablero);
        switch (resultado_juego) {
        case TERMINADO:
          if (!eval) {
            printf("El juego termina en un empate. \n");
          } else {
            printf("Gana el jugador %s con las %s. \n",
                   eval > 0 ? datos->jugador_b : datos->jugador_n,
                   eval > 0 ? "blancas" : "negras");
          }
          break;
        case INCOMPLETO_B:
        case INCOMPLETO_N:
          printf("El juego no fue terminado \n");
          break;
        case ILEGAL_B:
        case ILEGAL_N:
          printf("El juego concluye por una jugada ilegal de %s\n",
                 resultado_juego == ILEGAL_B ? datos->jugador_b
                                             : datos->jugador_n);
          break;
        }
        print_tablero(tablero);
        free(tablero);
        liberar_juego(datos);
      }
    }
  }

  return 0;
}

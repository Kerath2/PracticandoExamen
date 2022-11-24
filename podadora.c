#include <stdio.h>
#include <stdlib.h>
#define N 10
#define M 10

int contador = 0;
int mov[8][2];

void generateMove();
int resuelve(int x, int y, int c, int tablero[N][M], int num, int n, int m);
int sePuedeSeguir(int x, int y, int c, int tablero[N][M], int n, int m);
void inicializaTablero(int tablero[N][M], int n, int m);
int es_valido_llenar(int i, int x, int y, int c, int tablero[N][M], int n,
                     int m);
void llena(int i, int x, int y, int c, int tablero[N][M], int n, int m,
           int *quedaX, int *quedaY, int num);
int es_valido_pisar(int x, int y, int tablero[N][M], int n, int m);
void quita(int i, int x, int y, int c, int tablero[N][M], int n, int m);
void imprimeTablero(int tablero[N][M], int n, int m);
int main() {
  generateMove();
  int tablero[N][M];
  int n, m, c;
  printf("Ingrese n m y c:");
  fscanf(stdin, "%d %d %d", &n, &m, &c);
  inicializaTablero(tablero, n, m);
  imprimeTablero(tablero, n, m);
  int num = 1;
  resuelve(0, 0, c, tablero, num, n, m);
  return 0;
}

int resuelve(int x, int y, int c, int tablero[N][M], int num, int n, int m) {
  int quedaX, quedaY;
  int newX, newY;
  if (!sePuedeSeguir(x, y, c, tablero, n, m)) {
    imprimeTablero(tablero, n, m);
    contador++;
    return 0;
  }

  if (contador == 10) { // Se agrego esto para debuggear
    return 1;
  }

  // Si se puede seguir
  // hay 4 tipos de llenado
  for (int i = 0; i < 4; i++) {
    if (es_valido_llenar(i, x, y, c, tablero, n, m)) {
      llena(i, x, y, c, tablero, n, m, &quedaX, &quedaY, num);
      for (int j = 0; j < 8; j++) {
        newX = quedaX + mov[j][0];
        newY = quedaY + mov[j][1];
        if (es_valido_pisar(newX, newY, tablero, n, m)) {
          if (resuelve(newX, newY, c, tablero, num + 1, n, m))
            return 1;
          quita(i, quedaX, quedaY, c, tablero, n, m);
        }
      }
    }
  }
  return 0;
}

int sePuedeSeguir(int x, int y, int c, int tablero[N][M], int n, int m) {
  int arriba = 1, abajo = 1, izquierda = 1, derecha = 1;
  if (x - c + 1 >= 0) { // se puede seguir por arriba
    for (int i = 0; i < c; i++) {
      if (tablero[x - i][y] != 0)
        arriba = 0;
    }
  } else {
    arriba = 0;
  }

  if (x + c - 1 < n) { // se puedde seguir por abajo
    for (int i = 0; i < c; i++) {
      if (tablero[x + i][y] != 0)
        abajo = 0;
    }
  } else {
    abajo = 0;
  }
  if (y - c + 1 >= 0) { // Se puede seguir por la izquierda
    for (int i = 0; i < c; i++) {
      if (tablero[x][y - i] != 0)
        izquierda = 0;
    }
  } else {
    izquierda = 0;
  }
  if (y + c - 1 < m) { // Se puede seguir por la derecha
    for (int i = 0; i < c; i++) {
      if (tablero[x][y + i] != 0)
        derecha = 0;
    }
  } else {
    derecha = 0;
  }

  // if (arriba)
  //   printf("Arriba\n");
  // if (abajo)
  //   printf("Abajo\n");
  // if (derecha)
  //   printf("Derecha\n");
  // if (izquierda)
  //   printf("Izquierda\n");

  if (arriba || abajo || derecha || izquierda)
    return 1;
  else
    return 0;
}

void generateMove() {
  mov[0][0] = 1;
  mov[0][1] = 0;
  mov[1][0] = 1;
  mov[1][1] = 1;
  mov[2][0] = 1;
  mov[2][1] = -1;
  mov[3][0] = 0;
  mov[3][1] = 1;
  mov[4][0] = 0;
  mov[4][1] = -1;
  mov[5][0] = -1;
  mov[5][1] = 0;
  mov[6][0] = -1;
  mov[6][1] = 1;
  mov[7][0] = -1;
  mov[7][1] = -1;
}

void inicializaTablero(int tablero[N][M], int n, int m) {
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      tablero[i][j] = 0;
}

int es_valido_llenar(int i, int x, int y, int c, int tablero[N][M], int n,
                     int m) {
  // i: 0-arribla 1-abajo 2-izquierda 3-dercha
  int arriba = 1, abajo = 1, izquierda = 1, derecha = 1;
  if (x - c + 1 >= 0) { // se puede seguir por arriba
    for (int i = 0; i < c; i++) {
      if (tablero[x - i][y] != 0)
        arriba = 0;
    }
  } else {
    arriba = 0;
  }

  if (x + c - 1 < n) { // se puedde seguir por abajo
    for (int i = 0; i < c; i++) {
      if (tablero[x + i][y] != 0)
        abajo = 0;
    }
  } else {
    abajo = 0;
  }
  if (y - c + 1 >= 0) { // Se puede seguir por la izquierda
    for (int i = 0; i < c; i++) {
      if (tablero[x][y - i] != 0)
        izquierda = 0;
    }
  } else {
    izquierda = 0;
  }
  if (y + c - 1 < m) { // Se puede seguir por la derecha
    for (int i = 0; i < c; i++) {
      if (tablero[x][y + i] != 0)
        derecha = 0;
    }
  } else {
    derecha = 0;
  }
  switch (i) {
  case 0:
    return arriba;
    break;
  case 1:
    return abajo;
    break;
  case 2:
    return izquierda;
    break;
  case 3:
    return derecha;
    break;
  }
  return 0;
}

void llena(int i, int x, int y, int c, int tablero[N][M], int n, int m,
           int *quedaX, int *quedaY, int num) {

  switch (i) {
  case 0: // lena para arriba
    for (int k = 0; k < c; k++) {
      tablero[x - k][y] = num;
      *quedaX = x - k;
      *quedaY = y;
    }
    return;
  case 1:
    for (int k = 0; k < c; k++) {
      tablero[x + k][y] = num;
      *quedaX = x + k;
      *quedaY = y;
    }
    return;
  case 2:
    for (int k = 0; k < c; k++) {
      tablero[x][y - k] = num;
      *quedaX = x;
      *quedaY = y - k;
    }
    return;
  case 3:
    for (int k = 0; k < c; k++) {
      tablero[x][y + k] = num;
      *quedaX = x;
      *quedaY = y + k;
    }
    return;
  }
}

int es_valido_pisar(int x, int y, int tablero[N][M], int n, int m) {
  if (x >= 0 && x < n && y >= 0 && y < m) {
    if (tablero[x][y] == 0)
      return 1;
  }

  return 0;
}

void quita(int i, int x, int y, int c, int tablero[N][M], int n, int m) {
  // x e y es donde quedo, se tiene que quitar para el lado contrario
  switch (i) {
  case 0: // quita lo que lleno para arriba
    for (int k = 0; k < c; k++) {
      tablero[x + k][y] = 0;
    }
    return;
  case 1:
    for (int k = 0; k < c; k++) {
      tablero[x - k][y] = 0;
    }
    return;
  case 2:
    for (int k = 0; k < c; k++) {
      tablero[x][y + k] = 0;
    }
    return;
  case 3:
    for (int k = 0; k < c; k++) {
      tablero[x][y - k] = 0;
    }
    return;
  }
}

void imprimeTablero(int tablero[N][M], int n, int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("%d ", tablero[i][j]);
    }
    putchar('\n');
  }
  putchar('\n');
}

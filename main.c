#include <stdio.h>
#include <stdlib.h>

// Функции из fill_cols.c и fill_rows.c
double fill_matrix_rows(int *a, size_t N, int fill_type);
double fill_matrix_cols(int *a, size_t N, int fill_type);

int main(int argc, char *argv[]) {
  // Проверка аргументов командной строки
  if (argc != 4) {
    printf("Использование: %s <Размер N> <Режим (0-Строки, 1-Столбцы)> "
           "<Заполнение>\n",
           argv[0]);
    printf("  Заполнение: 0 - Нули, 1 - Последовательные числа, 2 - Случайные "
           "значения\n");
    return 1;
  }

  // Чтение аргументов
  size_t N = (size_t)atol(argv[1]);
  int mode = atoi(argv[2]); // 0 для строк, 1 для столбцов
  int fill =
      atoi(argv[3]); // 0 для нулей, 1 для последовательных, 2 для случайных

  // Динамическое выделение памяти для 1D массива, который симулирует 2D матрицу
  // N x N Это позволяет избежать ошибок сегментации при больших размерах и
  // гарантирует непрерывную память.
  int *a = (int *)malloc(N * N * sizeof(int));
  if (a == NULL) {
    printf("Ошибка: Не удалось выделить память (%zu байт)!\n",
           N * N * sizeof(int));
    return 1;
  }

  double elapsed_time = 0.0;

  // Запускаем вычисления в зависимости от режима и считаем время
  if (mode == 0) {
    elapsed_time = fill_matrix_rows(a, N, fill);
  } else if (mode == 1) {
    elapsed_time = fill_matrix_cols(a, N, fill);
  } else {
    printf("Неверный режим. Используйте 0 или 1.\n");
  }

  printf("Время выполнения циклов: %f секунд\n", elapsed_time);

  // Освобождение памяти
  free(a);

  return 0;
}

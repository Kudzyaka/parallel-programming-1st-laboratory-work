#include <omp.h>
#include <stddef.h>

double fill_matrix_cols(int *a, size_t N, int fill_type) {
    double start_time, end_time;

    // Режим 0 - Заполнение нулями
    if (fill_type == 0) {
        start_time = omp_get_wtime();
        // Внешний цикл - по строкам, внутренний - по столбцам,
        // НО заполнение идёт по формуле j * N + i
        // (то есть двигаемся по столбцам)
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                // Обращение a[j][i]
                a[j * N + i] = 0;
            }
        }
        end_time = omp_get_wtime();
    }
    // Режим 1 - Заполнение последовательными значениями
    else if (fill_type == 1) {
        int k = 1;
        start_time = omp_get_wtime();
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                a[j * N + i] = k++;
            }
        }
        end_time = omp_get_wtime();
    }
    // Режим 2 - Заполнение псевдослучайными значениями
    else if (fill_type == 2) {
        start_time = omp_get_wtime();
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                a[j * N + i] = (i * 31 + j * 17) % 1000;
            }
        }
        end_time = omp_get_wtime();
    } 
    else {
        return 0.0;
    }

    // Возвращаем время выполнения конкретного цикла
    return end_time - start_time;
}

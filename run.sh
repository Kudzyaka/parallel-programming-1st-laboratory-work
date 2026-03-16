#!/bin/bash
N=50000

# Ищет gcc
CC=""
for cmd in "gcc-15" "gcc-14" "gcc-13" "gcc"; do
    if command -v $cmd &> /dev/null; then
        CC=$cmd
        break
    fi
done

echo "Итоговый компилятор: $($CC --version | head -n 1)"

# Определение расширения исполняемого файла для Windows
EXT=""
if [[ "$OSTYPE" == "msys"* ]] || [[ "$OSTYPE" == "cygwin"* ]] || [[ "$OSTYPE" == "win32"* ]]; then
    EXT=".exe"
fi


# Компиляция без оптимизаций
echo "Компиляция без оптимизаций (-O0)..."
$CC -O0 -fopenmp main.c fill_rows.c fill_cols.c -o matrix_O0$EXT
if [ $? -ne 0 ]; then
    echo "Ошибка компиляции matrix_O0"
    exit 1
fi

# Компиляция с максимальными оптимизациями и авто-векторизацией
echo "Компиляция с оптимизациями (-O3)..."
$CC -O3 -fopenmp main.c fill_rows.c fill_cols.c -o matrix_O3$EXT
if [ $? -ne 0 ]; then
    echo "Ошибка компиляции matrix_O3"
    exit 1
fi

echo ""

function run_experiments() {
    local EXEC=$1
    echo "=========================================="
    echo "Тесты для $EXEC (Матрица $N x $N)"
    echo "=========================================="
    
    echo "--- ОБХОД ПО СТРОКАМ ---"
    printf "1. Нули:           "
    ./$EXEC $N 0 0 | grep -o 'Время выполнения.*'
    
    printf "2. Последоват.:    "
    ./$EXEC $N 0 1 | grep -o 'Время выполнения.*'
    
    printf "3. Псевдослуч.:    "
    ./$EXEC $N 0 2 | grep -o 'Время выполнения.*'
    
    echo "--- ОБХОД ПО СТОЛБЦАМ ---"
    printf "4. Нули:           "
    ./$EXEC $N 1 0 | grep -o 'Время выполнения.*'
    
    printf "5. Последоват.:    "
    ./$EXEC $N 1 1 | grep -o 'Время выполнения.*'
    
    printf "6. Псевдослуч.:    "
    ./$EXEC $N 1 2 | grep -o 'Время выполнения.*'
    echo ""
}

# Очистка старого отчета и генерация нового
echo "Идёт тестирование..."
run_experiments "matrix_O0$EXT" > report.txt
run_experiments "matrix_O3$EXT" >> report.txt

echo "Тестирование завершено! Результаты сохранены в report.txt:"
cat report.txt

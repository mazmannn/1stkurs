#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_ROWS 100
#define MAX_COLS 100

// Глобальные переменные для размеров и количества мин
int rows, cols, mines_count;
int **field;      // Скрытая матрица (0 - нет мины, -1 - мина)
int **visible;    // Видимая матрица (0 - закрыто, 1 - открыто, -2 - флаг)
int flags_placed; // Счетчик флажков

// Инициализация полей
void init_fields() {
    field = (int**)malloc(rows * sizeof(int*));
    visible = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        field[i] = (int*)malloc(cols * sizeof(int));
        visible[i] = (int*)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            field[i][j] = 0;
            visible[i][j] = 0;
        }
    }
    flags_placed = 0;
}

// Освобождение памяти
void free_fields() {
    for (int i = 0; i < rows; i++) {
        free(field[i]);
        free(visible[i]);
    }
    free(field);
    free(visible);
}

// Проверка границ поля
int is_valid(int r, int c) {
    return r >= 0 && r < rows && c >= 0 && c < cols;
}

// Генерация мин (после первого хода)
void place_mines(int start_r, int start_c) {
    int placed = 0;
    while (placed < mines_count) {
        int r = rand() % rows;
        int c = rand() % cols;
        
        // Не ставим мину в стартовую клетку и её соседей (чтобы первый ход был безопасным)
        int dist = 0;
        if (r == start_r && c == start_c) dist = 1;
        else if (abs(r - start_r) <= 1 && abs(c - start_c) <= 1) dist = 1;
        
        if (field[r][c] != -1 && dist == 0) {
            field[r][c] = -1;
            placed++;
        }
    }
    
    // Подсчет цифр вокруг мин
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (field[i][j] != -1) {
                int count = 0;
                for (int dr = -1; dr <= 1; dr++) {
                    for (int dc = -1; dc <= 1; dc++) {
                        if (dr == 0 && dc == 0) continue;
                        if (is_valid(i + dr, j + dc) && field[i + dr][j + dc] == -1) {
                            count++;
                        }
                    }
                }
                field[i][j] = count;
            }
        }
    }
}

// Рекурсивное открытие пустых областей
void open_cell(int r, int c) {
    if (!is_valid(r, c) || visible[r][c] != 0) return;
    
    visible[r][c] = 1; // Открываем клетку
    
    if (field[r][c] == -1) {
        // Взрыв мины
        return;
    }
    
    if (field[r][c] == 0) {
        // Если вокруг нет мин, открываем соседей рекурсивно
        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                if (dr == 0 && dc == 0) continue;
                open_cell(r + dr, c + dc);
            }
        }
    }
}

// Проверка победы
int check_win() {
    int open_count = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (visible[i][j] == 1) open_count++;
        }
    }
    return open_count == (rows * cols - mines_count);
}

// Отображение поля
void print_board() {
    printf("\n   ");
    for (int j = 0; j < cols; j++) printf("%2d ", j);
    printf("\n");
    
    for (int i = 0; i < rows; i++) {
        printf("%2d ", i);
        for (int j = 0; j < cols; j++) {
            if (visible[i][j] == 0) {
                printf(" . ");
            } else if (visible[i][j] == -2) {
                printf(" F ");
            } else if (field[i][j] == -1) {
                printf(" * ");
            } else {
                printf(" %d ", field[i][j]);
            }
        }
        printf("\n");
    }
}

// Основная функция
int main() {
    srand(time(NULL));
    
    printf("Введите размер поля (строки и колонки): ");
    if (scanf("%d %d", &rows, &cols) != 2 || rows <= 0 || cols <= 0 || rows > MAX_ROWS || cols > MAX_COLS) {
        printf("Ошибка ввода размеров.\n");
        return 1;
    }
    
    printf("Введите количество мин: ");
    if (scanf("%d", &mines_count) != 1 || mines_count < 0 || mines_count >= rows * cols) {
        printf("Ошибка ввода количества мин.\n");
        return 1;
    }
    
    init_fields();
    
    int first_move = 1;
    int game_over = 0;
    
    printf("\nДобро пожаловать в Сапер!\n");
    printf("Команды: (r c) - открыть клетку, (r c) F - поставить флаг, q - выход.\n");
    
    while (!game_over) {
        print_board();
        printf("Введите координаты и действие (например: 3 4 или 3 4 F): ");
        
        int r, c;
        char flag_input;
        int input_result = scanf("%d %d %c", &r, &c, &flag_input);
        
        // Очистка буфера ввода
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
        
        if (input_result < 2) {
            printf("Неверный формат ввода. Попробуйте снова.\n");
            continue;
        }
        
        if (flag_input == 'q' || flag_input == 'Q') break;
        
        if (!is_valid(r, c)) {
            printf("Координаты вне поля. Попробуйте снова.\n");
            continue;
        }
        
        if (flag_input == 'F' || flag_input == 'f') {
            if (visible[r][c] == 1) {
                printf("Эту клетку уже нельзя отметить флагом.\n");
                continue;
            }
            if (visible[r][c] == -2) {
                visible[r][c] = 0;
                flags_placed--;
            } else {
                visible[r][c] = -2;
                flags_placed++;
            }
            continue;
        }
        
        // Если это первый ход, генерируем мины
        if (first_move) {
            place_mines(r, c);
            first_move = 0;
        }
        
        open_cell(r, c);
        
        // Проверка на взрыв
        if (field[r][c] == -1) {
            printf("\nБум! Вы подорвались на мине.\n");
            game_over = 1;
            break;
        }
        
        // Проверка победы
        if (check_win()) {
            printf("\nПоздравляю! Вы победили!\n");
            game_over = 1;
        }
    }
    
    // Вывод статистики
    printf("\n--- Статистика ---\n");
    int open_count = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (visible[i][j] == 1) open_count++;
        }
    }
    printf("Открыто клеток: %d\n", open_count);
    printf("Поставлено флажков: %d\n", flags_placed);
    printf("Осталось мин: %d\n", mines_count - flags_placed);
    
    // Показать все мины в конце
    printf("\nВсе мины на поле:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (field[i][j] == -1) {
                printf("Мина в (%d, %d)\n", i, j);
            }
        }
    }
    
    free_fields();
    return 0;
}

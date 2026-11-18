#include<stdio.h>
#include<stdlib.h>
#include<time.h>
// int razvorot(int s, int a[s*s], int n){
//     int *b = malloc((size_t) s*s *sizeof*b);
//     if(b == NULL){
//         printf("неудалось выделить память");
//         return 1;
//     }
//     int *src = a;
//     int *dst = b;
//     for(int k =0; k<n; k++){
        
//         for(int i = 0; i<s; i++){
//             for(int j = 0; j<s; j++){
//                 dst[j*s + (s - 1 -i)] = src[i*s +j];

//             }
//         }
//         int *tmp = src;
//         src = dst;
//         dst = tmp;
//     }
//     for(int i = 0; i<s; i++){
//             for(int j = 0; j<s; j++){
//                 printf("%3d", src[i*s +j]);
//             }
//             printf("\n");
//         }
//     free(a);
//     free(b);
//     return 0;
// }

// int main(){
//     int s;
//     int c;
//     srand(time(NULL));


//     printf("введите ширину матрицы. ");
//     scanf("%d", &s);
//     int *a = malloc((size_t) s * s *sizeof*a);
//     if(a == NULL){
//         printf("неудалось создать матрицу");
//         return 1;
//     }
//     for(int i = 0; i<s; i++){
//         for(int j = 0; j< s; j++){
//             a[i*s + j] = (rand() % s*s);
//             printf("%3d", a[i*s + j]);
//         }
//         printf("\n");
//     }

//     printf("выберите действие и напишите число: \n ");
//     printf("1 - развернуть матрицу на 90 градусов \n ");
//     printf("2 - развернуть матрицу на 180 градусов \n");
//     printf("3 - развернуть матрицу на 270 градусов \n");
//     printf("4 - выход из программы \n");
//     scanf("%d", &c);
//     switch (c) {
//         case 1:
//             razvorot(s,a, 1);
//             break;
//         case 2:
//             razvorot(s,a, 2);
//             break;
//         case 3:
//             razvorot(s,a, 3);
//             break;
//         case 4:
//             break;
//         default:
//             printf("неподходящая цифра");
//     }
//     free(a);
//     return 0;
// }





#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void mines(int razryad, int *mine_matrix, int mines_count, int first_cell[2]) {
    int cells = razryad * razryad;
    int placed = 0;

    while (placed < mines_count) {
        int d = rand() % cells;
        if (mine_matrix[d] == -1 ||
            d == first_cell[0] * razryad + first_cell[1]) {
            continue;
        }
        mine_matrix[d] = -1;
        placed++;
    }
    for (int i = 0; i < cells; i++) {
        int row = i / razryad;
        int col = i % razryad;
        if (mine_matrix[i] == -1) {
            for (int j = -1; j <= 1; j++) {
                for (int k = -1; k <= 1; k++) {
                    if (j == 0 && k == 0) continue;
                    if (row + j >= 0 && row + j < razryad &&
                        col + k >= 0 && col + k < razryad) {
                        int neighbor = (row + j) * razryad + col + k;
                        if (mine_matrix[neighbor] != -1) {
                            mine_matrix[neighbor]++;
                        }
                    }
                }
            }
        }
    }
}


// Рекурсивное открытие клеток
// Возвращает количество новых открытых клеток
int open(int razryad, int *open_matrix, int *mine_matrix, int row, int col) {
    if (row < 0 || row >= razryad ||
        col < 0 || col >= razryad) {
        return 0;
    }

    int cel = row * razryad + col;

    // 0 - закрыто, 1 - открыто, 2 - флажок
    if (open_matrix[cel] != 0 || mine_matrix[cel] == -1) {
        return 0;
    }

    open_matrix[cel] = 1;
    int opened = 1;

    if (mine_matrix[cel] == 0) {
        for (int j = -1; j <= 1; j++) {
            for (int k = -1; k <= 1; k++) {
                if (j == 0 && k == 0) continue;

                opened += open(razryad, open_matrix, mine_matrix,
                               row + j, col + k);
            }
        }
    }

    return opened;
}


// Вывод видимого поля
void print_field(int razryad, int *open_matrix, int *mine_matrix, int show_mines) {
    printf("\n    ");

    for (int j = 0; j < razryad; j++) {
        printf("%3d", j);
    }
    printf("\n");

    for (int i = 0; i < razryad; i++) {
        printf("%3d ", i);

        for (int j = 0; j < razryad; j++) {
            int cel = i * razryad + j;

            if (show_mines && mine_matrix[cel] == -1) {
                printf("%3c", '*');
            }
            else if (open_matrix[cel] == 2) {
                printf("%3c", 'F');
            }
            else if (open_matrix[cel] == 0) {
                printf("%3c", '.');
            }
            else if (mine_matrix[cel] == 0) {
                printf("%3c", ' ');
            }
            else {
                printf("%3d", mine_matrix[cel]);
            }
        }
        printf("\n");
    }
}


// Основной игровой цикл
void hod(int razryad, int *open_matrix, int *mine_matrix,
         int mines_count, int opened) {

    int gameover = 0;
    int win = 0;
    int flags = 0;
    int cells = razryad * razryad;

    while (gameover == 0 && win == 0) {
        print_field(razryad, open_matrix, mine_matrix, 0);

        printf("\nOtkryto: %d | Flags: %d | Mines left: %d\n",
               opened, flags, mines_count - flags);

        if (opened == cells - mines_count) {
            win = 1;
            break;
        }

        int klet[2];
        char action;

        printf("\nAction (o - open, f - flag), row, col: ");

        if (scanf(" %c %d %d", &action, &klet[0], &klet[1]) != 3) {
            printf("Input error\n");
            return;
        }

        if (klet[0] < 0 || klet[0] >= razryad ||
            klet[1] < 0 || klet[1] >= razryad) {
            printf("Wrong coordinates!\n");
            continue;
        }

        int cel = klet[0] * razryad + klet[1];

        if (action == 'f' || action == 'F') {
            if (open_matrix[cel] == 1) {
                printf("Cell already opened!\n");
            }
            else if (open_matrix[cel] == 2) {
                open_matrix[cel] = 0;
                flags--;
            }
            else if (flags < mines_count) {
                open_matrix[cel] = 2;
                flags++;
            }
            else {
                printf("No flags left!\n");
            }
        }
        else if (action == 'o' || action == 'O') {
            if (open_matrix[cel] == 2) {
                printf("Remove flag first!\n");
                continue;
            }

            if (open_matrix[cel] == 1) {
                printf("Cell already opened!\n");
                continue;
            }

            if (mine_matrix[cel] == -1) {
                gameover = 1;
            }
            else {
                opened += open(razryad, open_matrix, mine_matrix,
                               klet[0], klet[1]);
            }
        }
        else {
            printf("Unknown action!\n");
            continue;
        }

        if (opened == cells - mines_count) {
            win = 1;
        }
    }

    print_field(razryad, open_matrix, mine_matrix, gameover);

    if (gameover == 1) {
        printf("\nGAME OVER! MINA!\n");
    }
    else if (win == 1) {
        printf("\nYOU WIN!\n");
    }

    printf("\n--- STATISTICS ---\n");
    printf("Opened cells: %d\n", opened);
    printf("Flags placed: %d\n", flags);
    printf("Mines left (counter): %d\n", mines_count - flags);
}


int main() {
    srand((unsigned int)time(NULL));

    int razryad;
    int mines_count;

    printf("Skolko pole? Kolichestvo min? ");

    if (scanf("%d %d", &razryad, &mines_count) != 2) {
        printf("Input error\n");
        return 1;
    }

    if (razryad <= 0 || razryad > 100 ||
        mines_count < 0 ||
        mines_count >= razryad * razryad) {
        printf("Nekorrectnye znacheniya\n");
        return 1;
    }

    int *open_matrix = calloc((size_t)razryad * razryad,
                              sizeof *open_matrix);

    int *mine_matrix = calloc((size_t)razryad * razryad,
                              sizeof *mine_matrix);

    if (mine_matrix == NULL || open_matrix == NULL) {
        printf("No memory\n");
        free(mine_matrix);
        free(open_matrix);
        return 1;
    }

    int first_cell[2];

    printf("Pervyi hod (row col): ");

    if (scanf("%d %d", &first_cell[0], &first_cell[1]) != 2 ||
        first_cell[0] < 0 || first_cell[0] >= razryad ||
        first_cell[1] < 0 || first_cell[1] >= razryad) {

        printf("Wrong coordinates!\n");
        free(mine_matrix);
        free(open_matrix);
        return 1;
    }

    // Мины появляются только после выбора первой клетки
    mines(razryad, mine_matrix, mines_count, first_cell);

    // Открываем первую безопасную клетку
    int opened = open(razryad, open_matrix, mine_matrix,
                      first_cell[0], first_cell[1]);

    hod(razryad, open_matrix, mine_matrix, mines_count, opened);

    free(open_matrix);
    free(mine_matrix);

    return 0;
}
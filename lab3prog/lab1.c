#include <stdio.h>
#include<stdlib.h>
// int main() {
//     int kolv=0;
//     int a = 0;
//     printf("введите chislo");
//     scanf("%d", &kolv);
//     for(int i = 0; i<kolv; i++ ) {
//         for(int j = 0; j < kolv; j++) {
//             a++;
//             printf("%d ",a);
//         }
// 	    printf("\n");
// 	}
//     return 0;
// }
int main() {
int a[] = {3, 8, 12, 17, 25};
int *p = a + 1;

printf("%d %d %td\n", *p, p[2], p - a);

(*p)++;
p++;

printf("%d %d\n", a[1], *p);
return 0;
}
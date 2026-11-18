#include<stdio.h>

// int sdvig(int a , int k){
//     for(int i =0; i<k;i++) {
//         a = a <<1;

//     }
//     return a;
// }

// int main(){
//     int a, k = 0;
//     printf("vvedite chisla");
//     scanf("%d",&a);
//     scanf("%d",&k);
//     int a1 = sdvig(a, k);
//     printf("sdvinutoe: %d",a1)
//     return 0;
// }

int kolv(int a){
    int k =0;
    a = a>>2;
    for(int j = 0; j <11;j++) {
        if((a & 1) == 0) {
            k++;
        }
        a = a>>1;
    }

    return k;
}

int main() {
    int a = 0;
    printf("vvedite chislo");
    scanf("%d", &a);
    int k = kolv(a);
    printf("Kolichestvo nuley: %d\n", k);
return 0;
}
    
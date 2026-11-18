// #include<stdio.h>
// #include<stdlib.h>
// #include<time.h>

// int main(){
//     srand(time(NULL));
//     int temp[12] = {0};
//     int summa = 0;
//     for(int i =0 ; i<12;i++) {
//         temp[i] = -40 + (rand() % (30+40+1));
//     }
//     for(int j = 0; j<12; j++){
//         printf("temp[%d] = %d\n", j ,temp[j]);
//         summa += temp[j];
//     }
//     int max = -60;
//     int min = 70;
//     for(int i =0 ; i<12;i++) {
//         if(max <= temp[i]) {
//             max = temp[i];
//         }
//         if(min >= temp[i]) {
//             min = temp[i];
//         }
//     }
//     float srednee = (float)summa / 12;
//     printf("summa = %d\n srednee = %.2f\n max = %d , min = %d\n", summa, srednee, max , min);
//     return 0;
// }













// #include<stdio.h>
// #include<stdlib.h>
// #include<time.h>
// int main(){
//     srand(time(NULL));
//     int n = 0;
//     int indmax = 0;
//     float energy = 0;
//     int minim = -32768;
//     int maxim = 32767;
//     printf("vvedide kolv");
//     scanf("%d", &n);
//     float masse[n*2];
//     for(int j = 0; j<n*2; j++){
//         masse[j] = minim + (rand() % (maxim - minim +1));
//         }
//     float max = masse[0];
//     for (int i = 0; i<n ; i++) {
//         printf("masse[%d] = %.2f + %.2f *i\n",i , masse[2*i], masse[2*i+1]);
//         energy += masse[i*2] * masse[i*2] + masse[i*2+1] * masse[i*2];
//         if (max<masse[i*2]){
//             max = masse[i*2];
//             indmax = i;
//         }
//     }
//     printf("energy = %.2f\n max = %.2f index = %d",energy, max, indmax );
//     return 0;

// }
 

#include<stdio.h>
#include<stdlib.h>

float spokoin(int n, int summa){
    float spokoinoe = (float)(n - summa) / n * 100;
    return spokoinoe;
}


int main(){
    int rssi[12] = {60, 59, 61, 58, 70, 74,
                    68, 57, 58, 62, 75, 71};

    int n = 12;
    int nachalo[12];
    int konec[12];
    int kolv = 0;
    int summa = 0;
    int maxdlina = 0;
    int indmax = 0;
    int aktiv = 0;
    int tekNachalo = 0;

    for(int i = 1; i < n; i++){
        int razn = abs(rssi[i] - rssi[i-1]);
        printf("razn[%d] = %d\n", i, razn);
        if(aktiv == 0 && razn > 5){
            aktiv = 1;
            tekNachalo = i;
        }
        if(aktiv == 1 && razn <= 5){
            nachalo[kolv] = tekNachalo;
            konec[kolv] = i;
            int dlina = konec[kolv] - nachalo[kolv];
            summa += dlina;
            if(maxdlina < dlina){
                maxdlina = dlina;
                indmax = kolv;
            }
            kolv++;
            aktiv = 0;
        }
    }
    if(aktiv == 1){
        nachalo[kolv] = tekNachalo;
        konec[kolv] = n - 1;
        int dlina = konec[kolv] - nachalo[kolv];
        summa += dlina;
        if(maxdlina < dlina){
            maxdlina = dlina;
            indmax = kolv;
        }
        kolv++;
    }
    printf("\nIntervaly aktivnosti:\n");
    for(int i = 0; i < kolv; i++){
        printf("%d: nachalo = %d, konec = %d, dlina = %d sec\n",
               i + 1, nachalo[i], konec[i],
               konec[i] - nachalo[i]);
    }
    printf("\nKolichestvo intervalov = %d\n", kolv);
    printf("Summa dlitelnosti = %d sec\n", summa);
    if(kolv > 0){
        printf("Samiy dlinniy interval: nachalo = %d, konec = %d\n",
               nachalo[indmax], konec[indmax]);
        printf("Ego dlitelnost = %d sec\n", maxdlina);
    }
    
    printf("Spokoinoe vremya = %.2f%%\n", spokoin(n, summa));
    
    return 0;
}
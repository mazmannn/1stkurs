#include<stdio.h>

int main() {
int n = 0;

printf("vvedite chislo");
scanf("%d", &n);
int v = n;
int v1 = n;
for(int i = 0; i<n; i+=2) {
	while(v>0){
		printf("o");
		v-=1;
		}
	printf("\n");
	}
for(int j = n ; j>0; j -=2) {
	while(j>0){
	printf("o");
	v1-=1;
		}
	printf("\n");
	}
return 0;
}

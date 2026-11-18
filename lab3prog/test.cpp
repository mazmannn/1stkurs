#include<iostream>
#include<climits>



int add_sub(int a, int b, int c) {
 int result;
 __asm__ (
 "movl %2, %%eax;" // a -> eax
 "addl %1, %%eax;" // eax += b
 "subl %3, %%eax;" // eax -= c
 : "=a" (result) // выход: результат в eax
 : "b" (b), "c" (a), "d" (c) // входные в регистры
 : "cc" // изменяем флаги
 );
 return result;
}

int main(){
    int a;
    int b;
    int c;
    scanf("vvod 3 %d %d %d", &a, &b, &c);
    printf("ADD = ", add_sub(a,b,c));
    return 0;
}
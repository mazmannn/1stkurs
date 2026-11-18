#include <stdio.h>
void bin(int dec) {


	for(int i = sizeof(dec)*8 -1; i >=0; i--) { 
		print("%d", (dec & (1<<i))>>i

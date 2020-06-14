#include <stdio.h>

int s();
int main(){

int s2 = s();
printf("suma podanych liczb to: ");
printf("%d", s2);}

int s(){
int x, y, s;
printf("Podaj pierwsza liczbe: ");
scanf("%d", &x);
printf("Podaj druga liczbe: ");
scanf("%d", &y);
s=(x+y);
return s; }
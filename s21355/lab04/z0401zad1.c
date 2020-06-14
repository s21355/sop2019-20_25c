#include <stdio.h>
#include <stdlib.h>
 
 
typedef int (*f)(int, int);
int dodawanie(int,int);
int max(int, int);
int min(int, int);
 
int main(int argc, char** argv){
    int x=atoi(argv[1]);
    int y=atoi(argv[2]);
    int odp=0;
    f functions[]={min, max, dodawanie};
    printf("Co chcesz wykonac?\n1. minimalna liczba\n2. maksymalna liczba\n3. dodawanie\n");
    scanf("%d", &odp);
    printf("wybrano %d\n", odp);
    if(odp==1){
        min(x,y);
    }
    if(odp==2){
        max(x,y);
    }
    if(odp==3){
        dodawanie(x,y);
    }
}
int dodawanie(int p,int d){
    int x = p+d;
    printf("%d + %d = %d\n", p, d, x);
}
int max(int p, int d){
   
    if(p>d){
        printf("max to = %d\n", p);
    }else{
        printf("max to = %d\n", d);
    }
}
int min(int p, int d){
   
    if(p>d){
        printf("min to = %d\n", d);
    }else{
        printf("min to = %d\n", p);
    }
}
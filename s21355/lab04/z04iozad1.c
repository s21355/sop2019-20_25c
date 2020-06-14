#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv){
	FILE *f;
	long int i;
	int cnt;
	char nazwa[25];
	if(argc>1){
		strcpy(nazwa, argv[1]);
		
	}else{
		printf("Enter name of a file you wish to see: ");
   		gets(nazwa);
	}
	f= fopen(nazwa,"r");
	fseek( f, 0, SEEK_END );
	cnt=ftell(f);
	while(i<cnt){
		fseek(f, -i, SEEK_END);
		if(feof(f)){
			break;
		}
		printf("%c",fgetc(f));
		i++;
	}
	fclose(f);
	 
	return 0;
}
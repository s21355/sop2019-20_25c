#include <iostream>
#include <stdlib.h>

void printArgs(int, char**);
int parseInput(int, char**);
void tree(int);
void printPaddingForRow(int, int);
void printTreeForRow(int);

int main(int argc, char** argv) {
	int lines = parseInput(argc, argv);
	if (lines <1) {
	return lines;
	}

	tree(lines);
	
	return 0;
}

int parseInput(int argc, char** argv) {
	if (argc !=2) {
	return -1;
	}

	int lines = atoi(argv[1]);
	return lines;
}

void tree(int lines) {
	for(int row = 1; row <= lines; row++) {
	printPaddingForRow(row, lines);
	printTreeForRow(row);
	printf("\n");
	}
}

void printPaddingForRow(int row, int totalRows) {
	for(int i = 0; i < totalRows - row; i++){
	printf(" ");
	}
}
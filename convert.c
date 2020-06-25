/*
 * Name: Jessica Stillwell, Haylee Rawdin
 * Description: This program converts decimal to either binary or hexadecimal
*/
#include <stdio.h>

/* Main
 * argc, argv 	Command line arguments.
 * return	zero for success, non-zero for failure
 *
 * This is the min entry point for the program.
*/

int read_decimal (void);
int main (int argc, char* argv[]) {
    if((argc != 2) || (argv[1] != "-x") || (argv[1] != "-b")){
        printf("Usage: ./convert [-x|-b]");
        break;
    }else if (argv[1] == "-x"){
        printf("%s\n", argv[1]);
    }else if (argv[1] == "-b"){
        printf("%s\n", arg[1]);
    }
    
    int i;
    for(i=0; i < argc; i++){
        printf("%s/n", argv[i])
    }
 printf("%d\n", read_decimal());
 return 0;
}

int read_decimal (void){
 int decimal;
 scanf("%d" , &decimal);
 return (decimal);
}

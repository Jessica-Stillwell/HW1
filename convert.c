/*
 * Name: Jessica Stillwell, Haylee Rawdin
 * Description: This program converts decimal to either binary or hexadecimal
*/
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>

/* Main
 * argc, argv 	Command line arguments.
 * return	zero for success, non-zero for failure
 *
 * This is the min entry point for the program.
*/

int read_decimal (void);
int main (int argc, char* argv[]) {
    if(argc == 2){
        int x = strncmp(argv[1], "-x", 3);
        int b = strncmp(argv[1], "-b", 3);
        if(x==0){
            printf("%s\n", argv[1]);
        }else if(b==0){
            printf("%s\n", argv[1]);
        }else{
            printf("Usage: ./convert [-x|-b]\n");
            exit(0);
        }
    }else if(argc != 2){
        printf("Usage: ./convert [-x|-b]\n");
        exit(0);
    }
 printf("%d\n", read_decimal());
 return 0;
}

int read_decimal (void){
 int decimal;
 scanf("%d" , &decimal);
 return (decimal);
}

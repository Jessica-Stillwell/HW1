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
void convertToBinary(int);

int main (int argc, char* argv[]) {
    if(argc == 2){
        int x = strncmp(argv[1], "-x", 3);
        int b = strncmp(argv[1], "-b", 3);
        if(x==0){
            printf("%s\n", argv[1]);
        }else if(b==0){
            int decimal=read_decimal();
            while (decimal != EOF){
                convertToBinary(decimal);
                decimal=read_decimal();
                }
            exit(0);
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
    int input=scanf("%d" , &decimal);
    if (input==EOF){
        printf("^D\n");
        return(EOF);
        }
    else{
        return (decimal);
    }
}

void convertToBinary(int dec){
    int binaryArr[16];
    int i=0;
    while (dec!=0){
        int rem = dec%2;
        binaryArr[i]=rem;
        dec = dec/2;
        i++;
    }
    int v=i-1;
    for (int j=i-1; j>=0; j--){
        printf("%d", binaryArr[j]);
        if (v%4==0){
            printf(" ");
        }
        v--;
    }
    printf("\n");
}

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
void decToHex(int dec);

int main (int argc, char* argv[]) {
    int decimal;
    if(argc == 2){
        int x = strncmp(argv[1], "-x", 3);
        int b = strncmp(argv[1], "-b", 3);
        if(x==0){
            decimal = read_decimal();
            while (decimal != EOF) {
                decToHex(decimal);
                decimal = read_decimal();
            }
            exit(0);
        }else if(b==0){
            decimal = read_decimal();
            while (decimal != EOF){
                convertToBinary(decimal);
                decimal = read_decimal();
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

void decToHex(int dec){
    int remainder;
    int i =0;
    char hexArr[100];
    while(dec != 0){
        remainder = dec % 16;
        if(remainder < 10){
            hexArr[i] = remainder + 48;
            i++;
        }else{
            hexArr[i] = remainder + 55;
            i++;
        }
        dec=dec/16;
    }
    int j;
    printf("0x");
    for( j = i-1; j >= 0; j--){
        printf("%c", hexArr[j]);
    }
    printf("\n");
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
    for (i=i-1; i>=0; i--){
        printf("%d", binaryArr[i]);
        if (i%4==0){
            printf(" ");
        }
    }
    printf("\n");
}

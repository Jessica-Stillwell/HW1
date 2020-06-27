/*
 * Name: Jessica Stillwell, Haylee Rawdin
 * Description: This program converts decimal to either binary or hexadecimal
*/
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>

/* Declaring functions */
int read_decimal (void);
void decToBinary(int);
void decToHex(int dec);

/* Main
 * argc, argv   Command line arguments.
 * return   zero for success, non-zero for failure
 *
 * This is the main entry point for the program.
*/
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
                decToBinary(decimal);
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

/* Read Decimal
 * Purpose: This function reads an input decimal from stdin.
 * Returns: An int value representing a decimal, collected from scanf.
*/
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

/* decToHex
 * Purpose: This function converts a decimal value and to its hexadecimal value.
 * Parameters:
 *  int dec: this int parameter represents the decimal to be converted to hexadecimal
 * Result: A printed hexadecimal value.
 */
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

/* decToBinary
 * Purpose: This function converts a decimal value to its binary value.
 * Parameters:
 *  int dec: this int parameter represents the decimal to be converted to binary
 * Result: A binary value.
 */
void decToBinary(int dec){
    int binaryArr[100];
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

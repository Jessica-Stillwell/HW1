/*
 *
 * Name: Jessica Stillwell, Haylee Rawdin
 * User ID: stillwj3, rawdinh
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution by editing the collection of functions below.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  /* brief description of how your implementation works */
  int Funct(arg1, arg2, ...) {
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   *
   * exploit ability of shifts to compute powers of 2
   */
  int pow2plus1(int x) {
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   *
   * exploit ability of shifts to compute powers of 2
   */
  int pow2plus4(int x) {
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function.
     The max operator count is checked by dlc. Note that '=' is not
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */


#endif
/*
 * bitAnd - x&y using only ~ and |
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 *   Hint : less than 5 lines of code
 *
 * This function ors a not(x) and not(y), and then performs not on this output to get
 * the desired & output between x and y.
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}
/*
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 *   Hint : less than 5 lines of code
 *
 * Shifting n to the left by three, means x will be shifted right by the amount of bits
 * in n bytes. Masking with 0xFF returns only the requested 8 bits' value.
 */
int getByte(int x, int n) {
  return (x>>(n<<3)) & 0xFF;
}
/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 *   Hint : less than 10 lines of code
 */
 /* Shifts x to the right by n and then masks the leftmost n-1 bits with 0s so that
    it returns the logical shift.
*/
int logicalShift(int x, int n) {
  return (x >> n) & ~((1<<31 >> n) << 1);
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 *   Hint : less than 10 lines of code
 *
 * This function masks every first bit per group of 4 bits, and shifts until reaching the 4th bit.
 * These masked values are added. This totals the one's in each 4 bit group.
 * Then this new str is shifted by four until each group of four bits is examined.
 * Masking each 4 bit grouping with 15 evaluates 4 bits at a time, and adding them returns the total 1s.
 */
int bitCount(int x) {
    int mask = (17 | (17<<8) | (17<<16) | (17<<24));
    int bits4 = (x&mask) + ((x>>1)&mask) + ((x>>2)&mask) + ((x>>3)&mask);
    int bytes12 = (bits4 & 15)+((bits4>>4) & 15)+((bits4>>8) & 15)+((bits4>>12) & 15);
    int bytes34 = ((bits4>>16) & 15)+((bits4>>20) & 15)+((bits4>>24) & 15)+((bits4>>28) & 15);
    int total = bytes12 + bytes34;

  return total;
}
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 *   Hint : less than 5 lines of code
 *
 * This function shifts 1 to the MSB followed by 0s.
 */
int tmin(void) {
  return 1<<31;
}
/*
 * fitsBits - return 1 if x can be represented as an
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 *   Hint : less than 5 lines of code
 *
 * Shift x so that all bits which cannot fit in the new n bit size, are removed.
 * Then check if x and y (x shifted to be n bits) are equal.
 */
int fitsBits(int x, int n) {
    int y = (x<<(32+(~n+1)))>>(32+(~n+1));
    return !(x^y);
}
/*
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 *   Hint : less than 5 lines of code
 */
 /* Checks to see if the sign bit of x is 1. If x is negative, 1 needs to be added to x so that it
    rounds towards 0. Shifting 1 to the left by n and adding this to x>>31 creates a mask with 1s in 
    the rightmost n-1 bits. When this is added to x and shifted right n bits it is equivalent to x/(2^n) 
    rounded towards zero
*/
int divpwr2(int x, int n) {
    int i=(x>>31);
    return(x+(((i&1)<<n)+i))>>n;
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 *   Hint : less than 5 lines of code
 */
 /* Returns -x by flipping the bits of x then adding 1 
 */
int negate(int x) {
  return (~x+1);
}
/*
 * isPositive - return 1 if x > 0, return 0 otherwise
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 *   Hint : less than 5 lines of code
 */
 /* If sign bit & 1 equals 1 then x is negative, returns 0. If x is 0 then this will return 1, so 
    there is an additional check, !x, using xor. If x is 0 then 1^1 returns 0.
 */
int isPositive(int x) {
  return !(1&(x>>31)) ^ !x;
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 *   Hint : less than 100 lines of code
 *
 * Shifting x and the | with x, all bits to the right of the highest set bit are 1s...
 * then shift one so the total ones counts the index of the highest set bit.
 */
int ilog2(int x) {
    int msk;
    int bits;
    int bytes12;
    int bytes34
    x = x | (x >>  1);
    x = x | (x >>  2);
    x = x | (x >>  4);
    x = x | (x >>  8);
    x = x | (x >> 16);
    x = x >> 1;
    msk = (17 | (17<<8) | (17<<16) | (17<<24));
    bits = (x&msk) + ((x>>1)&msk) + ((x>>2)&msk) + ((x>>3)&msk);
    bytes12 = (bits & 15)+((bits>>4) & 15)+((bits>>8) & 15)+((bits>>12) & 15);
    bytes34 = ((bits>>16) & 15)+((bits>>20) & 15)+((bits>>24) & 15)+((bits>>28) & 15);
  
    return bytes34 + bytes12;
}
/*
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 *   Hint : less than 10 lines of code
 */
 /* Changes sign of x using xor. Ex: if x is positive then 0^1 returns x with a 1 in the sign bit, -x. 
    If exponent bits are all 1s and frac is nonzero then x is not a NaN. Checks the exponent bits using
    a mask of 8 1s. If NaN, returns uf.
 */
unsigned float_neg(unsigned uf) {
  unsigned ex=(uf<<1)>>24;
  unsigned frac=uf<<9;

  if (!(ex^0xff) && frac){
    return uf;
  }
  return uf^(1<<31);
}
/*
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 *   Hint : less than 20 lines of code
 */
 /* Adding 1 to the exponent is equivalent to multiplying by 2. To do this, 1<<23 is added to uf to
    add only to the portion with the exponent bits. If exponents are all 0s then shifting uf to the 
    left by 1 is equivalent to multiplying by 2. Once it is shifted, the sign bit is added back in.
    If exponent is all 1s, then NaN or infinity, returns uf. 
*/
unsigned float_twice(unsigned uf) {
  unsigned ex=(uf<<1)>>24;

  if (!(ex^0x00)){
    return (uf<<1)+(uf&(1<<31));
  }

  if (!(ex^0xff)){
    return uf;
  }

  return uf +(1<<23);
}

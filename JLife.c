/*
 * Name: Jessica Stillwell, Haylee Rawdin
 * Description: This program creates the boards for each generation in
 * the Game of Life by counting the neighbors of a cell. 
 * Changes: We removed the neighbors function, partially unrolled the for loops,
 * and evaluated corners first then broke the board into chunks. 
*/
/* This is a cellular automation simulator.  The rules are very
 * simple.  The board is a grid.  Each grid square can hold at most
 * one cell.  For a cell to survive from generation to generation it
 * needs two or three neighbors.  Too many neighbors causes the cell
 * to starve.  Too few causes an incurable case of ennui.  All is not
 * lost.  If a grid square has exactly three neighbors, a new cell is
 * born, which is kind of strange when you think about it.
 *
 * There are lots of variations on this game.  Technically, this is Conway's
 * Game of Life and is a B3/S23 game.  That is, cells survive with two or three
 * neighbors and are born with exactly 3 neighbors.  This game can also be
 * extended into the real domain or more diminutions.  We, however, with stick
 * with Conway's original automation.
 *
 * Below is a very simple implementation.  This is your chance to apply some of
 * the loop optimization techniques we've been talking about in class:
 *  1) Remove loop inefficiencies
 *  2) Reduce procedure calls
 *  3) Reduce unnecessary memory references
 *  4) Loop unrolling
 * There are, of course, more optimizations that you can apply.  For example,
 * moving sequentially through memory is more efficient than jumping around.
 * We'll see why in Chapter 9.
 * C stores 2D arrays Column Major Order.  That is to say that cell
 * A[0][WIDTH-1] is right next to A[1][0] in memory.  If you notice the nested
 * loops in evolve (below) I'm incrementing the column index, i, more quickly
 * than the row index, j.  Try reversing these and see what happens.
 *
 * The experimental set-up is implemented in a library called liblife.a  Since
 * it has solutions, it is providing it as a binary in:
 *
 *   /home/jagodzf/lib/liblife.a
 *
 * The provided make file links to this library.
 *
 * There are three ways to run the test program: with a window (full
 * GUI), silently, or lazy GUI. Without a window (silent), the program
 * runs the test cases against the provided evolution methods as
 * quickly as possible.  After about 500 generations, it stops and
 * reports the average performance of each method.
 *
 * The following flags are available
 *
 * silent mode (default)
 * -lg : lazy GUI
 * -fg : full GUI
 *
 * See how fast you can make your code.
 *
 * You are free to add as many test methods as you want.  You are
 * encouraged to do this.  Copy the code, give it a new name, and
 * add it to the library's suite of methods.  This way you can really
 * see if you are making improvements.  Have fun.
 *
 */

#include "liblife.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define ALIVE(n,b) (n==3) | (b & (n==2))
int printLazy=0;
int generation=0;
/* Simple Life evolution.  These functions implement Conway's game of
 * life rules.  Your millage may vary, void where prohibited.
 */
/*static int max(int x, int y) {
   return x < y ? y : x;
}*/

/* Neighbors: Given the board b, this function counts the number of
 * neighbors of cell-(i,j).
 *
 * This implementation over-counts the neighborhood.  The loop counts the
 * cell-(i,j) and then subtracts off one if it is alive.
 *
 * The use of min and max ensure that the neighborhood is truncated at the edges
 * of the board.
 */
/*static int neighbors (board b, register unsigned int i, register unsigned int j)
{
  return b[i][j+1]+b[i][j-1]+b[i-1][j]+b[i-1][j+1]+b[i-1][j-1]+b[i+1][j]+b[i+1][j+1]+b[i+1][j-1];
}*/

/* lazyPrint: A not-too-elegant print function that prints the
 * upper-left 10 x 10 cells of the simulation board, and sleeps for 1
 * second.
 */
void lazyPrint(board prv){
  int i =9;
  while(i--){
    printf("%d",prv[i][0]);
    printf("%d",prv[i][1]);
    printf("%d",prv[i][2]);
    printf("%d",prv[i][3]);
    printf("%d",prv[i][4]);
    printf("%d",prv[i][5]);
    printf("%d",prv[i][6]);
    printf("%d",prv[i][7]);
    printf("%d",prv[i][8]);
    printf("%d",prv[i][9]);

    printf("\n");
  }
  printf("\n");

  //sleep 1 seconds
  unsigned int time_to_sleep = 1;
  while(time_to_sleep){
    time_to_sleep = sleep(time_to_sleep);
  }
}

/* Evolve: This is a very simple evolution function.  It applies the
 * rules of Conway's Game of Live as written.  There are a lot of
 * improvements that you can make.  Good luck beating Ada, she is
 * really good.
 */
void evolve(board prv, board nxt){
  
   register int i, j, n;
   printf("\rGeneration %d\n", generation++);
   if (printLazy){
     lazyPrint(prv);
   }

   n = prv[0][1]+prv[1][0]+prv[1][1];
   nxt[0][0]= (n==3) | (prv[0][0] & (n==2));

   n = prv[0][WIDTH-2]+prv[1][WIDTH-2]+prv[1][WIDTH-1];
   nxt[0][WIDTH-1]=(n==3) | (prv[0][WIDTH-1] & (n==2));

   n = prv[HEIGHT-2][0]+prv[HEIGHT-2][1]+prv[HEIGHT-1][1];
   nxt[HEIGHT-1][0]=ALIVE(n,prv[HEIGHT-1][0]);

   n = prv[HEIGHT-2][WIDTH-2]+prv[HEIGHT-2][WIDTH-1]+prv[HEIGHT-1][WIDTH-2];
   nxt[HEIGHT-1][WIDTH-1]=ALIVE(n,prv[HEIGHT-1][WIDTH-1]);

   for (j=1; j<WIDTH-1; ++j){
      n = prv[0][j-1]+prv[0][j+1]+prv[1][j-1]+prv[1][j]+prv[1][j+1];
      nxt[0][j]=(n==3) | (prv[0][j] & (n==2));
      n = prv[HEIGHT-2][j-1]+prv[HEIGHT-2][j]+prv[HEIGHT-2][j+1]+prv[HEIGHT-1][j-1]+prv[HEIGHT-1][j+1];
      nxt[HEIGHT-1][j]=(n==3) | (prv[HEIGHT-1][j] & (n==2));
   }
   for (i=1; i<HEIGHT-1; ++i){
      n = prv[i-1][0]+prv[i-1][1]+prv[i][1]+prv[i+1][0]+prv[i+1][1];
      nxt[i][0]=(n==3) | (prv[i][0] & (n==2));
      n = prv[i-1][WIDTH-2]+prv[i-1][WIDTH-1]+prv[i][WIDTH-2]+prv[i+1][WIDTH-2]+prv[i+1][WIDTH-1];
      nxt[i][WIDTH-1]=(prv[i][WIDTH-1] & (n==2)) | (n==3);
   }

   for (i=HEIGHT-2; i>0; --i) {
      for (j=WIDTH-2; j>0; --j) {
         n = prv[i-1][j-1]+prv[i-1][j]+prv[i-1][j+1]+prv[i][j-1]+prv[i][j+1]+prv[i+1][j-1]+prv[i+1][j]+prv[i+1][j+1];
         nxt[i][j] = (prv[i][j] & (n==2)) | (n==3);
      }
   }

}


/* The program takes one optional arugment: -fg (full GUI) or -lg
 * (lazy GUI).  The default (no option) tells the program to skip the
 * GUI components (in other words run silently), while lg tells the
 * program to print to the screen the left-most 10 x 10 cells of the
 * board using a "text-only" (hence lazy) GUI. The silent mode is much
 * more stable than the fg mode and what will be used measure your
 * code's performance.
 */
int main(int argc, char* argv[]){

  // mode 1 : invalid number of arguments specified
  // mode 2 : -fg full GUI mode
  // mode 3 : -lg (lazy gui) console print GUI mode
  // mode 4 : silent (default)
  
  if (argc > 2 ){
    fprintf(stderr, "Usage: %s [-fg or -lg]\n\t-fg Full GUID\n\t-lg Lazy GUI Mode\n", argv[0]);
    return EXIT_FAILURE;
  } else if ((argc == 2 && 0 == strcmp (argv[1], "-lg"))) {
    printf("Running in -lg (Lazy GUI) mode\n");
    printLazy += 1;
    add_method("stillwj3", &evolve);
    run_game(1);
  } else if ((argc == 2 && 0 == strcmp (argv[1], "-fg"))) {
    printf("Running in GUI mode\n");
    add_method("stillwj3", &evolve);
    run_game(0);
  } else if ((argc == 2 && (1 != strcmp (argv[1], "-fg") || 1 != strcmp (argv[1], "-lg")))) {
    fprintf(stderr, "Usage: %s [-fg or -lg]\n\t-fg Full GUID\n\t-lg Lazy GUI Mode\n", argv[0]);
    return EXIT_FAILURE;
  } else {
    printf("Running in silent (no GUI window) mode\n");
    add_method("stillwj3", &evolve);
    run_game(1);
  }
  return 0;
}



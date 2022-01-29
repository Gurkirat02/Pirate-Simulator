#include "defs.h"

/*
  Function:  main.c
  Purpose:   To output the interface which has the table of statstics from the simulation
   Author:   Gurkirat Singh Dhatt
    Usage:   241,722 bytes 
Revisions:   Only one major revision done from Decemeber 5-December 12, 2021
*/


void printStat(StatsType** stats, int total){
  printf("+-----------------------------------------------------------------------------------------------+\n");
  printf("|    Hero with Sword \t|\t%%Success\t|\t%%Partial\t|\t%%Failure\t|\n");
  printf("+-----------------------------------------------------------------------------------------------+\n");
  printf("|\tTortoise\t|\t    %d\t\t|\t    %d\t\t|\t    %d\t\t|\n",(stats[0]->numSuccess*100)/total,(stats[0]->numPartSuccess*100)/total, (stats[0]->numFailure*100)/total);
  printf("+-----------------------------------------------------------------------------------------------+\n");
  printf("|\t   Hare\t\t|\t    %d\t\t|\t    %d\t\t|\t    %d\t\t|\n",(stats[1]->numSuccess*100)/total,(stats[1]->numPartSuccess*100)/total, (stats[1]->numFailure*100)/total);
  printf("+-----------------------------------------------------------------------------------------------+\n");
  printf("|\t   None\t\t|\t    %d\t\t|\t    %d\t\t|\t    %d\t\t|\n",(stats[2]->numSuccess*100)/total,(stats[2]->numPartSuccess*100)/total, (stats[2]->numFailure*100)/total);
  printf("+-----------------------------------------------------------------------------------------------+\n");
}

int main(int argc, char *argv[])
{
  // Section 4.1.1
  int total_runs;
  if (argc > 1)
    sscanf(argv[1], "%d", &total_runs);
  else
    total_runs = NUM_RUNS;

  // Section 4.1.2 (a)
  srand( (unsigned)time( NULL ) );

  // declare StatsType* to use for all runs
  StatsType** stats = malloc(NUM_SCENARIOS* sizeof(*stats));;
  for(int i=0; i<NUM_SCENARIOS;i++){
    stats[i] = malloc(sizeof(*stats[i]));
    stats[i]->numFailure = 0;
    stats[i]->numSuccess = 0;
    stats[i]->numPartSuccess = 0;
  }

  for(int i=0; i<total_runs; i++){
    // printf("%d",i);
    executeRun(stats, i+1);
  }

  printStat(stats, total_runs);
  printf("\nTotal Runs : %d\n",total_runs);

  for(int i=0; i<NUM_SCENARIOS;i++){
    free(stats[i]);
  }
  free(stats);
  
  return 0;
}

/*
  Function:  randm
  Purpose:   returns a pseudo randomly generated number, 
             in the range 0 to (max - 1), inclusively
       in:   upper end of the range of the generated number
   return:   randomly generated integer in the range [0, max-1) 
*/
int randm(int max)
{
  double r = ( (double)rand() / ((double)(RAND_MAX)+(double)(1)) ); 

  return (int)(r * max);
}


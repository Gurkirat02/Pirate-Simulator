#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_RUNS       100
#define NUM_PIRATES     10
#define NUM_SCENARIOS    3

#define TORT_STRENGTH    5
#define TORT_ARMOUR      8
#define HARE_STRENGTH    8
#define HARE_ARMOUR      5
#define HERO_HEALTH     20
#define PIRATE_HEALTH   10
#define SWORD_STRENGTH   2

#define MAX_STR         64

typedef enum { SUCCESS, FAILURE, PART_SUCCESS, RES_UNKNOWN } ResultType;
typedef enum { FRONT, BACK } DirectionType;

typedef struct {	// Stats for one scenario, accumulated over all runs
  int numSuccess;
  int numPartSuccess;
  int numFailure;
} StatsType;

typedef struct {	// One fighter:  Tortoise, Hare, or Pirate
  int  strength;
  int  armour;
  int  health;
} FighterType;

typedef struct Node {
  FighterType  *data;
  struct Node  *next;
} NodeType;

typedef struct {	// Stores the fighting pirates for one scenario
  NodeType *head;
  NodeType *tail;
} DequeType;

typedef struct {	// Specs for one scenario of one run
  DequeType   *pirates;
  FighterType *tort;
  FighterType *hare;
  StatsType   *stats;
} RunSpecsType;

typedef struct {	// Specs for one fight of one scenario of one run
  FighterType  *hero;
  DequeType    *pirates;
  DirectionType dir;
  sem_t        *dqMutex;
} FightSpecsType;


int randm(int);		// Pseudo-random number generator function

// Scenario Functions
RunSpecsType initScenario(DequeType*, FighterType*, FighterType*, StatsType*);
void cleanUpRunSpecsType(RunSpecsType*);
void* runScenarioThread(void *);
ResultType computeScenarioOutcome(RunSpecsType*);

// Deque Functionalities
void initDeque(int, DequeType**);
void printDeque(DequeType*);
void deepCopyDeque(DequeType*, DequeType**);
void removeFighterFromBack(DequeType**, FighterType**);
void addElementtoDeque(NodeType**);
void removeFighterFromFront(DequeType**, FighterType**);
int isEmpty(DequeType*);
void cleanUpFighterNode(NodeType**);
void cleanUpDeque(DequeType**);

// Fight Functionalities
void initPirate(FighterType**);
void initHare(FighterType**);
void initTortoise(FighterType**);
void printFighter(FighterType*);
void deepCopyFighter(FighterType*, FighterType**);
void addSword(FighterType*);
FightSpecsType initFightSpecsType(FighterType*, DequeType* , DirectionType, sem_t*);
int Fight(FighterType**, FighterType**);
void* runFightThread(void*);

// Run Functionalities
void executeRun(StatsType**, int);

#endif


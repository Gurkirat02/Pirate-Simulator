#include "defs.h"


/*
  Function:  initFighter
  Purpose:   initializes a fighter
       in:   Takes the required parameters
   return:   void
*/
void initFighter(int strength, int armour, int health, FighterType** fighter){
    fighter[0] = malloc(sizeof(*fighter[0]));
    fighter[0]->strength = strength;
    fighter[0]->health = health;
    fighter[0]->armour = armour;
}

/*
  Function:  initPirate
  Purpose:   Initalizes the pirate fighter
       in:   int randm returns till number between 0 - parameter-1, we need betweem 5 - 9 inclusive i.e., randm(5) + 5 will give us random between 5 - 9 and armour
   return:   void
*/
void initPirate(FighterType** fighter){

    int strength = randm(5) + 4;
    int armour = randm(4) + 1;
    initFighter(strength, armour, PIRATE_HEALTH, fighter);
}
/*
  Function:  initHare
  Purpose:   initalizes a Hare hero
       in:   Takes the required parameters
   return:   void
*/

void initHare(FighterType** fighter){
    initFighter(HARE_STRENGTH, HARE_ARMOUR, HERO_HEALTH, fighter);
}

/*
  Function:  initTortoise
  Purpose:   initalizes a Tortoise hero
       in:   Takes the required parameters
   return:   void
*/
void initTortoise(FighterType** fighter){
    initFighter(TORT_STRENGTH, TORT_ARMOUR, HERO_HEALTH, fighter);
}
/*
  Function:  printFighter
  Purpose:   Test Function
       in:   prints the fighter data to screen
   return:   void
*/
void printFighter(FighterType* fighter){
    printf("Strength : %d -- Armour : %d -- Health : %d \n",fighter->strength, fighter->armour, fighter->health);
}

/*
  Function:  deepCopyFighter
  Purpose:   creates the deepcopy of a fighter
       in:   Fighter pointer as input and 2d pointer of figther will be return
   return:   void
*/
void deepCopyFighter(FighterType* fighter, FighterType** copy){
    initFighter(fighter->strength, fighter->armour, fighter->health, copy);
}
/*
  Function:  addSword
  Purpose:   assigns a sword to the given hero by adding sword power to its strength
       in:   Addsword takes in a fighter and assigns a sword to it i.e increases its strength
   return:   void
*/
void addSword(FighterType* fighter){
    fighter->strength = fighter->strength + SWORD_STRENGTH;
}
/* 
  Function:  initFightSpecsType
  Purpose:   initializes a fight specstype object by using given parameters
       in:   rakes in required data for fight specs and assigns them after creating its object and returns that object
   return:   void
*/
FightSpecsType initFightSpecsType(FighterType* hero, DequeType* pirates, DirectionType dir, sem_t* dqMutex){
    FightSpecsType fighterSpecs; //= malloc(sizeof(*fighterSpecs));
    fighterSpecs.hero = hero;
    fighterSpecs.pirates = pirates;
    fighterSpecs.dir = dir;
    fighterSpecs.dqMutex = dqMutex;
    return fighterSpecs;
}
/* 
  Function:  runFightThread
  Purpose:   executes all task for a single fight thread and keeps running until hero die of pirates list ends
       in:   
   return:   void
*/
void* runFightThread(void *fightSpecs){
    FighterType* pirate;
    FightSpecsType* fightSpec = (FightSpecsType*) fightSpecs;

    sem_wait(fightSpec->dqMutex);
    int isempty = isEmpty(fightSpec->pirates);
    sem_post(fightSpec->dqMutex);
    // int x = 0;

    // runn until pirates not empty and hero is alive
    while(isempty == 0 && fightSpec->hero->health > 0){ 
        
        sem_wait(fightSpec->dqMutex);
        if(fightSpec->dir == FRONT){    // removes pirate from front
            removeFighterFromFront(&(fightSpec->pirates), &pirate);
        }
        else    // removes pirate from back
            removeFighterFromBack(&(fightSpec->pirates), &pirate);
        sem_post(fightSpec->dqMutex);
        int f = Fight(&(fightSpec->hero),&pirate); // Fight between hero and pirate
        // uncomment this code to delete the fighter
        // int f = 1;
        if (f == 1){
            free(pirate);
            // printFighter(pirate);
        }
        else{
            free(pirate);
            break;
        }
                usleep(1000);

        sem_wait(fightSpec->dqMutex);
        isempty = isEmpty(fightSpec->pirates);
        sem_post(fightSpec->dqMutex);       
    }

    pthread_exit(NULL);
}
/*
  Function:  Fight
  Purpose:   this function handles the fight between hero and pirate 
       in:   
   return:     
*/
int Fight(FighterType** hero, FighterType** pirate){
    int damage;
    int fightstatus = 0;

    while(fightstatus == 0){    // run until one of the fighter die
        //hero attacks
        damage = hero[0]->strength - pirate[0]->armour;
        if(damage >= 0){    // if valid damage
            pirate[0]->health = pirate[0]->health - damage; 
            if(pirate[0]->health <= 0){    // pirates died
                pirate[0]->health = 0;
                fightstatus = 1;    // update status
                hero[0]->health = hero[0]->health + 3;    // bonus hero health for kill
                if(hero[0]->health > HERO_HEALTH)
                    hero[0]->health = HERO_HEALTH;
            }
        }
        //pirate attacks
        damage = (pirate[0]->strength + randm((pirate[0]->strength) - 2)) - hero[0]->armour;   // calculate damage, increased by strength + radm between 0 to strength -2 as randm gives radom till parameter -1(inclusive)
        // damage = (randm(pirate[0]->strength - 1)) - hero[0]->armour;
        if(damage >=0){ // valid damage
            hero[0]->health = hero[0]->health - damage;
            if(hero[0]->health <=0){   // hearo died
                hero[0]->health = 0;
                fightstatus = -1;   // update status
            }
        }
    }
    return fightstatus;
}
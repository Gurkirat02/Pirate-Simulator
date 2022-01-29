#include "defs.h"

/*
  Function:  initRun
  Purpose:   initializes data for all scenarios
       in:   2D pointers of deques and 2 2d pointers of fighters
    inout:   will contain a list of deques and for fighters aswell
   return:   void
*/
void initRun(DequeType** piratesList, FighterType** HaresList, FighterType** TortoiseList){
    initDeque(NUM_PIRATES, &piratesList[0]);
    for(int i = 1;i< NUM_SCENARIOS;i++){
        deepCopyDeque(piratesList[0], &piratesList[i]);
    }

    for(int i=0; i<NUM_SCENARIOS;i++){
        initHare(&HaresList[i]);
        initTortoise(&TortoiseList[i]);
    }
    addSword(TortoiseList[0]); // adding sword to tortoise in scenario 0
    addSword(HaresList[1]); // adding sword to Hare in scenario 1
}

/*
  Function:  executeRun
  Purpose:   executes the run of the fight and creates threads for each scenario and executes them
       in:   takes in deques
   return:   void
*/
void executeRun(StatsType** stats, int exec){

    DequeType** piratesList = malloc(NUM_SCENARIOS* sizeof(*piratesList));
    FighterType** HaresList = malloc(NUM_SCENARIOS* sizeof(*HaresList));
    FighterType** TortoiseList = malloc(NUM_SCENARIOS* sizeof(*TortoiseList));

    initRun(piratesList, HaresList, TortoiseList);

    // if(exec == 1)
    // {
    //     printf("Hare Scenario 0 :");
    //     printFighter(HaresList[0]);
    //     printf("Hare Scenario 1 :");
    //     printFighter(HaresList[1]);
    //     printf("Hare Scenario 2 :");
    //     printFighter(HaresList[2]);

    //     printf("Tortoise Scenario 0 :");
    //     printFighter(TortoiseList[0]);
    //     printf("Tortoise Scenario 1 :");
    //     printFighter(TortoiseList[1]);
    //     printf("Tortoise Scenario 2 :");
    //     printFighter(TortoiseList[2]);
    // }

    RunSpecsType runScenarios[NUM_SCENARIOS]; // = malloc(NUM_SCENARIOS* sizeof(*runScenarios));
    for(int i=0; i<NUM_SCENARIOS; i++){
        runScenarios[i] = initScenario(piratesList[i], TortoiseList[i], HaresList[i], stats[i]);
    }

    pthread_t threadScenarios[NUM_SCENARIOS];

    // create Threads for each Scenario
    for(int i=0;i<NUM_SCENARIOS;i++){
        pthread_create(&threadScenarios[i],NULL,runScenarioThread,(void*)&runScenarios[i]); 
    }

    // Wait for all the threads to finish the execution.
    for(int i=0; i<NUM_SCENARIOS;i++){
        pthread_join(threadScenarios[i],NULL);//wait until threads execution is completed
    }

    // un comment this code to run the clean up function
    for(int i=0; i<NUM_SCENARIOS;i++){
        // printDeque(runScenarios->pirates);
        // printf("\n\n");
        cleanUpRunSpecsType(&runScenarios[i]);
    }

    free(piratesList);
    free(HaresList);
    free(TortoiseList);
}
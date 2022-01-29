#include "defs.h"

/*
  Function:  initScenario
  Purpose:   this function initializes a scenario
       in:   values
   return:   returns the initalization of the scenario
*/
RunSpecsType initScenario(DequeType* pirates, FighterType* tort, FighterType* hare, StatsType* stats){
    RunSpecsType scenario;
    scenario.hare = hare;
    scenario.tort = tort;
    scenario.pirates = pirates;
    scenario.stats = stats;
    return scenario;
}
/*
  Function:  cleanUpRunSpecsType
  Purpose:   this function cleans up the memory allocated to RunSecsType along with its deque and heroes.
       in:   
   return:   void
*/
void cleanUpRunSpecsType(RunSpecsType* Scenario){
    cleanUpDeque(&(Scenario->pirates));
    free(Scenario->pirates);
    free(Scenario->hare);
    free(Scenario->tort);
    Scenario->stats = NULL;
}
/*
  Function:  cleanUpRunSpecsType
  Purpose:   this functions computes the outcome of the scenario 
   output:   ResultType Enum
   return:   Scenario Result
*/
ResultType computeScenarioOutcome(RunSpecsType* runScenario){
    if(isEmpty(runScenario->pirates) == 1){ // check if pirates list is empty
        if(runScenario->hare->health > 0 && runScenario->tort->health > 0){ // check if both heroes are alive
            return SUCCESS;
        }
        else    // both heroes not alive
            return PART_SUCCESS;
    }
    else    // list not empty
        return FAILURE;
}
/*
  Function:  runScenarioThread
  Purpose:   this function performs all the tasks for a single scenario thread
   output:   
   return:   void
*/
void* runScenarioThread(void *runScenario)
{
    RunSpecsType* scenario = (RunSpecsType*) runScenario;   // type cast void* to RunSpecstype*

    sem_t mutex;
    sem_init(&mutex, 0, 1); // create and initialize semaphore

    FightSpecsType fightSpecs[2]; //= malloc(2* sizeof(*fightSpecs));
    fightSpecs[0] = initFightSpecsType(scenario->tort, scenario->pirates, FRONT, &mutex); // fight specifications for tortoise
    fightSpecs[1] = initFightSpecsType(scenario->hare, scenario->pirates, BACK, &mutex); // fight specifications for hare

    pthread_t fightThreads[2];

    // create Threads for each fight
    for(int i=0;i<2;i++){
        pthread_create(&fightThreads[i],NULL,runFightThread,(void*)&fightSpecs[i]); 
    }

    // Wait for all the threads to finish the execution.
    for(int i=0; i<2;i++){
        pthread_join(fightThreads[i],NULL);//wait until threads execution is completed
    }

    // checks for the outcome of the scenario after both fights
    ResultType result = computeScenarioOutcome(scenario);

    if(result == SUCCESS)
        scenario->stats->numSuccess = scenario->stats->numSuccess + 1;
        // printf("Success\n");
    else if(result == PART_SUCCESS)
        scenario->stats->numPartSuccess = scenario->stats->numPartSuccess + 1;
        // printf("Partial Success\n");
    else if (result == FAILURE)
        scenario->stats->numFailure = scenario->stats->numFailure + 1;
        // printf("Failure\n");

    sem_destroy(&mutex);
    // since no pointer created just using the previous data so no deallocation required
    
    pthread_exit(NULL);
}

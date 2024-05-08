/* 
    These functions are compulsory for search algorithms but they are specific
    to problems. More clearly, you must must update their blocks but do not change
    their input and output parameters.
    
    Also, you can add new functions at the end of file by declaring them in GRAPH_SEARCH.h
*/


#define INF 999999


#include "GRAPH_SEARCH.h"
#include "data_types.h"
#include <stdio.h>
#include <stdlib.h>

//______________________________________________________________________________
State* Create_State()
{
	State *state = (State*)malloc(sizeof(State));
    if(state==NULL)
    	Warning_Memory_Allocation(); 
   
   	for(state->tile=A1; state->tile<=B2; state->tile++){        
    	printf("%d --> ", state->tile);
        Print_State(state);
        printf("\n");
   	}        
   
   	do{ 
    	printf("Enter the code of the state: ");
        scanf("%d", &state->tile);
   	}while(state->tile<0 && state->tile>=TILE_NUMBER);
	       
    return state;    
}

//______________________________________________________________________________
void Print_State(const State *const state)
{
    switch(state->tile){
         case  A1:      printf("A1"); break;
         case  A2:      printf("A2"); break;
         case  B1:      printf("B1"); break;
         case  B2:      printf("B2"); break;
    }  
}

//______________________________________________________________________________
void Print_Action(const enum ACTIONS action)
{
   switch(action){
         case  Go_A1:      printf("Go_A1"); break;
         case  Go_A2:      printf("Go_A2"); break;
         case  Go_B1:      printf("Go_B1"); break;
         case  Go_B2:      printf("Go_B2"); break;
    }        
}

//______________________________________________________________________________
int Result(const State *const parent_state, const enum ACTIONS action, Transition_Model *const trans_model)
{
    State new_state;
	const int PATH_COSTS[TILE_NUMBER][ACTIONS_NUMBER] = 
        {   {   0,    5,    1,   -1  },  // A1
            {   5,    0,   -1,  INF  },  // A2
            {   1,   -1,    0,  INF  },  // B1
            {  -1,  INF,  INF,    0  },  // B2
		};
	     //    A1  A2  B1  B2    
	 
         if(PATH_COSTS[parent_state->tile][action]<=0) 
              return FALSE;
         else{
              new_state.tile = action;
              trans_model->new_state = new_state;
              trans_model->step_cost = PATH_COSTS[parent_state->tile][action]; 
         }     
         return TRUE;                                               
}

//______________________________________________________________________________
float Compute_Heuristic_Function(const State *const state, const State *const goal)
{
      const float sqrt2 = 1.4142f;
      const float SLD[TILE_NUMBER][TILE_NUMBER] =
        {   {      0,      1,      1,  sqrt2  },  // A1
            {      1,      0,  sqrt2,      1  },  // A2
            {      1,  sqrt2,      0,      1  },  // B1
            {  sqrt2,      1,      1,      0  },  // B2
		};
	     //    A1  A2  B1  B2
         
        return SLD[state->tile][goal->tile];   
}

//_______________ Update if your goal state is not determined initially ___________________________________
int Goal_Test(const State *const state, const State *const goal_state)
{
	if(PREDETERMINED_GOAL_STATE)	
		return Compare_States(state, goal_state); 
	else
		return 1;
}

// ==================== WRITE YOUR OPTIONAL FUNCTIONS (IF REQUIRED) ==========================

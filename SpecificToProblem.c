/* 
    These functions are compulsory for search algorithms but they are specific
    to problems. More clearly, you must must update their blocks but do not change
    their input and output parameters.
    
    Also, you can add new functions at the end of file by declaring them in GRAPH_SEARCH.h
*/


#include <stdio.h>
#include <stdlib.h>


#include "GRAPH_SEARCH.h"
#include "data_types.h"
#include "map_loader.h" 


//______________________________________________________________________________
State* Create_State()
{
	State *state = (State*)malloc(sizeof(State));
    if(state==NULL)
    	Warning_Memory_Allocation(); 
   
   	for(state->tile=0; state->tile<TILE_NUMBER; state->tile++){        
    	printf("%d --> ", state->tile);
        Print_State(state);
        printf("\n");
   	}        
   
   	do{ 
    	printf("Enter the code of the state: ");
        scanf("%d", &state->tile);
   	}while(state->tile<0 && state->tile>TILE_NUMBER);
	       
    return state;    
}

//______________________________________________________________________________
void Print_State(const State *const state)
{
    print_tile(state->tile);
}

//______________________________________________________________________________
void Print_Action(const ACTIONS action)
{
    print_action(action);      
}

//______________________________________________________________________________
int Result(const State *const parent_state, const ACTIONS action, Transition_Model *const trans_model)
{
    State new_state;
	 
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

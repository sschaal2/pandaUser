/*============================================================================
==============================================================================
                      
                              initUserTasks.c
 
==============================================================================
Remarks:

         Functions needed to initialize and link user tasks for the
         simulation

============================================================================*/

#include "SL.h"
#include "SL_user.h"
#include "SL_man.h"
#include "SL_tasks.h"
#include "SL_task_servo.h"
#include "unistd.h"
#include "limits.h"
#include "string.h"

/* global variables */

/* local variables */
static int user_tasks_initialized = FALSE;
int no_user_interaction_flag = FALSE;

// local functions
static void runInsertions(void);


/*****************************************************************************
******************************************************************************
Function Name	: initUserTasks
Date		: June 1999
   
Remarks:

      initialize tasks that are not permanently linked in the simulation
      This replaces the <ltask facility in vxworks -- just that we cannot
      do on-line linking in C.

******************************************************************************
Paramters:  (i/o = input/output)

  none   

*****************************************************************************/
void
initUserTasks(void)

{

  extern void add_gravcomp_task();
  extern void add_sample_task();  

  add_sample_task();  
  add_gravcomp_task();

  //sprintf(initial_user_command,"go0");

}

 

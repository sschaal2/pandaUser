/*============================================================================
==============================================================================
                      
                              gravcomp_task.c
 
==============================================================================
Remarks:

      put the robot in pure gravity compensation

============================================================================*/

// system headers
#include "SL_system_headers.h"

// SL includes 
#include "SL.h"
#include "SL_user.h"
#include "SL_tasks.h"
#include "SL_task_servo.h"
#include "SL_kinematics.h"
#include "SL_dynamics.h"
#include "SL_collect_data.h"
#include "SL_shared_memory.h"
#include "SL_man.h"
#include "SL_unix_common.h"

// defines

// local variables
static double start_time = 0.0;
static SL_DJstate  target[N_DOFS+1];

// global functions

// local functions
static int  init_gravcomp_task(void);
static int  run_gravcomp_task(void);
static int  change_gravcomp_task(void);

/*****************************************************************************
******************************************************************************
Function Name	: add_gravcomp_task
Date		: Feb 1999
Remarks:

adds the task to the task menu

******************************************************************************
Paramters:  (i/o = input/output)

none

*****************************************************************************/
void
add_gravcomp_task( void )

{
  int i, j;
  
  addTask("Gravcomp Task", init_gravcomp_task, 
	  run_gravcomp_task, change_gravcomp_task);

}    

/*****************************************************************************
******************************************************************************
  Function Name	: init_gravcomp_task
  Date		: Dec. 1997

  Remarks:

  initialization for task

******************************************************************************
  Paramters:  (i/o = input/output)

       none

 *****************************************************************************/
static int 
init_gravcomp_task(void)
{
  int j, i;
  int ans;
  static int firsttime = TRUE;
  
  if (firsttime){
    firsttime = FALSE;
  }

  // prepare going to the default posture
  bzero((char *)&(target[1]),N_DOFS*sizeof(target[1]));
  for (i=1; i<=N_DOFS; i++)
    target[i] = joint_default_state[i];

  // go to the target using inverse dynamics (ID)
  if (!go_target_wait_ID(target)) 
    return FALSE;

  // ready to go
  ans = 999;
  while (ans == 999) {
    if (!get_int("Enter 1 to start or anthing else to abort ...",ans,&ans))
      return FALSE;
  }
  
  // only go when user really types the right thing
  if (ans != 1) 
    return FALSE;

  start_time = task_servo_time;
  printf("start time = %.3f, task_servo_time = %.3f\n", 
	 start_time, task_servo_time);
  scd();

  return TRUE;
}

/*****************************************************************************
******************************************************************************
  Function Name	: run_gravcomp_task
  Date		: Dec. 1997

  Remarks:

  run the task from the task servo: REAL TIME requirements!

******************************************************************************
  Paramters:  (i/o = input/output)

  none

 *****************************************************************************/
static int 
run_gravcomp_task(void)
{
  int j, i;

  double task_time;

  task_time = task_servo_time - start_time;

  // the following variables need to be assigned
  for (i=1; i<=N_DOFS; ++i) {
    joint_des_state[i].th   = joint_state[i].th;
    joint_des_state[i].thd  = joint_state[i].thd;
    joint_des_state[i].thdd = 0.0;
    joint_des_state[i].uff  = 0.0;
  }

  // compute inverse dynamics torques
  SL_InvDynNE(joint_state,joint_des_state,endeff,&base_state,&base_orient);

  return TRUE;
}

/*****************************************************************************
******************************************************************************
  Function Name	: change_gravcomp_task
  Date		: Dec. 1997

  Remarks:

  changes the task parameters

******************************************************************************
  Paramters:  (i/o = input/output)

  none

 *****************************************************************************/
static int 
change_gravcomp_task(void)
{
  int    ivar=0;
  double dvar=0;

  get_int("This is how to enter an integer variable",ivar,&ivar);
  get_double("This is how to enter a double variable",dvar,&dvar);

  return TRUE;

}


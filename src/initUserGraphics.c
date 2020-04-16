/*============================================================================
==============================================================================
                      
                              initUserGraphics.c
 
==============================================================================
Remarks:

         Functions needed for user graphics
         simulation

============================================================================*/

#include "SL.h"
#include "SL_user.h"
#include "SL_man.h"
#include "string.h"

// openGL includes
#include "GL/glut.h"
#include "SL_openGL.h"
#include "SL_userGraphics.h"

// global variables

// local variables
static void displayFTVector(void *b);

/*****************************************************************************
******************************************************************************
Function Name	: initUserGraphics
Date		: June 1999
   
Remarks:

      allows adding new graphics functions to openGL interface

******************************************************************************
Paramters:  (i/o = input/output)

  none   

*****************************************************************************/
int
initUserGraphics(void)

{

  switchCometDisplay(TRUE,500);

  addToUserGraphics("displayFTVector","Displays a F/T vector at pos x",displayFTVector,
                    3*N_CART*sizeof(float));

  return TRUE;

}

/*!*****************************************************************************
 *******************************************************************************
 \note  displayFTVector
 \date  April. 2012

 \remarks

 at a given world position, displays a Force/Torque vector (also in world
 coordinates)

 *******************************************************************************
 Function Parameters: [in]=input,[out]=output

 \param[in]      b      : the general array of bytes

 ******************************************************************************/
static void
displayFTVector(void *b)
{
  int i,j,n;
  double f[N_CART+1];
  double t[N_CART+1];
  double x[N_CART+1];  
  double fscale_N=0.025;
  double fscale_Nm=0.15;
  double s[N_CART+1];
  double e[N_CART+1];
  double arrow_width = 0.01;
  float  data[3*N_CART+1];

  // assign the ball position from b array
  memcpy(&(data[1]),b,3*N_CART*sizeof(float));

  // rotate the force torque info to world coordinates
  for (i=1; i<=N_CART; ++i) {
    f[i] = data[i];
    t[i] = data[i+N_CART];
    x[i] = data[i+2*N_CART];
  }

  glPushMatrix();
    
  // move to the force torque sensor
  glTranslated(x[_X_],x[_Y_],x[_Z_]);

  // the start and end point of the force vector
  s[_X_] =  0.0;
  s[_Y_] =  0.0;
  s[_Z_] =  0.0;

  e[_X_] = s[_X_] + f[_X_]*fscale_N;
  e[_Y_] = s[_Y_] + f[_Y_]*fscale_N;
  e[_Z_] = s[_Z_] + f[_Z_]*fscale_N;


  glColor4f (0.8,1.0,1.0,1.0);      
  drawArrow(s,e,arrow_width);

  e[_X_] = s[_X_] + t[_X_]*fscale_Nm;
  e[_Y_] = s[_Y_] + t[_Y_]*fscale_Nm;
  e[_Z_] = s[_Z_] + t[_Z_]*fscale_Nm;

    
  glColor4f (0.8,0.4,0.0,1.0);
  drawArrow(s,e,arrow_width);

  glPopMatrix();

}

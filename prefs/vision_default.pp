/* this file contains information how to post process the vision blobs. 
   Butterworth filtering and Kalman filtering are possible. Additionally,
   coefficents for the acceleration of a blob can be provided, if known */

/* format: keyword, 9 number for butterworth cutoffs, 9 number for
           kalman filter coefficients, 3 number for acceleration vector,
           one number for prediction */

PREDICT
0.033

BLOB1_BUTTER
20   20  20        /* x, y, z position     */
100 100 100     /* x, y, z velocity     */
100 100 100     /* x, y, z acceleration */

BLOB1_ACCELERATION
0 0 0

BLOB2_BUTTER
20 20 20        /* x, y, z position     */
100 100 100     /* x, y, z velocity     */
100 100 100     /* x, y, z acceleration */

BLOB2_ACCELERATION
0 0 0


BLOB3_BUTTER
20 20 20        /* x, y, z position     */
100 100 100     /* x, y, z velocity     */
100 100 100     /* x, y, z acceleration */

BLOB3_ACCELERATION
0 0 0




BLOB4_BUTTER
20 20 20        /* x, y, z position     */
100 100 100     /* x, y, z velocity     */
100 100 100     /* x, y, z acceleration */

BLOB4_ACCELERATION
0 0 0


BLOB5_BUTTER
20 20 20        /* x, y, z position     */
100 100 100     /* x, y, z velocity     */
100 100 100     /* x, y, z acceleration */


BLOB5_ACCELERATION
0 0 0

BLOB6_BUTTER
20 20 20        /* x, y, z position     */
100 100 100     /* x, y, z velocity     */
100 100 100     /* x, y, z acceleration */

BLOB6_ACCELERATION
0 0 0




/*
BLOB6_KALMAN
0.75 0.75 1.05  /* position gains */
8.4  8.4  16.5  /* velocity gains */
0.0  0.0   0.0  /* acceleration gains */

*/
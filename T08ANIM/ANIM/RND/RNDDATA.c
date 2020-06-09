/* FILE NAME: RNDDATA.C
 * PROGRAMMER: GC6
 * DATE: 06.06.2020
 * PURPOSE: 3D animation project.
 *          
*/
#include "rnd.h"

HWND GC6_hRndWnd;/* Work window handle */     
HDC GC6_hRndDCFrame;/* Work window memory device context  */
HBITMAP GC6_hRndBmFrame;/* Work window background bitmap handle */
INT GC6_RndFrameW, GC6_RndFrameH; /* Work window size */


DBL
  GC6_RndProjSize,  /* Project plane fit square */
  GC6_RndProjDist,  /* Distance to project plane from viewer (near) */
  GC6_RndProjFarClip;  /* Distance to project far clip plane (far) */


MATR
  GC6_RndMatrView, /* View coordinate system matrix */
  GC6_RndMatrProj, /* Projection coordinate system matrix */
  GC6_RndMatrVP;   /* Stored (View * Proj) matrix */

/* END OF 'RNDDATA.C' FILE */
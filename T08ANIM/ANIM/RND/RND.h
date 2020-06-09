/* FILE NAME: RND.H
 * PROGRAMMER: GC6
 * DATE: 06.06.2020
 * PURPOSE: 3D animation project.
 *          
 */

#ifndef __RND_H_
#define __RND_H_

#include "../../def.h"

extern HWND GC6_hRndWnd;        /* Work window handle */
extern HDC GC6_hRndDCFrame;     /* Work window memory device context  */
extern HBITMAP GC6_hRndBmFrame; /* Work window background bitmap handle */
extern INT GC6_RndFrameW, GC6_RndFrameH;/* Work window size */

extern DBL
  GC6_RndProjSize,  /* Project plane fit square */
  GC6_RndProjDist,  /* Distance to project plane from viewer (near) */
  GC6_RndProjFarClip;  /* Distance to project far clip plane (far) */

extern MATR
  GC6_RndMatrView, /* View coordinate system matrix */
  GC6_RndMatrProj, /* Projection coordinate system matrix */
  GC6_RndMatrVP;   /* Stored (View * Proj) matrix */

VOID GC6_RndInit( HWND hWnd );
VOID GC6_RndClose( VOID );
VOID GC6_RndResize( INT W, INT H );
VOID GC6_RndCopyFrame( HDC hDC );
VOID GC6_RndStart( VOID );
VOID GC6_RndProjSet( VOID );
VOID GC6_RndCamSet( VEC Loc, VEC At, VEC Up );
VOID GC6_RndEnd( VOID );

typedef struct taggc6VERTEX
{
  VEC P;  /* Vertex position */
} gc6VERTEX;

typedef struct taggc6PRIM
{
  gc6VERTEX *V; /* Vertex attributes array */
  INT NumOfV;   /* Number of vertices */

  INT *I;       /* Index array (for trimesh – by 3 ones) */
  INT NumOfI;   /* Number of indices */

  MATR Trans;   /* Additional transformation matrix */
} gc6PRIM;

BOOL GC6_RndPrimCreate( gc6PRIM *Pr, INT NoofV, INT NoofI );
VOID GC6_RndPrimFree( gc6PRIM *Pr );
VOID GC6_RndPrimDraw( gc6PRIM *Pr, MATR World );
VOID GC6_RndPrimCreateSphere( gc6PRIM *Pr, VEC C, DBL R, INT SplitW, INT SplitH );
BOOL GC6_RndPrimLoad( gc6PRIM *Pr, CHAR *FileName );
//VOID VG4_RndEnd( VOID );
#endif /* __RND_H_ */

/* END OF 'RND.H' FILE */
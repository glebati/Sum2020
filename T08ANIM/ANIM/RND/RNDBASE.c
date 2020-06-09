/* FILE NAME: RNDBASE.C
 * PROGRAMMER: GC6
 * DATE: 06.06.2020
 * PURPOSE: 3D animation project.
 *          
*/

#include "rnd.h"

VOID GC6_RndInit( HWND hWnd )
{
  HDC hDC;
  
  GC6_hRndWnd = hWnd;

  hDC = GetDC(hWnd);
  GC6_hRndDCFrame = CreateCompatibleDC(hDC);
  ReleaseDC(hWnd, hDC);
  GC6_hRndBmFrame = NULL;

 /* Set default render parameters*/
 GC6_RndFrameW = 45;
 GC6_RndFrameH = 45;
 GC6_RndProjSize = 0.1;
 GC6_RndProjDist = 0.1;
 GC6_RndProjFarClip = 300;

 GC6_RndProjSet();
 GC6_RndCamSet(VecSet(7, 2, 2), VecSet(0, 1, -2), VecSet(2, 2, 2) );
}/* End of 'GC6_RndInit' function*/

VOID GC6_RndClose( VOID )
{
  DeleteDC(GC6_hRndDCFrame);
  DeleteObject(GC6_hRndBmFrame);  
}/* End of 'GC6_RndClose' fn*/

VOID GC6_RndResize( INT W, INT H )
{
  HDC hDC = GetDC(GC6_hRndWnd);

  if (GC6_hRndBmFrame != NULL)
    DeleteObject(GC6_hRndBmFrame);
  GC6_hRndBmFrame = CreateCompatibleBitmap(hDC, W, H);
  ReleaseDC(GC6_hRndWnd, hDC);		
  SelectObject(GC6_hRndDCFrame, GC6_hRndBmFrame);

  /* Saving size */
  GC6_RndFrameW = W;
  GC6_RndFrameH = H;

  /* recounting projection*/
  GC6_RndProjSet();
}
VOID GC6_RndCopyFrame( HDC hDC )
{
  BitBlt(hDC, 0, 0, GC6_RndFrameW, GC6_RndFrameH,
         GC6_hRndDCFrame, 0, 0, SRCCOPY);
}


VOID GC6_RndStart( VOID )
{

  /* Clear Background */
  SelectObject(GC6_hRndDCFrame, GetStockObject(WHITE_BRUSH));
  SelectObject(GC6_hRndDCFrame, GetStockObject(NULL_PEN));
  Rectangle(GC6_hRndDCFrame, 0, 0, GC6_RndFrameW + 1, GC6_RndFrameH + 1);

  SelectObject(GC6_hRndDCFrame, GetStockObject(NULL_BRUSH));
  SelectObject(GC6_hRndDCFrame, GetStockObject(BLACK_PEN));
}

VOID GC6_RndProjSet( VOID )
{
  DBL rx, ry;

  rx = ry = GC6_RndProjSize;

  /* Correct aspect ration */
  if (GC6_RndFrameW > GC6_RndFrameH)
    rx *= (DBL)GC6_RndFrameW / GC6_RndFrameH;
  else
    ry *= (DBL)GC6_RndFrameH / GC6_RndFrameW;


  GC6_RndMatrProj =
    MatrFrustum(-rx / 2, rx / 2, -ry / 2, ry / 2,
      GC6_RndProjDist, GC6_RndProjFarClip);
  GC6_RndMatrVP = MatrMulMatr(GC6_RndMatrView, GC6_RndMatrProj);
}/* End of 'GC6_RndProjSet' function */

VOID GC6_RndCamSet( VEC Loc, VEC At, VEC Up )
{
  GC6_RndMatrView = MatrView(Loc, At, Up);
  GC6_RndMatrVP = MatrMulMatr(GC6_RndMatrView, GC6_RndMatrProj);
}/* End of 'GC6_RndCamSet' function */

VOID GC6_RndEnd( VOID )
{
}

/* END OF 'RNDBASE.C' FILE */
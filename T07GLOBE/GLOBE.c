/* FILE NAME: GLOBE.c
 * PROGRAMMER: GC6
 * DATE: 04.06.2020
 * PURPOSE:
 */

#include <windows.h>
#include <time.h>

#include "timer.h"
#include "globe.h"
#include "math.h"

#define M (25 * 3)
#define N (12 * 3)

static VEC Geom[N][M];
static INT CenterX, CenterY;

VEC VecRotateZ( VEC V, DBL Angle )
{
  VEC r;
  
  Angle *= PI / 180; 
  r.X = V.X * cos(Angle) - V.Y * sin(Angle);
  r.Y = V.X * sin(Angle) + V.Y * cos(Angle);
  r.Z = V.Z;

  return r;
}

VEC VecRotateY(VEC V, DOUBLE Angle)
{
    VEC r;

    Angle *= PI / 180;
    r.X = V.X * cos(Angle) - V.Y * sin(Angle);
    r.Y = V.X * sin(Angle) + V.Y * cos(Angle);
    r.Z = V.Z;

    return r;
}

VEC VecRotateX(VEC V, DOUBLE Angle)
{
    VEC r;

    Angle *= PI / 180;
    r.Y = V.Y  * cos(Angle) - V.Z * sin(Angle);
    r.Z = V.Y * sin(Angle) + V.Z * cos(Angle);
    r.X = V.X;

    return r;
}

/* GlobeSet function */                                                       
VOID GlobeSet( INT Xc, INT Yc, DBL R )
{
  INT i, j;
  DBL theta, phi;
  CenterX = Xc, CenterY = Yc;

  for (i = 0, theta = 0; i < N; i++, theta += PI / (N - 1))
    for (j = 0, phi = 0; j < M; j++, phi += 2 * PI / (M - 1))
    {
      Geom[i][j].X =  R * sin(theta) * sin(phi);
      Geom[i][j].Y =  R * cos(theta);
      Geom[i][j].Z = R * sin(theta) * cos(phi);
    }
}/* End of GlobeSet function */
     
/* Globe Draw function */
VOID GlobeDraw( HDC hDC )
{
  DBL t = GLB_Time, A, z[N][M];
  INT i, j, s = 3; 
  static POINT pnts[N][M];  
  MATR m = MatrRotateX(GLB_Time * 30);

  for (i = 0; i < N; i++)
    for (j = 0; j < M; j++)
    {
      VEC
        v = PointTransform(Geom[i][j], m);
                                         
      z[i][j] = v.Z;
      pnts[i][j].x = CenterX + (INT)v.X,
      pnts[i][j].y = CenterY - (INT)v.Y;  
    }

  SelectObject(hDC, GetStockObject(DC_BRUSH));
  SelectObject(hDC, GetStockObject(DC_PEN));
  srand(30);
  for (i = 0; i < N - 1; i++)
    for (j = 0; j < M - 1; j++)
      { 
        POINT ps[4];
        ps[0] = pnts[i][j]; 
        ps[1] = pnts[i][j + 1]; 
        ps[2] = pnts[i + 1][j + 1]; 
        ps[3] = pnts[i + 1][j]; 

        A = ((ps[0].x - ps[1].x) * (ps[0].y + ps[1].y) +
             (ps[1].x - ps[2].x) * (ps[1].y + ps[2].y) +
             (ps[2].x - ps[3].x) * (ps[2].y + ps[3].y) +
             (ps[3].x - ps[0].x) * (ps[3].y + ps[0].y));
        if (A >= 0)
        {
        SetDCBrushColor(hDC, RGB(0, 0, 0));
        SetDCPenColor(hDC, RGB(255, 255, 255));
        Polygon(hDC, ps, 4);
        }
      }                             
}/* End of GlobeDraw function */
/* FILE NAME: TIMER.c
 * PROGRAMMER: GC6
 * DATE: 04.06.2020
 * PURPOSE:
 */
#include "TIMER.H"

VOID GLB_TimerInit( VOID )
{
  StartTime = OldTime = OldFPSTime = clock();
  PauseTime = 0;
  FrameCount = 0;
  GLB_IsPause = FALSE;
}

VOID GLB_TimerResponse( VOID )
{
  LONG t = clock();

  if (!GLB_IsPause)
  {
    GLB_Time = (DOUBLE)(t - PauseTime - StartTime) / CLOCKS_PER_SEC;
    GLB_DeltaTime = (DOUBLE)(t - OldTime) / CLOCKS_PER_SEC;
  }
  else
  {
    PauseTime += t - OldTime;
    GLB_DeltaTime = 0;
  }
  FrameCount++;
  if (t - OldFPSTime > CLOCKS_PER_SEC)
  {
    GLB_FPS = FrameCount / ((DBL)(t - OldFPSTime) / CLOCKS_PER_SEC);
    OldFPSTime = t;
    FrameCount = 0;
  }
  OldTime = t;
}
    
    
    
    

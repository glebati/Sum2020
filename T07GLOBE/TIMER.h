/* FILE NAME: TIMER.h
 * PROGRAMMER: GC6
 * DATE: 04.06.2020
 * PURPOSE:
 */
#include <windows.h>
#include <time.h>

typedef double DBL;

DBL GLB_Time, GLB_DeltaTime, GLB_FPS;
BOOL GLB_IsPause;
LONG StartTime, OldTime, OldFPSTime, FrameCount, PauseTime;

VOID GLB_TimerInit( VOID );
VOID GLB_TimerResponse( VOID );
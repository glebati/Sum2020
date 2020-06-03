/* *FILENAME: T05DET.c 
    *PROGRAMMER: GC6
    *DATE: 02.06.2020 
    *PURPOSE: 
    */

#include <stdio.h>

#include <windows.h>

typedef DOUBLE DBL;

#define MAX 10
DBL A[MAX][MAX];
INT N;

INT P[MAX];
BOOL IsParity;

 /* Load matrix */
BOOL LoadMatrix( CHAR *FileName )
{
  FILE *F;

  N = 0;
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  fscanf(F, "%d", &N);
  if (N > MAX)
    N = MAX;
  else
    if (N < 0)
      N = 0;
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      fscanf(F, "%lf", &A[i][j]);

  fclose(F);
  return TRUE;
}/* end of load matrix function */



VOID main( VOID )
{
  LoadMatrix("IN.txt");


}

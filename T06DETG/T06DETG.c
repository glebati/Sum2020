/* FILE NAME: T04PERM.C
   PROGRAMMER: GC6
   DATE: 02.06.2020
   PURPOSE: 
*/

#include <stdio.h>
#include <windows.h>
#include <math.h>

#define MAX 10
typedef DOUBLE DBL;
DBL A[MAX][MAX];
INT N;

INT P[MAX];
BOOL IsParity;

/* load matrix function */
BOOL LoadMaxtrix( CHAR *FileName )
{
  FILE *F;
  INT i, j;

  N = 0;
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  fscanf(F, "%d", &N);
  if (N < 0)
    N = 0;
  else
    if (N > MAX)
      N = MAX;

  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      fscanf(F, "%lf", &A[i][j]);

  fclose(F);
  return TRUE;
}/* end of load function */

/* Swap function */
VOID Swap( DBL *a, DBL *b )
{
  DBL tmp = *a;
  *a = *b;
  *b = tmp;
}/* End of "swap" function */

/* Determinate fucntion */
DBL DetG( VOID )
{
  DBL det = 1, x;
  INT i, max_row, max_col;

  for (i = 0; i < N; i++)
  {
    INT x, y, k, z;

    max_col = max_row = i;
    for (y = i; y < N; y++)
      for (x = i; x < N; x++)
        if (fabs(A[y][x]) > fabs(A[max_row][max_col]))
          max_col = x, max_row = y;
    if (A[max_row][max_col] == 0)
    {
      det = 0;
      break;
    }
    if (max_row != i)
    {
      for (x = i; x < N; x++)
        Swap(&A[i][x], &A[max_row][x]);
      det = -det;
    }
    if (max_col != i)
    {
      for (x = i; x < N; x++)
        Swap(&A[x][i], &A[x][max_col]);
      det = -det;
    }
    x = A[i + 1][i] / A[i][i];
    A[i + 1][i] = 0;
    for (k = i + 1; k < N; k++)
      A[i + 1][k] -= A[i][k] * x;
    for (z = 1; z < N - 1; z++)
    {
      x = A[i + 1 + z][i] / A[i][i];
      for (k = i; k < N; k++)
        A[i + 1 + z][k] -= A[i][k] * x;
    }
    det *= A[i][i];
  }
  return det;
}/* end of determinate fucntion */

VOID main( VOID )
{
  LoadMaxtrix("IN.TXT");
  printf("%f", DetG());
  getchar();
}

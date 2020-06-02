/* FILE NAME: T04PERM.C
   PROGRAMMER: GC6
   DATE: 02.06.2020
   PURPOSE: 
*/

#include <windows.h>
#include <stdio.h>

/* base array */
#define MAX 5
INT P[MAX];

BOOL IsParity = 1;

/* srote function */
VOID Store( VOID )
{
  FILE *F;
  INT i;

  F = fopen("PERM.TXT", "a");
  if (F != NULL)
    return;

  for (i = 0; i < MAX - 1; i++)
    fprintf(F, "%d,", P[i]);
  fprintf(F, "%d – parity: %s\n", P[MAX - 1], IsParity ? "even" : "odd");

  fclose(F);
}/* End of "store" function */

/* Swap function */
VOID Swap( INT *a, INT *b )
{
  INT tmp = *a;
  *a = *b;
  *b = tmp;
}/* End of "swap" function */ 

/* Go function */
VOID Go( INT Pos )
{
  INT i, n;
  BOOL SaveParity;

  if (Pos == MAX)
    Store();
  else
  {
    SaveParity = IsParity;
    Go(Pos + 1);
    for (i = Pos + 1; i < MAX; i++)
    {
      Swap(&P[Pos], &P[i]);
      IsParity = !IsParity;
      Go(Pos + 1);
    }
    n = P[Pos];
    for (i = Pos + 1; i < MAX; i++)
      P[i - 1] = P[i];
    P[MAX - 1] = n;
    IsParity = SaveParity;
  }
} /* end of "Go" function */

VOID main( VOID )
{
  INT i;
  
  for(i = 0; i < MAX; i++)
    P[i] = i + 1;
  Go(0);
}

/* End of "T04PERM.C" file */
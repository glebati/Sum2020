  /* FILE NAME: MATH.h
 * PROGRAMMER: GC6
 * DATE: 05.06.2020
 * PURPOSE:
 */
#ifndef __MTH_H_
#define __MTH_H_

#include <math.h>
#include <windows.h>

#define PI 3.14159265358979323846
#define D2R(A) ((A) * (PI / 180.0))
#define Degree2Radian(a) D2R(a)

typedef double DBL;
typedef float FLT;

typedef struct tagVEC
{
  DBL X, Y, Z;
} VEC;

typedef struct tagMATR
{
  DBL M[4][4];
} MATR;

__inline VEC VecSet( DBL X, DBL Y, DBL Z )
{
  VEC v;

  v.X = X;
  v.Y = Y;
  v.Z = Z;
  return v;
} /* End of 'VecSet' function */

__inline VEC VecAddVec( VEC V1, VEC V2 )
{
  VEC v;

  return VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
}

__inline VEC VecSubVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X - V2.X, V1.Y - V2.Y, V1.Z - V2.Z);
}

__inline VEC VecMulNum( VEC V1, DBL N )
{
  return VecSet(V1.X * N, V1.Y * N, V1.Z * N);
}

__inline VEC VecDivNum( VEC V1, DBL N )
{
  return VecSet(V1.X / N, V1.Y / N, V1.Z / N);
}

__inline VEC VecNeg( VEC V )
{
  return VecSet(-V.X, -V.Y, -V.Z);
}                                                       

__inline DBL VecDotVec( VEC V1, VEC V2 )
{
  return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;  
}

__inline VEC VecCrossVec( VEC V1, VEC V2 )
{
  return VecSet(V1.Y * V2.Z - V1.Z * V2.Y, V1.Z * V2.X - V1.X * V2.Z, V1.X * V2.Y - V1.Y * V2.X);
}

__inline DBL VecLen2( VEC V )
{
  return VecDotVec(V, V);
}

__inline DBL VecLen( VEC V )
{
  DBL len = VecDotVec(V, V);

  if (len == 1 || len == 0)
    return len;
  return sqrt(len);
}

__inline VEC VecNormalize( VEC V )   
{
  DBL len = VecDotVec(V, V);

  if (len == 1 || len == 0)
    return V;
  len = sqrt(len);
  return VecDivNum(V, len);
}

__inline VEC PointTransform( VEC V, MATR M )
{
  return VecSet(V.X * M.M[0][0] + V.Y * M.M[1][0] + V.Z * M.M[2][0] + M.M[3][0], 
                 V.X * M.M[0][1] + V.Y * M.M[1][1] + V.Z * M.M[2][1] + M.M[3][1], 
                 V.X * M.M[0][2] + V.Y * M.M[1][2] + V.Z * M.M[2][2] + M.M[3][2]);
}

__inline VEC VectorTransform( VEC V, MATR M )
{
  return VecSet(V.X * M.M[0][0] + V.Y * M.M[1][0] + V.Z * M.M[2][0], 
                V.X * M.M[0][1] + V.Y * M.M[1][1] + V.Z * M.M[2][1], 
                V.X * M.M[0][2] + V.Y * M.M[1][2] + V.Z * M.M[2][2]);
}

__inline VEC VecMulMatr( VEC V, MATR M )
{
  DBL w = V.X * M.M[0][3] + V.Y * M.M[1][3] + V.Z * M.M[2][3] + M.M[3][3];
  return VecSet((V.X * M.M[0][0] + V.Y * M.M[1][0] + V.Z * M.M[2][0] + M.M[3][0]) / w, 
                (V.X * M.M[0][1] + V.Y * M.M[1][1] + V.Z * M.M[2][1] + M.M[3][1]) / w,
                (V.X * M.M[0][2] + V.Y * M.M[1][2] + V.Z * M.M[2][2] + M.M[3][2]) / w);
}

static MATR UnitMatrix =
#define UnitMatrix 
{                  \
  {                \
    {1, 0, 0, 0},  \
    {0, 1, 0, 0},  \
    {0, 0, 1, 0},  \
    {0, 0, 0, 1}   \
  }                \
};

__inline MATR MatrIdentity( VOID )
{
  return UnitMatrix;
}

__inline MATR SetMatr(DBL A00, DBL A01, DBL A02, DBL A03,
                      DBL A10, DBL A11, DBL A12, DBL A13,
                      DBL A20, DBL A21, DBL A22, DBL A23,
                      DBL A30, DBL A31, DBL A32, DBL A33)
{
  MATR m;

  m.M[0][0] = A00;
  m.M[0][1] = A01;
  m.M[0][2] = A02;
  m.M[0][3] = A03;
  m.M[1][0] = A10;
  m.M[1][1] = A11;
  m.M[1][2] = A12;
  m.M[1][3] = A13;
  m.M[2][0] = A20;
  m.M[2][1] = A21;
  m.M[2][2] = A22;
  m.M[2][3] = A23;
  m.M[3][0] = A30;
  m.M[3][1] = A31;
  m.M[3][2] = A32;
  m.M[3][3] = A33;

  return m;
}

__inline MATR MatrTranslate( VEC T )
{
  MATR m =
  {
    {
      {1, 0, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 1, 0},
      {T.X, T.Y, T.Z, 1}
    }
  };
}

__inline MATR MatrRotateX( DBL AngleInDegree )
{
   return SetMatr(1, 0, 0, 0,
      0, cos(D2R(AngleInDegree)), sin(D2R(AngleInDegree)), 0,
      0, -sin(D2R(AngleInDegree)), cos(D2R(AngleInDegree)), 0,
      0, 0, 0, 1);
}

__inline MATR MatrRotateY( DBL AngleInDegree )
{
  return SetMatr(cos(D2R(AngleInDegree)), 0, -sin(D2R(AngleInDegree)), 0,
      0, 1, 0, 0,
      sin(D2R(AngleInDegree)), 0, cos(D2R(AngleInDegree)), 0,
      0, 0, 0, 1);
}

__inline MATR MatrRotateZ( DBL AngleInDegree )
{
  return SetMatr(cos(D2R(AngleInDegree)), sin(D2R(AngleInDegree)), 0, 0,
      -sin(D2R(AngleInDegree)), cos(D2R(AngleInDegree)), 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1);
}

__inline MATR MatrRotate( DBL AngleInDegree, VEC V )
{
  DBL
    a = D2R(AngleInDegree),
    c = cos(a),
    s = sin(a);
  VEC
    A = VecNormalize(V);
  MATR m =
  {
    {
      {c + A.X * A.X * (1 - c), A.X * A.Y * (1 - c) + A.Z * s, A.X * A.Z * (1 - c) - A.Y * s, 0},
      {A.X * A.Y * (1 - c) - A.Z * s, c + A.Y * A.Y * (1 - c), A.Z * A.Y * (1 - c) + A.X * s, 0},
      {A.X * A.Z * (1 - c) + A.Y * s, A.Y * A.Z * (1 - c) - A.X * s, c + A.Z * A.Z * (1 - c), 0},
      {0, 0, 0, 1}
    }
  };

  return m;
}

__inline MATR MatrTranspose( MATR M )
{
  MATR M1;

  M1.M[0][0] = M.M[0][0];
  M1.M[0][1] = M.M[1][0];
  M1.M[0][2] = M.M[2][0];
  M1.M[0][3] = M.M[3][0];
  M1.M[1][0] = M.M[0][1];
  M1.M[1][1] = M.M[1][1];
  M1.M[1][2] = M.M[2][1];
  M1.M[1][3] = M.M[3][1];
  M1.M[2][0] = M.M[0][2];
  M1.M[2][1] = M.M[1][2];
  M1.M[2][2] = M.M[2][2];
  M1.M[2][3] = M.M[3][2];
  M1.M[3][0] = M.M[0][3];
  M1.M[3][1] = M.M[1][3];
  M1.M[3][2] = M.M[2][3];
  M1.M[3][3] = M.M[3][3];
  return M1;
}

__inline MATR MatrMulMatr( MATR M1, MATR M2 ) 
{
  MATR r;
  INT i, j, k;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      for (r.M[i][j] = 0, k = 0; k < 4; k++)
        r.M[i][j] += M1.M[i][k] * M2.M[k][j];
  return r;
}

#define MatrMulMatr2(A, B) MatrMulMatr(A, B)


__inline DBL MatrDeterm3x3( DBL A11, DBL A12, DBL A13,
                            DBL A21, DBL A22, DBL A23,
                            DBL A31, DBL A32, DBL A33 )
{
  return A11 * A22 * A33 - A11 * A23 * A32 - A12 * A21 * A33 + 
         A12 * A23 * A31 + A13 * A21 * A32 - A13 * A22 * A31;
}

__inline DBL MatrDeterm( MATR M )
{
  return
    M.M[0][0] * MatrDeterm3x3(M.M[1][1], M.M[1][2], M.M[1][3],
                              M.M[2][1], M.M[2][2], M.M[2][3],
                              M.M[3][1], M.M[3][2], M.M[3][3]) +
    -M.M[0][1] * MatrDeterm3x3(M.M[1][0], M.M[1][2], M.M[1][3],
                               M.M[2][0], M.M[2][2], M.M[2][3],
                               M.M[3][0], M.M[3][2], M.M[3][3]) +
    M.M[0][2] * MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][3],
                              M.M[2][0], M.M[2][1], M.M[2][3],
                              M.M[3][0], M.M[3][1], M.M[3][3]) +
    -M.M[0][3] * MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][2],
                               M.M[2][0], M.M[2][1], M.M[2][2],
                               M.M[3][0], M.M[3][1], M.M[3][2]);
}

__inline MATR MatrInverse( MATR M )
{
  MATR r;
  DBL det = MatrDeterm(M);

  if (det == 0)
    return UnitMatrix;

  r.M[0][0] =
    MatrDeterm3x3(M.M[1][1], M.M[1][2], M.M[1][3],
                  M.M[2][1], M.M[2][2], M.M[2][3],
                  M.M[3][1], M.M[3][2], M.M[3][3]);
  r.M[1][0] =
    -MatrDeterm3x3(M.M[1][0], M.M[1][2], M.M[1][3],
                   M.M[2][0], M.M[2][2], M.M[2][3],
                   M.M[3][0], M.M[3][2], M.M[3][3]);
  r.M[2][0] =
    MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][3],
                  M.M[2][0], M.M[2][1], M.M[2][3],
                  M.M[3][0], M.M[3][1], M.M[3][3]);
  r.M[3][0] =
    -MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][2],
                   M.M[2][0], M.M[2][1], M.M[2][2],
                   M.M[3][0], M.M[3][1], M.M[3][2]);

  r.M[0][1] =
    MatrDeterm3x3(M.M[0][1], M.M[0][2], M.M[0][3],
                  M.M[2][1], M.M[2][2], M.M[2][3],
                  M.M[3][1], M.M[3][2], M.M[3][3]);
  r.M[1][1] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][2], M.M[0][3],
                   M.M[2][0], M.M[2][2], M.M[2][3],
                   M.M[3][0], M.M[3][2], M.M[3][3]);
  r.M[2][1] =
    MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][3],
                  M.M[2][0], M.M[2][1], M.M[2][3],
                  M.M[3][0], M.M[3][1], M.M[3][3]);
  r.M[3][1] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][2],
                   M.M[2][0], M.M[2][1], M.M[2][2],
                   M.M[3][0], M.M[3][1], M.M[3][2]);


  r.M[0][2] =
    MatrDeterm3x3(M.M[0][1], M.M[0][2], M.M[0][3],
                  M.M[1][1], M.M[1][2], M.M[1][3],
                  M.M[3][1], M.M[3][2], M.M[3][3]);
  r.M[1][2] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][2], M.M[0][3],
                   M.M[1][0], M.M[1][2], M.M[1][3],
                   M.M[3][0], M.M[3][2], M.M[3][3]);
  r.M[2][2] =
    MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][3],
                  M.M[1][0], M.M[1][1], M.M[1][3],
                  M.M[3][0], M.M[3][1], M.M[3][3]);
  r.M[3][2] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][2],
                   M.M[1][0], M.M[1][1], M.M[1][2],
                   M.M[3][0], M.M[3][1], M.M[3][2]);

  r.M[0][3] =
    MatrDeterm3x3(M.M[0][1], M.M[0][2], M.M[0][3],
                  M.M[1][1], M.M[1][2], M.M[1][3],
                  M.M[2][1], M.M[2][2], M.M[2][3]);
  r.M[1][3] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][2], M.M[0][3],
                   M.M[1][0], M.M[1][2], M.M[1][3],
                   M.M[2][0], M.M[2][2], M.M[2][3]);
  r.M[2][3] =
    MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][3],
                  M.M[1][0], M.M[1][1], M.M[1][3],
                  M.M[2][0], M.M[2][1], M.M[2][3]);
  r.M[3][3] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][2],
                   M.M[1][0], M.M[1][1], M.M[1][2],
                   M.M[2][0], M.M[2][1], M.M[2][2]);
  r.M[0][0] /= det;
  r.M[0][1] /= det;
  r.M[0][2] /= det;
  r.M[0][3] /= det;
  r.M[1][0] /= det;
  r.M[1][1] /= det;
  r.M[1][2] /= det;
  r.M[1][3] /= det;
  r.M[2][0] /= det;
  r.M[2][1] /= det;
  r.M[2][2] /= det;
  r.M[2][3] /= det;
  r.M[3][0] /= det;
  r.M[3][1] /= det;
  r.M[3][2] /= det;
  r.M[3][3] /= det;
  return r;
}

__inline MATR MatrView( VEC Loc, VEC At, VEC Up1 )
{
  VEC
    Dir = VecNormalize(VecSubVec(At, Loc)),
    Right = VecNormalize(VecCrossVec(Dir, Up1)),
    Up = VecNormalize(VecCrossVec(Right, Dir));
  MATR m =
  {
    {
      {Right.X, Up.X, -Dir.X, 0},
      {Right.Y, Up.Y, -Dir.Y, 0},
      {Right.Z, Up.Z, -Dir.Z, 0},
      {-VecDotVec(Loc, Right), -VecDotVec(Loc, Up), VecDotVec(Loc, Dir), 1}
    }
  };

  return m;
}

#endif
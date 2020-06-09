/* FILE NAME: MAIN.c
 * PROGRAMMER: GC6
 * DATE: 07.06.2020
 * PURPOSE:
 */
#include <windows.h>
#include <time.h>
#include "../def.h"
#include "../anim/rnd/rnd.h"


/* Window class name */
#define WND_CLASS_NAME "My Window Class Name"

/* Forward declaration */
LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

/* The main program function */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT CmdShow )
{
  HWND hWnd;
  MSG msg;
  WNDCLASS wc;

  /* Fill window class structure */
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_HAND);
  wc.hIcon = LoadIcon(NULL, IDI_SHIELD);
  wc.hInstance = hInstance;
  wc.lpszClassName = WND_CLASS_NAME;
  wc.lpszMenuName = NULL;
  wc.lpfnWndProc = WinFunc;

  /* Register window class */
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error regoister window class", "Error", MB_OK | MB_ICONERROR);
    return 0;
  }

  /* Window creation */
  hWnd = CreateWindow(WND_CLASS_NAME, "CGSG Primary Practice Group First Window",
    WS_OVERLAPPEDWINDOW | WS_VISIBLE,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
    NULL, NULL, hInstance, NULL);

  /* Message loop */
  while (TRUE)
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        break;
      DispatchMessage(&msg);
    }
    else
      SendMessage(hWnd, WM_TIMER, 47, 0);

  return 30;
} /* End of 'WinMain' function */

/* Main window handle function */
LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  PAINTSTRUCT ps;
  static gc6PRIM cow, Pr;

  switch (Msg)
  {
  case WM_CREATE:
    GC6_RndInit(hWnd);
    GC6_RndPrimCreateSphere(&Pr, VecSet(2, 2, 2), 2, 50, 50);
    GC6_RndPrimLoad(&cow, "cow.obj");
    SetTimer(hWnd, 30, 12, NULL);
    return 0;
  case WM_SIZE:
     GC6_RndResize(LOWORD(lParam), HIWORD(lParam));

    SendMessage(hWnd, WM_TIMER, 0, 0);

    return 0;
  case WM_KEYDOWN:
    if (wParam == VK_ESCAPE)
      SendMessage(hWnd, WM_CLOSE, 0, 0);
    return 0;
  case WM_TIMER:
    GC6_RndStart();

    /*painting stage*/
    GC6_RndPrimDraw(&Pr, MatrRotateX(clock() / 200.0));
    GC6_RndPrimDraw(&cow, MatrRotateY(-clock() / 200.0));
    GC6_RndEnd();
    hDC = GetDC(hWnd);
    GC6_RndCopyFrame(hDC);
    ReleaseDC(hWnd, hDC);
    InvalidateRect(hWnd, NULL, FALSE); 
    return 0;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    GC6_RndCopyFrame(hDC);  
    GC6_RndCopyFrame(hDC);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_CLOSE:
    if (MessageBox(hWnd, "Are you sure you want to close window?", "Close",
          MB_YESNO | MB_DEFBUTTON2 | MB_ICONQUESTION) == IDYES)
      DestroyWindow(hWnd);
    return 0;
  case WM_DESTROY:
    GC6_RndPrimFree(&Pr);//
    GC6_RndPrimFree(&cow);
    GC6_RndClose();

    KillTimer(hWnd, 30);
    PostMessage(hWnd, WM_QUIT, 0, 0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'WinFunc' function */

/* End of 'T07GLOBE.c' file */
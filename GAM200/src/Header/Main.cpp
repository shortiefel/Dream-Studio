/* Start Header**********************************************************************************/
/*!
\file Main.cpp
\team name
\software name
\authors
NAME							EMAIL									ROLE
Tan Wei Ling Felicia			weilingfelicia.tan@digipen.edu			PRODUCER
Goh	See Yong Denise				2001220@sit.singaporetech.edu.sg
Ow Jian Wen						jianwen123321@hotmail.com				TECHINCAL DIRECTOR
Chia Yi Da						chiayida98@gmail.com
Margaret Teo Boon See			Teo.b@digipen.edu
Wang Ao							Ao.Wang@digipen.edu
Ng Jia Yi						Jiayi.ng@digipen.edu
\date 26/04/2021
\brief
This file contains the starting point of the application. This is provided by Elie in CSD1130.
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "framework.hpp"
#include "Main.hpp"

#include <stdio.h>
#include "Application.hpp"


//#define MAX_LOADSTRING 100
//
//// Global Variables:
//HINSTANCE hInst;                                // current instance
//WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
//WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
//
//// Forward declarations of functions included in this code module:
//ATOM                MyRegisterClass(HINSTANCE hInstance);
//BOOL                InitInstance(HINSTANCE, int);
//LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
//
//HWND hWnd;
//
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    //use try and except (require logging)
    Application::Create();
    Application::Run();
    Application::Destroy();

    return 1;
//
//
//    if (AllocConsole())
//    {
//        FILE* file;
//
//        freopen_s(&file, "CONOUT$", "wt", stdout);
//        freopen_s(&file, "CONOUT$", "wt", stderr);
//        freopen_s(&file, "CONOUT$", "wt", stdin);
//
//        SetConsoleTitle(L"Simulation...");
//
//        printf("Simulation Starting...\n");
//    }
//
//
//    // Initialize global strings
//    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
//    LoadStringW(hInstance, IDC_WIN32TUTORIAL, szWindowClass, MAX_LOADSTRING);
//    MyRegisterClass(hInstance);
//
//    // Perform application initialization:
//    if (!InitInstance(hInstance, nCmdShow))
//    {
//        return FALSE;
//    }
//
//    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32TUTORIAL));
//
//    MSG msg;
//
//
//    // Main message loop:
//    /*while (GetMessage(&msg, nullptr, 0, 0))
//    {
//        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
//        {
//            TranslateMessage(&msg);
//            DispatchMessage(&msg);
//        }
//    }*/
//
//
//    bool loop = true;
//    while (loop)
//    {
//        //while (GetMessage(&msg, NULL, 0, 0))
//        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//        {
//            if (msg.message == WM_QUIT)
//                loop = false;
//
//            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
//            {
//                TranslateMessage(&msg);
//                DispatchMessage(&msg);
//            }
//        }
//
//        static int counterLoop;
//        if (counterLoop < 100000)
//            counterLoop++;
//        printf("counterLoop = %d\n", counterLoop);
//    }
//
//
//
//    FreeConsole();
//
//    return (int)msg.wParam;
//}
//
//
//
////
////  FUNCTION: MyRegisterClass()
////
////  PURPOSE: Registers the window class.
////
//ATOM MyRegisterClass(HINSTANCE hInstance)
//{
//    WNDCLASSEXW wcex;
//
//    wcex.cbSize = sizeof(WNDCLASSEX);
//
//    wcex.style = CS_HREDRAW | CS_VREDRAW;// | CS_NOCLOSE;
//    wcex.lpfnWndProc = WndProc;
//    wcex.cbClsExtra = 0;
//    wcex.cbWndExtra = 0;
//    wcex.hInstance = hInstance;
//    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32TUTORIAL));
//    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
//    wcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 255, 0));  //(COLOR_WINDOW+1);
//    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WIN32TUTORIAL);
//    wcex.lpszClassName = szWindowClass;
//    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));
//
//    return RegisterClassExW(&wcex);
//}
//
////
////   FUNCTION: InitInstance(HINSTANCE, int)
////
////   PURPOSE: Saves instance handle and creates main window
////
////   COMMENTS:
////
////        In this function, we save the instance handle in a global variable and
////        create and display the main program window.
////
//BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
//{
//    hInst = hInstance; // Store instance handle in our global variable
//
//    hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
//        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
//
//    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
//
//    if (!hWnd)
//    {
//        return FALSE;
//    }
//
//    ShowWindow(hWnd, nCmdShow);
//    UpdateWindow(hWnd);
//
//    return TRUE;
//}
//
////
////  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
////
////  PURPOSE: Processes messages for the main window.
////
////  WM_COMMAND  - process the application menu
////  WM_PAINT    - Paint the main window
////  WM_DESTROY  - post a quit message and return
////
////
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    // HBITMAP hBtp;
//
//    int x, y;
//    int j;
//    POINT pt[6] = { 460, 150, 500, 150, 530, 104, 700, 290, 790, 300, 460, 150 };
//    RECT rect, rect2;
//
//    switch (message)
//    {
//    case WM_CREATE:
//        // hBtp = LoadBitmap(hInst, (LPCTSTR)IDB_BITMAP1);
//       //  SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (ULONG_PTR)CreatePatternBrush(hBtp));
//        break;
//    case WM_COMMAND:
//    {
//        int wmId = LOWORD(wParam);
//        // Parse the menu selections:
//        switch (wmId)
//        {
//        case IDM_ABOUT:
//            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
//            break;
//        case IDM_EXIT:
//            DestroyWindow(hWnd);
//            break;
//        case ID_FILE_CUSTOMBUTTON:
//            SetWindowText(hWnd, L"CSD1130-Win32");
//            break;
//        default:
//            return DefWindowProc(hWnd, message, wParam, lParam);
//        }
//    }
//    break;
//    case WM_PAINT:
//    {
//        PAINTSTRUCT ps;
//        HDC hdc = BeginPaint(hWnd, &ps);
//
//        GetClientRect(hWnd, &rect);
//        for (x = 0; x < rect.right; x += 100)
//        {
//            MoveToEx(hdc, x, 0, NULL);
//            LineTo(hdc, x, rect.bottom);
//        }
//
//        for (y = 0; y < rect.bottom; y += 100)
//        {
//            MoveToEx(hdc, 0, y, NULL);
//            LineTo(hdc, rect.right, y);
//        }
//
//        MoveToEx(hdc, pt[0].x, pt[0].y, NULL);
//        PolylineTo(hdc, pt + 1, 5);
//
//        for (j = 0; j < 5; j++)
//        {
//            rect2.top = j * 100;
//            rect2.left = j * 100;
//            rect2.bottom = (j + 1) * 100;
//            rect2.right = (j + 1) * 100;
//
//            FillRect(hdc, &rect2, CreateSolidBrush(RGB(20 * (j + 1), 40 * (j + 1), 53 * (j + 1))));
//        }
//
//        EndPaint(hWnd, &ps);
//    }
//    break;
//    case WM_DESTROY:
//        PostQuitMessage(0);
//        break;
//    default:
//        return DefWindowProc(hWnd, message, wParam, lParam);
//    }
//    return 0;
//}
//
//// Message handler for about box.
//INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    UNREFERENCED_PARAMETER(lParam);
//    switch (message)
//    {
//    case WM_INITDIALOG:
//        RECT rect;
//        GetWindowRect(hWnd, &rect);
//        SetWindowPos(hDlg, 0, rect.left + 100, rect.top + 100, 322, 200, SWP_SHOWWINDOW);
//        return (INT_PTR)TRUE;
//
//    case WM_COMMAND:
//        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
//        {
//            EndDialog(hDlg, LOWORD(wParam));
//            return (INT_PTR)TRUE;
//        }
//        break;
//    }
//    return (INT_PTR)FALSE;
}
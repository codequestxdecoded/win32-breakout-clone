#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif


#include <tchar.h>
#include <windows.h>
#include <stdlib.h>


#include "breakout.h"


#include<iostream>
using namespace std;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int column_count = 6;
int block_count = 24;
vector2 pmin = {800, 50};
vector2 pmax = {1200,550};

//FPS
float _fps;
float _frametime;
float _time;
float _maxFPS = 60.0f;

void calculateFPS()
{
    static const int NUM_SAMPLES = 10;
    static float frameTimes[NUM_SAMPLES];
    static int currentFrame = 0;

    static float prevTicks = GetTickCount();

    float currentTicks;
    currentTicks = GetTickCount();



    _frametime = currentTicks - prevTicks;
    frameTimes[currentFrame % NUM_SAMPLES] = _frametime;

    prevTicks = currentTicks;

    currentFrame ++;

    int count;
    if(currentFrame < NUM_SAMPLES)
    {
        count = currentFrame;
    }
    else
    {
        count = NUM_SAMPLES;
    }

    float frameTimeAverage = 0;
    for(int i=0; i<count; i++)
    {
        frameTimeAverage += frameTimes[i];
    }
    frameTimeAverage /= count;

    if(frameTimeAverage > 0)
    {
        _fps = 1000.0f / frameTimeAverage;
    }
    else
    {
        _fps = 0;
    }
}

b2Vec2 gravity(0, 80/100.0f);
b2World world(gravity);

LPBLOCK* blocks;
LPPAD pad;




int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG msg;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               _T("Code::Blocks Template Windows App"),       /* Title Text */
               WS_OVERLAPPEDWINDOW, /* default window */
               CW_USEDEFAULT,       /* Windows decides the position */
               CW_USEDEFAULT,       /* where the window ends up on the screen */
               1280,                 /* The programs width */
               1024,                 /* and height in pixels */
               NULL,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );

     if( !hwnd )
    {
        printf("Oh shi- %d\n", GetLastError() );
    }


    breakout_init_game(pmin, pmax, &world, &pad, &blocks);


    ShowWindow( hwnd, SW_SHOWDEFAULT );
    UpdateWindow( hwnd );

    bool bQuit = false;

    while (!bQuit)
    {
        float startTicks = GetTickCount();


        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                bQuit = true;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        //UPDATE
        world.Step(1.0f/60.0f, 8, 3);
        /*
        for (b2Contact* contact = world.GetContactList(); contact; contact = contact->GetNext()){
            cout<<"collision"<<endl;

            //contact->GetFixtureB()->GetBody()->SetLinearVelocity(v);

            cout<<"s angle: "<<contact->GetFixtureA()->GetBody()->GetAngle()<<endl;
            cout<<"b angle: "<<contact->GetFixtureB()->GetBody()->GetAngle()<<endl;
            cout<<"b pos: "<<contact->GetFixtureB()->GetBody()->GetPosition().x<<" , "<<contact->GetFixtureB()->GetBody()->GetPosition().y<<endl;
        }
        cout<<endl;
        */

        for (b2Body* b = world.GetBodyList(); b; b = b->GetNext())
		{
			if (b->GetType() != b2_dynamicBody)
			{
				continue;
			}

			b2Vec2 p = b->GetPosition();

			//if (p.x <= -10.0f || 10.0f <= p.x || p.y <= 0.0f || 20.0f <= p.y)
			if(p.x <= pmin.x/100.0f || pmax.x/100.0f <= p.x || p.y <= pmin.y/100.0f || pmax.y/100.0f <= p.y)
			{
				//p.x += 0.0f;
				cout<<"test"<<endl;
			}
		}

        InvalidateRect( hwnd, NULL, TRUE );

        calculateFPS();


        //limit fps
        float frameTicks = GetTickCount() - startTicks;

        if(1000.0f / _maxFPS > frameTicks)
        {
            Sleep( (1000.0f / _maxFPS) - frameTicks);
        }
    }


    breakout_free_blocks(&world, blocks, block_count);

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return msg.wParam;
}



/*  This function is called by the Windows function DispatchMessage()  */
int mx = 0;
int my = 0;

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    //box1 = pad->body;
    switch (message)                  /* handle the messages */
    {
    case WM_CREATE:
    {

    } break;

    case WM_DESTROY:
    {
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
    }
    break;
    case WM_SIZE:
    {

        InvalidateRect(hwnd, NULL, TRUE);
    }
    break;
    case WM_MOUSEMOVE:
    {
        mx = LOWORD(lparam);
        my = HIWORD(lparam);
        //cout<<"mouse x: "<<mx<<" mouse y: "<<my<<endl;
    }
    break;

    case WM_KEYDOWN:
    {
        //b2Vec2 vel = pad->body->GetLinearVelocity();
        switch(wparam)
        {
        case VK_UP:
        {

        }

        break;

        case VK_DOWN:
        {

        }
        break;

        case VK_LEFT:
        {

        }
        break;

        case VK_RIGHT:
        {
            //vel.x += 18/100.0f;
        }
        break;
        }

    }
    break;
    case WM_KEYUP:
    {

        switch(wparam)
        {
        case VK_UP:
        {

        }
        break;
        case VK_DOWN:
        {

        }
        break;

        case VK_LEFT:
        {

        }
        break;

        case VK_RIGHT:
        {

        }
        break;


        }

    }
    break;

    case WM_PAINT:
    {
        LPRECT prc = (LPRECT)malloc(sizeof(RECT));
        GetClientRect(hwnd,prc);


        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        //dbbuffer
        HDC hdcBuffer = CreateCompatibleDC(hdc);
        HBITMAP hbmBuffer = CreateCompatibleBitmap(hdc, prc->right, prc->bottom);
        HBITMAP hbmOldBuffer = (HBITMAP)SelectObject(hdcBuffer, hbmBuffer);

        //clear screen
        HBRUSH hBrush1 = CreateSolidBrush(BREAK_WHITE);
        HBRUSH holdBrush = (HBRUSH)SelectObject(hdcBuffer, hBrush1);

        FillRect(hdcBuffer, prc, hBrush1);

        SelectObject(hdcBuffer, holdBrush);
        DeleteObject(hBrush1);




        for(int i=0; i<block_count; i++){
            //cout<<"block ["<<i<<"] x: "<<block[i]->body->GetPosition().x <<" y: "<<block[i]->body->GetPosition().y<<endl;
            block_render(hdcBuffer, blocks[i]);
        }
        pad_render(hdcBuffer, pad);

        MoveToEx(hdcBuffer, pmin.x, pmin.y, NULL);
        LineTo(hdcBuffer,   pmax.x, pmin.y);
        LineTo(hdcBuffer,   pmax.x, pmax.y);
        LineTo(hdcBuffer,   pmin.x, pmax.y);
        LineTo(hdcBuffer,   pmin.x, pmin.y);


        BitBlt(hdc, 0, 0, prc->right, prc->bottom, hdcBuffer, 0, 0, SRCCOPY);


        EndPaint(hwnd, &ps);

        ReleaseDC(hwnd, hdc);

        DeleteDC(hdcBuffer);
        DeleteObject(hbmBuffer);
        DeleteObject(hbmOldBuffer);
        free(prc);
    }
    break;
    case WM_ERASEBKGND:
    {
        //return 1;
    }break;

    case WM_GETMINMAXINFO:
    {
        LPMINMAXINFO lpMMI = (LPMINMAXINFO)lparam;
        lpMMI->ptMinTrackSize.x = 800;
        lpMMI->ptMinTrackSize.y = 850;
        InvalidateRect(hwnd, NULL, TRUE);
    }
    break;


    case WM_MOVE:
    {
        InvalidateRect(hwnd, NULL, TRUE);
    } break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wparam, lparam);
    }

    return 0;
}

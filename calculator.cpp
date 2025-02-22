#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <stdio.h>

char input1[100],input2[100],ans[100];
HWND text,fill1,fill2,button_plus,button_minus,button_multi,button_div;
double num1,num2,sum;
/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		case WM_CREATE: 
			text = CreateWindow("STATIC", "please input two nubers",WS_VISIBLE | WS_CHILD | WS_BORDER,40,10,175,20,hwnd, NULL,NULL,NULL);
			fill1 = CreateWindow("EDIT", "",WS_VISIBLE | WS_CHILD | WS_BORDER,50,50,140,20,hwnd, (HMENU) 5,NULL,NULL);
			fill2 = CreateWindow("EDIT", "",WS_VISIBLE | WS_CHILD | WS_BORDER,50,90,140,20,hwnd, (HMENU) 6,NULL,NULL);
			button_plus = CreateWindow("BUTTON", "+",WS_VISIBLE | WS_CHILD | WS_BORDER,30,130,30,20,hwnd, (HMENU) 1,NULL,NULL);
			button_minus = CreateWindow("BUTTON", "-",WS_VISIBLE | WS_CHILD | WS_BORDER,80,130,30,20,hwnd, (HMENU) 2,NULL,NULL);
			button_multi = CreateWindow("BUTTON", "*",WS_VISIBLE | WS_CHILD | WS_BORDER,130,130,30,20,hwnd, (HMENU) 3,NULL,NULL);
			button_div = CreateWindow("BUTTON", "/",WS_VISIBLE | WS_CHILD | WS_BORDER,180,130,30,20,hwnd, (HMENU) 4,NULL,NULL);
			break;

		case WM_COMMAND: 
			GetWindowText(GetDlgItem(hwnd, 5), input1, sizeof(input1));
			GetWindowText(GetDlgItem(hwnd, 6), input2, sizeof(input2));
			num1 = atof(input1);
			num2 = atof(input2);
			switch (LOWORD(wParam))
			{
			case 1:
				sum = num1 + num2;
				sprintf(ans, "%.2f",sum);
				MessageBox(hwnd, ans, "Result", MB_OK);
				break;
			case 2:
				sum = num1 - num2;
				sprintf(ans, "%.2f",sum);
				MessageBox(hwnd, ans, "Result", MB_OK);
				break;
			case 3:
				sum = num1 * num2;
				sprintf(ans, "%.2f",sum);
				MessageBox(hwnd, ans, "Result", MB_OK);
			case 4:
				if (num2 == 0)
				{	
					if (num1 != 0)
					{
					MessageBox(hwnd, "Cannot divide by zero", "Result", MB_OK | MB_OK);
					return 0;
					}else{
		
					MessageBox(hwnd, ans, "Result", MB_OK);
					return 0;
					}
				}
				sum = num1 / num2;
					sprintf(ans, "%.2f",sum);
					MessageBox(hwnd, ans, "Result", MB_OK);
					break;
				
			
			}
			break;
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(255,0,0));
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}

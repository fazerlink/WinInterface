#include <windows.h>
#include <string>
#include <vector>
#include "sqlite3.h"
#include "Iteratiron_method.h"
#include "Database.h"
TCHAR edit1[25];
TCHAR edit2[25];
TCHAR edit3[25];
TCHAR edit4[25];
std::vector <HWND> editWindow;
std::vector <HWND> outputWindow;
int fieldID = 1000;
int outputID = 2000;
int counter = 0;
int editID = 0;
int linesCounter = 0;
int fieldSaveID = 0;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK NewProc(HWND, UINT, WPARAM, LPARAM);
int MainWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hMainWnd;
	char szClassName[] = "MyClass";
	MSG msg;
	WNDCLASSEX wc;
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);


	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Cannot register class", "Error", MB_OK);
		return 0;
	}


	hMainWnd = CreateWindow(
		szClassName, "Interface", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		(HWND)NULL, (HMENU)NULL,
		(HINSTANCE)hInstance, NULL
	);

	if (!hMainWnd) {
		MessageBox(NULL, "Cannot create main window", "Error", MB_OK);
		return 0;
	}


	ShowWindow(hMainWnd, nCmdShow);
	UpdateWindow(hMainWnd);


	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hMainWnd;
	char szClassName[] = "MyClass";
	MSG msg;
	WNDCLASSEX wc;
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Cannot register class", "Error", MB_OK);
		return 0;
	}

	hMainWnd = CreateWindow(
		szClassName, "Interface", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		(HWND)NULL, (HMENU)NULL,
		(HINSTANCE)hInstance, NULL
	);

	if (!hMainWnd) {
		MessageBox(NULL, "Cannot create main window", "Error", MB_OK);
		return 0;
	}

	ShowWindow(hMainWnd, nCmdShow);
	UpdateWindow(hMainWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT ps;
	int userReply;
	int check = 0;


	switch (msg)
	{
		do {
	case WM_CREATE:
	{
		HWND hButton = CreateWindow("BUTTON", "Create", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, 140, 50,
			hWnd, reinterpret_cast<HMENU>(200), nullptr, nullptr);
		HWND hButton1 = CreateWindow("BUTTON", "Save", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 0, 140, 50,
			hWnd, reinterpret_cast<HMENU>(201), nullptr, nullptr);
		HWND hButton2 = CreateWindow("BUTTON", "Output", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300, 0, 140, 50,
			hWnd, reinterpret_cast<HMENU>(202), nullptr, nullptr);
		HWND hButton3 = CreateWindow("BUTTON", "Result", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 450, 0, 140, 50,
			hWnd, reinterpret_cast<HMENU>(203), nullptr, nullptr);


	}
	case WM_COMMAND:
	{
		switch (wParam)
		{
		case 200:
		{
			editWindow.push_back(CreateWindowEx(WS_EX_CLIENTEDGE, "edit", "", WS_CHILD | WS_VISIBLE | ES_RIGHT,
				30, 80 + counter * 30, 150, 25, hWnd, reinterpret_cast<HMENU>(fieldID), nullptr, NULL));
			fieldID++;
			editWindow.push_back(CreateWindowEx(WS_EX_CLIENTEDGE, "edit", "", WS_CHILD | WS_VISIBLE | ES_RIGHT,
				190, 80 + counter * 30, 150, 25, hWnd, reinterpret_cast<HMENU>(fieldID), nullptr, NULL));
			fieldID++;
			editWindow.push_back(CreateWindowEx(WS_EX_CLIENTEDGE, "edit", "", WS_CHILD | WS_VISIBLE | ES_RIGHT,
				350, 80 + counter * 30, 150, 25, hWnd, reinterpret_cast<HMENU>(fieldID), nullptr, NULL));
			fieldID++;
			editWindow.push_back(CreateWindowEx(WS_EX_CLIENTEDGE, "edit", "", WS_CHILD | WS_VISIBLE | ES_RIGHT,
				510, 80 + counter * 30, 150, 25, hWnd, reinterpret_cast<HMENU>(fieldID), nullptr, NULL));
			fieldID++;
			counter++;
			check = 1;
			break;

		}

		case 201:
		{
			if (counter == 0)
			{
				MessageBox(hWnd, "Nothing to save",
					"", MB_OK | MB_ICONWARNING);
			}
			for (int i = 0; i < counter; i++)
			{



				GetDlgItemText(hWnd, 1000 + fieldSaveID, edit1, 25);
				fieldSaveID++;
				GetDlgItemText(hWnd, 1000 + fieldSaveID, edit2, 25);
				fieldSaveID++;
				GetDlgItemText(hWnd, 1000 + fieldSaveID, edit3, 25);
				fieldSaveID++;
				GetDlgItemText(hWnd, 1000 + fieldSaveID, edit4, 25);
				fieldSaveID++;
				linesCounter++;
				inputInfo(edit1, edit2, edit3, edit4, linesCounter, hWnd);

			}
			fieldSaveID = 0;
			break;
		}
		case 202:
		{
			int editID = fieldID - 1000;
			for (int i = 0; i < editID; i++)
			{
				DestroyWindow(editWindow[i]);

			}


			for (int i = 1; i <= linesCounter; i++)
			{
				char* output = outputInfoLineID(i);
				outputWindow.push_back(CreateWindowEx(WS_EX_CLIENTEDGE, "edit", output, WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_READONLY,
					1, 80 + i * 30, 25, 25, hWnd, reinterpret_cast<HMENU>(outputID), nullptr, NULL));
				output = outputInfoName(i);
				outputID++;
				outputWindow.push_back(CreateWindowEx(WS_EX_CLIENTEDGE, "edit", output, WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_READONLY,
					35, 80 + i * 30, 150, 25, hWnd, reinterpret_cast<HMENU>(outputID), nullptr, NULL));
				output = outputInfoTemperature(i);
				outputID++;
				outputWindow.push_back(CreateWindowEx(WS_EX_CLIENTEDGE, "edit", output, WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_READONLY,
					195, 80 + i * 30, 150, 25, hWnd, reinterpret_cast<HMENU>(outputID), nullptr, NULL));
				output = outputInfoPressure(i);
				outputID++;
				outputWindow.push_back(CreateWindowEx(WS_EX_CLIENTEDGE, "edit", output, WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_READONLY,
					355, 80 + i * 30, 150, 25, hWnd, reinterpret_cast<HMENU>(outputID), nullptr, NULL));
				output = outputInfoMinutes(i);
				outputID++;
				outputWindow.push_back(CreateWindowEx(WS_EX_CLIENTEDGE, "edit", output, WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_READONLY,
					515, 80 + i * 30, 150, 25, hWnd, reinterpret_cast<HMENU>(outputID), nullptr, NULL));
			}
			closeDatabase();
			break;

		}
		case 203:
		{
			Iteratiron_method result;
			result.Method();
			break;
		}

		}
	}
	case WM_PAINT:
	{
		hDC = BeginPaint(hWnd, &ps);
		TextOut(hDC, 50, 55, "Result %", strlen("Result (%)"));
		TextOut(hDC, 210, 55, "Temperature °C", strlen("Temperature °C"));
		TextOut(hDC, 370, 55, "Pressure 10^6 Pa", strlen("Pressure 10^6 Pa"));
		TextOut(hDC, 530, 55, "Minutes", strlen("Minutes"));
		EndPaint(hWnd, &ps);
		return 0;
	}
	case WM_CLOSE:
	{
		userReply = MessageBox(hWnd, "Are you shure about that?",
			"", MB_YESNO | MB_ICONQUESTION);
		if (IDYES == userReply)
			DestroyWindow(hWnd);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
		} while (!hWnd);
	}
	return 0;
}

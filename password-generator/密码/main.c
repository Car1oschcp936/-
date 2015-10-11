#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
char array[10] = "0123456789";
FILE * fp;
int count = 0;
void swap(char a[], char b[], int i, int size,int x)
{
	int temp;
	if (i == x)
	{
		fwrite(b, i, 1, fp);
		fwrite("\n", 1, 1, fp);
		count++;
	}
	else
	{
		for (int j = 0; j<size; j++)
		{
			b[i] = a[j];
			temp = a[j]; a[j] = a[size - 1]; a[size - 1] = temp;
			swap(a, b, i + 1, size - 1, x);
			temp = a[j]; a[j] = a[size - 1]; a[size - 1] = temp;
		}
	}
}
int sum(int count)
{
	int temp = count;
	int j=0;
	for (int i = 10; temp != 0;)
	{
		temp = temp / i;
		j++;
	}
	return j;
}
int init(int x)
{
	int j;
	char *p=(char *)malloc(sizeof(char)*(x));
	j = fopen_s(&fp,"G:\\passwd\\pwaawd","w+");
	if (j != 0)
	{
		fclose(fp);
		return 0;
	}
	else
	{
		char a[80];
		swap(array, p, 0, 10,x);
		fwrite("-------------------\n", 20, 1, fp);
		sprintf_s(a, 17+sum(count), "一共生成了%d个密码", count);
		fwrite(a, 17 + sum(count), 1, fp);
		fclose(fp);
		return 1;
	}

}
char str[80];
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = "Hello";
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, "窗口注册失败!", "HelloWin", 0);
		return 0;
	}
	int Wwide = 120, Whigh = 300;
	int x, y;
	x = GetSystemMetrics(SM_CXSCREEN);//屏幕宽度
	y = GetSystemMetrics(SM_CYSCREEN);//屏幕高度
	hwnd = CreateWindow("Hello", "密码生成器 by:C4r1os.chcp936", WS_OVERLAPPEDWINDOW, (x-Whigh)/2, (y-Wwide)/2, Whigh, Wwide, NULL, NULL, hInstance, NULL);
	//SetWindowPos(hwnd ,NULL, (rScreen.right - (rWindow.right - rWindow.left)) / 2)
	ShowWindow(hwnd, nCmdShow);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static HWND hButton, hwndEdit[3];
	int a[3];
	char strEdit[80];
	int i;
	switch (message)
	{
	case WM_CREATE:
		hwndEdit[0] = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 70, 40, 50, 20, hwnd, NULL, NULL, NULL);
		//hwndEdit[1] = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 130, 70, 100, 25, hwnd, NULL, NULL, NULL);
		//hwndEdit[2] = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 240, 70, 100, 25, hwnd, NULL, NULL, NULL);
		hButton = CreateWindow("button", "生成", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 130, 40, 80, 20, hwnd, NULL, NULL, NULL);
		return 0;
	case WM_COMMAND:
		if (((HWND)lParam == hButton) && (HIWORD(wParam) == BN_CLICKED))
		{
			for (i = 0; i<1; i++)
			{
				GetWindowText(hwndEdit[i], strEdit, 80);
				a[i] = (float)atof(strEdit);
			}
			
			int x=init(a[0]);
			if(x==0)
				sprintf_s(str, 30, "打开文件失败");
			else
				sprintf_s(str, 30, "生成密码成功");
			//sprintf_s(str, 30, "您输入的数字为:%d", a[0]);
			//MessageBox(NULL, str, "方程的根", 0);
			//int n = GetRoot(a[0], a[1], a[2], root);
			/*if (n<1)
				strcpy_s(str, 20,"方程无根!");
			else 
				sprintf_s(str, 30,"方程的解为: %f,%f", root[0], root[1]);*/
			MessageBox(NULL, str, "提示", 0);
		}
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 30, 10, "请输入您要生成几位密码", 22);
		TextOut(hdc, 30, 40, "个数：", 12);
		TextOut(hdc, 30, 70, "@AUthor：C4r1os", 15);
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
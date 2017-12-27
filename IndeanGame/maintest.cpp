#include <iostream>
#include <stdio.h>
#include <Windows.h> //API �Լ���
#include <conio.h>
#include "resource.h"
//���ҽ��� ����ϱ� ���� �����Ϸ��� �������ִ� �������
//#include "mainD.h"

using namespace std;

static HWND hWnd; //�ܼ� ������ â�� �ڵ鰪
static HINSTANCE hlnst; //���α׷��� �ν��Ͻ� �ڵ鰪

//�׸��� �Լ�. �μ��� ����� ��ǥ ( ������ �������� ������ �۾��������� Ŀ���� �ƴ� �ȼ� ���� ) 
void Render(int x, int y, char bit) {
	HDC hDC, hMemDC; 
	//DC�� �ڵ鰪�� ���� ���� ����. ( hDC : ����ȭ�� DC, hMemDC : �̹����� ���� DC)
	//Device Context�� �׷��ȿ� �ʿ��� ��� �ɼ��� �־�� ����ü��� �� �� �ִ�. 
	//�׸� �׸��� �׸� ȭ���̶�� ���� �ȴ�. 

	static HDC hBackDC;
	//�ĸ����. 

	HBITMAP hBitmap, hOldBitmap, hBackBitmap;
	//�̹��� ��Ʈ���� �ڵ鰪�� ������ ����

	BITMAP Bitmap;
	//�ڵ鰪���κ��� ���� ���� ��Ʈ�� ����ü. 

	RECT WindowRect; 
	GetWindowRect(hWnd, &WindowRect);
	//���� �������� Rect��(ũ��)�� ���´�. Rect�� ���� ��, ������ �Ʒ��� ���� ������ ���簢���� ��Ÿ���� ����ü

	hDC = GetDC(hWnd); //���� �������� DC �ڵ鰪�� ���´�. GetWindowDC(hWnd) ����
	hBackDC = CreateCompatibleDC(hDC);
	hMemDC = CreateCompatibleDC(hDC);
	//hDC�� ȣȯ�Ǵ� DC�� �޸𸮿� ����� �ڵ鰪�� ��ȯ

	hBackBitmap = CreateCompatibleBitmap(hDC, WindowRect.right, WindowRect.bottom);
	//��Ʈ�� �޸𸮸� �Ҵ��ϰ� �ڵ��� ��ȯ
	hOldBitmap = (HBITMAP)SelectObject(hBackDC, hBackBitmap);
	//�׸� ��ȭ���� �غ� 
	hBitmap = LoadBitmap(hlnst, MAKEINTRESOURCE(bit));
	//��Ʈ���� �ε��Ͽ� �ڵ��� ��ȯ. resource.h�� ������ definde �Ǿ��ִ� �ҷ��� ���ҽ��� �ε�
	GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
	//ũ�⸦ �ޱ� ���� ��Ʈ�� ����ü�� ��Ʈ�� �ڵ�κ��� ����. 
	SelectObject(hMemDC, hBitmap);
	//�о�� ��Ʈ�� ���ҽ��� �޸� DC�� ����.

	BitBlt(hBackDC, 0, 0, Bitmap.bmWidth, Bitmap.bmHeight, hMemDC, 0, 0, SRCCOPY);
	//hMemeDC�� �̹����� hBackDC�� ���ϴ� ��ġ�� ��Ӻ����Ų��. ( ����Ϸ��� �̹����� �ĸ���ۿ� ����. )

	//hBackDC ( �ĸ���� ) �� �ϼ��� �׸��� ȭ������ ��Ӻ���. 
	BitBlt(hDC, x, y, x + Bitmap.bmWidth, y + Bitmap.bmHeight, hBackDC, 0, 0, SRCCOPY);

	//�޸𸮿� ������Ʈ ���� 
	DeleteObject(SelectObject(hBackDC, hBackBitmap));
	DeleteObject(hBitmap);
	DeleteDC(hBackDC);
	DeleteDC(hMemDC);

	ReleaseDC(hWnd, hDC);
}

//���α׷� ���� 
int main() {
	
	//�׽�Ʈ������ �Է� ���� ����
	char buf[100] = { 0, };
	int i = 0; 

	hWnd = GetConsoleWindow(); //�ܼ� ������ â�� �ڵ鰪 ���´�.
	hlnst = GetModuleHandle(NULL);//���α׷� �ν��Ͻ� �ڵ鰪 ����. 


	printf("\n\n\n\n\n\n\n\n\n\n\n\n1234");

	//������ ���� 
	while (1) {
		Render(10, 10, IDB_BITMAP1); //�Է½� ���α׷��� ����Ͽ� Render�� ȣ����� �ʴ� ���� �����ϱ� ���� �Է¹�� �ʿ�. 
	}
	cout << "1234";
	return 0; 

}
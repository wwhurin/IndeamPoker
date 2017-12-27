#include <Windows.h>
#include <iostream>
using namespace std;

static HWND hWnd; //�ܼ� ������ â�� �ڵ鰪
static HINSTANCE hlnst; //���α׷��� �ν��Ͻ� �ڵ鰪

void gotoxy(int x, int y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void textcolor(int color_number) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}

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

	hWnd = GetConsoleWindow(); //�ܼ� ������ â�� �ڵ鰪 ���´�.
	hlnst = GetModuleHandle(NULL);//���α׷� �ν��Ͻ� �ڵ鰪 ����. 

	return;

}

void drawCard(int x, int y) {
	int startx = x; int starty = y;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j <10; j++) {
			gotoxy(x, y);
			textcolor(0x00FF);
			printf("��");
			x++; 
		}
		x = startx;
		y++;
		cout << endl;
	}
}

void drawLine(int x, int y) {
	gotoxy(x, y);
	for (int i = 0; i < 65; i++) {
		 textcolor(0x00FF);  cout << "��";
	}
}

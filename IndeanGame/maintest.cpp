#include <iostream>
#include <stdio.h>
#include <Windows.h> //API 함수용
#include <conio.h>
#include "resource.h"
//리소스를 사용하기 위해 컴파일러가 생성해주는 헤어파일
//#include "mainD.h"

using namespace std;

static HWND hWnd; //콘솔 윈도우 창의 핸들값
static HINSTANCE hlnst; //프로그램의 인스턴스 핸들값

//그리는 함수. 인수는 출력할 좌표 ( 윈도우 프레임을 제외한 작업영역에서 커서가 아닌 픽셀 기준 ) 
void Render(int x, int y, char bit) {
	HDC hDC, hMemDC; 
	//DC의 핸들값을 받을 변수 선언. ( hDC : 실제화면 DC, hMemDC : 이미지를 담을 DC)
	//Device Context는 그래픽에 필요한 모든 옵션을 넣어둔 구조체라고 볼 수 있다. 
	//그림 그릴때 그릴 화폭이라고 보면 된다. 

	static HDC hBackDC;
	//후면버퍼. 

	HBITMAP hBitmap, hOldBitmap, hBackBitmap;
	//이미지 비트맵의 핸들값을 저장할 변수

	BITMAP Bitmap;
	//핸들값으로부터 얻어올 실제 비트맵 구조체. 

	RECT WindowRect; 
	GetWindowRect(hWnd, &WindowRect);
	//현재 윈도우의 Rect값(크기)를 얻어온다. Rect는 왼쪽 위, 오른쪽 아래의 값을 가지는 정사각형을 나타내는 구조체

	hDC = GetDC(hWnd); //현재 윈도우의 DC 핸들값을 얻어온다. GetWindowDC(hWnd) 가능
	hBackDC = CreateCompatibleDC(hDC);
	hMemDC = CreateCompatibleDC(hDC);
	//hDC와 호환되는 DC를 메모리에 만들어 핸들값을 반환

	hBackBitmap = CreateCompatibleBitmap(hDC, WindowRect.right, WindowRect.bottom);
	//비트맵 메모리를 할당하고 핸들을 반환
	hOldBitmap = (HBITMAP)SelectObject(hBackDC, hBackBitmap);
	//그릴 도화지를 준비 
	hBitmap = LoadBitmap(hlnst, MAKEINTRESOURCE(bit));
	//비트맵을 로드하여 핸들을 반환. resource.h에 정수로 definde 되어있는 불러온 리소스를 로드
	GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
	//크기를 받기 위해 비트맵 구조체를 비트맵 핸들로부터 생성. 
	SelectObject(hMemDC, hBitmap);
	//읽어온 비트맵 리소스를 메모리 DC에 선택.

	BitBlt(hBackDC, 0, 0, Bitmap.bmWidth, Bitmap.bmHeight, hMemDC, 0, 0, SRCCOPY);
	//hMemeDC의 이미지를 hBackDC의 원하는 위치로 고속복사시킨다. ( 출력하려는 이미지를 후면버퍼에 복사. )

	//hBackDC ( 후면버퍼 ) 의 완성된 그림을 화면으로 고속복사. 
	BitBlt(hDC, x, y, x + Bitmap.bmWidth, y + Bitmap.bmHeight, hBackDC, 0, 0, SRCCOPY);

	//메모리와 오브젝트 해지 
	DeleteObject(SelectObject(hBackDC, hBackBitmap));
	DeleteObject(hBitmap);
	DeleteDC(hBackDC);
	DeleteDC(hMemDC);

	ReleaseDC(hWnd, hDC);
}

//프로그램 진입 
int main() {
	
	//테스트용으로 입력 받을 버퍼
	char buf[100] = { 0, };
	int i = 0; 

	hWnd = GetConsoleWindow(); //콘솔 윈도우 창의 핸들값 얻어온다.
	hlnst = GetModuleHandle(NULL);//프로그램 인스턴스 핸들값 얻어옴. 


	printf("\n\n\n\n\n\n\n\n\n\n\n\n1234");

	//루프를 돈다 
	while (1) {
		Render(10, 10, IDB_BITMAP1); //입력시 프로그램이 대기하여 Render이 호출되지 않는 것을 방지하기 위한 입력방법 필요. 
	}
	cout << "1234";
	return 0; 

}
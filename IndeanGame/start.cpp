
#include <iostream>
#include <conio.h>
#include "fuction.h"
#include "mainD.h"
#include "resource.h"
#include "poker.h"
using namespace std;



int main() {
	consolsize();//콘솔 사이즈 정하기 
	
	cout << "wwhurin";//2606 김효린

	int menu = 0; 
	gotoxy(60, 10);
	textcolor(0x000E);
	cout << "INDEAN";  textcolor(7);
	cout << " GAME";
	gotoxy(51, 13);
	cout << "○ Indean Porker [ 인디언포커 ] ";
	gotoxy(51, 14);
	cout << "○ Indean Holdem [ 인디언홀덤 ] ";
	gotoxy(51, 15);
	cout << "○ How To Play [ 플레이 방법 ] " << endl;

	gotoxy(51, 13);
	cout << ">";


	for (int i = 0; i <=1;i++)
		Render(560, 400, IDB_BITMAP1);  

	for (int i = 0; i <= 1; i++)
		Render(650, 400, IDB_BITMAP2);

	for (int i = 0; i <= 1; i++)
		Render(740, 400, IDB_BITMAP3);

	for (int i = 0; i <= 1; i++)
		Render(830, 400, IDB_BITMAP4);

	
	int key = _getch();
	int y = 13;

	while (1) {
		key = _getch();
		if ((key == 72 || key == 80) && (y >= 13 && y <= 15)) {
			gotoxy(51, y); cout << "○";
			if (key == 80) {
				++y;	if (y == 16) y = 15;
			}
			else {
				--y;	 if (y == 12) y = 13;
			}
			gotoxy(51, y);
			cout << ">";
		}
		if (key == 13) { menu = y; break; }
	}

	switch (menu)
	{
	case 13 :
		poker(); break;
	case 14:
		break;
	case 15:
		break;
	default:
		break;
	}

	/*do{
		key = _getch();
	} while (key != 80);
	int y; 
	y = 13;

	do{
		if ((key == 72 || key == 80)&&(y >=13 && y <=15)) {
			gotoxy(51, y); cout << "○";
			if (key == 80) {
				++y;	if (y == 16) y = 15;
			}
			else { 
				--y;	 if (y == 12) y = 13; 
			}
			gotoxy(51, y);
			cout << ">";
		}
		key = _getch(); 
	}while (key != 13);
*/

	//poker();
	

	return 0; 	gotoxy(130, 40);
}

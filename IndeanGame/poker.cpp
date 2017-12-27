#include <iostream>
#include <conio.h>
#include <time.h>
#include<Windows.h>
#include "fuction.h"
#include "fuction.h"
#include "resource.h"
using namespace std;
#define CARD_X 57

#define COM_Y 2 
#define P_Y 29 

#define COMMAN_X 51
#define COMMAN_Y 20


struct Card{
	int cardnum = 0;
	int cardS;
};

void poker() {
	system("cls");
	cout << "wwhurin";//2606김효린

	char *card_shape[2] = { "♥", "♠" }; //카드 모양, 20개의 카드만 사용하므로 종류는 2개만 사용한다
	int card_num[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };//각각의 번호는 2번씩만 나와야한다 
	int com_chip = 17, p_chip = 17;//칩이 0개가 되면 종료해야하며 보유 칩 이상은 베팅 못한다

	int s = -1, cnt=1;
	int com_bet=1, p_bet=1;
	int p_bet_in=0, com_bet_in=0;
	boolean com_allin_chk = false, p_allin_chk = false;
	boolean com_f = false, p_f = false;
	Card log[20];

	gotoxy(60, 10);  cout << "게임을 시작합니다.";  Sleep(1000);

	//그리기 
	
	drawLine(0, 13); //line1
	drawLine(0, 26);//line2
	

	


	while (1) {
		srand((unsigned int)time(NULL));
		Card computer;
		Card player;
		drawCard(CARD_X, COM_Y);//컴퓨터 카드 그리기
		drawCard(CARD_X, P_Y);//사용자 카드 그리기 

		textcolor(0x000F);
		
		gotoxy(3, 15); cout << "컴퓨터 베팅 수 : "; gotoxy(15, 15); cout << com_bet;
		gotoxy(3, 24); cout << "사용자 베팅 수 : "; gotoxy(15, 24); cout << p_bet;
		gotoxy(100, 1); cout << "컴퓨터 칩 수 : "; gotoxy(117, 1); cout << com_chip;
		gotoxy(100, 38); cout << "플레이어 칩 수 : "; gotoxy(117, 38);  cout << p_chip;
		gotoxy(3, 22); cout << "플레이어 현재 베팅 수 : " << p_bet_in;
		gotoxy(3, 17); cout << "컴퓨터 현재 베팅 수 : " << com_bet_in;

		gotoxy(COMMAN_X, COMMAN_Y); cout << "                                                                                              ";
		gotoxy(COMMAN_X - 10, COMMAN_Y + 1); cout << "                                                                                 ";

		
	   gotoxy(COMMAN_X, COMMAN_Y); cout << "컴퓨터가 카드를 듭니다…"; Sleep(1000);
		computer.cardnum = rand() % 10 + 1; computer.cardS = rand() % 2;
		for (int i = 0; i < s; i++) {
			if ((log[i].cardnum == computer.cardnum) && (log[i].cardS == computer.cardS)) {
				computer.cardnum = rand() % 10 + 1;
				computer.cardS = rand() % 2;
				i = 0;
			}
		}

		
		 //textcolor(card_color[(int)computer.cardS]);  
		if (computer.cardS == 0)
			textcolor(0x00FC);
		else
			textcolor(0x00F0);
		gotoxy(CARD_X, COM_Y); cout << card_shape[computer.cardS];
		gotoxy(CARD_X + 9, COM_Y + 8);  cout << card_shape[computer.cardS];
		gotoxy(62, COM_Y+4); cout << computer.cardnum;

		textcolor(0x000F);  gotoxy(COMMAN_X, COMMAN_Y); cout << "플레이어가 카드를 듭니다…"; Sleep(1000);
		player.cardnum = rand() % 10 + 1; player.cardS = rand() % 2;
		for (int i = 0; i < s; i++) {
			if ((log[i].cardnum == player.cardnum) && (log[i].cardS == player.cardS)) {
				player.cardnum = rand() % 10 + 1;
				player.cardS = rand() % 2;
				i = 0;
			}
		}

		gotoxy(COMMAN_X, COMMAN_Y); cout << "                                                                                              ";
		gotoxy(COMMAN_X, COMMAN_Y); textcolor(0x000C); cout << cnt<<"라운드";  cout << "베팅"; textcolor(0x000F); cout << "을 시작합니다." << endl;
		gotoxy(COMMAN_X, COMMAN_Y+1); cout << "포기는 -1을 베팅하세요.";
		Sleep(1000);

		do{

			gotoxy(COMMAN_X, COMMAN_Y); cout << "                                                                                              ";
			gotoxy(COMMAN_X - 10, COMMAN_Y + 1); cout << "                                                                                 ";

			gotoxy(COMMAN_X, COMMAN_Y);
			cout << "플레이어가 베팅합니다."<< endl;	
			do{
				gotoxy(COMMAN_X - 10, COMMAN_Y + 1); cout << "몇개를 베팅하시나요? 베팅 후 엔터를 눌러주세요 : ";
				cin >> p_bet_in;
				//if()
				if (p_bet_in == p_chip) {//플레이어의 올인 체크
					gotoxy(COMMAN_X, COMMAN_Y); cout << "                                                                                              ";
					gotoxy(COMMAN_X, COMMAN_Y); textcolor(0x000C); cout << "올인."; p_allin_chk = true;
					textcolor(0x000F); Sleep(1000);  break;
				}
				if (p_bet_in == -1) {//포기 체크
					gotoxy(COMMAN_X, COMMAN_Y); cout << "                                                                                              ";
					gotoxy(COMMAN_X - 10, COMMAN_Y + 1); cout << "                                                                                                  ";
					gotoxy(COMMAN_X, COMMAN_Y); textcolor(0x000C); cout << "라운드 포기.";
					textcolor(0x000F); p_f = true; break;
				}
				if ((p_chip - p_bet_in) < 0 || com_bet_in > p_bet_in || p_bet_in < 0) {//잘못 베팅
					gotoxy(COMMAN_X - 10, COMMAN_Y + 1); cout << "올바른 베팅이 아닙니다. 다시 입력해주세요.";
				}
				else 
				{//옳은 베팅
					p_chip -= p_bet_in; p_bet += p_bet_in;  break;
				}
			}while (1);
			gotoxy(3, 24); cout << "플레이어 총 베팅 수 : "<< p_bet;
			gotoxy(100, 38); cout << "플레이어 칩 수 : "; cout << "   "; gotoxy(117, 38); cout << p_chip;
			gotoxy(3, 22); cout << "플레이어 현재 베팅 수 : " << p_bet_in;

			if (p_f) break;
			if (p_bet_in == com_bet_in) break;

			gotoxy(COMMAN_X, COMMAN_Y); cout << "                                                                                 ";
			gotoxy(COMMAN_X - 10, COMMAN_Y + 1); cout << "                                                                                 ";

			gotoxy(COMMAN_X, COMMAN_Y); 
			cout << "컴퓨터가 베팅합니다."; Sleep(1000);
			while(1){
				com_bet_in = rand() % com_chip;

				if (p_allin_chk||(p_bet_in>com_chip)) {
					if (p_allin_chk) {
						gotoxy(COMMAN_X, COMMAN_Y); cout << "                                                                                 ";
						gotoxy(COMMAN_X - 10, COMMAN_Y + 1); cout << "                                                                                 ";
						gotoxy(COMMAN_X, COMMAN_Y); cout << "플레이어의 올인.";
					}
					if (com_bet_in != 1) {
						cout << "컴퓨터 올인합니다.      "; p_bet = p_chip;  break;
					}
					else
						com_f = true;
				}

				if (com_f) {
					gotoxy(COMMAN_X, COMMAN_Y); cout << "                                                                                              ";
					gotoxy(COMMAN_X - 10, COMMAN_Y + 1); cout << "                                                                                                  ";
					gotoxy(COMMAN_X, COMMAN_Y); textcolor(0x000C); cout << "컴퓨터의 라운드 포기.";
					textcolor(0x000F); com_f = true; break;
				}
				
				if ((com_chip - com_bet_in) < 0 || com_bet_in < p_bet_in || com_bet_in < 0)
					continue;
				else
				{
					com_chip -= com_bet_in; 
					com_bet += com_bet_in;  
					break;
				}
			} 
			gotoxy(3, 15); cout << "컴퓨터 총 베팅 수 : "<< com_bet;
			gotoxy(99, 1); cout << "컴퓨터 칩 수 : ";  cout << "      "; gotoxy(117, 1);  cout << com_chip;
			gotoxy(3, 17); cout << "컴퓨터 현재 베팅 수 : " << com_bet_in;

			if (com_f) break;
			if (p_bet_in == com_bet_in) break;

		}while (true);

		gotoxy(COMMAN_X, COMMAN_Y); cout << "                                                                                              ";
		gotoxy(COMMAN_X - 10, COMMAN_Y + 1); cout << "                                                                                 ";

		gotoxy(COMMAN_X, COMMAN_Y); textcolor(0x000C); cout << "베팅 종료. "; Sleep(1500);
		textcolor(0x000F); cout << "본인의 카드를 확인합니다."; Sleep(1500);

		gotoxy(CARD_X, P_Y); 
		if (player.cardS == 0)
			textcolor(0x00FC);
		else
			textcolor(0x00F0);
		cout << card_shape[player.cardS];
		gotoxy(CARD_X + 9, P_Y + 8);  cout << card_shape[player.cardS];
		gotoxy(62, P_Y+4); cout << player.cardnum;
		Sleep(1500);

		textcolor(0x000F);
		if (computer.cardnum > player.cardnum||p_f) {
			com_chip += com_bet;
			com_chip += p_bet;
			p_chip -= p_bet;
			gotoxy(COMMAN_X, COMMAN_Y); cout << "                                                                                              ";
			gotoxy(COMMAN_X - 10, COMMAN_Y + 1); cout << "                                                                                 ";
			gotoxy(COMMAN_X, COMMAN_Y); cout << "컴퓨터 승리."; Sleep(1500);
		}
		else {
			p_chip += com_bet;
			p_chip += p_bet;
			com_chip -= com_bet;
			gotoxy(COMMAN_X, COMMAN_Y); cout << "                                                                                              ";
			gotoxy(COMMAN_X - 10, COMMAN_Y + 1); cout << "                                                                                 ";
			gotoxy(COMMAN_X, COMMAN_Y); cout << "플레이어의 승리.";  Sleep(1500);
		}
		

		log[++s].cardnum = computer.cardnum; log[s].cardS = computer.cardS;
		log[++s].cardnum = player.cardnum; log[s].cardS = player.cardS;


		if (com_chip <= 0 || p_chip <= 0) break;

		com_bet = 0; p_bet = 0;
		com_bet_in = 0; p_bet_in = 0;
		p_allin_chk = false; com_allin_chk = false;
		p_f = false; com_f = false;
		cnt++;
		
		gotoxy(COMMAN_X, COMMAN_Y); cout << "다음 라운드를 진행합니다."; Sleep(2000);
	}


	//cout << endl << endl << endl;
}
//ヘッダーをインクルードする場所
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

//定数を宣言する場所
//フィールドの大きさを定義する
#define FIELD_WIDTH 24
#define FIELD_HEIGHT 24

//セルの生死を定義する
int cells[2][FIELD_HEIGHT][FIELD_WIDTH];

//現在のフィールドのセルを定義
int current;

//カーソルの場所を宣言する
int cursorX, cursorY;

//生きているセルをカウントする
int getAdjacentLivesCount(int _x, int _y) {
	//カウントを定義する
	int count = 0;

	//原点のセルの相対座標を調べる
	for (int y = -1; y <= 1; y++)
		for (int x = -1; x <= 1; x++) {
			//原点自身をスルーする
			if ((x == 0) && (y == 0))
				continue;

			//それぞれの相対座標のxを定義する
			int x2 = (FIELD_WIDTH + _x + x) % FIELD_WIDTH;//原点のxと相対座標のxを足す。範囲外は足さない
			//それぞれの相対座標のyを定義する
			int y2 = (FIELD_HEIGHT + _y + y) % FIELD_HEIGHT;//原点のyと相対座標のxを足す。範囲外は足さない
			//相対座標にいるセルをカウントする
			count += cells[current][y2][x2];
		}

	//カウントされた数を返す
	return count;
}

//メイン
int main() {
	while (1)//ループ
	{
		system("cls");//再描画する
		//上下に反復する
		for (int y = 0; y < FIELD_HEIGHT; y++) {
			//左右に反復する
			for (int x = 0; x < FIELD_WIDTH; x++)
				//カーソルの位置に◎を置く
				if ((x == cursorX) && (y == cursorY))
					printf("◎");
				else//それ以外
					//セルが生きていたら■、それ以外は・
					printf("%s", cells[current][y][x] ? "■" : "・");

			//デバック用
			/*if ((x == cursorX) && (y == cursorY))
				printf("@");
			else
				printf("%d", getAdjacentLivesCount(x,y));
			*/

			printf("\n");//改行する

		}
		//wasdが入力されたとき
		switch (_getch()) {
		case 'w': cursorY--;  break;//カーソルが上へ行く
		case 's': cursorY++;  break;//カーソルが下へ行く
		case 'a': cursorX--;  break;//カーソルが左へ行く
		case 'd': cursorX++;  break;//カーソルが右へ行く
		case ' ': cells[current][cursorY][cursorX] ^= 1; break;//セルが生きているとする
		case 0x1b://エスケープキーが押されたときフィールドをクリアする
			//上下に反復する
			for (int y = 0; y < FIELD_HEIGHT; y++)
				//左右に反復する
				for (int x = 0; x < FIELD_WIDTH; x++)
					cells[current][y][x] = 0;
			break;
		case '\r'://エンターを押すとすべてのセルをチャックする
			//上下に反復する
			for (int y = 0; y < FIELD_HEIGHT; y++) 
				//左右に反復する
				for (int x = 0; x < FIELD_WIDTH; x++) {
					//すべての生きているセルを数える
					int n = getAdjacentLivesCount(x, y);
					//次のセルの状態を現在のセルの状態に初期化する
					int next = cells[current][y][x];

					//セルが生きていたら
					if (cells[current][y][x]) {
						//隣接しているセルが1以下もしくは4以上の場合
						if ((n <= 1) || (n >= 4))
							//死滅
							next = 0;
					}
					//セルが死んでいたら
					else {
						//隣接しているセルが3なら
						if (n == 3)
							//誕生
							next = 1;
					}
					//次の世代のセル
					cells[current ^ 1][y][x] = next;
				}
			//現在のcurrentが1なら0へ、0なら1へ
			current ^= 1;
			break;
		}
	}
}
//�w�b�_�[���C���N���[�h����ꏊ
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

//�萔��錾����ꏊ
//�t�B�[���h�̑傫�����`����
#define FIELD_WIDTH 24
#define FIELD_HEIGHT 24

//�Z���̐������`����
int cells[2][FIELD_HEIGHT][FIELD_WIDTH];

//���݂̃t�B�[���h�̃Z�����`
int current;

//�J�[�\���̏ꏊ��錾����
int cursorX, cursorY;

//�����Ă���Z�����J�E���g����
int getAdjacentLivesCount(int _x, int _y) {
	//�J�E���g���`����
	int count = 0;

	//���_�̃Z���̑��΍��W�𒲂ׂ�
	for (int y = -1; y <= 1; y++)
		for (int x = -1; x <= 1; x++) {
			//���_���g���X���[����
			if ((x == 0) && (y == 0))
				continue;

			//���ꂼ��̑��΍��W��x���`����
			int x2 = (FIELD_WIDTH + _x + x) % FIELD_WIDTH;//���_��x�Ƒ��΍��W��x�𑫂��B�͈͊O�͑����Ȃ�
			//���ꂼ��̑��΍��W��y���`����
			int y2 = (FIELD_HEIGHT + _y + y) % FIELD_HEIGHT;//���_��y�Ƒ��΍��W��x�𑫂��B�͈͊O�͑����Ȃ�
			//���΍��W�ɂ���Z�����J�E���g����
			count += cells[current][y2][x2];
		}

	//�J�E���g���ꂽ����Ԃ�
	return count;
}

//���C��
int main() {
	while (1)//���[�v
	{
		system("cls");//�ĕ`�悷��
		//�㉺�ɔ�������
		for (int y = 0; y < FIELD_HEIGHT; y++) {
			//���E�ɔ�������
			for (int x = 0; x < FIELD_WIDTH; x++)
				//�J�[�\���̈ʒu�Ɂ���u��
				if ((x == cursorX) && (y == cursorY))
					printf("��");
				else//����ȊO
					//�Z���������Ă����灡�A����ȊO�́E
					printf("%s", cells[current][y][x] ? "��" : "�E");

			//�f�o�b�N�p
			/*if ((x == cursorX) && (y == cursorY))
				printf("@");
			else
				printf("%d", getAdjacentLivesCount(x,y));
			*/

			printf("\n");//���s����

		}
		//wasd�����͂��ꂽ�Ƃ�
		switch (_getch()) {
		case 'w': cursorY--;  break;//�J�[�\������֍s��
		case 's': cursorY++;  break;//�J�[�\�������֍s��
		case 'a': cursorX--;  break;//�J�[�\�������֍s��
		case 'd': cursorX++;  break;//�J�[�\�����E�֍s��
		case ' ': cells[current][cursorY][cursorX] ^= 1; break;//�Z���������Ă���Ƃ���
		case 0x1b://�G�X�P�[�v�L�[�������ꂽ�Ƃ��t�B�[���h���N���A����
			//�㉺�ɔ�������
			for (int y = 0; y < FIELD_HEIGHT; y++)
				//���E�ɔ�������
				for (int x = 0; x < FIELD_WIDTH; x++)
					cells[current][y][x] = 0;
			break;
		case '\r'://�G���^�[�������Ƃ��ׂẴZ�����`���b�N����
			//�㉺�ɔ�������
			for (int y = 0; y < FIELD_HEIGHT; y++) 
				//���E�ɔ�������
				for (int x = 0; x < FIELD_WIDTH; x++) {
					//���ׂĂ̐����Ă���Z���𐔂���
					int n = getAdjacentLivesCount(x, y);
					//���̃Z���̏�Ԃ����݂̃Z���̏�Ԃɏ���������
					int next = cells[current][y][x];

					//�Z���������Ă�����
					if (cells[current][y][x]) {
						//�אڂ��Ă���Z����1�ȉ���������4�ȏ�̏ꍇ
						if ((n <= 1) || (n >= 4))
							//����
							next = 0;
					}
					//�Z��������ł�����
					else {
						//�אڂ��Ă���Z����3�Ȃ�
						if (n == 3)
							//�a��
							next = 1;
					}
					//���̐���̃Z��
					cells[current ^ 1][y][x] = next;
				}
			//���݂�current��1�Ȃ�0�ցA0�Ȃ�1��
			current ^= 1;
			break;
		}
	}
}
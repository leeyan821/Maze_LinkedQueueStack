#define _CRT_SECURE_NO_WARNINGS
#include "Maze.h"
using namespace std;

class MazeGame {
	char** map = NULL;
	int width;
	int height;
	int ER = 0;
	int EC = 0;
	Maze maze;
	LinkedStack stackMaze;
	LinkedStack enemy;
public:
	void in(int w, int h) //map ������ �迭�� �������� �Ҵ�
	{
		map = new char* [h];
		for (int i = 0; i < h; i++)
			map[i] = new char[w];
	}
	void ReadFile(const char* filename)	//���� ���� �� ũ�� ���
	{
		char c;
		ifstream fp(filename);
		if (fp.fail())
			printf("Error: ������ �������� �ʽ��ϴ�.");

		//�̷� ũ�� ���
		FILE* fd = fopen(filename, "r");
		int word = 0;
		height = 1;
		width = 0;
		while ((c = getc(fd)) != EOF) {
			if (c == '\n') height++;
			if (c == '0' || c == '1' || c == 'e' || c == 'x')
			{
				word++;
			}
		}
		width = word / height;

		//map �������迭 �������� �Ҵ�
		in(width, height);

		//map �������迭�� �̷� ����
		for (int i = 0; i < height; i++)
		{
			for (int z = 0; z < width; z++)
			{
				fp >> c;
				map[i][z] = c;
				if (map[i][z] == 'e')
				{
					stackMaze.push(new Node(i, z));
				}
			}
		}
		fclose(fd);
		fp.close();
	}
	void showMap() {
		//printf("��ü �̷��� ũ�� = %d X %d \n", width, height);
		printf("\n\n  [ Map ]\n\n");
		for (int i = 0; i < height; i++)
		{
			for (int z = 0; z < width; z++)
			{
				if (map[i][z] == '0') //��
				{
					cout << "  ";
				}
				else if (map[i][z] == '1') //��
				{
					cout << "��";
				}
				else if (map[i][z] == 'e') //�Ա�
				{
					cout << "o ";
				}
				else if (map[i][z] == 'x') //�ⱸ
				{
					cout << "x ";
				}
				else if (map[i][z] == '.') //������ ��
				{
					cout << "* ";
				}
				else if (map[i][z] == '2')	//��
				{
					std::cout << "��";
				}
			}
			cout << endl;
		}
		cout << endl;
	}
	//Ž�� ���� �� ���
	void ReGame(int cnt)
	{
		cnt++;
		stackMaze.pop();
		system("cls");
		printf("\n!Ž�� ����!\n");
		printf("=====[ Result ]=====\n");
		printf("�̵�: %d��", cnt);
		showMap();
		return;
	}
	void MakeE()	//�� ��ġ ����
	{
		for (int i = 1; i < height-1; i++)
		{
				for (int z = width - 1; z > 0; z--)
				{
					if (map[i][z] == '0')
					{
						map[i][z] = '2';
						ER = z; EC = i;
						printf("%d %d", i, z);
						return;
					}
			}
		}
	}
	//�̷� ���� ver2
	void MazeGameStack()
	{
		int num = 0;
		LinkedStack enemy;
		bool ene = false;
		MakeE();
		printf("Enemy is Coming!! Move.");
		//ù ��ġ push
		enemy.push(new Node(EC, ER));
		showMap();
		int cnt = 0;

		while (stackMaze.isEmpty() == false)
		{
			Node* here = stackMaze.peek();
			int r = here->row;
			int c = here->col;
			Node* enemyHere = enemy.peek();

			srand((unsigned int)time(NULL));//���� ��
			int er = enemyHere->row;
			int ec = enemyHere->col;

			//�� �������� �����̱�
			while (1) {
				int nu = rand() % 4;	//0,1,2,3 ����
				map[er][ec] = '0';

				switch (nu)
				{
				case 0:	//�� �̵�
					if (er - 1 >= 0 && ec >= 0 && er - 1 < height && ec < width && map[er - 1][ec] == '0')//����� ����� ���
					{
						enemy.pop();
						enemy.push(new Node(er - 1, ec));
						map[er - 1][ec] = '2';
						break;
					}
					else if (er - 1 >= 0 && ec >= 0 && er - 1 < height && ec < width && map[er - 1][ec] == '.')	//�ڽ��� ���� ��� ��ġ�� ��� ����
					{
						enemy.pop();
						map[er - 1][ec] = '2';
						printf("==== You Lose!! ====\n");
						showMap();
						return;
					}
					else
						continue;
				case 1:	//�� �̵�
					if (er + 1 >= 0 && ec >= 0 && er + 1 < height && ec < width && map[er + 1][ec] == '0')//�ϴ��� ����� ���
					{
						enemy.pop();
						enemy.push(new Node(er + 1, ec));
						map[er + 1][ec] = '2';
						break;
					}
					else if (er + 1 >= 0 && ec >= 0 && er + 1 < height && ec < width && map[er + 1][ec] == '.')	//�ڽ��� ���� �ϴܿ� ��ġ�� ��� ����
					{
						enemy.pop();
						map[er + 1][ec] = '2';
						printf("==== You Lose!! ====\n");
						showMap();
						return;
					}					
					else
						continue;
				case 2:	//�� �̵�
					if (er >= 0 && ec - 1 >= 0 && er < height && ec - 1 < width && map[er][ec - 1] == '0')//������ ����� ���
					{
						enemy.pop();
						enemy.push(new Node(er, ec - 1));
						map[er][ec - 1] = '2';
						break;
					}
					else if (er >= 0 && ec - 1 >= 0 && er < height && ec - 1 < width && map[er][ec - 1] == '.')	//�ڽ��� ���� ������ ��ġ�� ��� ����
					{
						enemy.pop();
						map[er][ec - 1] = '2';
						printf("==== You Lose!! ====\n");
						showMap();
						return;
					}
					else
						continue;
				case 3:	//�� �̵�
					if (er >= 0 && ec + 1 >= 0 && er < height && ec + 1 < width && map[er][ec + 1] == '0')//������ ����� ���
					{
						enemy.pop();
						enemy.push(new Node(er, ec + 1));
						map[er][ec + 1] = '2';
						break;
					}
					else if (er >= 0 && ec + 1 >= 0 && er < height && ec + 1 < width && map[er][ec + 1] == '.')	//�ڽ��� ���� ������ ��ġ�� ��� ����
					{
						enemy.pop();
						map[er][ec + 1] = '2';
						printf("==== You Lose!! ====\n");
						showMap();
						return;
					}
					else
						continue;
				}
				break;
			}

			//���� �����̱�
			printf("���ؼ� �̵��ϼ���.\n");
			printf("enter\n");
			int key;	//�̵� ���� Ű���� �Է�
			key = maze.get_Enterkey();

			switch (key)
			{
			case 72:	//��
				if(r - 1 >= 0 && c >= 0 && r - 1 < height && c < width && map[r - 1][c] == 'x') {	//��� �������� ��� �Ϸ�
					map[r][c] = '0';
					map[r - 1][c] = '.';
					ReGame(cnt); return;
				}
				else if (r - 1 >= 0 && c >= 0 && r - 1 < height && c < width && map[r - 1][c] == '0')	//��� �̵� ���� ���
				{
					map[r][c] = '0';
					map[r - 1][c] = '.';
					stackMaze.pop();
					stackMaze.push(new Node(r - 1, c));
				}
				else if (r - 1 >= 0 && c >= 0 && r - 1 < height && c < width && map[r - 1][c] == '2')	//��� ���� �ִ� ��� ����
				{
					map[r][c] = '0';
					map[r - 1][c] = '2';
					system("cls");
					printf("==== You Lose!! ====\n");
					showMap();
					return;
				}
				break;
			case 80:	//��
				if (r + 1 >= 0 && c >= 0 && r + 1 < height && c < width && map[r + 1][c] == 'x') {	//�ϴ� �ⱸ ����
					map[r][c] = '0';
					map[r + 1][c] = '.';
					ReGame(cnt); return;
				}
				else if (r + 1 >= 0 && c >= 0 && r + 1 < height && c < width && map[r + 1][c] == '0')	//�ϴ� ���
				{
					map[r][c] = '0';
					map[r + 1][c] = '.';
					stackMaze.pop();
					stackMaze.push(new Node(r + 1, c));
				}
				else if (r + 1 >= 0 && c >= 0 && r + 1 < height && c < width && map[r + 1][c] == '2')	//�ϴ� �� ��ġ�� ��� ����
				{
					map[r][c] = '0';
					map[r + 1][c] = '2';
					system("cls");
					printf("==== You Lose!! ====\n");
					showMap();
					return;
				}
				break;
			case 75:	//��
				if (r >= 0 && c - 1 >= 0 && r < height && c - 1 < width && map[r][c - 1] == 'x') {	//���� �ⱸ ����
					map[r][c] = '0';
					map[r][c - 1] = '.';
					ReGame(cnt); return;
				}
				else if (r >= 0 && c - 1 >= 0 && r < height && c - 1 < width && map[r][c - 1] == '0')	//���� ���
				{
					map[r][c] = '0';
					map[r][c - 1] = '.';
					stackMaze.pop();
					stackMaze.push(new Node(r, c - 1));
				}
				else if (r >= 0 && c - 1 >= 0 && r < height && c - 1 < width && map[r][c - 1] == '2')	//���� �� ��ġ ����
				{
					map[r][c] = '0';
					map[r][c - 1] = '2';
					system("cls");
					printf("==== You Lose!! ====\n");
					showMap();
					return;
				}
				break;
			case 77:	//��
				if (r >= 0 && c + 1 >= 0 && r < height && c + 1 < width && map[r][c + 1] == 'x') {	//���� �ⱸ ����
					map[r][c] = '0';
					map[r][c + 1] = '.';
					ReGame(cnt); return;
				}
				else if (r >= 0 && c + 1 >= 0 && r < height && c + 1 < width && map[r][c + 1] == '0')	//���� ���
				{
					map[r][c] = '0';
					map[r][c + 1] = '.';
					stackMaze.pop();
					stackMaze.push(new Node(r, c + 1));
				}
				else if (r >= 0 && c + 1 >= 0 && r < height && c + 1 < width && map[r][c + 1] == '2')	//���� �� ��ġ ����
				{
					map[r][c] = '0';
					map[r][c + 1] = '2';
					system("cls");
					printf("==== You Lose!! ====\n");
					showMap();
					return;
				}
				break;
			}
			cnt++;
			system("cls");
			showMap();
		}
	}

	//===========
	//�̷�3

	void ShowGame()
	{
		printf("\n\n  [ Map ]\n\n");
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (j > width / 2 - 2 && j < width / 2 + 1 && i < height - 1 && i>1)	//�̷� ���� ũ�� / 2 - 2 ���� ũ�� �̷� ����ũ��/2 +1 ���� ���� ���, 
				{																		//����ũ�� -1 ���� �۰� ũ�� 1���� Ŭ�� ���, ���� ?�� ǥ�� 
					if (map[i][j] == '0') //��
					{
						std::cout << "? ";
					}
					else if (map[i][j] == '1')	//��
					{
						std::cout << "? ";
					}
					else if (map[i][j] == 'e')	//�Ա�
					{
						std::cout << "o ";
					}
					else if (map[i][j] == 'x')	//�ⱸ
					{
						std::cout << "x ";
					}
					else if (map[i][j] == '.')	//������ ��
					{
						std::cout << "* ";
					}
				}
				else {
					if (map[i][j] == '0') //��
					{
						std::cout << "  ";
					}
					else if (map[i][j] == '1')	//��
					{
						std::cout << "��";
					}
					else if (map[i][j] == 'e')	//�Ա�
					{
						std::cout << "o ";
					}
					else if (map[i][j] == 'x')	//�ⱸ
					{
						std::cout << "x ";
					}
					else if (map[i][j] == '.')	//������ ��
					{
						std::cout << "* ";
					}
				}
			}
			std::cout << std::endl;
		}
	}
	void StackGameTwo()
	{
		printf("���� �ε����� �ʰ� �����̼���(��ȸ 3��)\n");
		ShowGame();
		int count = 0;

		while (stackMaze.isEmpty() == false)
		{
			Node* here = stackMaze.peek();
			int r = here->row;
			int c = here->col;

			//���� �����̱�
			int key;
			key = maze.get_Enterkey();

			if (count < 3) {
				switch (key)
				{
				case 72:	//��
					if (r - 1 >= 0 && c >= 0 && r - 1 < height && c < width && map[r - 1][c] == 'x') {
						map[r][c] = '0';
						map[r - 1][c] = '.';
						stackMaze.pop();
						system("cls");
						printf("\n!Ž�� ����!\n");
						ShowGame();
						return;
					}
					else if (r - 1 >= 0 && c >= 0 && r - 1 < height && c < width && map[r - 1][c] == '0')	//��� �̵� ���� ���
					{
						system("cls");
						map[r][c] = '0';
						map[r - 1][c] = '.';
						stackMaze.pop();
						stackMaze.push(new Node(r - 1, c));
						printf("����: %d�� \n", count);
						ShowGame();
					}
					else {
						printf("Can't Move\n");
						count++;
					}
					break;
				case 80:	//��
					if (r + 1 >= 0 && c >= 0 && r + 1 < height && c < width && map[r + 1][c] == 'x') {
						map[r][c] = '0';
						map[r + 1][c] = '.';
						stackMaze.pop();
						system("cls");
						printf("\n!Ž�� ����!\n");
						ShowGame();
						return;
					}
					else if (r + 1 >=0 && c >= 0 && r + 1 < height && c < width && map[r + 1][c] == '0')	//�ϴ� ���
					{
						system("cls");
						map[r][c] = '0';
						map[r + 1][c] = '.';
						stackMaze.pop();
						stackMaze.push(new Node(r + 1, c));
						printf("����: %d�� \n", count);
						ShowGame();
					}
					else {
						printf("Can't Move\n");
						count++;
					}
					break;
				case 75:	//��
					if (r >= 0 && c - 1 >= 0 && r < height && c - 1 < width && map[r][c - 1] == 'x') {
						map[r][c] = '0';
						map[r][c - 1] = '.';
						stackMaze.pop();
						system("cls");
						printf("\n!Ž�� ����!\n");
						ShowGame();
						return;
					}
					else if (r >= 0 && c - 1 >= 0 && r < height && c - 1 < width && map[r][c - 1] == '0')	//���� ���
					{
						system("cls");
						map[r][c] = '0';
						map[r][c - 1] = '.';
						stackMaze.pop();
						stackMaze.push(new Node(r, c - 1));
						printf("����: %d�� \n", count);
						ShowGame();
					}
					else {
						printf("Can't Move\n");
						count++;
					}
					break;
				case 77:	//��
					if (r >= 0 && c + 1 >= 0 && r < height && c + 1 < width && map[r][c + 1] == 'x') {
						map[r][c] = '0';
						map[r][c + 1] = '.';
						stackMaze.pop();
						system("cls");
						printf("\n!Ž�� ����!\n");
						ShowGame();
						return;
					}
					else if (r >= 0 && c + 1 >= 0 && r < height && c + 1 < width && map[r][c + 1] == '0')	//���� ���
					{
						system("cls");
						map[r][c] = '0';
						map[r][c + 1] = '.';
						stackMaze.pop();
						stackMaze.push(new Node(r, c + 1));
						printf("����: %d�� \n", count);
						ShowGame();
					}
					else {
						printf("Can't Move\n");
						count++;
					}
					break;
				}
			}
			else
			{
				system("cls");
				printf("����!!\n");
				ShowGame();
				return;
			}
		}
		return;
	}
};

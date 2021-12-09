#define _CRT_SECURE_NO_WARNINGS
#include "Link.h"
#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;

class Maze
{
	char** map = NULL;
	int width;
	int height;

	//위치 큐,스택 객체 생성
	LinkedQueue locQueue;
	LinkedStack stack;

public:

	Maze() { init(0, 0); }
	~Maze() { reset(); }

	void init(int w, int h) //map 이차원 배열을 동적으로 할당
	{
		map = new char* [h];
		for (int i = 0; i < h; i++)
			map[i] = new char[w];
	}

	void reset() //미로 맵 maze를 동적으로 해제
	{
		for (int i = 0; i < height; i++)
			delete[]map[i];
		delete[]map;
	}

	bool isValidLoc(int r, int c)
	{
		if (r < 0 || c < 0 || r >= height || c >= width) return false;
		else return map[r][c] == '1' || map[r][c] == '9';
	}

	void roadMap(const char* filename, int num)
	{
		char c;
		ifstream fp(filename);
		if (fp.fail())
			printf("Error: 파일이 존재하지 않습니다.");

		//만약에 미로 크기 지정해주시면.. p.213처럼
		//fp >> width >> height; 

		//미로 크기 계산
		FILE* fd = fopen(filename, "r");
		int word = 0;
		height = 1;
		width = 0;
		while ((c = getc(fd)) != EOF) {
			if (c == '\n') height++;
			if (c == '0' || c == '1' || c == '5' || c == '9')
			{
				word++;
			}
		}
		width = word / height;

		//map 이차원배열 동적으로 할당
		init(width, height);

		//map 이차원배열에 미로 삽입
		for (int i = 0; i < height; i++)
		{
			for (int z = 0; z < width; z++)
			{
				fp >> c;
				map[i][z] = c;

				//큐에 입구 위치 삽입
				if (map[i][z] == '5')
				{
					Location2D entry(i, z);
					if (num == 1)
						stack.push(new Node(i, z)); //스택 입구!
					else if (num == 2)
						locQueue.enqueue(new Node(i, z));
				}
			}
		}
		fp.close();
	}

	//미로 화면에 출력
	void printMap() {
		//printf("전체 미로의 크기 = %d X %d \n", width, height);
		printf("\n\n  [ Map ]\n\n");
		for (int i = 0; i < height; i++)
		{
			for (int z = 0; z < width; z++)
			{
				if (map[i][z] == '1') //길
				{
					cout << "  ";
				}
				else if (map[i][z] == '0') //벽
				{
					cout << "■";
				}
				else if (map[i][z] == '5') //입구
				{
					cout << "o ";
				}
				else if (map[i][z] == '9') //출구
				{
					cout << "x ";
				}
				else if (map[i][z] == '.') //지나온 길
				{
					cout << "* ";
				}

			}
			cout << endl;
		}
		cout << endl;
	}

	int get_Enterkey()
	{
		int key;
		key = _getch();
		if (key == 13)
		{
			return key;
		}
		return 0;
	}

	void queue_SearchExit()
	{
		while (locQueue.isEmpty() == false) //큐가 비어있지 않는 동안
		{
			if (get_Enterkey() == 13)
			{
				system("cls");

				Location2D* here = locQueue.peek(); //큐의 상단 front 객체 복사
				locQueue.dequeue(); //큐 상단 객체 삭제

				int r = here->row;
				int c = here->col;

				if (map[r][c] == '9') { //출구이면 성공
					printf("\n!탐색 성공!\n");
					printf("=====[ Result ]=====\n");
					printMap();

					return;
				}
				else
				{
					map[r][c] = '.';
					if (isValidLoc(r - 1, c)) locQueue.enqueue(new Node(r - 1, c));
					if (isValidLoc(r + 1, c)) locQueue.enqueue(new Node(r + 1, c));
					if (isValidLoc(r, c - 1)) locQueue.enqueue(new Node(r, c - 1));
					if (isValidLoc(r, c + 1)) locQueue.enqueue(new Node(r, c + 1));
					printf("Now Position: (%d,%d) \n", r, c);
					printMap();

				}
			}
		}
		printf("미로 탐색 실패\n");
	}

	void stack_Search()	//스택 부분
	{
		while (stack.isEmpty() == false) {	//스택 비어있지 않을 경우
			printMap();
			if (get_Enterkey() == 13) {
				system("cls");
				Node* here = stack.peek();
				stack.pop();

				int r = here->row;
				int c = here->col;
				printf("Now Position: (%d,%d) ", r, c);

				if (map[r][c] == '9')
				{
					system("cls");
					printf("\n!탐색 성공!\n");
					printf("=====[ Result ]=====\n");
					printMap();
					return;
				}
				else {
					map[r][c] = '.';
					if (isValidLoc(r - 1, c)) stack.push(new Node(r - 1, c));
					if (isValidLoc(r + 1, c)) stack.push(new Node(r + 1, c));
					if (isValidLoc(r, c - 1)) stack.push(new Node(r, c - 1));
					if (isValidLoc(r, c + 1)) stack.push(new Node(r, c + 1));
				}
			}
		}
		printf("미로 탐색 실패\n");
	}
};

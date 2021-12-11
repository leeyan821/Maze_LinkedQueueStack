#include "MazeGame.h"
void main()
{
	system("mode con cols=120 lines=40");
	int num;
	Maze maze;
	MazeGame mazegame;

	while (1) {
		printf("=================================\n");
		printf("1. 연결리스트 스택으로 미로찾기\n");
		printf("2. 연결리스트 큐로 미로찾기\n");
		printf("3. 연결리스트 스택, 큐 미로 경로 결과\n");
		printf("4. 연결리스트 스택, 큐 비교하기\n");
		printf("5. 연결리스트 큐로 미로찾기 게임하기\n");
		printf("6. 연결리스트 스택으로 미로찾기 게임하기1\n");
		printf("7. 연결리스트 스택으로 미로찾기 게임하기2\n");
		printf("=================================\n");
		printf("번호 입력, 번호 외 값 종료 : ");
		scanf("%d", &num);

		if (num == 1)
		{
			maze.roadMap("Maze.txt", num);
			system("cls");
			printf("<Linked Stack Maze> Start!!\n-> Enter and Show Miro Program");
			maze.stack_Search();
		}
		else if (num == 2)
		{
			maze.roadMap("Maze.txt", num);
			system("cls");
			printf("<LinkedQueueMaze> Start!!\n-> Enter and Show Miro Program");
			maze.queue_SearchExit();
		}
		else if (num == 3)
		{
			system("cls");
			maze.roadMap("Maze.txt", 1);
			maze.resultSatckWay();
			maze.roadMap("Maze.txt", 2);
			maze.resultQueueWay();

		}
		else if (num == 4)
		{
			maze.compare_roadMap("Maze.txt");
			system("cls");
			printf("<Compare Stack & Queue> Start!!\n");
			maze.compare();
		}
		else if (num == 5)
		{
			maze.roadMap("Maze.txt", num);
			system("cls");
			printf("<LinkedQueueMazeGame> Start!!\n-> Enter → ← ↑ ↓");
			maze.printMap();
			maze.QueueMazeGame();

		}
		else if (num == 6)
		{
			mazegame.ReadFile("Maze.txt");
			system("cls");
			mazegame.MazeGameStack();
		}
		else if (num == 7)
		{
			system("cls");
			mazegame.ReadFile("Maze.txt");
			mazegame.StackGameTwo();
		}
		else
		{
			printf("프로그램을 종료합니다.\n");
			break;
		}
	}

}
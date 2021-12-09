#include "Maze.h"
void main()
{
	int num;
	Maze maze;

	while (1) {
		printf("=================================\n");
		printf("1. 연결리스트 스택으로 미로찾기\n");
		printf("2. 연결리스트 큐로 미로찾기\n");
		printf("=================================\n");
		printf("번호 입력, 번호 외 값 종료 : ");
		scanf("%d", &num);
		maze.roadMap("Maze.txt", num);
		if (num == 1)
		{
			system("cls");
			printf("<Linked Stack Maze> Start!!\n-> Enter and Show Miro Program");
			maze.stack_Search();
		}
		else if(num==2)
		{
			system("cls");
			printf("<LinkedQueueMaze> Start!!\n-> Enter and Show Miro Program");
			maze.queue_SearchExit();
		}
		else if (num == 3)
		{
			system("cls");
			printf("<LinkedQueueMaze> Start!!\n-> Enter and Show Miro Program");
			maze.printMap();
			maze.QueueMazeGame();
		}
		else
		{
			printf("프로그램을 종료합니다.\n");
			break;
		}
	}
	
}
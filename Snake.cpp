#include<stdio.h>
//ʹ��easyxͼ�ο�
#include<graphics.h>
#include<conio.h>
//���峤����
#define WIN_WIDTH 640
#define WIN_HEIGHT 480
/*���÷���*/
#define MAX_SCORE 100
bool pause=false;
enum DIR {
	UP,
	DOWN,
	LEFT,
	RIGHT
};
struct MyStruct
{
	int num;
	int dir;
	int score;
	int size;
	int speed;
	POINT coor[MAX_SCORE];
} snake;
struct FOOD
{
	int flag;
	POINT fd;
	DWORD color;
} food;

/*��ʼ������*/
void GameInit();
/*���Ƶ�ͼ*/
void GameDraw();
/*ʹ���ƶ�*/
void SnakeMove();
//���̿����ߵ��ƶ�
void KEYBORD_CONTROL()
{
	if (GetAsyncKeyState(VK_UP)&&snake.dir!=DOWN)
	{
		snake.dir = UP;
	}
	if (GetAsyncKeyState(VK_DOWN) && snake.dir != UP)
	{
		snake.dir = DOWN;
	}
	if (GetAsyncKeyState(VK_LEFT) && snake.dir != RIGHT)
	{
		snake.dir = LEFT;
	}
	if (GetAsyncKeyState(VK_RIGHT) && snake.dir != LEFT)
	{
		snake.dir = RIGHT;
	}
	if (GetAsyncKeyState(VK_SPACE))
	{
		!pause;
	}
}
//�Ե�ʳ�ˢ��ʳ�
void EatFood();
//�����Լ�������
void Dead();
//��ͣ��Ϸ
void Pause();
int main()
{
	srand(GetTickCount());
	//��ʼ��ͼ�δ���
	initgraph(WIN_WIDTH,WIN_HEIGHT,SHOWCONSOLE);
	GameInit();
	DWORD t1, t2;
	t1 = t2 = GetTickCount();
	BeginBatchDraw();
	while(1)
	{
		
		
		if (t2 - t1 > 100) {
			SnakeMove();
			t1 = t2;
		}
		t2 = GetTickCount();
		GameDraw();
		EatFood();
		Dead();
		FlushBatchDraw();
		KEYBORD_CONTROL();
		Pause();
	}
	
	printf("Welcome!");
	getchar();
	closegraph();
	return 0;
}
void GameInit() {
	/*��ʼ����*/
	snake.num = 3;
	snake.dir = RIGHT;
	snake.score = 0;
	snake.size = 10;
	snake.coor[2].x = 0;
	snake.coor[2].y = 0;
	snake.coor[1].x = 0 + snake.size;
	snake.coor[1].y = 0;
	snake.coor[0].x = 2 * snake.size;
	snake.coor[0].y = 0;
	/*��ʼ��ʳ��*/
	food.fd.x = (rand() % (WIN_WIDTH/10))*10;
	food.fd.y = (rand() % (WIN_HEIGHT/10))*10;
	food.flag = 1;
	food.color = BROWN;
}
void GameDraw()
{
	//setbkcolor(WHITE);
	setbkcolor(GREEN);
	cleardevice();
	//����
	
	for (int i = 0;i < snake.num;i++)
	{
		setlinecolor(BLACK);
		setfillcolor(BLUE);
		fillrectangle(snake.coor[i].x,snake.coor[i].y , snake.coor[i].x+snake.size, snake.coor[i].y+snake.size);
		//printf("%d",);
	}
	//����ʳ��
	setlinecolor(BLACK);
	setfillcolor(food.color);
	fillrectangle(food.fd.x, food.fd.y, food.fd.x + snake.size, food.fd.y + snake.size);

}
void SnakeMove() {
	
	int i = snake.num-1;
	//������ͷ�ߵ������ڵ㶼�ǵ�����ǰһ�ڽڵ��λ��
	for (i;i > 0;i--)
	{
		snake.coor[i].x = snake.coor[i - 1].x;
		snake.coor[i].y = snake.coor[i - 1].y;
	}
	//��ͷ�������ƶ�
	switch (snake.dir)
	{
	case RIGHT:
		snake.coor[0].x += snake.size;
		if (snake.coor[0].x - snake.size >= WIN_WIDTH)
		{
			snake.coor[0].x = 0;
		}
		break;
	case LEFT:
		snake.coor[0].x -= snake.size;
		if (snake.coor[0].x + snake.size <= 0)
		{
			snake.coor[0].x = WIN_WIDTH;
		}
		break;
	case UP:
		snake.coor[0].y -= snake.size;
		if (snake.coor[0].y + snake.size <= 0)
		{
			snake.coor[0].y = WIN_HEIGHT;
		}
		break;
	case DOWN:
		snake.coor[0].y += snake.size;
		if (snake.coor[0].y - snake.size >= WIN_HEIGHT)
		{
			snake.coor[0].y = 0;
		}
		break;
	default:
		break;
	}	
}
void EatFood()
{
	if (snake.coor[0].x == food.fd.x && snake.coor[0].y == food.fd.y)
	{
		snake.num++;
		snake.score += 10;
		food.flag = 0;
	}
	//ʳ�ﱻ�Բ�����ʳ��
	if (food.flag == 0)
	{
		food.fd.x = (rand() % (WIN_WIDTH / 10)) * 10;
		food.fd.y = (rand() % (WIN_HEIGHT / 10)) * 10;
		food.flag = 1;
		food.color = BROWN;
	}
	//��ʾ����
	TCHAR temp[20];
	_stprintf(temp,_T("����:%d"),snake.score);
	setbkmode(TRANSPARENT);
	outtextxy(20, 20,temp);
}
void Dead(){
	for (int i = 3;i < snake.num;i++)
	{
		if (snake.coor[0].x == snake.coor[i].x && snake.coor[0].y == snake.coor[i].y)
		{
			outtextxy(200, 200,_T("GAME OVER!"));
			getchar();
			exit(66);
		}
	}
}
void Pause()
{
	if (pause)
	{
		system("pause");
		!pause;
	}
}

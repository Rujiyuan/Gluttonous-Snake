#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#define WALL 35//�궨��ǽ�ı߳�����Ϊ������
int SX = WALL / 2, SY = WALL / 2, len = 4, map[WALL * WALL] = { 0 };//����ȫ�ֱ���ͷ�ĺ�������SX��SY���߳�len����ͼ��-2:ǽ��-1:ʳ��;0:�հ�;>0:����
char c = 'd', c1 = 'd', deaw[WALL * WALL * 2 + 1] = { 0 };


//�ж��Ƿ���ԭ�����ͻ����
void judge()
{
	switch (c1) 
	{
	case 'a':case 'A': if (c != 'd') c = 'a'; break;
	case 'd':case 'D': if (c != 'a') c = 'd'; break;
	case 'w':case 'W': if (c != 's') c = 'w'; break;
	case 's':case 'S': if (c != 'w') c = 's'; break;
	case ' ': _getch();  break;//�ո���ͣ
	case 27:exit(0); break;//Esc�˳�
	}
	//return (c);
}


//����ͷ���꺯��
void update_snake()
{
	switch (c)
	{
	case 'a':if (SX > 0) SX -= 1; else SX += WALL-1; break;
	case 'd':if (SX < WALL-1) SX += 1; else SX -= WALL-1; break;
	case 's':if (SY < WALL-1) SY += 1; else SY -= WALL-1; break;
	case 'w':if (SY > 0) SY -= 1; else SY += WALL-1; break;
	}
}


//���Ƶ�ͼ������������
void draw()
{
	int i;//����ѭ������
	if (map[SY * WALL + SX] == -1)//�ж��Ƿ�Ե�ʳ��
	{
		len++;
		do i = rand() % (WALL * WALL);
		while (map[i]);//��֤ʳ������λ��Ϊ�յ�
		map[i] = -1;//�Ե�ʳ������������ʳ��
		sprintf_s(deaw, 32, "title �÷�:%d", len - 4);//�Ʒְ壬�÷����������ȥһ��ʼ���е��ĸ�����
		system(deaw);
	}
	else 
		for (i = 0; i < WALL * WALL; i++)//ȫ������ֵ-1
			if (map[i] > 0)map[i] -= 1;
	map[SY * WALL + SX] = len;//��ͷ��ֵ
	for (i = 0; i < WALL * WALL * 2; i++)//���»��ƻ���
	{
		if (map[i / 2] == 0)deaw[i] = ' ';
		else if (map[i / 2] > 0)deaw[i] = (i % 2) ? ')' : '(';
		else if (map[i / 2] == -2)deaw[i] = (i & 1) ? ']' : '[';//ǽ
		else deaw[i] = '0';
	}
}


//������
int main()
{
	srand((unsigned)malloc(1));//��ʼ����������ӣ�malloc��̬�ֲ������������ַ
	void judge();//�����ж��Ƿ���ԭ�����ͻ����
	void update_snake();//��������ͷ���꺯��
	void draw();//�������Ƶ�ͼ������������
	int rd, j;//���������rd,ѭ������j
	//char c1 = 'd';//�����ʼ����Ϊ������
	for (j = 0; j < WALL; j += 2)//-2:ǽ
		map[j] = map[WALL * WALL - 1 - j] = map[j * WALL] = map[j * WALL + WALL - 1] = -2;//ʹ���ܵ�ǽ����һ��ֲ�
	for (j = 3; j < WALL - 3; j += 2)
		map[4 * WALL - 1 - j] = map[WALL * (WALL - 3) - 1 - j] = map[j * WALL + 3] = map[j * WALL + WALL - 4] = -2;
	sprintf_s(deaw, 32, "mode con: cols=%d lines=%d", WALL * 2, WALL);//�޸Ŀ���̨���ڴ�С
	system(deaw);
	for (int num = 6; num; num--)///���ɶ��ʳ�num�����������ɸı�num����ֵ���ĵ�ͼ�е�ʳ�����
	{
		do rd = rand() % (WALL * WALL);
		while (map[rd] == -2 || map[rd] > 0);
		map[rd] = -1;//���������ʳ��ĵ�ַ��Ϊ-1
	}
	for (system("title �÷�:0"); 1; Sleep(100))//��ʼ���Ʒְ壬����ѭ����Sleep��ʱ
	{
		if (_kbhit() && (c1 = _getch())) //�ж��Ƿ������룬��������ֵ��c1,getch�����Զ���ȡ���µ��ַ������谴�س���
			judge();//���ú������ж��Ƿ���ԭ�����ͻ
		update_snake();//���ø���ͷ���꺯��
		if (map[SY * WALL + SX] > 1 || map[SY * WALL + SX] == -2)
			exit(!_getch());//�ж��Ƿ�Ե��Լ�����ײǽ
		draw();//���û��Ƶ�ͼ������������
		//system("cls");//����
		printf(deaw);//��ӡ
	}
}
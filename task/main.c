#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include "node.h"
double testnum[5][3] = { {24,10,20 },{24,20,10 },{20,10,24 },{50,10,20 },{24,15,20 } };//repeat���ܲ���
struct List list;
FILE* Answers;
FILE* Exercises;
FILE* Grade;
int QuesNum = 0;//��Ŀ��
int QuesN = 0;//���
int feature=0;//�ж��Ƿ��������
char sign[4] = { '+','-','*','/' };
double max;
double min;
typedef struct Repeat
{
	NODE Rp[50];
	int n[50];
	int Index;
}REPEAT;
void InputDate()
{
	printf("\n������������Ŀ����������������");
	scanf("%d", &QuesNum);
	while (QuesNum <= 0)
	{
		printf("\n������������Ŀ����������������");
		scanf("%d", &QuesNum);
	}
	printf("\n���������ɷ�Χ ��Сֵ�����ڵ������������");
	scanf("%lf", &min);
	printf("\n���������ɷ�Χ ���ֵ(����ֵС�ڵ���СֵʱĬ����Сֵ��50)��");
	scanf("%lf", &max);
	printf("\n�������Ƿ�������� 0������ 1������");
	scanf("%d", &feature);
	if (min < 0)
		min = 0;
	if (max <= min)
	{
		max = min + 50;
	}
	printf("��Ŀ����\t����\t���ֵ\t��Сֵ\n");
	printf("\t%d\t%d\t%.2lf\t%.2lf\n", QuesNum, feature, max, min);
}
double randNum()
{
	double x = 0;
	int y = rand() % 10;
	x =1.0* y/10;
	x =( x* max)+ min;
	if (x > 1)
	{
		int y = x;
		x = y;
	}
	else
	{
		x = x * 100;
		int y = x;
		x = 1.0*y / 100;
	}
	return x;
}
double Value(double a, double b, char op)
{
	double value = 0.0;
	switch (op)
	{
	case '+':
		value = a + b;
		break;
	case '-':
		value = a - b;
		break;
	case '*':
		value = a * b;
		break;
	case '/':
		value = a / b;
		break;
	}
	return value;
}
char* ToLine(double x)
{
	char *ch=(char*)malloc(100);
	memset(ch, 0,100);
	if (x < 1)
	{
		int n = x * 100;
		int n_1 = 2;
		int temp_1 = x * 100;
		int temp_2 = 100;
		while (n_1 <= temp_1&& n_1 <= temp_2)
		{
			if (temp_1%n_1 == 0 && temp_2%n_1 == 0)
			{
				temp_1 = temp_1 / n_1;
				temp_2 = temp_2 / n_1;
				n_1 = 2;
				continue;
			}
			n_1++;
		}
		sprintf(ch, "(%d/%d)", temp_1, temp_2);
	}
	else
	{
		sprintf(ch, "%.0lf", x);
	}
	return ch;
}
double myceil(double x)
{
	if (x < 0)
	{
		x = -x;
		x *= 100;
		int n = x;
		if ((x - n)*10 > 5)
		{
			n--;
		}
		else
		{
			n++;
		}
		x = -1.0*n / 100;
	}
	else
	{
		x *= 100;
		int n = x;
		if ((x - n) * 10 >= 5)
		{
			n++;
		}
		x = 1.0*n / 100;
	}
	return x;
}
void rubric()
{
	NODE temp;
	QuesN++;
	InitDate(&temp);
	char *ch=(char*)malloc(1024);
	char *num[4] = { NULL};
	memset(ch,0,1024);
	int n = 3;
	int tempnum = rand() % 5;

	while (!(n > 1 && n < 5))
	{
		n = rand() % 5;
	}
	for (int i = 0; i < n; i++)
	{
		temp.number[i] =randNum();
	}
	for (int i = 0; i < n - 1; i++)
	{
		temp.sign[i] = sign[rand()%4];
	}
	temp.size = n;
	//����repeat����
	//for (int i = 0; i < n; i++)
	//{
	//	temp.number[i] = testnum[tempnum][i]/*randNum()*/;
	//}
	//for (int i = 0; i < n - 1; i++)
	//{
	//	temp.sign[i] ='+';
	//}
	int left_insignia = 0;
	//�������ţ����ݲ������������жϣ�����������������������ŵ�λ��ֻ�е�һ������ǰ�棬���������壬��˲������������3���ſɲ��룬
	//����������ĿΪ��ʱ����Ŀ�ɲ���λ��Ϊ��һ���͵ڶ�����ǰ��
	//����������ĿΪ��ʱ����Ŀ�ɲ���λ��Ϊ��һ�����ڶ������͵�������ǰ��
	if (n== 4)
	{
		while (!left_insignia)
		{
			left_insignia = rand() % 4;
		}
	}
	else if (n == 3)
	{
		while (!left_insignia)
		{
			left_insignia = rand() %3;
		}
	}
	if (feature&&left_insignia)
	{
		switch (left_insignia)
		{
		case 1:
			if (n > 3)
			{
				int right_insignia = 0;
				while (!right_insignia)
				{
					right_insignia = rand()% 3;
				}
				if (right_insignia == 2)
				{

					if (temp.sign[1] == '/' || temp.sign[1] == '*')
					{
						temp.result = Value(temp.number[1], temp.number[2], temp.sign[1]);
						temp.result = Value(temp.number[0], temp.result,temp.sign[0]);
						temp.result = Value(temp.result, temp.number[3], temp.sign[2]);
					}
					else
					{
						temp.result = Value(temp.number[0], temp.number[1], temp.sign[0]);
						temp.result = Value(temp.result, temp.number[2], temp.sign[1]);
						temp.result = Value(temp.result, temp.number[3], temp.sign[2]);
					}
					for (int i = 0; i < 4; i++)
					{
						num[i] = ToLine(temp.number[i]);
					}
					temp.result = myceil(temp.result);
					sprintf(ch,"(%s %c %s %c %s) %c %s", num[0], temp.sign[0], num[1], temp.sign[1], num[2], temp.sign[2], num[3]);
				}
				else
				{
					temp.result = Value(temp.number[0], temp.number[1], temp.sign[0]);
					if (temp.sign[2] == '/' || temp.sign[2] == '*')
					{
						temp.result = Value(temp.result, Value(temp.number[2], temp.number[3], temp.sign[2]), temp.sign[1]);
					}
					else
					{
						temp.result = Value(temp.result, temp.number[2], temp.sign[1]);
						temp.result = Value(temp.result, temp.number[3], temp.sign[2]);
					}
					for (int i = 0; i < 4; i++)
					{
						num[i] = ToLine(temp.number[i]);
					}
					temp.result = myceil(temp.result);
					sprintf(ch, "(%s %c %s) %c %s %c %s", num[0], temp.sign[0], num[1], temp.sign[1], num[2], temp.sign[2], num[3]);
				}
			}
			else
			{
				temp.result = Value(temp.number[0], temp.number[1], temp.sign[0]);
				temp.result = Value(temp.result, temp.number[2], temp.sign[1]);
				temp.result = ceil(temp.result);
				for (int i = 0; i < 3; i++)
				{
					num[i] = ToLine(temp.number[i]);
				}
				sprintf(ch,"(%s %c %s) %c %s",num[0], temp.sign[0], num[1], temp.sign[1], num[2]);
			}
			break;
		case 2://1+/2+3/
			if (n > 3)
			{
				int right_insignia = 0;
				while (!right_insignia)
				{
					right_insignia = rand() % 3;
				}
				if (right_insignia == 2)
				{

					if (temp.sign[2] == '/' || temp.sign[2] == '*')
					{
						temp.result = Value(temp.number[2],temp.number[3], temp.sign[2]);
						temp.result = Value(temp.number[1],temp.result, temp.sign[1]);
						temp.result = Value(temp.number[0],temp.result, temp.sign[0]);

					}
					else
					{
						temp.result = Value(temp.number[1], temp.number[2], temp.sign[1]);
						temp.result = Value(temp.result, temp.number[3], temp.sign[2]);
						temp.result = Value(temp.number[0], temp.result, temp.sign[0]);
					}
					for (int i = 0; i < 4; i++)
					{
						num[i] = ToLine(temp.number[i]);
					}
					temp.result = myceil(temp.result);
					sprintf(ch, "%s %c (%s %c %s %c %s)", num[0], temp.sign[0], num[1], temp.sign[1], num[2], temp.sign[2], num[3]);
				}
				else
				{
					temp.result = Value(temp.number[1],temp.number[2], temp.sign[1]);
					if (temp.sign[2] == '/' || temp.sign[2] == '*')
					{
						temp.result= Value(temp.result, temp.number[3], temp.sign[2]);
						temp.result = Value(temp.number[0],temp.result, temp.sign[0]);
					}
					else
					{
						temp.result = Value(temp.number[0],temp.result, temp.sign[0]);
						temp.result = Value(temp.result, temp.number[3], temp.sign[2]);
					}
					for (int i = 0; i < 4; i++)
					{
						num[i] = ToLine(temp.number[i]);
					}
					temp.result = myceil(temp.result);
					sprintf(ch, "%s %c (%s %c %s) %c %s", num[0], temp.sign[0], num[1], temp.sign[1], num[2], temp.sign[2], num[3]);
				}
			}
			else
			{//1+2+3
				temp.result = Value(temp.number[1], temp.number[2], temp.sign[1]);
				temp.result = Value(temp.number[0], temp.result, temp.sign[0]);
				for (int i = 0; i < 3; i++)
				{
					num[i] = ToLine(temp.number[i]);
				}
				temp.result = myceil(temp.result);
				sprintf(ch, "%s %c (%s %c %s)", num[0], temp.sign[0], num[1], temp.sign[1],num[2]);
			}
			break;
		case 3://1+2+/3+4/
				temp.result = Value(temp.number[2], temp.number[3], temp.sign[2]);
				if (temp.sign[1] == '/' || temp.sign[1] == '*')
				{
					temp.result = Value(temp.number[1], temp.result, temp.sign[1]);
					temp.result = Value(temp.number[0], temp.result, temp.sign[0]);
				}
				else
				{
					temp.result = (Value(temp.number[0], temp.number[1], temp.sign[0]), temp.result, temp.sign[1]);
				}
				for (int i = 0; i < 4; i++)
				{
					num[i] = ToLine(temp.number[i]);
				}
				temp.result = myceil(temp.result);
				sprintf(ch, "%s %c %s %c (%s %c %s)", num[0], temp.sign[0], num[1], temp.sign[1], num[2], temp.sign[2], num[3]);
		break;
		}
	}
	else
	{
		if (n > 3)
		{
			if ((temp.sign[1] == '/' || temp.sign[1] == '*') && (temp.sign[2] == '/' || temp.sign[2] == '*'))
			{
				temp.result = Value(temp.number[1],temp.number[2],temp.sign[1]);
				temp.result = Value(temp.result, temp.number[3], temp.sign[2]);
				temp.result = Value(temp.number[0], temp.result, temp.sign[0]);
				for (int i = 0; i < 4; i++)
				{
					num[i] = ToLine(temp.number[i]);
				}
				temp.result = myceil(temp.result);
				sprintf(ch, "%s %c %s %c %s %c %s", num[0], temp.sign[0], num[1], temp.sign[1], num[2], temp.sign[2], num[3]);
			}
			else if ((temp.sign[1] == '/' || temp.sign[1] == '*') || (temp.sign[2] == '/' || temp.sign[2] == '*'))
			{
				if (temp.sign[2] == '/' || temp.sign[2] == '*')
				{
					temp.result = Value(temp.number[2], temp.number[3], temp.sign[2]);
					temp.result = Value(temp.number[0], temp.result,  temp.sign[0]);
					temp.result = Value( temp.number[1], temp.result, temp.sign[1]);
					for (int i = 0; i < 4; i++)
					{
						num[i] = ToLine(temp.number[i]);
					}
					temp.result = ceil(temp.result);
					sprintf(ch, "%s %c %s %c %s %c %s", num[0], temp.sign[0], num[1], temp.sign[1], num[2], temp.sign[2], num[3]);
				}
				else
				{
					temp.result = Value(temp.number[1], temp.number[2], temp.sign[1]);
					temp.result = Value(temp.number[0], temp.result, temp.sign[0]);
					temp.result = Value(temp.result, temp.number[3], temp.sign[2]);
					for (int i = 0; i < 4; i++)
					{
						num[i] = ToLine(temp.number[i]);
					}
					temp.result = myceil(temp.result);
					sprintf(ch, "%s %c %s %c %s %c %s", num[0], temp.sign[0], num[1], temp.sign[1], num[2], temp.sign[2], num[3]);
				}
			}
			else
			{
				temp.result = Value(temp.number[0], temp.number[1], temp.sign[0]);
				temp.result = Value(temp.result, temp.number[2], temp.sign[1]);
				temp.result = Value(temp.result, temp.number[3], temp.sign[2]);
				temp.result = myceil(temp.result);
				for (int i = 0; i < 4; i++)
				{
					num[i] = ToLine(temp.number[i]);
				}
				sprintf(ch, "%s %c %s %c %s %c %s", num[0], temp.sign[0], num[1], temp.sign[1], num[2], temp.sign[2], num[3]);
			}
		}
		else if (n == 3)
		{
			if (temp.sign[1] == '/' || temp.sign[1] == '*')
			{
				temp.result = Value(temp.number[1], temp.number[2], temp.sign[1]);
			temp.result = Value(temp.number[0], temp.result, temp.sign[0]);
			for (int i = 0; i < 3; i++)
			{
				num[i] = ToLine(temp.number[i]);
			}
			temp.result = myceil(temp.result);
			sprintf(ch, "%s %c %s %c %s", num[0], temp.sign[0], num[1], temp.sign[1], num[2]);
			}
			else
			{
				temp.result = Value(temp.number[0], temp.number[1], temp.sign[0]);
				temp.result = Value(temp.result, temp.number[2], temp.sign[1]);
				for (int i = 0; i < 3; i++)
				{
					num[i] = ToLine(temp.number[i]);
				}
				temp.result = myceil(temp.result);
				sprintf(ch, "%s %c %s %c %s", num[0], temp.sign[0], num[1], temp.sign[1], num[2]);
			}
		}
		else
		{
			temp.result = Value(temp.number[0], temp.number[1], temp.sign[0]);
			temp.result = myceil(temp.result);
			for (int i = 0; i < 2; i++)
			{
				num[i] = ToLine(temp.number[i]);
			}
			sprintf(ch, "%s %c %s", num[0], temp.sign[0], num[1]);
		}
	}
	double answer = 0.0;
	printf("%s =",ch);
	scanf("%lf", &answer);
	if (answer == temp.result)
	{
		printf("\n�ش���ȷ!");
		temp.state = 1;
	}
	else
	{
		printf("\n�ش����!");
		temp.state = 0;
	}
	temp.QuesNum = QuesN;
	temp.Que =ch;
	InsertDate(temp);
	printf("\n");
}
void Save()
{
	Answers = fopen("Answers.txt", "w+");
	Exercises=fopen("Exercises.txt", "w+");
	Grade=fopen("Grade.txt", "w+");
	for (int i = 0; i < list.Size; i++)
	{
		fprintf(Exercises, "%d. %s\n",i+1, list.Ques[i].Que);
	}
	fclose(Exercises);
	for (int i = 0; i < list.Size; i++)
	{
		fprintf(Answers, "%d. %0.2lf\n", i+1, list.Ques[i].result);
	}
	fclose(Answers);
	int Correct[100]={0};
	int C=0;
	int Wrong[100]={0};
	int W=0;
	for(int i = 0; i < list.Size; i++)
	{
		if(list.Ques[i].state)
		{
			Correct[i]=list.Ques[i].QuesNum;
			C++;
		}
		else
		{
			Wrong[i]=list.Ques[i].QuesNum;
			W++;
		}
	}
	for(int i = 0; i < C; i++)
	{
		if(!i)
		{
			fprintf(Grade, "Correct:%d(",C);
		}
		if(i==C-1)
		{
				fprintf(Grade, "%d)\n",Correct[i]);
		}
		else
		fprintf(Grade, "%d,",Correct[i]);
	}
	for(int i = 0; i < W; i++)
		{
			if(!i)
			{
				fprintf(Grade, "Wrong:%d(",W);
			}
			if(i==W-1)
			{
					fprintf(Grade, "%d)\n",Wrong[i]);
			}
			else
			fprintf(Grade, "%d,",Wrong[i]);
		}
	NODE temp;
	NODE tempN[100];
	int N=0;
	REPEAT *Rp=(REPEAT *)malloc(list.Size*sizeof(REPEAT));
	for(int i=0;i<list.Size;i++)
	{
		Rp[i].Index = 0;
		memset(Rp[i].Rp, 0, sizeof(Rp[i].Rp));
		memset(Rp[i].n, 0, sizeof(Rp[i].n));
	}
    for(int i=0;i< list.Size;i++)
    {
    	temp=list.Ques[i];
    	
    	for(int k=0;k<temp.size-1;k++)
    	{
			if(temp.sign[k]==temp.sign[0]&&(temp.sign[0]=='*'||temp.sign[0]=='+'))
			{
				if(k==temp.size-2)
				{
					
					tempN[N++]=temp;
				}
			}
			else
			{
				break;
			}
		}
	}
	int tempR=0;
    int tempRt=0; 
	for(int i=0;i<N;i++)
	{
		int flag = 0;
	    for(int k=0;k< tempRt;k++)
		{
			for (int j = 0; j < Rp[k].Index; j++)
			{
				if (i == Rp[k].n[j])
				{
					flag = 1;
					break;
				}
			}
			if (flag)
			{
				break;
			}
		}
		if (flag)
		{
			continue;
		}
		temp=tempN[i];
		Rp[tempR].Rp[Rp[tempR].Index++] = temp;
		for(int j=i+1;j<N;j++)
		{
			int tempj=0;
			if(temp.sign[0]==tempN[j].sign[0]&&temp.size==tempN[j].size)
			{
				for(int k=0;k<temp.size;k++)
				{
					int n=0;
					for(int x=0;x<temp.size;x++)
					{
							if(temp.number[k]!=tempN[j].number[x])
							{
								n++;
							}
					}
					if(n>=temp.size)
					{
						break;
					}
					else if(n<temp.size&&k==temp.size-1)
					{
						Rp[tempR].n[Rp[tempR].Index-1] = j;
						Rp[tempR].Rp[Rp[tempR].Index++]=tempN[j];
						tempRt++;
						
					}
				}
			}
		}
		tempR++;
	}
	int rpn=1;
	fprintf(Grade, "Repeat:%d\n",tempRt);
	if(tempRt!=0)
	{
		fprintf(Grade, "RepeatDetail:\n");
			for(int i=0;i<tempR;i++)
			{
				if(Rp[i].Index>=2)
				{
					for(int j=0;j<Rp[i].Index;j++)
					{
						if(j==0)
						{
							fprintf(Grade, "(%d) %d,%s Repeat",rpn++,Rp[i].Rp[j].QuesNum,Rp[i].Rp[j].Que);
						}
						else
						{
							fprintf(Grade, " %d,%s",Rp[i].Rp[j].QuesNum,Rp[i].Rp[j].Que);
						}
						if(i==Rp[i].Index-1)
						{
							fprintf(Grade, "\n");
						}
					}
					
				}
			}
	}
	fclose(Grade);
}
int main()
{
	srand((unsigned)time(NULL));
	InputDate();
	CreateList();
	printf("����������Ľ����������λС����\n");
	for (int i = 0; i < QuesNum; i++)
	{
		rubric();
	}
	Save();
	return 0;
}

#pragma once
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <stdio.h>
typedef struct Node
{
	double number[4];	//������
	char sign[3];	//�����
	int size;       //�������ĸ���
	int QuesNum;	//��Ŀ��
	char *Que;      //��Ŀ
	double result;	//�����
	int state;		//�����Ƿ���ȷ 0������1��ȷ
}NODE,*LPNODE;
struct List
{
	LPNODE Ques;
	int curentIndex;
	int Size;
};
extern struct List list;
void InitDate(LPNODE date);

void CreateList();

void AddSize(int newsize);

void InsertDate(NODE node);

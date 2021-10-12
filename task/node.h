#pragma once
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <stdio.h>
typedef struct Node
{
	double number[4];	//操作数
	char sign[3];	//运算符
	int size;       //操作数的个数
	int QuesNum;	//题目号
	char *Que;      //题目
	double result;	//本题答案
	int state;		//本题是否正确 0，错误，1正确
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

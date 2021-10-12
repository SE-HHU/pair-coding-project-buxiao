include"node.h"
void InitDate(LPNODE date)
{
	for (int i = 0; i < 4; i++)
	{
		date->number[i] = 0.0;
	}
	memset(date->sign,0, 3);
	date->Que = NULL;
	date->QuesNum = 0;
	date->result = 0;
	date->state = 0;
	date->size = 0;
}
void CreateList()
{
	list.Ques = (LPNODE)malloc(sizeof(NODE));
	list.curentIndex = 0;
	list.Size = 1;
	InitDate(&list.Ques[list.Size - 1]);
}
void AddSize(int newsize)
{
	list.Ques = (LPNODE)realloc(list.Ques, sizeof(NODE));
	InitDate(&list.Ques[newsize - 1]);
}
void InsertDate(NODE node)
{
	if (list.curentIndex>=list.Size)
	{
		AddSize(++list.Size);
	}
	list.Ques[list.curentIndex++] = node;
}

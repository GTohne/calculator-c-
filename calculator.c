#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define  end '\n'	
///////////////////////////////////////////////////////////开始定义数栈，包括了函数声明
typedef double ElemType;
typedef struct node
{
	ElemType data;
	struct node*next;
}*linkStack, stackNode;

//链栈初始化
linkStack create()
{
	linkStack top = (linkStack)malloc(sizeof(stackNode));
	if (!top)
	{
		printf("动态内存分配失败!\n");
		exit(0);
	}
	else
	{
		top->next = NULL;
		printf("数栈初始化成功!\n");
		return top;
	}
}

//入栈
int push(linkStack top, ElemType e)
{
	if (top)
	{
		linkStack p = (linkStack)malloc(sizeof(stackNode));
		p->data = e;
		p->next = top->next;
		top->next = p;
		return 1;
	}
	return 0;

}
//出栈
ElemType pop(linkStack st)			//返回pop的元素值
{
	ElemType x;
	linkStack p;
	p = st;
	x = st->next->data;
	st->next = st->next->next;

	return x;

}
//判断栈空
int isEmpty(linkStack top)
{
	if (top->next == NULL)
		return 1;
	return 0;

}
//获取栈顶元素
double getTop(linkStack top)
{
	if (top->next)
	{
		return top->next->data;

	}
	return -1;
}






///////////////////////////////////////////////////////////结束定义数栈，以及函数声明

///////////////////////////////////////////////////////////开始运算符栈的定义，以及其函数的声明

typedef char ElemType2;
typedef struct node2
{
	ElemType2 data;
	struct node2*next;
}*linkStack2, stackNode2;

//链栈初始化
linkStack2 create2()
{
	linkStack2 top = (linkStack2)malloc(sizeof(stackNode2));
	if (!top)
	{
		printf("动态内存分配失败!\n");
		exit(0);
	}
	else
	{
		top->next = NULL;
		printf("运算符栈初始化成功!\n");
		return top;
	}
}

//入栈
int push2(linkStack2 top, ElemType2 e)
{
	if (top)
	{
		linkStack2 p = (linkStack2)malloc(sizeof(stackNode2));
		p->data = e;
		p->next = top->next;
		top->next = p;
		return 1;
	}
	return 0;

}
//出栈
ElemType2 pop2(linkStack2 st)			//返回pop的元素值
{
	ElemType2 x;
	linkStack2 p;
	p = st;
	x = st->next->data;
	st->next = st->next->next;

	return x;

}
//判断栈空
int isEmpty2(linkStack2 top)
{
	if (top->next == NULL)
		return 1;
	return 0;

}
//获取栈顶元素
int getTop2(linkStack2 top)
{
	if (top->next)
	{
		return top->next->data;

	}
	return -1;
}

//////////////////////////////////////////////////////////////声明全局栈
linkStack num;
linkStack2 optr;
char a[100][100];



///////////////////////////////////////////////////////////结束运算符栈的定义，以及其函数的声明


//////////////////////////////////////////////////////////其他函数的声明
double operate(double a, char t, double b);
int judge(char a);
double read(char *p);
char precede(char t1, char t2);
void fun(char*p1, char*p2);
//////////////////////////////////////////////////////////其他函数的声明结束


int main()
{
	char c[100];
	char *p1, *p2;
	num = create();
	optr = create2();
	double result;
	for (int i = 0, j = 0; i <= 99;)
	{
		if (j == 100)
		{
			i++;
			j = 0;
		}
		else
		{
			a[i][j] = '\0';
			j++;
		}
	}
	printf("请输入表达式并且以#结尾，例如12.2+6/(9-3)+3#\n");
	scanf("%s", c);
	strcat(c, "\n ");
	p1 = a; p2 = c;
	fun(p1, p2);
	push2(optr, '#');/////在运算符栈中压＃
	result = read(p1);
	printf("%lf", result);
	return 0;
}
/////////////////////////////////////////////////////////////////////////表达式存值函数
void fun(char*p1, char*p2)
{
	int i = 0;
	while (*p2 != end)
	{

		if (*p2 >= '0'&&*p2 <= '9')
		{
			p1 = a + i;
			for (int j = 0; (*p2 >= '0'&&*p2 <= '9') || (*p2 == '.'); j++, p2++)
			{
				*(p1 + j) = *p2;
			}
			i++;

		}
		else if (*p2 == '#')
		{
			p1 = a + i;
			*p1 = *p2;
			p2++;
		}

		else
		{
			p1 = a + i;
			*p1 = *p2;
			i++;
			p2++;
		}
	}
}


/////////////////////////////////////////////////////////////////////////读取函数
double read(char *p)
{
	int i = 0;
	double c, b;
	char t;
	while ((*p != '#') || (optr->next->data != '#'))
	{
		if (judge(*p))
		{
			switch (precede(optr->next->data, *p))
			{
			case'<':
			{
					   push2(optr, *p);
					   i++;
					   break;
			}
			case'=':
			{
					   pop2(optr);
					   i++;
					   break;
			}
			case'>':
			{
					   t = pop2(optr);
					   b = pop(num);
					   c = pop(num);
					   push(num, operate(c, t, b));
			}
			}
		}
		else
		{
			push(num, atof(p));
			i++;
		}
		if (*p != '#')
		{
			p = a + i;
		}
	}
	return getTop(num);
}
int judge(char a)
{
	switch (a)
	{
	case'+':return 1;
	case'-':return 1;
	case'*':return 1;
	case'/':return 1;
	case'(':return 1;
	case')':return 1;
	case'#':return 1;
	default:return 0;
	}

}
double operate(double a, char t, double b)
{
	double d;
	switch (t)
	{

	case'+':
	{
			   d = a + b;
			   break;
	}
	case'-':
	{
			   d = a - b;
			   break;
	}
	case'/':
	{
			   d = a / b;
			   break;
	}
	case'*':
	{
			   d = a*b;
			   break;
	}
	}
	return d;
}

char precede(char a, char b)
{
	int i, j;
	char pre[7][7] =                        //定义运算符之间的优先级
	{
		{ '>', '>', '<', '<', '<', '>', '>' },
		{ '>', '>', '<', '<', '<', '>', '>' },
		{ '>', '>', '>', '>', '<', '>', '>' },
		{ '>', '>', '>', '>', '<', '>', '>' },
		{ '<', '<', '<', '<', '<', '=', '0' },
		{ '>', '>', '>', '>', '0', '>', '>' },
		{ '<', '<', '<', '<', '<', '0', '=' },
	};
	switch (a)
	{
	case '+':
		i = 0;
		break;
	case '-':
		i = 1;
		break;
	case '*':
		i = 2;
		break;
	case '/':
		i = 3;
		break;
	case '(':
		i = 4;
		break;
	case ')':
		i = 5;
		break;
	case '#':
		i = 6;
		break;
	}
	switch (b)
	{
	case '+':
		j = 0;
		break;
	case '-':
		j = 1;
		break;
	case '*':
		j = 2;
		break;
	case '/':
		j = 3;
		break;
	case '(':
		j = 4;
		break;
	case ')':
		j = 5;
		break;
	case '#':
		j = 6;
		break;
	default:
		printf("表达式要以#结尾！！！\n");
		exit(1);
	}
	return pre[i][j];
}

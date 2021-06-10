#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>


#define MULTIPLIER 10
#define MAXSIZE 60

int MAXDEPTH = 3;

struct expre_stack
{
	char* data;
	int top;
};

struct  expression
{
	int val;
	int depth;
	char optor;
	struct expre_stack* expre;

	struct expression* father;
	struct expression* left;
	struct expression* right;
};

struct loca_stack
{
	int* data;
	int top;
};

void print(struct expre_stack* expre)
{
	int i = 0;
	while (i <= expre->top)
	{
		printf("%c", *(expre->data + i));
		i = i + 1;
	}
}

struct expression* ealloc(void) {
	return (struct expression*) malloc(sizeof(struct expression));
}

void stack_push(struct loca_stack* stack, int i)
{
	//printf("asdf\n");
	stack->top = stack->top + 1;
	//printf("%d\n", stack->top);
	*(stack->data + stack->top) = i;
}

int stack_pop(struct loca_stack* stack)
{
	int b;
	b = *(stack->data + stack->top);
	stack->top = stack->top - 1;

	return b;

}

int re_optor(struct expre_stack* expre)
{
	//printf("已进入re_optor\n");
	//printf("\n成功传递参数\n");
	int j = 0;
	int k = (-1);
	int temp = 0;
	int val = 0;
	int count = 0;

	struct loca_stack* stack;
	stack = (struct loca_stack*) malloc(sizeof(struct loca_stack));

	if (stack != NULL)
	{
		stack->data = (int*)malloc(MAXSIZE * sizeof(int));
	}
	else
	{
		assert(0);
	}

	stack->top = (-1);

	struct loca_stack* leftstack;
	struct loca_stack* rightstack;
	leftstack = (struct loca_stack*) malloc(sizeof(struct loca_stack));
	rightstack = (struct loca_stack*) malloc(sizeof(struct loca_stack));
	if ((leftstack != NULL) && (rightstack != NULL))
	{
		leftstack->data = (int*)malloc(MAXSIZE * sizeof(int));
		rightstack->data = (int*)malloc(MAXSIZE * sizeof(int));
	}
	else
	{
		assert(0);
	}
	leftstack->top = (-1);
	rightstack->top = (-1);

	int op[MAXSIZE] = {};

	//printf("re_optor成功初始化\n");

	while (j <= (expre->top))
	{
		//printf("成功进入re_optro   while, j = %d, expre->top = %d \n",j, expre->top);
		if (*(expre->data + j) == '(') {
			stack_push(stack, j);
			//printf("1\n");
		}
		else if (*(expre->data + j) == ')') {
			stack_push(leftstack, stack_pop(stack));
			stack_push(rightstack, j);
			//printf("2\n");
		}
		else if ((*(expre->data + j) == 'A') || (*(expre->data + j) == 'E') || (*(expre->data + j) == 'L') || (*(expre->data + j) == 'O'))
		{
			k = k + 1;
			op[k] = j;

			//printf("3\n");
		}

		j = j + 1;
	}

	int aa = 0;

	//while (aa <= k)
	//{
		//printf("op[%d] = %d\t k = %d \n",aa, op[aa], aa);
		//aa = aa + 1;
	//}

	if ((leftstack->top >= 0) && (rightstack->top >= 0) && (leftstack->top == rightstack->top))
	{
		leftstack->top = leftstack->top - 1;
		rightstack->top = rightstack->top - 1;
		if ((leftstack->top == (-1)) && (k == 0))
		{
			val = op[k];
		}
		//去掉最外层括号

		temp = rightstack->top;
		//printf("temp = %d\n", temp);
		while (k >= 0)
		{
			//printf(" k = %d \n", k);
			while (leftstack->top >= 0)
			{
				//printf("left = %d\t right = %d \n", *(leftstack->data + leftstack->top), *(rightstack->data + rightstack->top));
				if ((*(leftstack->data + leftstack->top) < op[k]) && (op[k] < *(rightstack->data + rightstack->top)))
					//printf("成功进入if\n")
					;
				else
				{
					//printf("成功进入else\n");
					count = count + 1;
				}

				if (count == (temp + 1))
					val = op[k];
				//printf("k = %d\n", k);
				leftstack->top = leftstack->top - 1;
				rightstack->top = rightstack->top - 1;
			}
			count = 0;
			k = k - 1;

			leftstack->top = temp;
			rightstack->top = temp;
		}

		leftstack->top = temp;
		rightstack->top = temp;
	}

	free(stack->data);
	free(stack);
	free(leftstack->data);
	free(leftstack);
	free(rightstack->data);
	free(rightstack);
	return val;

}

void expre_push(struct expre_stack* expre, char a)
{

	expre->top = expre->top + 1;
	*(expre->data + expre->top) = a;
}

struct expre_stack* re_left(struct expre_stack* expre, int mid)
{
	int j = 0;
	struct expre_stack* a;
	a = (struct expre_stack*)malloc(sizeof(struct expre_stack));
	if (a != NULL)
	{
		a->data = (char*)malloc(MAXSIZE * sizeof(char));
	}
	else
	{
		assert(0);
	}
	a->top = (-1);

	while (j < mid - 1)
	{
		a->top = a->top + 1;
		if (a->data + j != NULL)
		{
			*(a->data + j) = *(expre->data + j + 1);
		}
		else
		{
			assert(0);
		}

		j = j + 1;
	}
	return a;
}

struct expre_stack* re_right(struct expre_stack* expre, int mid)
{
	struct expre_stack* a;
	a = (struct expre_stack*)malloc(sizeof(struct expre_stack));
	if (a != NULL)
	{
		a->data = (char*)malloc(MAXSIZE * sizeof(char));
	}
	else
	{
		assert(0);
	}
	a->top = (-1);

	mid = mid + 1;
	while (mid < expre->top)
	{
		a->top = a->top + 1;
		if ((a->data + a->top) != NULL)
		{
			*(a->data + a->top) = *(expre->data + mid);
		}
		else
		{
			assert(0);
		}
		mid = mid + 1;
	}
	return a;
}

int expre_tree(struct expression* input)  //初始化需要给深度赋值为1；表达式赋值为输入；
{
	int mid = 0;

	if (*(input->expre->data) == '(')
	{

		mid = re_optor(input->expre);

		input->optor = *(input->expre->data + mid);

		input->left = ealloc();
		input->right = ealloc();


		input->left->expre = (struct expre_stack*) malloc(sizeof(struct expre_stack));

		if (input->left->expre != NULL)
		{
			input->left->expre->data = (char*)malloc(MAXSIZE * sizeof(char));
		}
		else
		{
			assert(0);
		}

		input->right->expre = (struct expre_stack*) malloc(sizeof(struct expre_stack));

		if (input->right->expre != NULL)
		{
			input->right->expre->data = (char*)malloc(MAXSIZE * sizeof(char));
		}
		else
		{
			assert(0);
		}

		input->left->expre = re_left(input->expre, mid);
		input->right->expre = re_right(input->expre, mid);

		input->left->depth = input->depth + 1;
		input->right->depth = input->depth + 1;

		input->left->father = input;
		input->right->father = input;

		expre_tree(input->left);
		expre_tree(input->right);

	}

	else
	{
		input->left = NULL;
		input->right = NULL;
	}

	return 0;
}

int Not(int a)
{
	a = !a;
	return a;
}

int Equal(int a, int b) {
	int e;
	e = (a == b);
	return e;
}

int And(int a, int b) {
	int c;
	c = (a && b);
	return c;
}

int Or(int a, int b) {
	int c;
	c = (a || b);
	return c;
}

int Entail(int a, int b) {
	int c;
	c = ((!a)||b);
	return c;
}

struct Node {
	int val;
	int depth;
	struct Node *left;
	struct Node *right;
	struct Node *father;
};

struct Node* balloc(void) {
	return (struct Node* ) malloc(sizeof(struct  Node));
}

void createtree(struct Node* p)
{
	if (p->father == NULL)  //for init
	{
		p->depth = 0;
		p->val = 0;

		p->left = balloc();
		p->right = balloc();

		p->left->father = p;
		p->right->father = p;

		createtree(p->left);
		createtree(p->right);
	}
	else
	{
		if ((p->father->depth + 1) <= MAXDEPTH)
		{
			p->depth = p->father->depth + 1;

			if (p->father->left == p)
			{
				p->val = MULTIPLIER * (p->father->val) + 2;
			}
			else
			{
				p->val = MULTIPLIER * (p->father->val) + 1;
			}

			p->left = balloc();
			p->right = balloc();

			p->left->father = p;
			p->right->father = p;

			createtree(p->left);
			createtree(p->right);

		}
	}
};
//建立二叉树

int i = 0;

void getlevelvalue(struct Node* p, int* value) {
	if (p->depth == MAXDEPTH) {
		*(value + i) = p->val;
		//printf("i = %d \n", i);
		//printf("value = %d \n", *(value + i));
		i = i + 1;
	}
	else
	{
		getlevelvalue(p->left, value);
		getlevelvalue(p->right, value);
	}
}
//获取固定深度的值

void unpack(int* value,int* unpackd) { 
	int a = 1;
	int b = 0;
	int c = 0;

	while (b <= (pow(2,MAXDEPTH)) - 1) {

		while (a <= MAXDEPTH) {

			*(unpackd + c) = ( ( (int) (*( value + b ) / pow(10,((double)a - 1))) % 10 ) - 1);
			//printf("unpackd %d = %d \n", c, *(unpackd + c));
			a = a + 1;
			c = c + 1;
		}
		a = 1;
		b = b + 1;
	}
}
//将值解包到unpackd中

int _max(int a, int b)
{
	if (a >= b) return a;
	else return b;
}

int expre_tree_depth(struct expression* input)
{
	int a;
	if (input == NULL) return 0;

	a = (1 + _max(expre_tree_depth(input->left), expre_tree_depth(input->right)));

	return a;
}

void expre_tree_level_cal(struct expression* input, int level, int val_combi[])
{
	int sub = 0;

	if(input != NULL)
	{ 
		if (input->depth == level)
		{
			if (*(input->expre->data) == '(')
			{
				if (input->optor == 'A')
				{
					input->val = And(input->left->val, input->right->val);
				}
				else if (input->optor == 'L')
				{
					input->val = Entail(input->left->val, input->right->val);
				}
				else if (input->optor == 'E')
				{
					input->val = Equal(input->left->val, input->right->val);
				}
				else if (input->optor == 'O')
				{
					input->val = Or(input->left->val, input->right->val);
				}
				else
				{
					assert(0);
				}

			}
			else if (*(input->expre->data) == 'N')
			{
				sub = ((int)(*(input->expre->data) - 'a'));
				input->val = Not(val_combi[sub]);
			}
			else if (*(input->expre->data) >= 'a')
			{
				sub = ((int)(*(input->expre->data) - 'a'));
				input->val = val_combi[sub];
			}
			else
			{
				assert(0);
			}
		}
		else
		{
			expre_tree_level_cal(input->left, level, val_combi);
			expre_tree_level_cal(input->right, level, val_combi);
		}
	}
	
}

int expre_tree_cal(struct expression* input, int val_combi[])
{
	int level = 0;
	int re = 0;

	level = expre_tree_depth(input);

	while (level >= 1)
	{
		expre_tree_level_cal(input, level, val_combi);
		level = level - 1;
	}

	re = input->val;

	return re;
}


int main() {

	printf("表达式书写规则：\n \n");
	printf("不要使用任何空格 \n \n");
	printf("N = 非； E = 等价；A = 合取；O (字母) = 析取；L = 蕴涵 \n \n");
	printf("命题变项请依次使用小写的a, b, c ....指代\n \n");
	printf("所有的二元运算符使用后都要在式子外加上英文括号 \n \n");
	printf("例如：((aL(bOc))A(NcEc))\n \n");
	printf("请输入命题变项的个数并回车：(1-6)\n \n");
	//声明格式+输入关键参数（命题变项的个数）和需要计算的表达式

	scanf_s("%d",& MAXDEPTH);
	assert(MAXDEPTH >= 1);
	assert(MAXDEPTH <= 6);
	fflush(stdin);
	//获取命题变项的个数

	struct Node* root;
	root = balloc();
	root->father = NULL;
	createtree(root);

	int *value = NULL;
	value = (int*) malloc(100*sizeof(int)); 
	getlevelvalue(root, value);
	int* unpackd = NULL;
	unpackd = (int*)malloc(300 * sizeof(int));

	unpack(value, unpackd);

	char aa[MAXSIZE] = {};
	printf("请输入表达式并回车：\n \n");

	scanf_s("%s", aa, MAXSIZE);


	//表达式获取、生成环节
	struct expression* input;
	int j = 0;

	input = ealloc();
	input->father = NULL;

	input->expre = (struct expre_stack*) malloc(sizeof(struct expre_stack));

	if (input->expre != NULL)
	{
		input->expre->data = (char*)malloc(MAXSIZE * sizeof(char));
	}
	else
	{
		assert(0);
	}

	input->expre->top = (-1);
	input->depth = 1;

	while (j <= (strlen(aa) - 1))
	{
		expre_push(input->expre, aa[j]);
		j = j + 1;
	}


	expre_tree(input);

	//输出环节: 

	char proposition = 'a';
	int n = 0;		//生成0，1组合用的
	int nfenge = 0; //分割线用的
	int nnn = 0;	//生成0，1组合用的
	int npro = 0;   //命题生成用的

	while (npro <= (MAXDEPTH -1)) {
		printf("%c\t", proposition);
		npro = npro + 1;
		proposition = proposition + 1;
	}
	//输出命题


	printf("%s \n", &aa); //用scanf直接获得expression

	while (nfenge <= MAXDEPTH)
	{
		printf("----------");
		nfenge = nfenge + 1;
	} 
	printf("\n");
	//输出分割线

	int val_combi[MAXSIZE] = {};

	assert(input != NULL);
	
	while (n <= (MAXDEPTH * pow(2, MAXDEPTH) - MAXDEPTH)) {
		if ((unpackd + n) == NULL) {
			free(unpackd + n);
		}//糊弄糊弄编译器，免得警告,实际上只检查三分之一的unpackd
		else
		{
			while ( nnn <= MAXDEPTH -1)
			{
				val_combi[nnn] = *(unpackd + n + (MAXDEPTH - nnn - 1));
				printf("%d\t", *(unpackd + n + (MAXDEPTH - nnn - 1)));
				nnn = nnn + 1;
			}
			printf("%d", expre_tree_cal(input,val_combi));  //在此处输出outcome
			nnn = 0;
			n = n + MAXDEPTH;
			printf("\n");
		}
	}

	free(input->expre);
	free(input);

	printf("\n\n按Ctrl + Z 然后回车退出\n");
	while (getchar() != EOF) {

	}
}

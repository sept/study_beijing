#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	char item;
	int counter;
	struct node *l;
	struct node *r;
}* link;

link make_node(char c)
{
	link p = malloc(sizeof(struct node));
	if(p == NULL)
	{
		perror("malloc failed");
		exit(-1);
	}
	p->item = c;
	p->counter = 0;
	p->l = NULL;
	p->r = NULL;

	return p;
}
/*使用递归顺序打印 链表 （先打印再入栈）*/
/*如果使用递归倒叙打印 则利用栈 先入栈再打印*/
/*二叉树 打印 一般使用中序*/
void travel(link p)
{
	if(!p)
		return;

	travel(p->l);
	printf("the letter %c : %d\n", p->item, p->counter);
	travel(p->r);
}
/*使用递归 统计结点个数*/
int count_tree(link p)
{
	if(p == NULL)
		return 0;

	return 1 + count_tree(p->l) + count_tree(p->r);
}
/*使用递归 统计二叉树的深度*/
int depth_tree(link p)
{
	if(p == NULL)
		return 0;

	int dl = depth_tree(p->l);
	int dr = depth_tree(p->r);
	return 1 + (dl > dr ? dl : dr);
}
/*使用递归 查找判断二叉树中的某一结点是否存在*/
link search(link p, char key)
{
	if(!p)                     /*递归先左边查找完之后 的返回条件*/
		return NULL;

	if(p->item == key)         /*函数的终止条件*/
		return p;

	link sl = search(p->l, key); /*查找二叉树的左边*/
	if(sl != NULL)
		return sl;

	link sr = search(p->r, key);
	if(sr != NULL)
		return sr;

	return NULL;
}
void sum_key(link root, char key)
{
	link node = search(root, key);
	if(node != NULL)
	{
		node->counter++;
//		printf("found node %c : %d\n", node->item, node->counter);
	}
	else
		printf("not found %c\n", key);

}
/*根据前序和中序 建立二叉树*/
link init_tree(char *VLR, char *LVR, int n)
{
	int k;
	link p;

	if(n <= 0)
		return NULL;

	for(k = 0; VLR[0] != LVR[k]; k++);
	p = make_node(VLR[0]);
	p->l = init_tree(VLR+1, LVR, k);
	p->r = init_tree(VLR+1+k, LVR+1+k, n-k-1);

	return p;
}
int main(void)
{
	link root;
//	char *buf = "4854863116";
	printf("hello, link & tree\n");
#if 0
	root = make_node('a');
	root->l = make_node('b');
	root->r = make_node('c');

	root = make_node('4');
	root->l = make_node('2');
	root->r = make_node('5');
	root->l->l = make_node('1');
	root->l->r = make_node('3');
	root->r->r = make_node('6');

	printf("all node is    %d\n", count_tree(root));
	printf("tree's depth is %d\n", depth_tree(root));

	printf("the buf is %s\n", buf);

	while(*buf != '\0')
	{
		sum_key(root, *buf);
		buf++;
	}
#endif
	char VLR[7] = "dbacfeg";
	char LVR[7] = "abcdefg";

	root = init_tree(VLR, LVR, 7);

	travel(root);



	return 0;
}

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef struct node *link;

struct node {
	char item[32];
	int counter;
	link l, r;
};

char buf[1024] =
{
	"This is a book.\n"
	"That is a bag.\n"
	"This is a pencil.\n"
	"This is a ship.\n"
};

link make_node(char * key)
{
	link p = malloc(sizeof(struct node));
	if(p == NULL)
	{
		perror("malloc");
		exit(-1);
	}
	strcpy(p->item, key);
	p->counter = 1;
	p->l = NULL;
	p->r = NULL;

	return p;
}

void travel(link p, int depth)
{
	if (!p)
		return;

	travel(p->l, depth+1);
	printf("node [dep = %d] %d : <%s> \n", depth, p->counter, p->item);
	travel(p->r, depth+1);
}

link insert_node(link p, char *key)
{
	if (!p)
		return make_node(key);

	if ((strcmp(p->item, key)) > 0)
		p->l = insert_node(p->l, key);
	else if ((strcmp(p->item, key) < 0))
		p->r = insert_node(p->r, key);
	else
		p->counter++;

	return p;
}

link search(link p, char *key)
{
	if (!p)
		return NULL;

	if (strcmp(p->item, key) == 0)
		return p;
	if (strcmp(p->item, key) > 0)
		search(p->r, key);
	if (strcmp(p->item, key) < 0)
		search(p->l, key);

	return NULL;
}

int main(void)
{
	printf("hello, my word\n");
	printf("%s", buf);

	int i = 0;
	int state = 0;
	char word[32];
	char c;
	int j = 0;
	link root = NULL;

#if 0
	while ((c = buf[i++]) != '\0') {
		if (isalpha(c)) {
			state = 1;
			word[j++] = c;
			continue;
		}

		if (isalpha(c) && state == 1) { 无论state是0还是1操作都一样，合并
			word[j++] = c;
			continue;
		}

		if ((c == ' ' || c == '\n') && state == 1) {
			word[j] = '\0';
			j = 0;
			printf("find a word: <%s>\n", word);
		}
	}
#endif

	//合并后用下方法也可以
	while ((c = buf[i++]) != '\0') {
		if (isalpha(c)) {
			state = 1;
			word[j++] = c;
		} else if ((c == ' ' || c == '\n') && state == 1) {
			word[j] = '\0';
			j = 0;
			root = insert_node(root, word);
//			printf("find a word: <%s>\n", word);
			state = 0;
		}
	}

	travel(root, 1);

	return 0;
}

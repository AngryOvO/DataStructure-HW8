/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* �ʿ��� ������� �߰� */

typedef struct Node { // ����ü ����
	int key; 
	struct Node* llink;
	struct Node* rlink;
} listNode;
// ����Ʈ�� ù ��° ��带 ����Ű�� ��������͸� ���� ����ü�� ���� �������� ����


/* �Լ� ����Ʈ */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL; // ����带 ���� ���� �� NULL �ʱ�ȭ

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("--------------[201803805]------[���Ͽ�]-------------------------\n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* �޸� ���� */
int freeList(listNode* h){
	
	listNode* n = h; // ����Ʈ�� Ž���� ������ ����
	listNode* p = h; // n�� ���� ��带 ����ų ������ ����

	if(h->rlink == h) // ����� �� ���� ����Ʈ�� �����ϴ� ���
	{
		free(h); // ����� �Ҵ� ����
		return 1;
	}
	
	while(n->rlink != h) //n�� ���� ��尡 ������� �� ���� �ݺ�
	{
		p = n; // p�� n�� ��ġ��
		n = n->rlink; //n�� ��������
		free(p); //p ����
	}
	free(h); // ������ ������ ����带 ������ ��� ��尡 �����ǹǷ� ����� ����

	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(listNode* h, int key) {
	
	listNode* node = (listNode*)malloc(sizeof(listNode));
	// �� ��� ���� �� �ʱ�ȭ
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;
	
	listNode* n = h->llink; // ����Ʈ�� ������ ��带 ����Ű�� ������ ����
	// ������� ���� ��尡 ������ ���
	h->llink = node; // ����� ���� ��尡 �� ���
	n->rlink = node; // n�� ���� ��尡 �� ���
	node->llink = n; //����� ���� ��尡 n
	node->rlink = h; //����� ���� ��尡 ��� ���

	return 1;
}


/**
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h) {
	
	if(h->rlink == h)
	{
		printf("noting to delete in list !!\n");
		return 0;
	}
	
	listNode* n = h->llink; // ������ n�� ����Ʈ�� ������ ����
	
	n->llink->rlink = h; //n�� ��������� ������尡 �����
	h->llink = n->llink; //������� �������� n�� �������
	free(n); //n ����
	
	return 1;
}


/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(listNode* h, int key) {
	// �� ��� ���� �� �ʱ�ȭ
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = NULL;
	node->rlink = NULL;
	
	h->rlink->llink = node; //����� ��������� ������尡 �� ���
	node->llink = h; // �� ����� ���� ��尡 �����
	node->rlink = h->rlink; // �� ����� ���� ��尡 ����� �������
	h->rlink = node; // ����� ���� ��尡 �� ���
	
	return 1;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(listNode* h) {
	
	if(h->rlink == h) // ������� ������尡 �ڱ� �ڽ��ΰ�� : ����Ʈ�� ��尡 �������
	{
		printf("noting to delete in list!!\n");
		return 0;
	}
	
	listNode* n = h->rlink; // ������ n�� ����� ��������
	
	h->rlink = n->rlink; // ����� �������� n�� �������
	n->rlink->llink = h; // n�� ��������� �������� �����
	free(n); // n ����

	return 1;

}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h) {
	
	if(h->rlink == h) // ����Ʈ�� ����常 �����ϴ°��
	{
		printf("no list to invert!\n\n"); //�������� ��� �� ����
		return 0;
	}
	// ���� ��ġ�� ������ ���� �غ� first = middle�� �������, middle�� ����Ʈ ����ȭ, last�� ����Ʈ �̵�
	listNode* first = h; //first�� middle�� last�� �ڿ� �־�� �ϹǷ� h���� ����
	listNode* middle = h;
	listNode* last = h->rlink; //last�� h�� ���� ��忡������ ����

	h->llink = h->rlink; //h�� �������� h�� �������
	
	while(last != h) // last�� h�� ���� ������ �ݺ�
	{
		first = middle; //�� ������ ��ġ �̵�
		middle = last;
		last = last->rlink;
		
		middle->rlink = first; //middle�����͸� ���� ����Ʈ ����ȭ
		middle->llink = last;
	}
	
	h->rlink = middle; //����� �������� middle

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(listNode* h, int key) {
	//�� ��� ���� �� �ʱ�ȭ
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = NULL;
	node->rlink = NULL;
	
	listNode* n = h->rlink; //����Ʈ�� Ž���� ������ ����
	
	while(n != h) //n�� h�� �ٸ��� �ݺ�
	{
		if(n->key >= key) //�Է¹��� key������ ū ��尡 �������
		{
			node->rlink = n; //�� ����� ���� ��尡 n
			node->llink = n->llink; //�� ����� ���� ��尡 n�� �������
			n->llink->rlink = node; //n�� ��������� ������尡 �� ���
			n->llink = node; //n�� ������尡 �� ���
			return 0;
		}
		n = n->rlink; //n�� ��������
	}
	insertLast(h,key); //�Է¹��� key���� ���� ū��� insertLast ����
	
	
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {
	
	if(h->rlink == h) // ����Ʈ�� ����常 �����ϴ� ���
	{
		printf("not exist node in list!!\n\n");
		return 0;
	}
	
	listNode* n = h->rlink; // n�� ������� ��������
	
	while(n != h) //n�� h�� �ٸ��� �ݺ�
	{
		if(n->key == key) // �Է¹��� key���̶� ���� ���� ���� ��尡 �ִ°��
		{
			n->llink->rlink = n->rlink; //n�� ��������� ���� ��尡 n�� �������
			n->rlink->llink = n->llink; //n�� ��������� ������尡 n�� �������
			free(n); //n ����
			return 0;
				
		}
		n = n->rlink; //n�� ��������
	}
	
	printf("not exist key node in list!!\n\n");
	return 0;
}
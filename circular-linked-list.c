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
/* 필요한 헤더파일 추가 */

typedef struct Node { // 구조체 선언
	int key; 
	struct Node* llink;
	struct Node* rlink;
} listNode;
// 리스트의 첫 번째 노드를 가리키는 헤드포인터를 담은 구조체를 따로 선언하지 않음


/* 함수 리스트 */
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
	listNode* headnode=NULL; // 헤드노드를 새로 선언 후 NULL 초기화

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("--------------[201803805]------[정하용]-------------------------\n");
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

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){
	
	listNode* n = h; // 리스트를 탐색할 포인터 생성
	listNode* p = h; // n의 이전 노드를 가리킬 포인터 생성

	if(h->rlink == h) // 헤드노드 한 개만 리스트에 존재하는 경우
	{
		free(h); // 헤드노드 할당 해제
		return 1;
	}
	
	while(n->rlink != h) //n의 다음 노드가 헤드노드일 때 까지 반복
	{
		p = n; // p를 n의 위치로
		n = n->rlink; //n을 다음노드로
		free(p); //p 해제
	}
	free(h); // 루프를 끝나면 헤드노드를 제외한 모든 노드가 해제되므로 헤드노드 해제

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
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
	
	listNode* node = (listNode*)malloc(sizeof(listNode));
	// 새 노드 생성 및 초기화
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;
	
	listNode* n = h->llink; // 리스트의 마지막 노드를 가리키는 포인터 생성
	// 헤드노드의 이전 노드가 마지막 노드
	h->llink = node; // 헤드의 이전 노드가 새 노드
	n->rlink = node; // n의 다음 노드가 새 노드
	node->llink = n; //노드의 이전 노드가 n
	node->rlink = h; //노드의 다음 노드가 헤드 노드

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
	
	if(h->rlink == h)
	{
		printf("noting to delete in list !!\n");
		return 0;
	}
	
	listNode* n = h->llink; // 포인터 n을 리스트의 마지막 노드로
	
	n->llink->rlink = h; //n의 이전노드의 다음노드가 헤드노드
	h->llink = n->llink; //헤드노드의 이전노드는 n의 이전노드
	free(n); //n 삭제
	
	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
	// 새 노드 생성 및 초기화
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = NULL;
	node->rlink = NULL;
	
	h->rlink->llink = node; //헤드의 다음노드의 이전노드가 새 노드
	node->llink = h; // 새 노드의 이전 노드가 헤드노드
	node->rlink = h->rlink; // 새 노드의 다음 노드가 헤드의 다음노드
	h->rlink = node; // 헤드의 다음 노드가 새 노드
	
	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
	
	if(h->rlink == h) // 헤드노드의 다음노드가 자기 자신인경우 : 리스트에 노드가 없을경우
	{
		printf("noting to delete in list!!\n");
		return 0;
	}
	
	listNode* n = h->rlink; // 포인터 n을 헤드의 다음노드로
	
	h->rlink = n->rlink; // 헤드의 다음노드는 n의 다음노드
	n->rlink->llink = h; // n의 다음노드의 이전노드는 헤드노드
	free(n); // n 삭제

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
	
	if(h->rlink == h) // 리스트에 헤드노드만 존재하는경우
	{
		printf("no list to invert!\n\n"); //오류문자 출력 및 종료
		return 0;
	}
	// 역순 배치용 포인터 세개 준비 first = middle의 이전노드, middle은 리스트 역순화, last는 리스트 이동
	listNode* first = h; //first와 middle은 last의 뒤에 있어야 하므로 h에서 시작
	listNode* middle = h;
	listNode* last = h->rlink; //last는 h의 다음 노드에서부터 시작

	h->llink = h->rlink; //h의 이전노드는 h의 다음노드
	
	while(last != h) // last가 h와 같지 않을때 반복
	{
		first = middle; //각 포인터 위치 이동
		middle = last;
		last = last->rlink;
		
		middle->rlink = first; //middle포인터를 통해 리스트 역순화
		middle->llink = last;
	}
	
	h->rlink = middle; //헤드의 다음노드는 middle

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {
	//새 노드 생성 및 초기화
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = NULL;
	node->rlink = NULL;
	
	listNode* n = h->rlink; //리스트를 탐색할 포인터 생성
	
	while(n != h) //n이 h와 다를때 반복
	{
		if(n->key >= key) //입력받은 key값보다 큰 노드가 있을경우
		{
			node->rlink = n; //새 노드의 다음 노드가 n
			node->llink = n->llink; //새 노드의 이전 노드가 n의 이전노드
			n->llink->rlink = node; //n의 이전노드의 다음노드가 새 노드
			n->llink = node; //n의 이전노드가 새 노드
			return 0;
		}
		n = n->rlink; //n을 다음노드로
	}
	insertLast(h,key); //입력받은 key값이 가장 큰경우 insertLast 실행
	
	
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
	
	if(h->rlink == h) // 리스트에 헤드노드만 존재하는 경우
	{
		printf("not exist node in list!!\n\n");
		return 0;
	}
	
	listNode* n = h->rlink; // n을 헤드노드의 다음노드로
	
	while(n != h) //n이 h와 다를때 반복
	{
		if(n->key == key) // 입력받은 key값이랑 같은 값을 가진 노드가 있는경우
		{
			n->llink->rlink = n->rlink; //n의 이전노드의 다음 노드가 n의 다음노드
			n->rlink->llink = n->llink; //n의 다음노드의 이전노드가 n의 다음노드
			free(n); //n 삭제
			return 0;
				
		}
		n = n->rlink; //n을 다음노드로
	}
	
	printf("not exist key node in list!!\n\n");
	return 0;
}
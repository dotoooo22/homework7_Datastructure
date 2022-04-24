#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;

int initialize(headNode** h);

int freeList(headNode* h);

int insertNode(headNode* h, int key);	//key삽입
int insertLast(headNode* h, int key);	//라스트에삽입
int insertFirst(headNode* h, int key);	//첫번째삽입
int deleteNode(headNode* h, int key);	//키삭제
int deleteLast(headNode* h);			//마지막삭제
int deleteFirst(headNode* h);			//첫번째삭제
int invertList(headNode* h);			//리스트거꾸로

void printList(headNode* h);			//프린트


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	printf("[----- [곽민정] [2021041021] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
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
		case 'z': case 'Z':		//z: 초기화
			initialize(&headnode);
			break;
		case 'p': case 'P':		//p: 리스트 출력
			printList(headnode);
			break;
		case 'i': case 'I':		//i: 키 삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':		//d: 키 삭제
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':		//n: 마지막에 키 삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':		//e: 마지막거 삭제
			deleteLast(headnode);
			break;
		case 'f': case 'F':		//f: 첫번째에 키 삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':		//t: 첫번째거삭제
			deleteFirst(headnode);
			break;
		case 'r': case 'R':		//r: 거꾸로
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


int initialize(headNode** h) {

	if(*h != NULL)		//헤드가 널이아니고 뭐가있으면 메모리해제
		freeList(*h);

	*h = (headNode*)malloc(sizeof(headNode));		//헤드메모리할당
	(*h)->first = NULL;
	return 1;
}

int freeList(headNode* h){
	
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {		//p가 비어있을때까지
		prev = p;		//prev에 p넣고
		p = p->rlink;	//p는 p오른쪽링크
		free(prev);		//메모리해제
	}
	free(h);	//헤드메모리해제
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {		//널이면 비어있따고함
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);		//몇갠지도 출력
}


int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));		//노드하나 메모리 할당받기
	node->key = key;		//노드에 키값을 넣기
	node->rlink = NULL;
	node->llink = NULL;

	if (h->first == NULL)		//처음꺼비어있으면 넣고리턴
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;		//n이 처음거
	while(n->rlink != NULL) {		//오른쪽 널일때까지 이동
		n = n->rlink;
	}
	n->rlink = node;	//새노드추가
	node->llink = n;	//왼쪽에 앞거연결
	return 0;
}

int deleteLast(headNode* h) {

	if (h->first == NULL)	//비어있으면 없다고
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	if(n->rlink == NULL) {	//첫번째가 마지막이면(노드하나임) 
		h->first = NULL;	//first가 널넣고
		free(n);			//메모리해제
		return 0;
	}

	while(n->rlink != NULL) {	//노드끝까지이동
		trail = n;
		n = n->rlink;
	}

	trail->rlink = NULL;	//마지막거랑 연결된거(이전오른쪽링크) 연결끊고
	free(n);				//메모리해제

	return 0;
}

int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));	//노드하나메모리할당받음
	node->key = key;	//키값저장해주고
	node->rlink = node->llink = NULL;

	if(h->first == NULL)		//처음거비어있으면 걍 처음에 삽입하고 리턴
	{
		h->first = node;
		return 1;
	}

	node->rlink = h->first;		//원래첫번째걸 생성한노드 다음으로
	node->llink = NULL;			//왼쪽은 없고

	listNode *p = h->first;		//포인터p에 원래첫번째인걸넣고
	p->llink = node;			//왼쪽에 새로들어온걸연결
	h->first = node;			//헤드는 새로들어온거가리키도록하기

	return 0;
}

int deleteFirst(headNode* h) {

	if (h->first == NULL)		//암것도없으면 삭제할거없음
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;		//n에 지금 첫번째노드넣어두고
	h->first = n->rlink;		//처음은 그다음걸 가리키게하고

	free(n);		//첫번째넣어둔거 삭제

	return 0;
}

int invertList(headNode* h) {


	if(h->first == NULL) {		//아무것도없음
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){		//n이 널을 가리킬때까지 (n은 계속 다음으로이동함)
		trail = middle;		//트레일에 미들을넣고
		middle = n;			//미들에 n을넣고
		n = n->rlink;		//n에 그다음거를넣음
		middle->rlink = trail;	//미들다음거에 트레일(트레일은전에꺼니까오른쪽왼쪽을바꾼거)
		middle->llink = n;		//미들왼족에 n(n은n오른쪽거있으니 오른쪽걸왼쪽에넣은거)
	}

	h->first = middle;		//처음엔 미들넣기

	return 0;
}

int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));		//노드하나할당
	node->key = key;	//키넣고
	node->llink = node->rlink = NULL;

	if (h->first == NULL)		//아무것도없으면 그냥 처음에 삽입
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;

	while(n != NULL) {//n을리스트오른쪽끝까지이동시키면서
		if(n->key >= key) {			//입력받은키가 지금위치의 키보다 작으면
			if(n == h->first) {		//n이 첫번째면 처음에 삽입
				insertFirst(h, key);
			} else { //첫번째아니면
				node->rlink = n;		//n을 새노드다음거에연결
				node->llink = n->llink;		//새노드왼쪽에는 n왼쪽거
				
				n->llink->rlink = node;		//n전거의 오른쪽을 새노드
				n->llink=node;				//n의 왼쪽(이전)것도 새노드를 가리키게
			}
			return 0;
		}

		n = n->rlink;
	}

	insertLast(h, key);		//마지막노드까지갔는데 입력된키값이 제일크면 마지막에 삽입
	return 0;
}


int deleteNode(headNode* h, int key) {

	if (h->first == NULL)		//리스트비어잇으면삭제할거없음
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first;

	while(n != NULL) {
		if(n->key == key) {
			if(n == h->first) { //첫번째노드면첫번째노드삭제
				deleteFirst(h);
			} else if (n->rlink == NULL){ //마지막노드면마지막거삭제
				deleteLast(h);
			} else { //중간에있으면
				n->llink->rlink = n->rlink;		//n이랑 연결을 빼고 다음거랑 다연결시키기
				n->rlink->llink = n->llink;
				free(n);		//n메모리해제
			}
			return 1;	//리턴
		}

		n = n->rlink;	
	}

	//키값이없음
	printf("cannot find the node for key = %d\n", key);
	return 1;
}



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

int insertNode(headNode* h, int key);	//key����
int insertLast(headNode* h, int key);	//��Ʈ������
int insertFirst(headNode* h, int key);	//ù��°����
int deleteNode(headNode* h, int key);	//Ű����
int deleteLast(headNode* h);			//����������
int deleteFirst(headNode* h);			//ù��°����
int invertList(headNode* h);			//����Ʈ�Ųٷ�

void printList(headNode* h);			//����Ʈ


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	printf("[----- [������] [2021041021] -----]\n");

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
		case 'z': case 'Z':		//z: �ʱ�ȭ
			initialize(&headnode);
			break;
		case 'p': case 'P':		//p: ����Ʈ ���
			printList(headnode);
			break;
		case 'i': case 'I':		//i: Ű ����
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':		//d: Ű ����
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':		//n: �������� Ű ����
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':		//e: �������� ����
			deleteLast(headnode);
			break;
		case 'f': case 'F':		//f: ù��°�� Ű ����
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':		//t: ù��°�Ż���
			deleteFirst(headnode);
			break;
		case 'r': case 'R':		//r: �Ųٷ�
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

	if(*h != NULL)		//��尡 ���̾ƴϰ� ���������� �޸�����
		freeList(*h);

	*h = (headNode*)malloc(sizeof(headNode));		//���޸��Ҵ�
	(*h)->first = NULL;
	return 1;
}

int freeList(headNode* h){
	
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {		//p�� �������������
		prev = p;		//prev�� p�ְ�
		p = p->rlink;	//p�� p�����ʸ�ũ
		free(prev);		//�޸�����
	}
	free(h);	//���޸�����
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {		//���̸� ����ֵ�����
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);		//����� ���
}


int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));		//����ϳ� �޸� �Ҵ�ޱ�
	node->key = key;		//��忡 Ű���� �ֱ�
	node->rlink = NULL;
	node->llink = NULL;

	if (h->first == NULL)		//ó������������� �ְ���
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;		//n�� ó����
	while(n->rlink != NULL) {		//������ ���϶����� �̵�
		n = n->rlink;
	}
	n->rlink = node;	//������߰�
	node->llink = n;	//���ʿ� �հſ���
	return 0;
}

int deleteLast(headNode* h) {

	if (h->first == NULL)	//��������� ���ٰ�
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	if(n->rlink == NULL) {	//ù��°�� �������̸�(����ϳ���) 
		h->first = NULL;	//first�� �γְ�
		free(n);			//�޸�����
		return 0;
	}

	while(n->rlink != NULL) {	//��峡�����̵�
		trail = n;
		n = n->rlink;
	}

	trail->rlink = NULL;	//�������Ŷ� ����Ȱ�(���������ʸ�ũ) �������
	free(n);				//�޸�����

	return 0;
}

int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));	//����ϳ��޸��Ҵ����
	node->key = key;	//Ű���������ְ�
	node->rlink = node->llink = NULL;

	if(h->first == NULL)		//ó���ź�������� �� ó���� �����ϰ� ����
	{
		h->first = node;
		return 1;
	}

	node->rlink = h->first;		//����ù��°�� �����ѳ�� ��������
	node->llink = NULL;			//������ ����

	listNode *p = h->first;		//������p�� ����ù��°�ΰɳְ�
	p->llink = node;			//���ʿ� ���ε��°ɿ���
	h->first = node;			//���� ���ε��°Ű���Ű�����ϱ�

	return 0;
}

int deleteFirst(headNode* h) {

	if (h->first == NULL)		//�ϰ͵������� �����Ұž���
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;		//n�� ���� ù��°���־�ΰ�
	h->first = n->rlink;		//ó���� �״����� ����Ű���ϰ�

	free(n);		//ù��°�־�а� ����

	return 0;
}

int invertList(headNode* h) {


	if(h->first == NULL) {		//�ƹ��͵�����
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){		//n�� ���� ����ų������ (n�� ��� ���������̵���)
		trail = middle;		//Ʈ���Ͽ� �̵����ְ�
		middle = n;			//�̵鿡 n���ְ�
		n = n->rlink;		//n�� �״����Ÿ�����
		middle->rlink = trail;	//�̵�����ſ� Ʈ����(Ʈ�������������ϱ�����ʿ������ٲ۰�)
		middle->llink = n;		//�̵������ n(n��n�����ʰ������� �����ʰɿ��ʿ�������)
	}

	h->first = middle;		//ó���� �̵�ֱ�

	return 0;
}

int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));		//����ϳ��Ҵ�
	node->key = key;	//Ű�ְ�
	node->llink = node->rlink = NULL;

	if (h->first == NULL)		//�ƹ��͵������� �׳� ó���� ����
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;

	while(n != NULL) {//n������Ʈ�����ʳ������̵���Ű�鼭
		if(n->key >= key) {			//�Է¹���Ű�� ������ġ�� Ű���� ������
			if(n == h->first) {		//n�� ù��°�� ó���� ����
				insertFirst(h, key);
			} else { //ù��°�ƴϸ�
				node->rlink = n;		//n�� ���������ſ�����
				node->llink = n->llink;		//�������ʿ��� n���ʰ�
				
				n->llink->rlink = node;		//n������ �������� �����
				n->llink=node;				//n�� ����(����)�͵� ����带 ����Ű��
			}
			return 0;
		}

		n = n->rlink;
	}

	insertLast(h, key);		//���������������µ� �Էµ�Ű���� ����ũ�� �������� ����
	return 0;
}


int deleteNode(headNode* h, int key) {

	if (h->first == NULL)		//����Ʈ�������������Ұž���
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first;

	while(n != NULL) {
		if(n->key == key) {
			if(n == h->first) { //ù��°����ù��°������
				deleteFirst(h);
			} else if (n->rlink == NULL){ //���������鸶�����Ż���
				deleteLast(h);
			} else { //�߰���������
				n->llink->rlink = n->rlink;		//n�̶� ������ ���� �����Ŷ� �ٿ����Ű��
				n->rlink->llink = n->llink;
				free(n);		//n�޸�����
			}
			return 1;	//����
		}

		n = n->rlink;	
	}

	//Ű���̾���
	printf("cannot find the node for key = %d\n", key);
	return 1;
}



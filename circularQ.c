#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4    //큐의 최대 크기를 4로 설정한다.

typedef char element;       
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;                 //typedef를 이용하여 char형을 element로 정의하고, 큐를 구현한 자료형 구조체를 QueueType으로 정의한다.


QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();


int main(void)
{
    printf("[---------[최 현 철]    [2022078014]---------]");

	QueueType *cQ = createQueue();  //createQueue함수를 호출하여 포인터 cQ에 큐를 저장할 공간을 할당 받는다.
	element data;                   //char data를 선언한다.

	char command;

	do{     //do-while문을 이용하여 Quit커맨드가 들어올 때 까지 명령어를 받고 각 case의 함수를 호출한다.
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //커맨드를 입력받는다.

		switch(command) {       //switch문을 이용하여 커맨드에 따른 함수를 각각 다르게 호출한다.
		case 'i': case 'I':     //insert 커맨드를 입력받으면 getelement()함수를 호출하여 data를 입력 받은 후, enqueue를 호출하여 큐의 rear에 값을 삽입한다.
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':     //delete 커맨드를 입력받으면 dequeue함수를 호출하여 first의 값을 삭제하고, 삭제한 값을 data에 넣는다.
			deQueue(cQ,&data);
			break;
		case 'p': case 'P':     //print 커맨드를 입력받으면 printQ함수를 이용하여 큐를 출력한다.
			printQ(cQ);
			break;
		case 'b': case 'B':     //debug커맨드를 입력받으면 debugQ함수를 호출하여 큐의 앞뒤에 상관없이 원소를 0부터 MAx까지 출력한다.
			debugQ(cQ);
			break;
		case 'q': case 'Q':     //freeQueue를 호출하여 해당 큐(cQ)를 해제 한다.
            freeQueue(cQ);
			break;
		default:                //잘못된 커맨드가 들어오면 해당 내용을 출력한다.
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');   //quit command가 들어올 때 까지 반복한다.


	return 1;
}

QueueType *createQueue()    
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;      //동적할당을 이용하여 QueueType 크기 만큼을 할당받고, 해당 큐의 front, rear를 0으로 초기화한다. 그리고 할당받은 포인터 cQ를 반환.
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;
    free(cQ);
    return 1;       //큐의 주소를 넘겨받아 해당 큐를 free해준다. 큐가 NULL이면 아무것도 없는 상태이므로 함수를 종료한다.
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}                   //item을 입력받은 후 item을 반환한다.


int isEmpty(QueueType *cQ)
{
	if (cQ->front == cQ->rear){
		printf("Circular Queue is empty!");
		return 1;
	}
	else return 0;
}                   //큐의 주소를 넘겨받아 해당 큐의 front와 rear값이 동일하면 큐에 아무것도 없으므로 1을 반환. 아니면 0을 반환.

int isFull(QueueType *cQ)
{
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) {   // % MAX_QUEUE_SIZE를 이용하여 0~MAX_QUEUE_SIZE-1 에서 rear가 순환하도록 한다.
		printf(" Circular Queue is full!");
		return 1;
	}
	else return 0;  //큐의 주소를 넘겨받아 큐가 MAX_SIZE만큼 꽉 찼는지 검사한다. rear에서 +1 한 값과 front와 동일하면 꽉 찼다고 간주하고 1을 반환한다. 아니면 0을 반환.
}

void enQueue(QueueType *cQ, element item)
{
	if(isFull(cQ)) return;
	else {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;
		cQ->queue[cQ->rear] = item;
	}               //큐의 주소와 삽입할 item을 인수로 받아서 해당 큐가 꽉 찼다면 함수를 종료. 아니면 rear의 값을 +1한 후 해당 인덱스에 item을 삽입한다.
}

void deQueue(QueueType *cQ, element *item)
{
	if(isEmpty(cQ)) return;
	else {
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE;
		*item = cQ->queue[cQ->front];
		return;     //큐의 주소와 data의 주소를 인수로 넘겨받아 해당 큐가 비어있다면 함수를 종료. 아니라면 큐의 front를 +1한 후 해당 인덱스의 값을 data에(역참조를 이용하여) 저장한다.
	}
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;    //%MAX_QUEUE_SIZE를 이용하여 0~MAX_QUEUE_SIZE-1 에서 rear혹은 front가 큐에서 순환하도록 한다.
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");     //큐의 주소를 인수로 넘겨받아 해당 큐의 front+1, rear+1한 값을 first,last에 각각 저장하고, i가 first부터 last 직전까지 큐의 해당 인덱스 원소 값을 출력하도록 한다.
}


void debugQ(QueueType *cQ)  //큐의 주소를 인수로 넘겨받아 해당 큐의 인덱스 0번 요소부터 MAX_QUEUE_SIZE-1요소까지 출력한다. 만약 출력할 요소의 인덱스가 큐의 front라면 front임을 출력한다.
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);  

	}
	//printQ(cQ);
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); //해당 큐의 front, rear 위치의 요소를 각각 출력한다.
}


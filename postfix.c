#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

typedef enum{lparen=0, rparen = 9, times=7, divide = 6, plus = 5, minus=4, operand = 1} precedence;
//연산자와 피연산자의 우선순위를 열거형으로 정의합니다. 또한 해당 열거형을 precedence로 정의합니다.

char infixExp[MAX_EXPRESSION_SIZE];
char postfixExp[MAX_EXPRESSION_SIZE];
char postfixStack[MAX_STACK_SIZE];
int evalStack[MAX_STACK_SIZE];
int postfixStackTop = -1;
int evalStackTop = -1;
int evalResult = 0;
//전역 배열, 전역변수(top 변수, 최종 결과 저장 변수)를 선언합니다.
void postfixPush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();


 int main() {

    printf("[---------[최 현 철]    [2022078014]---------]");

    char command;
    do{
        printf("----------------------------------------------------------------\n");
        printf("               Infix to Postfix, then Evaluation\n");
        printf("----------------------------------------------------------------\n");
                printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
        printf("----------------------------------------------------------------\n");
        printf("Command = ");
        scanf(" %c", &command);
        //command를 입력받습니다.
        
        
        switch(command) {   //입력 받은 command에 따라 호출 함수를 switch문을 이용하여 다르게 합니다.(즉, 입력에 따라 실행 기능이 달라집니다.)
        case 'i': case 'I':
            getInfix();
            break;
        case 'p': case 'P':
            toPostfix();
            break;
        case 'e': case 'E':
            evaluation();
            break;
        case 'd': case 'D':
            debug();
            break;
        case 'r': case 'R':
            reset();
            break;
        case 'q': case 'Q':
            break;
        default:
            printf("\n>>>>>   Concentration!!   <<<<<");
            break;
        }
    //do-while문을 이용하여 입력된 command가 q or Q일 때 까지 해당 명령문을 반복합니다.
    }while(command != 'q' && command != 'Q');

 return 1;
}

void postfixPush(char x)    //문자를 넘겨받아 postfix스택에 push합니다.
{
    postfixStack[++postfixStackTop] = x;    //top변수를 +1한 후 postfix스택의 top에 X를 push합니다.
}
char postfixPop()
{
     char x;
    if(postfixStackTop == -1)   //스택이 비어있다면 -1을 반환합니다.
        return '\0';
    else {  //postfix 스택의 top요소를 반환하고 top을 -1합니다.
     x = postfixStack[postfixStackTop--];
    }
return x; }
void evalPush(int x)    //push할 정수값을 넘겨받아 top변수를 +1한 후 eval스택의 top에 push합니다. 
{
    evalStack[++evalStackTop] = x;
}
int evalPop()   //eval스택의 top변수가 가리키고 있는 요소를 꺼냅니다.
{
    if(evalStackTop == -1)  //만약 top변수가 -1이라면 스택이 비어있다는 의미이므로 -1을 반환합니다.
        return -1;
    else
        return evalStack[evalStackTop--];   //해당 요소를 반환 후, top변수를 -1합니다.
}

void getInfix() //중위 표기식을 입력받아 infixexp 전역 배열에 저장합니다.
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);
}

precedence getToken(char symbol)    //문자를 인수로 넘겨받아 해당 문자가 어떤 연산자인지를 switch문을 통해 판별 후, enum precedence를 반환한다.
{

      switch(symbol) {
     case '(' : return lparen;
     case ')' : return rparen;
     case '+' : return plus;
     case '-' : return minus;
     case '/' : return divide;
     case '*' : return times;
     default : return operand;
     }
}

precedence getPriority(char x)
{
     return getToken(x);    //문자를 인수로 넘겨받아 해당 문자를 다시 인수로 getToken함수를 호출한다.
}

void charCat(char* c)
{
     if (postfixExp[0] == '\0')    //postfixExp문자열이 비어잇는지 검사 후 예외처리. strncat함수는 이어붙일 배열이 비어있을 경우 안된다.
           strncpy(postfixExp, c, 1);
     else
           strncat(postfixExp, c, 1);
}

void toPostfix()
{
    char *exp = infixExp;   //중위 표기식을 저장한 infixexp 시작 주소를 포인터 exp에 저장.
    char x;                 //문자를 저장할 임시변수 선언.

    while(*exp != '\0')     //exp가 가리키는 infixexp의 원소가 /0일 때 즉, 해당 문자열의 마지막까지 반복한다.
    {
        if(getPriority(*exp) == operand)    //exp가 가리키는 문자를 getpriority함수로 열거형 precedence 중 무었인지 파악 후 피연산자라면 해당 명령문 실행
        {
            x = *exp;
            charCat(&x);
            //exp가 가리키는 문자를 임시변수 x에 저장 후, charcat함수를 호출하여 인자로 넘긴다. x가 postfixexp 전역 배열 끝에 이어서 저장된다.
        }
        else if(getPriority(*exp) == lparen)    //exp가 가리키는 문자가 왼쪽 소괄호라면 postfixpush함수를 호출하여 postfixstack에 push한다.
        {
        postfixPush(*exp);
        }
        else if(getPriority(*exp) == rparen)    
        //exp가 가리키는 문자가 오른쪽 소괄호 ')'라면 '('문자가 나올 때 까지 postfixpop함수를 호출하여 해당 스택에서 문자를 꺼내고 charcat함수를 호출하여 postfixexp배열 뒤에 넣는다.
        {
            while((x = postfixPop()) != '(') 
            {    
                charCat(&x);
            } 
        }
        else //exp가 가리키는 문자가 그 외의 연산자라면 postfixstack의 top에 있는 연산자가 해당 연산자보다 우선순위가 높을 동안 pop하여 postfixexp배열에 붙인다.
        {
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))
            {
                x = postfixPop();
                charCat(&x);
            }

            postfixPush(*exp);//while문이 끝나면 해당 연산자를 stack에 push한다.
        }
        exp++; //다음 연산자를 가리킨다.
    }
    while(postfixStackTop != -1) //stack에 있는 모든 원소만큼 각 원소를 pop한 뒤, charcat함수를 호출하여 postfixexp배열 뒤에 이어붙인다.
    {
    x = postfixPop();
    charCat(&x);
    }
}
void debug()
{
     printf("\n---DEBUG\n");
     printf("infixExp =  %s\n", infixExp);  //infixExp(중위 표기식) 문자열을 출력한다.
     printf("postExp =  %s\n", postfixExp); //postfixExp(후위 표기식) 문자열을 출력한다.
     printf("eval result = %d\n", evalResult);//최종 결과값을 출력한다.
     printf("postfixStack : "); 
     for(int i = 0; i < MAX_STACK_SIZE; i++)    //postfix 스택에 저장된 모든 연산자를 출력한다. 0부터 인덱스가 커지는 방향으로 출력된다.
           printf("%c  ", postfixStack[i]);
     printf("\n");
}
void reset()
{
     infixExp[0] = '\0';    //infixExp배열을 초기화한다.
     postfixExp[0] = '\0';  //postfixExp배열을 초기화한다.

      for(int i = 0; i < MAX_STACK_SIZE; i++)   //postfix 스택의 모든 요소를 '\0'으로 초기화한다.
           postfixStack[i] = '\0';
     postfixStackTop = -1;
     evalStackTop = -1; //각각 스택의 top변수를 -1로 초기화한다. 
     evalResult = 0;    //최종 결과를 저장하는 전역변수 evalResult를 0으로 초기화한다.
}   
void evaluation()
{
     int opr1, opr2, i; //피연산자를 담을 변수와 for문용 조작 변수 선언
     int length = strlen(postfixExp); //strlen함수를 이용하여 해당 배열의 전체 길이를 변수 length에 넣는다.
     char symbol;   //연산자, 피연산자를 담을 임시변수 선언
     evalStackTop = -1; //스택이 비어있음을 설정하기 위해 스택의 top을 -1로 설정한다.
     for(i = 0; i < length; i++)    //i는 0부터 length-1 까지 반복한다.
     {
           symbol = postfixExp[i];  //해당 배열로부터 원소를 symbol에 저장한다. 해당 배열의 0번부터 인덱스가 커지는 방향으로 진행한다.
           if(getToken(symbol) == operand) {    //getToken함수를 호출하여 symbol의 값이 피연산자인지 검사한다.
                evalPush(symbol - '0'); //피연산자라면 해당 값은 아스키코드 값이므로 정수로 변환 후 eval스택에 push한다.
           }
           else {
                opr2 = evalPop();   //symbol의 값이 연산자라면 eval스택으로부터 pop하여 피연산자를 opr2, opr1에 넣는다.
                opr1 = evalPop();
                switch(getToken(symbol)) {  //해당 symbol의 연산자가 무었인지에 따라 계산이 달라진다.
                case plus: evalPush(opr1 + opr2); break;
                case minus: evalPush(opr1 - opr2); break;
                case times: evalPush(opr1 * opr2); break;
                case divide: evalPush(opr1 / opr2); break;
                default: break;
                }
} }
     evalResult = evalPop();    //결국 위의 코드를 수행하면 eval스택엔 최종 결과값만 남아있으므로 해당 스택을 pop하여 전역변수 evalresult에 저장한다.
}

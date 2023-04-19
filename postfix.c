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

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x;
}
char postfixPop()
{
     char x;
    if(postfixStackTop == -1)
        return '\0';
    else {
     x = postfixStack[postfixStackTop--];
    }
return x; }
void evalPush(int x)
{
    evalStack[++evalStackTop] = x;
}
int evalPop()
{
    if(evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--];
}

void getInfix() //중위 표기식을 입력받아 infixexp 전역 배열에 저장합니다.
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);
}

precedence getToken(char symbol)
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
     return getToken(x);
}
/***
* 문자하나를 전달받아, postfixExp에 추가 */
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
        else if(getPriority(*exp) == rparen)    //
        {
            while((x = postfixPop()) != '(') 
            {    
                charCat(&x);
            } 
        }
        else 
        {
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))
            {
                x = postfixPop();
                charCat(&x);
            }

            postfixPush(*exp);
        }
        exp++; 
    }
    while(postfixStackTop != -1)
    {
    x = postfixPop();
    charCat(&x);
    }
}
void debug()
{
     printf("\n---DEBUG\n");
     printf("infixExp =  %s\n", infixExp);
     printf("postExp =  %s\n", postfixExp);
     printf("eval result = %d\n", evalResult);
     printf("postfixStack : ");
     for(int i = 0; i < MAX_STACK_SIZE; i++)
           printf("%c  ", postfixStack[i]);
     printf("\n");
}
void reset()
{
     infixExp[0] = '\0';
     postfixExp[0] = '\0';

      for(int i = 0; i < MAX_STACK_SIZE; i++)
           postfixStack[i] = '\0';
     postfixStackTop = -1;
     evalStackTop = -1;
     evalResult = 0;
}
void evaluation()
{
     int opr1, opr2, i;
     int length = strlen(postfixExp);
     char symbol;
     evalStackTop = -1;
     for(i = 0; i < length; i++)
     {
           symbol = postfixExp[i];
           if(getToken(symbol) == operand) {
                evalPush(symbol - '0');
           }
           else {
                opr2 = evalPop();
                opr1 = evalPop();
                switch(getToken(symbol)) {
                case plus: evalPush(opr1 + opr2); break;
                case minus: evalPush(opr1 - opr2); break;
                case times: evalPush(opr1 * opr2); break;
                case divide: evalPush(opr1 / opr2); break;
                default: break;
                }
} }
     evalResult = evalPop();
}

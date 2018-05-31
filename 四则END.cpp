#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stack>
#include<math.h>
#include<Windows.h>
using namespace std;
int n,t,n1;
struct ZX
{
    char a;
    bool b;//if b=0 À¨ºÅ if b=1 Êý×Ö
} ;
stack<ZX>s1;
void atersz(ZX number[100]);
void afterfh(ZX number[100]);
void passkh(ZX number[100]);
int convert(ZX number[100])
{
    stack<ZX>s2;
    for(int i=0;i<t;i++)
    {
        if(number[i].b==1)//²Ù×÷Êý
        s2.push(number[i]);
        else
        {
            if(number[i].a==')')
            { 
                while(s1.top().a!='(')
                {
                    s2.push(s1.top());
                    s1.pop();
                }
                s1.pop();
            }
            else if(s1.empty()||s1.top().a=='('||number[i].a=='(')
            s1.push(number[i]);
            else
            {
                if(number[i].b==0&&(number[i].a=='*'||number[i].a=='/'||number[i].a=='^')&&(s1.top().a=='+'||s1.top().a=='-'))
                s1.push(number[i]);
                else
                {
                    s2.push(s1.top());
                    s1.pop();
                    i--;
                }
            }
        }  
    }
    while(!s1.empty())
    {
        s2.push(s1.top());
        s1.pop();
    }
    while(!s2.empty())
    {
        ZX s=s2.top();
        s2.pop();
        s1.push(s);
    }
    ZX c1;
    int c2,c3,c4;
    stack<int>s3;
    while(!s1.empty())
    {
        c1=s1.top();
        s1.pop();
        if(c1.b==1)
        s3.push(c1.a);
        else
        {
            c2=s3.top();
            s3.pop();
            c3=s3.top();
            s3.pop();
            switch(c1.a)
            {
                case '+':c4=c3+c2;break;
                case '-':c4=c3-c2;break;
                case '*':c4=c3*c2;break;
                case '/':c4=c3/c2;break;
                case '^':c4=pow(c3,c2);break;
            }
            s3.push(c4);
        }  
    }
    return s3.top();
}
void passkh(ZX number[100])
{
    for(int i=1;i<t-1;i++)
    {
        number[i-1].a=number[i].a;
        number[i-1].b=number[i].b;
    }
    t-=2;
}
void aftersz(ZX number[100])
{
    int i=rand()%10;
    if(i<=2)
    {
        int j=rand()%5;
            if(j==0)
            number[t].a='+';
            else if(j==1)
            number[t].a='-';
            else if(j==2)
            number[t].a='*';
            else if(j==3)
            number[t].a='/';
            else number[t].a='^';
        number[t].b=0;
        t++;
        afterfh(number);
    }
    else if(i>=3&&i<=6)
    {
        if(n1==1)
        {
            aftersz(number);
        }
        else
        return ;
    }
    else//ÓÒÀ¨ºÅ
    {
        if(n>0&&number[t-2].a!='('&&number[t-2].b!=0)
        {
            number[t].b=0;
            number[t].a=')';
            n--;
            t++;
            aftersz(number);
        }
        else
        aftersz(number);
    }  
}
void afterfh(ZX number[100])
{
        int p=rand()%10;
        if(p>=3)//Êý×Ö
        {
            number[t].b=1;
            number[t].a=rand()%10+1;
            t++;
            n1++;
            aftersz(number);
        }
        else//×óÀ¨ºÅ
        {
            number[t].b=0;
            number[t].a='(';
            n++;
            t++;
            afterfh(number);
        }
}
int main()
{
	int N;
	printf("Please enter the number of the test:");
	scanf("%d",&N);
    while(N--)
    {
        n1=0,n=0;
        ZX number[100];
        t=0;
        afterfh(number);
        while(n>0)
        {          
            number[t].a=')';
            number[t++].b=0;   
            n--;       
        } 
        while(number[0].a=='('&&number[0].b==0&&number[t-1].b==0&&number[t-1].a==')')
        passkh(number);
        while(number[t-3].a=='('&&number[t-3].b==0)
        {
                number[t-3].a=number[t-2].a;
                number[t-3].b=number[t-2].b;
                t-=2;
        }
        for(int i=0;i<t;i++)
        {
            if(number[i].b==0)
            printf("%c",number[i].a);
            else
            printf("%d",number[i].a);
        }
        printf("=\n");
        int p,q=convert(number);
        printf("Countdown start:\n");
        for(int time=20;time>=0;time--)
        {
        	Sleep(1000);
        	printf("\r%2d",time);
        }
        printf("\n");
        scanf("%d",&p);
        if(p==q)
        printf("You're right!\n\n");
        else
        printf("It's wrong!\nThe right answer is: %d\n\n",q);
         
    }
    return 0;
}

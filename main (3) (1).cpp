/* Hrant Virabyan
October 29, 2022
Stack Calculator 
This program was created in order to calculate math expressions given by the user. It will take the infix expression, turn it into postfix
and then continue to solve the postfix expression. In the end, it will simply display all of the above. 
*/  

#include<iostream>
#include<stack>
#include<math.h>
using namespace std;


bool isOperator(char c)//true or false statement for the operators which will be used later in the code
{
	if(c=='+'||c=='-'||c=='*'||c=='/'||c=='^')
	{
		return true;
	}
	else
	{
		return false;
	}
}

int precedence(char c) 
{ 
    if(c == '^') 
    return 3; 
    else if(c == '*' || c == '/') 
    return 2; 
    else if(c == '+' || c == '-') 
    return 1; 
    else
    return -1; 
} 

string InfixToPostfix(stack<char> s, string infix)
{
	string postfix;

	for(int i=0;i<infix.length();i++)
	{
		if(infix[i] >= '0' && infix[i] <= '9')//makes sure that the expression has numbers
		{
			postfix+=infix[i];

		}
		else if(infix[i] == '(') //if parentheses are present, it will put them in the stack in order to complete the expression in the correct order
		{
			s.push(infix[i]);
		}
		else if(infix[i] == ')')
		{
			while((s.top()!='(') && (!s.empty()))
			{
				char temp=s.top();
				postfix+=temp;

				
				s.pop();
			}
			if(s.top()=='(')
			{
				s.pop();
			}
		}
		else if(isOperator(infix[i]))// this checks if the character is an operator and skips it
		{
			if(s.empty())
			{
				s.push(infix[i]);
			}
			else
			{
				if(precedence(infix[i])>precedence(s.top()))
				{
					s.push(infix[i]);
				}	
				else if((precedence(infix[i])==precedence(s.top()))&&(infix[i]=='^'))// checks if it raised to  a power
				{
					s.push(infix[i]);
				}
				else
				{
					while((!s.empty())&&( precedence(infix[i])<=precedence(s.top())))//while the stack is empty, it adds the expression char to the postfix expression. like a regular number
					{
						postfix+=s.top();

						s.pop();
					}
					s.push(infix[i]);
				}
			}
		}
	}
	while(!s.empty())
	{
		postfix+=s.top();

		s.pop();
	}
	
	return postfix;

}

//this is the code to calculate the postfix expression
int postfixCalc(string a){
    stack<int> st;
    
    for(int i=0; i<a.length();i++){
        if(a[i]>='0' && a[i]<='9') {
            st.push(a[i]-'0');
    }
    else{
        int operation2=st.top();
        st.pop();
        int operation1=st.top();
        st.pop();
        
        switch (a[i])//math operations
             {
            case ' ':
                st.push(a[i]+1);
                break;
            case '+':
                st.push(operation1+operation2);//add
                break;
            case '-':
                st.push(operation1-operation2);//subtract
                break;
            case '*':
                st.push(operation1*operation2);//multiply
                break;
            case '/':
                st.push(operation1/operation2);//divide
                break;
            case '^':
                st.push(pow(operation1,operation2));//raise to the power
                break;
             }
        }
    }
    return st.top();
}




int main() //calls everything
{  

  	string infix_exp, postfix_exp;
  	cout<<"Enter your expression:"<<endl;
  	cin>>infix_exp;//enter the infix expression
  	stack <char> stack;
	cout<<"Infix: "<<infix_exp<<endl;//repeats what you entered
  	postfix_exp = InfixToPostfix(stack, infix_exp);
  	cout<<endl<<"Postfix: "<<postfix_exp<< endl<< endl ;//shows the postfix expression
	cout<<"Evaluation:"<< postfixCalc(postfix_exp)<<endl;//shows the evaluated postfix expresion
	return 0;
}
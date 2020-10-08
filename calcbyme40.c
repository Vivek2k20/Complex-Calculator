/*

Created By Vivek M R.
Started on 1/2/2020
Debugging started on 2/2/2020.
4 Major Versions Created.
This is the latest version of the code.

KNOWN BUGS:(Version 4.0)

1.Multiple Operations cannot be performed at the same time.Only One Operation per Input can be done.

  Proposed Solution: After Identifying PureString,Seperate the string by identifying individual keywords(Use String Search Algorithm) and storing each keyword/substring/operand in another array of strings.
                     Do the same for Operators.Store them in an array of doubles.Currently the same mechanism is being applied,But increasing the size of array is required.
  
  
2.Pie,e,mem1,mem2,mem3,mem4 and rec are treated as an operation.Hence any operation involving these constants need to be inputted in 2 stages:
  a.First,To set an operator to these constants.Hence,Giving input as pie/e will return result as the values.
    This will make it available to the next operation.
  b.Second Input involves the operand and the 2nd operator(if applicable).
    The First Operator is taken as the previous result if an input consists of only one operator,but the operation requires 2 operators.
  
  Proposed Solution: Using String Search/Pattern Identification Algorithm,Whenever these sub strings are encountered in the main string,They can be replaced by the values.

3.Negative values are not being recognised in the input.So,If Negative Values are to be involved,We have to get the result to be the negative value and then use the result.
  Ex:
  If we want arcsin(-1),We have to First Input "0-1"and then "arcsin".This is because the pureno function decodes the mainstring and assumes the numbers to be +ve.
  
  Proposed Solution: Change the pureno function.Maintain another Variable to store the previous character of the character conatining the number.Use this in a if statement and calculate the values of operators accordingly.
                     However,This will lead to a problem during addition and subtraction.We will have to remove the subtraction and addition operators itself.If after reading the input,Operators are not found,Addition should be assumed(strlen of func==0 && topn!=-1).
					 So,In addition to modifying pureno with if cases,We need to modify the purestring function to omit the '+'&'-' Operators,as well as the mainfunction.
					 In the main function,We need to call the pureno and purestring functions right after the input,but before the if(strlen(mainstr)!=) condition.
					 Also,Appropriate actions should be taken inside the if(topn) i.e 
					 1st case :  if((topn==-1)&&(strlen(fun)==0))
						         then,go back and wait for another input.
					 2nd case :  if((topn!=-1)&&(strlen(fun)==0))
						         then add the contents of the stack no(if topn==1)
							     or add the result to the content of the stack(if topn==0)and give out the result.

								 
    LAST UPDATED ON 4/2/2020 18:01

*/  



//Including Header Files and Defining Constants.//
//nan is a constant reserved to flag invalid returns or inputs or outputs//
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define e 2.71828182
#define nan 7242.232123
#define pie 3.14159265359

//History storing variables//
double a[100];
char inputs[100][20];
int top=-1;

//Memory storing variables//
double mem1,mem2,mem3,mem4=0;

//Making Default Notation for trigonometry as radians//
int rad=1;

//Main-Input string storage,Operators and Operands storaging arrays.no is the operator storing array,fun stores operand,mainstr stores the main input//
double no[2];
int topn=-1;
char mainstr[100],fun[100];

//Function to initialize operators array to 0//
void ini()
{
	int i;
	no[0]=no[1]=0;
	topn=-1;
}

//Custom Function that does modulus for double values//
double cusmodulo(double a,double b)
{
    int i=(int)(a/b);
    return(a-(b*i));
}


//Function to display history//
void displayhistory()
{
	if(top==-1)
		printf("No History\n");
	else
	{
		printf("INPUTS\t\t\tRESULTS\n");
		int i;
		for(i=top;i>-1;i--)
			printf("%s\t\t\t%lf\n",inputs[i],a[i]);
	};
}

//Function to Clear History
void clrhis()
{
	int i,j;
		for(i=0;i<99;i++)
		{
			a[i]=0;
			for(j=0;j<19;j++)
			inputs[i][j]="0";
		    inputs[i][j]=NULL;
		};
		for(j=0;j<20;j++)
			inputs[i][j]=NULL;
		top=-1;
}

//Function to store the inputs and results in history//
void addhistory(double r)
{
	top++;
	strcpy(inputs[top],mainstr);
	a[top]=r;
}


//Function to return the most recent result//
double popa()
{
	if(top==-1)
		return 0;
	else
		return a[top];
}


//Function to Calculate Trigonometric values//
double trigon(double b,char sym[])
{
	if(!strcmp(sym,"sin"))
	{
		if(rad==1)return(sin(b));else return(sin((b/180)*pie));
	}else
	if(!strcmp(sym,"cos"))
	{
		if(rad==1)return(cos(b));else return(cos((b/180)*pie));
	}else
	if(!strcmp(sym,"tan"))
	{
		if(rad==1)return(tan(b));else return(tan((b/180)*pie));
	}else
	if(!strcmp(sym,"sinh"))
	{
		if(rad==1)return(sinh(b));else return(sinh((b/180)*pie));
	}else
	if(!strcmp(sym,"cosh"))
	{
		if(rad==1)return(cosh(b));else return(cosh((b/180)*pie));
	}else
	if(!strcmp(sym,"tanh"))
	{
		if(rad==1)return(tanh(b));else return(tanh((b/180)*pie));
	}else
	if(!strcmp(sym,"arcsin"))
	{
		if(rad==1)return(asin(b));else return (asin(b)*180/pie);
	}else
	if(!strcmp(sym,"arccos"))
	{
		if(rad==1)return(acos(b));else return (acos(b)*180/pie);
	}else
	if(!strcmp(sym,"arctan"))
	{
		if(rad==1)return(atan(b));else return (atan(b)*180/pie);
	}else
	if(!strcmp(sym,"arcsinh"))
	{
		if(rad==1)return(asinh(b));else return (asinh(b)*180/pie);
	}else
	if(!strcmp(sym,"arccosh"))
	{
		if(rad==1)return(acosh(b));else return (acosh(b)*180/pie);
	}else
	if(!strcmp(sym,"arctanh"))
	{
		if(rad==1)return(atanh(b));else return ((atanh(b))*180/pie);
	}else
	{
		printf("Syntax Error\n");
	};
	return nan;
}
	
	
//Function that does memory related operations//
double memoryoperations(double b,char sym[])
{
	if(!strcmp(sym,"aclr")||!strcmp(sym,"clra")||!strcmp(sym,"memaclr")||!strcmp(sym,"clrmema"))
	{
		mem1=0;printf("Memory A Cleared!\n");return nan;
	}else
	if(!strcmp(sym,"mema")||!strcmp(sym,"a"))
	{
		return(mem1);
	}else
	if(!strcmp(sym,"memaadd")||!strcmp(sym,"mema+")||!strcmp(sym,"a+")||!strcmp(sym,"aadd"))
	{
		mem1=b;
	    printf("%lf is stored in Memory A!\n",b);return nan;
	}else
	if(!strcmp(sym,"membadd")||!strcmp(sym,"memb+")||!strcmp(sym,"b+")||!strcmp(sym,"badd"))
	{
		mem2=b;
	    printf("%lf is stored in Memory B!\n",b);return nan;
	}else
	if(!strcmp(sym,"membclr")||!strcmp(sym,"bclr")||!strcmp(sym,"clrb")||!strcmp(sym,"clrmemb"))
	{
		mem2=0;printf("Memory B Cleared!\n");return nan;
	}else
	if(!strcmp(sym,"memb")||!strcmp(sym,"b"))
	{
		return(mem2);
	}else
	if(!strcmp(sym,"memcadd")||!strcmp(sym,"cadd")||!strcmp(sym,"c+")||!strcmp(sym,"memc+"))
	{
		mem3=b;
	    printf("%lf is stored in Memory C!\n",b);return nan;
	}else
	if(!strcmp(sym,"memcclr")||!strcmp(sym,"clrc")||!strcmp(sym,"cclr")||!strcmp(sym,"clrmemc"))
	{
		mem3=0;printf("Memory C Cleared!\n");return nan;
	}else
	if(!strcmp(sym,"memc")||!strcmp(sym,"c"))
	{
		return(mem3);
	}else 
	if(!strcmp(sym,"memdadd")||!strcmp(sym,"dadd")||!strcmp(sym,"d+")||!strcmp(sym,"memd+"))
	{
		mem4=b;
	    printf("%lf is stored in Memory D!\n",b);return nan;
	}else
	if(!strcmp(sym,"memdclr")||!strcmp(sym,"clrd")||!strcmp(sym,"dclr")||!strcmp(sym,"clrmemd"))
	{
		mem4=0;printf("Memory D Cleared!\n");return nan;
	}else
	if(!strcmp(sym,"memd")||!strcmp(sym,"d"))
	{
		return(mem4);
	}else
	if(((((((((2*b/pie)-1)/2)-(int)(((2*b/pie)-1)/2))==0)&&(rad==1))||((((((b/90)-1)/2)-(int)(((b/90)-1)/2))==0)&&(rad==0)))&&(!strcmp(sym,"Tan")||!strcmp(sym,"TAN")||!strcmp(sym,"tan")))||(((b>1)||(b<-1))&&(!strcmp(sym,"arcsin")||!strcmp(sym,"arccos")))||((b<1)&&!strcmp(sym,"arccosh"))||(((b>=1)||(b<=-1))&&(!strcmp(sym,"arctanh"))))
	{
		printf("Invalid Input\n");return nan;
	}
	else return(trigon(b,sym));
}

//Function to manage History,Constants and Default settings//
double historyandsettings(double b,char sym[])
{
	if(!strcmp(sym,"his"))
	{
		displayhistory();return nan;
	}else
    if(!strcmp(sym,"hisclr"))
	{
		clrhis();printf("\nHistory Cleared!\n\n");return nan;
	}else
	if(!strcmp(sym,"rec"))
	{
		return(a[top]);
	}else
	if(!strcmp(sym,"help"))
	{
		printf("\n\nJust Type in the Operations you want to perform using the keywords of the functions with operators.\nPlease use one input/keyword in each input\nEx:\n8+9\nmemadd(8)\nSin(78)\nFor Function Library/Keywords Available,type func\n\n");return nan;
	}else
	if(!strcmp(sym,"func"))
	{
		functions();return nan;
	}else
	if(!strcmp(sym,"quit"))
	{
		printf("\n\nQuitting....\nPress any key\n");
		getch();
		exit(0);
	}else
	if(!strcmp(sym,"degtorad"))
	{
		return((b/180)*pie);
	}else
	if(!strcmp(sym,"radtodeg"))
	{
		return((b/pie)*180);
	}else
	if(!strcmp(sym,"settorad"))
	{
		rad=1;printf("\nDefault Inputs and Outputs for Trigonometric functions set to Radians\n\n");return nan;
	}else
	if(!strcmp(sym,"settodeg"))
	{
		rad=0;printf("\nDefault Inputs and Outputs for Trigonometric functions set to Degrees\n\n");return nan;
	}else
	if(!strcmp(sym,"pi")||!strcmp(sym,"pie"))
	{
		return(pie);
	}else
	if(!strcmp(sym,"e"))
	{
		return(e);
	}else
		return memoryoperations(b,sym);
}

	
//Function to calculate which uses only one operand//
double calculatesingle(double b,char sym[])
{
	if(!strcmp(sym,"log"))
	{
		if(b>0)
		return(log10(b));
	    else
		printf("Invalid Input\n");
	return nan;
	}else
	if(!strcmp(sym,"ln"))
	{
		if(b>0)
		return(log(b));
	else printf("Invalid Input\n");
	return nan;
	}else
	if(!strcmp(sym,"sqrt"))
	{
		if(b>=0)
		return(pow(b,0.5));
	else printf("Invalid Input\n");
	return nan;
	}else
	if(!strcmp(sym,"sq"))
	{
		return(pow(b,2));
	}else
	if(!strcmp(sym,"cube"))
	{
		return(pow(b,3));
	}else
	if(!strcmp(sym,"exp"))
	{
		return(pow(e,b));
	}else
		return(historyandsettings(b,sym));
}

//Function that calculates for 2 operands//
double calculate(double a,double b,char sym[])
{
	if(!strcmp(sym,"+"))
	{
		return (a+b);
	}else
	if(!strcmp(sym,"-"))
	{
		return (a-b);
	}else
	if(!strcmp(sym,"*"))
	{
		return (a*b);
	}else
	if(!strcmp(sym,"/"))
	{
		if(b==0)
		{
			printf("Division by 0 error\n");
			return nan;
		}
		else
		return (a/b);
	}else
	if(!strcmp(sym,"%"))
	{
		return (cusmodulo(a,b));
	}else
	if(!strcmp(sym,"^"))
	{
		return pow(a,b);
	}else
	if(!strcmp(sym,"!")&&(b>=0))
	{
		int i,res=1;
		for(i=1;i<=(int)b;i++)
			res=res*i;
		return(res);
	}else 
	if(topn==-1)
		return(calculatesingle(a,sym));
	else
		return(calculatesingle(b,sym));
}

//Function to display the function library and keywords//
void functions()
{
	int ch;
	printf("\n--------Functions Library--------\n\n\n1.Arithmetic Functions\n2.Trigonometric Functions\n3.Memory Operations :\n\nEnter your choice :\n");
	scanf("%d",&ch);
	if(ch==1)
	{
		printf("Keywords are given in the brackets\nOperations available :\n1.Add(+)\n2.Subtract(-)\n3.Multiply(*)\n4.Divide(/)\n5.Remainder(%)\n6.Power(^)\n7.Square-root(sqrt)\n8.Square(sq)\n9.Cube(cube)\n10.Log to base 10(log)\n11.Log to base e(ln)\n12.e to the power(exp)\n13.Factorial(!)\n");
	}
	else if(ch==2)
	{
		printf("Keywords are given in the brackets\nCurrent default inputs & outputs are in terms of : ");
		if(rad==1)printf("Radians\n");else printf("Degrees\n");
		printf("Operations available :\n1.Sin(sin)\n2.Cos(cos)\n3.Tan(tan)\n4.Sinh(sinh)\n4.Cosh(cosh)\n5.Tanh(tanh)\n6.Degrees to Radians(degtorad)\n7.Radians to Degrees(radtodeg)\n8.Set Radians as Default Input & Output(settorad)\n9.Set Degrees as Default Input & Output(settodeg)\n10.Sin-Inverse(arcsin)\n11.Cos-Inverse(arccos)\n12.Tan-Inverse(arctan)\n13.Sinh-Inverse(arcsinh)\n14.Cosh-Inverse(arccosh)\n15.Tanh-Inverse(arctanh)\n"	);
	}
	else if(ch==3)
	{
		printf("Keywords are given in the brackets\nOperations available :\n1.Show History(his)\n2.Clear History(hisclr)\n3.Show Most Recent Result(rec)\n4.Access Memory A(mema or a)\n5.Clear Memory A(mem1clr or clra or clrmema)\n6.Store at Memory A(memaadd or mema+ or a+)\nSimilarly 3 more memories are available.\nMemory B,Memory C and Memory D.\nThese Memories also support the same operations as Memory A.\nCurrent Memory Values :\nMemory A:%lf\nMemory B:%lf\nMemory C:%lf\nMemory D:%lf\n",mem1,mem2,mem3,mem4);
	}
	else printf("Invalid Input\n");
}



//Function to convert the mainstring to purecharacters or operand string//
void purestring()
{
	int i,j=0;
	for(i=0;i<strlen(mainstr);i++)
	{
		 if ((mainstr[i] >= 'A' && mainstr[i] <= 'Z') || (mainstr[i] >='a' && mainstr[i] <= 'z')||(mainstr[i]=='!')||(mainstr[i]=='%')||(mainstr[i]=='*') || (mainstr[i]=='+')||(mainstr[i]=='-')||(mainstr[i]=='/')||(mainstr[i]=='^'))
        {
            fun[j] = mainstr[i];
            j++;
        }
	};
	fun[j]='\0';
}



//Function to remove the operators and place them in stack no or operator array no//
void pureno()
{
	int i,j,done;
	done=0;
	topn++;
	i=0;j=0;
	while(i<=strlen(mainstr))
	{
		while(((mainstr[i]>='0')&&(mainstr[i]<='9')))
		{
			done=1;
			no[topn]=(no[topn]*10)+(int)mainstr[i]-48;
			i++;
		};
	    if(mainstr[i]=='.')
	    {
			done=1;
			i++;
			j=1;
			while(((mainstr[i]>='0')&&(mainstr[i]<='9')))
			{
				no[topn]=no[topn]+(((int)mainstr[i]-48)/(double)pow(10,j));
				j++;
				i++;
			};
		};
		if(done==1)
		{
			done=0;
			topn++;
			i++;
		}
		else i++;
	};
	topn--;
}



//MAIN FUNCTION//

void main()
{
	double op1,op2,result;
	clrhis();
	printf("For Help,type help\nTo Quit,type quit\n");
	while(1)
	{
	    op1=op2=result=0;
		ini();
		gets(mainstr);
		if(strlen(mainstr)!=0)
		{
		purestring();
		pureno();
		if(topn==0)
		{
			op1=popa();
			op2=no[topn];
		}
		else if(topn==-1)
		{
			op2=popa();
			op1=popa();
		}
		else 
		{
			op1=no[topn-1];
			op2=no[topn];
		};
		result=calculate(op1,op2,strlwr(fun));
		if (result!=nan)
		{
			printf("Result : %lf\n",result);
		    addhistory(result);
		};
		};
	};
}




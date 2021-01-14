//HW7, Nick Feibel, CS222-001

#include <stdio.h>	//Include for printf/scanf
#include <math.h>	//Include for sqrt

typedef struct {double num1, num2;} complexNum;				//Complex number structure with 2 doubles

void add_complex(complexNum, complexNum, complexNum*);		//Method to add the complex numbers
void multiply_complex(complexNum, complexNum, complexNum*); //Method to multiply the complex numbers
void abs_complex(complexNum, double*);						//Method to get absolute value of the complex number
void f(int, complexNum, complexNum*);						//Method to get recursive f(n, c) value
void scan_complex(double*, double*, int*);					//Method to scan inputs for main program
void print_complex(int n, complexNum, complexNum);			//Method to print f(n, complex number) result

//main() runs needed methods for HW
int main(){
	
	//Variables initalized
	int n;
	double abs;
	complexNum c, re;
	
	//scan_complex() is called to provide the values
	scan_complex(&c.num1, &c.num2, &n);

	//f() is called to calculate recursive function
	f(n, c, &re);
	
	//print_complex() called to print the evaluation of the above f() call
	print_complex(n, c, re);
	
	//abs_complex() called and value printed
	abs_complex(re, &abs);
	printf("Absolute Value = %f\n", abs);
	
	return 1;
}

/*scan_complex() scans the values from input and provides them for main
  through address passing*/
void scan_complex(double *a, double *b, int *n){
	
	printf("Please input integer n, and complexNum a and b doubles: \n");	
	scanf("%d%lf%lf", n, a, b);
	
	
}

//print_complex() prints the evaluation from f()
void print_complex(int n,complexNum c, complexNum re){
	
	printf("f(%d,(%f, %f)) = (%f, %f)\n", n, c.num1, c.num2, re.num1, re.num2);

}

//add_complex() adds the 2 complex numbers, a and b. This is utilized in f()
void add_complex(complexNum a, complexNum b, complexNum *re){
	
	
	(*re).num1 = a.num1 + b.num1;
	(*re).num2 = a.num2 + b.num2;
	
}

//multiply_complex() multiplies the 2 complex numbers, a and b. This is utilized in f()
void multiply_complex(complexNum a, complexNum b, complexNum *re){
	
	
	(*re).num1 = a.num1 * b.num1 - a.num2*b.num2;
	(*re).num2 = a.num1 * b.num2 + a.num2*b.num1;
	
}

//abs_complex() calculates the absolute value of complex number a
void abs_complex(complexNum a, double *re){
	
	*re = sqrt((a.num1 * a.num1) + (a.num2 * a.num2));
	
}

/*f() calculates the recursive function f(n, c) = f(n-1, c)*f(n-1, c) + c
  with end condition of f(0, c) = c*/
void f(int n, complexNum c, complexNum *re){
	
	
	if (n<=0){	//End Condition
		*re = c;
	}
	else {		//Recursive call if end condition not met
		f(n-1, c, re);
		multiply_complex(*re, *re, re);
		add_complex(*re,c, re);
	}
	
}
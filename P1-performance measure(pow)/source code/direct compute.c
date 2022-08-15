#include<stdio.h>
#include<time.h>
clock_t start,stop;// Time recorder 
double duration;// Time use in algorithm
double Pow(double x,int i);//Calculate function
int main(){
	double x,sum;    								//The number we will calculate
	int i,j;										//The power rate is i
	printf("«Î ‰»Îx∫Õi£∫\n");					//reminder to reader
	scanf("%lf %d",&x,&i);        				//input x and i
	start = clock();							//Initialize the start time
	for(j=1;j<=10000;j++)						//Expand 10000 times
	sum = Pow(x,i);								//Calculate function
	printf("%lf\n",sum);							//output calculate consequence
	stop = clock();								//record final time
	duration = ((double) (stop - start))/CLK_TCK;//calculate duration
	printf("To increase run time,consider run 10000 times\n");
	printf("duration is %lf\nall time is %lf",duration,(double)(stop - start));//output value
}
double Pow(double x,int i){
	double sum = 1;								//Initialize the output
	if(i==0){									//analyse n is 0
		return 1;							//make a loop to compute n times 
	}else{
		int j;
		for(j=1;j<=i;j++){						// with j growing, sum change
			sum*=x;
		}
	}
	return sum;									//output the consequence
}

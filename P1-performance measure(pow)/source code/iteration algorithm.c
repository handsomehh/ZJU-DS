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
	for(j=1;j<=1000000;j++)						//Expand 1000000 times
	sum = Pow(x,i);								//Calculate function
	printf("%lf\n",sum);							//output calculate consequence
	stop = clock();								//record final time
	duration = ((double) (stop - start))/CLK_TCK;//calculate duration
	printf("To increase run time,consider run 1000000 times\n");
	printf("duration is %lf\nall time is %lf",duration,(double)(stop - start));//output value
}
double Pow(double x,int i){
	if(i==0){									//analyse when i is 0
		return 1;								//consequence is 1
	}
	if(i==1){									//ananlyse when i is 1
		return x;								//consequence is x
	}
	int j;										//auxiliary number
	double sum=x;
	for(j=2;j<=i;j=j*2);						//calculate whether we should compute x extraly in certain loop
	j=j/4;										//find nearest 2 powers
	while(j>=1){
		if((i/j)%2==0){							
			x = x*x;							//when i/j is Exactly divisible by2
		}else{
			x = x*x*sum; 						//when i/j is not divisible by2
		}
		j=j/2;
	}
	return x;									//output value
}

#include<stdio.h>
#include<time.h>
clock_t start,stop;// Time recorder 
double duration;// Time use in algorithm
double Pow(double x,int i);//Calculate function
int main(){
	double x,sum;    							//The number we will calculate
	int i,j,k;									//The power rate is i
	printf("«Î ‰»Îx∫Õi£∫\n");					//reminder to reader
	scanf("%lf %d",&x,&i);						//input x and i
	start = clock();							//Initialize the start time
	for(j=1;j<=1000000;j++)						//Expand 1000000 times
	sum = Pow(x,i);								//Calculate function
	printf("%lf\n",sum);						//output calculate consequence
	stop = clock();								//record final time
	duration = ((double) (stop - start))/CLK_TCK;//calculate duration
	printf("To increase run time,consider run 1000000 times\n with i = %d",i);
	printf("duration is %lf\nall time is %lf\n",duration,(double)(stop - start));//output value
}
double Pow(double x,int i){
	if(i == 0){
		return 1;								//analyse when i is 0
	}
	if(i == 1){									//ananlyse when i is 1
		return x;
	}
	if(i%2 == 0){								//when i is divisible by 2
		return Pow(x*x,i/2);			//recursive 
	}else{										//when i is not divisible by 2
		return Pow(x*x,i/2)*x;         //recursive 
	}
}

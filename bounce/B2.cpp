/* Author: º«âýÈÙ; ID: 3200105385; No.02 */
#include<stdio.h>
#define MAXSIZE 99999
typedef struct man MAN;
typedef struct hats HAT;
struct man{
	int weight;
	int index;
}M[MAXSIZE];
struct hats{
	int size;
}H[MAXSIZE];
int stack[MAXSIZE],top = 0;
int N;
void PrintResult();
void Sort();
int main(){
	int i;
	scanf("%d",&N);
	for(i=1;i<=N;i++){
		scanf("%d",&stack[top]);
		H[i].size = stack[top++];
	}
	for(i=1;i<=N;i++){
		scanf("%d",&M[i].weight);
		M[i].index = i;
	}
	Sort();
	PrintResult();
} 
void Sort(){
	int i,j;
	for(i=1;i<N;i++){
		for(j=1;j<=N-i;j++){
			if(M[j].weight<M[j+1].weight){
				MAN temp1 = M[j];
				M[j] = M[j+1];
				M[j+1] = temp1;
			}
			if(H[j].size<H[j+1].size){
				HAT temp2 = H[j];
				H[j] = H[j+1];
				H[j+1] = temp2;
			}
		}
	}
}
void PrintResult(){
	while(1){
		if(top==0)break;
		int i;
		for(i=1;i<=N;i++){
			if(stack[top-1]==H[i].size)break;
		}
		if(top-1!=0)printf("%d ",M[i].index);
		else printf("%d",M[i].index);
		top--;
	}
}

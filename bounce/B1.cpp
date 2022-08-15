/* Author: º«âýÈÙ; ID: 3200105385; No.01 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXSIZE 1000
struct queue{
	int Ele[MAXSIZE];
	int front,rear;
}Q;
int N,M;
int enqueue(int x);
int isEmpty();
void Initial();
int Judge(int ori[],int temp[]);
int main(){
	scanf("%d %d",&N,&M);
	int ori[N+1],temp[N+1],i,j;
	Initial();
	for(j=1;j<=N;j++)scanf("%d",&ori[j]);
	for(i=1;i<=M;i++){
		for(j=1;j<=N;j++)scanf("%d",&temp[j]);
		if(!Judge(ori,temp)){
			printf("no");
		}else{
			printf("yes");
		}
		if(i!=M)printf("\n");
		Initial();
	}
}
int Judge(int ori[],int temp[]){
	int index_o=1,index_t=1;
	while(1){
		int flag=0;
		if(index_o != N+1)enqueue(ori[index_o++]);
		if(Q.Ele[Q.front]==temp[index_t]){
			Q.front++;
			index_t++;
			flag = 1;
		}else if(Q.Ele[Q.rear-1]==temp[index_t]){
			Q.rear--;
			index_t++;
			flag = 1;
		}
		if(index_o==N+1&&index_t==N+1)return 1;
		if(index_o==N+1&&index_t<N+1&&flag==0)return 0;
	}
}
int enqueue(int x){
	Q.Ele[Q.rear++] = x;
}
void Initial(){
	Q.front = 0;
	Q.rear = 0;
}

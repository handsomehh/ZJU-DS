#include<stdio.h>
#include<stdlib.h>
#define INF 11111
#define MAXSIZE 10001
#define ERROR -1

struct hospital{
	int path[MAXSIZE];//memorize the path for each verterx's father node 
	int Am;			  //memorize the number of ambulances in this hospital
	int dist[MAXSIZE];//memorize the distance from hospital to verterx
	int know[MAXSIZE];//memorize the node which is alrady be collected
	int street[MAXSIZE];//memorize the the number of streets that we must pass to reach the verterx 
}*H[100];

int Adj[MAXSIZE][MAXSIZE];//adjacency matrix
int Adj_f[MAXSIZE][MAXSIZE];//auxiliary adjacency matrix
int Na,Ns,edge,k,call,flag;//Na is the number of hospital,Ns is spots,edge is edge,flag is to adjust the format of outputing

void Init_Adj();//initial the adjacency matrix
void InputRoute();//input the edge and construct the graph
void Print(int k);//print the final consequence
void CopyAdj();//copy to assign to matrix "Adj_f"
int TurnToInt(char *ch);//Turn a char to integer
void Dij(int num);//Dijkstra algorithm
int FindMin(int dist[],int know[]);//Find a min term of distance for a verterx
void Outputpath(int index,int call1);//output consequence

int main(){
	int i,j;
	scanf("%d %d",&Ns,&Na);//input the number of spots and hospitals
	for(i=1;i<=Na;i++){
		H[i] = (struct hospital*)malloc(sizeof(struct hospital));//apply for space
		scanf("%d",&H[i]->Am);//number of ambulances 
	}
	scanf("%d",&edge);//number of edges
	Init_Adj();//initial the adj matrixm, inwhich adj[i][i] is 0 and others are INF
	for(i=1;i<=edge;i++){
		InputRoute();//input route
	}
	for(i=1;i<=Na;i++)Dij(i);//Dijkstra for every hosptial,record path message and distance message
	scanf("%d",&call);//number of calls
	for(i=1;i<=call;i++){
		scanf("%d",&k);
		Print(k);//arange every route for every call
	}
}
void Init_Adj(){//initial the adj matrixm, in which adj[i][i] is 0 and others are INF
	int i,j;
	for(i=1;i<=Na+Ns;i++){
		for(j=1;j<=Na+Ns;j++){
			if(i==j){
				Adj[i][j]=0;//the distance from a verterx to itself is zero 
			}
			else {
				Adj[i][j]=INF;//the distance from a verterx to others are infinite 
			}
		}
	}
}
void InputRoute(){
	int ve1,ve2,rank;
	char ch[10],ch1[10];
	scanf("%s",ch);//input as a string
	scanf("%s",ch1);
	scanf("%d",&rank);//the rank of every edge
	if(ch[0]!='A'){//when inputting is not a hospital 
		ve1 = TurnToInt(ch);//convert string to integer
	}else{
		ve1 = TurnToInt(ch+2)+Ns;
	}
	if(ch1[0]!='A'){//when inputting is not a hospital 
		ve2 = TurnToInt(ch1);//convert string to integer
	}else{
		ve2 = TurnToInt(ch1+2)+Ns;
	}
	Adj[ve1][ve2] = rank;//assign to the adjacency matrix
	Adj[ve2][ve1] = rank;//assign to the adjacency matrix
}
int TurnToInt(char *ch){//convert string to integer
	int sum=0,i=0;
	while(ch[i]!='\0'){//stop when read '\0'
		sum = sum*10 + ch[i]+0-'0';
		i++; 
	}
	return sum;	//return sum
}
void CopyAdj(){//copy adjacency matrix
	int i,j;
	for(i=1;i<=Na+Ns;i++){
		for(j=1;j<=Na+Ns;j++){
			Adj_f[i][j]=Adj[i][j];//assign to every element
		}
	}
} 
void Dij(int num){//Dijkstra algorithm
	int j,i,ve;
	CopyAdj();//copy matrix
	for(i=1;i<=Na+Ns;i++){//initial hospital's message
		H[num]->dist[i]=Adj_f[num+Ns][i];
		if(H[num]->dist[i]<INF)//discuss different cases
			H[num]->path[i] = num+Ns;
		else
			H[num]->path[i] = -1;
		H[num]->know[i]=0;//when not be collected, assign 0
		H[num]->street[i]=0;//when cross streets are unnessary
	}
	while(1){
		ve = FindMin(H[num]->dist,H[num]->know);//find minterm in dist[]
		if(ve==ERROR) break;//if the graph is all scaned
		H[num]->dist[ve]=Adj_f[num+Ns][ve];//assign the value to dist[]
		H[num]->know[ve] = 1;//ve is what we find as a nearest verterx
		for(i=1;i<=Na+Ns;i++){
			if(i != num+Ns){//except for hospital itself 
				if(H[num]->know[i]==0&&Adj_f[ve][i]<INF){//if it's not be dealt
					if(Adj_f[num+Ns][i]>Adj_f[num+Ns][ve]+Adj_f[ve][i])//update distance's message
					{
						Adj_f[num+Ns][i] = Adj_f[num+Ns][ve]+Adj_f[ve][i];
						H[num]->dist[i] =  Adj_f[num+Ns][ve]+Adj_f[ve][i];//memorize dist message
						H[num]->path[i] = ve;//memorize the path message
						H[num]->street[i] = H[num]->street[ve]+1;//memorize street message
					}
				}
			}
		}
	}
}
int FindMin(int dist[],int know[]){//find minterm
	int i,min=INF-1,index=ERROR;
	for(i=1;i<=Na+Ns;i++){
		if(min > dist[i] && know[i] == 0 && dist[i]>0){//record the index of min term in uncollected array
			min = dist[i];
			index = i;
		}
	}
	return index;//return index
}
void Print(int call1){//print result for every call
	int min_dist=INF;
	int min_street=INF;
	int max_Am=-1;
	int index=-1;
	int i,j,k;
	for(i=1;i<=Na;i++){//find minmum distance at first
		if(min_dist>H[i]->dist[call1]&&H[i]->Am>0){//ensure this hospital has ambulance
			index = i;//record index
			min_dist = H[i]->dist[call1];//update distance message
			min_street = H[i]->street[call1];//update street message =
			max_Am = H[i]->Am;//update ambulance message
		}
	}
	if(index == -1){//if not be found, index is -1 and it means All busy
		printf("\nAll Busy");
		return;	
	}
	for(i=1;i<=Na;i++){//keep  ambulance number in mind,and update result
		if(min_dist==H[i]->dist[call1]&&max_Am<H[i]->Am&&H[i]->Am>0){
			index = i;
			min_street =  H[i]->street[call1];
			max_Am = H[i]->Am;
		}
	}
	for(i=1;i<=Na;i++){//keep street in mind,and update result
		if(min_dist==H[i]->dist[call1]&&max_Am==H[i]->Am&&H[i]->Am>0){
			if(min_street>H[i]->street[call1]){
				index = i;
				min_street = H[i]->street[call1];
			}
		}
	}
	(H[index]->Am)--;//reduce ambulance after every call
	Outputpath(index,call1);//output result
	printf("\n%d",H[index]->dist[call1]);//output distance
}
void Outputpath(int index,int call1){
	int stack[MAXSIZE];//define a stack to inverse the result
	int top=0;//stack's top
	if((flag++)==0)printf("A-%d",index);//adjust format of outputting
	else printf("\nA-%d",index);
	int i;
	for(i=call1;i!=index+Ns;i=H[index]->path[i])stack[top++]=i;//push into stack one by one
	for(i=top-1;i>=0;i--){//print result on the screen
		if(stack[i]>Ns)
		printf(" A-%d",stack[i]-Ns);
		else
		printf(" %d",stack[i]);
	}
}

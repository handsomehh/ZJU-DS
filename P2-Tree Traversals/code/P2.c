#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define LEFT -1										//define the position to make a linked-List 
#define RIGHT -2									//define the position to make a linked-List
#define MAXSIZE 300									//define most range of inputting number
int N,index;  										//index is used to create "add" array,index is "index" of array's elements
typedef struct tree *Tree;							//define a tree
struct tree{										//implementation of the tree
	int index;										//store elements' index
	Tree next;
	Tree left,right;
};
struct queue{										//implementation of the queue
	Tree elements[MAXSIZE]; 						//elements of the queue is a tree
	int front,rear;
};
int first;
Tree dummy;											//dummy head defined only one
typedef struct queue *QUEUE;
void Levelorder(Tree T);							//print tree's elements by levelorder traversal
Tree DeletQ(QUEUE Q)	;							//delet and output one element in the queue
void AddQ(QUEUE Q,Tree ele);						//add elements in to the array
void BuildTree(int *in_left,int *pos_left,int size,Tree ptr,int position);//build a tree to print elements
int MakeTree(int in_left,int in_right,int pre_left,int pre_right,int pos_left,int pos_right);//judge and make a final array
void Calculate(int *unce,int *doubt);				//calculate the number
void InputElements(int N);							//input elements to array
int ReadInt();  									//read the inputting data
void BuildFinal(int *in,int *pos,int size,Tree T,int position);
int in[MAXSIZE],pos[MAXSIZE],pre[MAXSIZE],miss[MAXSIZE],final_in[MAXSIZE],final_pos[MAXSIZE],final_pre[MAXSIZE];//store final consequence
int main(){
	scanf("%d",&N);                                	//the size of  the tree we will input
	dummy = (Tree)malloc(sizeof(struct tree));
	dummy->next=NULL;
	int unce,doubt;									//unce is uncertain,doubt is suspective elements,miss is auxiliary array
	InputElements(N);								//input elements to array
	Calculate(&unce,&doubt);						//find the number of unce and doubt
	int i;
	if(unce>1||MakeTree(1,N,1,N,1,N)==0){
		printf("Impossible");						//if can make a unique tree,print impossible
	}else{	
		for (i = 1;i<=N+1;i++)if(!final_in[i]&&unce)final_in[i]=doubt;//assignment of uncertain to in[]
		for (i = 1;i<=N+1;i++)if(!final_pos[i]&&unce)final_pos[i]=doubt;//assignment of uncertain to pre[]
		for (i = 1;i<=N+1;i++)if(!final_pre[i]&&unce)final_pre[i]=doubt;//assignment of uncertain to pos[]
		for(i = 1;i<N;i++)printf("%d ",final_in[i]);
		printf("%d\n",final_in[N]);					//print tree's elements by inorder traversal
		for(i = 1;i<N;i++)printf("%d ",final_pre[i]);
		printf("%d\n",final_pre[N]);				//print tree's elements by preorder traversal
		for(i = 1;i<N;i++)printf("%d ",final_pos[i]);
		printf("%d\n",final_pos[N]);				//print tree's elements by postorder traversal
		BuildFinal(final_in,final_pos,N,NULL,0);	
		Levelorder(dummy->next);					//print tree's elements by levelorder traversal
	}
}
int Readint(){  									//read the inputting data
    int index,sum=0;
	char num[50];
    scanf("%s", num);								//read as the string
    for (index=0;index<strlen(num);index++){
		if (num[0] == '-') return sum; 				//case that inputting is '-'
		sum=sum*10+num[index]-'0'; 					//transform char to int
	}  
    return sum;
}
void InputElements(int N){							//input elements
	int i;
	for (i = 1; i <= N; i++){
        in[i] = Readint();
        if(in[i]!='-') miss[in[i]]=1; 				//input in[],and assignment to miss[in[i]]
    }
    for (i = 1; i <= N; i++){
        pre[i] = Readint();
        if(pre[i]!='-') miss[pre[i]]=1;  			//input pre[],and assignment to miss[pre[i]]
    }
    for (i = 1; i <= N; i++){
        pos[i] = Readint();
        if(pos[i]!='-') miss[pos[i]]=1; 			//input pos[],and assignment to miss[pos[i]]
    }
}

int MakeTree(int in_left,int in_right,int pre_left,int pre_right,int pos_left,int pos_right){
	int i,max;										//max store the final elements to it 
	if (in_left>in_right){							//exit of function
	return 1; 	
	}
    for(i=in_left;i<=in_right;i++){
    	//control the input elements,if elements is illegal continue always
		if (in[i] && pre[pre_left] && in[i]!=pre[pre_left])continue;
		if (in[i] && pos[pos_right]&&in[i]!=pos[pos_right])continue;
        if (pre[pre_left] && pos[pos_right] && pre[pre_left] != pos[pos_right])continue;
        //find the node of the root or all searched elements are '-'
		max = (in[i]>pre[pre_left]?in[i]:pre[pre_left]);
		max = (max>pos[pos_right]?max:pos[pos_right]);//assignment of max
        //assignment and add elements to array
		final_in[i] = max;
        final_pos[pos_right] = max;
        final_pre[pre_left] = max;
		// *child = i; 
        //recursive to judge if this is correct case
		if (!MakeTree(i+1,in_right,pre_left+i-in_left+1,pre_right,pos_left+i-in_left,pos_right-1))continue;
        if (!MakeTree(in_left,i-1,pre_left+1,pre_left+i-in_left,pos_left,pos_left+i-in_left-1))continue;
		return 1;
    } 
    return 0;
}
void Calculate(int *unce,int *doubt){
	int i;									//loop auxiliary variable
	*unce=0,*doubt=-1;						
	for(i=1;i<=N;i++){
		if(miss[i]==0){						//recorded the miss elements
			*doubt=i;						//only function when unce is 1
			(*unce)++;
		}
	}
}
void BuildFinal(int *in,int *pos,int size,Tree T,int position){//build up a final tree according to pos[] and in[]
	int index,i;							//index is the elements index
	int in_left[MAXSIZE],in_right[MAXSIZE]; //in_left[] stores the elements in left of in[]
	int pos_left[MAXSIZE],pos_right[MAXSIZE];//pos_left[] stores the elements in left of in[]
	Tree temp=(Tree)malloc(sizeof(struct tree));//make a temporary node
	if(size<=0){							//recursive exit
		return;
	}else{
		for(index=1;index<=size;index++){	//find the index which in[index]=pos[size]
			if(in[index]==pos[size])break;
		}
		pos_left[0]=0;
		pos_right[0]=0;
		for(i=0;i<=index-1;i++){			//asignment to array
			in_left[i]=in[i];
			pos_left[i]=pos[i];
		}
		for(i=0;i<=size-index;i++){			//asignment to array
			if(i==0)continue;
			in_right[i]=in[index+i];
			pos_right[i]=pos[index-1+i];
		}
		if(dummy->next==NULL){				//first case when dummy->next is NULL
			temp->index = pos[size];		//make a node and tie it ti dummy->next
			temp->left=NULL;				//make sure tree is ilegal
			temp->right=NULL;
			dummy->next=temp;
		}else{								//ordinary case,when positon 
			temp->index = pos[size];		//make a node and tie it ti dummy->next
			temp->left=NULL;
			temp->right=NULL;
			if(position==RIGHT)T->right=temp;//when position is "LEFT",tie it to left of tree
			else T->left=temp;
		}
		BuildFinal(in_right,pos_right,size-index,temp,RIGHT);//recursive 
		BuildFinal(in_left,pos_left,index-1,temp,LEFT);
		return;
	}
}
QUEUE CreateQueue(){								//create a Queue and return dummy header
	QUEUE Q;
	Q = (QUEUE) malloc(sizeof(struct queue));
	Q->front=0;
	Q->rear=0;
	return Q; 
}
void AddQ(QUEUE Q,Tree ele){							//add one element in to queue
	QUEUE temp;
	if(ele==NULL)return;
	Q->elements[Q->rear]=ele;
	Q->rear++;
}
Tree DeletQ(QUEUE Q){								//delet one element and input it in the queue
	if(Q->rear<=Q->front){
		return NULL;
	}else{
		if(index!=N-1){
			printf("%d ",(Q->elements[Q->front])->index);//output the result
			index++;
		}else{
			printf("%d",(Q->elements[Q->front])->index);
		}
		return Q->elements[Q->front++];
	}
}
void Levelorder(Tree T){							//traversal tree in levelorder sequence
	QUEUE Q;
	Q = CreateQueue();								//create a queue
	int index;
	AddQ(Q,dummy->next);						//add one element into queue
	while(T = DeletQ(Q)){						//loop
		if(T->left)AddQ(Q,T->left);
		if(T->right)AddQ(Q,T->right);
	}
}

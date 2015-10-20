#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
struct node{
	int index;
	int parent;
	int key; //a big number
	int add;
	int inheap;
	//struct node *edge = NULL;
	struct node *next;
    
};

int getint(char *s){
	int i=0;
	int p=1;
	int len2=strlen(s);
	printf("str: %s, len:%d\n",s,len2);
	int num=0;
	for(i=0;i<len2;i++){
		p=1;
		int j=0;
		for(j=0;j<len2-i-1;j++){
			p=p*10;
		}
		num=num+p*(s[i]-'0');
	}
	//printf("hehe %d\n",num);
	return num;
}
void find(int start,int end,int cor[10000][2],int nume,struct node s[]){
	int i=0;
	
	/*
	for(i=0;i<all-1;i++){
		s[i].next=&s[i+1];
		s[i].index=i;
	}
	*/
	//s[all-1].next=NULL;
	//s[all-1].index=all-1;
	for(i=0;i<nume;i++){
		struct node e1;
		e1.index=cor[i][1];
		e1.next=s[cor[i][0]].next;
		s[cor[i][0]].next=&e1;
		struct node e2;
		e2.index=cor[i][0];
		e2.next=s[cor[i][1]].next;
		s[cor[i][1]].next=&e2;
	}


}
void main(){
	char name[10000];
	int cor[10000][2];
	int nume=0;
	int all=0;
	int start;
	int end;
	while(gets(name)){
		if(name[0]=='V'){
			int len=strlen(name);
			int num=0;
			int i=2;
			int j=0;
			int p=1;
			for(i=2;i<strlen(name);i++){
				p=1;
				for(j=1;j<=len-i-1;j++){
					p=p*10;
				}
				num=num+p*(name[i]-'0');
			}
			all=num;
		}
		else if(name[0]=='E'){
			nume=0;
			int i=4;
			char x[100];
			int pointer=0;
			int xp=0; //for 
			for(i=4;i<strlen(name)-1;i++){
				if(name[i]==',' && name[i-1]!='>'){
					pointer=1;
					printf("kkk:  %s",x);
					cor[nume][0]=getint(x);
					if(cor[nume][0]<0 || cor[nume][0]>=all){
						printf("Error: wrong point"); 
						continue;
					}
					memset(x,0,strlen(x)*sizeof(char));
					printf("kkk222:  %s",x);
					xp=0;

				}else if(name[i]=='>' && pointer==1){
					pointer=0;
					//printf("%c name[i]     getint(x):%d",name[i],getint(x));
					printf("kkk:  %s",x);
					cor[nume][1]=getint(x);
					if(cor[nume][1]<0 || cor[nume][1]>=all){
						printf("Error: wrong point"); 
						continue;
					}
					nume++;
					memset(x,0,strlen(x)*sizeof(char));
					printf("kkk2222:  %s",x);
					xp=0;
				}else if(name[i]>='0' && name[i]<='9'){
					printf("=====%d:  %c",xp,name[i]);
					x[xp++]=name[i];
				}	
			     else{	
			     	xp=0;
				}
			}
		}else if(name[0]=='s'){
			int i=0;
			int p1=0;
			char s1[100];
			memset(s1,0,strlen(s1)*sizeof(char));
			for(i=2;i<strlen(name);i++){
				if(name[i]>='0' && name[i]<='9'){
					s1[p1++]=name[i];
				}else if(name[i]==' '){
					start=getint(s1);
					p1=0;
					memset(s1,0,strlen(s1)*sizeof(char));
				}
			}
			end=getint(s1);
			struct node *head=NULL;
			struct node s[all];
			find(start,end,cor,nume,s);
			int heapsize=all-1;
			int A[heapsize+1];
			int jj=0;
			int ii=1;
			struct node *st=&s[start];
			int par=start;
			s[start].add=-1;
			while(st->next!=NULL){
				s[st->next->index].key=1;
				s[st->next->index].parent=par;
				s[st->next->index].inheap=-1;
				A[i++]=st->next->index;
				st=st->next;
			}
			buildheap(A,1,ii-1,s);
			int flag=0;
			while(ii!=0){
				int v=getmax(A,1,ii-1,s);
				s[v].add=-1;
				if(s[v].index==end){
					flag=-1;
					break;
				}
				ii--;
				struct node *st2=&s[v];
				int par2=v;
				while(st2->next!=NULL){
					if(s[st2->next->index].inheap!=-1 && s[st2->next->index].add!=-1){//not in heap
						s[st2->next->index].key=s[v].key+1;
						s[st2->next->index].parent=par2;
						//A[ii++]=st2->next->index; //add to the heap
						s[st2->next->index].inheap=-1;
						heapdecrease(A,ii-1,s,st2->next->index);
						ii++;
					}
					else if(s[st2->next->index].add!=-1&&s[v].key+1<s[st2->next->index].key){//in the heap
						s[st2->next->index].key=s[v].key+1;
						s[st2->next->index].parent=par2;
						buildheap(A,1,ii,s);	
					}
				st=st->next;
			}
			}
			if(flag!=-1){
				printf("Error: no path from  %d to %d",start,end);
			}else{
				int path[10000];
				int pi=0;
				path[pi++]=end;
				struct node *st3=&s[end];
				while(st3->parent!=start){
					path[pi++]=s[st3->parent].index;
					st3=st3->parent;
				}
				path[pi++]=start;
				int count=0;
				for(count=pi-1;count>0;count--){
					printf("%d-",path[count]);
				}
				printf("%d\n",start);
			}

		}
		int iii=0;
		for(iii=0;iii<nume;iii++){
			printf("%d,%d\n",cor[iii][0],cor[iii][1]);
		}
	}
	printf("say you\n");
}



void maxheapify(int A[],int i,int size,struct node s[]){
	int l=2*i;
	int r=2*i+1;
	int lowest;
	if(l<=size&& s[A[l]].key<s[A[i]].key){
		lowest=l;
	}else{
		lowest=i;
	}

	if(r<size && s[A[r]].key<s[A[lowest]].key){
		lowest=r;
	}
	if(lowest!=i){
		int temp=A[lowest];
		A[lowest]=A[i];
		A[i]=temp;
		maxheapify(A,lowest,size,s);
	}
}

void buildheap(int A[],int i,int size,struct node s[]){
	int ss=size/2;
	int j=1;
	for(j=ss;j>=1;j--){
		maxheapify(A,j,size,s);
	}
	//return A;
}

int getmax(int A[],int i,int size,struct node s[]){
	int min;
	if(s<=0){
		return -1;
	}else{
		min=A[1];
		A[1]=A[size];
		maxheapify(A,1,size-1,s);
		return min;
	}
}

void heapdecrease(int A[],int size,struct node s[],int new){
	A[size+1]=s[new].index;
	int j=size+1;
	while(j>1 and s[A[j/2]].key>s[A[j]].key){
		int temp=A[j/2];
		A[j/2]=A[j];
		A[j]=temp;
		j=j/2;
	}
}

void heapdchange(int A[],int i,int size,struct node s[]){
	int j=i;
	while(j>1 && s[A[j/2]].key>s[A[j]].key){
		int temp=A[j/2];
		A[j/2]=A[j];
		A[j]=temp;
		j=j/2;
	}
}


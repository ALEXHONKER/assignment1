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
	//printf("str: %s, len:%d\n",s,len2);
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
void find(int start,int end,int cor[1000][2],int nume,struct node s[]){
	int i=0;
	
	/*
	for(i=0;i<all-1;i++){
		s[i].next=&s[i+1];
		s[i].index=i;
	}
	*/
	//s[all-1].next=NULL;
	//s[all-1].index=all-1;
	//printf("find %d,%d,    %d\n",start,end,nume);
	printf("nume%d",nume);
	for(i=0;i<nume;i++){

		//printf("ffff %d,%d\n",cor[i][0],cor[i][1]);
		struct node e1;
		e1.index=cor[i][1];

		//printf("ffff %d\n",cor[i][1]);
		//printf("next%d\n",e1.index);
		e1.next=s[cor[i][0]].next;
		s[cor[i][0]].next=&e1;
		s[cor[i][0]].index=cor[i][0];
		//printf("next2%d\n",e1.index);
		struct node e2;
		e2.index=cor[i][0];
		e2.next=s[cor[i][1]].next;
		s[cor[i][1]].next=&e2;
		s[cor[i][1]].index=cor[i][1];
		printf("edges1: %d--> %d\n",s[cor[i][0]].index,s[cor[i][0]].next->index);
		printf("%dedges2: %d--> %d\n",i,s[cor[i][1]].index,s[cor[i][1]].next->index);
		if(i==nume-1) {
			printf("2444444");
			return ;}
	
	}
   printf("22222223333");

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
	while(j>1 && s[A[j/2]].key>s[A[j]].key){
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


void main(){
	char name[1000];
	int cor[1000][2];
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
			memset(x,0,100*sizeof(char));
			for(i=4;i<strlen(name)-1;i++){
				if(name[i]==',' && name[i-1]!='>'){
					pointer=1;
					//printf("kkk:  %s",x);
					cor[nume][0]=getint(x);
					//printf("c0:%d\n",cor[nume][0]);
					if(cor[nume][0]<0 || cor[nume][0]>=all){
						printf("Error: wrong point\n"); 
						continue;
					}
					memset(x,0,100*sizeof(char));
					//printf("kkk222:  %s",x);
					xp=0;

				}else if(name[i]=='>' && pointer==1){
					pointer=0;
					//printf("%c name[i]     getint(x):%d",name[i],getint(x));
					//printf("kkk2:  %s",x);
					cor[nume][1]=getint(x);
					//printf("c1:%d\n",cor[nume][1]);
					if(cor[nume][1]<0 || cor[nume][1]>=all){
						printf("Error: wrong point\n"); 
						continue;
					}
					nume++;
					memset(x,0,100*sizeof(char));
					//printf("kkk2222:  %s",x);
					xp=0;
				}else if(name[i]>='0' && name[i]<='9'){
					//printf("=====%d:  %c\n",xp,name[i]);
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
			memset(s1,0,100*sizeof(char));
			for(i=2;i<strlen(name);i++){
				if(name[i]>='0' && name[i]<='9'){
					s1[p1++]=name[i];
				}else if(name[i]==' '){
					start=getint(s1);
					p1=0;
					memset(s1,0,100*sizeof(char));
				}
			}
			//printf(":%s\n",s1);
			//printf("%d\n",start);
			end=getint(s1);
			printf("start:%d,end: %d\n",start,end);
			//printf("start2: %d, end2: %d\n",start,end);
			struct node *head=NULL;
			struct node s[all];
			int iiii=0;
			for (iiii=0;iiii<all;iiii++){
				s[iiii].index=iiii;
				//s[iiii].parent=NULL;
				s[iiii].next=NULL;
				s[iiii].add=0;
				s[iiii].key=99999;
				s[iiii].inheap=0;
				//int index;
				//int parent;
				//int key; //a big number
				//int add;
				//int inheap;
			}
			for (iiii=0;iiii<nume;iiii++){
				printf("%d\n",s[cor[iiii][0]].index);
			}
			printf("alll:%d\n",all);
			//find(start,end,cor,nume,s);
			printf("nume:%d\n",nume);
			struct node e1[nume];
			struct node e2[nume];
			for(i=0;i<nume;i++){
				printf("i: %d",i);
				//printf("ffff %d,%d\n",cor[i][0],cor[i][1]);
				//struct node e1;
				//struct node e2;
				//e1=memset(e1,0,sizeof(node);
				e1[i].index=cor[i][1];
				//e2=memset(e2,0,sizeof(node);
				//printf("ffff %d\n",cor[i][1]);
				//printf("next%d\n",e1.index);
				e1[i].next=s[cor[i][0]].next;
				s[cor[i][0]].next=&e1[i];
				s[cor[i][0]].index=cor[i][0];
				//printf("next2%d\n",e1.index);
				e2[i].index=cor[i][0];
				e2[i].next=s[cor[i][1]].next;
				s[cor[i][1]].next=&e2[i];
				s[cor[i][1]].index=cor[i][1];
				printf("%dedges1: %d--> %d\n",i,s[cor[i][0]].index,s[cor[i][0]].next->index);
				printf("%dedges2: %d--> %d\n",i,s[cor[i][1]].index,s[cor[i][1]].next->index);
				if(i==nume-1){
					int ik=0;
					for(ik=0;ik<all;ik++){
						if(s[ik].next!=NULL){
							printf("%d",s[ik].next->index);
						}
					}
				}
			}



			//
			printf("222222222222");
			int heapsize=all-1;
			int A[heapsize+1];
			int jj=0;
			int ii=1;
			printf("222222222222");
			struct node *st=&s[start];
			printf("start: %d",st->index);
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
				int path[1000];
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
		/*
		int iii=0;
		for(iii=0;iii<nume;iii++){
			printf("%d,%d\n",cor[iii][0],cor[iii][1]);
		}
		*/
	}
	printf("say you\n");
}





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
	struct node *next;
    
};

int getint(char *s){
	int i=0;
	int p=1;
	int len2=strlen(s);
	int num=0;
	for(i=0;i<len2;i++){
		p=1;
		int j=0;
		for(j=0;j<len2-i-1;j++){
			p=p*10;
		}
		if(!(s[i]-'0'>=0 && s[i]-'0'<=9)){
			
			return -1;
		}else{
			num=num+p*(s[i]-'0');
		}
		
	}
	return num;
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
	char *name;//char name[1000]
	name = (char *) malloc(2147483646*sizeof(char));
	//int **cor=malloc(100000000*sizeof(int*));
	int cor[99999][2];
	//int icor=0;
	//int cor[1000][2];
    int nume=0;
	int all=0;
	int start;
	int end;
	int index=0;
	while(gets(name)){
		if(name[0]=='V'){
			index=0;
			int len=strlen(name);
			int num=0;
			int i=2;
			int j=0;
			int p=1;
			int fau=0;
			//fprintf(stdout,"LEN:%d===%s",len,name);
			for(i=2;i<strlen(name);i++){
				p=1;
				for(j=1;j<=len-i-1;j++){
					p=p*10;
				}
				if(!(name[i]-'0'>=0 && name[i]-'0'<=9)){
					fprintf(stdout,"Error: wrong V1\n");
					fau=1;
					break; 
				}else{
					num=num+p*(name[i]-'0');
				}
			}
			
			if(num==0&&fau==0){
				fprintf(stdout,"Error: wrong V2\n");
					break;
			}else{
				all=num;
			}
			index=1;
		}
		else if(name[0]=='E'){
			if(index!=1){
				fprintf(stdout,"Error: Wrong input.\n"); 
				continue;
			}
			//fprintf(stdout,"%s\n",name);//////////////////////////////////////////////////////////////////////////////////////////////////////// 
			nume=0;
			int i=4;
			char x[100];
			int pointer=0;
			int xp=0; //for 
			memset(x,0,100*sizeof(char));
			int fault=0;
			memset(cor,0,2*99999*sizeof(int));
			
			// free(cor);
			// cor=malloc(100000000*sizeof(int*));
			
			// for(icor=0;icor<100000000;icor++){
			// 	cor[icor]=malloc(2*sizeof(int));
			// }
			int outof=0;
			for(i=4;i<strlen(name)-1;i++){
				
				if(fault==1) break;
				
				if(name[i]==',' && name[i-1]!='>'){
					//fprintf(stdout,"222222222222\n"); //////////////////////////////////////////////////////////////////////////////////////////// 
					// if(nume>=99999999){
					// cor=realloc(cor,sizeof(int*)*(nume+10));
   		// 			cor[nume]=malloc(2*sizeof(int));
					// }
					pointer=1;
					cor[nume][0]=getint(x);
					if(cor[nume][0]<0 || cor[nume][0]>=all){
						fprintf(stdout,"Error: Wrong point\n"); 
						fault=1;
						break;
					}
					memset(x,0,100*sizeof(char));
					xp=0;
					

				}else if(name[i]=='>' && pointer==1){
					if(nume>=all*all){
						fprintf(stdout, "Error: Wrong input of E\n");
						fault=1;
						break;
					}
					//fprintf(stdout,"23333333\n"); //////////////////////////////////////////////////////////////////////////////////////////// 
					pointer=0;
					cor[nume][1]=getint(x);
					if(cor[nume][1]<0 || cor[nume][1]>=all){
						fprintf(stdout,"Error: Wrong point\n"); 
						fault=1;
						break;
					}
					nume++;
					memset(x,0,100*sizeof(char));
					xp=0;
				}else if(name[i]>='0' && name[i]<='9'){
					x[xp++]=name[i];
				}	
			     else{	
			     	xp=0;
				}
				
			}
			if(fault==1) continue;
			index=2;
		}else if(name[0]=='s'){
			if(index!=2){
				fprintf(stdout, "Error: Wrong input\n");
				continue;
			}
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
			end=getint(s1);
			if(start<0 || start>=all || end<0 || end >=all){
				fprintf(stdout,"Error: Wrong point\n"); 
				continue;
			}
			if(start==end){
				fprintf(stdout,"%d-%d\n", start,end);
				continue;
			}
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
			}
			struct node e1[nume];
			struct node e2[nume];
			for(i=0;i<nume;i++){
				e1[i].index=cor[i][1];
				e1[i].next=s[cor[i][0]].next;
				s[cor[i][0]].next=&e1[i];
				s[cor[i][0]].index=cor[i][0];
				e2[i].index=cor[i][0];
				e2[i].next=s[cor[i][1]].next;
				s[cor[i][1]].next=&e2[i];
				s[cor[i][1]].index=cor[i][1];
			}
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
				A[ii++]=st->next->index;
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
						s[st2->next->index].inheap=-1;
						heapdecrease(A,ii-1,s,st2->next->index);
						ii++;
					}
					else if(s[st2->next->index].add!=-1&&s[v].key+1<s[st2->next->index].key){//in the heap
						s[st2->next->index].key=s[v].key+1;
						s[st2->next->index].parent=par2;
						buildheap(A,1,ii,s);	
					}
					st2=st2->next;
				}
			}
			if(flag!=-1){
				fprintf(stdout,"Error: no path from  %d to %d\n",start,end);
			}else{
				int path[1000];
				int pi=0;
				path[pi++]=end;
				struct node *st3=&s[end];
				int counti=0;
				while(s[st3->parent].index!=start){
					path[pi++]=s[st3->parent].index;
					st3=&s[st3->parent];
				}
				path[pi++]=start;
				int count=0;
				for(count=pi-1;count>0;count--){
					printf("%d-",path[count]);
				}
				printf("%d\n",path[0]);
			}

		}
	 memset(name,0,2147483646*sizeof(char));
	}
}





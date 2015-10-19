#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
struct node{
	int index=-1;
	int parent;
	int key=65555; //a big number
	//struct node *edge = NULL;
	struct node *next = NULL;
    
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
			find(start,end,cor,nume,all);
		}
		int iii=0;
		for(iii=0;iii<nume;iii++){
			printf("%d,%d\n",cor[iii][0],cor[iii][1]);
		}
	}
	printf("say you\n");
}

void find(int start,int end,int cor[10000][2],int nume,int all){
	int i=0;
	struct node *head=NULL;
	struct node s[all];
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
		s[cor[i][0]].next=e1;
		struct node e2;
		e2.index=cor[i][0];
		e2.next=s[cor[i][1]].next;
		s[cor[i][1]].next=e2;
	}


}
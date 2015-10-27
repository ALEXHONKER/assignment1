//
//  main.c
//  assignment2_first
//
//  Created by chuan1900 on 2015-10-20.
//  Copyright © 2015 chuan1900. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define isNum(a)  (a>='0'&& a<='9')
#define MAX 300


/*
 *    to construct a linked queue
 *
 */

//#define Data int
typedef int Data;

//node struct
typedef struct QNode{
    Data data;
    struct QNode *next;
}QNode;

//queue struct
typedef struct Queue{
    QNode *front;
    QNode *rear;
    int size;
}Queue;

//create a new queue
Queue *NewQueue()
{
    Queue *pqueue=(Queue *)malloc(sizeof(Queue));
    if (pqueue!=NULL) {
        pqueue->front=NULL;
        pqueue->rear=NULL;
        pqueue->size=0;
    }
    return pqueue;
}

//queue is empty or not
int Empty(Queue *pqueue)
{
    if (pqueue->size==0)
        return 1;
    else
        return 0;
}

//Enqueue
void Enqueue(Queue *pqueue,Data data)
{
    QNode *P=(QNode *)malloc(sizeof(QNode));
    if (P!=NULL)
    {
        P->data=data;
        P->next=NULL;
        if (Empty(pqueue)) {
            pqueue->front=P;
            pqueue->rear=P;
            pqueue->size++;
        }
        else {
            pqueue->rear->next=P;
            pqueue->rear=P;
            pqueue->size++;
        }
    }
}

//Dequeue
QNode *Dequeue(Queue *pqueue)
{
    QNode *P=pqueue->front;
    if (Empty(pqueue)!=1&&P!=NULL)
    {
        pqueue->front=P->next;
        pqueue->size--;
        free(P);
        //if (pqueue->size==0) {
        //pqueue->rear=NULL;
        //}
    }
    return P;
}


/*
 * to define and creat adjgraph and work out the shortest path using BFS
 */

//mark array
int pa[MAX];
int visited[MAX];
//
typedef struct edgeTable{
    int ivex;
    struct edgeTable *next;
}Enode;

typedef struct Vertex{
    int data;
    Enode *Firstedge;
}Vexnode;

typedef struct AdjGraph{
    int vexnum;
    int edgenum;
    Vexnode vex[MAX];
}AdjGraph;

//to add an Enode to the last of a linklist
void linkLast(Enode *list,Enode *node){
    Enode *p=list;
    while(p->next){
        p=p->next;
    }
    p->next=node;
}

AdjGraph *creatGraph(int v_num, int e_num, int arrEdge[][2]){
    int i,n1,n2;
    Enode *node1,*node2;
    AdjGraph *pG;
    
    if ((pG=(AdjGraph*)malloc(sizeof(AdjGraph))) == NULL )
        return NULL;
    memset(pG, 0, sizeof(AdjGraph));
    
    pG->vexnum=v_num;
    pG->edgenum=e_num;
    
    //to initiate the vetex
    for(i=0;i<pG->vexnum;i++){
        pG->vex[i].data=i;
        pG->vex[i].Firstedge=NULL;
        
    }
    
    for(i=0;i<pG->edgenum;i++){
        n1=arrEdge[i][0];
        n2=arrEdge[i][1];
        
        node1=(Enode*)malloc(sizeof(Enode));
        node1->ivex=n1;
        node2=(Enode*)malloc(sizeof(Enode));
        node2->ivex=n2;
        if(pG->vex[n2].Firstedge==NULL){
            pG->vex[n2].Firstedge=node1;
        }
        else{
            linkLast(pG->vex[n2].Firstedge, node1);
        }
        
        if(pG->vex[n1].Firstedge==NULL){
            pG->vex[n1].Firstedge=node2;
        }
        else{
            linkLast(pG->vex[n1].Firstedge, node2);
        }
        
        
    }
    return pG;
    
}

void print_adjGraph(AdjGraph G){
    int i;
    Enode *node;
    
    printf("Adj Graph:\n");
    for(i=0;i<G.vexnum;i++){
        printf("%d",G.vex[i].data);
        node=G.vex[i].Firstedge;
        while(node!=NULL){
            printf("%d",node->ivex);
            node=node->next;
        }
        printf("\n");
    }
}

//shortest path using BFS
void shortestPath(AdjGraph G,int s,int d){
    //Queue *q;
    Enode *p=NULL;
    int parents=s;
    memset(visited,0,sizeof(visited));
    memset(pa,-1,MAX*sizeof(int));
    visited[s]=1;
    pa[s]=-1;
    Queue *q=NewQueue();
    Enqueue(q,s);
    
    while(Empty(q)==0){
        p=G.vex[q->front->data].Firstedge;
        parents=q->front->data;
        Dequeue(q);
        
        while(p!=NULL){
            if(!visited[p->ivex])
            {
                visited[p->ivex]=1;
                pa[p->ivex]=parents;
                if(p->ivex==d){
                    //have found the target point:d
                    break;
                }
                Enqueue(q, p->ivex);
            }
            p=p->next;
        }
    }
    //printf("the shortest path is:");
    parents=d;
    if (pa[parents]==-1&&s!=d) {
        printf("Error: no path between the two points.");
    }
    else if(s==d){
        printf("%d-%d",s,s);
    }
    //to print the shortest path in array pa[]
    else{
        int tempPa[10];
        int index=0,i;
        tempPa[index]=parents;
        index++;
        while(pa[parents]!=-1){
            //printf("%d-",parents);
            parents=pa[parents];
            tempPa[index]=parents;
            //printf("temp:%d",tempPa[index]);
            index++;
        }
        //printf("%d\n",parents);
        
        for(i=index-1;i>=0;i--){
            if(i>0){
                printf("%d-",tempPa[i]);
            }
            else printf("%d\n",tempPa[i]);
        }
    }
    
}



int main() {
    //to judge whether input V or E is correct
    int flag=0;
    
    int read;
    size_t len=100;
    char *s=NULL;
    if((s=malloc((len+1)))==NULL){
        printf("Can't get memory\n");
        exit(-1);
    }
    
    while((read=getline(&s,&len,stdin))!=-1){
        int v_num,e_num;
        AdjGraph* pG;
        
        char*p;
        int x[300];
        int temp1[100][2];
        int count1=0;
        int i=0;
        //to extract numbers from string
        for (p = s; *(p+1) != '\0' ; p++ )
        {
            if ((*p <= '0'|| *p >= '9') && (*(p+1) <='9' && *(p+1) >= '0'))
            {
                sscanf(p+1,"%d",(x+i));
                i++;
            }
        }
        
        if(s[0]=='V'){
            
            pG=NULL; //to creat a new adj graph
            
            v_num=x[0];
            if(v_num==0){
                printf("Error:v number is invalid.\n");
                flag=0;
                continue;
            }
            else flag=1;
            //printf("v_num:%d\n",v_num);
        }
        else if(s[0]=='E'&& flag==1){
            
            int j=0;
            for (; j < i; j++){
                //printf("%d-%d\n",j,x[j]);
                temp1[count1][0]=x[j];
                temp1[count1][1]=x[j+1];
                
                if(temp1[count1][0]>v_num||temp1[count1][1]>v_num){
                    printf("Error: Vextex does not exist.\n");
                    flag=0;
                    break;
                }
                
                count1++;
                j=j+1;
            }
            if(flag==0){
                continue;
            }
            e_num=j/2;
            //printf("e_num:%d\n",e_num);
        }
        
        else if(s[0]=='s'){
            int s_v,d_v;
            s_v=x[0];
            d_v=x[1];
            if(s_v>v_num||d_v>v_num){
                printf("Error: Vetex does not exist.");
                continue;
            }
            else{
                //printf("s:%d, d:%d\n",s_v,d_v);
                pG=creatGraph(v_num, e_num,temp1);
                //print_adjGraph(*pG);
                shortestPath(*pG,s_v,d_v);
            }
            
        }
        
    }
    free(s);
    return 0;
    
}
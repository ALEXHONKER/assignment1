#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define MAXLENGTH 5000000
struct node{
	int index;  //unique index of the node
	int parent; //parent of the node
	int key;    //a big number
	struct node *child;
	struct node *next; //next node
};

int getint(char *s){
	int i = 0;
	int p = 1;
	int len2 = strlen(s);
	int num = 0;
	for (i = 0; i<len2; i++){
		p = 1;
		int j = 0;
		for (j = 0; j<len2 - i - 1; j++){
			p = p * 10;
		}
		if (!(s[i] - '0' >= 0 && s[i] - '0' <= 9)){
			return -1;
		}
		else{
			num = num + p*(s[i] - '0');
		}

	}
	return num;
}

struct node* findindex(struct node *f, int index){
	while (f != NULL){
		if (f->index == index) return f;
		f = f->next;
	}
	return NULL;
}

struct node* findchild(struct node *f, int index){
	while (f != NULL){
		if (f->index == index) return f;
		f = f->child;
	}
	return NULL;
}

void main(){
	char *name=NULL;
	unsigned long maxl=MAXLENGTH;
	name = (char *)malloc(maxl * sizeof(char));
	int **cor;
	cor=malloc(1 * sizeof(int*));
	int nume = 0;
	int all = 0;
	int start;
	int end;
	int index = 0;
	int alloc = 0;
	struct node *first=NULL;
	while (getline(&name,&maxl,stdin)!=EOF){
		name[strlen(name)-1]='\0';
		if (name[0] == 'V'){
			if(first!=NULL){
				free(first);
				first=NULL;
			}
			index = 0;
			int len = strlen(name);
			int num = 0;
			int i = 2;
			int j = 0;
			int p = 1;
			int fau = 0;
			for (i = 2; i<strlen(name); i++){
				p = 1;
				for (j=1;j<=len-i-1;j++){
					p = p * 10;
				}
				if (!(name[i] - '0' >= 0 && name[i] - '0' <= 9)){
					fprintf(stdout, "Error: wrong V\n");
					fau = 1;
					break;
				}
				else{
					num = num + p*(name[i] - '0');
				}
			}

			if (num == 0 && fau == 0){
				fprintf(stdout, "Error: wrong V\n");
				continue;
			}
			else{
				all = num;
			}
			index = 1;
		}
		else if (name[0] == 'E'){
			alloc = 0;
			if (cor != NULL){
				free(cor);
			}
			cor = malloc(1 * sizeof(int*));
			if (index != 1){
				fprintf(stdout, "Error: Wrong input.\n");
				continue;
			}
			nume = 0;
			int i = 4;
			char x[100];
			int pointer = 0;
			int xp = 0;
			memset(x, 0, 100 * sizeof(char));
			int fault = 0;
			int outof = 0;
			for (i = 4; i<strlen(name) - 1; i++){
				if (fault == 1) break;

				if (name[i] == ',' && name[i - 1] != '>'){
					pointer = 1;
					cor = realloc(cor, (alloc + 1)*sizeof(int*));
					cor[alloc++] = malloc(2 * sizeof(int));
					cor[nume][0] = getint(x);
					if (cor[nume][0]<0 || cor[nume][0] >= all){
						fprintf(stdout, "Error: Wrong point\n");
						fault = 1;
						break;
					}
					memset(x, 0, 100 * sizeof(char));
					xp = 0;


				}
				else if (name[i] == '>' && pointer == 1){
					long long mul = (long)all*(long)all;
					if (nume >= mul){
						fprintf(stdout, "Error: Wrong input of E\n");
						fault = 1;
						break;
					}
					pointer = 0;
					cor[nume][1] = getint(x);
					if (cor[nume][1]<0 || cor[nume][1] >= all){
						fprintf(stdout, "Error: Wrong point\n");
						fault = 1;
						break;
					}
					struct node *anode = malloc(sizeof(struct node));
					anode->index = cor[nume][0];
					anode->key = 999999;
					anode->next = NULL;
					anode->child = NULL;
					struct node *tf = first;
					int same = 0;
					if (tf == NULL){
						first = anode;
						struct node *sc = malloc(sizeof(struct node));
						sc->next = NULL;
						sc->child = NULL;
						sc->index = cor[nume][1];
						sc->key = 999999;
						first->next =sc;
						same = 1;
					}
					else{
						while (tf != NULL){
							if (tf->index == anode->index){
								struct node *s2 = findindex(tf->next, cor[nume][1]);
								if (s2 == NULL){
									struct node *ss2 = malloc(sizeof(struct node));
									ss2->next = NULL;
									ss2->child = NULL;
									ss2->key = 999999;
									ss2->index = cor[nume][1];
									ss2->next = tf->next;
									tf->next = ss2;
								}
								same = 1;
								break;
							}
							else{
								tf = tf->child;
							}
						}
					}
					if (same == 0){
						anode->child = first;
						first = anode;
						struct node *s3 = malloc(sizeof(struct node));
						s3->next = NULL;
						s3->child = NULL;
						s3->key = 999999;
						s3->index = cor[nume][1];
						first->next = s3;
					}


					struct node *anode2=malloc(sizeof(struct node));
					anode2->index = cor[nume][1];
					anode2->key = 999999;
					anode2->child = NULL;
					anode2->next = NULL;
					struct node *tf2 = first;
					int same2 = 0;
					while (tf2 != NULL){
						if (tf2->index == anode2->index){
							struct node *s4 = findindex(tf2->next, cor[nume][0]);
							if (s4 == NULL){
								struct node *ss4 = malloc(sizeof(struct node));
								ss4->next = NULL;
								ss4->child = NULL;
								ss4->key = 999999;
								ss4->index = cor[nume][0];
								ss4->next = tf2->next;
								tf2->next = ss4;
							}
								same2 = 1;
								break;
							}
						else{
							tf2 = tf2->child;
						}
					}
					if (same2 == 0){
						anode2->child = first;
						first = anode2;
						struct node *s5 = malloc(sizeof(struct node));
						s5->child = NULL;
						s5->next= NULL;
						s5->key = 999999;
						s5->index = cor[nume][0];
						first->next = s5;
					}
					nume++;
					memset(x, 0, 100 * sizeof(char));
					xp = 0;
				}
				else if (name[i] >= '0' && name[i] <= '9'){
					x[xp++] = name[i];
				}
				else if(name[i]=='-'){
					fprintf(stdout, "Error: Wrong point\n");
					fault = 1;
					break;	
				}
				else{
					xp = 0;
				}

			}
			if (fault == 1) continue;
			index = 2;
			
		}
		else if (name[0] == 's'){
			if (index != 2){
				fprintf(stdout, "Error: Wrong input\n");
				continue;
			}
			int i = 0;
			int p1 = 0;
			char s1[100];
			memset(s1, 0, 100 * sizeof(char));
			int special=0;
			for (i = 2; i<strlen(name); i++){
				if (name[i] >= '0' && name[i] <= '9'){
					s1[p1++] = name[i];
				}
				else if (name[i] == ' '){
					start = getint(s1);
					p1 = 0;
					memset(s1, 0, 100 * sizeof(char));
				}else{
					special=1;
				}
			}
			end = getint(s1);
			if (start<0 || start >= all || end<0 || end >= all || special==1){
				fprintf(stdout, "Error: Wrong point\n");
				continue;
			}
			if (start == end){
				fprintf(stdout, "%d-%d\n", start, end);
				continue;
			}
			struct node *st = first;
			st = findchild(st, start);
			st->key = 0;
			struct node *head = first;
			struct node *hnext = first;
			struct node *h = first;
			while (head != NULL){
				while (h!= NULL){
					hnext = h;
					while (hnext->next!= NULL){
						struct node *fd = findchild(first, hnext->next->index);
						if (fd->key>(h->key + 1)){
							fd->key = h->key + 1;
							fd->parent = h->index;
						}
						hnext = hnext->next;
					}
					h = h->child;
				}
				h = first;
				head = head->child;
			}
			struct node *pa = findchild(first, end);
			struct node *sa = findchild(first, start);
			if ( pa==NULL || sa ==NULL||pa->key >= 999999){
				fprintf(stdout, "Error: no path from  %d to %d\n", start, end);
				continue;
			}
			else{
				int path[100000];
				int pi = 0;
				path[pi++] = end;
				struct node *st3 = pa;
				int counti = 0;
				while (pa->parent != start){
					path[pi++] = pa->parent;
					pa = findchild(first, pa->parent);
				}
				path[pi++] = start;
				int count = 0;
				for (count = pi - 1; count>0; count--){
					fprintf(stdout, "%d-", path[count]);
				}
				fprintf(stdout, "%d\n", path[0]);
			}
			struct node *head2=first;
			struct node *next2=first;
			while(head2!=NULL){
				next2=head2;
				while(next2!=NULL){
					next2->key=999999;
					next2=next2->next;
				}
				head2=head2->child;
			}
		}
		memset(name, 0, maxl * sizeof(char));
	}
}



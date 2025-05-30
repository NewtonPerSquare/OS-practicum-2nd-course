#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <string.h>
#include <time.h>

struct Tree{
    int n;
    struct Tree* L;
    struct Tree* R;
};

void deleteT(struct Tree* T){
    if (T->L != NULL){
        deleteT(T->L);
    }
    if (T->R != NULL){
        deleteT(T->R);
    }
    free(T);
    return;
}

struct Tree* read_Tree(){
    struct Tree* T1 = NULL;
    struct Tree* T2 = NULL;
    int c;
    while (scanf("%d", &c) != EOF){
        struct Tree* Tb = calloc(1, sizeof(struct Tree));
        Tb->n = c;
        Tb->L = NULL;
        Tb->R = NULL;
        if (T1 == NULL){
            T1 = Tb;
        }
        else{
            T2 = T1;
            while (1){
                if ((c < T2->n) && (T2->L != NULL)){
                    T2 = T2->L;
                }
                else if ((c > T2->n) && (T2->R != NULL)){
                    T2 = T2->R;
                }
                else{
                    break;
                }
            }
            if (c < T2->n){
                T2->L = Tb;
            }
            else if (c > T2->n){
                T2->R = Tb;
            }
            else{
                free(Tb);
            }
        }
    }
    return T1;
}

int min(int a, int b){
    if (a >= b){
        return b;
    }
    else{
        return a;
    }
}

char max(int a, int b){
    if (a >= b){
        return a;
    }
    else{
        return b;
    }
}

void print_Tree(struct Tree* p, int height){
    if (p != NULL){
        print_Tree(p->R, height + 1);
        for (int i = 0; i < height; i++){
            printf("    ");
        }
        printf("%d\n", p->n);
        print_Tree(p->L, height + 1);
    }
}

int find_in_Tree(struct Tree* T, int F, int height){
    int a = -1;
    int b = -1;
    if (F == T->n){
        return height;
    }
    if ((F < T->n) && (T->L != NULL)){
        a = find_in_Tree(T->L, F, height + 1);
    }
    else if ((F > T->n) && (T->R != NULL)){
        b = find_in_Tree(T->R, F, height + 1);
    }
    else{
        return -1;
    }
    if (a==-1){
        return b;
    }
    if (b==-1){
        return a;
    }
    return min(a,b);
}
///////////////

struct Tree* DeleteNode(struct Tree* node, int val){
    if(node == NULL)        //nothing to delete
    {
        return node;
    }
    if(val == node->n)      //found the node
    {
        struct Tree* tmp;
        if(node->R == NULL) //no right subtree
        {
            tmp = node->L;
        }
        else
        {
            struct Tree* ptr = node->R;
            if(ptr->L == NULL) // good exception
            {
                ptr->L = node->L;
                tmp = ptr;
            }
            else //common case
            {
                struct Tree* pmin = ptr->L;
                while(pmin->L != NULL){ //reassemble the tree - get the leftmost node of right subtree instead of node
                    ptr = pmin;
                    pmin = ptr->L;
                }
                ptr->L = pmin->R;
                pmin->L = node->L;
                pmin->R = node->R;
                tmp = pmin;
            }
        }
        free(node);
        return tmp;
    }
    else if(val < node->n) //searching the node
    {
        node->L = DeleteNode(node->L, val);
    }
    else
    {
        node->R = DeleteNode(node->R, val);
    }
    return node;
}

char tree_h(struct Tree* T){ //tree height
    if(T == NULL)
    {
        return 0;
    }
    else
    {
        return (char) (1 + max(tree_h(T->L), tree_h(T->R)));
    }
    
}

struct Tree* rotateright(struct Tree* p){//right turn (I don't remember them, copied from Internet :D)
	struct Tree* q = p->L;
	p->L = q->R;
	q->R = p;
	return q;
}

struct Tree* rotateleft(struct Tree* q){    //left turn
	struct Tree* p = q->R;
	q->R = p->L;
	p->L = q;
	return p;
}

int h_delta(struct Tree* p){                //difference of subtrees height
	return tree_h(p->R)-tree_h(p->L);
}

struct Tree* balance(struct Tree* p){        //took from internet, corrected for the task
    if(p->L != NULL)
    {
        p->L = balance(p->L); 
    }
    if(p->R != NULL)
    {
        p->R = balance(p->R);
    }
	if (h_delta(p)>=1) 
	{
		if(h_delta(p->R)<0)
			p->R = rotateright(p->R);       //RL
        p = rotateleft(p);                  //L
		return p;
	}
	if (h_delta(p)<=-1)         
	{
		if(h_delta(p->L)>0)
			p->L = rotateleft(p->L);        //LR
        p = rotateright(p);                 //R
		return p;
	}
	return p;                               //it was alrerady balanced
}

char balanced(struct Tree* p){           //check if tree is balanced
    if (p == NULL)
        return 0;
    int d = h_delta(p); 
    if ((d >= 2) || (d <= -2))
        return 1;
    return balanced(p->L) || balanced(p->R);
}

struct Tree* T_balance(struct Tree* p)  //balancing tree
{
    while(balanced(p) == 1)
    {
        p = balance(p);
    }
    return p;
}
////////

int main(void){
    ////////1-5 were done on lesson
    struct Tree* T1 = NULL;
    printf("Input tree elements: ");
    T1 = read_Tree();
    printf("\n----------------\n");
    print_Tree(T1, 0);
    printf("----------------\n");
    clearerr(stdin);
    printf("Input element to find and delete: ");
    int c;
    scanf("%d", &c);
    printf("\nPath length = %d\n", find_in_Tree(T1, c, 0));
    printf("----------------\n");
    printf("Tree without node:\n");
    ////////
    T1 = DeleteNode(T1, c);     //deleting a number user inputed
    print_Tree(T1, 0);
    printf("----------------\n");
    printf("Balanced tree:\n");
    T1 = T_balance(T1);         //balancing tree
    print_Tree(T1, 0);
    printf("----------------\n");
    deleteT(T1);
    return 0;
}
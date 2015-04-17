#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree_t{
	char el;
	int num;
	struct tree_t *right;
	struct tree_t *left;
}tree;

int ins;

void add_node(tree *t,char c,int num){
	if(t->el == 'N')
		return;
	if(t->left == NULL && !ins){
		tree *nt = (tree *) malloc(sizeof(tree));
		if(num == -1) 
			nt->el = c;
		else{
			nt->el = c;
			nt->num = num;
		}
		nt->right = NULL;
		nt->left = NULL;
		t->left = nt;
		ins = 1;
	}	
	else if (!ins){
		add_node(t->left,c,num);
	}
	if(t->right == NULL && !ins){
		tree *nt = (tree *) malloc (sizeof(tree));
		if(num == -1)
			nt->el = c;
		else
			nt->num = num;
		nt->el = c;
		nt->right = NULL;
		nt->left = NULL;
		t->right = nt;
		ins = 1;
	}	
	else if(!ins){
		add_node(t->right,c,num);
	}
		
};
void create_tree(tree *t,char *input){
	int i;
	t->el = input[0];
	for(i = 1;i < strlen(input);i++){
		if(input[i] != ' ' && input[i] != '\n'){
			if(i == 0){
				if(input[i] < '1' || input[i]>'9')
					add_node(t,input[i],-1);
				else
					add_node(t,'N',atoi(&input[i]));
			}
			else if(input[i-1] == ' '){	
				  if(input[i] < '1' || input[i]>'9')
                                          add_node(t,input[i],-1);
                                  else
                                          add_node(t,'N',atoi(&input[i]));
			}

			ins = 0;
		}
	}
};
void print(tree *t){
	if(t->el != 'N')
		printf("%c\n",t->el);
	else
		printf("%d\n",t->num);
	if(t->left == NULL || t->right == NULL)
		return;
	if(t->left != NULL)
		print(t->left);
	if(t->right != NULL)
		print(t->right);
};
int eval_op(int n1,int n2,char op){
	switch(op){
		case '+': 
			return n1 + n2;
		case '*':
			return n1 * n2;
		case '/':
			return n1 / n2;
	}
};
int eval_exp(tree *t){
	int num1 = 0;int num2=0;
	if(t->left != NULL)
		num1 = eval_exp(t->left);
	if(t->right != NULL)
		num2 = eval_exp(t->right);
	if(t->el != 'N')
		return eval_op(num1,num2,t->el);
	else
		return t->num;
};

int main(int argc,const char *argv[]){
	FILE *file = fopen(argv[1],"r");
	char line[1024];
	tree root;
	root.right = NULL;
	root.left = NULL;
	while(fgets(line,1024,file)){
		create_tree(&root,line);
//		print(&root);
		printf("%d\n",eval_exp(&root));
		root.left = NULL;
		root.right = NULL;	
	}	
	return 0;
}

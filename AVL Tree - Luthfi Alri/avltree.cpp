#include <limits.h>
#include <malloc.h>
#include "avlTree.h"

void avlCreate(avlTree *x){
	(*x).root=NULL;
}

avlAddr avlCNode(avlType X){
	avlAddr newNode;
	newNode=(avlAddr) malloc(sizeof(ElmtTree));
	if (newNode != NULL){
		newNode->left=NULL;
		newNode->info=X;
		newNode->right=NULL;
	}
	return newNode;
}

void avlInsert(avlAddr *root, avlType X){
	
	avlAddr newNode, temp;
	
	newNode=avlCNode(X);
	if (newNode !=NULL){ //Jika penciptaan node baru berhasil
		if (*root==NULL){ //JIka belum terdapat root
			*root=newNode;
		}else{
			if (X < (*root)->info) 
        		avlInsert(&(*root)->left, X); 
    		else if (X >= (*root)->info) 
        		avlInsert(&(*root)->right, X);
		}
		avlBalance(&(*root),X);
	}
}

void avlBalance(avlAddr *root, avlType X){
	int balance = getBalance(*root);
		
		// Left Left Case 
	if (balance > 1 && X < (*root)->left->info) 
    	*root = rightRotate(*root); 
  
	    // Right Right Case 
	if (balance < -1 && X > (*root)->right->info) 
		*root = leftRotate(*root); 
	  
	    // Left Right Case 
	if (balance > 1 && X > (*root)->left->info){ 
	    (*root)->left =  leftRotate((*root)->left); 
	    *root = rightRotate(*root); 
	} 
	  
	    // Right Left Case 
	if (balance < -1 && X < (*root)->right->info){ 
	    (*root)->right = rightRotate((*root)->right); 
        *root = leftRotate(*root); 
    } 
}

void bInsert(avlAddr *root, avlType X){
	
	avlAddr newNode, temp;
	
	newNode=avlCNode(X);
	if (newNode !=NULL){ //Jika penciptaan node baru berhasil
		if (*root==NULL){ //JIka belum terdapat root
			*root=newNode;
		}else{
			if (X < (*root)->info) 
        		bInsert(&(*root)->left, X); 
    		else if (X >= (*root)->info) 
        		bInsert(&(*root)->right, X);
		}
	}
}

avlAddr avlSearch(avlAddr root, avlType src){
	avlAddr nSrc;
	if (root!=NULL){
		if (root->info==src)
			return root;
		else{
			(src > root->info) ? avlSearch(root->right,src) : avlSearch(root->left,src);
		}
	}
	else{
		return NULL;
	}
}

void deleteTree(avlAddr *node){
    if ((*node) == NULL) return; 
	
	deleteTree(&(*node)->left); 
    deleteTree(&(*node)->right); 
    
    printf("\n DeletavlIng node: %d", (*node)->info); 
    free((*node)); 
}

avlAddr minValueNode(avlAddr node) { 
    avlAddr current = node; 
  
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL) 
        current = current->left; 
  
    return current; 
} 

avlAddr avlDelete(avlAddr root, int X){
    // base case 
    if (root == NULL) return root; 
  
    // If the key to be deleted is smaller than the root's key, 
    // then it lies in left subtree 
    if (X < root->info) {
        root->left = avlDelete(root->left, X);
    	avlBalance(&root, X);
	} 
  
    // If the key to be deleted is greater than the root's key, 
    // then it lies in right subtree 
    else if (X > root->info) {
        root->right = avlDelete(root->right, X); 
    	avlBalance(&root, X);
	}
  
    // if key is same as root's key, then This is the node 
    // to be deleted 
    else
    { 
        // node with only one child or no child 
        if (root->left == NULL) 
        { 
            avlAddr temp = root->right; 
            free(root); 
            return temp; 
        } 
        else if (root->right == NULL) 
        { 
            avlAddr temp = root->left; 
            free(root); 
            return temp; 
        } 
  
        // node with two children: Get the inorder successor (smallest 
        // in the right subtree) 
        avlAddr temp = minValueNode(root->right); 
  
        // Copy the inorder successor's content to this node 
        root->info = temp->info; 
  
        // Delete the inorder successor 
        root->right = avlDelete(root->right, temp->info); 
        avlBalance(&root, temp->info);
    } 
    return root; 
}

int avlDepth(avlAddr root)
{
	int y=0,z=0;

	if(root==NULL)
		return -1;
	y=avlDepth(root->left);
	z=avlDepth(root->right);
	if (y > z)
		return (y+1);
	else
		return (z+1);
}

int getBalance(avlAddr root) 
{ 
    if (root == NULL) 
        return 0; 
    return avlHeight(root->left) - avlHeight(root->right); 
} 

int max(int a, int b) 
{ 
  return (a >= b)? a: b; 
} 

int avlHeight(avlAddr root) 
{ 
    if (root == NULL)
        return 0; 
    return 1 + max(avlHeight(root->left), avlHeight(root->right));
} 

/*------------------ ROTATE Tree ------------------ */

avlAddr rightRotate(avlAddr root) 
{ 
    avlAddr x = root->left; 
    avlAddr y = x->right; 
  
    // Perform rotation 
    x->right = root; 
    root->left = y; 
  
    // Return new root 
    return x; 
} 

avlAddr leftRotate(avlAddr root) 
{ 
    avlAddr x = root->right; 
    avlAddr y = x->left; 
  
    // Perform rotation 
    x->left = root; 
    root->right = y; 
  
    // Return new root 
    return x; 
} 

/* ---------------- TRAVERSAL Tree ---------------- */
void avlPost(avlAddr root){
	if (root!=NULL){
		avlPost(root->left);
		avlPost(root->right);
		printf("%d ", root->info);
	}
}

void avlPre(avlAddr root){
	if (root!=NULL){
		printf("%d ", root->info);
		avlPre(root->left);
		avlPre(root->right);
	}
}

void avlIn(avlAddr root){
	if (root!=NULL){
		avlIn(root->left);
		printf("%d ", root->info);
		avlIn(root->right);
	}
}

void avlLevelOrder(avlAddr root,int curLevel, int desLevel)
{
	if(root!=NULL)
	{
		if(curLevel==desLevel)
			printf("%d  ",root->info);
		avlLevelOrder(root->left,curLevel+1,desLevel);
		avlLevelOrder(root->right,curLevel,desLevel);
	}
}

void avlPrint(avlAddr node, char tab[], char type){
	char tempTab[255];
	strcpy(tempTab, tab);
	strcat(tempTab, "\t");
	if (node!=NULL){
		if (type == '0')
			printf("%s`[ROOT]--[%d]\n",tab,node->info);
		else if (type == 'L')
			printf("%s`[L]--[%d]\n",tab,node->info);
		else
			printf("%s`[R]--[%d]\n",tab,node->info);
		avlPrint(node->left,tempTab,'L');
		avlPrint(node->right,tempTab,'R');
	}
}

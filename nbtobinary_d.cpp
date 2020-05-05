#include "nbtobinary_d.h"

/////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// Non Binary ke Binary //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////


void nbToBinary (bAddr *dest, nbAddr src) {
	if (src!=NULL){
		*dest=bCNode(src->info);
		nbToBinary(&(*dest)->left,src->fs);
		nbToBinary(&(*dest)->right,src->nb);
	}
}

void bToBalance (bAddr *dest, nbAddr src) {
	if (src!=NULL){
		*dest=bCNode(src->info);
		bToBalance(&(*dest)->left,src->fs);
		bToBalance(&(*dest)->right,src->nb);
		fixBalance (&(*dest));
	}
}

void fixBalance (bAddr *dest) {
	if (*dest!=NULL){
		bBalance(&(*dest),(*dest)->info);
		fixBalance(&(*dest)->left);
		fixBalance(&(*dest)->right);
	}
}

void bBalance(bAddr *root, infType X){
	int balance = getBalance(*root);
		
		// Left Left Case 
	if (balance > 1) 
    	*root = rightRotate(*root); 
  
	    // Right Right Case 
	if (balance < -1) 
		*root = leftRotate(*root); 
}

int getBalance(bAddr root) { 
    if (root == NULL) 
        return 0; 
    return bHeight(root->left) - bHeight(root->right); 
} 

int max(int a, int b) { 
  return (a >= b)? a: b; 
} 

int bHeight(bAddr root) { 
    if (root == NULL)
        return 0; 
    return 1 + max(bHeight(root->left), bHeight(root->right));
} 

/*------------------ ROTATE Tree ------------------ */

bAddr rightRotate(bAddr root) 
{ 
    bAddr x = root->left; 
    bAddr y = x->right; 
  
    // Perform rotation 
    x->right = root; 
    root->left = y; 
  
    // Return new root 
    return x; 
} 

bAddr leftRotate(bAddr root) 
{ 
    bAddr x = root->right; 
    bAddr y = x->left; 
  
    // Perform rotation 
    x->left = root; 
    root->right = y; 
  
    // Return new root 
    return x; 
} 

/////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// MODUL NON BINARY TREE //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

/* -------------------------------- Konstruktor Tree --------------------------------- */

void nbCreate(nbTree *x){
	(*x).root=NULL;
}

/* ----------------------------- Alokasi node baru Tree ------------------------------ */

nbAddr nbCNode(infType X){
	nbAddr newNode;
	newNode=(nbAddr) malloc(sizeof(nbElmtTree));
	if (newNode != NULL){
		newNode->fs=NULL;
		newNode->info=X;
		newNode->nb=NULL;
		newNode->parent=NULL;
	}
	return newNode;
}

/* ------------------------------ Operasi-operasi Tree ------------------------------- */

void nbInsert(nbTree *tRoot, nbAddr parent, infType X){
	
	nbAddr newNode, temp;
	
	newNode=nbCNode(X);
	if (newNode !=NULL){ 
		if (parent==NULL) 
			tRoot->root=newNode;
		else{
			temp=parent;
			if (temp->fs != NULL){
				temp=temp->fs;
				while(temp->nb!=NULL)
					temp=temp->nb;
				temp->nb=newNode;
			}else
				temp->fs=newNode;
			newNode->parent=parent;
		}
	}
}

nbAddr nbSearch(nbAddr root, infType src){
	nbAddr nSrc;
	if (root!=NULL){
		if (root->info==src)
			return root;
		else{
			nSrc=nbSearch(root->fs,src);
			if (nSrc==NULL)
				return nbSearch(root->nb,src);
			else
				return nSrc;
		}
	}
	else{
		return NULL;
	}
}

void nbUpgrade(nbAddr *root){
	nbAddr temp;
	temp=(*root)->nb;
	if ((*root)->fs==NULL)
		(*root)->fs=temp;
	while(temp!=NULL){
		temp->parent=*root;
		temp=temp->nb;
	}
}

// Menghapus node tertentu dan digantikan oleh fs dari node tsb
void nbDelete(nbAddr *pDel, nbAddr pCur, nbTree *pTree){
	if (pCur != NULL) {
		if (pCur==pTree->root && pCur->fs==NULL){
			pTree->root=NULL;
			return;
		}
		
		if (pCur->fs != NULL)
			nbDelete(&(*pDel), pCur->fs, &(*pTree));
		else{
			nbAddr temp=pCur->parent;
			
			if(temp->fs==pCur){
				temp->fs=pCur->nb;
			}
			else{
				temp=temp->fs;
				while(temp->nb != NULL ){
					if(temp->nb==pCur){
						temp->nb = temp->nb->nb;
						
					}
					else{
						temp=temp->nb;
					}
				}
			}
			free(pCur);
			return;
		}
		
		if (pCur!=*pDel){
			nbUpgrade(&pCur);
			if (pCur->nb != pCur->parent->nb){
				pCur->nb=pCur->parent->nb;
			}
		}else{
			nbUpgrade(&pCur);
			if (pCur->parent!=NULL){
				if (pCur->parent->fs == pCur)
					pCur->parent->fs=pCur->fs;
				else{
					nbAddr Temp = pCur->parent->fs;
					while (Temp->nb->nb != NULL){
						Temp = Temp->nb;
					}
					Temp->nb = pCur->fs;
				}
			}
			if (pCur->fs!=NULL){
				pCur->fs->parent=pCur->parent;
			}
			if (pCur->parent==NULL){
				pTree->root=pCur->fs;
				pCur->fs=NULL;
			}
			
			free(pCur);
		}
	}
}

int nbDepth(nbAddr root)
{
	int y=0,z=0;

	if(root==NULL) {
		return -1;
	}else {
		y=nbDepth(root->fs);
		z=nbDepth(root->nb);
		
		if (root->parent == NULL || root->parent->fs == root) {
			if (y > z)
				return (y+1);
			else
				return (z+1);		
		}else {
			if (y > z)
				return (y);
			else
				return (z);	
		}
	}
}


/* --------------------------------- Traversal Tree ---------------------------------- */

// Postorder traversing
void nbPost(nbAddr root){
	if (root!=NULL){
		nbPost(root->fs);
		nbPost(root->nb);
		printf("%c ", root->info);
	}
}

// Preorder traversing
void nbPre(nbAddr root){
	if (root!=NULL){
		printf("%c ", root->info);
		nbPre(root->fs);
		nbPre(root->nb);
	}
} 

// Inorder traversing
void nbIn(nbAddr root){
 	if (root!=NULL){
		nbPost(root->fs);
		printf("%c ", root->info);
		nbPost(root->nb);
	}
} 

// Levelorder traversing
void nbLevelOrder(nbAddr root,int curLevel, int desLevel){
	if(root!=NULL)
	{
		if(curLevel==desLevel)
			printf("%c ",root->info);
		nbLevelOrder(root->fs,curLevel+1,desLevel);
		nbLevelOrder(root->nb,curLevel,desLevel);
	}
}


/* ----------------------------------- Print TREE ------------------------------------ */

void nbPrint(nbAddr node, char tab[], char type[]){
	char tempTab[255];
	strcpy(tempTab, tab);
	strcat(tempTab, "\t");
	if (node!=NULL){
		printf("%s`[%s]--[%c]\n",tab,type,node->info);
		nbPrint(node->fs,tempTab,"FS");
		nbPrint(node->nb,tab,"NB");
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// MODUL BINARY TREE ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

/* -------------------------------- Konstruktor Tree --------------------------------- */

void bCreate(bTree *x){
	(*x).root=NULL;
}

/* ----------------------------- Alokasi node baru Tree ------------------------------ */

bAddr bCNode(infType X){
	bAddr newNode;
	newNode=(bAddr) malloc(sizeof(bElmtTree));
	if (newNode != NULL){
		newNode->left=NULL;
		newNode->info=X;
		newNode->right=NULL;
	}
	return newNode;
}

/* ------------------------------ Operasi-operasi Tree ------------------------------- */

void bInsert(bAddr *root, infType X){
	if (*root == NULL){ //JIka belum terdapat root
		*root=bCNode(X);
	}else{
		if (X < (*root)->info) 
        	bInsert(&(*root)->left, X); 
    	else if (X >= (*root)->info) 
    		bInsert(&(*root)->right, X);
	}
}

bAddr bSearch(bAddr root, infType src){
	if (root!=NULL){
		if (root->info==src)
			return root;
		else{
			(src > root->info) ? bSearch(root->right,src) : bSearch(root->left,src);
		}
	}
	else{
		return NULL;
	}
}

/*void bDelete(bAddr *pDel, bAddr pCur, bTree *pTree){
	if (pCur != NULL) {
		if (pCur==pTree->root && pCur->left==NULL && pCur->right==NULL){
			pTree->root=NULL;
			return;
		}
		
		bDelete(&(*pDel), pCur->left, &(*pTree));
		
		if (pCur!=*pDel){
			if (pCur->right != pCur->parent->right){
				pCur->right=pCur->parent->right;
			}
		}else{
			if (pCur->parent!=NULL){
				if (pCur->parent->left == pCur)
					pCur->parent->left=pCur->left;
				else{
					pCur->parent->right=pCur->right;
				}
			}
			if (pCur->left!=NULL && pCur->right==NULL){
				pCur->left->parent=pCur->parent;
			}
			if (pCur->right!=NULL && pCur->left==NULL){
				pCur->right->parent=pCur->parent;
			}
			if (pCur->parent==NULL){
				pTree->root=pCur->left;
				pCur->left=NULL;
			}
			free(pCur);
		}
	}
}*/

int bDepth(bAddr root){
	int y=0,z=0;

	if(root==NULL)
		return -1;
	y=bDepth(root->left);
	z=bDepth(root->right);
	if (y > z)
		return (y+1);
	else
		return (z+1);
}


/* --------------------------------- Traversal Tree ---------------------------------- */

void bPost(bAddr root){
	if (root!=NULL){
		bPost(root->left);
		bPost(root->right);
		printf("%c ", root->info);
	}
}

void bPre(bAddr root){
	if (root!=NULL){
		printf("%c ", root->info);
		bPre(root->left);
		bPre(root->right);
	}
}

void bIn(bAddr root){
	if (root!=NULL){
		bIn(root->left);
		printf("%c ", root->info);
		bIn(root->right);
	}	
}

void bLevelOrder(bAddr root,int curLevel, int desLevel){
	if(root!=NULL)
	{
		if(curLevel==desLevel)
			printf("%c ",root->info);
		bLevelOrder(root->left,curLevel+1,desLevel);
		bLevelOrder(root->right,curLevel+1,desLevel);
	}
}

/* ----------------------------------- Print TREE ------------------------------------ */

void bPrint(bAddr node, char tab[], char type[]){
	char tempTab[255];
	strcpy(tempTab, tab);
	strcat(tempTab, "\t");
	if (node!=NULL){
		printf("%s`[%s]--[%c]\n",tab,type,node->info);
		bPrint(node->left,tempTab,"[L]");
		bPrint(node->right,tempTab,"[R]");
	}
}

/* ------------------------------ Extended Binary Tree ------------------------------- */
/* ---- Balanced Binary Tree atau AVL Tree (Adelson-Velksii dan Landis) ----*/

//avlAddr avlCNode(avlType X){
//	avlAddr newNode;
//	newNode=(avlAddr) malloc(sizeof(ElmtTree2));
//	if (newNode != NULL){
//		newNode->info=X;
//		newNode->height=1;
//		newNode->left=NULL;
//		newNode->right=NULL;
//	}
//	return newNode;
//}
//
//int height(avlAddr N) 
//{ 
//	if (N == NULL) 
//		return 0; 
//	return (N)->height; 
//} 
//
//int max(int a, int b) 
//{ 
//	return (a > b)? a : b; 
//}  
// 
//avlAddr rightRotate(avlAddr y) 
//{ 
//	avlAddr x = (y)->left; 
//	avlAddr T2 = (x)->right; 
//
//	// proses rotasi 
//	(x)->right = y; 
//	(y)->left = T2; 
//
//	// update height 
//	(y)->height = max(height(y->left), height((y)->right))+1; 
//	(x)->height = max(height((x)->left), height((x)->right))+1; 
// 
//	return (x); 
//} 
//
// 
//avlAddr leftRotate(avlAddr x) 
//{ 
//	avlAddr y = (x)->right; 
//	avlAddr T2 = (y)->left; 
//
//	// proses rotasi
//	(y)->left = x; 
//	(x)->right = T2; 
//
//	// update height
//	(x)->height = max(height((x)->left), height((x)->right))+1; 
//	(y)->height = max(height((y)->left), height((y)->right))+1; 
//
//	return (y); 
//} 
// 
//int getBalance(avlAddr N) 
//{ 
//	if (N == NULL) 
//		return 0; 
//	return height((N)->left) - height((N)->right); 
//} 
//
//void avlInsert(avlAddr *node, infType X){
//	avlAddr root;
//	
//	root=avlCNode(X);
//	
//	/* Normal BST Insertion */
//	if (root != NULL){ 
//		if (*node == NULL) 
//			*node=root;
//		else{
//			if (X < (*node)->info) 
//				avlInsert(&(*node)->left, X); 
//			else if (X > (*node)->info) 
//				avlInsert(&(*node)->right, X); 
//		}
//	}
//
//	/* Update height */
//	(*node)->height = 1 + max(height((*node)->left), 
//						height((*node)->right)); 
//
//	/* Menyeimbangkan tree */
//	int balance = getBalance(*node); 
//
//	// Jika tree masih belum seimbang, berlanjut ke salah satu dari 4 kasus di bawah 
//
//	// Left Left Case 
//	if (balance > 1 && X < (*node)->left->info) 
//		*node = rightRotate(*node);
//
//	// Right Right Case 
//	if (balance < -1 && X > (*node)->right->info) 
//		*node = leftRotate(*node); 
//
//	// Left Right Case 
//	if (balance > 1 && X > (*node)->left->info) { 
//		(*node)->left = leftRotate((*node)->left); 
//		*node = rightRotate(*node); 
//	} 
//
//	// Right Left Case 
//	if (balance < -1 && X < (*node)->right->info) { 
//		(*node)->right = rightRotate((*node)->right); 
//		*node = leftRotate(*node); 
//	} 
//}
//
//avlAddr avlSearch(avlAddr root, avlType src){
//	avlAddr nSrc;
//	if (root!=NULL){
//		if (root->info==src)
//			return root;
//		else{
//			nSrc=avlSearch(root->left,src);
//			if (nSrc==NULL)
//				return avlSearch(root->right,src);
//			else
//				return nSrc;
//		}
//	}
//	else{
//		return NULL;
//	}
//}
//
//avlAddr minValueNode(avlAddr node) { 
//    avlAddr current = node; 
//  
//    /* Mencari node terkecil */
//    while (current && current->left != NULL) 
//        current = current->left; 
//  
//    return current; 
//} 
//
//avlAddr avlDel(avlAddr root, int key) { 
//	avlAddr temp;
//	// BASE CASE
//    if (root == NULL) return root; 
//  
//    // Jika nilai yang dihapus lebih kecil dari nilai root
//    if (key < root->info) 
//        root->left = avlDel(root->left, key); 
//  
//  
//    // Jika nilai yang dihapus lebih besar dari nilai root
//    else if (key > root->info) 
//        root->right = avlDel(root->right, key); 
//  
//    // Jika root yang dihapus
//    else{ 
//        // Node dengan 1 child 
//        if (root->left == NULL) { 
//            temp = root->right; 
//            free(root); 
//            return temp; 
//        } 
//        else if (root->right == NULL) { 
//            avlAddr temp = root->left; 
//            free(root); 
//            return temp; 
//        } 
//  
//        // Node dengan 2 child: Get the inorder successor (smallest) 
//        
//        temp = minValueNode(root->right); 
//  
//        // Salin inorder successor sebagai pengganti root 
//        root->info = temp->info; 
//  
//        // Delete the inorder successor 
//        root->right = avlDel(root->right, temp->info); 
//    } 
//    return root; 
//} 
//
//bAddr minValueNode(bAddr node) { 
//    bAddr current = node; 
//  
//    /* Mencari node terkecil */
//    while (current && current->left != NULL) 
//        current = current->left; 
//  
//    return current; 
//} 
//
//bAddr bDel(bAddr root, int key) { 
//	bAddr temp;
//	// BASE CASE
//    if (root == NULL) return root; 
//  
//    // Jika nilai yang dihapus lebih kecil dari nilai root
//    if (key < root->info) 
//        root->left = bDel(root->left, key); 
//  
//  
//    // Jika nilai yang dihapus lebih besar dari nilai root
//    else if (key > root->info) 
//        root->right = bDel(root->right, key); 
//  
//    // Jika root yang dihapus
//    else{ 
//        // Node dengan 1 child 
//        if (root->left == NULL) { 
//            temp = root->right; 
//            free(root); 
//            return temp; 
//        } 
//        else if (root->right == NULL) { 
//            bAddr temp = root->left; 
//            free(root); 
//            return temp; 
//        } 
//  
//        // Node dengan 2 child: Get the inorder successor (smallest) 
//        
//        temp = minValueNode(root->right); 
//  
//        // Salin inorder successor sebagai pengganti root 
//        root->info = temp->info; 
//  
//        // Delete the inorder successor 
//        root->right = bDel(root->right, temp->info); 
//    } 
//    return root; 
//} 

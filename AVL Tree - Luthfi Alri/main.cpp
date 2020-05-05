#include "avlTree.h"

avlTree AVL,BST;
int x;
//rightavlType isi;
avlAddr PDel, Prec;
	
int main(){
	
	//Header
	printf("Struktur data dan Algoritma : BST dan AVL\n");
	printf("Dibuat Oleh :	");
	printf("\nLuthfi Alri		(181511021)\n");
	printf("==============================\n");
	
	printf("\n\nIn Order : ");
	avlIn(AVL.root);
	
	if (AVL.root == NULL && BST.root == NULL){
		//ALLOC
		avlCreate(&AVL);
		avlCreate(&BST);
	}
	
	//MENU
	printf("\n\nPROGRAM MENU\n");
	printf("1. Input Element\n");
	printf("2. Delete Element\n");
	printf("3. Tampilkan AVL Tree\n");
	printf("4. Tampilkan BST Tree\n");
	printf("5. Exit\n\n");
	printf("Pilihan	:"); scanf("%d", &x);
	switch(x){
		case 1 : {
			system("cls");
			printf("\nInput Element\n");
			printf("Input Angka		: "); scanf("%d", &x);
			
			avlInsert(&AVL.root,x);
			bInsert(&BST.root,x);
			break;
		}
		case 2 : {	
			system("cls");
			printf("\nDelete Element\n");
			printf("Input Angka		: "); scanf("%d", &x);
			AVL.root = avlDelete(AVL.root, x);
			avlPrint(AVL.root, " ",'0');
			printf("\n\n");
			system("pause");
			system("cls");
			break;
		}
		case 3 : {	
			system("cls");
			printf("===AVL TREE=== \n");
			printf("\nDEPTH: %d\n\n", avlDepth(AVL.root));
			avlPrint(AVL.root, " ",'0');
			printf("\n\n");
			system("pause");
			system("cls");
			break;
		}
		case 4 : {	
			system("cls");
			printf("===BST TREE=== \n");
			printf("\nDEPTH: %d\n\n", avlDepth(BST.root));
			avlPrint(BST.root, " ",'0');
			printf("\n\n");
			system("pause");
			system("cls");
			break;
		}
		default : {
			exit(0);
			break;
		}
	}
	
	return main();
}

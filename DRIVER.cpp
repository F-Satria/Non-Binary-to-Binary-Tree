/*
File		: ADT Binary Tree + Balanced Binary Tree (AVL)
Author		: Febriyoga BS / 181511013
Last Update : 18-6-2019

 ** Modul AVL Insert (termasuk cara menyeimbangkan Node) dan AVL Delete,
 ** adalah hasil modifikasi dari code yang ditemukan di geeksforgeeks

*/

#include "nbtobinary_d.h"
	
nbTree nBTree;
nbAddr nbPDel;

bTree BTree;
bAddr Tree,
	  bPDel;

char nilai;
int	parent,
	pilih;
	
bool isBinary,
	 isTransformReady=false;
	
void printTree_withTraversal(bool isBinary);		

int main(){

	system("cls");
	printf("======================================================\n");
	printf("|| Tugas Akhir Struktur data dan Algoritma \t    ||\n");
	printf("|| Transformasi Non-Binary Tree ke Binary Tree\t    ||\n");
	printf("|| Dibuat oleh : Adhitya Febhiakbar     [181511002] ||\n");
	printf("|| 	       : Febriyoga Bagus Satria [181511013] ||\n");
	printf("||	       : Luthfi Alri	        [181511021] ||\n");
	printf("======================================================\n");
	
	//ALLOC Tree
	if (nBTree.root == NULL) 
		nbCreate(&nBTree);
	if (BTree.root == NULL) 
		bCreate(&BTree);

	//Selection
	printf("\n[MENU]");
	printf("\n(1) View Non-Binary Tree \n(2) Transform Tree (From Non-Binary to Binary) \n(3) Transform Tree (From Non-Binary to Balanced Binary) \n(0) Exit ");
	printf("\n\nPilihan : ");
	scanf("%d", &pilih);
	switch(pilih){
		case 1 :{
			system("cls");
			isTransformReady=1;
			printf("[Non Binary Tree]  ");
			if (nBTree.root == NULL) {
				nbInsert(&nBTree, 0, 'X');
				nbInsert(&nBTree, nbSearch(nBTree.root, 'X'), 'A');
				nbInsert(&nBTree, nbSearch(nBTree.root, 'X'), 'B');
				nbInsert(&nBTree, nbSearch(nBTree.root, 'X'), 'C');
				nbInsert(&nBTree, nbSearch(nBTree.root, 'A'), 'P');
				nbInsert(&nBTree, nbSearch(nBTree.root, 'A'), 'Q');
				nbInsert(&nBTree, nbSearch(nBTree.root, 'C'), 'R');
				nbInsert(&nBTree, nbSearch(nBTree.root, 'C'), 'S');
				nbInsert(&nBTree, nbSearch(nBTree.root, 'C'), 'T');
				nbInsert(&nBTree, nbSearch(nBTree.root, 'Q'), 'K');
				nbInsert(&nBTree, nbSearch(nBTree.root, 'Q'), 'L');
				nbInsert(&nBTree, nbSearch(nBTree.root, 'Q'), 'M');
			}
			printTree_withTraversal(0);
			
			NB_Menu:
			printf("\n\n(1) Insert Node \n(2) Delete Node \n(3) Kembali ke Menu");
			printf("\nPilihan : ");
			scanf("%d", &pilih);
			switch (pilih){
				case 1 : {
					printf("\nNilai node baru : "); fflush(stdin); scanf("%c", &nilai);
					printf("\nParent : "); fflush(stdin); scanf("%c", &parent);
					nbInsert(&nBTree, nbSearch(nBTree.root, parent), nilai);
					
					system("cls");
					printf("[Non Binary Tree]");
					printTree_withTraversal(0);
					goto NB_Menu;
					break;
				}
				case 2 : {
					printf("\nNode yang akan dihapus : "); scanf("%s", &nilai);
					nbPDel = nbSearch(nBTree.root, nilai);
					nbDelete(&nbPDel, nbPDel, &nBTree);
					
					system("cls");
					printf("[Binary Tree]  ");
					printTree_withTraversal(0);
					goto NB_Menu;
					break;
				}
				case 3 : {
					main();
					break;
				}
			}
			break;
		}
		case 2 :{
			if (isTransformReady==1){
				system("cls");
				printf("[Binary Tree]\n");
				nbToBinary (&BTree.root,nBTree.root);
				printTree_withTraversal(1);
				system("pause");
				main();
				break;	
			} else {
				printf("\nTransform to Binary Tree belum bisa diakses \nPilih View Non-Binary Tree terlebih dahulu untuk memilih menu ini\n\n");
				system("pause");
				main();
				break;
			}
		}
		case 3 :{
			if (isTransformReady==1){
				system("cls");
				printf("[Binary Tree]\n");
				bToBalance (&BTree.root, nBTree.root);
				printTree_withTraversal(1);
				system("pause");
				main();
				break;	
			} else {
				printf("\nTransform to Balanced Binary Tree belum bisa diakses \nPilih View Non-Binary Tree terlebih dahulu untuk memilih menu ini\n\n");
				system("pause");
				main();
				break;
			}
		}
		default :{
			exit(0);
			break;
		}
	}
	
	return 0;
}

//Menampilkan Tree dan Menampilkan Traversal Tree tersebut
void printTree_withTraversal(bool isBinary){
	int idx;
	if (isBinary){
		printf("Depth: %d\n\n", bDepth(BTree.root));
		bPrint(BTree.root, " ", "ROOT");
		printf("\nTraversal Pre-Order\n"); bPre(BTree.root);
		printf("\n\nTraversal In-Order\n"); bIn(BTree.root);
		printf("\n\nTraversal Post-Order\n"); bPost(BTree.root);
		printf("\n\nTraversal Level-Order\n"); 
		for (idx=0;idx <= bDepth(BTree.root);idx++){
			printf("Level-%d\t",idx); 
			bLevelOrder(BTree.root, 0, idx); printf("\n");
		}
	} else {
		printf("Depth: %d\n\n", nbDepth(nBTree.root));
		nbPrint(nBTree.root, " ", "ROOT");
		printf("\nTraversal Pre-Order\n"); nbPre(nBTree.root);
		printf("\n\nTraversal In-Order\n"); nbIn(nBTree.root);
		printf("\n\nTraversal Post-Order\n"); nbPost(nBTree.root);
		printf("\n\nTraversal Level-Order\n");
		for (idx=0;idx <= nbDepth(nBTree.root);idx++){
			printf("Level-%d\t",idx); 
			nbLevelOrder(nBTree.root, 0, idx); printf("\n");
		}
	}
}

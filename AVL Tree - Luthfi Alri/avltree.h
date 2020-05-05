/*
File	: rightavlTree_d.h
Author	: SN
Last Updt : 25-5-2011
*/

#ifndef rightavlTree_d_H
#define rightavlTree_d_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct avlTreeNode *avlAddr;
typedef int avlType;

typedef struct avlTreeNode{
	avlAddr left;
	avlType info;
	avlAddr right;
}ElmtTree;

struct avlTree{
	avlAddr root;
};

/* ---------------- Konstruktor Tree ---------------- */
void avlCreate(avlTree *x);
//Membuat avlTree kosong (X.root=NULL)

/* ---------------- Alokasi node baru Tree ---------------- */
avlAddr avlCNode(avlType X);
//Alokasi untuk membuat node baru

/* ---------------- Operasi-operasi Tree ---------------- */

void avlInsert(avlAddr *root, avlType X);
// Menambah element pada node parent

void avlBalance(avlAddr *root, avlType X);

void bInsert(avlAddr *root, avlType X);

avlAddr avlSearch(avlAddr root, avlType src);
// Mencari node dengan info ttn dan mengembalikan avlAddressnya

void deleteTree(avlAddr *node);
// Menghapus node tertentu dan digantikan oleh left dari node tsb

avlAddr minValueNode(avlAddr node);

avlAddr avlDelete(avlAddr root, int X);
// 

int avlDepth(avlAddr root);
// Mengukur kedalaman suatu node dari root

int getBalance(avlAddr root);

int max(int a, int b);

int avlHeight(avlAddr root);

/*------------------ ROTATE Tree ------------------ */

avlAddr rightRotate(avlAddr root);

avlAddr leftRotate(avlAddr root);

/* ---------------- TRAVERSAL Tree ---------------- */
void avlPost(avlAddr root); // Postorder traversing
void avlPre(avlAddr root); // Preorder traversing
void avlIn(avlAddr root); // Inorder traversing
void avlLevelOrder(avlAddr root,int curLevel, int desLevel); // Levelorder traversing

/* ---------------- PRINT TREE ---------------- */
void avlPrint(avlAddr node, char tab[], char type);

#endif

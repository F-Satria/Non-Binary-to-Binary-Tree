/*
File		: nbtobinary_d.h
Last Updte	: 25-6-2019
 */

#ifndef nbtobinary_d_H
#define nbtobinary_d_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma GCC diagnostic ignored "-Wwrite-strings"

/////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// Struktur Data /////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////


typedef char infType;

/* ------------------------------------ Non Binary ----------------------------------- */

typedef struct nbTreeNode *nbAddr;

typedef struct nbTreeNode{
	nbAddr fs; //First child
	infType info;
	nbAddr nb; //Next brother
	nbAddr parent;
}nbElmtTree;

struct nbTree{
	nbAddr root;
};
/* -------------------------------------- Binary ------------------------------------- */

typedef struct bTreeNode *bAddr;

typedef struct bTreeNode{
	bAddr left;
	infType info;
	bAddr right;
}bElmtTree;

struct bTree{
	bAddr root;
};

/////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// Non Binary ke Binary //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void nbToBinary (bAddr *dest, nbAddr src);

void bToBalance (bAddr *dest, nbAddr src);

void fixBalance (bAddr *dest);
/* Fungsinya sama dengan bBalance tetapi dicek kembali apabila masih ada yang belum balance */

void bBalance(bAddr *root, infType X);

int getBalance(bAddr root);

int max(int a, int b);

int bHeight(bAddr root);

bAddr rightRotate(bAddr root);

bAddr leftRotate(bAddr root);

/////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// MODUL NON BINARY TREE //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

/* -------------------------------- Konstruktor Tree --------------------------------- */

void nbCreate(nbTree *x);
//Membuat tree kosong (X.root=NULL)

/* ----------------------------- Alokasi node baru Tree ------------------------------ */

nbAddr nbCNode(infType X);
//Alokasi untuk membuat node baru

/* ------------------------------ Operasi-operasi Tree ------------------------------- */

void nbInsert(nbTree *tRoot, nbAddr parent, infType X);
// Menambah element pada node parent

nbAddr nbSearch(nbAddr root, infType src);
// Mencari node dengan info ttn dan mengembalikan addressnya

void nbUpgrade(nbAddr *root);
// Mengupgrade parent dari beberapa node. (digunakan pada proses penghapusan)

void nbDelete(nbAddr *pDel, nbAddr pCur, nbTree *pTree);
// Menghapus node tertentu dan digantikan oleh fs dari node tsb

int nbDepth(nbAddr root);
// Mengukur kedalaman suatu node dari root


/* --------------------------------- Traversal Tree ---------------------------------- */

void nbPost(nbAddr root); 
// Postorder traversing

void nbPre(nbAddr root); 
// Preorder traversing

void nbIn(nbAddr root); 
// Inorder traversing

void nbLevelOrder(nbAddr root,int curLevel, int desLevel); 
// Levelorder traversing

/* ----------------------------------- Print TREE ------------------------------------ */

void nbPrint(nbAddr node, char tab[], char type[]);

/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// MODUL BINARY TREE ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

/* -------------------------------- Konstruktor Tree --------------------------------- */

void bCreate(bTree *x);
//Membuat tree kosong (X.root=NULL)

/* ----------------------------- Alokasi node baru Tree ------------------------------ */

bAddr bCNode(infType X);
//Alokasi untuk membuat node baru

/* ------------------------------ Operasi-operasi Tree ------------------------------- */

void bInsert(bAddr *root, infType X);
// Menambah element pada node parent

bAddr bSearch(bAddr root, infType src);
// Mencari node dengan info ttn dan mengembalikan addressnya

void bDelete(bAddr *pDel, bAddr pCur, bTree *pTree);
// Menghapus node tertentu dan digantikan oleh fs dari node tsb

int bDepth(bAddr root);
// Mengukur kedalaman suatu node dari root


/* --------------------------------- Traversal Tree ---------------------------------- */

void bPost(bAddr root); 
// Postorder traversing

void bPre(bAddr root); 
// Preorder traversing

void bIn(bAddr root); 
// Inorder traversing

void bLevelOrder(bAddr root,int curLevel, int desLevel); 
// Levelorder traversing

/* ----------------------------------- Print TREE ------------------------------------ */

void bPrint(bAddr node, char tab[], char type[]);

#endif

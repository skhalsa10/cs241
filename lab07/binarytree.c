/***********************************************
*                                              *
*               By: Siri Khalsa                *
*                  11/04/16                    *
*                 CS-241 001                   *
*		            lab07                      *
*              | binarytree.c |                *
*        defines binarytree data struct        *
*                                              *
***********************************************/

#include "linkedlist.h"
#include <stdlib.h>
#include <stdio.h>

/************************************************************
 * parameters:
 * int data - data to be inserted in new TreeNode
 ************************************************************
 * this function Allocs a new node with given data.
 ************************************************************
 * Returns:
 * struct TreeNode* - pointer to new TreeNode 
 ************************************************************/
struct TreeNode* createNode(int data)
{
    struct TreeNode* node = malloc(sizeof(struct TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/************************************************************
 * parameters:
 * int data - Data used to determine where 
 *            new node will be inserted
 * struct TreeNode* root - pointer to the Root TreeNode
 ************************************************************
 * Insert data at appropriate place in BST
 ************************************************************
 * Returns:
 * struct TreeNode* - pointer to new Tree Root
 ************************************************************/
struct TreeNode* insertBST(struct TreeNode* root, int data)
{
    
}

/************************************************************
 * parameters:
 * int data - Data used to determine which
 *            node will be removed
 * struct TreeNode** rootRef - Ref to a pointer 
 *                             to the Root node
 ************************************************************
 * Remove data from BST pointed to by rootRef, 
 * changing root if necessary.
 * For simplicity's sake, always choose node's in-order
 * predecessor in the two-child case.
 * Memory for removed node will be freed.
 ************************************************************
 * Returns:
 * Return 1 if data was present, 0 if not found
 ************************************************************/
int removeBST(struct TreeNode** rootRef, int data)

/************************************************************
 * parameters:
 * struct TreeNode* root - root pointer
 ************************************************************
 * this function will find the maximum value in BST
 ************************************************************
 * Returns:
 * Maximum value in non-empty binary search tree. 
 ************************************************************/
int maxValueBST(struct TreeNode* root)

/************************************************************
 * parameters:
 * struct TreeNode* root - root pointer
 ************************************************************
 * this function will find the maximum depth
 ************************************************************
 * Returns:
 * maximum depth of tree. Empty tree has depth 0
 ************************************************************/
int maxDepth(struct TreeNode* root)

/************************************************************
 * parameters:
 * struct TreeNode* root - root pointer
 ************************************************************
 * Checks if BST is balanced. based on the following:
 * A tree is balanced if both subtrees are balanced and
 * the difference in height between 
 * the subtrees is no more than 1.
 ************************************************************
 * Returns:
 * 1 if tree is balanced, 0 if not.
 ************************************************************/
int isBalanced(struct TreeNode* root)

/************************************************************
 * parameters:
 * struct TreeNode* root - root pointer
 ************************************************************
 * Checks to see if the BST is a real BST
 ************************************************************
 * Returns:
 * 1 if tree is a binary search tree, 0 if not
 ************************************************************/
int isBST(struct TreeNode* root)

/************************************************************
 * parameters:
 * struct TreeNode* root - root pointer
 ************************************************************
 * Print data for inorder tree traversal on single line,
 * separated with spaces, ending with newline.
 ************************************************************
 * Returns:
 * void
 ************************************************************/
void printTree(struct TreeNode* root)

/* Print data for leaves on single line,
 * separated with spaces, ending with newline.*/
void printLeaves(struct TreeNode* root)

/* Free memory used by the tree. */
void freeTree(struct TreeNode* root)

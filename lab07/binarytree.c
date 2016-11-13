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

#include "binarytree.h"
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
    if(root == NULL) return createNode(data);    

    if(data < root->data)
    {
        if(root->left == NULL)
        {
            root->left = createNode(data);
            return root;
        }
        else
        {
            insertBST(root->left,data);
            return root;
        }
    }
    if(data >= root->data)
    {
        if(root->right == NULL)
        {
            root->right = createNode(data);
            return root;
        }
        else
        {
            insertBST(root->right, data);
            return root;
        }
    }
    return root;
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
{
    struct TreeNode* current = *rootRef;
    struct TreeNode** currentRef = NULL;
    struct TreeNode* toFree = NULL;
    struct TreeNode* temp = NULL;
    if(*rootRef == NULL) return 0;
    while(current->data != data&&current->left != NULL &&current->right != NULL)
    {
        if(data < current->data)
        {
            removeBST(&(current->left),data);
        }
        if(data >= current->data)
        {
            removeBST(&(current->right),data);
        }
    }
    if(current->data != data && current->left == NULL &&current->right == NULL)
    {
        return 0;
    }
    if(current->data == data && current->left == NULL &&current->right == NULL)
    {
        free(current);
        return 1;
    }
    if(current->data == data && current->left != NULL &&current->right == NULL)
    {
        toFree = current;
        current = current->left;
        free(toFree);
        return 1;
    }
    if(current->data == data && current->left == NULL &&current->right != NULL)
    {
        toFree = current;
        current = current->right;
        free(toFree);
        return 1;
    }
    if(current->data == data && current->left != NULL &&current->right != NULL)
    {
        toFree = current;
        currentRef = &current;
        currentRef = &(toFree->left);
        temp = toFree->right;
        while(current->right != NULL)
        {
            current = current->right;
        }
        current->right = temp;
        free(toFree);
        return 1;
    }
    return 0;
}

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
{
    if(root->right == NULL) return root->data;
    return maxValueBST(root->right);
}

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
{
    int left = 0;
    int right = 0;
    if(root == NULL)return 0;
    if(root->left == NULL && root->right == NULL)
    {
        return 1;
    }
    left += maxDepth(root->left);
    right += maxDepth(root->right);

    return ((left >= right) ? left : right);

}

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
{
    if(root == NULL) return 1;
    if(root->left == NULL && root->right == NULL) return 1;
    if(isBalanced(root->left) && isBalanced(root->right))
    {
        if(maxDepth(root->left)-maxDepth(root->right) < 2)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

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
{
    if(root->left == NULL && root->right == NULL)
    {
        return 1;
    }
    if(root->left == NULL)
    {
        if(root->right->data < root->data) 
        {
            return 0;
        }
        else
        {
            return isBST(root->right);
        }
    }
    if(root->right == NULL)
    {
        if(root->left->data >= root->data)
        {
            return 0;
        }
        else
        {
            return isBST(root->left);
        }
    }
    if(isBST(root->left)&&isBST(root->right))
    {
        return 1;
    }

    return 0;
}

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
{
    if(root == NULL)
    {
        printf("\n");
        return;
    }
    if(root->left == NULL && root->right == NULL)
    {
        printf(" %d", root->data);
        if(root->data == maxValueBST(root))
        {
            printf("\n");
        }
        return;
    }
    if(root->right == NULL)
    {
        printTree(root->left);
    }
    if(root->left == NULL)
    {
        printf(" %d", root->data);
        printTree(root->right);
    }
    printTree(root->left);
    printf(" %d", root->data);
    printTree(root->right);
}

/* Print data for leaves on single line,
 * separated with spaces, ending with newline.*/
void printLeaves(struct TreeNode* root)
{
    printf("%d",root->left->data);
    printf("%d\n",root->right->data);
}

/* Free memory used by the tree. */
void freeTree(struct TreeNode* root)
{
    if(root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

/* Aly Abdelrahman
   COP 3502
   assignment four
*/


#include <stdio.h>
#include <stdlib.h>
#include <strings.h>



//Structures
struct binTreeNode
{
    int data;
    struct binTreeNode *right;
    struct binTreeNode *left;
};

typedef struct binTreeNode node;

//Function Prototypes
void insert(node **tree, int val);
void rFile(node **tree);
void print_preorder(node *tree);
void print_inorder (node *tree);
void print_postorder (node *tree);
int search(node *tree, int);
int minimum(node* tree);
void maximum(node *tree);
int avgTree(node* tree);
int sumTree(node *tree);
int numInTree(node *tree);
int height(node *tree);
void print_breadthfirst(node *tree);
double median(node*);
int arrinorder(node *, int*, int);
struct binTreeNode* delete(struct binTreeNode* root, int value);
int add(struct binTreeNode *current_ptr);

//====================================//
int main()
{
    node *root;
    node *temp;

    root = NULL;

    //User input variable
    int i, val = 0;

    int average;
    int sumOfAll;
    int totalNodes;
    double med;

    while(1)
    {
        /*Menu options for user*/
        printf("\nPlease choose an option from the Menu\n");
        printf("Enter an integer corresponding to the following menu options\n");

        printf("\nMenu\n");
        printf("-----------------\n\n");

        printf("1. Generate Binary Search Tree\n");
        printf("2. Print the BST in pre-order format\n");
        printf("3. Print the BST in in-order format\n");
        printf("4. Print the BST in post-order format\n");
        printf("5. Print the BST  in breadth-first format\n");
        printf("6. Find a value in the BST\n");
        printf("7. Find the minimum value in the BST nodes\n");
        printf("8. Find the maximum value in the BST nodes\n");
        printf("9. Calculate the average value of the BST nodes\n");
        printf("10. Find the median value of the BST nodes\n");
        printf("11. Calculate the sum of the BST nodes\n");
        printf("12. Count the number of BST nodes\n");
        printf("13. Delete a value in the BST\n");
        printf("14. Exit Program\n\n");

         if(scanf("%d", &i) <=0)
            {
                printf("Enter an integer only\n");
                exit(0);
            }
            else
            {
                switch(i)
                {

                case 1:
                    //read file
                    rFile(&root);
                    break;

                //Print in Pre Order
                case 2:
                    printf("Pre Order \n");
                    print_preorder(root);
                    break;
                //Print  In Order
                case 3:
                    printf("In Order \n");
                    print_inorder(root);
                    break;
                //Print in Post Order
                case 4:
                    printf("Post Order \n");
                    print_postorder(root);
                    break;
                //Print in Breadth-First
                case 5:
                    printf("Breadth-First \n");
                    print_breadthfirst(root);
                    break;
                //Finding a value
                case 6:
                    printf("Enter the value you would like to find: ");
                    scanf("%d", &val);
                    if(search(root, val))
                        printf("\n Located in the tree: %d\n", val);
                    else
                        printf("\n %d was not found in the tree.\n", val);
                    break;
                //Find the minimum value
                case 7:
                    minimum(root);
                    break;
                //Find the maximum value
                case 8:
                    maximum(root);
                    break;
                //Calculate the average
                case 9:
                    average = avgTree(root);
                    printf("The average  is: %d\n", average);
                    break;
                //Find the median
                case 10:
                    med = median(root);
                    printf("The median  is %.1f \n", med);
                    break;
                //Calculate the Sum
                case 11:
                    sumOfAll=sumTree(root);
                    printf("The sum of all BST nodes is: %d\n\n", sumOfAll);
                    break;
                //Count the number of nodes
                case 12:
                    totalNodes=numInTree(root);
                    printf("Total number of nodes is: %d\n\n", totalNodes);
                    break;
                //Delete a value
                case 13:
                    printf("What would you like to delete?\n\n");
                    scanf("%d", &val);

                    if (!find(root,val))
                           printf("The value doesnt exist.\n");
                        else {
                        root = delete(root,val);
                        printf("The value was deleted!\n\n");
                        }

                    break;
                //Exit
                case 14:
                    printf("Exit\n");
                    return 0;
                default:
                    printf("Invalid option\n");
                    printf("For real ? enter a correct input");

                }
            }
    }


}


//Insert Function
void insert(node **tree, int val)
{
    node *temp = NULL;

    if(!(*tree))
    {
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right = NULL;
        temp->data = val;
        *tree = temp;
        return;
    }

    if(val < (*tree)->data)
    {
        insert(&(*tree)->left, val);
    }
    else if(val > (*tree)->data)
    {
        insert(&(*tree)->right, val);
    }

}



//Read File Function
void rFile(node **tree)
{
    int value;
    FILE *fp;

    fp=fopen("AssignmentFour.txt", "r");

    if(fp == NULL)
    {
        perror("Error opening file.\n");
        exit(0);
    }

    printf("\n");

    while(fscanf(fp, "%d", &value) != EOF)
    {
        printf("%d ", value);
        insert(tree, value);
    }

    fclose(fp);
}

//Pre-Order Function
void print_preorder(node *tree)
{
    if(tree)
    {
        printf("%d ", tree->data);
        print_preorder(tree->left);
        print_preorder(tree->right);
    }
}


//In-Order Function
void print_inorder (node *tree)
{
    if(tree)
    {
        print_inorder(tree->left);
        printf("%d ", tree->data);
        print_inorder(tree->right);
    }
}

//Post-Order Function
void print_postorder (node *tree)
{
    if(tree)
    {
        print_postorder(tree->left);
        print_postorder(tree->right);
        printf("%d ", tree->data);
    }
}


//Breadth-First Function
void breadFirst(node *tree, int bstree)
{
    if(tree==NULL)
    {
        return;
    }
    if(bstree==1)
    {
        printf(" %d ", tree->data);
    }
    else if(bstree > 1)
    {
        breadFirst(tree->left, bstree-1);
        breadFirst(tree->right, bstree-1);
    }
}



// height function
int height(node *tree)
{
   int left;
   int right;

   if(tree==NULL)
   {
       return 0;
   }

   left = height(tree->left);
   right = height(tree->right);

   if(left > right)
   {
       return left+1;
   }

   return right+1;
}


//Breadth-First Function
void print_breadthfirst(node *tree)
{
    int a,b;

    a = height(tree);
    printf("Levels if tree in order is: %d\n", a);

    for(b=0; b <= a; b++)
    {
        breadFirst(tree, b);
    }
}


//Search Function
int search(node *tree, int val)
{
    if(tree != NULL)
    {
        if(tree->data == val)
        {
            return 1;

            if(val < tree->data)
            {
                return search(tree->left, val);
            }
            else
                return search(tree->right, val);
        }
    }
    else
        return 0;
}



//Minimum Value

int minimum(node* tree)
{
    if(tree->left==NULL)
    {
        printf("Min value is %d: \n", tree->data);
        return tree;
    }
    else
        return minimum(tree->left);
}



// Maximum Value

void maximum(node *tree)
{
    if(tree->right==NULL)
    {
        printf("The max value is %d: \n", tree->data);
        return tree;
    }
    else return maximum(tree->right);
}



//average Function

int avgTree(node *tree)
{

    int cnt = sumTree(tree);
    int sum = numInTree(tree);
    int avg;
    avg = cnt/sum;
    return avg;

}



//Maximum Value Function
int sumTree(node *tree)
{
    if(tree!=NULL)
    {
        return tree->data + sumTree(tree->left) + sumTree(tree->right);
    }
    else
        return 0;

}


// Maximum Value Function
int numInTree(node *tree)
{
    if(tree!=NULL)
    {
        return 1 + numInTree(tree->left) + numInTree(tree->right);
    }
    else
        return 0;
}

int addNumsThree(node *tree)
{
    if(tree!=NULL)
    {
        return tree->data + addNumsThree(tree->left) + addNumsThree(tree->right);
    }
    else
        return 0;
}

double median(node *p)
{

    int arr[25];
    int len = inorder(p, arr, 0);
    int position = len/2;

    if (len % 2 == 1)
        return (double) arr[position];

    return (arr[position] + arr[position+1]) / 2.0;

}

int inorder(node *p, int arr [], int index)
{
        if(p->left != NULL)
            index = inorder(p->left, arr, index);

        arr[index] = p->data;
        index++;

        if(p->right != NULL)
            index = inorder(p->right, arr, index);

        return index;
}
int find(struct binTreeNode *current_ptr, int val) {

  if (current_ptr != NULL) {

    if (current_ptr->data == val)
      return 1;

    // Search left.
    if (val < current_ptr->data)
      return find(current_ptr->left, val);

    // search right
    else
      return find(current_ptr->right, val);

  }
  else
    return 0;
}

int add(struct binTreeNode *current_ptr) {

  if (current_ptr != NULL)
    return current_ptr->data+add(current_ptr->left)+
           add(current_ptr->right);
  else
    return 0;
}

struct binTreeNode* parent(struct binTreeNode *root, struct binTreeNode *node) {

  if (root == NULL || root == node)
    return NULL;

  if (root->left == node || root->right == node)
    return root;

  if (node->data < root->data)
    return parent(root->left, node);

  else if (node->data > root->data)
    return parent(root->right, node);

  return NULL;

}
int isLeaf(struct binTreeNode *node) {

  return (node->left == NULL && node->right == NULL);
}

int leftchild(struct binTreeNode *node) {
  return (node->left!= NULL && node->right == NULL);
}

int rightchild(struct binTreeNode *node) {
  return (node->left== NULL && node->right != NULL);
}


struct binTreeNode* findNode(struct binTreeNode *current_ptr, int value) {

  if (current_ptr != NULL) {

    if (current_ptr->data == value)
      return current_ptr;

    if (value < current_ptr->data)
      return findNode(current_ptr->left, value);

    else
      return findNode(current_ptr->right, value);

  }
  else
    return NULL;
}
// deleting portion of tree either children or parents.
// different cases if deleting left side, right side or parent node with multiple leafs.
// saves to temp and removes

struct binTreeNode* delete(struct binTreeNode* root, int value) {

  struct binTreeNode *deletenode, *new_del_node, *save_node;
  struct binTreeNode *par;
  int savevalue;

  deletenode = findNode(root, value);

  par = parent(root, deletenode);

  if (isLeaf(deletenode)) {

    if (par == NULL) {
      free(root);
      return NULL;
    }

    if (value < par->data) {
      free(par->left);
      par->left = NULL;
    }


    else {
      free(par->right);
      par->right = NULL;
    }

    return root;
  }


  if (leftchild(deletenode)) {

    if (par == NULL) {
      save_node = deletenode->left;
      free(deletenode);
      return save_node;
    }


    if (value < par->data) {
      save_node = par->left;
      par->left = par->left->left;
      free(save_node);
    }


    else {
      save_node = par->right;
      par->right = par->right->left;
      free(save_node);
    }

    return root;
  }

  if (rightchild(deletenode)) {

    if (par == NULL) {
      save_node = deletenode->right;
      free(deletenode);
      return save_node;
    }

    if (value < par->data) {
      save_node = par->left;
      par->left = par->left->right;
      free(save_node);
    }

    else {
      save_node = par->right;
      par->right = par->right->right;
      free(save_node);
    }
    return root;
  }

  new_del_node = minimum(deletenode->right);
  savevalue = new_del_node->data;

  delete(root, savevalue);


  deletenode->data = savevalue;

  return root;
}

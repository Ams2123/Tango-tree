#include <stdio.h>
#include <stdlib.h>

class tango {
  struct node {
    int data;
    node *right;
    node *left;
    node *parent;
    int isRoot;
    node *prefChild1;
    node *prefChild2;
    int balance;
  };
  struct node *root;
  struct node *auxroot;

public:
  tango() {
    root = NULL;
    auxroot = NULL;
  }

  struct node *insert(int, int, struct node *);
  struct node *creNewnode(int, struct node *);
  void setroot(struct node *);

  struct node *getroot();
  struct node *getauxroot();
  void inorder(struct node *);
  void pref(struct node *);
  void preorder(struct node *);
  void postorder(struct node *);

  int search(int);
  struct node *avl(struct node *);
  int checkBalance(struct node *);
  int getHeight(struct node *);
  struct node *balance(struct node *);

  //{ // void join();
  // void cut();
  // // void inorder(struct node *);
  // // void postorder(struct node *);
  // // void preorder(struct node *);
  //
  // struct node *avl(struct node *);
  // int getBalance(struct node *);
  // void joincut(struct node *);
  // struct node *gethead();
  // // struct node *leftRotate(struct node *);
  // // struct node *rightRotate(struct node *);
  // int getHeight(struct node *);
  // int search(int);
  //}
};

// these following 3 functions are for creating an perfectly balanced tree

struct tango::node *tango::creNewnode(int data, struct node *par) {
  struct node *newnode = new node;
  newnode->data = data;
  newnode->left = NULL;
  newnode->right = NULL;
  newnode->prefChild1 = NULL;
  newnode->prefChild2 = NULL;
  newnode->parent = par;
  if (par == NULL)
    newnode->isRoot = 1;
  else
    newnode->isRoot = 0;
  newnode->balance = 0;
  auxroot = NULL;
  return newnode;
}

struct tango::node *tango::insert(int low, int high, struct node *node) {
  if (low == high)
    return NULL;
  int mid = low + (high - low) / 2;
  struct node *newnode = creNewnode(mid, node);
  newnode->left = insert(low, mid, newnode);
  newnode->right = insert(mid + 1, high, newnode);
  return newnode;
}

void tango::setroot(struct node *node) { root = node; }

// these following 6 functions are for displaying

struct tango::node *tango::getroot() {
  return root;
}

struct tango::node *tango::getauxroot() {
  return auxroot;
}

void tango::inorder(node *root) {
  if (root == NULL)
    return;
  inorder(root->left);
  printf("%d ", root->data);
  inorder(root->right);
  return;
}

void tango::preorder(node *root) {
  if (root == NULL)
    return;
  printf("%d ", root->data);
  preorder(root->left);
  preorder(root->right);
  return;
}

void tango::pref(node *root) {
  if (root == NULL)
    return;
  pref(root->prefChild1);
  printf("%d ", root->data);
  return;
}

void tango::postorder(node *root) {
  if (root == NULL)
    return;
  postorder(root->left);
  postorder(root->right);
  printf("%d ", root->data);
  return;
}

int tango::search(int data) {
  int found = 0;
  if (auxroot == NULL) {
    struct node *temp = root;
    while (temp != NULL) {
      if (temp->data >= data) {
        if (temp->data == data)
          found = 1;
        temp->prefChild1 = temp->left;
        temp = temp->left;
      } else {
        temp->prefChild1 = temp->right;
        temp = temp->right;
      }
    }
    auxroot = avl(auxroot);
    return found;
  }
  return 0;
}

// these functions are for creating an auxillary tree for the first time

struct tango::node *tango::avl(struct node *node) {
  if (node == NULL)
    return NULL;
  struct node *temproot;
  temproot = avl(node->prefChild1);
  if (temproot == NULL) {
    temproot = node;
  } else {
    struct node *temp = temproot, *templ, *tempr;
    while (temp->prefChild1 != NULL)
      temp = temp->prefChild1;
    if (temp->data > node->data) {
      templ = temp->left;
      temp->left = node;
      node->parent = temp;
      node->right = templ;
      node->prefChild1 = NULL;
      node->prefChild2 = NULL;
      pref(temproot);
      if (node->parent != NULL)
        node->parent->prefChild1 = node;
      if (node->right != NULL)
        node->right->parent = node;
    } else {
      tempr = temp->right;
      temp->right = node;
      node->parent = temp;
      node->left = tempr;
      node->prefChild1 = NULL;
      node->prefChild2 = NULL;
      pref(temproot);
      if (node->parent != NULL)
        node->parent->prefChild1 = node;
      if (node->left != NULL)
        node->left->parent = node;
    }
    temp = temproot;
    while (temp != NULL) {
      temp->balance = checkBalance(temp);
      temp = temp->prefChild1;
    }
    temproot = balance(temproot);
  }
  return temproot;
}

struct tango::node *tango::balance(struct node *node) {
  if (node == NULL)
    return node;
  struct node *temp = node->prefChild1;
  if (node->balance > 1) {
    if (node->parent != NULL)
      node->parent = temp;
    if (node->parent != NULL && node->parent->prefChild1 == node) {
      node->parent->prefChild1 = temp;
      node->right = temp->left;
      temp->left = node;
      temp->prefChild2 = node;
      node->prefChild1 = NULL;
    }
  } else if (node->balance < -1) {
    if (node->parent != NULL)
      node->parent = temp;
    if (node->parent != NULL && node->parent->prefChild1 == node) {
      node->parent->prefChild1 = temp;
      temp->prefChild2 = node;
      node->left = temp->right;
      temp->right = node;
      node->prefChild1 = NULL;
    }

  } else
    temp = node;
  temp->prefChild1 = balance(temp->prefChild1);
  temp->prefChild2 = balance(temp->prefChild2);
  return temp;
}

int tango::checkBalance(struct node *node) {
  if (node == NULL)
    return 0;
  int leftHeight = 0, rightHeight = 0;
  if (node->prefChild1 == node->left or node->prefChild2 == node->left)
    leftHeight = getHeight(node->left);
  if (node->prefChild1 == node->right or node->prefChild2 == node->right)
    rightHeight = getHeight(node->right);
  return leftHeight - rightHeight;
}

int tango::getHeight(struct node *node) {
  struct node *temp = node;
  if (temp == NULL)
    return -1;
  else if (temp->prefChild1 == NULL && temp->prefChild2 == NULL)
    return 0;
  int right = getHeight(temp->prefChild1), left = getHeight(temp->prefChild2);
  if (left > right)
    return left + 1;
  else
    return right + 1;
}

// these functions are for using from second time

int main() {
  class tango t;
  int choice, num;
  while (1) {
    printf("\n--- Tango Tree Operations ---\n");
    printf("\n1. Insert");
    printf("\n2. Search");
    printf("\n3. Exit");
    printf("\nEnter your choice : ");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
      printf("\n Note \n");
      printf("\n The tree is created with the help of perfectly balanced ");
      printf(
          "\n so if u enter any number n to make it perfectly balanced tree");
      printf(
          "\nThis code will be taking it as a range of numbers from 1 to n-1");
      printf("\n");
      printf("\nEnter the number to be inserted : ");
      scanf("%d", &num);
      t.insert(1, num, t.getroot());

      break;
    case 2:
      printf("Enter your number : ");
      scanf("%d", &num);
      if (t.search(num))
        printf("The number is present in the tree\n");
      else
        printf("The number is not present in the tree\n");
      break;
    case 3:
      exit(0);
    default:
      printf("Invalid choice");
    }
  }
  t.setroot(t.insert(1, 16, NULL));
  t.inorder(t.getroot());
  t.search(2);
  printf("\n");
  t.preorder(t.getauxroot());
  printf("\n");
  t.inorder(t.getauxroot());
  printf("\n");
  t.postorder(t.getauxroot());
}

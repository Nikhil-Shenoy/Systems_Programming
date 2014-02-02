#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
	int data;
	struct Node *left;
	struct Node *right;
} Node;
Node* Node_new(int data) {
    Node * n = malloc(sizeof(Node));
    n->data = data;
    n->left = 0;
    n->right = 0;
    return n;
}
void Node_add(Node *root, Node *n) {
    int right = 0;
    if (n->data > root->data) {
        right = 1;
    }
    if (right && root->right == 0) {
        root->right = n;
        return;
    } else if (right && root->right != 0) {
        Node_add(root->right, n);
        return;
    } else if (!right && root->left == 0) {
        root->left = n;
        return;
    } else if (!right && root->left != 0) {
        Node_add(root->left, n);
    }
}
typedef struct {
    Node * root;
} Tree;
Tree * Tree_new() {
    Tree *t = malloc(sizeof(Tree));
    t->root = 0;
    return t;
}
void Tree_addNode(Tree *t, int data) {
    Node * n = Node_new(data);
    if (t->root == 0) {
        t->root = n;
        return;
    } else {
        Node_add(t->root, n);
    }
}
typedef struct splStrRet {
    char ** tokens;
    int numTokens; 
} splStrRet;

splStrRet  split_string(char * str, int n, char delim) {
    int numTokens = 1;
    int i;
    //find num of tokens
    for (i=0; i<n; i++) {
        char c = str[i];
        if (c == delim) {
            numTokens++;
        }
    }
    char ** tokenArr = calloc(sizeof(char*), numTokens);
    int * tokenLenArr = calloc(sizeof(int), numTokens);
    int curLen = 0;
    int tokenIndex = 0;
    //find the len of each token
    for (i=0; i<n; i++) {
        char c = str[i];
        if (c != delim) {
            curLen++;
        } else {
            tokenLenArr[tokenIndex] = curLen;
            curLen = 0;
            tokenIndex++;
        }
    }
    //handle end case
    tokenLenArr[tokenIndex] = curLen;
    curLen = 0;
    tokenIndex++;
    //place each token in arr
    int offset = 0;
    for (i=0; i<numTokens; i++) {
        int currTokenLen = tokenLenArr[i];
        tokenArr[i] = calloc(sizeof(char), currTokenLen + 1);
        int j;
        for (j=0; j<currTokenLen; j++) {
            tokenArr[i][j] = str[j + offset];
        }
        tokenArr[i][j] = '\0';
        offset = j+1;
    }
    //cleanup
    free(tokenLenArr);
    tokenLenArr = 0;
    splStrRet ret;
    ret.tokens = tokenArr;
    ret.numTokens = numTokens;

    return ret;
}

void println(char *str) {
  printf("%s", str);
  printf("\n");
}

int main() {
  char * str = "8,4,0,7,5,3,9,6,2,1";
  splStrRet splitData = split_string(str, 19, ',');
  int i;
  for (i=0; i<splitData.numTokens; i++) {
      int x;
      println(splitData.tokens[i]);
      sscanf(splitData.tokens[i], "%d", &x);
      printf("%d\n", x);
  }
  return 0;
}

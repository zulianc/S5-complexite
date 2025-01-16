#include <iostream>
#include <cstdint>
using namespace std;

// Définition du type noeud de l'arbre ...
typedef struct node {
    uint64_t data;
    int height;
    struct node *left;
    struct node *right;
} node;

int calculateHeight(node* n) {
    if (n == NULL) return 0;
    return n->height;
}

// Balance Factor BF
int bf(node *n) {
    int leftHeight, rightHeight;
    node* left = n->left;
    node* right = n->right;

    if (n == NULL) {
        return 0;

    } 
    if (left == NULL) {
        leftHeight = 0;

    } else {
        leftHeight = left->height;
    }
    
    if (right == NULL) {
        rightHeight = 0;

    } else {
        rightHeight = right->height;
    } 

    return leftHeight - rightHeight;
}

// Rotation LL
node* llrotation(node *n) {
    node *tp;
    tp = n->left;

    n->left = tp->right;
    tp->right = n;

    int nLeftHeight  = calculateHeight(n->left);
    int nRightHeight = calculateHeight(n->right);
    int tpLeftHeight = calculateHeight(tp->left);

    n->height  = max(nLeftHeight, nRightHeight) + 1;
    tp->height = max(tpLeftHeight, n->height) + 1;

    return tp; 
}

// Rotation RR
node* rrrotation(node *n) {
    node *tp;
    tp = n->right;

    n->right = tp->left;
    tp->left = n;

    int nLeftHeight  = calculateHeight(n->left);
    int nRightHeight = calculateHeight(n->right);
    int tpLeftHeight = calculateHeight(tp->left);

    n->height  = max(nLeftHeight, nRightHeight) + 1;
    tp->height = max(tpLeftHeight, n->height) + 1;

    return tp; 
}

// Rotation RL
node * rlrotation(node *n) {
    node* tp;
    node* right = n->right;

    n->right = llrotation(right);

    tp = rrrotation(n);
    return tp; 
}

// Rotation LR
node* lrrotation(node *n) {
    node* tp;
    node* left = n->left;

    n->left = rrrotation(left);

    tp = llrotation(n);
    return tp; 
}

// Insertion
node* insert(node *&root, uint64_t data) {
    if (!root) {
        return new node{data, 1, nullptr, nullptr};
    }

    uint64_t rootData = root->data;
    node* rootLeft  = root->left;
    node* rootRight = root->right;
    int bfRoot = bf(root);

    if (data < rootData) {
        rootLeft = insert(rootLeft, data);

        if (bfRoot == 2) {
            data < rootLeft->data ? root = llrotation(root) : root = rrrotation(root);
        }
    } else if (data > rootData) {
        rootRight = insert(rootRight, data);

        if (bfRoot == -2) {
            data < rootRight->data ? root = rrrotation(root) : root = llrotation(root);
        }
    }

    int rootLeftHeight  = calculateHeight(root->left);
    int rootRightHeight = calculateHeight(root->right);

    root->height = max(rootLeftHeight, rootRightHeight) + 1;
    return root;
}

// Suppresion
node* deleteNode(node *root, uint64_t data) {
    // cherche la valeur data dans l'arbre enraciné en root puis la supprime ...    
    // TODO
    return root;
}

    
int main() {
    node* root = NULL;
    // remplir l'arbre
    // faire des tests
    std::cout << "HelloWorld" << std::endl;
    return 0;
}
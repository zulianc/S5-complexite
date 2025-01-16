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

// Balance Factor BF
int bf(node *n) {
    node* left = n->left;
    node* right = n->right;

    if (left == NULL && right == NULL) {
        return 0;

    } else if (left == NULL) {
        int rightHeight = right->height;
        return rightHeight - 1;

    } else if (right == NULL) {
        int leftHeight = left->height;
        return leftHeight + 1;

    } else {
        int leftHeight  = left->height;
        int rightHeight = right->height;

        return leftHeight - rightHeight;
    } 
}

// Rotation LL
node* llrotation(node *n) {
    node *p;
    node *tp;
    p = n;
    tp = p->left;

    p->left = tp->right;
    tp->right = p;

    return tp; 
}

// Rotation RR
node* rrrotation(node *n) {
    node *p;
    node *tp;
    p = n;
    tp = p->right;

    p->right = tp->left;
    tp->left = p;

    return tp; 
}

// Rotation RL
node * rlrotation(node *n) {
    node *tp;
    // effectue la rotation RL
    // TODO
    return tp; 
}

// Rotation LR
node* lrrotation(node *n){
    node *tp;
    // effectue la rotation LR
    // TODO
    return tp; 
}

// Insertion
node* insert(node *root, uint64_t data){
    // insère la valeur data au bon endroit dans l'arbre enraciné en root ...
    // TODO
    return root;
}

// Suppresion
node* deleteNode(node *root, uint64_t data){
    // cherche la valeur data dans l'arbre enraciné en root puis la supprime ...    
    // TODO
    return root;
}

    
int main(){
    node * root = NULL;
    // remplir l'arbre
    // faire des tests
    std::cout << "HelloWorld" << std::endl;
    return 0;
}
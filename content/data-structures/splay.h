/**
 * Author: Loc Bui
 * Description:
 */
#pragma once
struct Node {
    Node *l, *r, *p;
    int v, size;
    Node(): l(NULL), r(NULL), p(NULL), v(0), size(0) {};
    Node(int v): l(NULL), r(NULL), p(NULL), v(v), size(1) {};
};
Node *root;
void update(Node *P) {
    P->size = (P->l ? P->l->size : 0) + (P->r ? P->r->size : 0) + 1;
}
void rightRotate(Node *P) {
    Node *T = P->l;
    Node *B = T->r;
    Node *D = P->p;
    if (D) 
        if (D->r == P) D->r = T;
        else D->l = T;
    if (B)
        B->p = P;
    T->p = D, T->r = P;
    P->p = T, P->l = B;
    update(P); update(T);
}
void leftRotate(Node *P) {
    Node *T = P->r;
    Node *B = T->l;
    Node *D = P->p;
    if (D) 
        if (D->r == P) D->r = T;
        else D->l = T;
    if (B)
        B->p = P;
    T->p = D, T->l = P;
    P->p = T, P->r = B;
    update(P); update(T);
}
// Make T root and Balance tree 
void Splay(Node *T) {
    while (true) {
        Node *p = T->p;
        if (!p) break;
        Node *pp = p->p;
        if (!pp) {  //Zig
            if (p->l == T) rightRotate(p);
            else leftRotate(p);
            break;
        }
        if (pp->l == p) {
            if (p->l == T) {  //ZigZig
                rightRotate(pp);
                rightRotate(p);
            } else {  //ZigZag
                leftRotate(p);
                rightRotate(pp);
            }
        } else {
            if (p->l == T) {  //ZigZag
                rightRotate(p);
                leftRotate(pp);
            } else {  //ZigZig
                leftRotate(pp);
                leftRotate(p);
            }
        }
    }
    root = T;
}
// Insert to the right of the root, and return reference to the new created node
Node *Insert(int v) {
    Node *newNode = new Node(v);
    if (!root) {
        root = newNode;
        return newNode;
    }
    Node *R = root->r;
    root->r = newNode, newNode->p = root;
    if (R) newNode->r = R, R->p = newNode;
    update(newNode);
    update(root);
    return newNode;
}
// Delete v
bool Erase(Node *node) {
    Splay(node);
    Node *L = node->l;
    Node *R = node->r;

    if (L) L->p = NULL;
    if (R) R->p = NULL;
    free(node);

    if (!L) return root = R, true;
    if (!R) return root = L, true;

    while (L->r) L = L->r;
    Splay(L);
    root->r = R;
    update(root);
    
    return true;
}
// Find the node at position p and make it root (position start from 1)
void Find(int p) {
    Node *node = root;
    while (true) {
        if (node->l) {
            if (node->l->size >= p) {
                node = node->l;
                continue;
            } else 
                p -= node->l->size;
        }
        if (p == 1) break;
        p -= 1;
        if (node->r) node = node->r;
        else break;
    } 
    Splay(node);
}
void Inorder(Node *R) {
    if (!R) return;
    Inorder(R->l);
    printf("%d ", R->v);
    Inorder(R->r);
}
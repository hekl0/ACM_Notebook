/**
 * Author: Codeforces
 * Description:
 */
#pragma once
struct Node {
    Node *l;
    Node *r;
    Node *p;
    int v, size;
    Node(): l(NULL), r(NULL), p(NULL), v(0), size(0) {};
    Node(int v): l(NULL), r(NULL), p(NULL), v(v), size(1) {};
};
Node *root;
void update(Node *P) {
    P->size = P->l->size + P->r->size + 1;
}
void rightRotate(Node *P) {
    Node *T = P->l;
    Node *B = T->r;
    Node *D = P->p;
    if (D) {
        if (D->r == P)
            D->r = T;
        else
            D->l = T;
    }
    if (B)
        B->p = P;
    T->p = D;
    T->r = P;

    P->p = T;
    P->l = B;

    update(P); update(T);
}
void leftRotate(Node *P) {
    Node *T = P->r;
    Node *B = T->l;
    Node *D = P->p;
    if (D) {
        if (D->r == P)
            D->r = T;
        else
            D->l = T;
    }
    if (B)
        B->p = P;
    T->p = D;
    T->l = P;

    P->p = T;
    P->r = B;

    update(P); update(T);
}

// Make T root and Balance tree 
void Splay(Node *T) {
    while (true) {
        Node *p = T->p;
        if (!p) break;
        Node *pp = p->p;
        if (!pp)  //Zig
        {
            if (p->l == T)
                rightRotate(p);
            else
                leftRotate(p);
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
void Insert(int v) {
    if (!root) {
        root = new Node(v);
        return;
    }
    Node *P = root;
    while (true) {
        if (P->v == v) break;  // not multiset
        if (v < (P->v)) {
            if (P->l)
                P = P->l;
            else {
                P->l = new Node(v);
                P->l->p = P;
                P = P->l;
                update(P->p);
                break;
            }
        } else {
            if (P->r)
                P = P->r;
            else {
                P->r = new Node(v);
                P->r->p = P;
                P = P->r;
                update(P->p);
                break;
            }
        }
    }
    Splay(P);
}
void Inorder(Node *R) {
    if (!R) return;
    Inorder(R->l);
    printf("v: %d ", R->v);
    if (R->l) printf("l: %d ", R->l->v);
    if (R->r) printf("r: %d ", R->r->v);
    puts("");
    Inorder(R->r);
}
// Find v and make v root
Node *Find(int v) {
    if (!root) return NULL;
    Node *P = root;
    while (P) {
        if (P->v == v)
            break;
        if (v < (P->v)) {
            if (P->l)
                P = P->l;
            else
                break;
        } else {
            if (P->r)
                P = P->r;
            else
                break;
        }
    }
    Splay(P);
    if (P->v == v)
        return P;
    else
        return NULL;
}
// Delete v
bool Erase(int v) {
    Node *N = Find(v);
    if (!N) return false;
    Node *L = N->l;
    Node *R = N->r;

    L->p = NULL;
    R->p = NULL;
    free(N);

    while (L->r) L = L->r;
    Splay(L);
    root->r = R;
    update(root);
    
    return true;
}
int main() {
    while (true) {
        int t;
        scanf("%d", &t);
        if (t != 0 && t != -1)
            Insert(t);
        else if (t == 0) {
            scanf("%d", &t);
            if (!Find(t))
                printf("Couldn't Find %d!\n", t);
            else
                printf("Found %d!\n", t);
        } else {
            scanf("%d", &t);
            if (Erase(t))
                printf("Deleted %d!\n", t);
            else
                printf("Couldn't Find %d!\n", t);
        }
        if (root) printf("root: %d\n", root->v);
        Inorder(root);
    }
}
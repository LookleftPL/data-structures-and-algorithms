#include <iostream>

using namespace std;
typedef int Telement;
typedef struct Node
{
    Telement info;
    Node * left;
    Node * right;
};
typedef Node *PNode;

class BinaryTree
{
protected:
    PNode T;
public:
    BinaryTree() {
        T = NULL;
    }
    ~BinaryTree() {
        MAKENULL(T);
    }
    PNode PARENT(PNode n) {
        if (n == T) {
            return NULL;
        }
        return PARENT1(n,T);

    }
    PNode PARENT1(PNode n,PNode T) {
        if (T == NULL) {
            return NULL;
        }
        if (T->left == n || T->right == n) {
            return T;
        }
        PNode temp = PARENT1(n, T->left);
        if (temp != NULL) {
            return temp;
        }
        return PARENT1(n,T->right);
    }
    PNode LEFT_CHILD(PNode n) {
        return n->left;
    }
    PNode RIGHT_CHILD(PNode n) {
        return n->right;
    }
    Telement GetLabel(PNode n) {
        return n->info;
    }
    PNode BuildTree1(int m) {
        if (m==0)
            return NULL;
        Telement value;
        cout<<"Podaj wartosc dla wezla"<<endl;
        cin>>value;
        Node* n = new Node();
        n->info = value;
        int left_count = m/2;
        int right_count = m - left_count - 1;
        n->left = BuildTree1(left_count);
        n->right = BuildTree1(right_count);
        return n;
    }
    void BuildTree(int m) {
        T = BuildTree1(m);
    }
    PNode ROOT() {
        return T;
    }
    void MAKENULL(PNode p) {
        if (p != NULL) {
            MAKENULL(p->left);
            MAKENULL(p->right);
            delete p;
            p = NULL;
        }
    }
    void PreOrder(PNode t) {
        if (t != NULL) {
            cout<<GetLabel(t)<<" ";
            PreOrder(t->left);
            PreOrder(t->right);
        }
    }
    void InOrder(PNode t) {
        if (t != NULL) {
            InOrder(t->left);
            cout<<GetLabel(t)<<" ";
            InOrder(t->right);
        }
    }
    void PostOrder(PNode t) {
        if (t != NULL) {
            PostOrder(t->left);
            PostOrder(t->right);
            cout<<GetLabel(t)<<" ";
        }
    }
};

int main() {
    BinaryTree drzewo;
    drzewo.BuildTree(9); // Budujemy drzewo
    cout<<drzewo.GetLabel(drzewo.ROOT())<<endl; // wartosc korzenia
    cout<<drzewo.GetLabel(drzewo.LEFT_CHILD(drzewo.ROOT()))<<endl; // lewe dziecko korzenia
    cout<<drzewo.GetLabel(drzewo.RIGHT_CHILD(drzewo.ROOT()))<<endl; // prawe dziecko korzenia
    cout<<drzewo.GetLabel(drzewo.PARENT(drzewo.RIGHT_CHILD(drzewo.ROOT())))<<endl;
    cout<<drzewo.GetLabel(drzewo.PARENT(drzewo.RIGHT_CHILD(drzewo.LEFT_CHILD(drzewo.ROOT()))))<<endl;
    drzewo.PreOrder(drzewo.ROOT());
    cout<<endl;
    drzewo.InOrder(drzewo.ROOT());
    cout<<endl;
    drzewo.PostOrder(drzewo.ROOT());
    cout<<drzewo.GetLabel(drzewo.PARENT(drzewo.LEFT_CHILD(drzewo.LEFT_CHILD(drzewo.RIGHT_CHILD(drzewo.ROOT())))))<<endl;
    return 0;
}
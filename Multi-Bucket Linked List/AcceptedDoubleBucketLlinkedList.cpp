#include <iostream>
using namespace std;
class node
{
public:
    int a, b;
    node *z;
    node(int p, int q, node *r)
    {
        a = p;
        b = q;
        z = r;
    }
    node(int p, int q)
    {
        a = p;
        b = q;
    }
    node(){};
    static node* first;

    static void pt()
    {
        node *i = first;
        while (i != NULL)
        {
            cout << "[" << i->a << " " << i->b << "],";
            i = i->z;
        }
        cout << "\n";
    }
        
    static void insert(int x)
    {
        if (first == NULL){//case 1
            node *newNode = new node(x, -1, NULL);
            first = newNode;
            return;
        }

       // Find the correct position for the new node
        node* current = first;
        while (current->z != NULL && current->a < x && current->b < x) {
            current = current->z;
        }

        if(current->a>=x){//case 2
            if(current->b==-1){
                current->b=current->a;
                current->a=x;
                return;
            }
            node *newNode = new node(current->b, -1, current->z);
            current->b=current->a;
            current->a=x;
            current->z=newNode;
            return;
        }
        else if(current->b>=x){//case 3
            node *newNode = new node(current->b, -1, current->z);
            current->b=x;
            current->z=newNode;
            return;
        }
        else {//case 4
            if(current->b==-1){
                current->b=x;
                return;
            }
            node *newNode = new node(x, -1, NULL);
            current->z=newNode;
            return;
        }
    }
};
node* node::first = NULL;

int main()
{
    node a(74, -1), b(58, 62, &a), c(43, -1, &b), d(32, -1, &c), e(16, 26, &d);
    node::first = &e;
    node::pt(); //   [ 16 26],[ 32 -1],[ 43 -1],[ 58 62],[ 74 -1],
    node::insert(76);
    node::pt(); // [ 16 26],[ 32 -1],[ 43 -1],[ 58 62],[ 74 76],
    node::insert(77);
    node::pt(); // [ 16 26],[ 32 -1],[ 43 -1],[ 58 62],[ 74 76],[77,-1]
    
    // node a(74, -1), b(58, 62, &a), c(43, -1, &b), d(32, -1, &c), e(16, 26, &d);
    // node::first = &e;
    // node::pt(); //   [ 16 26],[ 32 -1],[ 43 -1],[ 58 62],[ 74 -1],
    // node::insert(12);
    // node::pt(); // [ 12 16],[26 -1],[ 32 -1],[ 43 -1],[ 58 62],[ 74 -1],
    // node::insert(47);
    // node::pt(); // [ 12 16],[26 -1],[ 32 -1],[ 43 -1],[ 47 58],[ 62 -1 ],[ 74 -1],
    // node::insert(41);
    // node::pt(); // [ 12 16],[26 -1],[ 32 -1],[ 41 43],[ 47 58],[ 62 -1 ],[ 74 -1],
    // node::insert(50);
    // node::pt(); // [ 12 16],[26 -1],[ 32 -1],[ 41 43],[ 47 50],[ 58 -1 ][ 62 -1 ],[ 74 -1],
}


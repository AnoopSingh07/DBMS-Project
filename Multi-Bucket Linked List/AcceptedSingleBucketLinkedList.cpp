#include <iostream>
using namespace std;
class node
{
public:
    int data;
    node *next;
    node(int p, node *q)
    {
        data = p;
        next = q;
    }
    node(int p)
    {
        data = p;
        next = NULL;
    }
    node() {}
};
node *head;
void pt()
{
    node *i;
    i = head;
    while (i != NULL)
    {
        cout << i->data << ",";
        i = i->next;
    }
    cout << "over\n";
}
void insert_begin(int y)
{
    node *k = new node();
    k->data = y;
    k->next = head;
    head = k;
}
void insert_second(int y)
{
    if (head == NULL) return;
    node *k = new node(y, head->next);
    head->next = k;
}
void insert_last(int y)
{
    node *k=new node(y);
    if(head==NULL){
        head=k;
        return;
    }
    node *last=head;
    while(last->next!=NULL){
        last=last->next;
    }
    last->next=k;
}
void insert_kth(int pos,int y)
{
    if(pos<0)return;
    if(pos==0){
        insert_begin(y);
        return;
    }
    node *atPosK=head;
    while(--pos)
    {
        if(atPosK==NULL)return;
        atPosK=atPosK->next;
    }
    node *k=new node(y,atPosK->next);
    atPosK->next=k;
}
void insert_second_last(int y)
{
    if (head == NULL) return;
    if(head->next==NULL){
        insert_begin(y);
        return;
    }
    node *k=new node(y);
    node* last_sec=new node();
    node* last=head;
    while(last->next!=NULL){
        last_sec=last;
        last=last->next;
    }
    last_sec->next=k;
    k->next=last;
}
int main()
{
    node a(41), b(82, &a), c(31, &b), d(21, &c), e(42, &d);
    head = &e;
    pt(); // 42,21,31,82,41,over
    insert_begin(36);
    pt(); // 36, 42,21,31,82,41,over
    insert_second(44);
    pt(); //  36,44,42,21,31,82,41,over
    insert_last(34);
    pt();              // 36,42,21,31,82,41,34,over
    insert_kth(5, 12); // insert at 5th location
    pt();              // 36,42,21,31,82,12,41,34,over
    insert_second_last(11);
    pt(); // 36,42,21,31,82,12,41,11,34,over
}
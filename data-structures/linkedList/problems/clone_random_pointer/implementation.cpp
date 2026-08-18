#include <bits/stdc++.h>
using namespace std;
struct Node { int value; Node* next; Node* random; };
Node* copyRandomList(Node* head) { if(!head)return nullptr; for(Node*p=head;p;){Node*n=new Node{p->value,p->next,nullptr};p->next=n;p=n->next;} for(Node*p=head;p;p=p->next->next)if(p->random)p->next->random=p->random->next; Node*copy=head->next; for(Node*p=head;p;){Node*n=p->next;p->next=n->next;if(n->next)n->next=n->next->next;p=p->next;} return copy; }

#include <bits/stdc++.h>
using namespace std;
struct Node { int value; Node* next; Node* bottom; };
static Node* mergeBottom(Node* a, Node* b) { Node dummy{0,nullptr,nullptr}; Node* t=&dummy; while(a&&b){if(a->value<=b->value){t->bottom=a;a=a->bottom;}else{t->bottom=b;b=b->bottom;} t=t->bottom; t->next=nullptr;} t->bottom=a?a:b; return dummy.bottom; }
Node* flatten(Node* head) { if(!head||!head->next)return head; head->next=flatten(head->next); return mergeBottom(head,head->next); }

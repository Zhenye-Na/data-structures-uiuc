#include <iostream>
using namespace std;


struct node
{
	int val;
	node * prev;
	node * next;
};



class List
{
public:
	node * head;

	List(){
		head=NULL;
	}
	~List(){
		node * temp=head;
		while(head!=NULL){
			head=head->next;
			delete temp;
			temp=head;
		}
		head=NULL;
	}

	void insert(int val){
		if(head==NULL){
			head=new node;
			head->val=val;
			head->next=NULL;
			head->prev=NULL;
		}
		else {

			node * temp =new node;
			temp->val=val;
			temp->next=head;
			head->prev=temp;
			temp->prev=NULL;
			head=temp;
		}

	}
	void oddprint(){
		cout<<endl;
		node * temp=head;
		while(temp!=NULL){
			temp=temp->next->next;
			cout<<temp->val<<" ";
			
		}
		cout<<endl;
	}

};


/*
*	This function should print a linked list in a odd fashion (fix it so it doesn't segfault in a reasonable way)
*
*/

int main (){
	List list;

	for (int i = 0; i < 10; ++i)
	{
		list.insert(i);
	}
	list.oddprint();

}


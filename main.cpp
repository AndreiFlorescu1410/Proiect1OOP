#include <iostream>
#include <fstream>
using namespace std;

class nod{
    int i;
public:
    int GetI() { return i;};
    void SetI(int x) { i=x;};
};

class lista : public nod{
    lista *next, *prev;
public:
    lista* GetNext() { return next;}
    void SetNext(lista* nod) { next = nod;}
    lista* GetPrev() { return prev;}
    void SetPrev(lista* nod) { prev = nod;}

    friend void insert_final(lista* &c, int x);
    friend ostream& operator <<(istream& i, lista* c);

    lista();
    ~lista();
};

lista::lista()
{
    next = NULL;
    prev = NULL;
}
void insert_final(lista* &c, int x)
{
    lista* new_element = new lista;
    new_element->SetI(x);
    if (c == NULL)
        c=new_element;
    else if (c->GetNext() == NULL)
    {
        c->SetNext(new_element);
        c->SetPrev(new_element);
        new_element->SetPrev(c);
        new_element->SetNext(c);
        c=new_element;
    }
    else
    {
        lista* after_new = c->GetNext();
        c->SetNext(new_element);
        new_element->SetPrev(c);
        new_element->SetNext(after_new);
        after_new->SetPrev(new_element);
        c = new_element;
    }
}


ostream& operator <<(ostream& i, lista* c)
{
    i<<c->GetI()<<" ";
    return i;
}
int main()
{
    ifstream f("input.in");
    int x,n=0;
    lista *c  = NULL, *l=c;
    while(f>>x)
    {
        insert_final(c,x);
        n++;
    }

    c = c->GetNext();
    for(int i = 0; i < n; i++)
    {
        cout<<(c);
        c = (c->GetNext());
    }

    return 0;
}

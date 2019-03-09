#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <conio.h>

using namespace std;

#define antet {system("CLS");cout<<"       Proiect 1 OOP -- liste circulare(alocate dinamic) -- Florescu Andrei Gr. 212         "<<endl<<endl;}

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

    friend ostream& operator <<(istream& i, lista* c);
    friend istream& operator >>(istream& i, lista* c);

    lista();
    ~lista();
};

lista::lista()
{
    next = NULL;
    prev = NULL;
}


istream& operator >>(istream& i, lista* c)
{
    int x;
    i >> x;
    c->SetI(x);
    return i;
}

ostream& operator <<(ostream& o, lista* c)
{
    o << c->GetI() << " ";
    return o;
}

void insert_final(lista* &c, lista* new_element)
{
    if (c == NULL)
        c = new_element;
    else if (c->GetNext() == NULL)      //cazul in care nodul cap este singurlui din liste si trebuie formata lista circulara
    {
        c->SetNext(new_element);        //formez conexiune tip "cerc"
        c->SetPrev(new_element);
        new_element->SetPrev(c);
        new_element->SetNext(c);
        c = new_element;                //noul element devine capul listei
    }
    else
    {
        lista* after_new = c->GetNext(); //initilizez nodul ce urmeaza sa fie precedentul noului nod
        c->SetNext(new_element);         //inlocuiesc nodul urmator(al nodului curent) cu noul nod
        new_element->SetPrev(c);
        new_element->SetNext(after_new);
        after_new->SetPrev(new_element);
        c = new_element;                 //noul element devine capul listei
    }
}

void insert_after_x(lista* c,lista* new_element, int x)
{
    while(c->GetI() != x)            //caut nodul cu valorea x
        c = c->GetNext();
    lista* after_new = c->GetNext(); //initilizez nodul ce urmeaza sa fie precedentul noului nod
    c->SetNext(new_element);         //inlocuiesc nodul urmator(al nodului curent) cu noul nod
    new_element->SetPrev(c);
    new_element->SetNext(after_new);
    after_new->SetPrev(new_element);
}

void read(lista* &c, int &n) //meniul de citire
{
    antet
    cout << "Alegeti metoda de citire a listei: " << endl;
    cout << "1. Fisier" << endl;
    cout << "2. Tastatura" << endl;
    int caz;
    cin >> caz;
    switch (caz)
    {
    case 1:
    {
        while  (1)
        {
            antet
            cout<<"Dati numele fisierului: ";
            char txt_name[100];
            cin>>txt_name;          //citesc numele fisierului
            ifstream f(txt_name);
            if(f.is_open() == 0)    //testez daca exista fisierul citit
            {
                antet
                cout<<"Nu am putut deschide fisierul."<<endl;
                cout<<"Apasa orice tasta pentru a te intoarce..."<<endl;
                getch();
            }
            else
            {
                lista* new_element = c;
                c = NULL;
                while(f>>new_element)           //citesc valoarea nodului
                {
                    insert_final(c,new_element);  //il adaug la "finalul" listei
                    new_element = new lista;    //reinitializez noul element
                    n++;                        //incrementez numarul nodurilor din lista
                }
                break;

            }
        }
        break;
    }
    case 2:
    {
        while (1)
        {
            antet
            cout << "Dati numarul de elemente din lista: ";
            cin >> n;
            cout << "Dati elementele listei: ";
            lista* new_element = c;
            c = NULL;
            for (int i = 0; i < n; i++)
            {
                cin >> new_element;         //citesc valoarea nodului
                insert_final(c,new_element);  //il adaug la "finalul" listei
                new_element = new lista;    //reinitializez noul element
            }
            break;

        }

        break;
    }
    default:
    {
        antet
        cout<<"Optiune inexistenta."<<endl;
        cout<<"Apasa orice tasta pentru a te intoarce..."<<endl;
        getch();
        read(c,n);
        break;
    }
    }
}

void afisare(lista* first, int n) //afiseaz lista care incepe de la nodul "first"
{
    antet
    for(int i = 0; i < n; i++)
    {
        cout << first;
        first = (first->GetNext());
    }
    cout<<endl<<"Apasa orice tasta pentru a te intoarce..."<<endl;
    getch();
}

void menu(lista* first, int n) //meniul principal al programului
{
    antet
    cout << "Meniu: " << endl;
    cout << "1. Afiseaza lista" << endl;
    cout << "2. Adauga un nou element" << endl;
    cout << "3. Sterge un element" << endl;
    cout << "4. Inverseaza legaturile listei" << endl;
    cout << "5. Elimina elemente din k in k" << endl;
    cout << "6. Concateneaza lista curenta cu una noua" << endl;
    cout << "9. Iesi din program" << endl;

    int caz;
    cin>>caz;

    switch (caz)
    {
    case 1:
    {
        afisare(first,n);
        break;
    }
    case 2:
    {
        while (1) { //loop infinit pentru a trata cazul in care se introduce un numar ce nu face parte din meniu
        antet
        cout << "1. Adauga la finalul listei" << endl;
        cout << "2. Adauga dupa nodul 'x'" << endl;

        int caz2;
        cin >> caz2;

        antet
        lista *new_element = new lista;
        cout << "Dati valoarea noului nod: "; cin >> new_element; //citesc noul nod, inainte de a intra in switch, pentru a economisi memorie

        lista* ultim = first->GetPrev(); //first->GetPrev() este, in cazul de fata, ultimul element din couda
        switch (caz2)
        {
        case 1:
        {
            insert_final(ultim,new_element);
            n++;
            cout << endl << "Nod adaugat cu succes." << endl ;
            cout<<endl<<"Apasa orice tasta pentru a te intoarce..."<<endl;
            getch();
            break;
        }
        case 2:
        {
            int x;
            cout << "Dati valoarea nodului 'x': "; cin >> x;
            insert_after_x(ultim, new_element, x);
            n++;
            cout << endl << "Nod adaugat cu succes." << endl ;
            cout<<endl<<"Apasa orice tasta pentru a te intoarce..."<<endl;
            getch();
            break;
        }
        default:
        {
            antet
            cout<<"Optiune inexistenta."<<endl;
            cout<<"Apasa orice tasta pentru a te intoarce..."<<endl;
            getch();
            break;
        }
        }
        if (caz2 == 1 || caz2 == 2) //conditie necesare pentru a iesii din loop-ul infinit
            break;
        }
    }
    case 3:
    {

    }


    }
    getch();
    menu(first, n);
}




int main()
{
    ifstream f("input.in");
    int x,n=0,caz;
    lista *c  = new lista, *new_element = new lista, *first = c;

    read(c,n);
    menu(first, n);














//    while(f>>new_element)
//    {
//        insert_final(c,new_element);
//        new_element = new lista;
//        n++;
//    }
    c = first;
    for(int i = 0; i < n; i++)
    {
        cout << c;
        c = (c->GetNext());
    }

    return 0;
}

#include <iostream>
using namespace std;
class base_parent{
    private:
        int id;
    public:
        virtual void display(){
            cout << "base parent called\n";
        }
};
class derived_child : public base_parent{
    private:
        int id2;
    public:
        void display(){
            cout << "derived chiled ccalleed\n";
        }
};

int main(){
    base_parent b1;
    b1.display();
    derived_child d1;
    d1.display();
    base_parent* p1;
    p1 = &d1;
    p1->display();
    return 0;
}
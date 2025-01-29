
class A{
private:
    struct Mystruct{
        int x;
        int y;
    };
public:
    Mystruct get() const {
        return Mystruct{1,2};
    }

    friend class B;
};

class B{
private:
    A::Mystruct st; // Allowed due to friend declaration
public:
    B(const A& a) : st(a.get()){}
};

int main(){
    A a;
    B b(a);
    return 0;
}
#include <chrono>

// Virtual method
class Base{
public:
    virtual void count(){};
};

class Derived : public Base {
public:
    void count() override {
        count_++;
    }

private:
    size_t count_=0;
};

// CRTP version
template <typename DerivedCRTP>
class BaseCRTP {
    void count(){
        static_cast<DerivedCRTP*>(this)->count();
    }
};

class DerivedCRTP : BaseCRTP<DerivedCRTP>{
    void count(){
        count_++;
    }

private:
    size_t count_=0;
};

void RunNormal(Base* interface){
    constexpr unsigned N = 4000;
    for(unsigned i=0; i<N; ++i){
        for(unsigned j=0; j<i; ++j){
            interface->count(j);
        }
    }
}

template <typename T>
void RunCRTP(BaseCRTP<T>* obj){
    constexpr unsigned N = 4000;
    for(unsigned i=0; i<N; ++i){
        for(unsigned j=0; j<i; ++j){
            obj->count();
        }
    }
}

template <typename T, typename F>
void BenchMark(T& obj, F f, std::string name){
    auto start = std::chrono::high_resolution_clock::now();
    f(&obj);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << name << "  " << duration.count() << " microseconds" << std::endl;
}

int main(){
    DerivedCRTP crtp{};
    Derived nocrtp{};

    BenchMark(crtp, RunCRTP<DerivedCRTP>, "CRTP");
    BenchMark(nocrtp, RunNormal, "Normal");
}
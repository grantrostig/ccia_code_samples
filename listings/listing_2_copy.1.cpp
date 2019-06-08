#include <thread>

void do_something(int& i)
{
    ++i;
}

void f( int & x ) {
    for (int i = 0; i < 1'000'000; ++i) {
       do_something(x);
    }
}

struct func
{
    int& i;

    func(int& i_):i(i_){}

    void operator()()
    {
        for(unsigned j=0;j<1000000;++j)
        {
            do_something(i);
        }
    }
};


void procedure()
{
    int some_local_state {};
      // todo: performance question: does my_thread1 copy f?
      // can it inline call to f?
      // when invoked by thread will it be done through a pointer, or directly?
    std::thread my_thread1(f, std::ref(some_local_state));
    my_thread1.join();

    func my_func(some_local_state);
    // copies my_func to new thread according to Williams and inline with how std:: bind works.
    std::thread my_thread2(my_func);
    my_thread2.join();
}

int main()
{
    procedure();
}

#include <iostream>
#include <thread>
#include <unistd.h>
using namespace std;

void output(int i)
{
   sleep(1);
   cout << std::this_thread::get_id() << endl;
}

int main()
{

    for (uint8_t i = 0; i < 10; i++)
    {
        thread t(output, i);
        t.detach(); 
    }
    sleep(1);
    return 0;
}

#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex
#include <unistd.h>
using namespace std;

int counter = 0; // non-atomic counter
std::mutex mtx;           // locks access to counter

void increase() 
{
    sleep(1);
	for (int i = 0; i < 1000; ++i) 
	{
	//	if (mtx.try_lock()) 
		{   //only increase if currently not locked:
                ++counter;
	//		mtx.unlock();
		}
      //  else
        //    cout<<"lock"<<endl;
	}
}

int main() 
{
	std::thread threads[10];
	for (int i = 0; i < 10; ++i)
		threads[i] = std::thread(increase);

	for (int i =0;i<10;++i) 
    {
        cout<<"线程"<<i<<"的id "<<threads[i].get_id()<<endl;
        threads[i].join();
    }
	//sleep(2);
	std::cout << counter <<std::endl;
	return 0;
}

/*文本加密
 *该文件用于测试读写文件使用多线程的效果，生成文件放在.file文件夹，为.c文件，加密部分已经被注释掉了
 *运行时只需执行shell脚本
demo:
 *       ./rw_txt.sh
 */
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>
#include <unistd.h>
#include <pthread.h>
 
using namespace std;

struct dString
{
    string* file_r_ptr;
    string* file_w1_ptr;
    string* file_w2_ptr;
};

void rw1(string &f0,string& f1)
{
	ifstream file0;
	file0.open(f0.c_str());
	string s;
	ofstream in;
	in.open(f1.c_str(),ios::trunc); //ios::trunc表示在打开文件前将文件清空,由于是写入,文件不存在则创建
	
	while(getline(file0,s))//逐行读取数据并存于s中，直至数据全部读取
	{
            cout<<s<<endl;
        for(size_t i=0;i<s.size();i++)
			s[i]=s[i]+1;
		reverse(s.begin(),s.end());
		in<<s<<endl;
	}
	return ;
}
void* rw1(void* arg)
{
	dString* file_ptr=(dString*) arg;
        string f0=*(file_ptr->file_r_ptr);
        string f1=*(file_ptr->file_w1_ptr);
        cout<<"读"<<f0<<endl;
        cout<<"写"<<f1<<endl;
	rw1(f0,f1);
	return NULL;
}
void rw2(string &f0,string & f1)
{
	ifstream file0;
	file0.open(f0.c_str());
	string s;
	ofstream in;
	in.open(f1.c_str(),ios::trunc); //ios::trunc表示在打开文件前将文件清空,由于是写入,文件不存在则创建
	
	while(getline(file0,s))//逐行读取数据并存于s中，直至数据全部读取
	{
            cout<<1;
        reverse(s.begin(),s.end());
		for(size_t i=0;i<s.size();i++)
			s[i]=s[i]-1;
		in<<s<<endl;
	}
	return ;
}
void* rw2(void* arg)
{
	dString* file_ptr=(dString*) arg;
        string f0=*(file_ptr->file_r_ptr);
        string f1=*(file_ptr->file_w2_ptr);
        cout<<"read "<<f0<<endl;
        cout<<"write " <<f1<<endl;
        rw2(f0,f1);
        return NULL;
}

 
int main (int argc,char* argv[])

{
	pthread_t thread1,thread2;
	string f0=argv[1];
	string f1=argv[2];
        string f2=argv[3];
        struct dString file_in_out;//这个结构用于传参
        file_in_out.file_r_ptr=&f0;
        file_in_out.file_w1_ptr=&f1;
        file_in_out.file_w2_ptr=&f2;

	int t1=clock();
        string f11="./file/对比1.c";
        string f12="./file/对比2.c";
	rw1(f0,f11);
	rw2(f0,f12);
	double tf=(clock()-t1)/1000.0;
	
	t1=clock();
	int rc1=pthread_create(&thread1,NULL,rw1,(void*)(&file_in_out));
	if (rc1){                
         cout << "Error:无法创建线程1," << rc1 << endl;
         exit(-1);
      }   
	int rc2=pthread_create(&thread2,NULL,rw2,&file_in_out);//最好像上面那样用类型转换
	if (rc2){                
         cout << "Error:无法创建线程2," << rc2 << endl;
         exit(-1);
      }   
        	
	double tp=(clock()-t1)/1000.0;//这样测试线程时间是不准的
	cout<<"普通函数执行时间："<<tf<<"ms"<<endl;

        cout<<"main退出。"<<endl;
        pthread_exit(NULL);
        return 0;
}
	

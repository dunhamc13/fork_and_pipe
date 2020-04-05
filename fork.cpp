#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
using namespace std;

int main()
{
  cout << "hello world" << endl;
  int pipeFD[2];
  pipe(pipeFD);



  int returnPid = fork();
  if (returnPid == 0)
  {
    close(pipeFD[1]);//close right side of pipe
    char buf[256];//create buffer
    sleep(5);
    int n = read(pipeFD[0], buf, 256);//read is sys call
    buf[n] = '\0';
    cout << buf << endl;
    /*
    int myPid = getpid();
    cout << "I am the child, my pid is " << myPid <<  endl;
    sleep(5);
    cout << "I am the child and i woke up" << endl;
  */
    }
  else
  {
    int myPid = getpid();
    cout << "i am the parent, my pid is " << myPid << endl;
    close(pipeFD[0]);//close read side of pipe
    dup2(pipeFD[1], 2);
    //cin cout cerr when a process starts for c++ stdin etc in other langs
    //these are 0 1 2 on the console device... so dup2 copies to cerr if 2
    //or 1 if cout
    cerr << "Hello, Child stay well" << endl;

    
    wait( NULL );
    sleep(2);
    cout << "child must have woken up" << endl;
  }
}

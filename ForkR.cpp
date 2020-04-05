#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <cmath>
#include <iostream>
using namespace std;

void print(int start, int numForks)
{
  //make pipe
  int pipeFD[2];
  pipe(pipeFD);

  //check if done
  if (start == numForks)
  {
    cout << "No More Forking!" << endl;
    return;
  }//end gaurd

  //not done
  else 
  {
    //create new process
    int returnPid = fork();

    //if child process, do parent and add one
    if (returnPid == 0)
    {
      //close pipe and read from it
      close(pipeFD[1]);//close right side of pipe
      char buf[256];//create buffer
      int n = read(pipeFD[0], buf, 256);//read is sys call
      buf[n] = '\0';
      
      //get pid and output message / pipe from parent
      int mypid = getpid();
      cout << "Child: " << mypid <<  " iteration: " << start << " of " 
        << numForks << " :Pipe from parent " << buf << endl;
      //sleep(5);
      //recursive call
      print(start + 1, numForks);

    }

    //must be parent
    else
    {
      int mypid = getpid();
      //make message close pipe
      close(pipeFD[0]);//close read side of pipe
      dup2(pipeFD[1], 1);
      //cin cout cerr when a process starts for c++ stdin etc in other langs
      //these are 0 1 2 on the console device... so dup2 copies to cerr if 2
      //or 1 if cout
      cout << "Child, mypid is " << mypid << endl;
      cout << "Parent " << mypid <<  " iteration: " << start << " of " 
        << numForks << endl;
     // print(start + 1, numForks);
    }

  }
}//end print

int main(int argc, char *argv[])
{
  if ((argc < 2 || argc > 2))
  {
    cout << "Needs::"  << argv[0] << " #leaves " << endl;
    exit ( -1 );
  }// end if

  cout << "Trying Fork with Recursion" << endl;
  int numForks = atoi(argv[1]);
  cout << "How many times? " << numForks << endl;
  double log = log2(6);
  int number = (int)log;
  cout << number << endl;
  print(0,numForks);

 // int pipeFD[2];
 // pipe(pipeFD);


/*
  int returnPid = fork();
  if (returnPid == 0)
  {
    close(pipeFD[1]);//close right side of pipe
    char buf[256];//create buffer
    sleep(5);
    int n = read(pipeFD[0], buf, 256);//read is sys call
    buf[n] = '\0';
    cout << buf << endl;
    
    int myPid = getpid();
    cout << "I am the child, my pid is " << myPid <<  endl;
    sleep(5);
    cout << "I am the child and i woke up" << endl;
  
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
  */
}

// threadtest.cc 
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield, 
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"

// testnum is set in main.cc
int testnum = 1;

//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread 
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------

void
SimpleThread(int arg)
{
    int num;
    /* modify*/
    printf("enter SimpleThread\n");
    /**/
    for (num = 0; num < 5; num++) {
	printf("threadID %d userID %d looped %d times\n",currentThread->get_tid() ,currentThread->get_uid() ,num);
        currentThread->Yield();
    }
}

//----------------------------------------------------------------------
// ThreadTest1
// 	Set up a ping-pong between two threads, by forking a thread 
//	to call SimpleThread, and then calling SimpleThread ourselves.
//----------------------------------------------------------------------

void
ThreadTest1()
{
    DEBUG('t', "Entering ThreadTest1");

    Thread *t = new Thread("forked thread");
    Thread *t1 = new Thread("forkded thread");
    Thread *t2 = new Thread("forkded thread");
    Thread *t3 = new Thread("forkded thread");
    t->Fork(SimpleThread,1);
    t1->Fork(SimpleThread,1);
    t2->Fork(SimpleThread,1);
    t3->Fork(SimpleThread,1);
}
void 
ThreadTest2()
{
     DEBUG('t',"Entering ThreadTest2");
     for (int i=0;i<129;i++)
     {
        Thread *t = new Thread("forked thread");
        printf("threadID %d userID %d\n",t->get_tid() ,t->get_uid());
     }
}
void 
print_status(int arg)
{
   // printf("threadID 0 status : running\n");  //main线程理解成一直在运行，手动输出其运行信息
    printf("threadID %d status : runnning\n",currentThread->get_tid());
    int j = currentThread->get_tid();
    for (int i = 1;i<128;i++)
    {
        if (i!=j && ThreadID[i]==1)
        {
            printf("threadID %d status : ready\n",i);
        }
    }
    printf("\n");
}
void 
ThreadTest3()
{
    DEBUG('t',"Entering ThreadTest3");
    Thread *t1 = new Thread("forkded thread");
    Thread *t2 = new Thread("forkded thread");
    Thread *t3 = new Thread("forkded thread");
    t1->Fork(print_status,1);
    t2->Fork(print_status,1);
    t3->Fork(print_status,1);
}


//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------

void
ThreadTest()
{
    switch (testnum) {
    case 1:
	ThreadTest1();
	break;
    case 2:
    ThreadTest2();
    break;
    case 3:
    ThreadTest3();
    break;
    default:
	printf("No test specified.\n");
	break;
    }
}


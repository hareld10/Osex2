//////#include <iostream>
//////#include <list>
//////
//////#include "uthreads.h"
//////#define SECOND 1000000
//////#define GRN "\e[32m"
//////#define RED "\x1B[31m"
//////#define RESET "\x1B[0m"
//////
//////void error()
//////{
//////    printf(RED "ERROR - wrong id returned\n" RESET);
//////    exit(1);
//////}
//////
//////void thread1(void){
//////    std::cout << "Func1!" << std::endl;
//////    int tmp = uthread_get_tid();
////////    uthread_block(tmp);
//////    for (;;);
//////}
//////
//////void thread2(void){
//////    std::cout << "Func2!" << std::endl;
//////    std::flush(std::cout);
//////
//////
//////    for( ; ;) { }
//////}
//////
//////void func3(void){
//////    std::cout << "Func3!" << std::endl;
//////    std::flush(std::cout);
//////
//////
//////    for( ; ;) { }
//////}
//////
//////void wait_next_quantum()
//////{
//////    int quantum = uthread_get_quantums(uthread_get_tid());
//////    while (uthread_get_quantums(uthread_get_tid()) == quantum)
//////    {}
//////    return;
//////}
//////
//////
//////int main(){
//////    std::cout << GRN "Test 1:    " RESET <<std::endl;
//////    uthread_init(10);
//////    if (uthread_spawn(thread1) != 1)
//////        error();
//////    if (uthread_spawn(thread2) != 2)
//////        error();
//////    if (uthread_spawn(thread2) != 3)
//////        error();
//////    if (uthread_spawn(thread1) != 4)
//////        error();
//////    if (uthread_spawn(thread2) != 5)
//////        error();
//////    if (uthread_spawn(thread1) != 6)
//////        error();
//////
//////    uthread_terminate(5);
//////    if (uthread_spawn(thread1) != 5)
//////        error();
//////
//////
//////    wait_next_quantum();
//////    wait_next_quantum();
//////
//////    uthread_terminate(5);
//////    if (uthread_spawn(thread1) != 5)
//////        error();
//////
//////    uthread_terminate(2);
//////    if (uthread_spawn(thread2) != 2)
//////        error();
//////
//////    uthread_terminate(3);
//////    uthread_terminate(4);
//////    if (uthread_spawn(thread2) != 3)
//////        error();
//////    if (uthread_spawn(thread1) != 4)
//////        error();
//////
//////    printf(GRN "SUCCESS\n" RESET);
//////    uthread_terminate(0);
//////
//////}

/**********************************************
 * Test 1: correct threads ids
 *
 **********************************************/

#include <cstdio>
#include <cstdlib>
#include "uthreads.h"

#define GRN "\e[32m"
#define RED "\x1B[31m"
#define RESET "\x1B[0m"

void halt()
{
    while (true)
    {}
}

void wait_next_quantum()
{
    int quantum = uthread_get_quantums(uthread_get_tid());
    while (uthread_get_quantums(uthread_get_tid()) == quantum)
    {}
    return;
}

void thread1()
{
    uthread_block(uthread_get_tid());
}

void thread2()
{
    halt();
}

void error()
{
    printf(RED "ERROR - wrong id returned\n" RESET);
    exit(1);
}

int main()
{
    printf(GRN "Test 1:    " RESET);
    fflush(stdout);

    uthread_init(10);
    if (uthread_spawn(thread1) != 1)
        error();
    if (uthread_spawn(thread2) != 2)
        error();
    if (uthread_spawn(thread2) != 3)
        error();
    if (uthread_spawn(thread1) != 4)
        error();
    if (uthread_spawn(thread2) != 5)
        error();
    if (uthread_spawn(thread1) != 6)
        error();

    uthread_terminate(5);
    if (uthread_spawn(thread1) != 5)
        error();


    wait_next_quantum();
    wait_next_quantum();

    uthread_terminate(5);
    if (uthread_spawn(thread1) != 5)
        error();

    uthread_terminate(2);
    if (uthread_spawn(thread2) != 2)
        error();

    uthread_terminate(3);
    uthread_terminate(4);
    if (uthread_spawn(thread2) != 3)
        error();
    if (uthread_spawn(thread1) != 4)
        error();

    printf(GRN "SUCCESS\n" RESET);
    uthread_terminate(0);

}

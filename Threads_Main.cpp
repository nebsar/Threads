/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Threads_Main.cpp
 * Author: Eagleye
 *
 * Created on September 8, 2018, 6:58 PM
 */

#include <cstdlib>
#include <thread>
#include <iostream>
#include <string>

using namespace std;

/*
 * 
 */

void funciton_1() {
    cout << "Hello World!" << endl;
}

struct Functor {
public:

    operator()(string msg) { // if you use std::move(argument) you cannot use string& msg, you have to use string msg.
        msg = "The message is change to something else!";
        // for (int i = 0; i>-100; i--)
        cout << "from child thread : " << msg << endl;
        cout<<"child thread ID : " <<std::this_thread::get_id()<<endl;
    }
};

int main(int argc, char** argv) {
    
    cout<<"Main thread ID : " <<std::this_thread::get_id()<<endl; // prints out the parent thread's ID.

    Functor f;

    //thread t1(funciton_1); //function threading

    //thread t1(f); // this is OK! ---- class threading

    /* you cannot do 
     * thread t1(Functor());
     * since t1(argument should be a pointer expression)
     */
    string s = "Everything is going alright!!!";

    ////////////// This is very important!!!! /////////////////////////////////////////////
    /*  thread t1((Functor()), std::ref(s)); /* 1. this is OK since you put additional ( ....... ) brackets.
     * if you want to pass the argument by reference to thread you should use std::ref(argument)
     */
    ////////////////////////////////////////////////////////////////////////////////////

    ////////////// This is very important!!!! /////////////////////////////////////////////
    thread t1((Functor()), std::move(s)); /*1. If you use std::move(argument) then you pass it by reference.
                                           *2. But you move it from main thread. So main thread cannot use that argument anymore.
                                           *2. If you use this method Functor(argument) is not by reference. 
                                         * if you want to pass the argument by reference to thread you should use std::ref(argument)
                                         */
    ////////////////////////////////////////////////////////////////////////////////////
    
      cout<<"t1 thread ID : " <<t1.get_id()<<endl; // prints out the t1 thread ID.

    // thread t2 = t1; // This is not a correct usage, since threads cannot be copied.

    thread t2 = std::move(t1); // This is a correct usage, since threads are also movable.
    
    cout<<"t2 thread ID : " <<t2.get_id()<<endl; // prints out the t2 thread ID.

    //Resource Acquisition is Initialization (RAII) 
    //Wrapper w(t1);

    //    try {
    //        for (int i = 0; i < 100; i++)
    //            cout << "from main " << i << endl;
    //
    //
    //        throw "error!";
    //
    //    } catch (const char* error) {
    //        cout << error << endl;
    //        t1.join();
    //
    //    }

    // t1.join();

    t2.join();

    cout << "from main : " << s << endl;

    //t1.detach();
    /** If you detach the child thread from the main thread. 
     *So child thread cannot join again and main thread does not wait for child thread to finish.
     * Because of this, you cannot see "Hello World" if you detach the child thread.
     **/

    // if (t1.joinable()) //checks if the thread is joinable.
    //     t1.join();








    return 0;
}


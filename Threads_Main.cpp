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

using namespace std;

/*
 * 
 */

void funciton_1() {
    cout << "Hello World!" << endl;
}

int main(int argc, char** argv) {

    thread t1(funciton_1);

    t1.join();

    t1.detach(); /** you detach the child thread from the main thread. 
                 *So child thread cannot join again and main thread does not wait for child thread to finish.
                 * Because of this, you cannot see "Hello World" if you detach the child thread.
                 **/
    
    




    return 0;
}


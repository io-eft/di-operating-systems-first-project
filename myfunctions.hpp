#ifndef __MYFUNCTIONS__HPP
#define __MYFUNCTIONS__HPP
#include "myclass.hpp"
#include <sstream>
#include <time.h>
#include <fstream>
#include <stdlib.h>

using namespace std;

void run_output(ofstream* outputfile);

void run_input_output(ifstream* inputfile, ofstream* outputfile);

void printtime(ofstream* outputfile);

void loadCommand(ifstream* batchfile, MyClass* mc);

void insertEntry(string l, MyClass* mc);

#endif

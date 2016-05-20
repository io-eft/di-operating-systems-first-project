#include "myfunctions.hpp"
#include <fstream>

int main(int argc, char* argv[])
{
    if(argc == 3 || argc == 5)  //if the program was called with 2 or 4 additional arguments
    {
        if(argc == 3)   //if it was called with 2 arguments
        {
            string input(argv[1]);
            if(input != "-o")   //if the first of them is not the output flag
            {
                cout << "Wrong Input, please run the program using the correct commands." << endl;      //let the user know
            }
            else    //if it is
            {
                ofstream outputfile;
                outputfile.open(argv[2]);   //open the file given in the 2nd command as output file
                if(outputfile.is_open())    //check if the file opened
                {
                    run_output(&outputfile);    //run the program with output only given
                    outputfile.close();         //close the file
                }
                else    //if it failed to open
                    cout << "Error Opening File." << endl;  //let the user know
            }
        }
        else    //if the program was given with 4 additional arguments
        {
            string input1(argv[1]);
            string input2(argv[3]);
            if((input1 == "-o" && input2 == "-i") || (input1 == "-i" && input2 == "-o"))    //check if the 1st was input flag and the 3rd ouput flag, or the other way around
            {
                ifstream inputfile;
                ofstream outputfile;
                if(input1 == "-o")  //if the first argument was output
                {
                    inputfile.open(argv[4]);    //open the 4th as input file
                    outputfile.open(argv[2]);   //and the 2nd as output file
                }
                else    //if the first argument was output
                {
                    inputfile.open(argv[2]);    //open the 2nd as output file
                    outputfile.open(argv[4]);   //and the 4th as input
                }
                if(inputfile.is_open() && outputfile.is_open()) //check if the files opened
                {
                    run_input_output(&inputfile, &outputfile);  //run the program with both input and output given
                    inputfile.close();      //close the input file
                    outputfile.close(); //close the output file
                }
                else    //if you can't open one of the files, let the user know
                {
                    cout << "Error Opening File." << endl;
                }
            }
            else    //if the program was given with wrong commands, let the user know
            {
                cout << "Wrong Input, please run the program using the correct commands." << endl;
            }
        }
    }
    else    //if the program was given with wrong amount of arguments let the user know
    {
        cout << "Wrong Input, please run the program using the correct commands." << endl;
    }
}

#include "myfunctions.hpp"
#include "graph.hpp"

void run_output(ofstream* outputfile)   //when only output file was given as an argument
{
    MyClass mc;
    string line;
    string command;
    string info;
    stringstream ss;
    while(1)
    {
        cout << "Your command: " << endl;
        getline(cin, line);     //get the whole user input
        ss << line;     //put in in a stringstream
        getline(ss, command,' ');   //get the first word
        if(command == "load")   //if it's load
        {
            ifstream batchfile;
            getline(ss, info);  //get the second word
            batchfile.open(info.c_str());   //open the file with that name
            if(batchfile.is_open()) //check if the file opened
                loadCommand(&batchfile, &mc);   //load the records in that file
        }
        if(command == "ins")    //in the insert
        {
            getline(ss, info);  //get the rest of the line
            insertEntry(info, &mc); //call the insertion function
        }
        if(command == "top")    //if the command is top
        {
            if(line == "top")   //check if the whole line is just top
                mc.top();   //call the top function

            else    //if there are other words in the line
            {
          //      getline(ss, info, ' ');
                getline(ss, info);  //get the percentile asked as a string
                double p = atof(info.c_str());  //turn it in to double
                mc.topPercentile(p);    //call the top percentile function
            }
        }
        if(command == "del")    //if the command is delete
        {
            mc.removeTop(outputfile);   //delete the top command
        }
        if(command == "lookup") //if the command is lookup
        {
       //    getline(ss, info, ' ');
            getline(ss, info);  //get the lookup value
            mc.lookUp(info.c_str());    //look up for it
        }
        if(command == "stats")  //if the command is stats
        {
       //     getline(ss, info, ' ');
            getline(ss, info);  //get the prefecture value
            mc.stats_prefecture(info.c_str());  //get the stats
        }
        if(command == "sumstats")   //if the command is sumstats
        {
            mc.sumStats();  //print them
        }
        if(command == "print")  //if the command is print
        {
            mc.print(); //print the tree
        }
        if(command == "exit")   //if the command is exit
        {
            if(line == "exit")  //if the whole line is exit
                return; //exit
            else    //if there's another word in the line
            {
                getline(ss, info);  //get the word
                ofstream dumpfile;
                dumpfile.open(info.c_str());    //open the file
                if(dumpfile.is_open())      //if the file is open
                    mc.exit(&dumpfile); //print the records in in
                return; //exit the program
            }
        }
        ss.str("");     //clear the stringstream
        ss.clear();
    }
}

void run_input_output(ifstream* inputfile, ofstream* outputfile)    //function when both input and output files were given
{                                   //most of it is same as above
    MyClass mc;
    string line;
    string command;
    string info;
    stringstream ss;
    while(getline(*inputfile, line))    //while there are still lines in the file
    {
        ss << line;
        getline(ss, command,' ');
        if(command == "load")
        {
            ifstream batchfile;
            getline(ss, info);
            batchfile.open(info.c_str());
            if(batchfile.is_open())
                loadCommand(&batchfile, &mc);
        }
        if(command == "ins")
        {
            getline(ss, info);
            insertEntry(info, &mc);
        }
        if(command == "top")
        {
            if(line == "top")
                mc.top();
            else
            {
    //            getline(ss, info, ' ');
                getline(ss, info);
                double p = atof(info.c_str());
                mc.topPercentile(p);
            }
            cout << endl;
        }
        if(command == "del")
        {
            mc.removeTop(outputfile);
        }
        if(command == "lookup")
        {
      //      getline(ss, info, ' ');
            getline(ss, info);
            mc.lookUp(info.c_str());
        }
        if(command == "stats")
        {
        //    getline(ss, info, ' ');
            getline(ss, info);
            mc.stats_prefecture(info.c_str());
        }
        if(command == "sumstats")
        {
            mc.sumStats();
        }
        if(command == "print")
        {
            mc.print();
        }
        if(command == "exit")
        {
            if(line == "exit")
                return;
            else
            {
                getline(ss, info);
                ofstream dumpfile;
                dumpfile.open(info.c_str());
                if(dumpfile.is_open())
                {
                    mc.exit(&dumpfile);
                    dumpfile.close();
                }
                return;
            }
        }
        ss.str("");
        ss.clear();
    }
    run_output(outputfile); //if there's no exit command in the input file, go to the mode where only output was given
}

void printtime(ofstream* outputfile)    //function found at http://www.cplusplus.com/reference/ctime/localtime/
{
    time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    *outputfile << asctime(timeinfo);
}

void loadCommand(ifstream* batchfile, MyClass* mc)  //insert entries from loadfile
{
    string line;
    string vat;
    string name;
    string surname;
    string hometown;
    string prefecture;
    string debt;
    stringstream ss;
    while(getline(*batchfile, line))        //while there are still lines in the file
    {
        ss << line;                     //put the line in a stringstream
        getline(ss, vat, ' ');          //get the first word for vat
        getline(ss, name, ' ');         //get the 2nd word for name
        getline(ss, surname, ' ');      //get the 3rd word for surname
        getline(ss, hometown, ' ');     //get the 4th word for hometown
        getline(ss, prefecture, ' ');   //get the 5th word for prefecture
        getline(ss, debt);              //get the rest as debt
        double d = atof(debt.c_str());  //turn the debt to doulbe
        TaxPayer* tax = new TaxPayer(vat.c_str(), surname.c_str(), name.c_str(), hometown.c_str(), prefecture.c_str(), d);  //create a new record
//        TaxPayer* tax = new TaxPayer(vat, surname, name, hometown, prefecture, d);
        ss.str(""); //clear the stringstream
        ss.clear();
        mc->insertEntry(tax);   //insert entry
    }
}

void insertEntry(string l, MyClass* mc) //insert entry from prompt
{                   //same as above, without the while
    string vat;
    string name;
    string surname;
    string hometown;
    string prefecture;
    string debt;
    stringstream ss;

    ss << l;
    getline(ss, vat, ' ');
    getline(ss, name, ' ');
    getline(ss, surname, ' ');
    getline(ss, hometown, ' ');
    getline(ss, prefecture, ' ');
    getline(ss, debt);
    double d = atof(debt.c_str());
    TaxPayer* tax = new TaxPayer(vat.c_str(), surname.c_str(), name.c_str(), hometown.c_str(), prefecture.c_str(), d);
//        TaxPayer* tax = new TaxPayer(vat, surname, name, hometown, prefecture, d);
    ss.str("");
    ss.clear();
    mc->insertEntry(tax);
}

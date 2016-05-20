#include "mytaxpayer.hpp"

TaxPayer::TaxPayer():debt(0)
{
    strcpy(vat,"0");
    strcpy(surname,"0");
    strcpy(name,"0");
    strcpy(hometown,"0");
    strcpy(prefecture,"0");
}

char* TaxPayer::getVat()
{
    return vat;
}

double TaxPayer::getDebt()
{
    return debt;
}
/*
TaxPayer::TaxPayer(char* v, char* s, char* n, char* h, char* p, double d):debt(d)
{
    if(strlen(v) > 10 || strlen(s) > 25 || strlen(n) > 15 || strlen(h) > 20 || strlen(p) > 3)
    {
        cout << "Wrong information provided for entry with VAT: " << v << ". All information for it now set to 0" << endl;
        TaxPayer();
    }
    else
    {
        strcpy(vat,v);
        strcpy(surname,s);
        strcpy(name,n);
        strcpy(hometown,h);
        strcpy(prefecture,p);
    }

}
*/
/*
void TaxPayer::print()
{
    cout << "VAT: " << vat << endl;
    cout << "Surname: " << surname << endl;
    cout << "Name: " << name << endl;
    cout << "Hometown: " << hometown << endl;
    cout << "Prefecture: " << prefecture << endl;
    cout << fixed << setprecision(2) << debt << endl;
    cout << endl;
}*/

char* TaxPayer::getPrefecture()
{
    return prefecture;
}

void TaxPayer::print(ofstream* outputfile)
{
    *outputfile << "VAT: " << vat << endl;
    *outputfile << "Surname: " << surname << endl;
    *outputfile << "Name: " << name << endl;
    *outputfile << "Hometown: " << hometown << endl;
    *outputfile << "Prefecture: " << prefecture << endl;
    *outputfile << fixed << setprecision(2) << debt << endl;
    *outputfile << endl << endl;
}

void TaxPayer::printToDumpfile(ofstream* outputfile)
{
    *outputfile << vat << " " << name << " " <<  surname << " " << hometown << " " << prefecture << " " << fixed << setprecision(2) << debt << endl;
}

TaxPayer::TaxPayer(const char* v, const char* s, const char* n, const char* h, const char* p, double d):debt(d)
{
    if(strlen(v) > 10 || strlen(s) > 25 || strlen(n) > 15 || strlen(h) > 20 || strlen(p) > 3)
    {   //check if the info exceed the maximum amount of characters, and notify the user
        cout << "Wrong information provided for entry with VAT: " << v << ". All information for it now set to 0" << endl;
        TaxPayer();
    }
    else
    {
        strcpy(vat,v);
        strcpy(surname,s);
        strcpy(name,n);
        strcpy(hometown,h);
        strcpy(prefecture,p);
    }

}

void TaxPayer::print()
{
    cout << "VAT: " << vat << ", "
     << "Surname: " << surname << ", "
     << "Name: " << name << ", "
     << "Hometown: " << hometown << ", "
     << "Prefecture: " << prefecture << ", "
     << fixed << setprecision(2) << debt << endl;   //this was found on http://www.cplusplus.com/reference/iomanip/setprecision/

}

/*!
 *  \file PrintFuncInfo.cpp
 *  \brief Source file for \ref PrintFuncInfo function implementation
 */

/*!
 *  \fn void PrintFuncInfo(int ncolumns, vector<TString> string2print) "";
 *  \brief Function used to print a banner with function info
 * 
 *  This function is used to print a banner with some "*" characters.\n
 *  These "*" are arranged in a rectangular format.\n
 *  They contains information given by the user as a vector of TString
 * 
 *  \param string2print vector of TString that the user wants to print
 */

#include "headers/PrintFuncInfo.h"

/*These namespaces can be useful*/
using namespace std;

/*Global definition of number of columns of the banner*/
const int ncolumns = 55;

void PrintFuncInfo(vector<TString> string2print)
{
    int nrows = string2print.size() * 2 + 3;
    int stringindex = 0;
    int printedcharactercounter = 0;    //Counter of printed characters to ensure all cut strings are considering their previous offset
    vector<int> partiallength;          //Length of the small strings remaining from cuts: even are left respect to the half

    cout << endl;
    for (int isymb = 0; isymb < nrows; isymb++)
    {
        int flag = 0;
        for (int jsymb = 0; jsymb < ncolumns; jsymb++)
        {
            if (isymb == 0 || isymb == nrows - 1)
            {
                cout << "*";
            }
            else if (isymb % 2 == 0 && flag == 0)
            {
                /*Variables used to control strings longer than limits*/
                int length = string2print[stringindex].Length();
                int iterator = 0;          //Number of times that a string has been cut

                /*Controls how many times we have to crop a string*/
                while (length > ncolumns)
                {
                    iterator = iterator + 2;
                    length = floor( length / 2);
                    if (string2print[stringindex].First(" ") > 0)
                    {
                        length = string2print[stringindex].Index(" ", 1, length, TString::ECaseCompare::kExact);
                        partiallength.push_back(length);
                        partiallength.push_back(string2print[stringindex].Length()-length);                    
                    }
                }

                /*Print all strings*/
                if (iterator > 0)
                {
                    printedcharactercounter = 0;
                    
                    /*Print cut strings*/
                    for (int i = 0; i < iterator; i++)
                    {
                        int pcc = 0;
                        int minchar = round((ncolumns - partiallength[i])/ 2);
                        int maxchar = round((ncolumns + partiallength[i]) / 2);
                        for (jsymb = 0; jsymb <ncolumns; jsymb++)
                        {
                            if ( jsymb == 0 || jsymb == ncolumns-1)
                            {
                                cout << "*";                               
                            }
                            else if (minchar<=jsymb && jsymb<=maxchar && pcc<partiallength[i] && printedcharactercounter<string2print[stringindex].Length())
                            {
                                cout << string2print[stringindex][printedcharactercounter];
                                pcc++;
                                printedcharactercounter++;
                            }
                            else
                            {
                                cout << " ";
                            }
                        }
                        if (i < iterator - 1) cout << endl;
                    }
                    printedcharactercounter = 0;
                    partiallength.clear();
                    stringindex++;
                    flag = 1;
                }
                /*Print uncut strings*/
                else
                {
                    printedcharactercounter = 0;
                    int minchar = round((ncolumns - length) / 2);
                    int maxchar = round((ncolumns + length) / 2);
                    for (jsymb=0; jsymb < ncolumns; jsymb++)
                    {
                        if (jsymb == 0 || jsymb == ncolumns -1)
                        {
                            cout << "*";
                        }
                        else if (minchar <= jsymb && jsymb < maxchar && printedcharactercounter<string2print[stringindex].Length())
                        {
                            cout << string2print[stringindex][printedcharactercounter];
                            printedcharactercounter++;
                        }
                        else
                        {
                            cout << " ";
                        }
                    }
                    stringindex++;
                    flag = 1;
                }
            }
            else if (jsymb == 0 || jsymb == ncolumns-1)
            {
                cout << "*";
            }
            else
            {
                cout << " ";
            }            
        }
        cout << endl;
    }
    cout << endl;
    return;
}
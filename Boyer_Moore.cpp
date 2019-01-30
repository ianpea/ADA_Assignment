/*****Please include following header files*****/
// string
// vector
/***********************************************/
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>
#include <algorithm>
/*****Please use following namespaces*****/
// std
/*****************************************/
using namespace std;

static int Max(int a, int b) {
    return a >= b ? a : b;
}

static void BadCharHeuristic(string str, int size, int* badChar) {
    int i;

    for (i = 0; i < 256; i++)
        badChar[i] = -1;

    for (i = 0; i < size; i++)
        badChar[(int)str[i]] = i;
}

static vector<int> SearchString(string str, string pat) {
    vector<int> retVal;
    int m = pat.length();
    int n = str.length();

    int* badChar = new int[256];

    BadCharHeuristic(pat, m, badChar);

    int s = 0;
    while (s <= (n - m))
    {
        int j = m - 1;

        while (j >= 0 && pat[j] == str[s + j])
            --j;

        if (j < 0)
        {
            retVal.push_back(s);
            s += (s + m < n) ? m - badChar[str[s + m]] : 1;
        }
        else
        {
            s += Max(1, j - badChar[str[s + j]]);
        }
    }

    delete[] badChar;
    
    return retVal;
}

string TextFileToString(string fn)
{
   ostringstream dosString(ios::out | ios::binary ) ; // *** binary
   ifstream inFile(fn.c_str()) ;
   string line;
   while(getline(inFile, line) ) dosString << line << "\r\n" ;

    return dosString.str() ;
}

int main(int argc, char const *argv[])
{
	string fn, str, data, pattern;
    pattern = "Moore";
	cout << "Enter filename with extension:" << endl;
	getline(cin, fn);
    if(fn.substr(fn.find_last_of(".") + 1) == "txt")
    {
        data = TextFileToString(fn);
    }else
    {   
        str = "docto.exe -f " + fn + " -O ";
        fn.erase(fn.find_last_of("."));
        str = str + fn + ".txt -T wdFormatText";
        const char *command = str.c_str(); 
        system(command);
        fn = fn + ".txt";
        data = TextFileToString(fn);
    }
    
    vector<int> value;
    auto start = chrono::high_resolution_clock::now();
    value = SearchString(data, pattern);
    auto finish = chrono::high_resolution_clock::now();
    auto elapsed = finish - start;
    chrono::duration_cast<chrono::nanoseconds>(elapsed);

    int occurrence = 0;
    for(int i =0; i<value.size(); i++){
        occurrence++;
    }


    cout << occurrence << " occurrence(s) of \"" << pattern << "\" found!" << endl;
    cout << "Elapsed time: " << elapsed.count() << "ns\n";

    return 0;
}



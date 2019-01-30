#include <string>
#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>

using namespace std;

//code to convert text file into string var
string TextFileToString(string filename )
{
   ostringstream dosString(ios::out | ios::binary ) ; // *** binary
   ifstream inFile(filename.c_str()) ;

   string line;
   while(getline(inFile, line) ) dosString << line << "\r\n" ;

    return dosString.str() ;
}

bool equal( const string& str, size_t pos, const string& pattern)
{
    // return str.substr( pos, pattern.size() ) == pattern ;

    if( pattern.size() > str.size() - pos ) return false ;

    for( size_t i = 0 ; i < pattern.size() ; ++i )
        if( pattern[i] != str[pos+i] ) return false ;

    return true ;
}

// return true if any sequence of characters in str
// is the same sequence of characters in pattern
void bruteForce( const string& str, const string& pattern )
{
    int count = 0;
    for( size_t i = 0 ; i < str.size() ; ++i )
        if( equal( str, i, pattern ) )
            count++;
    cout << count << " occurences found!";
}

string getTextFile()
{
    string fn, str, data;

	cout << "Enter filename with extensions:" << endl;
	getline(cin, fn);

    //code  to convert files to .txt
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

    return data;
}

int main()
{   
    string pattern;
    string data = getTextFile();
    cout <<"Enter pattern to search: ";
    getline(cin, pattern);


    auto start = chrono::high_resolution_clock::now();
    bruteForce(data,pattern);
    auto finish = chrono::high_resolution_clock::now();
    auto elapsed = finish - start;
    chrono::duration_cast<chrono::nanoseconds>(elapsed);
    cout << elapsed.count() << "ns" << endl;
}

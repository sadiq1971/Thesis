#include<iostream>
#include<fstream>

using namespace std;

int main()
{
    ifstream input;
    input.open("/home/sadiq/Thesis/run/scenGen/scenario");
    ofstream output;
    output.open("scen_100_250_625.out");
    
    while(!input.eof()){
        string value,s;
        int x;
        input >> value;
        if(value=="$god_")
        {
            input>>s;
           
            input>>x;
            output<<x<<" ";
            input>>x;
            output<<x<<" ";
            input>>x;
            output<<x<<"\n";
        
        }
        
    }
    



    return 0;
}

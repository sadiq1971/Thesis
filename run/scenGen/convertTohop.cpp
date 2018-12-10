#include<iostream>
#include<fstream>

using namespace std;

int main(int argc, char *argv[] )
{
    ifstream input;
    // cout<<argv[1];
    input.open(argv[1]);
    ofstream output;
    output.open(argv[2]);
    output<<(argv[3])<<"\n";
    
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

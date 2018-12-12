#include<iostream>
#include<fstream>

using namespace std;

int main(int argc, char *argv[] )
{
    ifstream in[4];
    string algo[4] = {"MCDS ", "CACDS", "DP   ", "DCADS"}; 
    
    for(int i = 0; i< 4; i++){
        in[i].open(argv[i+1]);
        //cout<<argv[i+1]<<endl;
    }

    int t= atoi(argv[6]);

    ofstream output;
    output.open(argv[5]);
    output<<"algo"<<"  "<< "   Delay    "<<" Reachability"<<"     D/R      "
    << "  A.Forwarding "<< "     F/R    "<<"   A.Colission\n";


    for(int i = 0; i < 4; i++){
        int c = 0;
        float delay = 0;
        float reach = 0;
        float d_r = 0;
        float af = 0;
        float af_r=0;
        float ac = 0;
        while(c<t){
            string value;
            float x = 0;
            
            in[i] >> value;
            
            in[i] >> x;
            //cout<<value<<endl;
            //cout<<x<<endl;
            delay+=x;

            in[i] >> value;
            in[i] >> x;
            //cout<<value<<endl;
            //cout<<x<<endl;
            reach+=x;

            in[i] >> value;
            in[i] >> x;
            //cout<<value<<endl;
            //cout<<x<<endl;
            af+=x;

            in[i] >> value;
            in[i] >> x;
            //cout<<value<<endl;
            //cout<<x<<endl;
            ac+=x;
            c++;
 
        }

        delay = delay/c;
        reach = reach/c;
        af = af/c;
        ac = ac/c;
        d_r = delay/reach;
        af_r = af/reach;
        output<<algo[i]<<"  "<<delay<<"    "<<reach<<"      "
        <<d_r<<"       "<<af<<"      "<<af_r<<"       "<<ac<<"\n";

    }

    for(int i = 0; i< 4; i++){
        in[i].close();
    }
    output.close();

    return 0;
}

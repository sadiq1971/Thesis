#include "DP.h"
using namespace std;
int main(){
    cout<<"DEBUG";
    int starting_node = 0;
    FILE *fp1, *fp2;
    FILE *fp_in;
    int total_black;
    char p[1000], t[1000], r[1000];
  
    fp_in=fopen("/home/sadiq/Thesis/NAWRIN_thesis_codes/f2.txt","r");
    int x=1;

    while(fscanf(fp_in,"%s",p)!=EOF)
    {

        // cout<<"Runnning Sceanrio::"<<x<<endl;
    x++;    
    total_black=0;
    node node_u, node_v;

    strcpy (t,"/home/sadiq/Thesis/NAWRIN_thesis_codes/test_input/");
    strcat(t,p);
    //printf(t);
    fp=fopen(t,"r");

   
    strcpy (r,"/home/sadiq/Thesis/NAWRIN_thesis_codes/outDP/");
     //printf("dones");
    stringstream cwn_s;
    cwn_s << starting_node;
    strcat(r,p);
    strcat(r,cwn_s.str().c_str());
    fp2=fopen(r,"w");

    fp1=fopen("out.txt","w");
    if (fp == NULL )
    {
            cout<<"Error! opening file....fp.";
    }
    if (fp1==NULL)
    {
            cout<<"Error! opening file. fp1....";
    }
    if (fp2==NULL)
    {

            cout<<"Error! opening file...fp2..";
    }

    initialization();
    
    for(int i = 0; i < num_nodes; i++){
        for(int j = 0; j < num_nodes; j++){
            ZeroOne[i][j]=0;
        }            
    }
    // cout<<"Number of Nodes::"<<num_nodes<<'\t';
    

            node_v.id=starting_node;
            q.push(node_v);
            node_v.k_forward_korte_bolse.push(null_node.id);

            while(!q.empty())
            {
                bool flag1=0;
                int temp= q.front().id;
                node_v=ob[temp];
               
                q.pop();

                 if(node_v.color==2)
                 {
                     flag1=1;
                 }


                 if(flag1==0)
                 {

                    node_v.color=2;

                    ob[node_v.id].color=node_v.color;

                    node_u.id=node_v.k_forward_korte_bolse.front();
                    node_v.k_forward_korte_bolse.pop();

 

                    for(int i=0;i<num_nodes;i++)
                    {
                        if(ob[i].id==node_u.id)
                        {
                            node_u=ob[i];
                            break;
                        }
                    }

                   
                    exact_two_hops_away(&node_v);
                    
                    selecting_B_Set(&node_v, &node_u);
                     
                    selecting_U_Set(&node_v, node_u);

                    selecting_forward_list(&node_v);
                     


                }
            }

           

            for(int i=0;i<num_nodes;i++)
            {

                if(ob[i].color==2)
                {
                    total_black++;
                }

            }

            // cout<<"total forwardings:"<<total_black<<endl;
            //fprintf(fp2, "%s %d\t", "Number of Nodes::",num_nodes);
            //fprintf(fp2,"total forwarding:: %d\n",total_black);
            for(int i=0;i<num_nodes;i++)
            {
                for(int j=0;j<num_nodes;j++)
                {
                    fprintf(fp2,"%d ", ZeroOne[i][j]);
                }
                fprintf(fp2,"\n");
            }
            fclose(fp1);
            fclose(fp);
            fclose(fp2);


    }

    fclose(fp_in);
    // printf("Done running all test cases. Results are in folder outDP\n");
    return 0;
}
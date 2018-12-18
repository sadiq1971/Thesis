#include<iostream>
#include<stdio.h>
#include<bits/stdc++.h>
#include<queue>
using namespace std;
int num_nodes, arr[1000][1000];
int sizec_intersection, sizec_minus;
int sizec_union;
FILE *fp, *fp1, *fp2;
int contention_count=0,sum=0;
bool ZeroOne[1000][1000]={};


int *Union(int a[],int b[],int m,int n)
{
 int i,j;
 int *c= new int[1000];
 sizec_union=0;
 int flag=0;
 for(i=0;i<m;i++)
 {
  c[sizec_union]=a[i];
  sizec_union++;
 }
 for(i=0;i<n;i++)
 {
  flag=0;
  for(j=0;j<m;j++)
  {
   if(b[i]==c[j])
   {
    flag=1;
    break;
   }
  }
  if(flag==0)
  {
   c[sizec_union]=b[i];
   sizec_union++;
  }
 }

  return c;
}

int *intersection(int a[],int b[], int sizea, int sizeb)
{
    sizec_intersection=0;
    int *c=new int[1000];
    for(int i=0;i<sizea;i++)
    {
        for(int j=0;j<sizeb;j++)
        {
            if(a[i]==b[j])
            {
                c[sizec_intersection++]=a[i];
                break;
            }
        }
    }
    return c;
}

int *twoset_minus(int a[], int b[], int sizea, int sizeb)
{
    int *c=new int[1000];
    sizec_minus=0;
    for(int i=0;i<sizea;i++)
    {
        bool flag=0;
        for(int j=0;j<sizeb;j++)
        {
            if(a[i]==b[j])
            {
                flag=1;
                
                break;
            }
        }
        
        if(flag==0)
        {
            //cout<<"Starting"<<endl;
            //cout<<sizec_minus<<endl;
            c[sizec_minus++]=a[i];
        }
    }
    return c;

}

bool areEqual(int arr1[], int arr2[], int n, int m)
{

    if (n != m)
        return false;

    sort(arr1, arr1+n);
    sort(arr2, arr2+m);

    for (int i=0; i<n; i++)
         if (arr1[i] != arr2[i])
            return false;

    return true;
}

class node
{
    public:

    int first_hop_neighbors[1000], size_of_first_hop;
    int second_hop_neighbors[1000], size_of_second_hop;
    int U_Set[1000], size_of_U_set;
    int B_Set[1000], size_of_B_set;
    int Forward_list[10000], size_of_Forward_list;

    //public:
    int color;
    queue <int>k_forward_korte_bolse;
    int id;
    node();
    friend void first_hop_neighbor_add(node *a);
    friend void second_hop_neighbor_add(node *a);
    friend void exact_two_hops_away(node *a);
    friend void selecting_B_Set(node *a, node *b);
    friend void selecting_forward_list(node *a);
    friend void selecting_U_Set(node *a, node b);

    friend void initialnode();
    void printneighbors();
};

queue <node>q;
node ob[1000];
node null_node;
void initialnode()
{
    null_node.size_of_first_hop=null_node.size_of_second_hop=1;
    for(int i=0;i<1;i++)
    {
        null_node.id=-1;
        null_node.first_hop_neighbors[i]=-1;
        null_node.second_hop_neighbors[i]=-1;

    }
}

void node::printneighbors()
{
    node a;
    for(int i=0;i<num_nodes;i++)
    {
        a.id=i;
        a=ob[i];
        cout<<"N(u) of node "<<a.id<<": ";
        for(int j=0;j<a.size_of_first_hop;j++)
            cout<<a.first_hop_neighbors[j]<<" ";
        cout<<endl;

       cout<<"N(N(u)) of node "<<a.id<<": ";
        for(int j=0;j<a.size_of_second_hop;j++)
            cout<<a.second_hop_neighbors[j]<<" ";
        cout<<endl<<endl;
    }
}

node::node()
{
    size_of_first_hop=size_of_second_hop=size_of_B_set=size_of_U_set=0; color=0;
    size_of_Forward_list=0;
}
void first_hop_neighbor_add(node *a)
{
    for(int i=0;i<num_nodes;i++)
        {
            if(arr[a->id][i]==1)
                a->first_hop_neighbors[a->size_of_first_hop++]=i;
        }
}
void second_hop_neighbor_add(node *a)
{
     bool flag;
        for(int i=0;i<a->size_of_first_hop;i++)
        {
            for(int j=0;j<num_nodes;j++)
            {
                if(arr[a->first_hop_neighbors[i]][j]==1)
                {
                    flag=0;
                    for(int k=0;k<a->size_of_second_hop;k++)
                    {

                        if(a->second_hop_neighbors[k]==j)
                        {
                            flag=1;
                            break;
                        }
                    }
                    if(flag==0)
                    {
                        a->second_hop_neighbors[a->size_of_second_hop++]=j;
                    }

                }
            }
        }
}
void exact_two_hops_away(node *a)
{

    a->size_of_U_set=0;
    for(int i=0;i<a->size_of_second_hop;i++)
    {
        bool flag=0;
       for(int j=0;j<a->size_of_first_hop;j++)
       {
           if(a->first_hop_neighbors[j]==a->second_hop_neighbors[i])
           {

               flag=1;
               break;
           }

       }
       if(flag==0)
       {
           a->U_Set[a->size_of_U_set++]=a->second_hop_neighbors[i];
       }
    }

}
void selecting_B_Set(node *a, node *b)
{
    int *B1_Set;
    B1_Set=twoset_minus(a->first_hop_neighbors,b->first_hop_neighbors,a->size_of_first_hop,b->size_of_first_hop);
    for(int i=0;i<sizec_minus;i++)
    {
        a->B_Set[i]=B1_Set[i];

    }
    a->size_of_B_set=sizec_minus;
    free(B1_Set);

}
void selecting_U_Set(node *a, node b)
{
    int *U1_Set;
    U1_Set=twoset_minus(a->U_Set, b.first_hop_neighbors, a->size_of_U_set, b.size_of_first_hop);

    for(int i=0;i<sizec_minus;i++)
    {
        a->U_Set[i]=U1_Set[i];
    }
    a->size_of_U_set=sizec_minus;
    free(U1_Set);

}


void selecting_forward_list(node *a)
{
    int *Z1_Set, one[1000],one_count=0, *U2_Set;
    int Z_Set[1000], size_of_Z_set=0, U1_Set[100000], size_of_U1_set=0,B1_Set[100000], size_of_B1_set=0;
    int maximum, pos_of_max;
    int *temp_set, temp1[1000], size_of_temp1_set, X_Set[1000], size_of_X_set=0,*X1_Set;
    node b;
    int f[1000],size_f=0;

   

    for(int i=0;i<a->size_of_B_set;i++)
    {
        node c;
        c.id=a->B_Set[i];
        for(int k=0;k<num_nodes;k++)
                {
                    if(ob[k].id==c.id)
                    {
                        c=ob[k];
                        break;
                    }
                }
        for(int j=0;j<c.size_of_first_hop;j++)
        {
            B1_Set[size_of_B1_set++]=c.first_hop_neighbors[j];
        }

    }

    for(int i=0;i<a->size_of_U_set;i++)
    {
        bool f=0;
        for(int j=0;j<size_of_B1_set;j++)
        {

            if(a->U_Set[i]==B1_Set[j])
            {
                f=1;
                break;
            }
        }
        if(f==0)
        {
            U1_Set[size_of_U1_set++]=a->U_Set[i];
        }
    }


    U2_Set=twoset_minus(a->U_Set,U1_Set,a->size_of_U_set, size_of_U1_set);
    for(int i=0;i<sizec_minus;i++)
    {
        a->U_Set[i]=U2_Set[i];
    }
    a->size_of_U_set=sizec_minus;

    free(U2_Set);

    for(int i=0;i<a->size_of_U_set;i++)
        X_Set[i]=a->U_Set[i];
    size_of_X_set=a->size_of_U_set;


    if(a->size_of_U_set>0)
    {

    bool flag=false;

    while(flag==false)
    {
        for(int i=0;i<num_nodes;i++)
        {
            one[i]=0;
        }
        for(int i=0;i<a->size_of_B_set;i++)
        {
            for(int j=0;j<size_of_X_set;j++)
            {
                if(arr[a->B_Set[i]][X_Set[j]]==1)
                {
                    one[a->B_Set[i]]=one[a->B_Set[i]]+1;
                }
            }
        }


        for(int i=0;i<num_nodes;i++)
            {
                one_count=one_count+one[i];
            }

            maximum=0;
            size_of_temp1_set=0;
            for(int i=0;i<num_nodes;i++)
            {
                if(one[i]>maximum)
                {
                    maximum=one[i];
                    pos_of_max=i;
                }
            }
            b.id=pos_of_max;
            for(int i=0;i<num_nodes;i++)
                {
                    if(ob[i].id==b.id)
                    {
                        b=ob[i];
                        break;
                    }
                }
            temp_set=intersection(b.first_hop_neighbors, a->U_Set, b.size_of_first_hop,a->size_of_U_set);
            for(int i=0;i<sizec_intersection;i++)
            {
                temp1[i]=temp_set[i];

            }
            size_of_temp1_set=sizec_intersection;
            free(temp_set);

            q.push(ob[pos_of_max]);
            ob[pos_of_max].k_forward_korte_bolse.push(a->id);

            a->Forward_list[a->size_of_Forward_list++]= pos_of_max;
            Z1_Set=Union(temp1, Z_Set, size_of_temp1_set, size_of_Z_set);

            for(int i=0;i<sizec_union;i++)
            {
                Z_Set[i]=Z1_Set[i];

            }
            size_of_Z_set=sizec_union;

            free(Z1_Set);

            X1_Set=twoset_minus(X_Set,Z_Set,size_of_X_set,size_of_Z_set);
            for(int i=0;i<sizec_minus;i++)
                X_Set[i]=X1_Set[i];
            size_of_X_set=sizec_minus;
            free(X1_Set);

            flag=areEqual(a->U_Set, Z_Set, a->size_of_U_set, size_of_Z_set);

            //free(U2_Set);
        }
    }
    // cout<<"Forward_list of : "<<a->id<<": ";
    
    for(int i=0;i<a->size_of_Forward_list;i++)
    {
        // cout<<a->Forward_list[i]<<" ";
        int index=a->Forward_list[i];
        ZeroOne[a->id][index]=1;
        //fprintf(fp2,"%d ",a->Forward_list[i]);

    }
    
    // cout<<endl;

}

void initialization()
{
    int fst_node,second_node,hop;
    fscanf(fp,"%d", &num_nodes);




    for(int i=0;i<num_nodes;i++)
    {
        for(int j=0;j<num_nodes;j++)
        {
            if(i==j)
                arr[i][j]=1;
            else
                arr[i][j]=0;
        }

    }
       
    while(fgetc(fp) != EOF)
        {
            fscanf(fp,"%d", &fst_node);
            fscanf(fp,"%d", &second_node);
            fscanf(fp,"%d", &hop);

            if(hop==1)
                {
                    arr[fst_node][second_node]=1;
                    arr[second_node][fst_node]=1;
                }

        }
        
        initialnode();
        
        int count=0;
        for(int i=0;i<num_nodes;i++)
        {
            ob[i].id=i;
            ob[i].size_of_first_hop=0;
            ob[i].size_of_second_hop=0;
            ob[i].size_of_B_set=0;
            ob[i].size_of_U_set=0;
            ob[i].color=0;
            ob[i].size_of_Forward_list=0;
            while(!ob[i].k_forward_korte_bolse.empty())
            {
                ob[i].k_forward_korte_bolse.pop();

            }
            first_hop_neighbor_add(&ob[i]);
            second_hop_neighbor_add(&ob[i]);
        }

}



int main(int charc, char *charv[])
{
    //srand(time(0));
    int starting_node = atoi(charv[1]);
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
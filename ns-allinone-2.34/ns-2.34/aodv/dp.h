//
// Created by sadiq on 12/22/18.
//

#ifndef UNTITLED7_DP_H
#define UNTITLED7_DP_H


#include<iostream>
#include<stdio.h>
#include<bits/stdc++.h>
#include<queue>

using namespace std;
int num_nodes, arr[500][500];
int sizec_intersection, sizec_minus;
int sizec_union;
int contention_count=0,sum=0;
bool ZeroOnedp[500][500]={};
bool ZeroOnedc[500][500]={};

FILE *fp;
int sizeof_flist;

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
    int Forward_list[1000], size_of_Forward_list;

    //public:
    int color;
    queue <int>k_forward_korte_bolse;
    int id;
    node();
    void inode();
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
    // size_of_first_hop=size_of_second_hop=size_of_B_set=size_of_U_set=0; color=0;
    // size_of_Forward_list=0;
}
void node:: inode(){
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


void selecting_forward_list_DP(node *a)
{
    sizeof_flist = 0;
    a->size_of_Forward_list=0;
    for(int i=0;i<1000;i++){
        a->Forward_list[i] = 0;
    }
    
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

            // q.push(ob[pos_of_max]);
            //ob[pos_of_max].k_forward_korte_bolse.push(a->id);

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

    for(int i=0; i< num_nodes; i++){
         ZeroOnedp[a->id][i]=0;
    }
    for(int i=0;i < a->size_of_Forward_list;i++)
    {
        // cout<<a->Forward_list[i]<<" ";
        sizeof_flist = a->size_of_Forward_list;
        int index = a->Forward_list[i];
        ZeroOnedp[a->id][index]=1;
        //fprintf(fp2,"%d ",a->Forward_list[i]);

    }

    // cout<<endl;

}

/////DCADS

void selecting_forward_list_DCADS(node *a)
{
    sizeof_flist = 0;
    a->size_of_Forward_list=0;
    for(int i=0;i<1000;i++){
        a->Forward_list[i] = 0;
    }
    int *Z1_Set, one[1000],one_count=0, *U2_Set,bla[10000],bla_count=0,*B;
    int Z_Set[100000], size_of_Z_set=0, U1_Set[100000], size_of_U1_set=0,B1_Set[100000], size_of_B1_set=0;
    int maximum=1, pos_of_max,minimum,pos_of_min;
    int *temp_set, temp1[1000], size_of_temp1_set, X_Set[100000], size_of_X_set=0,*X1_Set;
    node b;
     int f[1000],size_f=0;
    int B_copy_set[1000],size_of_B_copy=0,*Breceiver;
    int first_node_set[10];
    first_node_set[0]=a->id;
    Breceiver=twoset_minus(a->B_Set,first_node_set,a->size_of_B_set,1);
    for(int i=0;i<sizec_minus;i++)
    {
        a->B_Set[i]=Breceiver[i];
    }
    a->size_of_B_set=sizec_minus;

    free(Breceiver);

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

    int t1[1000],t2[100],*blackerjonno;
    t1[0]=-1;
    t2[0]=-1;

  int x=1;

        for(int i=0;i<num_nodes;i++)

        {  bla[i]=100;
        }
         for(int i=0;i<a->size_of_B_set;i++)

        {  bla[a->B_Set[i]]=1;
        }
    while(flag==false)
    {

        minimum=100,maximum=0;

        int candidate[1000],num_candidate=0;

            for(int i=0;i<a->size_of_B_set;i++)
            {
                if(arr[a->B_Set[i]][t2[0]]==1)
                {
                    bla[a->B_Set[i]]=bla[a->B_Set[i]]+1;
                }
            }



            for(int i=0;i<a->size_of_B_set;i++)
            {
                if(bla[a->B_Set[i]]<minimum)
                {

                    minimum=bla[a->B_Set[i]];
                }
            }


            for(int i=0;i<a->size_of_B_set;i++)
            {
                if(bla[a->B_Set[i]]==minimum)
                {
                    candidate[num_candidate++]=a->B_Set[i];

                }

            }


        for(int i=0;i<num_nodes;i++)
        {
            one[i]=0;
        }
        for(int i=0;i<num_candidate;i++)
        {
            for(int j=0;j<size_of_X_set;j++)
            {
                if(arr[candidate[i]][X_Set[j]]==1)
                {
                    one[candidate[i]]=one[candidate[i]]+1;
                }
            }
        }


        for(int i=0;i<num_nodes;i++)
            {
                if(one[i]>maximum)
                {
                    maximum=one[i];

                }
            }

            for(int i=0;i<num_candidate;i++)
            {
                if(one[candidate[i]]==maximum)
                {
                    pos_of_max=candidate[i];
                    break;
                }
            }

            t1[0]=pos_of_max;
if(maximum>0)
{
            b.id=pos_of_max;
            t2[0]=b.id;
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

            node x;
            x=ob[pos_of_max];

            q.push(x);
            a->Forward_list[a->size_of_Forward_list++]= pos_of_max;
            // for(int i=0;i<num_nodes;i++)
            // {
            //     if(x.id==ob[i].id)
            //     {
            //         ob[i].k_forward_korte_bolse.push(a->id);
            //     }
            // }

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

            B=twoset_minus(a->B_Set,t1,a->size_of_B_set,1);
            for(int i=0;i<sizec_minus;i++)
            {
                a->B_Set[i]=B[i];
            }
            a->size_of_B_set=sizec_minus;
            free(B);

            flag=areEqual(a->U_Set, Z_Set, a->size_of_U_set, size_of_Z_set);
}
else{

      B=twoset_minus(a->B_Set,candidate,a->size_of_B_set,num_candidate);
            for(int i=0;i<sizec_minus;i++)
            {
                a->B_Set[i]=B[i];
            }
            free(B);
            a->size_of_B_set=sizec_minus;

                  t2[0]=-1;
            flag=areEqual(a->U_Set, Z_Set, a->size_of_U_set, size_of_Z_set);
}



}
    }
    // cout<<"Forward_list of: "<<a->id<<": ";
    

    for(int i=0; i< num_nodes; i++){
         ZeroOnedc[a->id][i]=0;
    }
    for(int i=0;i<a->size_of_Forward_list;i++)
    {
        // cout<<a->Forward_list[i]<<" ";
        sizeof_flist = a->size_of_Forward_list;
        int index=a->Forward_list[i];
        ZeroOnedc[a->id][index]=1;
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


















#endif //UNTITLED7_DP_H

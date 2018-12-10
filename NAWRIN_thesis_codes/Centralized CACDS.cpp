#include<iostream>
#include<stdio.h>
#include<bits/stdc++.h>
#include<queue>
using namespace std;
int num_nodes=0,arr[10000][10000],cardinality[10000],arr1[10000];
int ColorB[10000]={0},ColorG[10000]={0},ColorW[10000]={0};
int ColorB_count=0,ColorG_count=0,ColorW_count=0;
int first_hop_nei[10000],first_count,cardi_check[10000],b=0;
int union_array[10000],intersection_array[10000],minus_array[10000];

FILE *fp_in,*fp2;
FILE *fp,*fp1;

void initialization_array(int a[])
{
        for(int i=0;i<10000;i++)
        {
            a[i]=-1;
        }

}

void Print_array(int a[],int num)
{
    int fl[num_nodes];
    for(int i=0;i<num_nodes;i++)
    {            
       fl[i] = 0;
    }
    for(int i=0;i<num;i++)
    {            
       fl[a[i]] = 1;
    } 
    
    for(int j = 0; j < num_nodes; j++)
    {        
        for(int i=0;i<num_nodes;i++)
        {            
            fprintf(fp2,"%d ", fl[i]);
            fprintf(fp2," ");
        }
        fprintf(fp2,"\n");   
    }
       
   

}
void find_cardinality()
{
    for(int i=0;i<num_nodes;i++)
        {
            int count_=0;
            for(int j=0;j<num_nodes;j++)
            {
                if(arr[i][j]==1)
                    cardinality[i]=++count_;

            }
        }
}
int search_cardinality(int l)
{
    return cardinality[l];
}
int find_first_hop(int a)
{

      int v=0,first_count1=0;
      for(int j=0;j<num_nodes;j++)
      {
            if(arr[a][j]==1)
            {
                first_hop_nei[first_count1++]=j;
            }

      }
      return first_count1;

}
int SetUnion(int a[],int b[],int a_count,int b_count)
{

    int i = 0, j = 0, k = 0,flag;
    for(i=0;i<a_count;++i){
        union_array[k]=a[i];
        k++;
    }

    for(i=0;i<b_count;++i){
        flag=1;
        for(j=0;j<a_count;++j){
            if(b[i]==a[j]){
                flag=0;
                break;
            }
        }

        if(flag){
            union_array[k]=b[i];
            k++;
        }
    }
    return k;
}
int SetIntersection(int a[],int b[],int a_count,int b_count)
{
     int i = 0, j = 0, k = 0;


    for( i=0;i<a_count;i++)
    {
        for( j=0;j<b_count;j++)
        {
            if(a[i]==b[j])
            {
                intersection_array[k++]=a[i];
                break;
            }
        }
    }
    return k;
}
int ArrayMinus(int a[], int b[],int a_count,int b_count)
{
    int c=0,minus_count=0;
    for(int i=0;i<a_count;i++)
    {
        bool flag=0;
       for(int j=0;j<b_count;j++)
       {
           if(a[i]==b[j])
           {
               flag=1;
               break;
           }

       }
       if(flag==0)
       {
           minus_array[c++]=a[i];
           minus_count++;
       }
    }
    return minus_count;
}

int main()
{
    
    int contention_count;
    char p[1000], t[1000], r[1000];

    fp_in=fopen("f2.txt","r");

    while(fscanf(fp_in,"%s",p)!=EOF)
    {

        ColorB[10000]={NULL},ColorG[10000]={NULL},ColorW[10000],ColorB_count=0,ColorG_count=0,ColorW_count=0;
        first_hop_nei[10000],first_count,cardi_check[1000],b=0,contention_count=0;;
        union_array[10000],intersection_array[10000],minus_array[10000];

        strcpy (t,"/home/sadiq/Thesis/NAWRIN_thesis_codes/test_input/");
        strcat(t,p);
        fp=fopen(t,"r");

        strcpy (r,"/home/sadiq/Thesis/NAWRIN_thesis_codes/outCACDS/");
        strcat(r,p);
        fp2=fopen(r,"w");
        //printf("%s\n",r );
    //fp=fopen("D:\\New code\\dp\\final input\\scen-100-125-625-625-1.out","r");
    //fp2=fopen("D:\\New code\\dp\\outputs\\scen-100-125-625-625-1.txt","w");
        fp1=fopen("b.txt","w");
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
    //printf("Here\n");

    int fst_node,second_node,hop,max_car=0,max_car_node,single[10000],single_count=0,camcds[10000];
    fscanf(fp,"%d",&num_nodes);
    for(int i=0;i<num_nodes;i++)
    {
        for(int j=0;j<num_nodes;j++)
        {
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
    for(int i=0;i<num_nodes;i++){
        for(int j=0;j<num_nodes;j++){
            //fprintf(fp2,"%d ", arr[i][j]);
            }
        //fprintf(fp2,"\n");
    }
    initialization_array(ColorB);
    initialization_array(ColorG);
    initialization_array(first_hop_nei);
    for(int i=0;i<num_nodes;i++)
    {
        ColorW[i]=i;
        ColorW_count++;
    }

    find_cardinality();


    for(int i=0;i<num_nodes;i++)
    {
            if(cardinality[i]>max_car)
        {
            max_car=cardinality[i];
            max_car_node=i;
        }
    }
    ColorB[ColorB_count++]=max_car_node;

    int first_count=find_first_hop(max_car_node);


    int union_count=SetUnion(ColorG,first_hop_nei,ColorG_count,first_count);
    for(int i=0;i<union_count;i++)
    {
        ColorG[ColorG_count++]=union_array[i];
    }

    int minus_count= ArrayMinus(ColorW,ColorB,ColorW_count,ColorB_count);
    for(int i=0;i<minus_count;i++)
    {
        ColorW[i]=minus_array[i];
        ColorW_count=minus_count;
    }
    minus_count= ArrayMinus(ColorW,ColorG,ColorW_count,ColorG_count);
    for(int i=0;i<minus_count;i++)
    {
        ColorW[i]=minus_array[i];

    }
    ColorW_count=minus_count;

    while(ColorW_count!=0)

    {


        int MaxWhite=-1,MinBlack=1000,Candidate[100],Temporary[100],BlackCount,WhiteCount;
        int Candidate_count=0,Temporary_count=0,dd[100],X[100],I[100],H[100];
        int neigh_max=-1,Selected[100],Y[100],ycount=0,temp[100],g[100];
        initialization_array(Candidate);
        initialization_array(Temporary);
        initialization_array(Selected);

        for(int u=0;u<ColorG_count;u++)
        {
            first_count=find_first_hop(ColorG[u]);
            BlackCount=SetIntersection(first_hop_nei,ColorB,first_count,ColorB_count);
            if(BlackCount<MinBlack)
            {
                MinBlack=BlackCount;
            }
        }

        for(int u=0;u<ColorG_count;u++)
        {
            first_count=find_first_hop(ColorG[u]);

            BlackCount=SetIntersection(first_hop_nei,ColorB,first_count,ColorB_count);

            if(BlackCount==MinBlack)
            {
                Candidate[Candidate_count++]=ColorG[u];
            }

        }



        for(int w=0;w<Candidate_count;w++)
        {
            first_count=find_first_hop(Candidate[w]);
            WhiteCount=SetIntersection(first_hop_nei,ColorW,first_count,ColorW_count);
            if(WhiteCount>MaxWhite)
            {
                MaxWhite=WhiteCount;
                Selected[0]=Candidate[w];

            }
        }



       if(MaxWhite>0)
        {

            ColorB_count=SetUnion(ColorB,Selected,ColorB_count,1);
            for(int i=0;i<ColorB_count;i++)
            {
                ColorB[i]=union_array[i];
            }

            first_count=find_first_hop(Selected[0]);
            ColorW_count= ArrayMinus(ColorW,first_hop_nei,ColorW_count,first_count);
            for(int i=0;i<ColorW_count;i++)
            {
                ColorW[i]=minus_array[i];
            }

            int t=ArrayMinus(first_hop_nei,ColorB,first_count,ColorB_count);
            for(int gg=0;gg<t;gg++)
            {
                temp[gg]=minus_array[gg];
            }

            ColorG_count= SetUnion(ColorG,temp,ColorG_count,t);
            for(int i=0;i<ColorG_count;i++)
            {
                ColorG[i]=union_array[i];
            }
             ColorG_count=ArrayMinus(ColorG,ColorB,ColorG_count,ColorB_count);
            for(int i=0;i<ColorG_count;i++)
            {
                ColorG[i]=minus_array[i];
            }
        }
        else
        {

            ColorG_count=ArrayMinus(ColorG,Candidate,ColorG_count,Candidate_count);
            for(int i=0;i<ColorG_count;i++)
            {
                ColorG[i]=minus_array[i];
            }
        }

    }
  cout<<"forwarding nodes are"<<endl;
  for(int i=0;i<ColorB_count;i++)
  {
      camcds[i]=ColorB[i];

  }
  Print_array(ColorB,ColorB_count);
  cout<<"number of forward "<<ColorB_count<<endl;


      fclose(fp);
      fclose(fp1);
      fclose(fp2);
  }

    fclose(fp_in);

    cout<<"Done Running all test cases. Results are in file b.txt"<<endl;

       return 0;
}
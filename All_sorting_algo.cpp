#include <bits/stdc++.h>
using namespace std;

void bubblesort(vector <int> &v)
{
    for (int i=0;i<v.size()-1;i++)
    {
        for (int j=0;j<v.size()-1-i;j++)
        {
            if (v[j] > v[j+1]) swap(v[j],v[j+1]);
            
        }
    }
}

void selectionsort(vector<int>&v)
{
    int min;
    for (int i=0;i<v.size()-1;i++)
    {
        min = v[i];
        for (int j=i+1;j<v.size();j++)
        {    if (min > v[j]) 
            {
                int temp = min;
                min = v[j];
                v[j] = temp;
            }
        }
        v[i] = min;
        
    }
    
}

void insertionSort(vector<int> &v)
{
    for (int i =1;i<v.size();i++)
    {
        int key = v[i];
        int j;
        for (j=i-1;j>=0 && v[j]>key;j--)
        {
            v[j+1] = v[j];
        }
        v[j+1] = key;
    }
}

void merge(vector<int>&v,int s,int e)
{
    int mid = (s+e)/2;
    int l = s;
    int r = mid +1;
    
    vector <int> temp;
    while (l <=mid and r <=e)
    {
        if (v[l]<v[r])
        {
            temp.push_back(v[l++]);
        }
        else temp.push_back(v[r++]);
    }
    while (l<=mid)temp.push_back(v[l++]);
    while (r<=e)temp.push_back(v[r++]);
    
    int k=0;
    for (int i=s;i<=e;i++) v[i] = temp[k++];
}

void mergeSort(vector<int>&v,int s,int e)
{
    if (s>=e) return;
    int mid = (s+e)/2;
    mergeSort(v,s,mid);
    mergeSort(v,mid+1,e);
    merge(v,s,e);
}

int partition(vector<int> &v,int s , int e)
{
    int pivot=v[e];
    int i= s ;
    for (int j=s;j<e;j++)
        if (v[j] < pivot)
            swap(v[i++],v[j]);
    swap(v[i],v[e]);
    return i;
}

void quickSort(vector<int> &v,int s,int e)
{
    if (s>=e)return ;
    
    int p = partition(v,s,e);
    quickSort(v,s,p-1);
    quickSort(v,p+1,e);
}

int main ()
{
    vector <int> arr = {2,65,34,2,1,7,8};
    //bubblesort(arr);
    //selectionsort(arr);
    //insertionSort(arr);
    //mergeSort(arr,0,arr.size()-1);
    //quickSort(arr,0,arr.size()-1);
    for (auto i : arr)cout<<i<<" ";
    return 0;
}
#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <ctime>
#include <map>
#include <algorithm>

using namespace std;
void SORT_BY_DIGIT(vector<int>& arr, int digit_place){
    map<int, vector<int>> numbers;
    vector<int> output(arr.size());
    for(int i=0;i<10;i++){
        numbers[i]={};
    }
    for(int i=0;i<arr.size();i++){
        int digit=(arr[i]/digit_place)%10;
        numbers[digit].push_back(arr[i]);
    }
    int index=0;
    for(int i=0;i<10;i++){
        for(int num:numbers[i]){
            arr[index++]=num;
        }
    }
}

void RADIX_SORT(vector<int>& arr, int arr_size){
    int maksimum = *max_element(arr.begin(),arr.end());
    int digit_place = 1;
    while(maksimum/digit_place>0){
        SORT_BY_DIGIT(arr,digit_place);
        digit_place*=10;
    }
}

int main()

{
    srand(time(0));
    vector<int> tab(100);
    for(int i=0;i<=tab.size();i++){
        tab[i] = rand()%1000+1;
        cout<<tab[i]<<", ";
    }
    cout<<endl;
    RADIX_SORT(tab, tab.size());
    for(int i=0;i<tab.size();i++){
        cout<<tab[i]<<", ";
    }


}

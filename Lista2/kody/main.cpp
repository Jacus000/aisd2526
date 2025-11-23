#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <ctime>
#include <map>
#include <algorithm>

using namespace std;
//sort z mapa
void SORT_BY_DIGIT(vector<int>& arr, int digit_place){
    map<int, vector<int>> numbers;
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
void RADIX_SORT(vector<int>& arr){
    int maksimum = *max_element(arr.begin(),arr.end());
    int digit_place = 1;
    while(maksimum/digit_place>0){
        SORT_BY_DIGIT(arr,digit_place);
        digit_place*=10;
    }
}
void RADIX_SORT_NEGATIVE(vector<int>& arr){
    vector<int> positive,negative;
    for(int num:arr)
        if(num>=0) positive.push_back(num);
        else negative.push_back(-num);

    RADIX_SORT(positive);
    RADIX_SORT(negative);
    arr.clear();
    for(int i=negative.size()-1;i>=0;i--){
        arr.push_back(-negative[i]);
    }
    for(int num:positive)
        arr.push_back(num);
}
int PARTITION(vector<int>& arr, int start, int ending){
    int pivot=arr[ending];
    int i=start-1;

    for(int j=start;j<=ending-1;j++){
        if(arr[j]<pivot){
            i++;
            swap(arr[i],arr[j]);
        }
    }
    i++;
    swap(arr[i],arr[ending]);

    return i; //pivot location
}
void QUICK_SORT(vector<int>& arr, int start, int ending){
    if(ending<=start)
        return;
    int pivot=PARTITION(arr,start,ending);
    QUICK_SORT(arr,start,pivot-1);
    QUICK_SORT(arr,pivot+1,ending);
}



int DUAL_PARTITION(vector<int>& arr,int leftIndex,int rightIndex, int& leftPivotFinalPos, int& rightPivotFinalPos){
    if(arr[leftIndex]>arr[rightIndex])
        swap(arr[leftIndex],arr[rightIndex]);

    int leftPivotValue  = arr[leftIndex];
    int rightPivotValue = arr[rightIndex];

    int lessThanPivotBoundary  = leftIndex + 1;     // granica czesci < leftPivot
    int greaterThanPivotBoundary = rightIndex - 1;  // granica czesci > rightPivot
    int scanIndex = lessThanPivotBoundary;          // aktualnie skanowana pozycja

    while (scanIndex <= greaterThanPivotBoundary) {

        if (arr[scanIndex] < leftPivotValue) {
            swap(arr[scanIndex], arr[lessThanPivotBoundary]);
            lessThanPivotBoundary++;
        }
        else if (arr[scanIndex] > rightPivotValue) {
            swap(arr[scanIndex], arr[greaterThanPivotBoundary]);
            greaterThanPivotBoundary--;
            scanIndex--;
        }

        scanIndex++;
    }

    lessThanPivotBoundary--;
    greaterThanPivotBoundary++;

    swap(arr[leftIndex], arr[lessThanPivotBoundary]);
    swap(arr[rightIndex], arr[greaterThanPivotBoundary]);

    leftPivotFinalPos  = lessThanPivotBoundary;
    rightPivotFinalPos = greaterThanPivotBoundary;

}
void DUAL_PIVOT_QUICK_SORT(vector<int>& arr, int left, int right){
    if(left>right){
        return;
    }
    int leftPivotFinalPos, rightPivotFinalPos;
    DUAL_PARTITION(arr,left,right,leftPivotFinalPos,rightPivotFinalPos);
    DUAL_PIVOT_QUICK_SORT(arr,left,leftPivotFinalPos-1);
    DUAL_PIVOT_QUICK_SORT(arr,leftPivotFinalPos+1,rightPivotFinalPos-1);
    DUAL_PIVOT_QUICK_SORT(arr,rightPivotFinalPos+1, right);
}
void INSERTION_SORT(vector<float>& arr){
    int arr_size = arr.size();
    for(int i=1;i<arr_size;i++){
        int j=i-1;
        float key=arr[i];
        while(arr[j]>key && j>=0){
            arr[j+1]=arr[j];
            j=j-1;
        }
        arr[j+1]=key;
    }
}
void BUCKET_SORT(vector<float>& arr, int arr_size){
    vector<vector<float>> buckets(arr_size);
    for(float num:arr){
        int index = int(arr_size*num);
        buckets[index].push_back(num);
    }//
    arr.clear();
    for(int i=0;i<arr_size;i++){
        INSERTION_SORT(buckets[i]);
        for(int j=0;j<buckets[i].size();j++){
            arr.push_back(buckets[i][j]);
        }
    }
}
int main(){
    srand(time(0));
    vector<int> positive_plus_negative(100);
    vector<int> normal_tab(100);
    vector<float> bucket_tab(100);

    for(int i=0;i<100;i++){
        positive_plus_negative[i] = rand()%2001-1000;
        normal_tab[i] = rand()%1000+1;
        bucket_tab[i] = (rand()+1) / (RAND_MAX+1.0);
        cout<<bucket_tab[i]<<", ";
    }
    cout<<endl<<endl;

    DUAL_PIVOT_QUICK_SORT(normal_tab,0,normal_tab.size()-1);
    for(int num:normal_tab){
        cout<<num<<", ";
    }

}

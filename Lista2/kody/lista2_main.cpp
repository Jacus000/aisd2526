#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <ctime>
#include <map>
#include <algorithm>
#include <list>
#include <chrono>
#include <fstream>
#include <sstream>

using namespace std;

//RADIX SORTS
void SORT_BY_DIGIT(vector<int>& arr, int digit_place);
void RADIX_SORT(vector<int>& arr);
void RADIX_SORT_NEGATIVE(vector<int>& arr);
void RADIX_SORT_FOR_DIFFERENT_DS(vector<int>& arr,int d);
void SORT_BY_DIGIT_FOR_D(vector<int>& arr, int digit_place,int d);
//RADIX SORTS


//BUCKET SORTS
void INSERTION_SORT(vector<float>& arr);
void BUCKET_SORT(vector<float>& arr, int arr_size);
int scan_data(vector<float>& arr);
void BUCKET_SORT_STANDARIZED(vector<float>& arr, int arr_size);
//BUCKET SORTS


//QUICK SORTS
struct DualPivotIndices {//dla wygody
    int p1_index;
    int p2_index;
};
int PARTITION(vector<int>& arr, int start, int ending);
void QUICK_SORT(vector<int>& arr, int start, int ending);
DualPivotIndices DUAL_PIVOT_PARTITION(vector<int>& arr, int start, int ending);
void DUAL_PIVOT_QUICK_SORT(vector<int>& arr, int start, int ending);
//QUICK SORTS



//TESTING
struct AlgorithmResult{
    string name;
    double timeMs;
    int size_arr;

    void print() const{
        cout << "\n=== " << name << " ===" << endl;
        cout<<"Wielkosc tablicy: "<< size_arr << endl;
        cout << "Czas wykonania: " << timeMs << " ms" << endl;
    }
    string toCSV() const{
        ostringstream oss;
        oss << timeMs;
        return oss.str();
    }
};
template<typename Func, typename... Args>
AlgorithmResult returnResults(const string& algorithmName,int size_arr, Func func, Args&&... args){
    using std::chrono::high_resolution_clock;
    using std::chrono::duration;

    auto t1 = high_resolution_clock::now();
    func(forward<Args>(args)...);
    auto t2 = high_resolution_clock::now();

    duration<double, std::milli> ms_double = t2 - t1;

    return{
        algorithmName,
        ms_double.count(),
        size_arr,
    };
}
void generate_decimal_array(vector<int>& arr,int arr_size){
    for(int i=0;i<arr_size;i++){
        arr[i]=rand()%1000+1;
    }
}
void copyArray(vector<int>& source, vector<int>& dest, int size){
    for(int i=0;i<size;i++) {
        dest[i]=source[i];
    }
}
void copyArray_float(vector<int>& source, vector<float>& dest, int size){
    for(int i=0;i<size;i++) {
        dest[i]=(float)(source[i]);
    }
}
void test_results(){
    srand(time(0));
    string filename="sorting_results.csv";
    vector<int> d_values = {2, 3, 4, 5, 6, 7, 8, 9, 10, 16, 32, 64, 100, 256, 512, 1000, 2000, 4000, 8000, 12000, 16000};
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    file <<"algorithm,size,time_ms\n";//headers
    for(int d:d_values){
        vector<int> originalArray(100000);
        generate_decimal_array(originalArray,100000);

        vector<int> arr1=originalArray;
        AlgorithmResult results[1];

        copyArray(originalArray,arr1,100000);
        results[0]=returnResults("RADIX_SORT_FOR_DIFFERENT_DS",100000, RADIX_SORT_FOR_DIFFERENT_DS, arr1, d);
        results[0].print();
    }
    vector<int> sizes = {1000 ,5000 ,10000, 25000, 50000,75000, 100000};
    for(int size:sizes){
        vector<int> originalArray(size);
        generate_decimal_array(originalArray, size);

        vector<float> tab_bucket(originalArray.begin(),originalArray.end());
        vector<int> tab2 = originalArray;
        vector<int> tab3 = originalArray;
        vector<int> tab4 = originalArray;

        AlgorithmResult results[4];

        copyArray_float(originalArray, tab_bucket, size);
        results[0] = returnResults("BUCKET_SORT_STANDARIZED",size, BUCKET_SORT_STANDARIZED,tab_bucket, size);
        file << "BUCKET_SORT_STANDARIZED," << size << "," << results[0].toCSV() << "\n";
        results[0].print();

        copyArray(originalArray, tab2, size);
        results[1] = returnResults("QUICK_SORT",size, QUICK_SORT, tab2, 0,tab2.size()-1);
        file << "QUICK_SORT," << size << "," << results[1].toCSV() << "\n";
        results[1].print();

        copyArray(originalArray, tab3, size);
        results[2] = returnResults("DUAL_PIVOT_QUICK_SORT",size, DUAL_PIVOT_QUICK_SORT, tab3, 0,tab3.size()-1);
        file << "DUAL_PIVOT_QUICK_SORT," << size << "," << results[2].toCSV() << "\n";
        results[2].print();

    }

}
//TESTING



void INSERTION_SORT_ON_LISTS(list<int>& lista);

int main(){
    srand(time(0));
    vector<float> positive_plus_negative(100);
    vector<int> normal_tab(100);
    vector<float> bucket_tab(100);
    vector<float> nums(100);
    list<int> lista = {9,3,6,8,10,4,1,5,63,7};

    float min_range = -1000.0f;
    float range_size = 2000.0f;

    for(int i=0;i<100;i++){
        positive_plus_negative[i] = rand()%2001-1000;
        normal_tab[i] = rand()%1000+1;
        bucket_tab[i] = (rand()+1.0) / (RAND_MAX+1.0);
        float random_normalized = (float)rand() / (float)RAND_MAX;
        nums[i] = random_normalized * range_size + min_range;
        cout<<nums[i]<<", ";
    }
    cout<<endl;
    cout<<"test";
    cout<<endl;

    BUCKET_SORT_STANDARIZED(nums, nums.size());
    for(float num:nums)
        cout<<num<<", ";
    cout<<endl;
    INSERTION_SORT_ON_LISTS(lista);
    for(int num:lista)
        cout<<num<<", ";

    cout<<endl;
    test_results();

}

void INSERTION_SORT_ON_LISTS(list<int>& lista){
    if(lista.empty() || lista.size() == 1)
        return;
    list<int>::iterator current = lista.begin();
    current++;

    while(current != lista.end()) {
        list<int>::iterator element_to_insert = current;
        current++;
        list<int>::iterator search_position = lista.begin();
        while(search_position != element_to_insert){
            if(*element_to_insert < *search_position){
                lista.splice(search_position, lista, element_to_insert);
                break;
            }
            search_position++;
        }
    }
}
void BUCKET_SORT(vector<float>& arr, int arr_size){
    vector<vector<float>> buckets(arr_size);
    for(float num:arr){
        int index = (int)(arr_size*num);
        if(index==arr_size){
            index=arr_size - 1;
        }
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
int scan_data(vector<float>& arr){
    if(arr.empty()) return 2;
    float max_value=*max_element(arr.begin(),arr.end());
    float min_value=*min_element(arr.begin(),arr.end());
    if(max_value<=1.0f&&min_value>0.0f) return 0;
    else return 1;
}
void BUCKET_SORT_STANDARIZED(vector<float>& arr, int arr_size){
    int which_case=scan_data(arr);
    if(arr_size==0) return;
    float max_value=*max_element(arr.begin(),arr.end());
    float min_value=*min_element(arr.begin(),arr.end());
    switch(which_case){
        case 0:
            BUCKET_SORT(arr,arr_size);
            break;
        case 1:
            float range=max_value-min_value;
            vector<float> scaled(arr_size);
            for(int i=0;i<arr_size;i++){
                scaled[i]=(arr[i]-min_value)/range;
            }
            BUCKET_SORT(scaled,arr_size);
            for(int i=0;i<arr_size;i++){
                arr[i]=scaled[i]*range+min_value;
            }
            break;
    }
}
////////////////////////////////////////////////////////////////////////////
void SORT_BY_DIGIT(vector<int>& arr, int digit_place){
    vector<vector<int>> numbers(10);
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

void RADIX_SORT(vector<int>& arr){
    int maksimum = *max_element(arr.begin(),arr.end());
    int digit_place = 1;
    while(maksimum/digit_place>0){
        SORT_BY_DIGIT(arr,digit_place);
        digit_place*=10;
    }
}


void SORT_BY_DIGIT_FOR_D(vector<int>& arr, int digit_place,int d){
    vector<vector<int>> buckets(d);

    for(int i=0;i<arr.size();i++){
        int digit=(arr[i]/digit_place)%d;
        buckets[digit].push_back(arr[i]);
    }
    int index=0;
    for(int i=0;i<d;i++){
        for(int num:buckets[i]){
            arr[index++]=num;
        }
    }
}
void RADIX_SORT_FOR_DIFFERENT_DS(vector<int>& arr, int d){
    int maksimum = *max_element(arr.begin(),arr.end());
    int digit_place = 1;
    while(maksimum/digit_place>0){
        SORT_BY_DIGIT_FOR_D(arr,digit_place,d);
        digit_place*=d;
    }

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
DualPivotIndices DUAL_PIVOT_PARTITION(vector<int>& arr, int start, int ending) {
    if (start >= ending){
        return {start, ending};
    }
    if (arr[start] > arr[ending]) {
        swap(arr[start], arr[ending]);
    }

    int p1 = arr[start];
    int p2 = arr[ending];

    int k = start + 1;
    int l = start + 1;
    int g = ending - 1;

    while (k <= g) {
        if (arr[k] < p1) {
            swap(arr[k], arr[l]);
            l++;
        } else if (arr[k] >= p2) {
            while (arr[g] > p2 && k < g) {
                g--;
            }
            swap(arr[k], arr[g]);
            g--;

            if (arr[k] < p1) {
                swap(arr[k], arr[l]);
                l++;
            }
        }
        k++;
    }
    l--;
    swap(arr[start], arr[l]);

    g++;
    swap(arr[ending], arr[g]);

    return {l, g};
}

void DUAL_PIVOT_QUICK_SORT(vector<int>& arr, int start, int ending) {
    if (ending <= start){
        return;
    }
    DualPivotIndices pivots = DUAL_PIVOT_PARTITION(arr, start, ending);
    int p1_index = pivots.p1_index;
    int p2_index = pivots.p2_index;

    //sekcja lewa
    DUAL_PIVOT_QUICK_SORT(arr, start, p1_index - 1);

    //sekcja srodkowa
    if (p1_index+1<p2_index-1){
        DUAL_PIVOT_QUICK_SORT(arr, p1_index+1, p2_index-1);
    }

    //sekcja prawa
    DUAL_PIVOT_QUICK_SORT(arr, p2_index + 1, ending);
}

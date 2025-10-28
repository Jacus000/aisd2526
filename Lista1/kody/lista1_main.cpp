#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
#include <sstream>

using namespace std;


long long comparisons = 0;
long long assignments = 0;

void resetCounters() {
    comparisons = 0;
    assignments = 0;
}

struct AlgorithmResult{
    string name;
    double timeMs;
    long long comparisons;
    long long assignments;

    void print() const{
        cout << "\n=== " << name << " ===" << endl;
        cout << "Porownania: " << comparisons << endl;
        cout << "Przypisania: " << assignments << endl;
        cout << "Czas wykonania: " << timeMs << " ms" << endl;
    }

    string toCSV() const{
        ostringstream oss;
        oss << comparisons << "," << assignments << "," << timeMs;
        return oss.str();
    }
};
template<typename Func, typename... Args>
AlgorithmResult returnResults(const string& algorithmName, Func func, Args&&... args){
    using std::chrono::high_resolution_clock;
    using std::chrono::duration;

    resetCounters();

    auto t1 = high_resolution_clock::now();
    func(forward<Args>(args)...);
    auto t2 = high_resolution_clock::now();

    duration<double, std::milli> ms_double = t2 - t1;

    return{
        algorithmName,
        ms_double.count(),
        comparisons,
        assignments
    };
}

void INSERTION_SORT(int tab[],int tabsize){
    for(int i=1;i<tabsize;i++){
        int x=tab[i];
        assignments++;
        int j=i-1;
        assignments++;
        while(j>=0 && tab[j]>x){
            comparisons += 2;
            tab[j+1]=tab[j];
            assignments++;
            j--;
        }
        comparisons += (j>=0 ? 2 : 1); // ostatnie sprawdzenie warunku
        tab[j+1]=x;
        assignments++;
    }

}

void INSERTION_SORT_MOD(int tab[], int tabsize){
    for(int i=1;i<tabsize;i+=2){
        int x=tab[i];
        assignments++;
        int y=tab[i+1];
        assignments++;
        int j=i-1;
        assignments++;

        comparisons++;
        if(y<x){
            int temp = x;
            assignments++;
            x=y;
            assignments++;
            y=temp;
            assignments++;
        }

        while(j>=0 && tab[j]>x){
            comparisons += 2;
            tab[j+1]=tab[j];
            assignments++;
            j--;
        }
        comparisons += (j>=0 ? 2 : 1);
        tab[j+1]=x;
        assignments++;

        int k=i;
        assignments++;

        while(k>=0 && tab[k]>y){
            comparisons += 2;
            tab[k+1]=tab[k];
            assignments++;
            k--;
        }
        comparisons += (k>=0 ? 2 : 1);
        tab[k+1]=y;
        assignments++;
    }
    if(tabsize%2==1){
        int last=tab[tabsize-1];
        assignments++;
        int j=tabsize-2;
        assignments++;
        while(j>=0 && tab[j]>last){
            comparisons += 2;
            tab[j+1]=tab[j];
            assignments++;
            j--;
        }
        comparisons += (j>=0 ? 2 : 1);
        tab[j+1]=last;
        assignments++;

    }
}

void MERGE(int leftTab[], int rightTab[], int tab[], int tabsize){
    int leftSize=tabsize/2;
    int rightSize=tabsize-leftSize;
    int i=0,l=0,r=0;
    assignments += 3;
    while(l<leftSize && r<rightSize){
        comparisons += 2;
        comparisons++;
        if(leftTab[l]<rightTab[r]){
            tab[i]=leftTab[l];
            assignments++;
            i++;
            l++;
        }else{
            tab[i]=rightTab[r];
            assignments++;
            i++;
            r++;
        }
    }
    comparisons += (l<leftSize || r<rightSize) ? (l<leftSize ? 2 : 1) : 1;
    //leftovers
    while(l<leftSize){
        comparisons++;
        tab[i]=leftTab[l];
        assignments++;
        i++;
        l++;
    }
    comparisons++;
    while(r<rightSize){
        comparisons++;
        tab[i]=rightTab[r];
        assignments++;
        i++;
        r++;
    }
    comparisons++;

}

void MERGE_SORT(int tab[], int tabsize){
    int lenght=tabsize;
    comparisons++;
    if(lenght<=1)
        return;
    int middle=lenght/2;
    int diff=lenght-middle;
    int leftTab[middle];
    int rightTab[diff];

    int j=0;
    assignments++;
    for(int i=0;i<lenght;i++){
        comparisons++;
        if(i<middle){
            leftTab[i]=tab[i];
            assignments++;
        }else{
            rightTab[j]=tab[i];
            assignments++;
            j++;
        }

    }
    MERGE_SORT(leftTab,middle);
    MERGE_SORT(rightTab,diff);
    MERGE(leftTab,rightTab,tab,tabsize);


}


void MERGE_3TAB(int leftTab[],int middleTab[],int rightTab[],
      int tab[], int leftSize,int middleSize, int rightSize
){
    int i=0,l=0,m=0,r=0;
    assignments += 4;
    while(l<leftSize && m<middleSize && r<rightSize){
        comparisons += 3;
        comparisons += 2;
        if(leftTab[l]<middleTab[m] && leftTab[l]<rightTab[r]){
            tab[i]=leftTab[l];
            assignments++;
            i++;
            l++;
        }else if(middleTab[m]<leftTab[l] && middleTab[m]<rightTab[r]){
            comparisons += 2;
            tab[i]=middleTab[m];
            assignments++;
            i++;
            m++;
        }else{
            tab[i]=rightTab[r];
            assignments++;
            i++;
            r++;
        }
    }
    comparisons += (l>=leftSize ? 1 : (m>=middleSize ? 2 : 3));
    while(l<leftSize && r<rightSize){
        comparisons += 2;
        comparisons++;
        if(leftTab[l]<rightTab[r]){
            tab[i]=leftTab[l];
            assignments++;
            i++;
            l++;
        }else{
            tab[i]=rightTab[r];
            assignments++;
            i++;
            r++;
        }
    }
    comparisons += (l>=leftSize ? 1 : 2);
    while(l<leftSize && m<middleSize){
        comparisons += 2;
        comparisons++;
        if(leftTab[l]<middleTab[m]){
            tab[i]=leftTab[l];
            assignments++;
            i++;
            l++;
        }else{
            tab[i]=middleTab[m];
            assignments++;
            i++;
            m++;
        }
    }
    comparisons += (l>=leftSize ? 1 : 2);
    while(m<middleSize && r<rightSize){
        comparisons += 2;
        comparisons++;
        if(middleTab[m]<rightTab[r]){
            tab[i]=middleTab[m];
            assignments++;
            i++;
            m++;
        }else{
            tab[i]=rightTab[r];
            assignments++;
            i++;
            r++;
        }
    }
    comparisons += (m>=middleSize ? 1 : 2);
    while(l<leftSize){
        comparisons++;
        tab[i]=leftTab[l];
        assignments++;
        i++;
        l++;
    }
    comparisons++;
    while(r<rightSize){
        comparisons++;
        tab[i]=rightTab[r];
        assignments++;
        i++;
        r++;
    }
    comparisons++;
    while(m<middleSize){
        comparisons++;
        tab[i]=middleTab[m];
        assignments++;
        i++;
        m++;
    }
    comparisons++;
}


void MERGE_SORT_MODE(int tab[], int tabsize){
    comparisons++;
    if(tabsize<=1)
        return;

    comparisons++;
    if(tabsize==2){
        comparisons++;
        if(tab[0]>tab[1]){
            int temp=tab[0];
            assignments++;
            tab[0]=tab[1];
            assignments++;
            tab[1]=temp;
            assignments++;
        }
        return;
    }

    int lenght=tabsize;
    int part1=lenght/3;
    int part2=part1*2;

    int leftTab[part1];
    int middleTab[part2-part1];
    int rightTab[lenght-part2];

    for(int i=0;i<part1;i++){
        leftTab[i]=tab[i];
        assignments++;
    }
    for(int i=0;i<part2-part1;i++){
        middleTab[i]=tab[part1+i];
        assignments++;
    }
    for(int i=0;i<lenght-part2;i++){
        rightTab[i]=tab[part2+i];
        assignments++;
    }

    MERGE_SORT_MODE(leftTab,part1);
    MERGE_SORT_MODE(middleTab,part2-part1);
    MERGE_SORT_MODE(rightTab,lenght-part2);

    int leftSize=part1;
    int middleSize=part2-part1;
    int rightSize=tabsize-part2;

    MERGE_3TAB(leftTab,middleTab,rightTab,tab,leftSize,middleSize,rightSize);
}
void HEAPIFY(int tab[], int i, int n){
    int left=2*i+1;
    int right=2*i+2;
    int largest=i;
    assignments++;

    comparisons += 2;
    if(left<n&&tab[left]>tab[i]){
        largest=left;
        assignments++;
    }

    comparisons += 2;
    if(right<n&&tab[right]>tab[largest]){
        largest=right;
        assignments++;
    }

    comparisons++;
    if(largest!=i){
        int temp=tab[i];
        assignments++;
        tab[i]=tab[largest];
        assignments++;
        tab[largest]=temp;
        assignments++;
        HEAPIFY(tab,largest,n);
    }
}
void HEAP_SORT(int tab[], int n){
    for(int i=n/2-1;i>=0;i--){
        HEAPIFY(tab,i,n);
    }
    for(int i=n-1;i>0;i--){
        int temp=tab[0];
        assignments++;
        tab[0]=tab[i];
        assignments++;
        tab[i]=temp;
        assignments++;
        HEAPIFY(tab,0,i);
    }
}

void HEAPIFY_TRIPLE(int tab[], int n, int i){
    int left=3*i+1;
    int middle=3*i+2;
    int right=3*i+3;
    int largest=i;
    assignments++;

    comparisons += 2;
    if(left<n&&tab[left]>tab[largest]){
        largest=left;
        assignments++;
    }
    comparisons += 2;
    if(middle<n&&tab[middle]>tab[largest]){
        largest=middle;
        assignments++;
    }
    comparisons += 2;
    if(right<n&&tab[right]>tab[largest]){
        largest=right;
        assignments++;
    }

    comparisons++;
    if(largest!=i){
        int temp=tab[i];
        assignments++;
        tab[i]=tab[largest];
        assignments++;
        tab[largest]=temp;
        assignments++;
        HEAPIFY_TRIPLE(tab,n,largest);
    }
}

void TRIPLE_HEAP_SORT(int tab[],int n){
    for(int i=(n-2)/3;i>=0;i--){
        HEAPIFY_TRIPLE(tab,n,i);
    }
    for(int i=n-1;i>0;i--){
        int temp=tab[0];
        assignments++;
        tab[0]=tab[i];
        assignments++;
        tab[i]=temp;
        assignments++;
        HEAPIFY_TRIPLE(tab,i,0);
    }
}
void generateArray(int tab[], int size){
    for(int i=0;i<size;i++){
        tab[i] = rand()%1000+1;
    }
}

void copyArray(vector<int>& source, vector<int>& dest, int size){
    for(int i=0;i<size;i++) {
        dest[i]=source[i];
    }
}

void testAndSaveResults() {
    srand(time(0));
    string filename="sorting_results.csv";
    vector<int> sizes = {1000 ,5000 ,10000, 25000, 50000,75000, 100000};

    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    file <<"algorithm,size,comparisons,assignments,time_ms\n";//headers

    for(int size : sizes) {

        vector<int> originalArray(size);
        generateArray(originalArray.data(), size);

        vector<int> tab1 = originalArray;
        vector<int> tab2 = originalArray;
        vector<int> tab3 = originalArray;
        vector<int> tab4 = originalArray;
        vector<int> tab5 = originalArray;
        vector<int> tab6 = originalArray;

        AlgorithmResult results[6];

        copyArray(originalArray, tab1, size);
        results[0] = returnResults("HEAP_SORT", HEAP_SORT, tab1.data(), size);
        file << "HEAP_SORT," << size << "," << results[0].toCSV() << "\n";
        results[0].print();

        copyArray(originalArray, tab2, size);
        results[1] = returnResults("TRIPLE_HEAP_SORT", TRIPLE_HEAP_SORT, tab2.data(), size);
        file << "TRIPLE_HEAP_SORT," << size << "," << results[1].toCSV() << "\n";
        results[1].print();

        copyArray(originalArray, tab3, size);
        results[2] = returnResults("MERGE_SORT", MERGE_SORT, tab3.data(), size);
        file << "MERGE_SORT," << size << "," << results[2].toCSV() << "\n";
        results[2].print();

        copyArray(originalArray, tab4, size);
        results[3] = returnResults("MERGE_SORT_MODE", MERGE_SORT_MODE, tab4.data(), size);
        file << "MERGE_SORT_MODE," << size << "," << results[3].toCSV() << "\n";
        results[3].print();

        copyArray(originalArray, tab5, size);
        results[4] = returnResults("INSERTION_SORT", INSERTION_SORT, tab5.data(), size);
        file << "INSERTION_SORT," << size << "," << results[4].toCSV() << "\n";
        results[4].print();

        copyArray(originalArray, tab6, size);
        results[5] = returnResults("INSERTION_SORT_MOD", INSERTION_SORT_MOD, tab6.data(), size);
        file << "INSERTION_SORT_MOD," << size << "," << results[5].toCSV() << "\n";
        results[5].print();

    }

    file.close();
    cout << "\n\nResults saved to: " << filename << endl;
}

int main()
{
    testAndSaveResults();

    int test_tab[100]={};
    for(int i=0;i<100;i++){
        test_tab[i] = rand()%1000+1;
        cout<<test_tab[i]<<", ";
    }
    cout<<endl;
    TRIPLE_HEAP_SORT(test_tab,100);

    for(int i=0;i<100;i++){
        cout<<test_tab[i]<<", ";
    }

    return 0;
}

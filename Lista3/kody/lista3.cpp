#include <bits/stdc++.h>

using namespace std;


//Czesc kodow ma naniesione poprawki, ktorych nie ma w sprawozdaniu, dot. odzyskiwania wynikow.
// --- CUT_ROD ---
int CUT_ROD_RECURENCY(int n, vector<int>& price);
int CUT_ROD_MEMO(int n, vector<int>& price, vector<int>& memo, vector<int>& s);

int CALL_CUT_ROD_RECURENCY(vector<int>& price) {
    int n= price.size();
    return CUT_ROD_RECURENCY(n, price);
}

int CUT_ROD_RECURENCY(int n, vector<int>& price) {
    if (n==0) return 0;
    int answer=-1;
    for (int j=1 ;j<=n ;j++) {
        answer = max(answer, price[j-1] + CUT_ROD_RECURENCY(n-j, price));
    }
    return answer;
}

int CALL_CUT_ROD_MEMO(vector<int>& price) {
    int n = price.size();
    vector<int> memo(n+1, -1);
    vector<int> s(n+1, 0); //tablica do rozwiazania
    int result = CUT_ROD_MEMO(n, price, memo, s);
    
    cout<<"Ciecia (Memo): ";
    int temp_n = n;
    while (temp_n > 0) {
        cout<<s[temp_n]<<" ";
        temp_n -= s[temp_n];
    }
    cout << endl;
    return result;
}

int CUT_ROD_MEMO(int n, vector<int>& price, vector<int>& memo, vector<int>& s) {
    if (n==0) return 0;
    if (memo[n]!=-1) return memo[n];
    int answer = -1;
    for (int j=1 ;j<=n; j++) {
        int val = price[j-1] + CUT_ROD_MEMO(n -j, price, memo, s);
        if (val > answer) {
            answer = val;
            s[n] =j;
        }
    }
    return memo[n] = answer;
}

int CALL_CUT_ROD_ITER(vector<int>& price) {
    int n = price.size();
    vector<int> tab(n + 1, 0);
    vector<int> s(n + 1, 0); //tablica do odzyskiwania rozwiazania
    for (int i = 1; i <= n; i++) {
        int max_val = -1;
        for (int j = 1; j <= i; j++) {
            if (max_val < price[j - 1] + tab[i - j]) {
                max_val = price[j - 1] + tab[i - j];
                s[i] = j;
            }
        }
        tab[i] = max_val;
    }
    
    cout<<"Ciecia (Iter): ";
    int temp_n = n;
    while (temp_n > 0) {
        cout<<s[temp_n]<<" ";
        temp_n -= s[temp_n];
    }
    cout<<endl;
    return tab[n];
}

// --- LCS ---
int CALL_LCS_ITER_SILENT(string& s1, string& s2) {
    int m = s1.size();
    int n = s2.size();
    vector<vector<int>> matrix(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                matrix[i][j] = matrix[i - 1][j- 1] + 1;
            } else {
                matrix[i][j] = max(matrix[i - 1][j], matrix[i][j- 1]);
            }
        }
    }
    
    //odzyskiwanie rozwiazania
    string lcs_str = "";
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            lcs_str += s1[i - 1];
            i--; j--;
        } else if (matrix[i- 1][j] >= matrix[i][j-1]) {
            i--;
        } else {
            j--;
        }
    }
    reverse(lcs_str.begin(), lcs_str.end());
    cout << "LCS (Iter): " << lcs_str << endl;
    
    return matrix[m][n];
}

int LCS_RECURENCY_MEMO(string& s1, string& s2, vector<vector<int>>& memo, int n, int m) {
    if (n == 0 || m == 0) return 0;
    if (memo[n][m] != -1) return memo[n][m];
    if (s1[n - 1] == s2[m - 1]) {
        return memo[n][m] = 1 + LCS_RECURENCY_MEMO(s1, s2, memo, n - 1, m - 1);
    }
    return memo[n][m] = max(LCS_RECURENCY_MEMO(s1, s2, memo, n, m - 1), LCS_RECURENCY_MEMO(s1, s2, memo, n - 1, m));
}

int CALL_LCS_RECURENCY_MEMO(string& s1, string& s2) {
    int n = s1.size();
    int m = s2.size();
    vector<vector<int>> memo(n + 1, vector<int>(m + 1, -1));
    int length = LCS_RECURENCY_MEMO(s1, s2, memo, n, m);
    
    //odzyskiwanie rozwiazania z tablicy memo
    string lcs_str = "";
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            lcs_str += s1[i - 1];
            i--; j--;
        } else {
            int val_top = (i > 1) ? memo[i - 1][j] : 0;
            int val_left = (j > 1) ? memo[i][j - 1] : 0;
            if (val_top >= val_left) i--;
            else j--;
        }
    }
    reverse(lcs_str.begin(), lcs_str.end());
    cout<<"LCS (Memo): "<<lcs_str<<endl;
    
    return length;
}

// --- ACTIVITY SELECTOR ---
struct Activity {
    int id;
    int start;
    int finish;
};

bool compare_start(Activity a, Activity b) { return a.start < b.start; }

int FIND_NEXT(vector<Activity>& activities, int finish_time) {
    int low = 0, high = activities.size() - 1;
    int ans = activities.size();
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (activities[mid].start >= finish_time) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return ans;
}

vector<Activity> ACTIVITY_SELECTOR_DP(vector<Activity> activities) {
    int n = activities.size();
    if (n == 0) return {};
    sort(activities.begin(), activities.end(), compare_start);
    vector<int> tab(n + 1, 0);
    vector<bool> picked(n, false);
    vector<int> next_compatible(n, n);

    for (int i = n - 1; i >= 0; i--) {
        int next = FIND_NEXT(activities, activities[i].finish);
        next_compatible[i] = next;
        int take = 1 + tab[next];
        int skip = tab[i + 1];
        if (take >= skip) {
            tab[i] = take;
            picked[i] = true;
        } else {
            tab[i] = skip;
            picked[i] = false;
        }
    }
    vector<Activity> result;
    for (int i = 0; i < n; ) {
        if (picked[i]) {
            result.push_back(activities[i]);
            i = next_compatible[i];
        } else {
            i++;
        }
    }
    return result;
}

void RECURENCY_STEP_ACTIVITY_SELECTOR(vector<Activity>& activities, int k, vector<Activity>& result) {
    int m = k - 1;
    while (m >= 0 && activities[m].finish > activities[k].start) {
        m--;
    }
    if (m >= 0) {
        result.push_back(activities[m]);
        RECURENCY_STEP_ACTIVITY_SELECTOR(activities, m, result);
    }
}

vector<Activity> ACTIVITY_SELECTOR_RECUR(vector<Activity> activities) {
    if (activities.empty()) return {};
    sort(activities.begin(), activities.end(), compare_start);
    vector<Activity> result;
    int n = activities.size();
    result.push_back(activities[n - 1]);
    RECURENCY_STEP_ACTIVITY_SELECTOR(activities, n - 1, result);
    reverse(result.begin(), result.end());
    return result;
}

vector<Activity> ACTIVITY_SELECTOR_ITER(vector<Activity> activities) {
    int n = activities.size();
    if (n == 0) return {};
    sort(activities.begin(), activities.end(), compare_start);
    vector<Activity> selected;
    int lastSelectedID = n - 1;
    selected.push_back(activities[lastSelectedID]);
    for (int i = n - 2; i >= 0; i--) {
        if (activities[i].finish <= activities[lastSelectedID].start) {
            selected.push_back(activities[i]);
            lastSelectedID = i;
        }
    }
    reverse(selected.begin(), selected.end());
    return selected;
}

int main() {
    vector<int> price = {1, 5, 8, 9, 10, 17, 17, 20};

    cout<<"Wynik (Iter): "<<CALL_CUT_ROD_ITER(price)<<endl;
    cout<<"Wynik (Memo): "<<CALL_CUT_ROD_MEMO(price)<<endl;

    string X= "ABCBDAB";
    string Y= "BDCABA";
    cout<<"Dlugosc LCS (Iter): "<< CALL_LCS_ITER_SILENT(X, Y)<<endl;
    cout<<"Dlugosc LCS (Memo): "<< CALL_LCS_RECURENCY_MEMO(X,Y)<<endl;
}
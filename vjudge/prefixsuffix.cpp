#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class PrefixesSuffixes{
public:
	string s;
    int count[100000];
    int len = 0;
    int k = 0;
    vector<int> results;
    
    void receiveString(){
        cin >> s;
    }

    void matches(){
        len = s.length();
        int p[len];
        p[0] = 0;
        for(int i = 1; i < len; i++){
            int j = p[i-1];
            while(j > 0 && s[i] != s[j]){
                j = p[j-1];
            }
            if(s[i] == s[j]){
                j++;
            }
		    p[i] = j;
        }
        results.push_back(len);
        int m = len;
        while(m > 0) {
            m = p[m-1];
            if(m != 0){ 
                results.push_back(m);
            }
        }
        reverse(results.begin(),results.end());
        k = results.size();
        for(int i = 0;i < len; i++){
            count[p[i]]++;
        } 
        for(int i = len-1; i >= 1; i--){
            count[p[i-1]] += count[i];
        } 
        cout << k << '\n';
        for(int i = 0;i < k; i++){
            cout << results[i] << ' ' << count[results[i]]+1 << '\n';
        }
	}
};

int main(){
    PrefixesSuffixes ps;
    ps.receiveString();
    ps.matches();
}
#include <iostream>

using namespace std;

class ZFunction{
private:

    void createZ(int zArr[], string str){
        int len = str.length();
        int l = 0;
        int h = 0;
        int k = 0;
        for (int i = 1; i < len; i++){
            if (i > h){
                l = h = i;
                while (h < len && str[h-l] == str[h]){
                    h++;
                }
                zArr[i] = h-l;
                h--;
            }
            else{
                k = i-l;
                if (zArr[k] < h-i+1){
                    zArr[i] = zArr[k];
                }
                else{
                    l = i;
                    while (h < len && str[h-l] == str[h]){
                        h++;
                    }
                    zArr[i] = h-l;
                    h--;
                }
            }
        }
    }

public:
    int t;
	string txt, pat;

    void searchPat(string text, string pattern){
        string newString = pattern + "$" + text;
        string indexes = "";
        int len = newString.length();
        int count = 0;
        int zArr[len];
        createZ(zArr, newString);
        for (int i = 0; i < len; i++){
            if (zArr[i] == pattern.length()){
                count++;
                indexes = indexes + to_string(i - pattern.length()) + " ";
            }
        }
        if (indexes == ""){
            cout << "Not Found" << "\n" << "\n";
        }
        else{
            cout << count << "\n" << indexes << "\n" << "\n";
        }
    }

    void getT(){
        cin >> t;
    }

    void patternFind(){
        for(int i = 0; i < t; i++){
            cin >> txt >> pat;
            searchPat(txt, pat);
        }
    }
};

int main(){
    ZFunction zFunction;
    zFunction.getT();
    zFunction.patternFind();
}
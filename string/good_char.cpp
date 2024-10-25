#include<iostream>
#include <string>
#include <algorithm>

using namespace std;

/*
    bpos[]: mảng lưu suffix của chuỗi s trùng khớp với một substring của chuỗi đó
    bpos[i] = j, tức là suffix của chuỗi s bắt đầu tại vị trí thứ j đến cuối mảng
    trùng khớp với một substring chuỗi bắt đầu tại vị trí i có độ dài bằng độ
    dài của chuỗi suffix.
    ví dụ: xabaabaab
           123456789
        bpos[5] = 8, bpos[4] = 7, bpos[3] = 6, bpos[2] = 5
    
    shift[j] = j - i: mảng lưu khoảng cách hai ký tự đầu của suffix chuỗi s bắt đầu tại vị trí thứ j
    và một substring chuỗi bắt đầu tại vị trí i có độ dài bằng độ
    dài của chuỗi suffix đó (ở đây substring đó khớp với chuỗi suffix)
    
    ví dụ: xabaabaab
           123456789
        shift[7] = 3, shift[6] = 3, shift[5] = 3
*/


void good_character_heuristic(string pat, int m, int *bpos, int *shift){
    fill(bpos, bpos + m + 1, 0);
    fill(shift, shift + m + 1, 0);

    int i = m, j = m+1;
    bpos[m] = m+1;
    while(i > 0){
        while(j <= m && pat[i-1] != pat[j-1]){ // Ở đây so sánh hai ký tự tại i-1 và j-1 cho t cho chỉ số i, j bắt đầu từ 1
                                                // nên phải trừ 1 cả hơn với đúng vị trí trong so sánh trong chuỗi
            if(shift[j] == 0){
                shift[j] = j - i;
            }
            j = bpos[j];
        }
        // Ở đây ký tự thứ i khớp với ký tự thứ j hoac j = m + 1, tuc la khong tim được chuỗi khớp
        i--; j--;
        bpos[i] = j;
    }

    int skip = bpos[0];
    for(int i = 0; i <= m; i++){
        if(shift[i] == 0){
            shift[i] = skip;
        }

        if(skip == i){
            skip = bpos[i];
        }
    }

}



int main(){
    freopen("input.txt", "r", stdin);
    freopen("a.txt", "w", stdout);

    string text;
    string pat;

    cin >> text >> pat;

    int n = text.size();
    int m = pat.size();

    int bpos[m+1], shift[m+1];

    good_character_heuristic(pat, m, bpos, shift);
    
    int s = 0, cnt = 0;
    while(s <= n - m){
        int j = m-1;
        while(j >= 0 && text[s + j] == pat[j]) j--;

        if(j < 0){
            cnt++;
            s += shift[0];
        }
        else{
            s += shift[j+1];
        }
    }

    cout << cnt << endl;
}
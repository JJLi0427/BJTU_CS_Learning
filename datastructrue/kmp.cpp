#include <iostream>
#include <cstring>
using namespace std;

void getNext(char *b, int lenb, int *next) {
    int now = 0, k = -1;
    next[0] = -1;
    while (now < lenb) {
        if (k == -1 || b[now] == b[k]) {
            now++;
            k++;
            next[now] = k;
        }
        else {
            k = next[k];
        }
    }
}

int KMP(char *a, char *b) {
    int lena = strlen(a);
    int lenb = strlen(b);
    
    int *next = new int[lenb];
    getNext(b, lenb, next);
    
    int i = 0, j = 0;
    while (i < lena && j < lenb) {
        if (j == -1 || a[i] == b[j]) {
            i++;
            j++;
        }
        else {
            j = next[j];
        }
    }
    
    delete[] next;
    
    if (j >= lenb) return (i - lenb);
    else return -1;
}

int main() {
    char a[] = "ABABDABACDABABCABAB";
    char b[] = "ABABCABAB";
    
    int index = KMP(a, b);
    
    if (index != -1) {
        cout << "Pattern found at index: " << index << endl;
    } else {
        cout << "Pattern not found in the text." << endl;
    }
    
    return 0;
}

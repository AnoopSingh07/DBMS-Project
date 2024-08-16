#include <bits/stdc++.h>
using namespace std;

class HashTable {
private:
    int N;
    int bucketSize;
    vector<int> h;
    vector<int> a;
    vector<int> b;
    int gd;  // global depth
    vector<int> ld;  // local depth
    /////////////////////////////////
    int settled;
    vector<int> unsettledH;
    vector<int> unsettledA;
    vector<int> unsettledB;

    void doubleHashTable() {
        int oldN = N;
        N = N*2;
        vector<int> newH(N, -1);
        vector<int> newA(N, -1);
        vector<int> newB(N, -1);
        vector<int> newLd(N, gd);


        // Rehash existing entries
        for (int i = 0; i < oldN; ++i) {
            if (h[i] != -1) {
                int oldIndex = h[i];
                newA[oldIndex] = a[oldIndex];
                newB[oldIndex] = b[oldIndex];
                newH[i] = oldIndex;
                newH[i + oldN] = oldIndex;
                newLd[oldIndex] = ld[oldIndex];
            }
        }

        h = newH;
        a = newA;
        b = newB;
        ld = newLd;
        ///////////////////////////////////
        unsettledH=h;
        unsettledA=a;
        unsettledB=b;
    }

    void settleKey(int key){
        int home=key%N;
        int index=unsettledH[home];
        int oldKeyA = unsettledA[index];
        int oldKeyB = unsettledB[index];
        // ld[index]++;//check  Doubt?

        unsettledH[home] = -1;
        int idx=0;
        while (unsettledA[idx] != -1||unsettledB[idx]!=-1) ++idx;
        unsettledA[idx] = key;
        unsettledH[home] = idx;
        ld[idx] = gd;

        int newHomeA=oldKeyA%N;
        int newHomeB=oldKeyB%N;
        if(unsettledH[newHomeA]==unsettledH[home]){
            unsettledA[index] = -1;
            int i = unsettledH[home];
            if(unsettledA[i]==-1){
                unsettledA[i] = oldKeyA;
            }else if (unsettledB[i] == -1) {
                unsettledB[i] = oldKeyA;
            } else {//means bucket is full
                if (gd == ld[i]) {
                    gd++;
                    doubleHashTable();
                    return;
                }
            }
        }

        if(unsettledH[newHomeB]==unsettledH[home]){
            unsettledB[index] = -1;
            int i = unsettledH[home];
            if(unsettledA[i]==-1){
                unsettledA[i] = oldKeyB;
            }else if (unsettledB[i] == -1) {
                unsettledB[i] = oldKeyB;
            } else {//means bucket is full
                if (gd == ld[i]) {
                    gd++;
                    doubleHashTable();
                    return;
                }
            }
        }

        settled=1;
        a=unsettledA;
        b=unsettledB;
        h=unsettledH;
        return;
    }

public:
    HashTable(int size, int bucketSize) : N(size), bucketSize(bucketSize), h(size, -1), a(size, -1), b(size, -1), gd(0), ld(size, 0), settled(1), unsettledH(size,-1), unsettledA(size,-1), unsettledB(size,-1) {}

    void insert(int key) {
        int home = key % N;
        if (h[home] == -1) {
            int index = 0;
            while (a[index] != -1||b[index]!=-1) ++index;
            a[index] = key;
            h[home] = index;
            ld[index] = gd;
        } else {
            int index = h[home];
            if(a[index]==-1){
                a[index] = key;
            }else if (b[index] == -1) {
                b[index] = key;
            } else {//means bucket is full
                if (gd == ld[index]) {
                    gd++;
                    doubleHashTable();
                    settled=0;
                    while(settled==0) settleKey(key);
                } else {
                    unsettledH=h;
                    unsettledA=a;
                    unsettledB=b;
                    settled=0;
                    while(settled==0) settleKey(key);
                }
            }
        }
    }

    void print() {
        cout << "Final output home: ";
        for (int i = 0; i < N; ++i) {
            if (h[i] == -1) cout << i << ":empty ";
            else cout << i << ":" << h[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < N; ++i) {
            if (a[i] != -1 || b[i] != -1) {
                cout << i << ": " << (a[i] == -1 ? -1 : a[i]) << " " << (b[i] == -1 ? -1 : b[i]) << endl;
            }
        }
    }
};

int main() {
    HashTable ht(1, 2);
    ht.insert(14);
    ht.insert(16);
    ht.print();
    ht.insert(18);
    ht.insert(15);
    ht.print();
    ht.insert(13);
    ht.print();
    return 0;
}

// int main() {
//     HashTable ht(5, 2);

//     // Insert keys
//     ht.insert(12);
//     ht.print();
//     ht.insert(14);
//     ht.print();
//     ht.insert(27);
//     ht.print();
//     ht.insert(35);
//     ht.print();
//     ht.insert(63);
//     ht.print();
//     ht.insert(44);
//     ht.print();
//     ht.insert(48);

//     // Print initial state
//     ht.print();

//     // Convert to extended hashing
//     ht.insert(79);
//     ht.print();
    
//     // More insertions
//     ht.insert(22);
//     ht.print();

//     ht.insert(60);
//     ht.print();
    
//     ht.insert(42);

//     // Print final state
//     ht.print();

//     return 0;
// }

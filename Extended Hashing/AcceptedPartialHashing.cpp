#include <bits/stdc++.h>
#include <iostream>
#include <map>
#include <vector>
#include <utility> // For std::pair

using namespace std;
// check do we need unsettled H,Ld?
class HashTable
{
private:
    int N;
    int bucketSize;
    map<pair<int, int>, int> h;
    vector<int> a;
    vector<int> b;
    // int gd;  // global depth
    vector<int> gd;
    vector<int> ld; // local depth
    /////////////////////////////////
    int underExtention;
    map<pair<int, int>, int> unsettledH;
    vector<int> unsettledA;
    vector<int> unsettledB;
    vector<int> unsettledLd;

    void split(pair<int, int> home, int key)
    {
        unsettledH = h;
        unsettledA = a;
        unsettledB = b;
        unsettledLd = ld;
        int index = unsettledH[home];
        int oldKeyA = unsettledA[index];
        int oldKeyB = unsettledB[index];

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if (ld[index] < gd[index] && underExtention == 0)
        { // will execute when partial extention is not required
            int idx = 0;
            while (unsettledA[idx] != -1 || unsettledB[idx] != -1)++idx; // inserting incoming key
            unsettledA[idx] = key;
            unsettledH[home] = idx;
            int n = home.first;
            gd[idx] = (log(n) / log(2));
            unsettledLd[idx] = gd[idx];

            int localDepth = ld[index];
            int tempN = home.first;
            pair<int, int> newHomeA = {tempN, oldKeyA % tempN};
            pair<int, int> newHomeB = {tempN, oldKeyB % tempN};
            if (unsettledH.find(newHomeA) != unsettledH.end() && unsettledH[newHomeA] == unsettledH[home])
            { // settling oldKeyA
                unsettledA[index] = -1;
                unsettledLd[index] = localDepth + 1;
                ld[index] = localDepth + 1;
                int i = unsettledH[home];
                if (unsettledA[i] == -1)
                {
                    unsettledA[i] = oldKeyA;
                }
                else if (unsettledB[i] == -1)
                {
                    unsettledB[i] = oldKeyA;
                }
                else
                { // means bucket is full
                    split(home, key);
                    return;
                }
            }

            if (unsettledH.find(newHomeB) != unsettledH.end() && unsettledH[newHomeB] == unsettledH[home])
            { // settling oldKeyB
                unsettledB[index] = -1;
                unsettledLd[index] = localDepth + 1;
                ld[index] = localDepth + 1;
                int i = unsettledH[home];
                if (unsettledA[i] == -1)
                {
                    unsettledA[i] = oldKeyB;
                }
                else if (unsettledB[i] == -1)
                {
                    unsettledB[i] = oldKeyB;
                }
                else
                { // means bucket is full
                    split(home, key);
                    return;
                }
            }
        }

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        else
        { // will execute when partial extention is required// ld[index]==gd[index]
            underExtention = 1;
            unsettledH.erase(home);
            h.erase(home);
            int n = home.first, rem = home.second;
            pair<int, int> newHome1 = {2 * n, rem};
            pair<int, int> newHome2 = {2 * n, rem + n};

            int pgd = (log(2 * n) / log(2));
            // gd=max(gd,pgd);
            gd[index] = pgd;
            unsettledA.push_back(-1);
            unsettledB.push_back(-1);
            a.push_back(-1);
            b.push_back(-1);
            gd.push_back(pgd);
            unsettledLd.push_back(gd[index]);
            ld.push_back(gd[index]);

            unsettledH[newHome1] = index;
            unsettledH[newHome2] = index;
            h[newHome1] = index;
            h[newHome2] = index;
            pair<int, int> newHomeKey;
            int curN;
            for (auto i : unsettledH)
            { // inserting incoming key
                int tempN = i.first.first;
                int tempRem = key % tempN;
                if (unsettledH.find({tempN, tempRem}) != unsettledH.end())
                {
                    newHomeKey = {tempN, tempRem};
                    unsettledH[newHomeKey] = -1;
                    curN = tempN;
                    int idx = 0;
                    while (unsettledA[idx] != -1 || unsettledB[idx] != -1)
                        ++idx;
                    unsettledA[idx] = key;
                    unsettledH[newHomeKey] = idx;
                    gd[idx] = gd[index];
                    unsettledLd[idx] = gd[idx];
                    ld[idx] = gd[idx]; // doubt
                    break;
                }
            }

            pair<int, int> newHomeA = {curN, oldKeyA % curN};
            pair<int, int> newHomeB = {curN, oldKeyB % curN};

            int localDepth = ld[index];
            if (unsettledH[newHomeA] == unsettledH[newHomeKey])
            { // settling oldKeyA
                unsettledA[index] = -1;
                unsettledLd[index] = localDepth + 1;
                int i = unsettledH[newHomeKey];
                if (unsettledA[i] == -1)
                {
                    unsettledA[i] = oldKeyA;
                }
                else if (unsettledB[i] == -1)
                {
                    unsettledB[i] = oldKeyA;
                }
                else
                { // means bucket is full
                    split(newHomeKey, key);
                    return;
                }
            }

            if (unsettledH[newHomeB] == unsettledH[newHomeKey])
            { // settling oldKeyB
                unsettledB[index] = -1;
                unsettledLd[index] = localDepth + 1;
                int i = unsettledH[newHomeKey];
                if (unsettledA[i] == -1)
                {
                    unsettledA[i] = oldKeyB;
                }
                else if (unsettledB[i] == -1)
                {
                    unsettledB[i] = oldKeyB;
                }
                else
                { // means bucket is full
                    split(newHomeKey, key);
                    return;
                }
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////
        underExtention = 0;
        a = unsettledA;
        b = unsettledB;
        h = unsettledH;
        ld = unsettledLd;
        return;
    }

public:
    HashTable(int size, int bucketSize) : N(size), bucketSize(bucketSize), h(), a(size, -1), b(size, -1), gd(size, 0), ld(size, 0), underExtention(0), unsettledH(), unsettledA(size, -1), unsettledB(size, -1), unsettledLd(size, 0) {}

    void insert(int key)
    {
        pair<int, int> home;
        if (h.size() == 0)
        {
            home = {N, key % N};
            a[0] = key;
            h[home] = 0;
            ld[0] = gd[0];
            return;
        }

        for (auto i : h)
        {
            int tempN = i.first.first;
            int tempRem = key % tempN;
            if (h.find({tempN, tempRem}) != h.end())
            {
                home = {tempN, tempRem};
                break;
            }
        }
        int index = h[home];
        if (a[index] == -1)
        {
            a[index] = key;
        }
        else if (b[index] == -1)
        {
            b[index] = key;
        }
        else
        { // means bucket is full
            split(home, key);
        }
    }

    void print()
    {
        cout << "Final output home: ";
        for (auto i : h)
        {
            if (i.second == -1)
                cout << i.first.first << "," << i.first.second << ":empty ";
            else
                cout << i.first.first << "," << i.first.second << ":" << i.second << " ";
        }
        cout << endl;
        for (int i = 0; i < h.size(); ++i)
        {
            if (a[i] != -1 || b[i] != -1)
            {
                cout << i << ": " << (a[i] == -1 ? -1 : a[i]) << " " << (b[i] == -1 ? -1 : b[i]) << endl;
            }
        }
    }
};

int main()
{
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

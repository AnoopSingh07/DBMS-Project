#include <bits/stdc++.h>
using namespace std;

class rootNode
{
public:
    int indicator, ind;
    rootNode *next;

    rootNode(int indicator, int ind)
    {
        this->indicator = indicator;
        this->ind = ind;
        next = NULL;
    }

    static vector<vector<int>> bucketList;
    static rootNode *first;
    
    static void insert(int x)
    {
        cout << "insert " << x << " ";
        if (first == NULL)
        {
            rootNode *newRoot = new rootNode(-1, 0);
            first = newRoot;
            if (bucketList.size() != 0)
                bucketList[0][0] = x;
            else
                bucketList.push_back({x});
            return;
        }

        rootNode *current = first;
        while (current->next != NULL && current->next->indicator < x)
        {
            current = current->next;
        }

        bucketList[current->ind].push_back(x);
        sort(bucketList[current->ind].begin(), bucketList[current->ind].end());

        if (bucketList[current->ind].size() == 4)
        {
            int medianIndicator = (bucketList[current->ind][1] + bucketList[current->ind][2]) / 2;
            rootNode *newRoot;
            int inserted = -1;
            for (int i = 0; i < bucketList.size(); i++)
            {
                if (bucketList[i][0] == -1)
                {
                    inserted = i;
                    newRoot = new rootNode(medianIndicator, i);
                    break;
                }
            }
            if (inserted == -1)
                newRoot = new rootNode(medianIndicator, bucketList.size());

            int ele1 = bucketList[current->ind][2];
            int ele2 = bucketList[current->ind][3];
            bucketList[current->ind].pop_back();
            bucketList[current->ind].pop_back();
            if (inserted != -1)
            {
                bucketList[inserted][0] = ele1;
                bucketList[inserted].push_back(ele2);
            }
            else
            {
                bucketList.push_back({ele1, ele2});
            }
            newRoot->next = current->next;
            current->next = newRoot;
            return;
        }
    }

    static void deleteNode(int x)
    {
        cout << "delete " << x << " ";
        if (first == NULL)
            return;

        rootNode *current = first;
        rootNode *prev = NULL;
        while (current->next != NULL && current->next->indicator < x)
        {
            prev = current;
            current = current->next;
        }
        vector<int> temp;
        for (int i = 0; i < bucketList[current->ind].size(); i++)
        {
            if (bucketList[current->ind][i] != x)
            {
                temp.push_back(bucketList[current->ind][i]);
            }
        }
        if (temp.size() == 1 && current->next != NULL)
        {
            if (bucketList[current->next->ind].size() == 3)
            {
                auto ele = bucketList[current->next->ind].begin();
                temp.push_back(*ele);
                bucketList[current->next->ind].erase(ele);
                if (current->next->indicator < temp.back())
                {
                    int e1 = temp.back();
                    int e2 = *bucketList[current->next->ind].begin();
                    current->next->indicator = (e1 + e2) / 2;
                }
            }
            else
            {
                for (auto i : bucketList[current->next->ind])
                {
                    temp.push_back(i);
                }
                while (bucketList[current->next->ind].size() != 0)
                {
                    bucketList[current->next->ind].pop_back();
                }
                bucketList[current->next->ind].push_back(-1);
                auto toDelete = current->next;
                current->next = current->next->next;
                delete (toDelete);
                if (current->next != NULL && current->next->indicator < temp.back())
                {
                    int e1 = temp.back();
                    int e2 = *bucketList[current->next->ind].begin();
                    current->next->indicator = (e1 + e2) / 2;
                }
            }
        }
        else if (temp.size() == 1 && bucketList[prev->ind].size() < 3)
        {
            bucketList[prev->ind].push_back(temp[0]);
            temp.clear();
            bucketList[current->ind].clear();
            bucketList[current->ind].push_back(-1);
            prev->next = NULL;
            return;
        }
        else if (temp.size() == 1 && bucketList[prev->ind].size() == 3)
        {
            int ele1 = bucketList[prev->ind][1];
            int ele2 = bucketList[prev->ind][2];
            int median = (ele1 + ele2) / 2;
            current->indicator = median;
            temp.insert(temp.begin(), ele2);
            bucketList[prev->ind].pop_back();
        }
        bucketList[current->ind] = temp;
        return;
    }

    static void pt()
    {
        cout << "root=[";
        rootNode *current = first;
        while (current != NULL)
        {
            if (current->indicator != -1)
                cout << current->indicator << ',';
            cout << current->ind;
            if (current->next != NULL)
            {
                cout << ',';
            }
            current = current->next;
        }
        cout << "]  ";

        if (first == NULL)
        {
            cout << endl;
            return;
        }

        current = first;
        while (current != NULL)
        {
            cout << current->ind << ":";
            int i = 0;
            for (auto ele : bucketList[current->ind])
            {
                cout << ele;
                if (i < 2)
                    cout << ',';
                i++;
            }
            while (i < 3)
            {
                cout << -1;
                if (i < 2)
                    cout << ',';
                i++;
            }
            cout << "  ";
            current = current->next;
        }
        cout << endl;
    }
};

vector<vector<int>> rootNode::bucketList;
rootNode *rootNode::first = NULL;

int main()
{
    rootNode::pt();
    rootNode::insert(12);
    rootNode::pt();
    rootNode::insert(26);
    rootNode::pt();
    rootNode::insert(19);
    rootNode::pt();
    rootNode::insert(30);
    rootNode::pt();
    rootNode::insert(25);
    rootNode::pt();
    rootNode::insert(17);
    rootNode::pt();
    rootNode::insert(10);
    rootNode::pt();
    rootNode::insert(23);
    rootNode::pt();
    rootNode::insert(15);
    rootNode::pt();
    rootNode::deleteNode(12);
    rootNode::pt();
    rootNode::deleteNode(10);
    rootNode::pt();
    rootNode::insert(34);
    rootNode::pt();
    rootNode::insert(36);
    rootNode::pt();
    rootNode::insert(38);
    rootNode::pt();
    rootNode::insert(31);
    rootNode::pt();
    rootNode::deleteNode(36);
    rootNode::pt();
    rootNode::deleteNode(38);
    rootNode::pt();
    rootNode::deleteNode(34);
    rootNode::pt();
    return 0;
}
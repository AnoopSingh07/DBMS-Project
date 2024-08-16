#include <bits/stdc++.h>
using namespace std;

class tree
{
public:
    static int root;
    static vector<vector<int>> nodes;

    static void settlePath(int nodeRoot)
    {
        vector<int> left;
        vector<int> right;
        for (int i = 0; i < 7; i++)
        {
            if (i < 3)
                left.push_back(nodes[nodeRoot][i]);
            if (i > 3)
                right.push_back(nodes[nodeRoot][i]);
        }
        int indicator = nodes[nodeRoot][3];
        int l = 50;
        while (l<nodes.size()&&!nodes[l].empty())
            l++;
        if (l == nodes.size())
            nodes.push_back(left);
        else
        {
            nodes[l]=left;
        }
        int r = 50;
        while (r<nodes.size()&&!nodes[r].empty())
            r++;
        if (r == nodes.size())
            nodes.push_back(right);
        else
        {
            nodes[r]=right;
        }
        vector<int> newInternalNode = {l, indicator, r};
        nodes[nodeRoot] = newInternalNode;
        return;
    }

    static void insert(int x)
    {
        cout << "insert " << x << " ";
        if (root == -1)
        {
            root = 0;
            nodes[0].push_back(x);
            return;
        }

        if (root <50)
        {
            nodes[root].push_back(x);
            sort(nodes[root].begin(), nodes[root].end());
            if (nodes[root].size() == 4)
            { //need to modify
                int indicator = (nodes[root][1] + nodes[root][2]) / 2;
                int i = 0;
                while (!nodes[i].empty() && i < 50)
                {
                    i++;
                }
                nodes[i].push_back(nodes[root][2]);
                nodes[i].push_back(nodes[root][3]);
                nodes[root].pop_back();
                nodes[root].pop_back();
                int newInd = 50;
                vector<int>newNode={root, indicator, i};
                while (newInd<nodes.size()&&!nodes[newInd].empty())newInd++;
                if (newInd == nodes.size())nodes.push_back(newNode);
                else
                {
                    nodes[newInd]=newNode;
                }
                root = 50;
            }
            return;
        }

        if (root >= 50)
        {
            int leafRoot = root;
            int nodeRoot = root;
            while (leafRoot >= 50)
            {
                int i = 1;
                nodeRoot = leafRoot;
                while (i < nodes[leafRoot].size() && nodes[leafRoot][i] < x)
                {
                    i += 2;
                }
                if (i == nodes[leafRoot].size())
                {
                    i -= 2;
                    leafRoot = nodes[leafRoot][i + 1];
                }
                else
                {
                    leafRoot = nodes[leafRoot][i - 1];
                }
            }
            // leaf node
            nodes[leafRoot].push_back(x);
            sort(nodes[leafRoot].begin(), nodes[leafRoot].end());
            if (nodes[leafRoot].size() == 4)
            {
                int indicator = (nodes[leafRoot][1] + nodes[leafRoot][2]) / 2;
                int i = 0;
                while (!nodes[i].empty() && i < 50)
                {
                    i++;
                }
                if (i == 50)
                {
                    cout << "no vacant bucket available to insert: " << x << endl;
                    return;
                }
                else
                {
                    nodes[i].push_back(nodes[leafRoot][2]);
                    nodes[i].push_back(nodes[leafRoot][3]);
                    nodes[leafRoot].pop_back();
                    nodes[leafRoot].pop_back();
                    vector<int> temp;
                    int j = 0;
                    while (nodes[nodeRoot][j] != leafRoot)
                    {
                        temp.push_back(nodes[nodeRoot][j]);
                        temp.push_back(nodes[nodeRoot][j + 1]);
                        j += 2;
                    }
                    temp.push_back(leafRoot);
                    temp.push_back(indicator);
                    temp.push_back(i);
                    j += 3;
                    while (j - 2 < nodes[nodeRoot].size())
                    {
                        temp.push_back(nodes[nodeRoot][j - 2]);
                        temp.push_back(nodes[nodeRoot][j - 1]);
                        j += 2;
                    }
                    nodes[nodeRoot] = temp;
                    if (temp.size() == 7)
                    {
                        settlePath(nodeRoot);
                    }
                    return;
                }
            }
            return;
        }
    }

    static void pt()
    {
        if (root == -1)
        {
            cout << "no leafs in tree" << endl;
            return;
        }
        cout << "root " << root << " ";
        if (root == 0)
        {
            cout << " 0: ";
            int i = 0;
            while (i < 3)
            {
                if (i < nodes[0].size())
                    cout << nodes[0][i] << " ";
                else
                    cout << "-1 ";
                i++;
            }
            cout << endl;
            return;
        }
        if (root >= 50)
        {
            for (int i = 50; i < nodes.size(); i++)
            {   
                if (!nodes[i].empty())
                {
                    cout << " " << i << ":";
                    for (int j = 0; j < nodes[i].size(); j++)
                    {
                        cout << nodes[i][j] << " ";
                    }
                }
            }
            for (int i = 0; i < 50; i++)
            {
                if (!nodes[i].empty())
                {
                    cout << " " << i << ":";
                    int j = 0;
                    while (j < 3)
                    {
                        if (j < nodes[i].size())
                            cout << nodes[i][j] << " ";
                        else
                            cout << "-1 ";
                        j++;
                    }
                }
            }
            cout << endl;
            return;
        }
    }

    static void settleInternalNodes(int indToCheck,vector<int>&internalNodePath){
        int nodeRoot=internalNodePath.back();
        internalNodePath.pop_back();
        int rootNodeRoot=-1;
        if(internalNodePath.size()>0)rootNodeRoot=internalNodePath.back();
        internalNodePath.pop_back();
        int rootRootNodeRoot=-1;
        if(internalNodePath.size()>0)rootRootNodeRoot=internalNodePath.back();
        auto it = find(nodes[nodeRoot].begin(), nodes[nodeRoot].end(), indToCheck);
        nodes[nodeRoot].erase(it);
        nodes[nodeRoot].erase(it-1);
        if(nodes[nodeRoot].size()==1){
            int siblingIndex=-1;
            bool siblingInLeft=true;
            int indicatorInd;
            if(rootNodeRoot==-1){
                root=0;
                nodes[nodeRoot].clear();
                return;
            }
            else{
            for (int i = 0; i < nodes[rootNodeRoot].size(); i += 2)
            {
                if (nodes[rootNodeRoot][i] == nodeRoot)
                {
                    if (i > 0)
                    {
                        siblingIndex = nodes[rootNodeRoot][i - 2];
                        indicatorInd=i - 1;
                    }
                    else if (i + 2 < nodes[rootNodeRoot].size())
                    {
                        siblingInLeft=false;
                        siblingIndex = nodes[rootNodeRoot][i + 2];
                        indicatorInd=i + 1;
                    }
                    break;
                }
            }
            }

            if (siblingIndex != -1 && nodes[siblingIndex].size() > 3)
            {
                // Borrow from sibling
                if (siblingInLeft)
                {
                    nodes[nodeRoot].insert(nodes[nodeRoot].begin(), nodes[rootNodeRoot][indicatorInd]);
                    nodes[nodeRoot].insert(nodes[nodeRoot].begin(), nodes[siblingIndex].back());
                    nodes[siblingIndex].pop_back();
                    nodes[rootNodeRoot][indicatorInd]=nodes[siblingIndex].back();
                    nodes[siblingIndex].pop_back();
                }
                else
                {
                    nodes[nodeRoot].push_back(nodes[rootNodeRoot][indicatorInd]);
                    nodes[nodeRoot].push_back(nodes[siblingIndex][0]);
                    nodes[siblingIndex].erase(nodes[siblingIndex].begin());
                    nodes[rootNodeRoot][indicatorInd]=nodes[siblingIndex][0];
                    nodes[siblingIndex].erase(nodes[siblingIndex].begin());
                }
            }
            else if (siblingIndex != -1)
            {
                // Merge with sibling
                if(nodes[rootNodeRoot].size()>3){
                if (siblingInLeft)
                {
                    nodes[siblingIndex].push_back(nodes[rootNodeRoot][indicatorInd]);
                    nodes[siblingIndex].push_back(nodes[nodeRoot][0]);
                    nodes[nodeRoot].clear();
                    vector<int>temp;
                    int idx=0;
                    while(idx<nodes[rootNodeRoot].size()){
                        if(nodes[rootNodeRoot][idx]!=nodeRoot&&idx!=indicatorInd){
                            temp.push_back(nodes[rootNodeRoot][idx]);
                        }
                        idx++;
                    }
                    nodes[rootNodeRoot]=temp;
                }
                else
                {
                    nodes[nodeRoot].push_back(nodes[rootNodeRoot][indicatorInd]);
                    nodes[nodeRoot].insert(nodes[nodeRoot].end(), nodes[siblingIndex].begin(), nodes[siblingIndex].end());
                    nodes[siblingIndex].clear();
                    vector<int>temp;
                    int idx=0;
                    while(idx<nodes[rootNodeRoot].size()){
                        if(nodes[rootNodeRoot][idx]!=siblingIndex&&idx!=indicatorInd){
                            temp.push_back(nodes[rootNodeRoot][idx]);
                        }
                        idx++;
                    }
                    nodes[rootNodeRoot]=temp;
                }
                }
                else{//nodes[rootNodeRoot].size()==3
                if (siblingInLeft)
                {
                    nodes[siblingIndex].push_back(nodes[rootNodeRoot][indicatorInd]);
                    nodes[siblingIndex].push_back(nodes[nodeRoot][0]);
                    int toDetete=siblingIndex;
                    nodes[nodeRoot].clear();
                    if(rootRootNodeRoot==-1){
                        nodes[rootNodeRoot]=nodes[siblingIndex];
                        nodes[toDetete].clear();
                        return;
                    }else{
                    for(int i=0;i<nodes[rootRootNodeRoot].size();i+=2){
                        if(nodes[rootRootNodeRoot][i]==rootNodeRoot){
                            nodes[rootNodeRoot]=nodes[siblingIndex];
                            nodes[siblingIndex].clear();
                            break;
                        }
                    }
                    }
                }
                else
                {
                    nodes[nodeRoot].push_back(nodes[rootNodeRoot][indicatorInd]);
                    nodes[nodeRoot].insert(nodes[nodeRoot].end(), nodes[siblingIndex].begin(), nodes[siblingIndex].end());
                    int toDelete=nodeRoot;
                    nodes[siblingIndex].clear();
                    if(rootRootNodeRoot==-1){
                        nodes[rootNodeRoot]=nodes[nodeRoot];
                        nodes[toDelete].clear();
                        return;
                    }
                    else{
                    for(int i=0;i<nodes[rootRootNodeRoot].size();i+=2){
                        if(nodes[rootRootNodeRoot][i]==rootNodeRoot){
                            nodes[rootNodeRoot]=nodes[nodeRoot];
                            nodes[nodeRoot].clear();
                            break;
                        }
                    }
                    }
                };
                }
            }
    }
    return;
}

    static void deleteLeaf(int x)
    {
        cout<<"delete "<<x<<" ";
        if (root == -1)
        {
            cout << "Tree is empty." << endl;
            return;
        }

        if (root <50)
        {
        auto it = find(nodes[root].begin(), nodes[root].end(), x);
        if (it != nodes[root].end())
        {
            nodes[root].erase(it);
            if(nodes[root].empty())root=-1;
            return;
        }
        }

        if(root>=50){
        int leafRoot = root;
        int nodeRoot = root;
        vector<int>internalNodePath;
        while (leafRoot >= 50)
        {
            int i = 1;
            internalNodePath.push_back(leafRoot);
            nodeRoot = leafRoot;
            while (i < nodes[leafRoot].size() && nodes[leafRoot][i] < x)
            {
                i += 2;
            }
            if (i == nodes[leafRoot].size())
            {
                i -= 2;
                leafRoot = nodes[leafRoot][i + 1];
            }
            else
            {
                leafRoot = nodes[leafRoot][i - 1];
            }
        }

        auto it = find(nodes[leafRoot].begin(), nodes[leafRoot].end(), x);
        if (it != nodes[leafRoot].end())
        {
            nodes[leafRoot].erase(it);
            if (nodes[leafRoot].size() < 2)
            {
                // Handle underflow
                int siblingIndex = -1;
                bool siblingInLeft=true;
                int modifyIndicatorAt;
                for (int i = 0; i < nodes[nodeRoot].size(); i += 2)
                {
                    if (nodes[nodeRoot][i] == leafRoot)
                    {
                        if (i > 0)
                        {
                            siblingIndex = nodes[nodeRoot][i - 2];
                            modifyIndicatorAt=i-1;
                        }
                        else if (i + 2 < nodes[nodeRoot].size())
                        {
                            siblingInLeft=false;
                            siblingIndex = nodes[nodeRoot][i + 2];
                            modifyIndicatorAt=i+1;
                        }
                        break;
                    }
                }

                if (siblingIndex != -1 && nodes[siblingIndex].size() > 2)
                {
                    // Borrow from sibling
                    int extremeLeftEle,extremeRightEle;
                    if (siblingInLeft)
                    {
                        nodes[leafRoot].insert(nodes[leafRoot].begin(), nodes[siblingIndex].back());
                        nodes[siblingIndex].pop_back();
                        extremeLeftEle=nodes[leafRoot][0];
                        extremeRightEle=nodes[siblingIndex].back();
                    }
                    else
                    {
                        nodes[leafRoot].push_back(nodes[siblingIndex][0]);
                        nodes[siblingIndex].erase(nodes[siblingIndex].begin());
                        extremeLeftEle=nodes[siblingIndex][0];
                        extremeRightEle=nodes[leafRoot].back();
                    }
                    int newIndicator=(extremeLeftEle+extremeRightEle)/2;
                    nodes[nodeRoot][modifyIndicatorAt]=newIndicator;
                }
                else if (siblingIndex != -1)
                {
                    // Merge with sibling
                    int IndToCheck=-1;
                    if (siblingInLeft)
                    {
                        nodes[siblingIndex].insert(nodes[siblingIndex].end(), nodes[leafRoot].begin(), nodes[leafRoot].end());
                        nodes[leafRoot].clear();
                        IndToCheck=leafRoot;
                    }
                    else
                    {
                        nodes[leafRoot].insert(nodes[leafRoot].end(), nodes[siblingIndex].begin(), nodes[siblingIndex].end());
                        nodes[siblingIndex].clear();
                        IndToCheck=siblingIndex;
                    }
                    settleInternalNodes(IndToCheck,internalNodePath);
                }
            }
        }
        else
        {
            cout << "Element not found in leaf nodes." << endl;
        }
    }
    }
};

int tree::root = -1;
vector<vector<int>> tree::nodes(50);

int main()
{
    tree::insert(12);
    tree::pt();
    tree::insert(26);
    tree::pt();
    tree::insert(19);
    tree::pt();
    tree::insert(30);
    tree::pt();
    tree::insert(25);
    tree::pt();
    tree::insert(17);
    tree::pt();
    tree::insert(10);
    tree::pt();
    // tree::insert(20);
    // tree::pt();
    tree::insert(23);
    tree::pt();
    tree::deleteLeaf(12);
    tree::pt();
    tree::deleteLeaf(19);
    tree::pt();
    tree::deleteLeaf(12);
    tree::pt();
    tree::deleteLeaf(10);
    tree::pt();
    tree::deleteLeaf(26);
    tree::pt();
    tree::deleteLeaf(17);
    tree::pt();
    tree::deleteLeaf(23);
    tree::pt();
    tree::deleteLeaf(30);
    tree::pt();
    tree::deleteLeaf(25);
    tree::pt();
    /////////////////////////
    cout<<"reinserting"<<endl;
    tree::insert(12);
    tree::pt();
    tree::insert(26);
    tree::pt();
    tree::insert(19);
    tree::pt();
    tree::insert(30);
    tree::pt();
    tree::insert(25);
    tree::pt();
    tree::insert(17);
    tree::pt();
    tree::insert(10);
    tree::pt();
    tree::insert(23);
    tree::pt();
    return 0;
}
//
//  main.cpp
//  hashTable95
//
//  Created by Md. Raihan Sobhan on 2/8/22.
//


#include <iostream>
#include <vector>
#include<list>
#include<queue>
#include<map>
#include <set>
using namespace std;

int max= INT_MAX;
int min= INT_MIN;
vector<string> keys;

string generateString()
{
    string temp="";
    int i=7;
    while (i--) {
        temp+= ('a'+(rand()%26));
    }

    return temp;

}

void generateKeyHelper(int size, set<string> stringSet){
    while(true)
    {
        string temp = generateString();
        if(stringSet.find(temp)==stringSet.end())
        {
            keys.push_back(temp);

        }
        stringSet.insert(temp);
        if(stringSet.size()==size) break;
    }
}

void keyGenerator(int n)
{
    set<string> stringSet;
    generateKeyHelper(n, stringSet);
    
}

int h1(string st)
{
    
    int hash = 0;
    int pPow = 1;
    int prime = 97;
    int maxi=1e9+7;
    
    for(int i=0; i<st.length(); i++)
    {
        hash=((hash +(st[i]-'a'+1)*pPow)%maxi);
        pPow = (pPow * prime) % maxi;
    }

    return hash;

}

int h2(string st)
{
    int hash = 0;
    int pPow = 1;
    int prime = 59;
    int maxi=1e9+9;
    
    for(int i=0; i<st.length(); i++)
    {
        hash=((hash +(st[i]-'a'+1)*pPow)%maxi);
        pPow = (pPow * prime) % maxi;
    }

    return hash;
}

class linkNode
{
public:
    linkNode* nextNode;
    int value;
    string key;
    
    linkNode(string key,int value)
    {
        nextNode=nullptr;
        this->key=key;
        this->value=value;
    }
    ~linkNode(){
        delete this->nextNode;
    }
};


class SeparateChaining
{
public:
    int n;
    vector<linkNode*> vec;
    SeparateChaining(int n)
    {
        this->n=n;
        int m=n;
        while (m--) {
            vec.push_back(new linkNode("hh",-1));
        }
    }

    void Insert(string key, int value)
    {
        int v = h1(key)%n;
        
        linkNode* node = vec[v];

        while(true)
        {
            if(node->nextNode!=nullptr){
                node=node->nextNode;
            }
            else{
                break;
            }

        }
        node->nextNode = new linkNode(key,value);

    }
    
    void Delete(string key)
    {
        int v = h1(key)%n;

        linkNode* node=vec[v];
        
        while(true)
        {
            if(node->nextNode!=nullptr){
                if(node->nextNode->key==key)
                {
                    node->nextNode=node->nextNode->nextNode;
                    break;
                }
                node=node->nextNode;
            }
            else{
                break;
            }
        }
    }

    int Search(string key)
    {
        int flag=-1;
        int v = h1(key)%n;

        linkNode* node = vec[v];
        while(true)
        {
            if(node->nextNode!=nullptr){
                if(key == node->nextNode->key)
                    flag=node->nextNode->value;
                node=node->nextNode;
            }
            else{
                break;
            }
        }

        return flag;
    }

    
    

    void printAll()
    {
        linkNode* node ;
        for(int i=0; i<n; i++)
        {
            cout<<i<<" ";
            node=vec[i];
            while(node->nextNode!=nullptr)
            {
                cout<<node->nextNode->key<<","<<node->nextNode->value<<" ";
                node=node->nextNode;
            }
            cout<<endl;
        }
    }
};


class LinProbing
{
    int n;
    pair<string,int> *pr;
    int cnt=0;
public:
    LinProbing(int n)
    {
        this->n = n;
        this->cnt=0;
        pr = new pair<string,int>[n];
        int i=0;
        int m= n;
        while(m--){
            pr[i] = {"",0};
            i++;
        }

    }
    
    void insertHelper(pair<string, int> st, int size){
        for(int i=0; i<n; i++){
            int p = (size+i)%n;
            if(pr[p].first=="" || pr[p].first=="0"){
                pr[p]= st;
                break;
            }
        }
    }

    void Insert(pair<string,int> st)
    {
        int size =h1(st.first);
        insertHelper(st, size);
    }
    
    bool Delete(string st){
        int p = Search(st);
        if(p==-1) return false;
        else{
            pr[p] = {"0",0};
        }
        return true;
    }

    
    int Search(string st){
        int size=h1(st);
        int p;
        for(int i=0; i<n; i++){
            p = (size+i)%n;
            if(i>0) cnt++;
            if(pr[p].first==st) return p;
            if(pr[p].first==""){
                break;
            }
        }
        return -1; // not found
    }

    
    void printAll()
    {
        for(int i=0; i<n; i++){
            cout<<pr[i].first<<" "<<pr[i].second<<endl;
        }
    }

};


class quadProbing
{
    int n;
    pair<string,int> *pr;
public:
    int cnt=0;
    quadProbing(int n)
    {
        pr = new pair<string,int>[n];
        this->cnt=0;
        this->n = n;
        int m= n;
        int i=0;
        while (m--) {
            pr[i] = {"",0};
            i++;
        }
    }

    void insertHelper(pair<string, int> st, int size){
        for(int i=0; i<n; i++){
            int p=0;
            p = (size+ 13*i + 19*i*i)%n;
            if(pr[p].first=="" || pr[p].first=="0"){
                pr[p]=st;
                break;
            }
        }
    }
    
    void Insert(pair<string,int> st)
    {
        int size =h1(st.first);
        insertHelper(st, size);
        
    }
    
    bool Delete(string st){
        int pos = Search(st);
        if(pos==-1) return false;
        else{
            pr[pos] = {"0",0};
        }
        return true;
    }
    
    
    
    int Search(string st){
        int size=h1(st);
        for(int i=0; i<n; i++){
            int p=0;
            p=(size+ 13*i +  19*i*i)%n;
            if(i>0) cnt++;
            if(pr[p].first==st) return p;
            if(pr[p].first==""){
                break;
            }
        }
        return -1;
    }

   
    void printAll()
    {
        for(int i=0; i<n; i++){
            cout<<pr[i].first<<' '<<pr[i].second<<endl;
        }
    }

};




int main()
{
    int n;
    
    
    
    cin>>n;
    
    

    keyGenerator(n);

    LinProbing *hash = new LinProbing(n);
    cout<<"Insert starts"<<endl;
    for(int j = 0; j<n; j++)
        hash->Insert(make_pair(keys[j],j+1));
    
    hash->printAll();
    cout<<"inserted"<<endl;
    cout<<"search starts"<<endl;
    for(int j = 0; j<n/2; j++)
        hash->Search(keys[j]);
    cout<<"deletion starts"<<endl;
    for(int j = 0; j<n/2; j++){
        if(!hash->Delete(keys[j])) cout<<"Can't delete, not found";
    }
    
    hash->printAll();
    
    
    SeparateChaining *hash1 = new SeparateChaining(n);
    cout<<"Insert starts"<<endl;
    for(int j = 0; j<n; j++)
        
        hash1->Insert(keys[j],j+1);
    
    hash1->printAll();
    cout<<"inserted"<<endl;
    cout<<"search starts"<<endl;
    for(int j = 0; j<n/2; j++)
        hash1->Search(keys[j]);
    cout<<"deletion starts"<<endl;
    for(int j = 0; j<n/2; j++){
        hash1->Delete(keys[j]);
    }
    
    hash1->printAll();

    
    
    quadProbing *hash2 = new quadProbing(n);
    cout<<"Insert starts"<<endl;
   for(int j = 0; j<n; j++)
       
       hash2->Insert(make_pair(keys[j],j+1));
   
   hash2->printAll();
   cout<<"inserted"<<endl;
    
    cout<<"search starts"<<endl;
   for(int j = 0; j<n/2; j++)
       hash2->Search(keys[j]);
    
    cout<<"delete starts"<<endl;
   for(int j = 0; j<n/2; j++){
       if(!hash2->Delete(keys[j])) cout<<"Can't delete, not found";
   }
   
   hash2->printAll();
    
    
    

}

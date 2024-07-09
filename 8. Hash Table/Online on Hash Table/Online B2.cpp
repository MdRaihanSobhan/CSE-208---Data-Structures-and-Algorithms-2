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
#include <algorithm>
using namespace std;

int max= INT_MAX;
int min= INT_MIN;
int prime1=97;
int prime2=59;
vector<string> keys;


bool isPrime(int n)
{
    if (n <= 1)  return false;
    if (n <= 3)  return true;
    if (n%2 == 0 || n%3 == 0) return false;
   
    for (int i=5; i*i<=n; i=i+6)
        if (n%i == 0 || n%(i+2) == 0)
           return false;
   
    return true;
}
 
int nextPrime(int N)
{
    if (N <= 1)
        return 2;
 
    int prime = N;
    bool get = false;
    while (!get) {
        prime++;
 
        if (isPrime(prime))
            get = true;
    }
 
    return prime;
}

int prevPrime(int N){
    if (N <= 1)
        return 2;
 
    int prime = N;
    bool get = false;
    while (!get) {
        prime--;
 
        if (isPrime(prime))
            get = true;
    }
 
    return prime;
}


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
    int maxi=1e9+7;
    
    for(int i=0; i<st.length(); i++)
    {
        hash=((hash +(st[i]-'a'+1)*pPow)%maxi);
        pPow = (pPow * prime1) % maxi;
    }

    return hash;

}

int h2(string st)
{
    int hash = 0;
    int pPow = 1;
    int maxi=1e9+9;
    
    for(int i=0; i<st.length(); i++)
    {
        hash=((hash +(st[i]-'a'+1)*pPow)%maxi);
        pPow = (pPow * prime2) % maxi;
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
    int maxLength=0 ;
    SeparateChaining(int n)
    {
        this->maxLength=0;
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
    
        int tempLength=1;

        while(true)
        {
            if(node->nextNode!=nullptr){
                node=node->nextNode;
                tempLength++;
            }
            else{
                break;
            }

        }
        node->nextNode = new linkNode(key,value);
        if(tempLength>maxLength)
            maxLength=tempLength;
        
        

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



class DoubleHashing
{
    int n;
    pair<string,int> *pr;
    int cnt=0;
public:
    DoubleHashing(int n)
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
        int size =h1(st.first) + h2(st.first);
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
        int size=h1(st) + h2(st);
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






int main()
{
    int n;
    double prob_factor;
    cin>>n;
    cin>>prob_factor;
    keyGenerator(n);
    
    
    auto start = std::chrono::high_resolution_clock::now();

    SeparateChaining *hash = new SeparateChaining(n);
    
    // cout<<"Insert starts"<<endl;
    for(int j = 0; j<n; j++){
        hash->Insert(keys[j],j+1);
    }
    
    auto end =std::chrono::high_resolution_clock::now();
    
    
    
    cout<<"Maximum Length before rehashing is "<<hash->maxLength<<endl;
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    cout<<"Time taken before rehashing is";
    cout<<duration.count()<<"microseconds"<<endl;
    
    
    
    start = std::chrono::high_resolution_clock::now();
        
    SeparateChaining *hash1 = new SeparateChaining(n);
    
    // cout<<"Insert starts"<<endl;
    for(int j = 0; j<n; j++){
        
        if(j%100==0 && hash1->maxLength>10){
            prime1= nextPrime(prime1);
        }
        
        hash1->Insert(keys[j],j+1);
        
    }
    end =std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    
    
    cout<<"Maximum length after rehashing is "<<hash1->maxLength<<endl;
        
    cout<<"Time taken after rehashing is";
    cout<<duration.count()<<"microseconds"<<endl;
    
    
    start = std::chrono::high_resolution_clock::now();
    
    for(int j = 0; j<n; j++){
        hash->Delete(keys[j]);
    }
    
    
    end =std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    
    cout<<"Time taken for deletion before rehashing is";
    cout<<duration.count()<<"microseconds"<<endl;
    
    
    
    start = std::chrono::high_resolution_clock::now();
    for(int j = 0; j<n; j++){
        
        if(j%100==0 && hash1->maxLength<3){
            prime1=prevPrime(prime1);
        }
        
        hash1->Delete(keys[j]);
        
    }
    end =std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    
    
    cout<<"Time taken for deletion after rehashing is";
    cout<<duration.count()<<"microseconds"<<endl;
    
}

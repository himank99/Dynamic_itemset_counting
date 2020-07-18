//DATE : 17 OCTOBER 2019


#include<bits/stdc++.h>
using namespace std;
ifstream fin;
double minfre;
vector<set<string> >datatable;
set<string>products;
map<string,int>freq;
map<string,int>f,f1;
set<string> dic(vector<set<string> > transac,set<string> dc);
set<string> add(set<string> ss,set<string> ds,set<string> dc,int c);
vector<string> wordsof(string str)                    //returns the string array of str
{
    vector<string> tmpset;
    string tmp="";
    int i=0;
    while(str[i])
    {
        if(isalnum(str[i]))tmp+=str[i];
        else {
            if(tmp.size()>0)
                tmpset.push_back(tmp);
            tmp="";
        }
        i++;
    }
    if(tmp.size()>0)tmpset.push_back(tmp);
    return tmpset;
}

string combine(vector<string> &arr,int miss)                    //combines the strings in the array and return the combined string...
{
    string str;
    for(int i=0;i<arr.size();i++)
        if(i!=miss)str+=arr[i]+" ";
    str=str.substr(0,str.size()-1);
    return str;
}

set<string> cloneit(set<string>&arr)
{
    set<string>dup;
    for(set<string>::iterator it=arr.begin();it!=arr.end();it++)dup.insert(*it);
    return dup;
}

set<string> apriori_gen(set<string>&sets,int k)
{
    set<string>set2;
    for(set<string>::iterator it1=sets.begin();it1!=sets.end();it1++)
    {
        set<string>::iterator it2=it1;
        it2++;
        for(;it2!=sets.end();it2++)
        {
            vector<string>v1=wordsof(*it1);
            vector<string>v2=wordsof(*it2);
            
            bool alleq=true;
            for(int i=0;i<k-1&&alleq;i++)
                if(v1[i]!=v2[i])
                    alleq=false;
            if(!alleq)continue;
            
            v1.push_back(v2[k-1]);
            if(v1[v1.size()-1]<v1[v1.size()-2])
                swap(v1[v1.size()-1],v1[v1.size()-2]);
            
            for(int i=0;i<v1.size()&&alleq;i++)
            {
                string tmp=combine(v1,i);                            // prune step.....
                if(sets.find(tmp)==sets.end())alleq=false;
            }
            
            if(alleq)set2.insert(combine(v1,-1));
        }
    }
    return set2;
}

int main()
{
    fin.open("doc.txt");
    minfre=2;
    if(fin.is_open())
        {
            cout<<endl;
        }
    else
        return 0;
    
    string str;
    while(!fin.eof())
    {
        getline(fin,str);
        vector<string>arr=wordsof(str);                                        //taking data from file ,
        set<string>tmpset;                                                    //creating datatable and
        for(int i=0;i<arr.size();i++)
            tmpset.insert(arr[i]);                    // generating one-itemsets...
        datatable.push_back(tmpset);
        for(set<string>::iterator it=tmpset.begin();it!=tmpset.end();it++)
        {
            products.insert(*it);
            freq[*it]++;
        }
    }
    fin.close();
    set<string> dic1=dic(datatable,products);
    for(set<string>::iterator it=dic1.begin();it!=dic1.end();it++)
        cout<<*it<<" ";
    return 0;
}
//dc all 1 itemset
//M transactions in T transactions
int compare(string s,set<string> t)
{
    int flag;
    for(int i=0;i<s.size();i+=2)
    {
        string str="";
        str+=s[i];
        str+=s[i+1];
        flag=0;
        for(set<string>::iterator it=t.begin();it!=t.end();it++)
        {
            if(*it==str)
            {
                flag=1;
                break;
            }
        }
        if(flag==0)
            return flag;
    }
    return flag;
}
set<string> dic(vector<set<string> >transac,set<string> dc)
{
    set<string> ss,sc,ds;
    int min_freq=2;
    int m=3;
    int k=0;
    int c=0;
    int temp=0;
    while(ds.size()!=0 || dc.size()!=0)
    {
        c++;
//        if(c==4)
//            return dc;
        //read M transactions from database table transac
        vector<set<string> > M;
        for(int i=k;i<m+k;i++)
        {
           set<string> t=transac[i];
            int flag=0;
            for(set<string>::iterator it1=dc.begin();it1!=dc.end();it1++)
            if(f1[*it1]<transac.size())
            {
                flag=compare(*it1,t);
                f[*it1]+=flag;
                f1[*it1]++;
            }
            for(set<string>::iterator it1=ds.begin();it1!=ds.end();it1++)
            if(f1[*it1]<transac.size())
            {
                flag=compare(*it1,t);
                f[*it1]+=flag;
                f1[*it1]++;
            }
        }
        k+=m;
        for(auto it=dc.begin();it!=dc.end();)
        {
            if(f[*it]>=min_freq)
            {
                ds.insert(*it);
                it=dc.erase(it);
            }
            else
                it++;
        }
        dc=add(ss,ds,dc,c); // for super set
        if(k==transac.size())
        {
            k=0;
            for(auto it=dc.begin();it!=dc.end();)
            {
                if(f1[*it]>=transac.size())
                {
                    sc.insert(*it);
                    it=dc.erase(it);
                }
                else
                    it++;
            }
            for(auto it=ds.begin();it!=ds.end();)
            {
                if(f1[*it]>=transac.size())
                {
                    ss.insert(*it);
                    it=ds.erase(it);
                }
                else
                    it++;
            }
        }
    }
//    cout<<f["I1I4"]<<" ";
    return ss;
}
int ck(string s)
{
    int count=0;
    for(int i=0;i<s.size();i++)
        if(s[i]=='I')
            count++;
    return count;
}
string form(string s1,string s2)
{
    set<char> item;
    for(int i=1;i<s1.size();i+=2)
    {
        item.insert(s1[i]);
        item.insert(s2[i]);
    }
    string str="";
    for(set<char>::iterator it=item.begin();it!=item.end();it++)
    {
        str+="I";
        str+=*it;
    }
    return str;
}
set<string> add(set<string> ss,set<string> ds,set<string> dc,int c)
{
    set<string> s,superset;
    map<string,int>m;
    for(set<string>::iterator it=ss.begin();it!=ss.end();it++)
        s.insert(*it);
    for(set<string>::iterator it=ds.begin();it!=ds.end();it++)
        s.insert(*it);
    if(s.size()<=1)
        return dc;
    vector<string> v(s.size());
    copy(s.begin(),s.end(),v.begin());
    for(int i=0;i<v.size();i++)
    {
        for(int j=i+1;j<v.size();j++)
        {
            if(v[i]!=v[j] && ck(v[i])==ck(v[j]) )
            {
                string str;//form a superset of size ck+1
                str=form(v[i],v[j]);
                if(f[str]<minfre)
                superset.insert(str);
                m[str]++;
            }
        }
    }
    for(set<string>::iterator it=superset.begin();it!=superset.end();it++)
    {
        int p=ck(*it);
        int sum=(p*(p-1))/2;
        if(m[*it]==sum)
            dc.insert(*it);
    }
    return dc;
}

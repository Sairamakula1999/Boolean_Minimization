// Online C++ compiler to run C++ program online
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <math.h>

using namespace std;

//Main class
class QM
{
public:

int VARIABLES;
string dontcares;

QM(int a)
{
   VARIABLES=a;
   dontcares.append(a,'-');

}

//function to get the boolean term letters
vector<string> getVars()
{
   vector<string> v;
   string letters[]={"a","b","c","d","e","f","g","h"};
   for(int i=0;i<this->VARIABLES;i++)
    v.push_back(letters[i]);

   return v;
}

//function to convert decimal to binary
string decToBin(int n)
{
   if ( n == 0 )
       return n+"";

   if ( n % 2 == 0 )
       return decToBin(n / 2) + "0";
   else
       return decToBin(n / 2) + "1";
}

//function to pad zeros(add zeroes at start) to the binary equivalent of digits.
string pad(string bin)
{
   int max=VARIABLES-bin.length();
   for(int i=0; i<max; i++)
       bin="0"+bin;
   return bin;
}

//function to check if two terms differ by just one bit
bool isGreyCode(string a,string b)
{
   int flag=0;
   for(int i=0;i<a.length();i++)
   {
       if(a[i]!=b[i])
        flag++;
   }
   return (flag==1);
}

//function to replace complement terms with don't cares
string replace_complements(string a,string b)
{
   string temp="";
   for(int i=0;i<a.length();i++)
   if(a[i]!=b[i])
       temp=temp+"-";
   else
       temp=temp+a[i];

   return temp;
}

//function to check if string b exists in vector a
bool in_vector(vector<string> a,string b)
{
     vector<string>::iterator it;
    if( find(a.begin(), a.end(), b)!= a.end())
            return true;
    return false;
}

//function to reduce minterms
vector<string> reduce(vector<string> minterms, vector<int> &group,vector<vector<int>> &term)
{
    vector<string> newminterms;
    vector<vector<int>> newterm;
    newterm.resize(minterms.size()*minterms.size()/4  );
      int max=minterms.size();
      vector<int>checked (max,0);
      int i=0;
      vector<int>next_group;
      next_group.push_back(0);
       int count=0;
      if(group.size()<3){
         for(int i=0;i<max;i++){
          for(int j=i;j<max;j++) { //If a grey code pair is found, replace the differing bits with don't cares. if minterm reduced is alreary present then not add it
               if(isGreyCode(minterms[i],minterms[j]){
                  checked[i]=1;
                  checked[j]=1;
                  if(!in_vector(newminterms,replace_complements(minterms[i],minterms[j]))){
                     newminterms.push_back(replace_complements(minterms[i],minterms[j]));
                  }
               }
          }
      }
      }
      else{
      while(i<group.size()-2){
        for(int j=group[i];j<group[i+1];j++){
            for(int k=group[i+1];k<group[i+2];k++){ 
                //If a gray code pair is found, replace the differing bits with don't cares.
                if(isGreyCode(minterms[j],minterms[k])){
                    checked[j]=1;
                    checked[k]=1;
                    if(!in_vector(newminterms,replace_complements(minterms[j],minterms[k]))){
                     newminterms.push_back(replace_complements(minterms[j],minterms[k]));
                    cout<<newminterms[newminterms.size()-1]<<" "<<minterms[j]<<" "<<minterms[k]<<endl;
                    newterm[count].insert(newterm[count].begin(), term[j].begin(), term[j].end());
                    newterm[count].insert(newterm[count].end(), term[k].begin(), term[k].end());
                     count++;// counts next group elem
                  }
                }
            }
        }
        next_group.push_back(count);
            i++;
         if(next_group[i]!=next_group[i-1])
         cout<<"-------------------------------"<<endl;
        }
        
      }
      //appending all uncheck terms to a new vector
      for(int i=0;i<max;i++){
        if(checked[i]!=1 && ! in_vector(newminterms,minterms[i])){
           newminterms.push_back(minterms[i]);
            cout<<newminterms[newminterms.size()-1]<<"\tunchecked"<<endl;
            newterm[count].insert(newterm[count].begin(), term[i].begin(), term[i].end());
            count++;
        }
      }
      cout<<endl;
        newterm.resize(count);
        group=next_group;
        term=newterm;
       return newminterms;
}


//Converting the boolean minterm into the variables
// Eg: 011- becomes a'bc
string getValue(string a)
{
   string temp="";
   vector<string> vars=this->getVars();
   if(a==dontcares)
     return "1";

   for(int i=0;i<a.length();i++)
   {
     if(a[i]!='-')
     {
        if(a[i]=='0')
         temp=temp+vars[i]+"\'";
        else
         temp=temp+vars[i];
     }
   }
   return temp;
}

//function to check if 2 vectors are equal
bool VectorsEqual(vector<string> a,vector<string> b){
   if(a.size()!=b.size())
      return false;
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    for(int i=0;i<a.size();i++){
        if(a[i]!=b[i])
        return false;
    }
    return true;
}

//for printing minterm
void  print_minterms(vector<string> minterms){
    
     int i;
    for (i=0;i<minterms.size()-1; i++)
          cout <<getValue(minterms[i])<<"+";
      cout<<getValue(minterms[i])<<endl;
}

};

//for sorting
int countBits(string a){
    int count = 0;
    for(int i=0;i<a.length();i++){
        if(a[i]=='1')
            count++;
    }
    return count;
}
int cmp(string a, string b){
    int count1 = countBits(a);
    int count2 = countBits(b);
    // this takes care of the stability of sorting algorithm too
    if (count1 >= count2)
        return false;
    return true;
}

//Main function

int main ()
{
   char check='y';
   while(check=='y')
   {
      int no;
      cout<<endl<<"Enter the number of variables:"<<endl;
      cin>>no;
      if(no > 8 || no < 1)
      {
          cout << "Invalid number of variables (1-8)" << endl;
          continue;
      }
      QM q(no);
      string temp="";
      cout<<"Enter the minterms(RANGE=0-"<<pow(2,no)-1<<") separated by comma:"<<endl;
      cin>>temp;
      //taking splitted the input(by ,) and saving as binary number
      vector<string> minterms;
      istringstream f(temp);
      string s;
      int num;
      while (getline(f, s, ',')){
        num=atoi(s.data());
         minterms.push_back(q.pad(q.decToBin(num)));
      }

      //sort by number of ones
      sort(minterms.begin(),minterms.end(),cmp);
      vector<int> group;
      int curr=0;
      group.push_back(0);
      vector<vector<int>> terms;
      terms.resize(minterms.size());
      vector<int> min_comp;

      // here groups differ by one are formed
      for(int i=0;i<minterms.size();i++){
        string k=minterms[i];
        int prev=curr;
        int bit=0;
        curr=0; 
        for(int i=0;i<k.length();i++){
            curr=curr^(k[i]-'0');
            bit=bit<<1;
            bit=bit+k[i]-'0';
            
        }
        if( curr ^prev==1)
            group.push_back(i);
        terms[i].push_back(bit);
        min_comp.push_back(bit);
      } 
      group.push_back(minterms.size());
        // print_minterms(minterms);
      for(int i=0;i<minterms.size();i++){
        cout<<minterms[i]<<endl;
      }
      cout<<endl;
    // here all groups are checcked until no gray code is left to combine
      do{
         minterms=q.reduce(minterms,group,terms);
      }while(group[1]!=0);
      cout << "The reduced boolean expression in SOP form before table reduced:" << endl;
      q.print_minterms(minterms);
      cout<<endl;
    // prime implicant table created
      vector<int> A;
      vector<vector<int>> B;
      B.resize(min_comp.size());
      for(int i=0;i<minterms.size();i++){
        cout<<"\t"<<q.getValue(minterms[i]);
      }
      cout<<endl;
      for(int i=0;i<min_comp.size();i++){
       cout<<min_comp[i]<<"\t";
        for(int j=0;j<terms.size();j++){
            vector<int>::iterator it;
            if( find(terms[j].begin(), terms[j].end(), min_comp[i])!= terms[j].end()){            
                B[i].push_back(j);
                cout<<"x";
            }
            else{
                cout<<" ";
            }
            cout<<"\t";
        }  
        cout<<endl;
      }
      
      //boolean minization using table A+AB=A
      vector<vector<int>> tk;
      tk.resize(B[0].size());
      for(int j=0;j<B[0].size();j++){
        tk[j].push_back(B[0][j]);
      }
      vector<vector<int>> ans1;
      int put=1;
      int cnt=0;
      cout<<endl;
      for(int m=1;m<B.size();m++){
        vector<int>::iterator it;
        for(int i=0;i<tk.size();i++){
            for(int j=0;j<tk[i].size();j++){         
                 if( find(B[m].begin(), B[m].end(), tk[i][j])!= B[m].end()){
                    ans1.push_back(tk[i]);
                    cnt++;
                    put=0;
                    break;          
                 }
            }
            if(put==1){
             for(int n=0;n<B[m].size();n++){
                    ans1.push_back(tk[i]);
                    ans1[ans1.size()-1].push_back(B[m][n]);
                    cnt++;
                }
            }
            put=1;
        }
        ans1.resize(cnt);
        tk.clear();
        tk=ans1;
        ans1.clear();
        cnt=0;
      }
    //cout<<tk[5].size();
      vector<int> ans;
      int min=100000;
      for(int i=0;i<tk.size();i++){
        if(tk.size()<min){
            ans.clear();
            ans=tk[i];
        }
      }
      vector<string> ans_reduced;
      for(int i=0;i<ans.size();i++){
        ans_reduced.push_back(minterms[ans[i]]);
      }

      q.print_minterms(ans_reduced);
      cout<<"Would you like to enter another expression? (y/n)"<<endl;
      cin>>check;
   }
   cout<<endl<<"---END--"<<endl<<"Created by Sairam"<<endl;
   return 0;
}

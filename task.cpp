#include <iostream>
#include<string>
#include<cstdlib>
#include<fstream>
#include <vector>
using namespace std;

vector<string> name;
vector<int> priority;

void help(){
    cout<<"Usage :-\n"
        <<"$ ./task add 2 hello world    # Add a new item with priority 2 and text \"hello world\" to the list\n"
        <<"$ ./task ls                   # Show incomplete priority list items sed by priority in ascending order\n"
        <<"$ ./task del INDEX            # Delete the incomplete item with the given index\n"
        <<"$ ./task done INDEX           # Mark the incomplete item with the given index as complete\n"
        <<"$ ./task help                 # Show usage\n"
        <<"$ ./task report               # Statistics";
}
int partition ( int low, int high){ 
    int pivot = priority[high];
    string pivot2 = name[high]; 
    int i = (low - 1); 
  
    for (int j = low; j <= high - 1; j++) 
    { 
        if (priority[j] < pivot) 
        { 
            i++;  
            swap(priority[i], priority[j]);
            swap(name[i],name[j]); 
        } 
    } 
    swap(priority[i + 1], priority[high]); 
    swap(name[i+1],name[high]);
    return (i + 1); 
}
void Short( int low, int high){
    if (low < high){ 
        int pi = partition( low, high); 
  
        Short( low, pi - 1); 
        Short( pi + 1, high); 
    }
}
void getData(string fileName){
    ifstream Rfile;

    Rfile.open(fileName,ios::in);
    
    if(Rfile){
      while(!Rfile.eof()){
        string line;
        getline(Rfile,line);
        char x;
        int i=0;
        for (; i < line.size(); i++){
            x=line[i];
            if(x=='$')
                break;
        }
        // cout<<"i "<<i<<endl;
        if (i != 0){
            string s;
            for (int j = 0; j < i; j++){
                s = s + line[j];
        }
        // cout<<"s1 "<<s<<endl;

        name.push_back(s);
        s="";
        for (int j = i+1; j < line.size(); j++){
            s =s + line[j];
        }                
        // cout<<"s "<<s<<endl;

        priority.push_back(stoi(s));
        }
    }  
    }
    
}
void addTask(int p,string n){
    ofstream file;

    name.push_back(n);
    priority.push_back(p);

    getData("Pending.txt");
    
    Short(0,priority.size()-1);

    file.open("Pending.txt",ios::ate);
    for (int i = 1; i <= name.size(); i++){
        file<<name[i-1]
            <<"$"
            <<priority[i-1]
            <<endl;
    }

    file.close();
    name.clear();
    priority.clear();

    cout<<"Added task: \""
        <<n
        <<"\" with priority "
        <<p<<endl;
}
void show(){
    getData("Pending.txt");
    for (int i = 1; i <= name.size(); i++){
        cout<<i<<". "
            <<name[i-1]
            <<"["
            <<priority[i-1]
            <<"]"<<endl;
    }
    name.clear();
    priority.clear();
}
void done(int index){
    ofstream file,cfile;

    getData("Pending.txt");

    file.open("Pending.txt",ios::ate);
    cfile.open("completed.txt",ios::app);
    for (int i = 1; i <= name.size(); i++){
        if (i!=index){
            file<<name[i-1]
                <<"$"
                <<priority[i-1]
                <<endl;
        }else{
            cfile<<name[i-1]<<endl;
        }
        
    }

    name.clear();
    priority.clear();

    file.close();
    cfile.close();
    cout<<"Maked item as done."<<endl;
}
void delt(int index){
    ofstream file;

    getData("Pending.txt");

    file.open("Pending.txt",ios::ate);
    for (int i = 1; i <=name.size(); i++){
        if (i!=index){
            file<<name[i-1]
                <<"$"
                <<priority[i-1]
                <<endl;
        }
    }
    name.clear();
    priority.clear();

    file.close();
    cout<<"Deleted task #"<<index<<endl;
}
void report(){
    getData("Pending.txt");

    cout<<"Pending : "<<name.size()<<endl;

    for (int i = 1; i <= name.size(); i++){
        cout<<i<<". "
            <<name[i-1]
            <<"["
            <<priority[i-1]
            <<"]"<<endl;
    }
    name.clear();

    ifstream Rfile;

    Rfile.open("completed.txt",ios::in);

    if(!Rfile){
        while(!Rfile.eof()){
            string line;
            getline(Rfile,line);
            name.push_back(line);
        }
    }
    
    Rfile.close();
    cout<<endl<<"Completed : "<<name.size()-1<<endl;


    for(int i=1;i<name.size();i++){
        cout<<i<<". "<<name[i-1]<<endl;
    }
    name.clear();
    priority.clear();
}
int main(int l, char **c){
   string cmnd ;

   if (l==1)
       help();
   else
        cmnd=c[1];
   if (cmnd=="help")
       help();
   else if(cmnd =="add")
        addTask(stoi(c[2]),c[3]);
    else if(cmnd=="ls")
        show();
    else if(cmnd=="done")
        done(stoi(c[2]));
    else if(cmnd=="del")
        delt(stoi(c[2]));
    else if(cmnd=="report")
        report();
    return 0;
}

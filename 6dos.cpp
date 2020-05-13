#include<iostream>
#include<vector>
#include<random>
#include<time.h>
#include<string>

using namespace std;

//use this to store index in vector. Significantly improves runtime. 
struct Entry{
    int position;    
    string name;    
    Entry(int pos, string Name) { 
        name = Name;
        position = pos;
    }
};

//overload operator for entry
ostream& operator <<(ostream &out, Entry e){
    cout << e.name;
}

//generate individual names. Pass as reference void name_generator(int name_length, vector<Entry> *names_list, int index){
    //chose from this list of letters
    static const char alphanum[] = 
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";   
    
    //choose random letter from above and make string of size <name_length> 
    string s;
    for(int i = 0; i < name_length; i++){
        s += alphanum[rand() % (sizeof(alphanum)-1)];
    }
    //create entry storing the index and the string
    Entry e = Entry(index, s);
    //push back random entry into names_list... use -> b/c its a pointer
    names_list->push_back(e);
}

void get_time(clock_t tStart){
    clock_t tEnd;
    tEnd = clock();
    double diff((double)tEnd-(double)tStart);
    cout << "Time to run: " << diff/CLOCKS_PER_SEC << " seconds." << endl; }

//used to print chain of people that connects start name and target name void print_chain(vector<Entry> index_people, vector<vector<Entry>> follow_list, int follow_num){
         cout << endl;
         cout << "Printing chain..." << endl;
         for(int p = 0; p < index_people.size(); p++){
            cout << index_people[p] << " follows ";
            for(int q = 0; q < follow_num; q++){
                    cout << follow_list[index_people[p].position][q].name << ", ";
                }
            cout << endl;
         }
}

int main(){
    //start clock
    srand(time(NULL)); //make sure everything is randomizing
    clock_t tStart, tEnd;
    tStart = clock();

    //initialize number of names, number of followers, name length
    int num_names = 1000000;
    int follow_num = 10;
    int name_length = 5;

    //initialize vectors containing names list and follow list
    vector<Entry> names_list;
    vector<vector<Entry>> follow_list;
    
    //call name_generator for total number of names
    for(int i = 0; i < num_names; i++){
        name_generator(name_length, &names_list, i);
    }
    cout << "Generated names..." << endl;
    
   //generate_follow_list(&names_list, &follow_list, follow_num);
   for(int i = 0; i < num_names; i++){
        vector<Entry> follow_sample;
        for (int k = 0; k < follow_num; k++){
            follow_sample.push_back(names_list[(rand() % names_list.size())]);
        }
        follow_list.push_back(follow_sample);
    } 
    cout << "Generated follow list..." << endl;
    cout << "names list size: " << names_list.size() << endl;
    cout << endl;

    //generate random name for start and target
    int start_index = rand() % num_names;
    int end_index =  rand() % num_names;

    Entry start_name = names_list[start_index];
    Entry target_name = names_list[end_index];
    
    cout << "Start name: " << start_name << endl;
    cout << "Target name: " << target_name << endl;
    cout << endl;

    //now the big loop begins
    cout << "Starting big loop..." << endl;
    vector<Entry> index_people;
    for(auto i : follow_list[start_index]){
        if(i.name == target_name.name){
            cout << start_name << " follows " << target_name << " directly" << endl << endl;    
            index_people = {start_name};
            print_chain(index_people, follow_list, follow_num);
            
            get_time(tStart);
            exit(0);
        }
        for(auto j : follow_list[i.position]){
                index_people.push_back(j);
            if(i.name == target_name.name){
                cout << start_name << " follows " << j << " who follows " << target_name << "Two degrees." << endl;     
                index_people = {start_name, i};
                print_chain(index_people, follow_list, follow_num);

                get_time(tStart);
                exit(0);
            }
            for(auto k : follow_list[j.position]){
                    index_people.push_back(k);
                if(k.name == target_name.name){
                    cout << start_name << " follows " << j << " who follows " 
                    << k  << " who follows " << target_name << " Three degrees."<< endl;     
                    index_people = {start_name, i, j};
                    print_chain(index_people, follow_list, follow_num);

                    get_time(tStart);
                    exit(0);
                }
                for(auto l : follow_list[k.position]){
                        index_people.push_back(l);
                    if(l.name == target_name.name){
                        cout << start_name << " follows " << j << " who follows " 
                        << k  << " who follows " << l << " who follows " << target_name  << " Four degrees." << endl;     
                        index_people = {start_name, i, j, k};
                        print_chain(index_people, follow_list, follow_num);

                        get_time(tStart);
                        exit(0);
                    }
                    for(auto m : follow_list[l.position]){
                            index_people.push_back(m);
                        if(m.name == target_name.name){
                            cout << start_name << " follows " << j << " who follows " 
                            << k  << " who follows " << l << " who follows " 
                            << m << " who follows " << target_name << " Five degrees." << endl;     
                            index_people = {start_name, i, j, k, l};
                            print_chain(index_people, follow_list, follow_num);

                            get_time(tStart);
                            exit(0);
                        }
                        for(auto n : follow_list[m.position]){
                            if(n.name == target_name.name){
                                cout << start_name << " follows " << i << " who follows " << j << " who follows " 
                                << k  << " who follows " << l << " who follows " 
                                << m << " who follows " << target_name << " Six degrees." << endl;     
                                index_people = {start_name, i, j, k, l, m};
                                print_chain(index_people, follow_list, follow_num);

                                get_time(tStart);
                                exit(0);
                            }
                        }
                    }
                }
            }
        }
    }


    //get end run time
    get_time(tStart);
   
    return 0;
}

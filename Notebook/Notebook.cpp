#include <iostream>
#include <fstream>
#include <vector>
#include <streambuf>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cstring>

using namespace std;

const int char_size = 4096;
const int max_size = 6000;
int Number_Of_files = 1;

struct StringHash {
    size_t operator()(const string& s) const {
        hash<string> hasher;
        size_t seed = hasher(s);
        return seed;
    }
};


struct Note{
    bool is_deleted = false;
    char key[char_size];
    char value[char_size];
};




int main()
{
    int n;
    int size = 1;
    unordered_map<string, vector<int>, StringHash> hashmap;
    
    cin >> n;

    for(int i = 0; i < n; ++i){
    
        Note note;
        string operation;
        cin >> operation;

        if(operation == "ADD"){

            string key;
            cin >> key >> note.value;
            strcpy(note.key, key.c_str());

            if(hashmap.size() == 0) {
                
                string file_name = to_string(Number_Of_files) + ".bin";
                ofstream fout(file_name, ios::binary);
                fout.write((char*)(&note), sizeof(Note));
                fout.close();
                
                vector<int> v;
                
                v.push_back(Number_Of_files * max_size + size);
                hashmap.insert(make_pair(note.key, v));
                size ++;
            } else {
                if(hashmap.find(key) != hashmap.end()) {
                    
                    vector<int> positions = hashmap.find(key) -> second;
                    bool bad = false;
                    
                    for (int i = 0; i < (int)positions.size(); ++i) {
                        
                        string file_name = to_string(positions[i]/max_size) + ".bin";
                        fstream fout(file_name, ios::out|ios::in|ios::binary);
                        fout.seekg(0, ios::beg); 
                        Note note_2;
                        fout.seekg(((positions[i] % max_size) - 1) * sizeof(Note), ios::beg);
                        fout.read((char*)(&note_2), sizeof(Note));
                        
                        if(strncmp(note.key, note_2.key, 100) == 0){
                            
                            fout.close();
                            bad = true;
                            cout << "ERROR" << endl;
                            break;
                        
                        }
                        fout.close();
                    }
                    if (!bad) {
                        
                        string file_name = to_string(Number_Of_files) + ".bin";
                        ofstream fout(file_name, ios::binary|ios::app);
                        fout.write((char*)(&note), sizeof(Note));
                        fout.close();
                        
                        hashmap.erase(key);
                        positions.push_back(Number_Of_files * max_size + size);
                        hashmap.insert(make_pair(key, positions));
                        
                        size ++;
                        
                        if (size > max_size ) {
                        size = 1;
                        Number_Of_files ++;
                        }
                    }
                } else {
                    
                    string file_name = to_string(Number_Of_files) + ".bin";
                    ofstream fout(file_name, ios::binary|ios::app);
                    fout.write((char*)(&note), sizeof(Note));
                    fout.close();
                    
                    vector<int> v;
                    
                    v.push_back(Number_Of_files * max_size + size);
                    hashmap.insert(make_pair(note.key, v));
                    size ++;
                    
                    if (size > max_size ) {
                        size = 1;
                        Number_Of_files ++;
                    }
                }
         
            }
        }

        if(operation == "DELETE"){

            string key;
            cin >> key;
            char kkey[char_size];
            strcpy(kkey, key.c_str());

            if(hashmap.find(key) != hashmap.end()) {
                
                bool good = false;
                vector<int> positions = hashmap.find(key) -> second;
                
                for (int i = 0; i < (int)positions.size(); ++i) {
                    
                    string file_name = to_string(positions[i]/max_size) + ".bin";
                    fstream fout(file_name, ios::out|ios::in|ios::binary);
                    fout.seekg(0, ios::beg); 
                    Note note;
                    fout.seekg(((positions[i] % max_size) - 1) * sizeof(Note), ios::beg);
                    fout.read((char*)(&note), sizeof(Note));
                    
                    if(strncmp(note.key, kkey, 1000) == 0){
                        
                        note.is_deleted = true;
                        
                        fout.seekg(((positions[i] % max_size) - 1) * sizeof(Note), ios::beg);
                        fout.write((char*)(&note), sizeof(Note));
                        fout.close();
                        
                        good = true;
                        hashmap.erase(key);
                        break;
                    }
                    fout.close();
                }
                if (!good) cout << "ERROR" << endl;
            } else {
                cout << "ERROR" << endl;
            }
        }

        if(operation == "UPDATE"){

            string key, new_value;
            cin >> key >> new_value;
            char kkey[char_size];
            strcpy(kkey, key.c_str());

            if(hashmap.find(key) != hashmap.end()) {
                
                bool good = false;
                vector<int> positions = hashmap.find(key) -> second;
                
                for (int i = 0; i < (int)positions.size(); ++i) {
                    
                    string file_name = to_string(positions[i]/max_size) + ".bin";
                    fstream fout(file_name, ios::out|ios::in|ios::binary);
                    fout.seekg(0, ios::beg); 
                    Note note;
                    fout.seekg(((positions[i] % max_size) - 1) * sizeof(Note), ios::beg);
                    fout.read((char*)(&note), sizeof(Note));
                    
                    if (strncmp(note.key, kkey, 100) == 0) {
                        
                        good = true;
                        
                        if(note.is_deleted == false){
                            strcpy(note.value, new_value.c_str());
                            fout.seekg(((positions[i] % max_size) - 1)* sizeof(Note), ios::beg);
                            fout.write((char*)(&note), sizeof(Note));
                        } else {
                            cout << "ERROR" << endl;
                        }
                        break;
                    }
                    fout.close();
            } 
            
            if(!good) cout << "ERROR" << endl;
            
            } else {
                cout << "ERROR" << endl;
            }
        }

        if(operation == "PRINT"){

            string key;
            cin >> key;
            char kkey[char_size];
            strcpy(kkey, key.c_str());


            if(hashmap.find(key) != hashmap.end()) {
                
                bool good = false;
                vector<int> positions = hashmap.find(key) -> second;
                
                for (int i = 0; i < (int)positions.size(); ++i) {
                    
                    string file_name = to_string(positions[i]/max_size) + ".bin";
                    ifstream fin(file_name, ios::out|ios::binary);
                    fin.seekg(0, ios::beg); 
                    Note note;
                    fin.seekg(((positions[i] % max_size) - 1) * sizeof(Note), ios::beg);
                    fin.read((char*)(&note), sizeof(Note));
                    
                    if (strncmp(note.key, kkey, 100) == 0) {
                        good = true;
                        if(note.is_deleted == false){
                            cout << note.key << " " << note.value << endl; 
                        } else {
                            cout << "ERROR" << endl;
                        }
                        break;
                    }
                    fin.close();
                }
                if(!good) cout << "ERROR" << endl;
            } else {
                cout << "ERROR" << endl;
            }
        }
    }

    return 0;
}
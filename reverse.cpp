#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

class Glossaire {
        
        const string &input_path;
        unordered_map<string, int> map;
    
    public:
        
        // Constructor
        Glossaire(const string &input_path):input_path(input_path){}

        // A method that takes the path of the input file as an argument, reads the file word by word and fills the unordered_map map with
        // the number of occurence of each word (return -1 if error, or else returns 0)  
        int get_occurences(){
            
            // Open the input file into a filestream object
            ifstream InputStream(this->input_path);
            
            // In case the file did not open
            if (!InputStream.is_open()) {
                cerr << "Cannot open the file. Please check if the file path given is the right one";
                return -1;
            }

            // Read each word of the stream
            string word;
            while (InputStream >> word) {
                string key = word;
                // if the word that is read is not in the unordered map, we add it to it as key with value 0
                if (this->map.find(key) == this->map.end()) {
                    this->map[key] == 0;
                }
                // increment the current word count
                this->map[key]++;
            }

            // Closing the file after completion
            InputStream.close();
            return 0;
        }

        // comparator to use for sorting (key,value) pairs by their value
        static bool comparator(const pair<string, int> &p1, const pair<string, int> &p2) {return p1.second > p2.second;}

        // method that copies the pair value of the unordered map into a vector in order to sort these pairs
        void sort_results(vector<pair<string, int>> &v) {
            // clear contents of vector in case if not empty
            v.clear();
            // fill vector with map pairs
            for (auto i:this->map) {
                v.push_back(i);
            }
            // sort vector using the comparator static method
            sort(v.begin(), v.end(), this->comparator);
        }

        int write_to_output() {

            // get the postion of the "." caracter at the end of the input file
            size_t dot = this->input_path.find_last_of(".");
            string suffix(".table.txt");
            // create the output path by concatenating the input path (minus the extenstion) and the suffix ".table.txt"
            string outut_path = this->input_path.substr(0,dot) + suffix;
            
            // create and open a new file
            ofstream OutputStream(outut_path);
            // In case the file did not open
            if (!OutputStream.is_open()) {
                cerr << "Cannot create the output file.";
                return -1;
            }

            // create a new vector in order to use it to sort the unordered_map values
            vector<pair<string, int>> v;
            this->sort_results(v);

            // write the sorted results inside the output file
            for (auto i:v) {
                OutputStream << i.first <<  ", " << i.second << endl;
            }

            // Closing file after completion
            OutputStream.close();
            return 0;
        }

};


int main (int argc, char **argv) {
    // If no file path is passed as an argument to the program
    if (argc == 1) {
        cerr << "No file path has been passed as argument" << endl;
        return -1;
    }

    // If too many arguments have been passed to the program
    else if (argc > 2) {
        cerr << "You passed too many arguments to the program. You need to only pass one" << endl;
        return -1;
    }

    // Get the file's path 
    const string &input_file_path(argv[1]);
    // instaciate a Glossaire object
    Glossaire glossary(input_file_path);

    // get word occurences
    int status_code = glossary.get_occurences();
    if (status_code == -1) {return -1;}
    // write results in output file
    status_code = glossary.write_to_output();
    return status_code;
}

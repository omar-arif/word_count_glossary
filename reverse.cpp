#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

class Glossaire {
        
        // input path
        const string &input_path;
        // an unordered map for minimal search and insertion complexity
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

            // A string containing all the characters that we allow a word to have
            string allowed_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789éèêàâëûùîçôöü-";

            // Read each word of the stream
            string word;
            while (InputStream >> word) {
                
                // use the current word a string stream
                istringstream iss(word);
                
                // get every subword using the "'" (apostrophe) delimiter
                string sub_word;
                while (getline(iss, sub_word, '\'')){

                    // interrupt and output error if a current word has more than 64 characters
                    if (sub_word.length() > 64){
                        cerr << "Error: The word: " << sub_word << " contains more than 64 characters";
                        return -1;
                    }

                    // check if a word is of length less than 2 or if a word contains an unallowed character
                    else if (sub_word.length() >= 2 && sub_word.find_first_not_of(allowed_chars) == string::npos) {
                        
                        // if the word that is read is not in the unordered map, we add it to it as key with value 0
                        if (this->map.find(sub_word) == this->map.end()) {
                            this->map[sub_word] = 0;
                        }

                        // increment the current word count
                        this->map[sub_word]++;
                    }

                }
            }
            // Closing the file after completion
            InputStream.close();
            return 0;
        }

        // comparator to use for sorting (key,value) pairs by their value
        static bool comparator(const pair<string, int> &p1, const pair<string, int> &p2) {return p1.second > p2.second;}

        // method that copies the pairs of the unordered map into a vector in order to sort these pairs
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

        // A method that creates a file based on the input file path and writes the glossary resluts in a formated way ("word, word count" in each line)
        int write_to_output() {

            // get word occurences
            int status_code = this->get_occurences();
            if (status_code == -1) {return -1;}

            // get the postion of the "." caracter at the end of the input file
            size_t dot = this->input_path.find_last_of(".");
            string suffix(".table.txt");
            
            // create the output path by concatenating the input path (minus the extenstion) and the suffix ".table.txt"
            string outut_path = this->input_path.substr(0, dot) + suffix;
            
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

    // write results in output file
    int status_code = glossary.write_to_output();
    return status_code;
}

#include <iostream>
#include <fstream>

#include <map>
#include "functions.hpp"
//make a function to open a file to encrypt or decrypt a message based on the key provided
using namespace std;

int main(int argc, char const *argv[])
{
    string filename = argv[1];
    string verifier;
    char word;
    char encryption;
    char key[26];
    char value[26];
    int counter = 0;
    bool flag;

    //open the file
    fstream file;
    file.open(filename, ios::in | ios::out | ios::binary);

    if (!file.is_open())
    {
        cout << "Error opening file" << endl;
        return 1;
    }

    //check if the file contains E: D: or nothing
    getline(file, verifier);
    if (verifier == "E: D:"){
        //read the file
        while (file.good()){
            file >> word;
            file >> encryption;

            key[counter] = word;
            value[counter] = encryption;
            counter++;
        }
    }
    else{
        cout << "Error: file is not is the correct format" << endl;
    }

    file.close();

    //print the key and value
    for (int i = 0; i < 26; i++)
    {
        cout << key[i] << " " << value[i] << endl;
    }
    return 0;
}

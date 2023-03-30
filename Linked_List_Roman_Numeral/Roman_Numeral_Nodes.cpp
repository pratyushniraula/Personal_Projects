#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cctype>

using namespace std;

struct Node
{
    int ArabicValue;
    string roman_numeral;
    Node *next;
};

string Arabic_to_Roman2(int arab)
{
    string Roman;
    int temp; // will store temporary values

    while (arab > 0)//while loop runs until arabic numeral is 0
    {
        if (arab >= 1000)
        {
            temp = arab / 1000;
            for (int i = 0; i < temp; i++)
            {
                Roman += "M";
            }
            arab -= temp * 1000;
        }

        else if (arab >= 900)
        {
            Roman += "CM";
            arab -= 900;
        }

        else if (arab >= 500)
        {
            temp = arab / 500;
            for (int i = 0; i < temp; i++)
            {
                Roman += "D";
            }
            arab -= temp * 500;
        }

        else if (arab >= 400)
        {
            Roman += "CD";
            arab -= 400;
        }

        else if (arab >= 100)
        {
            temp = arab / 100;
            for (int i = 0; i < temp; i++)
            {
                Roman += "C";
            }
            arab -= temp * 100;
        }

        else if (arab >= 90)
        {
            Roman += "XC";
            arab -= 90;
        }

        else if (arab >= 50)
        {
            temp = arab / 50;
            for (int i = 0; i < temp; i++)
            {
                Roman += "L";
            }
            arab -= temp * 50;
        }

        else if (arab >= 40)
        {
            Roman += "XL";
            arab -= 40;
        }

        else if (arab >= 10)
        {
            temp = arab / 10;//continue off of here 
            for (int i = 0; i < temp; i++)
            {
                Roman += "X";
            }
            arab -= temp * 10;
        }
        //account for 9s 5s and 4s
        else if (arab >= 9)
        {
            Roman += "IX";
            arab -= 9;
        }

        else if (arab >= 5)
        {
            temp = arab / 5;
            for (int i = 0; i < temp; i++)
            {
                Roman += "V";
            }
            arab -= temp * 5;
        }

        else if (arab >= 4)
        {
            Roman += "IV";
            arab -= 4;
        }

        else if ((arab / 1) > 0)
        {
            temp = arab / 1;
            for (int i = 0; i < temp; i++)
            {
                Roman += "I";
            }
            arab -= temp * 1;
        }

    }
    return Roman;
}

//roman to int function
int roman_to_int(string roman)
{
    int arabic = 0;
    int temp = 0;
    int temp2 = 0;
    for (int i = 0; i < roman.length(); i++)
    {
        if (roman[i] == 'M')
        {
            temp = 1000;
        }
        else if (roman[i] == 'D')
        {
            temp = 500;
        }
        else if (roman[i] == 'C')
        {
            temp = 100;
        }
        else if (roman[i] == 'L')
        {
            temp = 50;
        }
        else if (roman[i] == 'X')
        {
            temp = 10;
        }
        else if (roman[i] == 'V')
        {
            temp = 5;
        }
        else if (roman[i] == 'I')
        {
            temp = 1;
        }
        if (temp > temp2)
        {
            arabic += temp - 2 * temp2;
        }
        else
        {
            arabic += temp;
        }
        temp2 = temp;
    }
    return arabic;
}

int main(int argc, char const *argv[])
{
    fstream file;
    file.open("numbers1.txt", ios::in | ios::out | ios::binary);

    //file check
    if (!file.good())
    {
        cout << "File failed to open" << endl;
        return 1;
    }

    //pointers for linked list
    Node *head = nullptr;
    Node *tail = nullptr;

    //variables for arabic and roman numerals
    int arabic;
    string roman;
    string letter;
    
    // scan for arabic numerals and roman numerals
    while (file >> letter)
    {
        if (isdigit(letter[0]))
        {
            try {
                arabic = stoi(letter);
            }
            catch (const invalid_argument &ia) {
                continue;
            }
            roman = Arabic_to_Roman2(arabic);
            Node *temp = new Node;
            temp->ArabicValue = arabic;
            temp->roman_numeral = roman;
            temp->next = nullptr;

            if (head == nullptr)
            {
                head = temp;
                tail = temp;
            }
            else
            {
                tail->next = temp;
                tail = temp;
            }
        }
        else
        {
            roman = letter;
            arabic = roman_to_int(roman);
            Node *temp = new Node;
            temp->ArabicValue = arabic;
            temp->roman_numeral = roman;
            temp->next = nullptr;

            if (head == nullptr)
            {
                head = temp;
                tail = temp;
            }
            else
            {
                tail->next = temp;
                tail = temp;
            }
        }
    }

    // print out the linked list
    Node *temp = head;
    while (temp != nullptr)
    {
        int spaces;
        spaces = sizeof(temp->roman_numeral);
        while (spaces < 17)
        {
            cout << " ";
            spaces++;
        }
        cout << temp->ArabicValue << temp->roman_numeral << endl;
        temp = temp->next;
    }

    // reset file stream
    file.clear();
    file.seekg(0, ios::beg);

    // print the linked list to a file
    // make sure to fit requirements of file when writing to it
    // space 17 characters for roman and 4 for arabic and then a new line
    //
    ofstream newfile;
    newfile.open("numbers.txt", ios::out | ios::app);
    temp = head;
    while (temp != nullptr)
    {
        int spaces;
        int arabic_spaces;
        spaces = 17-(temp->roman_numeral.length());
        newfile << temp->roman_numeral;
        for (int i = 0; i < spaces; i++)
        {
            newfile << " ";
        }
        
        newfile << temp->ArabicValue << endl;
        temp = temp->next;
    }
    newfile.close();

    // free memory
    temp = head;
    while (temp != nullptr)
    {
        Node *next = temp->next;
        delete temp;
        temp = next;
    }

    file.close();
    return 0;
}

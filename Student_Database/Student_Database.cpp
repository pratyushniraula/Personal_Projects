#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

struct student
{
    string name;
    string studentID;
    double gpa;
    unsigned int grade;
    unsigned int age;
    student *next;
};
    //make a pointer just for the head of the list just so we have access to the head for the other funcitons aside from just add
    //add student should be called append student, linked list is made so that you can dynamically add and remove bits of the list from anywhere at any time
    //add ability to add to list anywhere

void addStudent(student *&head, string name, string id, double gpa, unsigned int grade, unsigned int age);
void deleteStudent(student *&head, string id);
void editStudent(student *&head, string name, string id, double gpa, unsigned int grade, unsigned int age);
void PrintStudents(student *&head);

int main(int argc, char const *argv[])
{
    int sc; //(student count)
    int selection = 0; //what choice was selected in the options menu
    int selection1; //choice for creating database or not
    string SName; //student name
    string SStudentID; //student id
    string newID; //student id they want to enter in order to parse through the list
    double SGPA; //student gpa
    unsigned int SGrade; //student grade
    unsigned int SAge; //student age
    bool flag = 0; //will check if head is empty or not

    //gpa sizer
    cout << setprecision(2) << fixed << showpoint << endl;
    
    //making the menu screen
    cout << "Welcome to the Student Database" << endl;
    
    cout << "Would You Like to Make a Database?\n1: Yes\n2: No" << endl;

    cin >> selection1;

    if (selection1 == 1)//asking if the database wants to be created or not
    {
        //this is actual head, everything will be built upon this head 
        student *head = new student();//
        student *current = head;
        head->next = nullptr;

        while (selection != 5)
        {
            cout << "\nSelect From the Following Options:\n" 
            << "1: Add a New Student \n2: Delete a Student \n3: Edit a Student \n4: Print All Students \n5: Exit\n\n" << endl;
            //maybe case 6 can be printing into a new file?
            cin >> selection;

            switch (selection)
            {
            case 1:
                /* add student */
                //if statement checks to see if head is empty
                if (flag == 0){
                    //account for head in addstudent to make sure that head can point to something and not always be nullptr 
                    //this checks if head is empty or not
                    flag = 1;
                    //now add to head
                    cout << "Enter Information of the Student:\n"
                    << "What is Their Name?: ";
                    cin >> SName;
                    cout << "What is Their Student ID?: ";
                    cin >> SStudentID;
                    cout << "What is Their GPA?: ";
                    cin >> SGPA;
                    cout << "What is Their Grade level: ";
                    cin >> SGrade;
                    cout << "What is their Age?: ";
                    cin >> SAge;
                    
                    head->name = SName;
                    head->studentID = SStudentID;
                    head->gpa = SGPA;
                    head->grade = SGrade;
                    head->age = SAge;

                }

                else{
                cout << "Enter Information of the Student:\n"
                << "What is Their Name?: ";
                cin >> SName;
                cout << "What is Their Student ID?: ";
                cin >> SStudentID;
                cout << "What is Their GPA?: ";
                cin >> SGPA;
                cout << "What is Their Grade level: ";
                cin >> SGrade;
                cout << "What is their Age?: ";
                cin >> SAge;
                addStudent(current, SName, SStudentID, SGPA, SGrade, SAge);
                }
                break;

            case 2:
                /* delete student */
                cout << "Please enter Their Student ID: ";
                cin >> SStudentID;
                deleteStudent(head, SStudentID);
                break;

            case 3:
                /* edit student */
                cout << "Enter the ID of the Student You Want to Edit:\n";
                cin >> SStudentID;
                
                cout << "What Is Their Name?: ";
                cin >> SName;
                cout << "What Is Their Current ID: ";
                cin >> newID;
                cout << "What Is Their Current GPA?: ";
                cin >> SGPA;
                cout << "What is their New Grade: ";
                cin >> SGrade;
                cout << "What is their Age?: ";
                cin >> SAge;
                editStudent(head, SName, SStudentID, newID, SGPA, SGrade, SAge);
                break;

            case 4:
                /* print students */
                PrintStudents(head);
                break;

            case 5:
                /* exit (stops from automatically outputting default case)*/
                cout << "Thank You! Program Terminated" << endl;
                break;

            default:
                cout << "Number is Out of Bounds" << endl;
                break;
            }
        }
    }
    
    else{
    cout << "Thank You! Program Terminated" << endl;
    }
    return 0;
}

void addStudent(student *&current, string n, string id, double g, unsigned int gr, unsigned int a){
    
    student *ptr = new student();//new student
    ptr->name = n;
    ptr->studentID = id;
    ptr->gpa = g;
    ptr->grade = gr;
    ptr->age = a;

    current->next = ptr;
    current = ptr;
    ptr->next = nullptr;
}

void deleteStudent(student *&head, string id)
{
        student *ptr = head;//makes new pointer start from the beginning and search throughout the list
        student *ptr1 = head;//this will keep track of one before ptr you want to delete

        while (ptr !=nullptr)
        {
            if (ptr->studentID == id)
            {
                ptr1->next = ptr->next;
                delete ptr;
            }
            else
            {
            ptr1 = ptr;
            ptr = ptr->next;
            }
        }
        cout << "Student " << ptr->name << " Has Been Deleted." << endl;

}

void editStudent(student *&head, string n, string oldID, string id, double g, unsigned int gr, unsigned int a){
        student *ptr = head;//makes new pointer start from the beginning and search throughout the list
        
        while (ptr !=nullptr)
        {
            if (ptr->studentID == oldID)
            {
                ptr->name = n;
                ptr->studentID = id;
                ptr->gpa = g;
                ptr->grade = gr;
                ptr->age = a;
            }
            else
            {
            ptr = ptr->next;
            }
        }
        cout << "Student " << ptr->name << " is Edited." << endl;
}

void PrintStudents(student *&head){
    student *ptr = head;
        while (ptr != nullptr)
    {
        cout << "\n";
        cout << "Name: "<< ptr->name << " " << endl;
        cout << "Student ID: " << ptr->studentID << " " << endl;
        cout << "GPA: " <<  ptr->gpa << " " << endl;
        cout << "Grade: " << ptr->grade << " " << endl;
        cout << "Age: " << ptr->age << " " << endl;
        ptr = ptr->next;
    }
    cout << endl;
}
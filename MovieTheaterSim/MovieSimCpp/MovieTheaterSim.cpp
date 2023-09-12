#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

//display auditorium function 
void displayAuditorium(string auditorium[10][26], int row)
{
    int k = 0;
    cout << "    ";
    //prints the column letters
    while(auditorium[0][k] != ""){
        cout << (char)(k+65);
        k++;
    }
    cout << endl;

    //prints the auditorium
    for (int i = 0; i < row; i++)
    {
        cout << i + 1 << "   ";
        for (int j = 0; j < 26; j++)
        {
            if (auditorium[i][j] == "A" || auditorium[i][j] == "S" || auditorium[i][j] == "C"){
                cout << "#";
            }
            else if (auditorium[i][j] == "."){
                cout << auditorium[i][j];
            }
        }
        cout << endl;
    }
}

int bestAvailable(string auditorium[10][26], int row, int colIndex, int adult, int senior, int child){
    //best available seats function
    //variables to use in calculations
    int total = adult + senior + child;
    int bestSeat = -1;
    int bestV = colIndex+1;
    int v = colIndex+1;
    int middle;
    //loop through the row
    for (int i = 0; i <= (colIndex - total); i++){
        bool available = true;
        for(int j = 0; j < total; j++){
            //if there is a seat that is already taken, break out of the loop
            if (auditorium[row][i + j] == "A" || auditorium[row][i + j] == "S" || auditorium[row][i + j] == "C"){
                available = false;
                break;
            }
        }
        //if there are no seats taken, find the best seat
        if(available){
            middle = (i + (i + total))/2;//middle seat
            v = abs(middle - (colIndex/2));//how close you are to the middle of the row
            if (v < bestV){
                bestV = v;
                bestSeat = i;
            }
        }
        
    
    }
    return bestSeat;
}

bool checkSeats(string auditorium[10][26], int row, int seat, int adult, int senior, int child){
    //check if seats are available
    int totalSeats = adult + senior + child;
    //loop through the seats
    for (int i = 0; i < totalSeats; i++){
        if (auditorium[row][seat + i] == "A" || auditorium[row][seat + i] == "S" || auditorium[row][seat + i] == "C"){
            return false;
        }
    }
    return true;
}

//reserve seats function
void reserveSeats(string auditorium[10][26], int row, int colIndex, int seat, int adult, int senior, int child){
    char yesNo;
    //check if seats are available
    if (checkSeats(auditorium, row, seat, adult, senior, child)){
        //reserve seats adult first, then child, then senior
        cout << "your seats have been reserved" << endl;
        while (adult > 0){
            auditorium[row][seat] = "A";
            seat++;
            adult--;
        }
        
        while (child > 0){
            auditorium[row][seat] = "C";
            seat++;
            child--;
        }
        
        while (senior > 0){
            auditorium[row][seat] = "S";
            seat++;
            senior--;
        }
        
    }
    else{
        //display best available seats if seats selected are not available
        if (bestAvailable(auditorium, row, colIndex, adult, senior, child)  != -1)
        {
            cout << "Although there are no exact seats that match this description, these are the closest seats we have to the ones";
                //find seat name and number
                char firstSeat = bestAvailable(auditorium, row, colIndex, adult, senior, child) + 65;
            cout << " that you have picked: " << row+1 << firstSeat;
            if ((adult + child + senior) > 1){
                char lastSeat = bestAvailable(auditorium, row, colIndex, adult, senior, child) + (adult + child + senior) +64;
                cout << " - " << row+1 << lastSeat;
            }
            //ask if they would like to confirm these seats
            cout << "\nwould you still like to confirm these seats? (y/n)" << endl;
            //if yes, reserve seats
            cin >> yesNo;
            if (yesNo == 'y' || yesNo == 'Y'){
                int NewSeat = bestAvailable(auditorium, row, colIndex, adult, senior, child);
                //reserve seats
                cout << "your seats have been reserved" << endl;
                //reserve seats adult first, then child, then senior
                while (adult > 0){
                    auditorium[row][NewSeat] = "A";
                    NewSeat++;
                    adult--;
                }
                
                while (child > 0){
                    auditorium[row][NewSeat] = "C";
                    NewSeat++;
                    child--;
                }
                
                while (senior > 0){
                    auditorium[row][NewSeat] = "S";
                    NewSeat++;
                    senior--;
                }
                
            }
            else{
                //guilt trip the user
                cout << "why did you pick seats that were already taken?" << endl;//this is a joke
            }
        }
        else{
            //if no seats are available, display this message
            cout << "no seats available" << endl;
        }
        
    }
}

void displayReport(string auditorium[10][26], int colIndex, int rowIndex){
    //variables to use in calculations
    int adult = 0;
    int child = 0;
    int senior = 0;
    int totalTickets = 0;
    double totalSales = 0.0;

    //report calculations
    for (int i = 0; i < rowIndex; i++){
        for (int j = 0; j < colIndex; j++){
            if (auditorium[i][j] == "A"){
                adult++;
                totalTickets++;
                totalSales += 10.0;
            }
            else if (auditorium[i][j] == "C"){
                child++;
                totalTickets++;
                totalSales += 5.0;
            }
            else if (auditorium[i][j] == "S"){
                senior++;
                totalTickets++;
                totalSales += 7.50;
            }
        }
    }
    //display auditorium seats in file
    ofstream filey;
    filey.open("A1.txt");
    for (int i = 0; i < rowIndex; i++)
    {
        for (int j = 0; j < colIndex; j++)
        {
            filey << auditorium[i][j];
        }
        if (i != rowIndex-1){
            filey << endl;
        }
        
    }

    //iomanip for everything 
    cout << fixed << setprecision(2);
    //////////////////////////////////////////////////////////////////
    //display total seats
    cout << "Total Seats: " << rowIndex*colIndex << endl;
    //display total tickets
    cout << "Total Tickets: " << totalTickets << endl;
    //display total adult child senior tickets
    cout << "Adult Tickets: " << adult << endl;
    cout << "Child Tickets: " << child << endl;
    cout << "Senior Tickets: " << senior << endl;
    //display total sales
    cout << "Total Sales: " << "$" << totalSales << endl;
    
}

//good main function?
int main(){
 ///////////////////////////////////////////////
 //variables
    string auditorium[10][26];
    string filetxt;
    int rowIndex = 0;
    int columnIndex = 0;
    string choice;
    cout << "file name required" << endl;
    cin >> filetxt;
    fstream file;
    file.open(filetxt, ios::in);
            
    //copy file into auditorium array
    if (file.is_open())
    {
        string line;
        while(getline(file, line)){
            for (int j = 0; j < 26; j++)
            {
                if (line[j] == '.' || line[j] == 'A' || line[j] == 'S' || line[j] == 'C'){
                    auditorium[rowIndex][j] = line[j];
                    columnIndex++;
                }
                else{
                    break;
                    }
            }
            rowIndex++;
        }
        file.close();
        //since you get every single iteration of the file, you have to divide the column index by the row index
        //that way you get the actual number of columns
        columnIndex = columnIndex/rowIndex;
        //file is successfully copied into auditorium array
    }

    /////////////////////////////////////////////////////////////
    do{
        //menu
        cout << "1. Reserve Seats" << endl;
        cout << "2. exit" << endl;
        cin >> choice;

        //if user chooses to reserve seats
        if (choice == "1" || choice == "reserve seats"){
       //add all calculations and functions here
            int row = -1;
            char col = -1;
            int adult = -1;
            int child = -1;
            int senior = -1;
            
            // Call the display function to print the auditorium for the consumer only on the console
            displayAuditorium(auditorium, rowIndex);
           
            //prompt for row
            while (row > rowIndex || row < 1){
                cout << "Enter row: ";
                cin >> row;
                if (row > rowIndex || row < 1){
                    cout << "Invalid row" << endl;
                }
            }

            //prompt for starting seat/column
            while ((col-'A') >= columnIndex || (col-'A') < 0){
                cout << "Enter starting seat: ";
                cin >> col;
                if ((col-'A') >= columnIndex || (col-'A') < 0){
                    cout << "Invalid starting seat" << endl;
                }
            }

            //loop until number of adult tickets
            while (adult < 0){
                cout << "Enter number of adult tickets: " << endl;
                cin >> adult;
                if (adult < 0){
                    cout << "Invalid number of adult tickets" << endl;
                }
            }
            //loop until valid number of child tickets
            while (child < 0){
                cout << "Enter number of child tickets: " << endl;
                cin >> child;
                if (child < 0){
                    cout << "Invalid number of child tickets" << endl;
                }
            }
            //loop until valid number of senior tickets
            while (senior < 0){
                cout << "Enter number of senior tickets: " << endl;
                cin >> senior;
                if (senior < 0){
                    cout << "Invalid number of senior tickets" << endl;
                }
            }
            //check if seats are available
            reserveSeats(auditorium, (row-1), columnIndex, (col-65), adult, senior, child);
            //if seats are available, reserve seats
            //if seats are not available, display best available seats
        
        
        }
    }while(choice == "1" || choice == "reserve seats" /*|| choice != "2" || choice != "exit"*/);
    //displays report and writes to A1.txt file
    displayReport(auditorium, columnIndex, rowIndex);

    return 0;
}

package MovieSimJava;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintWriter;
import java.util.Scanner;


public class Main{
    
    public static void displayAuditorium(char[][] auditorium, int row, int col){
        System.out.print("    ");

        // Print the column letter
        for(int i = 0; i < col; i++){
            char j = (char) (i + 65);
            System.out.print(j);
        }
        System.out.println();

        //print the auditorium
        for(int i = 0; i < row; i++){
            System.out.print(i + 1 + "   ");
            for(int j = 0; j < col; j++){
                if(auditorium[i][j] == 'A' || auditorium[i][j] == 'S' || auditorium[i][j] == 'C'){
                    System.out.print("#");
                }
                else{
                    System.out.print(auditorium[i][j]);
                }
            }
            System.out.println();
        }


    }

    public static int bestAvailable(char[][] auditorium, int row, int colIndex, int adult, int senior, int child){
        //initialize variables
        int total = adult + senior + child;
        int bestSeat = -1;
        int bestV = colIndex+1;
        int v = colIndex+1;
        int middle;

        //loop through the row
        for (int i = 0; i <= (colIndex - total); i++){
            Boolean available = true;
            for(int j = 0; j < total; j++){
                //if there is a seat that is already taken, break out of the loop
                if (auditorium[row][i + j] == 'A' || auditorium[row][i + j] == 'S' || auditorium[row][i + j] == 'C'){
                    available = false;
                    break;
                }
            }
            //if there are no seats taken, find the best seat
            if(available){
                middle = (i + (i + total))/2;//middle seat
                v = Math.abs(middle - (colIndex/2));//how close you are to the middle of the row
                if (v < bestV){
                    bestV = v;
                    bestSeat = i;
                }
            }
        }
        //return the best seat that was found
        return bestSeat;
    }

    public static Boolean checkSeats(char[][] auditorium, int row, int seat, int adult, int senior, int child){
        //check if seats are available
    int totalSeats = adult + senior + child;
    //loop through the seats
    for (int i = 0; i < totalSeats; i++){
        if (auditorium[row][seat + i] == 'A' || auditorium[row][seat + i] == 'S' || auditorium[row][seat + i] == 'C'){
            //if there is a seat that is already taken, return false
            return false;
        }
    }
    //if there are no seats taken, return true
    return true;
    }

    public static void reserveSeats(char[][] auditorium, int row, int colIndex, int seat, int adult, int senior, int child, Scanner s){
        char yesNo = 'b';
    //check if seats are available
    if (checkSeats(auditorium, row, seat, adult, senior, child)){
        //reserve seats adult first, then child, then senior
        System.out.println("your seats have been reserved");
        while (adult > 0){
            auditorium[row][seat] = 'A';
            seat++;
            adult--;
        }
        
        while (child > 0){
            auditorium[row][seat] = 'C';
            seat++;
            child--;
        }
        
        while (senior > 0){
            auditorium[row][seat] = 'S';
            seat++;
            senior--;
        }
        
    }
    else{
        //display best available seats if seats selected are not available
        if (bestAvailable(auditorium, row, colIndex, adult, senior, child)  != -1)
        {
            //prompt for if user wants best available seats
            System.out.println("Although there are no exact seats that match this description, these are the closest seats we have to the ones");
                //find seat name and number
                char firstSeat = (char) (bestAvailable(auditorium, row, colIndex, adult, senior, child) + 65);
            System.out.print(" that you have picked: ");
            System.out.print(row+1);
            System.out.print(firstSeat);
            if ((adult + child + senior) > 1){
                char lastSeat = (char) (bestAvailable(auditorium, row, colIndex, adult, senior, child) + (adult + child + senior) + 64);
                System.out.print(" - ");
                System.out.print(row+1);
                System.out.println(lastSeat);
            }
            //ask if they would like to confirm these seats
            System.out.println("\nwould you still like to confirm these seats? (y/n)");
            //if yes, reserve seats
            yesNo = s.next().charAt(0);
            if (yesNo == 'y' || yesNo == 'Y'){
                int NewSeat = bestAvailable(auditorium, row, colIndex, adult, senior, child);
                //reserve seats
                System.out.println("your seats have been reserved");
                //reserve seats adult first, then child, then senior
                while (adult > 0){
                    auditorium[row][NewSeat] = 'A';
                    NewSeat++;
                    adult--;
                }
                
                while (child > 0){
                    auditorium[row][NewSeat] = 'C';
                    NewSeat++;
                    child--;
                }
                
                while (senior > 0){
                    auditorium[row][NewSeat] = 'S';
                    NewSeat++;
                    senior--;
                }
                
            }
            else{
                //guilt trip the user
                System.out.println("why did you pick seats that were already taken?");//this is a joke
            }
        }
        else{
            //if no seats are available, display this message
            System.out.println("no seats available");
        }
    }//check this bracket (brace)
    
    }
    
    public static void displayReport(char [][]auditorium, int row, int col){
        //variavble initialization
        int adult = 0;
        int senior = 0;
        int child = 0;
        int totalTickets = 0;
        double totalSales = 0.0;

        //create output file and test if it works or not
        try{
        FileOutputStream fileStream = new FileOutputStream("A1.txt");
        PrintWriter out = new PrintWriter("A1.txt");

        //print the auditorium
        for(int i = 0; i < row; i++){
            for(int j = 0; j < col; j++){
                out.print(auditorium[i][j]);
            }
            out.println();
        }
        //close file and print
        out.close();
        fileStream.close();
        }
        catch(FileNotFoundException e){
            System.out.println("File not found");
        }catch(Exception e){
            System.out.println("Error");
        }
        
        //loop through auditorium
        for(int i = 0; i < row; i++){
            for(int j = 0; j < col; j++){
                //if seat is taken, add to the total tickets, whoever's seat it was, and total sales
                if(auditorium[i][j] == 'A'){
                    adult++;
                    totalTickets++;
                    totalSales += 10.0;
                }
                else if(auditorium[i][j] == 'S'){
                    senior++;
                    totalTickets++;
                    totalSales += 7.5;
                }
                else if(auditorium[i][j] == 'C'){
                    child++;
                    totalTickets++;
                    totalSales += 5.0;
                }
            }
        }
        
        //print the report
        System.out.println("Total Seats: " + (row * col));
        System.out.println("Total Tickets: " + totalTickets);
        System.out.println("Adult Tickets: " + adult);
        System.out.println("Child Tickets: " + child);
        System.out.println("Senior Tickets: " + senior);
        //printf for the decimal values 
        System.out.printf("Total Sales: $%.2f", totalSales);

    }
    
    public static void main(String[] args) {
        //variable initialization
        char [][]auditorium = new char[10][26];
        int row = 0;
        int col = -1;
        int choice = -1;

        //get input file
        Scanner s = new Scanner(System.in);
        System.out.println("Enter the name of the file: ");
        String fileName = s.nextLine();
        File file = new File(fileName);
        //see if file can open or not, if it can continue with the program, if not, say it cannot be found
        try{
            Scanner fileScanner = new Scanner(file);
            //get the auditorium
            while (fileScanner.hasNext()){
                String line = fileScanner.next();
                col = line.length();
                for(int j = 0; j < col; j++){
                    auditorium[row][j] = line.charAt(j);
                }
                row++;
            }
            //close scanner
            fileScanner.close();
            

        }
        catch(FileNotFoundException e){
            //if file cannot be found, print this
            System.out.println("File not found");
        }
        
        do{
            //initialize variables (given bogus values as to not get an error when going through initial run)
            int userRow = -1;
            char userCol = 255;
            int adult = -1;
            int child = -1;
            int senior = -1;
            
            //display menu
            System.out.println("1. Reserve Seats");
            System.out.println("2. Exit");
            choice = s.nextInt();
            if(choice == 1){
                displayAuditorium(auditorium, row, col);
                
                //get user input
                //validate user input for every input
                while (userRow < 1 || userRow > row){
                    System.out.println("Enter the row of the seat you want to reserve: ");
                    userRow = s.nextInt();
                    if (userRow < 1 || userRow > 10){
                        System.out.println("Invalid row");
                    }
                }
                
                while (userCol < 65 || userCol > 65 + col){
                    System.out.println("Enter the seat you want to reserve: ");
                    userCol = s.next().charAt(0);
                    if (userCol < 65 || userCol > col + 65){
                        System.out.println("Invalid seat");
                    }
                }
                
                while (adult < 0){
                    System.out.println("Enter the number of adult tickets: ");
                    adult = s.nextInt();
                    if (adult < 0){
                        System.out.println("Invalid number of tickets");
                    }
                }

                while (child < 0){
                    System.out.println("Enter the number of child tickets: ");
                    child = s.nextInt();
                    if (child < 0){
                        System.out.println("Invalid number of tickets");
                    }
                }

                while (senior < 0){
                    System.out.println("Enter the number of senior tickets: ");
                    senior = s.nextInt();
                    if (senior < 0){
                        System.out.println("Invalid number of tickets");
                    }
                }
                //once all inputs have been verified, reserve seats
                reserveSeats(auditorium, userRow-1, col,  userCol - 65, adult, senior, child, s);

            }
            else if(choice == 2){
                //when user is done with program, display report and exit
                displayReport(auditorium, row, col);
                //close scanner
                s.close();
                System.exit(0);
            }
            else{
                //if user inputs invalid option, display this
                System.out.println("Invalid option");
            }
        }while(choice != 2); //continue running until 2 is entered
        
    }
    
}
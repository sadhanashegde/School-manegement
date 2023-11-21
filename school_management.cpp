/*---------------------------------------------SCHOOL MANAGEMENT SYSYTEM--------------------------------------------------------------------------------------------------*/
#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include<sstream>
#include<limits>

using namespace std;

int i = 0;

struct student
{
    string roll,name, clas;
    float tot, obt, per;
} s[10];

void control_panel()
{
    cout << "\n\n\n\t\t\t\t***** Control Panel *****";
    cout << "\n\n 1. Insert Record";
    cout << "\n 2. Display Record";
    cout << "\n 3. Search Record";
    cout << "\n 4. Update Record";
    cout << "\n 5. Delete Record";
    cout << "\n 6. School Information";
    cout << "\n 7. Exit";
    cout << "\n\n Enter Your Choice : ";
}


void insert(student s[]) {
    system("cls");
    cout << "\n\n\t\t\t\tInsert Record";

    // Input validation for the roll number
    bool validRoll = false;
    do {
        cout << "\n\n Roll No. (numbers only): ";
        cin >> s[i].roll;
        validRoll = true;
        for (char c : s[i].roll) {
            if (!isdigit(c)) {
                cout << "Invalid input. Roll number should only contain numbers." << endl;
                validRoll = false;
                break;
            }
        }
    } while (!validRoll);

    // Input validation for the name (no numbers allowed)
    bool validName = false;
    do {
        cout << "\n\t\t\tName (no numbers): ";
        cin >> s[i].name;
        validName = true;
        for (char c : s[i].name) {
            if (isdigit(c)) {
                cout << "Invalid input. Name should not contain numbers." << endl;
                validName = false;
                break;
            }
        }
    } while (!validName);

    // Input validation for marks
    bool validMarks = false;
    do {
        cout << "\n Class : ";
        cin >> s[i].clas;
        cout << "\n\t\t\tTotal Marks (numbers only): ";
        cin >> s[i].tot;
        cout << "\n Obtained Marks (numbers only): ";
        cin >> s[i].obt;

        validMarks = true;

        if (!cin || s[i].tot < 0 || s[i].obt < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Total Marks and Obtained Marks should be positive numbers." << endl;
            validMarks = false;
        }
    } while (!validMarks);
 
    // Calculate the percentage
    s[i].per = (s[i].obt / s[i].tot) * 100;

    ofstream outFile;
    outFile.open("student_records.txt", ios::app); // Open the file in append mode

    if (outFile.is_open()) {
        outFile << s[i].roll << " " << s[i].name << " " << s[i].clas << " " << s[i].tot << " " << s[i].obt << " " << s[i].per << "%" << "\n";
        outFile.close(); // Close the file
    } else {
        cout << "Unable to open file";
    }
    i++;
}






void display(student s[])
{
    int c = 1;
    system("cls");
    cout << "\n\n\t\t\t\tDisplay Record"<<endl;
    
	cout<<"Students"<<endl; 
    
	ifstream inFile("student_records.txt");
    if (inFile.is_open())
    {
        string line;
        while (getline(inFile, line))
        {
            cout << line << endl;
        }
        inFile.close();
    }
    else
    {
        cout << "Unable to open file";
    }
}

void search(student s[])
{
    int count = 0;
    string roll;
    system("cls");
    cout << "\n\n\t\t\t\tSearch Record";
    
    cout << "\n\n Roll No. For Search : ";
    cin >> roll;
        
	ofstream outFile;
    outFile.open("student_records.txt", ios::app); // Open the file in append mode

    ifstream inFile("student_records.txt");
    if (inFile.is_open())
    {
        string line;
        while (getline(inFile, line))
        {
            istringstream iss(line);
            string fileRoll;
            iss >> fileRoll;
            if (roll == fileRoll)
            {
                cout << "\n\n Roll No. : " << fileRoll;
                string fileName, fileClass;
                float fileTotal, fileObtained, filePercentage;
                iss >> fileName >> fileClass >> fileTotal >> fileObtained >> filePercentage;
                cout << "\n\t\t\t Name : " << fileName;
                cout << "\n Class : " << fileClass;
                cout << "\n\t\t\t Total Marks : " << fileTotal;
                cout << "\n Obtained Marks : " << fileObtained;
                cout << "\n\t\t\t Percentage % : " << filePercentage;
                count++;
            }
        }
        inFile.close();
    }

    if (count == 0)
    {
        cout << "\n\n Record Not Found...";
    }
    else
    {
        cout << "\n\n Found " << count << " record(s).";
    }
}
void update(student s[]) {
    system("cls");
    string roll;
    int count = 0;
    cout << "\n\n\t\t\t\tUpdate Record";

    if (1) {
        bool isNumeric = true;
        do {
            isNumeric = true;
            cout << "\n\n Roll No. For Update (Numeric only): ";
            cin >> roll;
            for (char c : roll) {
                if (!isdigit(c)) {
                    isNumeric = false;
                    cout << "Invalid input. Please enter numeric characters only." << endl;
                    break;
                }
            }
        } while (!isNumeric);

        ifstream file("student_records.txt");
        int numLines = 0;
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                numLines++;
            }
            file.close();
        }

        bool found = false;
        int i = 0; // assuming i is declared and defined somewhere in the code
        for (int a = 0; a < numLines; a++) {
            if (roll == s[a].roll) {
                cout << "\n\n New Roll No. : ";
                cin >> s[a].roll;
                cout << "\n\t\t\tName : ";
                cin >> s[a].name;
                cout << "\n Class : ";
                cin >> s[a].clas;
                do {
                    cout << "\n\t\t\tTotal Marks (Non-negative): ";
                    while (!(cin >> s[a].tot)) {
                        cout << "Invalid input. Please enter a valid non-negative number." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    if (s[a].tot < 0) {
                        cout << "Total marks cannot be negative. Please enter a non-negative value." << endl;
                    }
                } while (s[a].tot < 0);

                do {
                    cout << "\n Obtained Marks (Non-negative): ";
                    while (!(cin >> s[a].obt)) {
                        cout << "Invalid input. Please enter a valid non-negative number." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    if (s[a].obt < 0) {
                        cout << "Obtained marks cannot be negative. Please enter a non-negative value." << endl;
                    }
                } while (s[a].obt < 0);

                s[a].per = (s[a].obt / static_cast<float>(s[a].tot)) * 100;
                count++;
                found = true;
            }
        }

        if (!found) {
            // If the roll number is not found, add it as a new record
            s[i].roll = roll;
            cout << "\n\t\t\tName : ";
            cin >> s[i].name;
            cout << "\n Class : ";
            cin >> s[i].clas;
            do {
                cout << "\n\t\t\tTotal Marks (Non-negative): ";
                while (!(cin >> s[i].tot)) {
                    cout << "Invalid input. Please enter a valid non-negative number." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                if (s[i].tot < 0) {
                    cout << "Total marks cannot be negative. Please enter a non-negative value." << endl;
                }
            } while (s[i].tot < 0);

            do {
                cout << "\n Obtained Marks (Non-negative): ";
                while (!(cin >> s[i].obt)) {
                    cout << "Invalid input. Please enter a valid non-negative number." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                if (s[i].obt < 0) {
                    cout << "Obtained marks cannot be negative. Please enter a non-negative value." << endl;
                }
            } while (s[i].obt < 0);

            s[i].per = (s[i].obt / static_cast<float>(s[i].tot)) * 100;
            i++;
            count++;
        }

        if (count == 0) {
            cout << "\n\n Record Not Found...";
        }
    } else {
        cout << "\n\n Data Base is Empty...";
    }

    // Update the "student_records.txt" file with the modified records
    ofstream outFile("student_records.txt");
    if (outFile.is_open()) {
        for (int a = 0; a < i; a++) {
            outFile << s[a].roll << " " << s[a].name << " " << s[a].clas << " " << s[a].tot << " " << s[a].obt << " " << s[a].per << "%" << "\n";
        }
        outFile.close();
    } else {
        cout << "Unable to open file for updating records.";
    }
}










 void del(student s[]) { 
    system("cls");
    string roll;
    int count = 0;
    cout << "\n\n\t\t\t\tDelete Record";
    if (1) {
        cout << "\n\n Roll No. For Delete : ";
        cin >> roll;

        // Count the number of lines in the file
        ifstream file("student_records.txt");
        int numLines = 0;
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                numLines++;
            }
            file.close();
        }

        // Reopen the file for reading
        file.open("student_records.txt");
        ofstream temp("temp.txt");
        if (file.is_open() && temp.is_open()) {
            string line;
            for (int a = 0; a < numLines; a++) {
                getline(file, line);
                istringstream iss(line);
                string fileRoll;
                iss >> fileRoll;
                if (roll == fileRoll) {
                    // Skip this line (delete the record)
                    count++;
                } else {
                    // Write the line to the temporary file
                    temp << line << "\n";
                }
            }
            file.close();
            temp.close();
            remove("student_records.txt");
            rename("temp.txt", "student_records.txt");
        } else {
            cout << "Unable to open file";
        }

        if (count == 0) {
            cout << "\n\n Record Not Found...";
        } else {
            cout << "\n\n Found and deleted " << count << " record(s).";
            i--; // Decrement the record count
        }
    } else {
        cout << "\n\n Data Base is Empty...";
    }

    // Update the student array from the modified file
    ifstream inFile("student_records.txt");
    if (inFile.is_open()) {
        for (int a = 0; a < i; a++) {
            inFile >> s[a].roll >> s[a].name >> s[a].clas >> s[a].tot >> s[a].obt >> s[a].per;
        }
        inFile.close();
    } else {
        cout << "Unable to open file";
    }
 }	
	

void school_info()
{
    int choice;
    char filename[20];//
    ifstream file;  // Declare the ifstream variable here to read info in the file

    cout << "\n\n\t\t\t\tSchool Information";
    cout << "\n\n\t\t\t1. Open File";
    cout << "\n\n\t\t\t2. Exit";
    cout << "\n\n\t\t\tEnter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
	cout<<"holiday.txt , extra_circulam.txt , faculty.txt"<<endl;
        cout << "\n\n\t\t\tEnter the file name: ";
        cin >> filename;
        file.open(filename);  // Open the file here

        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                cout << line << endl;
            }
            file.close();  // Close the file here
        }
        else
        {
            cout << "\n\n\t\t\tError opening file";
        }
        break;

    case 2:
        break;

    default:
        cout << "\n\n Invalid Choice...";
    }
}
 
 







int main()
{
    int choice;
    char x;
p:                    //it is the label used -- to display text or images that cannot be interacted with.
    system("cls");	
	system("color 03");	
    control_panel();
    cin >> choice;
    switch (choice)
    {
    case 1:
        do
        {
            insert(s);
            cout << "\n\n Do You Want To Add Another Record (y,n) : ";
            cin >> x;
        } while (x == 'y');
        break;
    case 2:
        display(s);
        break;
    case 3:
        search(s);
        break;
    case 4:
        update(s);
        break;
    case 5:
        del(s);
        break;
    case 6:
        school_info();
        break;
    case 7:
        exit(0);
    default:
        cout << "\n\n Invalid Value...Please Try Again...";
    }
   
		getch();
		goto p;//The goto statement can be used to alter the normal flow of control in a program. This statement causes the program to jump to a specified labe
}
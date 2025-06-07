#include<iostream>
#include<iomanip>
#include<fstream>

using namespace std;

bool admin_login();
void User_Role_Management();

void manageAdmins();
void manageEmployees();
void manageRole(const char* fileName, const char* roleType);

void addRole(const char* fileName, const char* roleType);
void removeRole(const char* fileName, const char* roleType);
void editRole(const char* fileName, const char* roleType);

// Customer Management
void manageCustomers();
void addCustomer();
void removeCustomer();
void editCustomer();


void removeProduct1(int productId);
void addProduct1();
void updateProduct1(int productId);
void viewallProducts2();
void bulkExport(const char* inputFileName, const char* outputFileName);
void bulkImport(const char* inputFileName, const char* outputFileName);
void trim2(char* str);




bool usernameExists(const char* roleFile, const char* username);
void copyText(char* dest, const char* src);
bool stringCompare(const char* str1, const char* str2);
void Advan_Pro_Management();
bool isEqual(char* str1, char* str2);
void RemovePromoCodeFromProduct();
void ModifyPromoCodeForProduct();
void AddPromoCodeForProduct();
void ViewPromoCode();
void announcement();
void displaylogs();
void viewAnnouncements();
void addAnnouncement(const char* announcement);



void Dicount_Promotions();
void Sales_Revenue_Analysis()
{

}
void Audit_Trial()
{

}






void admin()
{
    int choice = 0;

    do
    {
        if (admin_login())
        { // ADMIN LOGIN STARTS HERE
            do { // MENU LOOP STARTS HERE
                cout << "\t \t*************************************************\n";
                cout << "\t \t*               Admin Menu                      *\n";
                cout << "\t \t*************************************************\n\n";

                cout << "\t \t----------------------------------------------------------" << endl;
                cout << "\t \t|   1-->  User and Role Management                         |" << endl;
                cout << "\t \t----------------------------------------------------------" << endl;
                cout << "\t \t|   2-->  Advanced Product Management                      |" << endl;
                cout << "\t \t----------------------------------------------------------" << endl;
                cout << "\t \t|   3-->  Discounts and Promotions                         |" << endl;
                cout << "\t \t----------------------------------------------------------" << endl;
                cout << "\t \t|   4-->  Activity Logs and Security Monitoring            |" << endl;
                cout << "\t \t----------------------------------------------------------" << endl;
                cout << "\t \t|   5-->  Sales and Revenue Analysis                       |" << endl;
                cout << "\t \t----------------------------------------------------------" << endl;
                cout << "\t \t|   6-->  Audit Trail                                      |" << endl;
                cout << "\t \t----------------------------------------------------------" << endl;
                cout << "\t \t|   7-->  Announcements                                    |" << endl;
                cout << "\t \t----------------------------------------------------------" << endl;
                cout << "\t \t|   8--> Exit                                             |" << endl;
                cout << "\t \t _________________________________________________________" << endl;

                cout << "Enter your Choice: ";
                cin >> choice;

               
                if (cin.fail() || choice < 1 || choice > 8) {
                    cin.clear(); 
                    cin.ignore(1000, '\n'); 
                    cout << "Invalid input. Please enter a number between 1 and 8.\n";
                    continue; 
                }

                // Handle Menu Options
                switch (choice) {
                case 1:
                    User_Role_Management();
                    break;
                case 2:
                    Advan_Pro_Management();
                    break;
                case 3:
                    Dicount_Promotions();
                    break;
                case 4:
                    displaylogs();
                    break;
                case 5:
                    Sales_Revenue_Analysis();
                    break;
                case 6:
                    Audit_Trial();
                    break;
                case 7:
                    announcement();
                    break;
                case 8:
                    cout << "Exiting the program...\n";
                    return; 
                default:
                    cout << "An unexpected error occurred. Please try again.\n";
                }
            } while (true); 
        }
        else {
            
            cout << "You entered wrong credentials for admin.\n";
        }
    } while (true); 
}











void resizeArray(char*& array, int& size)
{
    int newSize = size * 2;
    char* newArray = new char[newSize];
    for (int i = 0; i < size; i++)
    {
        newArray[i] = array[i];
    }
    delete[] array;
    array = newArray;
    size = newSize;
}







bool admin_login()
{
    int usernameSize = 20, passwordSize = 20, bufferSize = 100;
    char* username = new char[usernameSize];
    char* password = new char[passwordSize];
    char* storedUsername = new char[20];
    char* storedPassword = new char[20];
    char* lineBuffer = new char[bufferSize];

    while (true) //agr login fail hoa to loop dobara chly ga
    { 
        cout << "Enter username: ";
        cin.ignore(); 
        int usernameLength = 0;
        char inputChar;
        while ((inputChar = cin.get()) != '\n')
        {
            if (usernameLength >= usernameSize - 1) resizeArray(username, usernameSize);
            username[usernameLength++] = inputChar;
        }
        username[usernameLength] = '\0';

        if (username[0] == '\0')
        {
            cout << "Username cannot be empty.\n";
            continue; 
        }

        cout << "Enter password: ";
        int passwordLength = 0;
        while ((inputChar = cin.get()) != '\n')
        {
            if (passwordLength >= passwordSize - 1) resizeArray(password, passwordSize);
            password[passwordLength++] = inputChar;
        }
        password[passwordLength] = '\0';

        if (password[0] == '\0')
        {
            cout << "Password cannot be empty.\n";
            continue; // Restart login attempt
        }

        ifstream inputFile("admin.csv");// Admin ki file open ho gae data read krny ka leay
        if (!inputFile) 
        {
            cerr << "Error: Unable to open admin file.\n";
            delete[] username;
            delete[] password;
            delete[] storedUsername;
            delete[] storedPassword;
            delete[] lineBuffer;
            return false;
        }

        fstream logFile("logs.txt", ios::out | ios::app);// Logs ki file open ho gae attempt write krny ka liay
        if (!logFile)
        {
            cerr << "Error: Unable to open log file.\n";
            delete[] username;
            delete[] password;
            delete[] storedUsername;
            delete[] storedPassword;
            delete[] lineBuffer;
            return false;
        }

        bool loginSuccessful = false;

        
        inputFile.clear();  
        inputFile.seekg(0); // Pointer ko start lany ka liay 

        while (inputFile.getline(lineBuffer, bufferSize))
 {
            int lineIndex = 0, storedIndex = 0;

            // Username extract krny ka liay array mn sy
            while (lineBuffer[lineIndex] != ',' && lineBuffer[lineIndex] != '\0')
            {
                storedUsername[storedIndex++] = lineBuffer[lineIndex++];
            }
            storedUsername[storedIndex] = '\0';
            if (lineBuffer[lineIndex] == ',') lineIndex++;

            // Password extract krny ka liay array mn sy
            storedIndex = 0;
            while (lineBuffer[lineIndex] != ',' && lineBuffer[lineIndex] != '\0')
            {
                storedPassword[storedIndex++] = lineBuffer[lineIndex++];
            }
            storedPassword[storedIndex] = '\0';

            // Username match krny ka liay file mn store ko user input ka sath
            bool isUsernameMatch = true, isPasswordMatch = true;
            for (int i = 0; username[i] != '\0' || storedUsername[i] != '\0'; ++i)
            {
                if (username[i] != storedUsername[i]) {
                    isUsernameMatch = false;
                    break;
                }
            }

            //Password match krny ka liay file mn store ko user input ka sath
            for (int i = 0; password[i] != '\0' || storedPassword[i] != '\0'; ++i)
            {
                if (password[i] != storedPassword[i])
                {
                    isPasswordMatch = false;
                    break;
                }
            }

            if (isUsernameMatch && isPasswordMatch)
            {
                logFile << "Admin login successful for username: " << username << endl;
                loginSuccessful = true;
                break;
            }
        }

        inputFile.close();

        if (loginSuccessful)
        {
            cout << "Login successful!\n";//agr login successful ho jata ha then menu mn enter 
            logFile.close();
            break;
        }
        else
        {
            logFile << "Admin login failed for username: " << username << endl;
            cout << "Incorrect username or password. Please try again.\n";
            logFile.close();
        }
    }

    // Memory clean krny ka liay jo dynamic bnai thi
    delete[] username;
    delete[] password;
    delete[] storedUsername;
    delete[] storedPassword;
    delete[] lineBuffer;

    return true;
}




void User_Role_Management()
{
    int choice;

    while (true)
    {
        cout << "------------------------------------------\n";
        cout << "|          Role Management Menu          |\n";
        cout << "|----------------------------------------|\n";
        cout << "| 1. Manage Admins                       |\n";
        cout << "| 2. Manage Employees                    |\n";
        cout << "| 3. Manage Customers                    |\n";
        cout << "| 4. Exit                                |\n";
        cout << "------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;


    

        switch (choice)
        {
        case 1:
            manageAdmins();
            break;
        case 2:
            manageEmployees();
            break;
        case 3:
            manageCustomers();
            break;
        case 4:
            cout << "Exiting Role Management Menu.\n";
            return;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}




void manageAdmins() {
    manageRole("admin.csv", "Admin");
}

void manageEmployees() {
    manageRole("employee.csv", "Employee");
}





void manageRole(const char* fileName, const char* roleType)
{
    int choice;

    while (true)
    {
        cout << "------------------------------------------\n";
        cout << "|          " << roleType << " Management Menu         |\n";
        cout << "|----------------------------------------|\n";
        cout << "| 1. Add " << roleType << "                           |\n";
        cout << "| 2. Remove " << roleType << "                        |\n";
        cout << "| 3. Edit " << roleType << "                          |\n";
        cout << "| 4. Back to Main Menu                    |\n";
        cout << "------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;


     

        switch (choice)
        {
        case 1:
            addRole(fileName, roleType);
            break;
        case 2:
            removeRole(fileName, roleType);
            break;
        case 3:
            editRole(fileName, roleType);
            break;
        case 4:
            return;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}




void addRole(const char* fileName, const char* roleType)
{
    ofstream fileOut(fileName, ios::app);//file open hui jo role user na select kia tha usi lehaz sy wohi file name aya

    if (!fileOut.is_open())
    {
        cout << "Error: Could not open " << fileName << " file.\n";
        return;
    }

    char* name = new char[50];
    char* password = new char[50];

    cin.ignore();
    cout << "Enter " << roleType << " Name: ";
    cin.getline(name, 50);
    cout << "Enter " << roleType << " Password: ";
    cin.getline(password, 50);

    // Data write krny ka liay file pr username and password
    fileOut << name << "," << password << endl;

    cout << roleType << " added successfully!\n";

    delete[] name;
    delete[] password;

    fileOut.close();
}





void removeRole(const char* fileName, const char* roleType)
{
    ifstream fileIn(fileName);
    ofstream fileOut("temp.csv");// ik temporary file use ki data swap krny ka liay mtlb ik role delete krna tha

    if (!fileIn.is_open() || !fileOut.is_open())
    {
        cout << "Error: Could not open " << fileName << " file.\n";
        return;
    }

    char* nameToRemove = new char[50];
    char* line = new char[200];
    char* name = new char[50];
    bool found = false;

    cin.ignore();
    cout << "Enter " << roleType << " Name to Remove: ";
    cin.getline(nameToRemove, 50);

    while (fileIn.getline(line, 200))
    {
        int i = 0, j = 0;

        // Name find krny ka liay file syy
        while (line[i] != ',' && line[i] != '\0') {
            name[j++] = line[i++];
        }
        name[j] = '\0';

        // phr use ka enetred name compare krny ka liay
        bool isSame = true;
        int k = 0;
        while (name[k] != '\0' || nameToRemove[k] != '\0')
        {
            if (name[k] != nameToRemove[k])
            {
                isSame = false;
                break;
            }
            k++;
        }

        if (!isSame)
        {
            fileOut << line << endl;
        }
        else 
        {
            found = true;
        }
    }

    fileIn.close();
    fileOut.close();

    if (found)//agr name mil jata ha then removing
    {
        remove(fileName);
        rename("temp.csv", fileName);
        cout << roleType << " removed successfully!\n";
    }
    else
    {
        cout << roleType << " not found.\n";
        remove("temp.csv");
    }

    delete[] nameToRemove;
    delete[] line;
    delete[] name;
}





void editRole(const char* fileName, const char* roleType)
{
    ifstream fileIn(fileName);
    ofstream fileOut("temp.csv");//Role edit krny ka liay temporary file

    if (!fileIn.is_open() || !fileOut.is_open())
    {
        cout << "Error: Could not open " << fileName << " file.\n";
        return;
    }

    char* nameToEdit = new char[50];
    char* line = new char[200];
    char* name = new char[50];
    bool found = false;

    cin.ignore(); 
    cout << "Enter " << roleType << " Name to Edit: ";
    cin.getline(nameToEdit, 50);


    while (fileIn.getline(line, 200))
    {
        int i = 0, j = 0;

        // Name extract krny ka liay
        while (line[i] != ',' && line[i] != '\0') {
            name[j++] = line[i++];
        }
        name[j] = '\0';

        // Manually name comapre krny ka liay
        bool isSame = true;
        int k = 0;
        while (name[k] != '\0' || nameToEdit[k] != '\0')
        {
            if (name[k] != nameToEdit[k])
            {
                isSame = false;
                break;
            }
            k++;
        }

        if (isSame)//Agr name mil jata ha
        {
            found = true;

            char* password = new char[50];
            int choice;

            cout << "======Select an option to edit=====\n";
            cout << "--->1. Edit Name\n--->2. Edit Password\n";
            cin >> choice;
            cin.ignore(); 

            switch (choice)
            {
            case 1:
            {
                char* newName = new char[50];
                cout << "Enter New Name: ";
                cin.getline(newName, 50);
                fileOut << newName << ","; // Updated name file mn write krny ka liay
                delete[] newName;

                
                i++; //  comma skip krny ka liay
                j = 0;
                while (line[i] != '\0')
                {
                    password[j++] = line[i++];
                }
                password[j] = '\0';
                fileOut << password << endl;//Updated password file pr write krny krna liay
                break;
            }
            case 2:
            {
                char* newPassword = new char[50];
                cout << "Enter New Password: ";
                cin.getline(newPassword, 50);
                fileOut << name << ",";
                fileOut << newPassword << endl; 
                delete[] newPassword;
                break;
            }
            default:
                cout << "Invalid option selected.\n";
               // Original line ko unchanged krny ka liay
                fileOut << line << endl;
                break;
            }

            delete[] password;
        }
        else
        {
            // temporary file mn changed copy krny ka liay
            fileOut << line << endl;
        }
    }

    fileIn.close();
    fileOut.close();

    if (found)//agr name mil jay to successfully update krny ka liay
    {
        remove(fileName);
        rename("temp.csv", fileName);
        cout << roleType << " updated successfully!\n";
    }
    else 
    {
        cout << roleType << " not found.\n";
        remove("temp.csv");
    }

    delete[] nameToEdit;
    delete[] line;
    delete[] name;
}





bool usernameExists(const char* roleFile, const char* username)
{
    int lineSize = 100, fileUsernameSize = 20;
    char* line = new char[lineSize];
    char* fileUsername = new char[fileUsernameSize];
    bool exists = false;

    ifstream file(roleFile);

    if (!file)
    {
        cout << "Error: Unable to open the file.\n";
        delete[] line;
        delete[] fileUsername;
        return false;
    }

    while (file.getline(line, lineSize))
    {
        int i = 0, j = 0;

        //useranme extract krny ka liay current line syy
        while (line[i] != ',' && line[i] != '\0')
        {
            if (j >= fileUsernameSize - 1) resizeArray(fileUsername, fileUsernameSize);// Array ko resize krny ka liay in cas
            fileUsername[j++] = line[i++];
        }
        fileUsername[j] = '\0'; // Null-terminate the extracted username

        if (stringCompare(fileUsername, username))
        {
            exists = true;
            break;
        }
    }

    file.close();

    delete[] line;
    delete[] fileUsername;

    return exists;
}





bool stringCompare(const char* str1, const char* str2)//char array ko manually compare krny ka liay
{
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return false;
        }
        i++;
    }
    return str1[i] == '\0' && str2[i] == '\0';
}




void copyText(char* dest, const char* src)//text ko copy krny ka liay mtlb manually character by character assign krty hoay
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}




void manageCustomers()
{
    int choice;

    while (true)
    {
        cout << "------------------------------------------\n";
        cout << "|          Customer Management Menu      |\n";
        cout << "|----------------------------------------|\n";
        cout << "| 1. Add Customer                        |\n";
        cout << "| 2. Remove Customer                     |\n";
        cout << "| 3. Edit Customer                       |\n";
        cout << "| 4. Back to Main Menu                   |\n";
        cout << "------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

    

        switch (choice) 
        {
        case 1:
            addCustomer();
            break;
        case 2:
            removeCustomer();
            break;
        case 3:
            editCustomer();
            break;
        case 4:
            return;
        default:
            cout << "Invalid choice! Please try again.\n";
            break;
        }
    }
}






bool isEmptyString(const char* str)//check krny ka liay character array empty to nahi
{
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i == 0; 
}



bool validateUsername(const char* username)//Username ki validation ka liay
{
    int len = 0;
    while (username[len] != '\0') {
        len++;
    }
    return len >= 5 && len <= 20;
}




void expandArray(char*& arr, int& size)// same array ko resize krny ka liay agr user input define size sy brr jata ha
{
    size *= 2;
    char* newArr = new char[size];
    for (int i = 0; i < size / 2; i++) {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
}






bool areStringsEqual(const char* str1, const char* str2) // manually arrays ko compare krny kaliay
{
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) return false;
        i++;
    }
    return str1[i] == str2[i];
}




bool checkPasswordStrength(const char* password)// Password ki strength check krny ka liay
{
    bool hasUpper = false, hasDigit = false;
    int len = 0;
    while (password[len] != '\0') {
        len++;
    }
    if (len < 8) return false;  // Password must be at least 8 characters long

    for (int i = 0; i < len; i++) {
        if (password[i] >= 'A' && password[i] <= 'Z') hasUpper = true;
        if (password[i] >= '0' && password[i] <= '9') hasDigit = true;
    }

    return hasUpper && hasDigit;
}


bool validateEmailFormat(const char* email)//simple email validation must contain @
{
    int atCount = 0, i = 0;
    while (email[i] != '\0') {
        if (email[i] == '@') atCount++;
        i++;
    }
    return atCount == 1;
}



bool validatePhoneNumber(const char* phoneNo)//phone number must 11 size ka pak
{
    int i = 0;
    while (phoneNo[i] != '\0')
    {
        if (phoneNo[i] < '0' || phoneNo[i] > '9') return false; // Non-digit character
        i++;
    }
    return i == 11; 
}




 
bool validateDOB(const char* dob)// valid DOB ki validation (DD-MM-YYYY format)
{
    int i = 0;
    if (dob[2] != '-' || dob[5] != '-') return false; 
    while (dob[i] != '\0')
    {
        if ((i != 2 && i != 5) && (dob[i] < '0' || dob[i] > '9')) return false; 
        i++;
    }
    return i == 10; 
}





void addCustomer()
{
    const int fieldSize = 50;
    char* username = new char[fieldSize];
    char* password = new char[fieldSize];
    char* email = new char[fieldSize];
    char* phoneNo = new char[fieldSize];
    char* dob = new char[fieldSize];

    int usernameSize = fieldSize, passwordSize = fieldSize, emailSize = fieldSize, phoneSize = fieldSize, dobSize = fieldSize;

    cout << "Enter Username: ";
    cin.ignore();
    cin.getline(username, usernameSize);
    while (isEmptyString(username) || !validateUsername(username))
    {
        cout << "Invalid username. It must be between 3 and 20 characters.\n";
        cout << "Enter Username: ";
        cin.getline(username, usernameSize);
    }

    cout << "Enter Password: ";
    cin.getline(password, passwordSize);
    while (isEmptyString(password) || !checkPasswordStrength(password))
    {
        cout << "Invalid password. It must be at least 8 characters, contain an uppercase letter and a number.\n";
        cout << "Enter Password: ";
        cin.getline(password, passwordSize);
    }

    cout << "Enter Email: ";
    cin.getline(email, emailSize);
    while (isEmptyString(email) || !validateEmailFormat(email))
    {
        cout << "Invalid email format.\n";
        cout << "Enter Email: ";
        cin.getline(email, emailSize);
    }

    cout << "Enter Phone Number (11 digits): ";
    cin.getline(phoneNo, phoneSize);
    while (!validatePhoneNumber(phoneNo))
    {
        cout << "Invalid phone number. It must be 11 digits.\n";
        cout << "Enter Phone Number: ";
        cin.getline(phoneNo, phoneSize);
    }

    cout << "Enter Date of Birth (DD-MM-YYYY): ";
    cin.getline(dob, dobSize);
    while (!validateDOB(dob))
    {
        cout << "Invalid date of birth format. Use DD-MM-YYYY.\n";
        cout << "Enter Date of Birth: ";
        cin.getline(dob, dobSize);
    }

    //Data write krny ka liay file prr updated
    ofstream fileOut("customer.csv", ios::app);
    if (!fileOut.is_open())
    {
        cout << "Error: Could not open customer file.\n";
        delete[] username;
        delete[] password;
        delete[] email;
        delete[] phoneNo;
        delete[] dob;
        return;
    }

    fileOut << username << "," << password << "," << email << "," << phoneNo << "," << dob << endl;//file pr write krny ka liay
    fileOut.close();

    cout << "Customer added successfully!\n";

    // Free memory
    delete[] username;
    delete[] password;
    delete[] email;
    delete[] phoneNo;
    delete[] dob;
}




void editCustomer()
{
    ifstream fileIn("customer.csv");//customer file
    ofstream fileOut("temp.csv");//temporary file

    if (!fileIn.is_open() || !fileOut.is_open()) 
    {
        cout << "Error: Could not open file.\n";
        return;
    }

    char* line = new char[200];
    char* username = new char[50];
    char* password = new char[50];
    char* email = new char[50];
    char* phoneNo = new char[50];
    char* dob = new char[50];

    int usernameSize = 50, passwordSize = 50, emailSize = 50, phoneSize = 50, dobSize = 50;
    bool found = false;

    cout << "Enter the Username of the customer to edit: ";
    cin.ignore();
    cin.getline(username, usernameSize);

    while (fileIn.getline(line, 200))
    {
        int i = 0, j = 0;

         //username extract krny ka liay 
        char* currentUsername = new char[50];
        while (line[i] != ',' && line[i] != '\0')
        {
            currentUsername[j++] = line[i++];
        }
        currentUsername[j] = '\0';

        // username match krny ka liay
        if (areStringsEqual(currentUsername, username))
        {
            found = true;

            // in a sequence in which data of customer is being written
            i++;  
            j = 0;
            while (line[i] != ',' && line[i] != '\0')
            {
                password[j++] = line[i++];
            }
            password[j] = '\0';

            i++;  // Move past the comma after the password
            j = 0;
            while (line[i] != ',' && line[i] != '\0')
            {
                email[j++] = line[i++];
            }
            email[j] = '\0';

            i++;  // Move past the comma after the email
            j = 0;
            while (line[i] != ',' && line[i] != '\0')
            {
                phoneNo[j++] = line[i++];
            }
            phoneNo[j] = '\0';

            i++;  // Move past the comma after the phone number
            j = 0;
            while (line[i] != '\0')
            {
                dob[j++] = line[i++];
            }
            dob[j] = '\0';

            //ask to which field want to edit 
            cout << "=====Customer found! What would you like to edit?\n";
            cout << "->1. Username\n-->2. Password\n-->3. Gmail\n-->4. Phone Number\n-->5. Date of Birth\n";
            int choice;
            cin >> choice;
            cin.ignore();

            // user ki choice ki base pr field ki edition
            switch (choice)
            {
            case 1:
                cout << "Enter new Username: ";
                cin.getline(username, usernameSize);
                while (isEmptyString(username) || !validateUsername(username))
                {
                    cout << "Invalid username. It must be between 3 and 20 characters.\n";
                    cout << "Enter new Username: ";
                    cin.getline(username, usernameSize);
                }
                break;
            case 2:
                cout << "Enter new Password: ";
                cin.getline(password, passwordSize);
                while (isEmptyString(password) || !checkPasswordStrength(password))
                {
                    cout << "Invalid password. It must be at least 8 characters, contain an uppercase letter and a number.\n";
                    cout << "Enter new Password: ";
                    cin.getline(password, passwordSize);
                }
                break;
            case 3:
                cout << "Enter new Gmail address: ";
                cin.getline(email, emailSize);
                while (isEmptyString(email) || !validateEmailFormat(email))
                {
                    cout << "Invalid Gmail address. Please enter a valid format (e.g., example@gmail.com).\n";
                    cout << "Enter new Gmail address: ";
                    cin.getline(email, emailSize);
                }
                break;
            case 4:
                cout << "Enter new Phone Number: ";
                cin.getline(phoneNo, phoneSize);
                while (!validatePhoneNumber(phoneNo))
                {
                    cout << "Invalid phone number. It must be 11 digits.\n";
                    cout << "Enter new Phone Number: ";
                    cin.getline(phoneNo, phoneSize);
                }
                break;
            case 5:
                cout << "Enter new Date of Birth (DD-MM-YYYY): ";
                cin.getline(dob, dobSize);
                while (!validateDOB(dob))
                {
                    cout << "Invalid date of birth format. Use DD-MM-YYYY.\n";
                    cout << "Enter new Date of Birth: ";
                    cin.getline(dob, dobSize);
                }
                break;
            default:
                cout << "Invalid option.\n";
                break;
            }

            // write data in a correct format according to customer fields
            fileOut << currentUsername << "," << password << "," << email << "," << phoneNo << "," << dob << endl;
        }
        else
        {
            // go to temporrary file for unchange
            fileOut << line << endl;
        }

        delete[] currentUsername;
    }

    fileIn.close();
    fileOut.close();

    if (found) {
        remove("customer.csv");
        rename("temp.csv", "customer.csv");
        cout << "Customer details updated successfully!\n";
    }
    else {
        cout << "Customer with username " << username << " not found.\n";
        remove("temp.csv");
    }

    // Free memory
    delete[] line;
    delete[] username;
    delete[] password;
    delete[] email;
    delete[] phoneNo;
    delete[] dob;
}





void removeCustomer()
{
    ifstream fileIn("customer.csv");
    ofstream fileOut("temp.csv");

    if (!fileIn.is_open() || !fileOut.is_open())
    {
        cout << "Error: Could not open customer.csv file.\n";
        return;
    }

    char* usernameToRemove = new char[50];
    char* line = new char[300];
    char* username = new char[50];
    bool found = false;

    cin.ignore(); 
    cout << "Enter Customer Username to Remove: ";
    cin.getline(usernameToRemove, 50);

    while (fileIn.getline(line, 300)) {
        int i = 0, j = 0;

        // extract kia username ko manually
        while (line[i] != ',' && line[i] != '\0') {
            username[j++] = line[i++];
        }
        username[j] = '\0';

        // extracted username ko mnaully comare krny ka liay
        bool isSame = true;
        int k = 0;
        while (username[k] != '\0' || usernameToRemove[k] != '\0')
        {
            if (username[k] != usernameToRemove[k])
            {
                isSame = false;
                break;
            }
            k++;
        }

        if (isSame)
        {
            found = true;
            cout << "Customer " << usernameToRemove << " removed successfully!\n";
        }
        else {
            fileOut << line << endl; // temporary file pr unchanged line ko write krny ka liay
        }
    }

    fileIn.close();
    fileOut.close();

    if (found) 
    {
        remove("customer.csv");
        rename("temp.csv", "customer.csv");
    }
    else 
    {
        cout << "Customer not found.\n";
        remove("temp.csv");
    }

    delete[] usernameToRemove;
    delete[] line;
    delete[] username;
}





void Advan_Pro_Management()
{

    const char* productsFile = "products.csv";  
    const char* importedFile = "import_products.csv"; 
    const char* exportedFile = "exported_products.csv";  

    int choice;
    int id;
                    //Menu of Product management
    cout << "\t _____________________________________________________________\n";
    cout << "\t|                                                             |\n";
    cout << "\t|             Advance Product Management                      |\n";
    cout << "\t|_____________________________________________________________|\n";
    cout << "\t|                                                             |\n";
    cout << "\t| 1. Add Product                                              |\n";
    cout << "\t| 2. Update Product                                           |\n";
    cout << "\t| 3. Remove Product                                           |\n";
    cout << "\t| 4. Bulk Import                                              |\n";
    cout << "\t| 5. Bulk Export                                              |\n";
    cout << "\t| 6. Exit                                                     |\n";
    cout << "\t|_____________________________________________________________|\n";

    cout << "\nEnter your choice:";

    cin >> choice;


    if (choice == 1)
    {
        viewallProducts2();
        addProduct1();
    }
    else if (choice == 2)
    {


        viewallProducts2();
        cout << "Enter Product Id: ";
        cin >> id;
        updateProduct1(id);
    }
    else if (choice == 3)
    {

        viewallProducts2();
        cout << "Enter Product Id: ";
        cin >> id;
        removeProduct1(id);
    }
    else if (choice == 4)  
    {
        bulkImport(importedFile, productsFile);  
    }
    else if (choice == 5)  
    {
        bulkExport(productsFile, exportedFile);  
    }
    else if (choice == 6) 
    {
        cout << "Exiting...\n";
        return;  
    }
    else
    {
        cout << "Invalid input Try again." << endl;

        Advan_Pro_Management();

    }



}



void addProduct1()
{
    int productIdSize = 10;
    int productNameSize = 50;
    int categorySize = 30;
    int stockSize = 10;
    int priceSize = 10;
    

    char* productId = new char[productIdSize];
    char* productName = new char[productNameSize];
    char* category = new char[categorySize];
    char* stock = new char[stockSize];
    char* price = new char[priceSize];
 

    cout << "Enter Product ID: ";
    cin.ignore();
    cin.getline(productId, productIdSize);

    cout << "Enter Product Name: ";
    cin.getline(productName, productNameSize);

    cout << "Enter Category: ";
    cin.getline(category, categorySize);

    cout << "Enter Stock Quantity: ";
    cin.getline(stock, stockSize);

    cout << "Enter Price: ";
    cin.getline(price, priceSize);

  

    // append mode mn file ko open kia ha data write krny ka liay
    ofstream fileOut("products.csv", ios::app);
    if (!fileOut.is_open())
    {
        cout << "Error: Could not open products file.\n";
        delete[] productId;
        delete[] productName;
        delete[] category;
        delete[] stock;
        delete[] price;
        return;
    }

    // data ko is trah sy write kia ha ka koi field mn double na aay
    fileOut << productId << ","
        << productName << ","
        << category << ","
        << stock << ","
        << price << ",";

 
 
     

    fileOut.close();

    cout << "Product added successfully!\n";

    // Cleanup
    delete[] productId;
    delete[] productName;
    delete[] category;
    delete[] stock;
    delete[] price;
   
}




void removeProduct1(int productId)
{
    ifstream fileIn("products.csv");
    ofstream fileOut("temp.csv");

    if (!fileIn.is_open() || !fileOut.is_open())
    {
        cout << "Error: Could not open file.\n";
        return;
    }

    char* line = new char[200];
    char* id = new char[10];
    bool found = false;

    while (fileIn.getline(line, 200))
    {
        int i = 0, j = 0;

        // product id ko extract krny ka liay
        while (line[i] != ',' && line[i] != '\0')
        {
            id[j++] = line[i++];
        }
        id[j] = '\0';

        // product id ko match krny ka liay
        int currentId = 0;
        int k = 0;
        while (id[k] != '\0')
        {
            currentId = currentId * 10 + (id[k] - '0');
            k++;
        }

        if (currentId != productId)
        {
            fileOut << line << endl;
        }
        else
        {
            found = true;
        }
    }

    fileIn.close();
    fileOut.close();

    if (found)
    {
        remove("products.csv");
        rename("temp.csv", "products.csv");
        cout << "Product with ID " << productId << " removed successfully.\n";
    }
    else
    {
        cout << "Product with ID " << productId << " not found.\n";
        remove("temp.csv");
    }

    delete[] line;
    delete[] id;
}




void updateProduct1(int productId)
{
    ifstream fileIn("products.csv");
    ofstream fileOut("temp.csv");

    if (!fileIn.is_open() || !fileOut.is_open())
    {
        cout << "Error: Could not open file.\n";
        return;
    }

    char* line = new char[200];
    char* id = new char[10]; 
    bool found = false;

    while (fileIn.getline(line, 200))
    {
        int i = 0, j = 0;

        
        while (line[i] != ',' && line[i] != '\0') {
            id[j++] = line[i++];
        }
        id[j] = '\0';  //string ko null sy terminate krny ka liay

        // product ko inetege mn covert krny ka liay
        int currentId = 0;
        int k = 0;
        while (id[k] != '\0')
        {
            currentId = currentId * 10 + (id[k] - '0');
            k++;
        }

        if (currentId == productId)
        {
            found = true;

            // Dynamically memory allocation
            char* productName = new char[50];
            char* category = new char[30];
            char* stock = new char[10];
            char* price = new char[10];

            

            //prduct ki sequence mn field ctrct krny ka liay jis trah sy data store hota ha 
            i++; 
            j = 0;
            while (line[i] != ',' && line[i] != '\0')
            {
                productName[j++] = line[i++];
            }
            productName[j] = '\0';

            i++; 
            j = 0;
            while (line[i] != ',' && line[i] != '\0')
            {
                category[j++] = line[i++];
            }
            category[j] = '\0';

            i++; 
            j = 0;
            while (line[i] != ',' && line[i] != '\0')
            {
                stock[j++] = line[i++];
            }
            stock[j] = '\0';

            i++; 
            j = 0;
            while (line[i] != '\0')
            {
                price[j++] = line[i++];
            }
            price[j] = '\0';

            // koi specific cheez edit krny ka menu
            cout << "===========Product found! Select an option to edit============\n";
            cout << "-->1. Edit ID\n-->2. Edit Name\n-->3. Edit Category\n-->4. Edit Stock\n-->5. Edit Price\n";
            int choice;
            cin >> choice;
            cin.ignore(); 

            // user ki choice ki base pr menu select krny ka liay
            switch (choice)
            {
            case 1:
                cout << "Enter new ID: ";
                cin.getline(id, 10);
                break;
            case 2:
                cout << "Enter new Name: ";
                cin.getline(productName, 50);
                break;
            case 3:
                cout << "Enter new Category: ";
                cin.getline(category, 30);
                break;
            case 4:
                cout << "Enter new Stock: ";
                cin.getline(stock, 10);
                break;
            case 5:
                cout << "Enter new Price: ";
                cin.getline(price, 10);
                break;
            default:
                cout << "Invalid option.\n";
                break;
            }

            // updated product ko write krny ka liay file pr uski exact place pr

            fileOut << id << "," << productName << "," << category << "," << stock << "," << price << endl;

           
            delete[] productName;
            delete[] category;
            delete[] stock;
            delete[] price;
        }
        else 
        {
            //original line ko temporary line pr paste krny ka liay
            fileOut << line << endl;
        }
    }

    fileIn.close();
    fileOut.close();

    if (found)
    {
        remove("products.csv");  //original file k delete krny ka liay
        rename("temp.csv", "products.csv");  // temp file ko as original file save krny ka liay
        cout << "Product updated successfully.\n";
    }
    else 
    {
        cout << "Product with ID " << productId << " not found.\n";
        remove("temp.csv");  // agr product na mily to temporary file kko delate krny ha
    }

    delete[] line;
    delete[] id;
}




void viewallProducts2()
{
    int lineSize = 150, fieldSize = 30;

    char* line = new char[lineSize];
    char* productID = new char[fieldSize];
    char* name = new char[fieldSize];
    char* category = new char[fieldSize];
    char* stockQty = new char[fieldSize];
    char* price = new char[fieldSize];
    char* promoCode = new char[fieldSize];
    char* promoCodeType = new char[fieldSize];

    ifstream file("products.csv");

    if (!file) {
        cout << "Error: Unable to open the file 'products.csv'.\n";
        delete[] line;
        delete[] productID;
        delete[] name;
        delete[] category;
        delete[] stockQty;
        delete[] price;
        delete[] promoCode;
        delete[] promoCodeType;
        return;
    }

    cout << "-----------------------------------------------------------------------------------------------------------\n";
    cout << "|  Product ID  |  Name            |  Category     | Stock Qty | Price     |  Promo-Code  |  Promo-code-Type|\n";
    cout << "-----------------------------------------------------------------------------------------------------------\n";

    while (file.getline(line, lineSize))
    {
        int i = 0, j = 0;

        // product id ko extract krny ka liay
        j = 0;
        while (line[i] != ',' && line[i] != '\0') {
            productID[j++] = line[i++];
        }
        productID[j] = '\0';
        if (line[i] == ',') i++;

        // product name ko extract krny ka liay
        j = 0;
        while (line[i] != ',' && line[i] != '\0') {
            name[j++] = line[i++];
        }
        name[j] = '\0';
        if (line[i] == ',') i++;

        // category ko extract  krny ka liay
        j = 0;
        while (line[i] != ',' && line[i] != '\0') {
            category[j++] = line[i++];
        }
        category[j] = '\0';
        if (line[i] == ',') i++;

        // stock qunatity ko extract krny ka liay
        j = 0;
        while (line[i] != ',' && line[i] != '\0') {
            stockQty[j++] = line[i++];
        }
        stockQty[j] = '\0';
        if (line[i] == ',') i++;

        // Price ko extract krny ka liay
        j = 0;
        while (line[i] != ',' && line[i] != '\0') {
            price[j++] = line[i++];
        }
        price[j] = '\0';
        if (line[i] == ',') i++;

        // Promocode ko extract krny ka liay
        j = 0;
        while (line[i] != ',' && line[i] != '\0') {
            promoCode[j++] = line[i++];
        }
        promoCode[j] = '\0';
        if (line[i] == ',') i++;

        // Promocode type ko extract krny ka liay
        j = 0;
        while (line[i] != '\0' && line[i] != '\n') {
            promoCodeType[j++] = line[i++];
        }
        promoCodeType[j] = '\0';

        // output ko ik format way mn display krwany ka liay
        cout << "| " << left << setw(12) << productID
            << "| " << left << setw(16) << name
            << "| " << left << setw(14) << category
            << "| " << right << setw(10) << stockQty
            << "| " << right << setw(8) << price
            << "| " << left << setw(12) << (promoCode[0] ? promoCode : "N/A")
            << "| " << left << setw(16) << (promoCodeType[0] ? promoCodeType : "N/A") << "|\n";
    }

    cout << "-----------------------------------------------------------------------------------------------------------\n";

    file.close();

    // Dynamic allocated memmory ko del krny ka liay
    delete[] line;
    delete[] productID;
    delete[] name;
    delete[] category;
    delete[] stockQty;
    delete[] price;
    delete[] promoCode;
    delete[] promoCodeType;
}




void bulkImport(const char* inputFileName, const char* outputFileName) 
{
    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName, ios::app); // file ko append mode mn open kia data enter krny ka liay

    if (!inputFile.is_open() || !outputFile.is_open())
    {
        cout << "Error: Could not open file.\n";
        return;
    }

    cout << "Available products in the import file:\n";
    char** products = nullptr; 
    int productCount = 0;
    int bufferSize = 10; // Initial size for dynamic array

    products = new char* [bufferSize]; 

    char* line = new char[200]; //hrr line sy input read krny  ka liay buffer use kia

    // data ko read krny ka liay import file ka liay
    while (inputFile.getline(line, 200))
    {
        if (line[0] != '\0')//ensure list empty nahi ha
        { 
            //resize krny ka liay agr zrorat ho
            if (productCount == bufferSize) 
            {
                bufferSize *= 2;
                char** temp = new char* [bufferSize];
                for (int i = 0; i < productCount; ++i)
                {
                    temp[i] = products[i];
                }
                delete[] products;
                products = temp;
            }

            // pori product ki line ya information of array mn sotre krwany ka liay

            int lineLength = 0;
            while (line[lineLength] != '\0')
            {
                lineLength++;
            }
            products[productCount] = new char[lineLength + 1];
            for (int i = 0; i < lineLength; ++i) 
            {
                products[productCount][i] = line[i];
            }
            products[productCount][lineLength] = '\0'; // Null-terminate the string
            productCount++;
        }
    }

    // product show krwany ka liay jo avail hain
    for (int i = 0; i < productCount; ++i)
    {
        cout << i + 1 << ". " << products[i] << "\n";
    }

    // admin ko numbers select krwany ka liay
    cout << "Enter the numbers of the products to import (comma-separated, e.g., 1,3,5): ";
    char* selection = new char[200];
    cin.ignore(); 
    cin.getline(selection, 200);

    //puri array ko as a string read krny ka liay
    int selectionIndex = 0;
    char* token = new char[10]; // 10 size ka buffer
    int tokenIndex = 0;

    while (selection[selectionIndex] != '\0')
    {
        if (selection[selectionIndex] == ',' || selection[selectionIndex + 1] == '\0')
 {
            // End of token
            if (selection[selectionIndex + 1] == '\0') {
                token[tokenIndex++] = selection[selectionIndex]; // Add last digit
            }
            token[tokenIndex] = '\0'; // Null-terminate the token

            //token ko manually integer mn convert krny ka liay
            int index = 0;
            for (int i = 0; token[i] != '\0'; i++) 
            {
                index = index * 10 + (token[i] - '0');
            }
            index--;

            
            if (index >= 0 && index < productCount)
            {
                outputFile << products[index] << endl; // jitni bi product select hon ge unko append mode mn file or write krwany ka liay
                cout << "Imported: " << products[index] << "\n";
            }
            else
            {
                cout << "Invalid selection: " << token << "\n";
            }

            tokenIndex = 0; //token ko dobara rest kia
        }
        else
        {
            token[tokenIndex++] = selection[selectionIndex]; //Token koo accumulate krny ka liay
        }
        selectionIndex++;
    }

    cout << "Selected products successfully imported.\n";

    // Clean up dynamically allocated memory
    delete[] selection;
    delete[] token;
    for (int i = 0; i < productCount; ++i) {
        delete[] products[i];
    }
    delete[] products;
    delete[] line;

    inputFile.close();
    outputFile.close();
}






void bulkExport(const char* inputFileName, const char* outputFileName)//bulk export krny ka liay
{
    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName); //overwrie mode mn file ko opn krny ka liay

    if (!inputFile.is_open() || !outputFile.is_open())
    {
        cout << "Error: Could not open file.\n";
        return;
    }

    cout << "Available products in the s:\n";
    char** products = nullptr; 
    int productCount = 0;
    int bufferSize = 10; 

    products = new char* [bufferSize]; //space dalny ka liay

    char* line = new char[200]; 

    //file sy sara catalog dekhanay ka laiy

    while (inputFile.getline(line, 200))
    {
        if (line[0] != '\0') 
        { 
            
            if (productCount == bufferSize) {
                bufferSize *= 2;
                char** temp = new char* [bufferSize];
                for (int i = 0; i < productCount; ++i) {
                    temp[i] = products[i];
                }
                delete[] products;
                products = temp;
            }

            // manually product ko copy krny ka liay
            int lineLength = 0;
            while (line[lineLength] != '\0')
            {
                lineLength++;
            }
            products[productCount] = new char[lineLength + 1];
            for (int i = 0; i < lineLength; ++i) {
                products[productCount][i] = line[i];
            }
            products[productCount][lineLength] = '\0'; // Null-terminate the string
            productCount++;
        }
    }

    
    for (int i = 0; i < productCount; ++i)
    {
        cout << i + 1 << ". " << products[i] << "\n";
    }

    // admin koselect krny ka liay allow krna
    cout << "Enter the numbers of the products to export (comma-separated, e.g., 1,3,5): ";
    char* selection = new char[200];
    cin.ignore(); 
    cin.getline(selection, 200);

    // array input
    int selectionIndex = 0;
    char* token = new char[10]; 
    int tokenIndex = 0;

    while (selection[selectionIndex] != '\0')
    {
        if (selection[selectionIndex] == ',' || selection[selectionIndex + 1] == '\0')
        {
           
            if (selection[selectionIndex + 1] == '\0')
            {
                token[tokenIndex++] = selection[selectionIndex]; //last didgit ko add krny ka liay
            }
            token[tokenIndex] = '\0';

           
            int index = 0;
            for (int i = 0; token[i] != '\0'; i++) 
            {
                index = index * 10 + (token[i] - '0');
            }
            index--; 

            //product ko file mn append mode mn write krny ka liay
            if (index >= 0 && index < productCount)
            {
                outputFile << products[index] << endl; 
                cout << "Exported: " << products[index] << "\n";
            }
            else
            {
                cout << "Invalid selection: " << token << "\n";
            }

            tokenIndex = 0; 
        }
        else {
            token[tokenIndex++] = selection[selectionIndex]; 
        }
        selectionIndex++;
    }

    cout << "Selected products successfully exported.\n";

    // Clean up dynamically allocated memory
    delete[] selection;
    delete[] token;
    for (int i = 0; i < productCount; ++i) {
        delete[] products[i];
    }
    delete[] products;
    delete[] line;

    inputFile.close();
    outputFile.close();
}




void trim2(char* str)
{
    int start = 0, end = 0;

    // pahla nonspace character find krny ka liay
    while (str[start] == ' ' && str[start] != '\0')
    {
        start++;
    }

    // last find krny ka liay
    end = start;
    while (str[end] != '\0')
    {
        end++;
    }
    end--;

    while (end >= start && str[end] == ' ') {
        end--;
    }

    // spaces remove krny ka liay
    int j = 0;
    for (int i = start; i <= end; i++)
    {
        str[j++] = str[i];
    }
    str[j] = '\0';
}





void displaylogs()
{
    ifstream logFile("logs.txt"); // logs file ko open krny ka liay

    if (!logFile.is_open()) 
    {
        cout << "Error: Could not open the logs file.\n";
        return;
    }

    char* lineBuffer = new char[200]; 
    int lineNumber = 1;

    cout << "Logs:\n";
    while (logFile.getline(lineBuffer, 200))
    {
        if (lineBuffer[0] != '\0')
        { 
            cout << lineNumber++ << ". " << lineBuffer << endl;
        }
    }

    delete[] lineBuffer; // Free dynamically allocated memory
    logFile.close();
}






void  Dicount_Promotions(){
    int choice;

    while (true) {
        cout << "\n======= ADMIN PROMO CODE MANAGEMENT =======\n";
        cout << "1. View Promo Codes\n";
        cout << "2. Add Promo Code for Specific Product\n";
        cout << "3. Modify Promo Code for Specific Product\n";
        cout << "4. Remove Promo Code from Product\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            ViewPromoCode();
            break;
        case 2:
            AddPromoCodeForProduct();
            break;
        case 3:
            ModifyPromoCodeForProduct();
            break;
        case 4:
            RemovePromoCodeFromProduct();
            break;
        case 5:
            return; // Exit the menu
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}



void AddPromoCodeForProduct()
{
    char* productID = new char[50];
    cout << "Enter Product ID to Apply Promo Code: ";
    cin >> productID;

    char* promoCode = new char[50];
    cout << "Enter Promo Code: ";
    cin >> promoCode;

    int type;
    cout << "Enter Promo Code Type (1 for Price-based, 2 for Quantity-based): ";
    cin >> type;

    ifstream productFile("products.csv");
    ofstream tempFile("temp.csv");

    if (!productFile.is_open() || !tempFile.is_open()) {
        cout << "ERROR: Could not open product file.\n";
        delete[] productID;
        delete[] promoCode;
        return;
    }

    bool productFound = false;
    char* buffer = new char[200];

    while (productFile.getline(buffer, 200))
    {
        char* existingProductID = new char[50];
        int i = 0, j = 0;

        // product id find krny ka liay
        while (buffer[i] != ',' && buffer[i] != '\0')
        {
            existingProductID[j++] = buffer[i++];
        }
        existingProductID[j] = '\0';

        // product id match krny ka liay
        bool matchFound = true;
        for (int k = 0; productID[k] != '\0' && existingProductID[k] != '\0'; ++k)
        {
            if (productID[k] != existingProductID[k])
            {
                matchFound = false;
                break;
            }
        }

        if (matchFound) {
            productFound = true;
            cout << "Product found. Applying promo code to this product.\n";

            // promocode ko write krny ka liay
            char* modifiedBuffer = new char[300];  
            int bufferLen = 0;

         
            while (buffer[bufferLen] != ',' && buffer[bufferLen] != '\0')
 {
                modifiedBuffer[bufferLen] = buffer[bufferLen];
                bufferLen++;
            }

            modifiedBuffer[bufferLen++] = ','; 

            //copy the remainig line in correct order

            while (buffer[bufferLen] != '\0')
            {
                modifiedBuffer[bufferLen] = buffer[bufferLen];
                bufferLen++;
            }

            // promocode and promotype ko likhna
            modifiedBuffer[bufferLen++] = ','; 
            int promoCodeLen = 0;
            while (promoCode[promoCodeLen] != '\0')
            {
                modifiedBuffer[bufferLen++] = promoCode[promoCodeLen++];
            }

            modifiedBuffer[bufferLen++] = ',';  

            // promocode ki base select krny ka liay price based or qunatity based

            const char* promoType = (type == 1) ? "Price-based" : "Quantity-based";
            int promoTypeLen = 0;
            while (promoType[promoTypeLen] != '\0') 
            {
                modifiedBuffer[bufferLen++] = promoType[promoTypeLen++];
            }

            modifiedBuffer[bufferLen] = '\0';  

         
            tempFile << modifiedBuffer << endl;

            delete[] modifiedBuffer;
        }
        else
        {
            
            tempFile << buffer << endl;
        }

        delete[] existingProductID;
    }

    if (!productFound) 
    {
        cout << "Product with ID " << productID << " not found.\n";
    }

    productFile.close();
    tempFile.close();
    remove("products.csv");
    rename("temp.csv", "products.csv");

    delete[] productID;
    delete[] promoCode;
    delete[] buffer;
}



void ModifyPromoCodeForProduct()
{
    char* productID = new char[50];
    cout << "Enter Product ID to Modify Promo Code: ";
    cin >> productID;

    char* oldPromoCode = new char[50];
    cout << "Enter Current Promo Code: ";
    cin >> oldPromoCode;

    char* newPromoCode = new char[50];
    cout << "Enter New Promo Code: ";
    cin >> newPromoCode;

    ifstream productFile("products.csv");
    ofstream tempFile("temp.csv");

    if (!productFile.is_open() || !tempFile.is_open())
    {
        cout << "ERROR: Could not open product file.\n";
        delete[] productID;
        delete[] oldPromoCode;
        delete[] newPromoCode;
        return;
    }

    bool promoCodeFound = false;
    char* buffer = new char[200];

    while (productFile.getline(buffer, 200))
    {
        char* existingProductID = new char[50];
        int i = 0, j = 0;

        // product id find krny ka liay
        while (buffer[i] != ',' && buffer[i] != '\0')
        {
            existingProductID[j++] = buffer[i++];
        }
        existingProductID[j] = '\0';

        // comparing
        bool productIDMatches = true;
        for (int i = 0; existingProductID[i] != '\0' || productID[i] != '\0'; i++)
        {
            if (existingProductID[i] != productID[i])
            {
                productIDMatches = false;
                break;
            }
        }

        if (productIDMatches)
        {
            // promocode find krny ka liay
            char* promoCodeStart = nullptr;
            for (int i = 0; buffer[i] != '\0'; i++)
            {
                if (buffer[i] == ',') {
                    promoCodeStart = &buffer[i + 1];  
                }
            }

            if (promoCodeStart != nullptr)
            {
                // Compare the old promo code
                bool oldPromoCodeMatches = true;
                int promoCodeLen = 0;
                for (int i = 0; promoCodeStart[i] != '\0' && oldPromoCode[i] != '\0'; i++)
                {
                    if (promoCodeStart[i] != oldPromoCode[i]) {
                        oldPromoCodeMatches = false;
                        break;
                    }
                    promoCodeLen++;
                }

                if (oldPromoCodeMatches)
                {
                    // promocode ko change krny ka liay
                    for (int i = 0; i < promoCodeLen; i++)
                    {
                        promoCodeStart[i] = newPromoCode[i];
                    }
                    promoCodeFound = true;
                }
            }

            // modified or unmodified data ko file pr write krny ka liay
            tempFile << buffer << endl;
        }
        else
        {
            tempFile << buffer << endl;  
        }

        delete[] existingProductID;
    }

    if (!promoCodeFound)
    {
        cout << "Promo code not found for the product.\n";
    }

    productFile.close();
    tempFile.close();
    remove("products.csv");
    rename("temp.csv", "products.csv");

    delete[] productID;
    delete[] oldPromoCode;
    delete[] newPromoCode;
    delete[] buffer;
}




bool isEqual(char* str1, char* str2)
{
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return false;
        }
        i++;
    }
    return (str1[i] == '\0' && str2[i] == '\0');
}


void RemovePromoCodeFromProduct()
{
    char* productID = new char[50];
    cout << "Enter Product ID to Remove Promo Code: ";
    cin >> productID;

    ifstream productFile("products.csv");
    ofstream tempFile("temp.csv");

    if (!productFile.is_open() || !tempFile.is_open()) {
        cout << "ERROR: Could not open product file.\n";
        delete[] productID;
        return;
    }

    bool promoCodeRemoved = false;
    char* buffer = new char[200];

    while (productFile.getline(buffer, 200)) {
        char* existingProductID = new char[50];
        int i = 0, j = 0;

      
        while (buffer[i] != ',' && buffer[i] != '\0') 
        {
            existingProductID[j++] = buffer[i++];
        }
        existingProductID[j] = '\0';

        // product ids ko manually compare krny ka liay
        bool productIDMatches = true;
        for (int i = 0; existingProductID[i] != '\0' || productID[i] != '\0'; i++) {
            if (existingProductID[i] != productID[i]) {
                productIDMatches = false;
                break;
            }
        }

        if (productIDMatches)
        {
            // Find the position of the last comma to identify the promo code
            int lastCommaIndex = -1;
            int commaCount = 0;
            for (int i = 0; buffer[i] != '\0'; i++) {
                if (buffer[i] == ',') {
                    lastCommaIndex = i;
                    commaCount++;
                }
            }

            // promocode check krna 
            if (commaCount >= 5) {
               
                buffer[lastCommaIndex] = '\0'; 
                promoCodeRemoved = true;
            }

          //temp file pr modify data likhny ka liay

            tempFile << buffer << endl;
        }
        else
        {
            
            tempFile << buffer << endl;
        }

        delete[] existingProductID;
    }

    if (promoCodeRemoved) {
        cout << "Promo code removed from product " << productID << ".\n";
    }
    else {
        cout << "No promo code found for product " << productID << ".\n";
    }

    productFile.close();
    tempFile.close();
    remove("products.csv");
    rename("temp.csv", "products.csv");

    delete[] productID;
    delete[] buffer;
}



void ViewPromoCode()
{
    ifstream productFile("products.csv");

    if (!productFile.is_open())
    {
        cout << "ERROR: Could not open product file.\n";
        return;
    }

    char* buffer = new char[200];
    bool promoCodeFound = false;

    // to track proceeds ids
    int maxProducts = 50;
    char** processedProductIDs = new char* [maxProducts];
    int productCount = 0;

    cout << "\n   VIEW PROMO CODES\n";
    cout << "-------------------------------------\n";

    while (productFile.getline(buffer, 200)) {
        char* existingProductID = new char[50];
        int i = 0, j = 0;

        //product id ectrcaction
        while (buffer[i] != ',' && buffer[i] != '\0')
        {
            existingProductID[j++] = buffer[i++];
        }
        existingProductID[j] = '\0';

        //check if id is already ha
        bool alreadyProcessed = false;
        for (int i = 0; i < productCount; ++i) {
            if (isEqual(processedProductIDs[i], existingProductID))
            {
                alreadyProcessed = true;
                break;
            }
        }

       
        if (!alreadyProcessed)
        {
           
            processedProductIDs[productCount++] = existingProductID;

            // Find the Promo Code (last column) in the CSV
            char* promoCodeStart = nullptr;
            char* priceStart = nullptr;
            for (int i = 0; buffer[i] != '\0'; i++) 
            {
                if (buffer[i] == ',') {
                    if (!priceStart) {
                        priceStart = &buffer[i + 1];
                    }
                    promoCodeStart = &buffer[i + 1];  
                }
            }

            // Output the Product ID, Price, and Promo Code
            if (promoCodeStart != nullptr && priceStart != nullptr) 
            {
                cout << "Product ID: " << existingProductID << "\n";
                cout << "Price: " << priceStart << "\n";
                cout << "Promo Code: " << promoCodeStart << "\n";
                cout << "-------------------------------------\n";
                promoCodeFound = true;
            }
        }
        else
        {
            delete[] existingProductID; // Free memory if product is already processed
        }
    }

    if (!promoCodeFound) {
        cout << "No promo codes available.\n";
    }

    // Cleanup
    for (int i = 0; i < productCount; ++i) 
    {
        delete[] processedProductIDs[i]; // Free memory for each Product ID
    }
    delete[] processedProductIDs;
    productFile.close();
    delete[] buffer;
}




void announcement()
{
    int choice;
    char* announcement = new char[200];

    while (true) {
        cout << "1. Add Announcement\n2. View Announcements\n3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); 

        switch (choice) {
        case 1:
            cout << "Enter the announcement: ";
            cin.getline(announcement, 200); // Get input from user into the dynamic array
            addAnnouncement(announcement);
            break;
        case 2:
            viewAnnouncements();
            break;
        case 3:
            cout << "Exiting..." << endl;
            delete[] announcement; 
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    delete[] announcement;
    
}







void addAnnouncement(const char* announcement)
{
    ofstream outFile("announcements.txt", ios::app);
    if (outFile.is_open()) {
        outFile << announcement << endl;
        outFile.close();
        cout << "Announcement added successfully!" << endl;
    }
    else {
        cerr << "Error opening file for writing." << endl;
    }
}



void viewAnnouncements()
{
    ifstream inFile("announcements.txt");
    char line[200]; // har line jo ready krni ha wo array ma store krwany ka liay

    if (inFile.is_open()) {
        cout << "Announcements:" << endl;
        while (inFile.getline(line, 200)) {
            cout << line << endl;
        }
        inFile.close();
    }
    else {
        cerr << "Error opening file for reading." << endl;
    }
}

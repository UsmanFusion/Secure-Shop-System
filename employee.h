#include<iostream>
#include<iomanip>
#include<fstream>
using namespace std;



void viewAllInquiries();
void provideResponse(const char* username);
void markResolved(const char* username);
void addNoteToInquiry(const char* username);
bool doesQueryExist(const char* username);
void deleteQuery(const char* username);
void resizeArray1(char*& arr, int& currentSize, int newSize);


bool employee_login();
void resizeArray_Employee(char*& array, int& currentSize);

void Support_Request_Management();
void Inventory_Management();
void removeProduct(int productId);
void addProduct();
void viewallProducts1();
void updateProduct(int productId);
void trim1(char* str);
void viewLowStockProducts(int threshold);
void updateProductStock(int productId);
void viewAnnouncements1();
void addAnnouncement1(const char* announcement);
void announcement1();



void Product_Availability_and_Low_Stock_Alerts();

void Sales_and_Revenue_Contributions();


void log_employee_impact(const char* employee_name, float sale_amount, const char* assistance_type);
void see_impact_on_sales(const char* employee_name);
bool compare_strings(const char* str1, const char* str2);
float parse_float(const char* arr);
void display_menu();
void handle_menu_choice(int choice);

void Feedback_Response();



void displayAnnouncements()
{
    ifstream inFile("announcements.txt");
    char line[200]; // Array to store each line read from the file

    if (inFile.is_open()) {
        cout << "\n\t---- Announcements ----\n";
        while (inFile.getline(line, 200)) {
            cout <<"\t"<< line << endl;
        }
        inFile.close();
    }
    else {
        cerr << "Error opening file for reading." << endl;
    }
}


void employee() {

    fstream rite;
    rite.open("customer.csv", ios::in);

    if (!rite) {
        rite.open("customer.csv", ios::out);
        if (!rite) {
            cerr << "Error creating file!" << endl;
            exit(1);
        }
        rite << "Username,Password,Email,PhoneNo,DOB\n";
        rite.close();
        cout << "Header written to a new file." << endl;
    }
    else {
        char firstChar;
        rite.get(firstChar);
        if (rite.eof()) {
            rite.close();
            rite.open("customer.csv", ios::out);
            if (!rite) {
                cerr << "Error reopening file for writing!" << endl;
                exit(1);
            }
            rite << "Username,Password,Email,PhoneNo,DOB\n";
            cout << "Header written to an empty file." << endl;
        }
        rite.close();
    }

    int choice = 0, choice1;
    do {
        if (employee_login()) {
                                  

            do {
                cout << "\t _____________________________________________________________\n";
                cout << "\t|                                                             |\n";
                cout << "\t|                 Employee Menu                               |\n";
                cout << "\t|_____________________________________________________________|\n";
                cout << "\t|                                                             |\n";
                cout << "\t| 1. Support Request Management                               |\n";
                cout << "\t| 2. Inventory Management                                     |\n";
                cout << "\t| 3. Product Availability and Low Stock Alerts                |\n";
                cout << "\t| 4. Sales and Revenue Contributions                          |\n";
                cout << "\t| 5. Feedback Response                                        |\n";
                cout << "\t| 6. Anouncements                                             |\n";
                cout << "\t| 7. Exit                                                     |\n";
                cout << "\t|_____________________________________________________________|\n";

                cin >> choice;
                if (cin.fail() || choice < 1 || choice > 7) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input. Please enter a number between 1 and 6.\n";
                    continue;
                }

                switch (choice) {
                case 1:
                    Support_Request_Management();
                    break;
                case 2:
                    Inventory_Management();
                    break;
                case 3:
                    Product_Availability_and_Low_Stock_Alerts();
                    break;
                case 4:
                    Sales_and_Revenue_Contributions();
                    break;
                case 5:
                    Feedback_Response();
                    break;
                case 6:
                    announcement1();
                case 7:
                    cout << "Exiting the program" << endl;
                    return;
                }

                if (choice < 1 || choice > 7) {
                    cout << "Do you want to exit the employee portal?\n";
                    cout << "Press 1 to re-enter or 0 to exit: ";
                    cin >> choice1;

                    if (choice1 == 0) {
                        return;
                    }
                }
            } while (true);
        }
        else {
            cout << "Invalid input" << endl;
        }
    } while (true);
}



void resizeArray_Employee(char*& array, int& currentSize)
{
    int newSize = currentSize * 2;
    char* newArray = new char[newSize];
    for (int i = 0; i < currentSize; i++) {
        newArray[i] = array[i];
    }
    delete[] array;
    array = newArray;
    currentSize = newSize;
}




void log_employee_login(const char* username, bool success)
{
    fstream logFile("logs.txt", ios::out | ios::app);
    if (!logFile) {
        cerr << "Error: Unable to open log file.\n";
        return;
    }

    // Log the result of the employee login attempt
    if (success) {
        logFile << "Employee login successful for username: " << username << endl;
    }
    else {
        logFile << "Employee login failed for username: " << username << endl;
    }

    logFile.close();
}


bool employee_login()
{
    int usernameSize = 20, passwordSize = 20;
    char* username = new char[usernameSize];
    char* password = new char[passwordSize];
    char fileUsername[20], filePassword[20];
    char buffer[100];

    cout << "Enter username: ";
    cin.ignore();
    int i = 0;
    char input;
    while ((input = cin.get()) != '\n') {
        if (i >= usernameSize - 1) resizeArray_Employee(username, usernameSize);
        username[i++] = input;
    }
    username[i] = '\0';

    cout << "Enter password: ";
    i = 0;
    while ((input = cin.get()) != '\n') {
        if (i >= passwordSize - 1) resizeArray_Employee(password, passwordSize);
        password[i++] = input;
    }
    password[i] = '\0';

    ifstream file("employee.csv");

    if (!file) {
        cerr << "Error: Unable to open the file 'employee.csv'.\n";
        delete[] username;
        delete[] password;
        return false;
    }

    bool loginSuccessful = false;
    while (file.getline(buffer, 100)) {
        int i = 0, j = 0;

        // Username extract krny ka liay
        while (buffer[i] != ',' && buffer[i] != '\0') {
            fileUsername[j++] = buffer[i++];
        }
        fileUsername[j] = '\0';
        if (buffer[i] == ',') i++;

        // password extract krny ka liay
        j = 0;
        while (buffer[i] != ',' && buffer[i] != '\0') {
            filePassword[j++] = buffer[i++];
        }
        filePassword[j] = '\0';

        // manually compare krny ka liay
        bool usernameMatch = true;
        for (int k = 0; username[k] != '\0' || fileUsername[k] != '\0'; ++k) {
            if (username[k] != fileUsername[k]) {
                usernameMatch = false;
                break;
            }
        }

        // Manual password comparison
        bool passwordMatch = true;
        for (int k = 0; password[k] != '\0' || filePassword[k] != '\0'; ++k) {
            if (password[k] != filePassword[k]) {
                passwordMatch = false;
                break;
            }
        }

        if (usernameMatch && passwordMatch) {
            loginSuccessful = true;
            break; 
        }
    }

    file.close();

    
    log_employee_login(username, loginSuccessful);

    // Cleanup
    delete[] username;
    delete[] password;

    return loginSuccessful; //login sucessful
}


void Support_Request_Management()
{
    char* username = new char[50];
    int choice;

    while (true) {
        cout << "------------------------------------------" << endl;
        cout << "|              Menu Options              |" << endl;
        cout << "|----------------------------------------|" << endl;
        cout << "| 1. View all inquiries                  |" << endl;
        cout << "| 2. Provide response                    |" << endl;
        cout << "| 3. Mark resolved                       |" << endl;
        cout << "| 4. Add note                            |" << endl;
        cout << "| 5. Exit                                |" << endl;
        cout << "------------------------------------------" << endl;

        cin >> choice;

        if (choice == 1) {
            viewAllInquiries();
        }
        else if (choice == 2) {
            cout << "Enter the username: ";
            cin.ignore();
            cin.getline(username, 50);
            provideResponse(username);
        }
        else if (choice == 3) {
            cout << "Enter the username: ";
            cin.ignore();
            cin.getline(username, 50);
            markResolved(username);
        }
        else if (choice == 4) {
            cout << "Enter the username: ";
            cin.ignore();
            cin.getline(username, 50);
            addNoteToInquiry(username);
        }
        else if (choice == 5) {
            cout << "Exiting Support System.\n";
            break;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    delete[] username;
}




void viewAllInquiries()
{
    ifstream fileIn("support.txt");

    if (!fileIn.is_open()) {
        cout << "Error: Could not open support file.\n";
        return;
    }

    char* line = new char[200];

    cout << "\n---------- All Inquiries ----------\n";
    while (fileIn.getline(line, 200)) {
        cout << line << endl;
    }
   

    fileIn.close();
    delete[] line;
}




void provideResponse(const char* username)
{
    if (!doesQueryExist(username)) {
        cout << "Error: No query found for username " << username << ".\n";
        return;
    }

    cout << "Enter the response: ";
    char* response = new char[200];
    cin.ignore();
    cin.getline(response, 200);

    ofstream fileOut("support.txt", ios::app);

    if (!fileOut.is_open()) {
        cout << "Error: Could not open support file for writing.\n";
        delete[] response;
        return;
    }

    fileOut << "Response for " << username << ": " << response << endl;
    fileOut << "-------------------------------------" << endl;

    fileOut.close();
    cout << "Response added for " << username << ".\n";

    delete[] response;
}


void markResolved(const char* username) {
    if (!doesQueryExist(username)) {
        cout << "Error: No query found for username " << username << ".\n";
        return;
    }

    deleteQuery(username);
    cout << "Query for " << username << " marked as resolved and removed from the system.\n";
}



void addNoteToInquiry(const char* username) {
    if (!doesQueryExist(username)) {
        cout << "Error: No query found for username " << username << ".\n";
        return;
    }

    cout << "Enter the note: ";
    char* note = new char[200];
    cin.ignore();
    cin.getline(note, 200);

    ofstream fileOut("support.txt", ios::app);

    if (!fileOut.is_open()) {
        cout << "Error: Could not open support file for writing.\n";
        delete[] note;
        return;
    }

    fileOut << "Note for " << username << ": " << note << endl;
    fileOut << "-------------------------------------" << endl;

    fileOut.close();
    cout << "Note added for " << username << ".\n";

    delete[] note;
}


bool doesQueryExist(const char* username) {
    ifstream fileIn("support.txt");

    if (!fileIn.is_open()) {
        cout << "Error: Could not open support file.\n";
        return false;
    }

    char* line = new char[200];
    bool found = false;

    while (fileIn.getline(line, 200)) {
        const char* prefix = "Customer Name: ";
        bool isCustomerNameLine = true;

        // line ki starting check krny ka liay
        for (int i = 0; prefix[i] != '\0'; i++) {
            if (line[i] != prefix[i]) {
                isCustomerNameLine = false;
                break;
            }
        }

        if (isCustomerNameLine) {
            // username compare ka liay
            int i = 15; 
            int j = 0;
            bool usernameMatches = true;

            while (username[j] != '\0' && line[i] != '\0') {
                if (username[j] != line[i]) {
                    usernameMatches = false;
                    break;
                }
                i++;
                j++;
            }

            if (usernameMatches && username[j] == '\0' && (line[i] == '\0' || line[i] == '\n')) {
                found = true;
                break;
            }
        }
    }

    fileIn.close();
    delete[] line;

    return found;
}



void deleteQuery(const char* username) {
    ifstream fileIn("support.txt");
    ofstream fileOut("temp.txt");

    if (!fileIn.is_open() || !fileOut.is_open()) {
        cout << "Error: Could not open file.\n";
        return;
    }

    char* line = new char[200];
    bool skipBlock = false;

    while (fileIn.getline(line, 200))
    {
        // agr username match ho jata ha
        bool isCustomerNameLine = true;

        const char* prefix = "Customer Name: ";
        for (int i = 0; prefix[i] != '\0'; i++)
        {
            if (line[i] != prefix[i])
            {
                isCustomerNameLine = false;
                break;
            }
        }

        if (isCustomerNameLine) {
            int i = 15; 
            int j = 0;
            bool usernameMatches = true;

            while (username[j] != '\0' && line[i] != '\0')
            {
                if (username[j] != line[i])
                {
                    usernameMatches = false;
                    break;
                }
                i++;
                j++;
            }

            if (usernameMatches && username[j] == '\0' && (line[i] == '\0' || line[i] == '\n')) {
                skipBlock = true; // block ko skip krny ka liay
            }
        }

        if (!skipBlock) {
            fileOut << line << endl;
        }
        else if (line[0] == '-' && line[1] == '-' && line[2] == '-')
        {
            skipBlock = false; // End of block
        }
    }

    fileIn.close();
    fileOut.close();

    remove("support.txt");
    rename("temp.txt", "support.txt");

    delete[] line;
}



void Inventory_Management()
{
    int choice;
    int id;

    cout << "\t _____________________________________________________________\n";
    cout << "\t|                                                             |\n";
    cout << "\t|             Inventory Management Menu                       |\n";
    cout << "\t|_____________________________________________________________|\n";
    cout << "\t|                                                             |\n";
    cout << "\t| 1. Add Product                                              |\n";
    cout << "\t| 2. Update Product                                           |\n";
    cout << "\t| 3. Remove Product                                           |\n";
    cout << "\t| 4. Exit                                                     |\n";
    cout << "\t|_____________________________________________________________|\n";



    cin >> choice;


    if (choice==1)
    {
        viewallProducts1();
        addProduct();
    }
    else if (choice == 2)
    {


        viewallProducts1();
        cout << "Enter Product Id: ";
        cin >> id;
        updateProduct(id);
    }
    else if (choice == 3)
    {

        viewallProducts1();
        cout << "Enter Product Id: ";
        cin >> id;
        removeProduct(id);
    }
    else if (choice == 4)
    {
        return;
    }
    else
    {
        cout << "Invalid input Try again." << endl;
        Inventory_Management();

    }

}



void resizeArray1(char*& arr, int& currentSize, int newSize)
{
    char* newArray = new char[newSize];
    for (int i = 0; i < currentSize; i++) {
        newArray[i] = arr[i];
    }
    delete[] arr;
    arr = newArray;
    currentSize = newSize;
}


void addProduct() {
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

    // append mode mn data write krny ka liay
    ofstream fileOut("products.csv", ios::app);
    if (!fileOut.is_open()) {
        cout << "Error: Could not open products file.\n";
        delete[] productId;
        delete[] productName;
        delete[] category;
        delete[] stock;
        delete[] price;
        return;
    }

    // ensuring data new line pr write hoa ha
    fileOut << productId << "," << productName << "," << category << "," << stock << "," << price << "\n";

    fileOut.close();

    cout << "Product added successfully!\n";

    // Cleanup
    delete[] productId;
    delete[] productName;
    delete[] category;
    delete[] stock;
    delete[] price;
}


void removeProduct(int productId)
{
    ifstream fileIn("products.csv");
    ofstream fileOut("temp.csv");

    if (!fileIn.is_open() || !fileOut.is_open()) {
        cout << "Error: Could not open file.\n";
        return;
    }

    char* line = new char[200];
    char* id = new char[10];
    bool found = false;

    while (fileIn.getline(line, 200)) {
        int i = 0, j = 0;

        // manually id's extract  krny ka liay
        while (line[i] != ',' && line[i] != '\0')
        {
            id[j++] = line[i++];
        }
        id[j] = '\0';

        // product id ko intege mn convert krny k liay
        int currentId = 0;
        int k = 0;
        while (id[k] != '\0')
        {
            currentId = currentId * 10 + (id[k] - '0');
            k++;
        }

        if (currentId != productId) {
            fileOut << line << endl;
        }
        else {
            found = true;
        }
    }

    fileIn.close();
    fileOut.close();

    if (found) {
        remove("products.csv");
        rename("temp.csv", "products.csv");
        cout << "Product with ID " << productId << " removed successfully.\n";
    }
    else {
        cout << "Product with ID " << productId << " not found.\n";
        remove("temp.csv");
    }

    delete[] line;
    delete[] id;
}


void updateProduct(int productId)
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

    while (fileIn.getline(line, 200)) {
        int i = 0, j = 0;

       
        while (line[i] != ',' && line[i] != '\0')
        {
            id[j++] = line[i++];
        }
        id[j] = '\0';  

        
        int currentId = 0;
        int k = 0;
        while (id[k] != '\0') {
            currentId = currentId * 10 + (id[k] - '0');
            k++;
        }

        if (currentId == productId) {
            found = true;

            //dynmically memeory allocation
            char* productName = new char[50];
            char* category = new char[30];
            char* stock = new char[10];
            char* price = new char[10];

            // Extract other fields (Name, Category, Stock, Price)
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

         
            cout << "Product found! Select an option to edit:\n";
            cout << "1. Edit ID\n2. Edit Name\n3. Edit Category\n4. Edit Stock\n5. Edit Price\n";
            int choice;
            cin >> choice;
            cin.ignore(); 

            //user sy input leny ka liay
            switch (choice) {
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

            // Write updated product to temp file
            fileOut << id << "," << productName << "," << category << "," << stock << "," << price << endl;

            // Free dynamically allocated memory for the fields
            delete[] productName;
            delete[] category;
            delete[] stock;
            delete[] price;
        }
        else 
        {
            // Write the original line to the temp file if the product ID doesn't match
            fileOut << line << endl;
        }
    }

    fileIn.close();
    fileOut.close();

    if (found)
    {
        remove("products.csv");  // Delete the original file
        rename("temp.csv", "products.csv");  // Rename temp file to products.csv
        cout << "Product updated successfully.\n";
    }
    else
    {
        cout << "Product with ID " << productId << " not found.\n";
        remove("temp.csv"); //agr product nahi milti then temporray file removeed
    }

    delete[] line;
    delete[] id;
}



void viewallProducts1()
{
    int lineSize = 150, fieldSize = 30;

    char* line = new char[lineSize];
    char* productID = new char[fieldSize];
    char* name = new char[fieldSize];
    char* category = new char[fieldSize];
    char* stockQty = new char[fieldSize];
    char* price = new char[fieldSize];

    ifstream file("products.csv");

    if (!file)
    {
        cout << "Error: Unable to open the file 'products.csv'.\n";
        delete[] line;
        delete[] productID;
        delete[] name;
        delete[] category;
        delete[] stockQty;
        delete[] price;
        return;
    }

    cout << "--------------------------------------------------------------------------\n";
    cout << "|  Product ID  |  Name            |  Category     | Stock Qty | Price     |\n";
    cout << "--------------------------------------------------------------------------\n";

    while (file.getline(line, lineSize))
    {
        int i = 0, j = 0;

        
        j = 0;
        while (line[i] != ',' && line[i] != '\0')
        {
            if (j >= fieldSize - 1) resizeArray(productID, fieldSize);
            productID[j++] = line[i++];
        }
        productID[j] = '\0';
        trim1(productID); 
        if (line[i] == ',') i++;

    
        j = 0;
        while (line[i] != ',' && line[i] != '\0')
        {
            if (j >= fieldSize - 1) resizeArray(name, fieldSize);
            name[j++] = line[i++];
        }
        name[j] = '\0';
        trim1(name);
        if (line[i] == ',') i++;

       
        j = 0;
        while (line[i] != ',' && line[i] != '\0')
        {
            if (j >= fieldSize - 1) resizeArray(category, fieldSize);
            category[j++] = line[i++];
        }
        category[j] = '\0';
        trim1(category); 
        if (line[i] == ',') i++;

        
        j = 0;
        while (line[i] != ',' && line[i] != '\0')
        {
            if (j >= fieldSize - 1) resizeArray(stockQty, fieldSize);
            stockQty[j++] = line[i++];
        }
        stockQty[j] = '\0';
        trim1(stockQty); 
        if (line[i] == ',') i++;

      
        j = 0;
        while (line[i] != '\0' && line[i] != '\n')
        {
            if (j >= fieldSize - 1) resizeArray(price, fieldSize);
            price[j++] = line[i++];
        }
        price[j] = '\0';
        trim1(price); 

        // DATA ko formatted way mn display krwany ka liay
        cout << "| " << left << setw(12) << productID
            << "| " << left << setw(16) << name
            << "| " << left << setw(14) << category
            << "| " << right << setw(10) << stockQty
            << "| " << right << setw(8) << price
            << " |\n";
    }

    cout << "--------------------------------------------------------------------------\n";

    file.close();

    // Free dynamically allocated memory
    delete[] line;
    delete[] productID;
    delete[] name;
    delete[] category;
    delete[] stockQty;
    delete[] price;
}





void trim1(char* str) 
{
    int start = 0, end = 0;

    
    while (str[start] == ' ' && str[start] != '\0') 
    {
        start++;
    }

   
    end = start;
    while (str[end] != '\0')
    {
        end++;
    }
    end--;

    while (end >= start && str[end] == ' ')
    {
        end--;
    }

   
    int j = 0;
    for (int i = start; i <= end; i++)
    {
        str[j++] = str[i];
    }
    str[j] = '\0';
}




void Product_Availability_and_Low_Stock_Alerts()
{
    int choice, id,threshold;

    cout << "\t _____________________________________________________________\n";
    cout << "\t|                                                             |\n";
    cout << "\t|         Low stock Alert and Update Stock                    |\n";
    cout << "\t|_____________________________________________________________|\n";
    cout << "\t|                                                             |\n";
    cout << "\t| 1. View Low stock Product                                   |\n";
    cout << "\t| 2. Update Stock                                             |\n";
    cout << "\t|_____________________________________________________________|\n";

    cin >> choice;

    if (choice == 1)
    {
        cout << "Enter threshold: ";
        cin >> threshold;
        viewLowStockProducts(threshold);



    }

    else if (choice == 2)

    {
        viewallProducts1();
        cout << "Enter the product Id: ";
        cin >> id;
        updateProductStock(id);

    }
    else
    {
        cout << "Invalid Choice. Try again" << endl;
        employee();

    }





}




void viewLowStockProducts(int threshold)
{
    ifstream file("products.csv");

    if (!file.is_open()) {
        cout << "Error: Could not open file.\n";
        return;
    }

    char* line = new char[200];
    char* stock = new char[10];

    cout << "Products with low stock (below threshold " << threshold << "):\n";

    while (file.getline(line, 200)) {
        int i = 0;

        // Skip product ID
        while (line[i] != ',') i++;
        i++;

        // Skip product Name
        while (line[i] != ',') i++;
        i++;

        // Skip Category
        while (line[i] != ',') i++;
        i++;

        // Extract stock value
        int j = 0;
        while (line[i] != ',' && line[i] != '\0')
        {
            stock[j++] = line[i++];
        }
        stock[j] = '\0'; 

        // Convert stock to integer
        int productStock = 0;
        for (int k = 0; stock[k] != '\0'; k++)
        {
            productStock = productStock * 10 + (stock[k] - '0');
        }

        if (productStock < threshold) {
            cout << "Product with low stock:\n";
            cout << "ID: " << line << endl;
            cout << "Stock: " << productStock << endl;
        }
    }

    delete[] line;
    delete[] stock;
    file.close();
}





void updateProductStock(int productId) 
{
    ifstream fileIn("products.csv");
    ofstream fileOut("temp.csv");

    if (!fileIn.is_open() || !fileOut.is_open()) {
        cout << "Error: Could not open file.\n";
        return;
    }

    char* line = new char[200];
    char* id = new char[10];
    bool found = false;

    while (fileIn.getline(line, 200)) {
        int i = 0, j = 0;

        // Extract product ID
        while (line[i] != ',' && line[i] != '\0') {
            id[j++] = line[i++];
        }
        id[j] = '\0';  

        // Convert productId to integer manually
        int currentId = 0;
        int k = 0;
        while (id[k] != '\0') {
            currentId = currentId * 10 + (id[k] - '0');
            k++;
        }

        // If this is the product we are updating, ask for details
        if (currentId == productId)
        {
            found = true;

            char* productName = new char[50];
            char* category = new char[30];
            char* stock = new char[10];
            char* price = new char[10];

            //comma include kr ka reading 
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

            // user sy new stock ki info leny ka liay
            cout << "Product found! Enter new stock quantity:\n";
            cout << "Current stock: " << stock << endl;
            cout << "Enter new stock: ";
            cin.ignore();
            cin.getline(stock, 10);

            // updated line ko write krny ka liay
            fileOut << id << "," << productName << "," << category << "," << stock << "," << price << endl;

            // Clean up dynamically allocated memory
            delete[] productName;
            delete[] category;
            delete[] price;
        }
        else 
        {
            // Copy the original line to the temp file if it's not the product we're updating
            fileOut << line << endl;
        }
    }

    fileIn.close();
    fileOut.close();

    if (found) {
        remove("products.csv");
        rename("temp.csv", "products.csv");
        cout << "Product stock updated successfully.\n";
    }
    else {
        cout << "Product with ID " << productId << " not found.\n";
        remove("temp.csv");
    }

    delete[] line;
    delete[] id;
}




int compareStrings(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return 0;  
        }
        i++;
    }
    return str1[i] == str2[i];  
}


bool containsSubstring(const char* str, const char* substr) {
    int lenStr = strlen(str);
    int lenSubstr = strlen(substr);

    for (int i = 0; i <= lenStr - lenSubstr; i++) {
        bool match = true;
        for (int j = 0; j < lenSubstr; j++) {
            if (str[i + j] != substr[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            return true;
        }
    }
    return false;
}



void searchFeedbackByUsername(const char* username)
{
    ifstream feedbackFile("feedback.txt");
    if (!feedbackFile.is_open()) {
        cout << "ERROR: Unable to open feedback file.\n";
        return;
    }

    char line[200];
    bool found = false;

    while (feedbackFile.getline(line, 200))
    {
        if (containsSubstring(line, username)) 
        {  
            found = true;
            cout << line << endl;  
        }
    }
    feedbackFile.close();

    if (!found) {
        cout << "No feedback found for the username: " << username << endl;
    }
}




void respondToFeedback() {
    char username[50];
    cout << "Enter the Username to search feedback: ";
    cin >> username;

    cout << "Searching feedback for username: " << username << "\n";

    // Search and show the feedback for the given username
    ifstream feedbackFile("feedback.txt");
    bool feedbackFound = false;
    char line[200];

    while (feedbackFile.getline(line, 200)) {
        if (containsSubstring(line, username)) { // Use the custom helper function
            feedbackFound = true;
            cout << "Customer Feedback: " << endl; // Show the feedback entry
            cout << line << endl;
        }
    }
    feedbackFile.close();

    if (!feedbackFound) {
        cout << "No feedback found for the username: " << username << ". No response will be recorded.\n";
        return;
    }

    // If feedback is found, prompt the employee for a response
    char response[500];
    cout << "Enter your response to the feedback: ";
    cin.ignore();
    cin.getline(response, 500);

    ofstream responseFile("responses.txt", ios::app);
    if (!responseFile.is_open()) {
        cout << "ERROR: Unable to open responses file.\n";
        return;
    }

    // Log the employee's response to the feedback
    responseFile << "Response to feedback for Username: " << username << "\n";
    responseFile << "Employee Response: " << response << "\n";
    responseFile << "--------------------------------------------------\n";

    responseFile.close();

    cout << "Your response has been logged. Thank you for your attention!\n";
}

void Feedback_Response()
{

    respondToFeedback();

}










void display_menu() {
    cout << "\n********** Menu **********" << endl;
    cout << "1. Log Employee Sales Impact" << endl;
    cout << "2. View Employee Sales Impact" << endl;
    cout << "3. Exit" << endl;
    cout << "****************************" << endl;
}


void handle_menu_choice(int choice) {
    if (choice == 1) {
        char employee_name[100];
        float sale_amount;
        char assistance_type[100];

        cout << "Enter employee name: ";
        cin.ignore(); 
        cin.getline(employee_name, 100);

        cout << "Enter sale amount: ";
        cin >> sale_amount;

        cout << "Enter assistance type: ";
        cin.ignore(); 
        cin.getline(assistance_type, 100);

        log_employee_impact(employee_name, sale_amount, assistance_type);
    }
    else if (choice == 2) {
        char employee_name[100];
        cout << "Enter employee name to see impact on sales: ";
        cin.ignore();  
        cin.getline(employee_name, 100);

        see_impact_on_sales(employee_name);
    }
    else if (choice == 3) {
        cout << "Exiting program..." << endl;
        employee();
    }
    else {
        cout << "Invalid choice. Please try again." << endl;
    }
}


bool compare_strings(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return false;
        }
        i++;
    }
    return str1[i] == str2[i];
}


void log_employee_impact(const char* employee_name, float sale_amount, const char* assistance_type)
{
    ofstream fs("SalesReport.txt", ios::app);  // Open file in append mode
    if (!fs) {
        cout << "Unable to open SalesReport" << endl;
        return;
    }

    // Directly write employee name, assistance type, and sale amount to the file
    fs << employee_name << "," << assistance_type << "," << fixed << setprecision(2) << sale_amount << endl;

    fs.close();
    cout << "Sales impact logged successfully." << endl;
}


float parse_float(const char* arr)
{
    float result = 0;
    int i = 0;
    bool is_negative = false;

    if (arr[0] == '-') {
        is_negative = true;
        i = 1;
    }

    while (arr[i] != '.' && arr[i] != '\0') {
        result = result * 10 + (arr[i] - '0');
        i++;
    }

    if (arr[i] == '.') {
        i++;
        float decimal_place = 0.1;
        while (arr[i] != '\0') {
            result += (arr[i] - '0') * decimal_place;
            decimal_place /= 10;
            i++;
        }
    }

    if (is_negative) {
        result = -result;
    }

    return result;
}


void see_impact_on_sales(const char* employee_name)
{
    ifstream fs("SalesReport.txt");  // Open the sales report file
    if (!fs) {
        cout << "No record find!" << endl;
        return;
    }

    char stored_name[100];
    char assistance_type[100];
    char sale_amount_str[20];
    bool found = false;
    float total_sales = 0.0f;

    while (fs.getline(stored_name, 100, ',') &&
        fs.getline(assistance_type, 100, ',') &&
        fs.getline(sale_amount_str, 20)) {
        // Compare employee name in record with the input name
        if (compare_strings(stored_name, employee_name))
        {
            // Parse sale amount and display it
            float sale_amount = parse_float(sale_amount_str);
            cout << "Assistance Type: " << assistance_type << ", Sale Amount: $" << sale_amount << endl;
            total_sales += sale_amount;
            found = true;
        }
    }

    // Show total sales impact if found
    if (found) {
        cout << "Total Sales Impact by " << employee_name << ": $" << fixed << setprecision(2) << total_sales << endl;
    }
    else {
        cout << "No sales impact found for employee: " << employee_name << endl;
    }

    fs.close();
}


void Sales_and_Revenue_Contributions()
{
    int choice;

    while (true)
    {
        display_menu();  // Display the menu
        cout << "Enter your choice: ";
        cin >> choice;

        handle_menu_choice(choice);  // Handle the menu choice
    }
    
}


void announcement1()
{
    int choice;
    char* announcement = new char[200];

    while (true) {
        cout << "-->1. Add Announcement\n-->2. View Announcements\n3. Exit\n";
        cout << "==Enter your choice: ";
        cin >> choice;
        cin.ignore(); 

        switch (choice) {
        case 1:
            cout << "Enter the announcement: ";
            cin.getline(announcement, 200); // Get input from user into the dynamic array
            addAnnouncement1(announcement);
            break;
        case 2:
            viewAnnouncements1();
            break;
        case 3:
            cout << "Exiting..." << endl;
            delete[] announcement; // Free the dynamically allocated memory
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    delete[] announcement;

}







void addAnnouncement1(const char* announcement)
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



void viewAnnouncements1()
{
    ifstream inFile("announcements.txt");
    char line[200]; // Array to store each line read from the file

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
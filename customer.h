#include<iostream>
#include<iomanip>
#include<fstream>
using namespace std;


void resizeArray_Customer(char*& array, int& currentSize);
bool isStringEmpty(const char* str);
bool isStrongPassword(const char* password);
bool isValidEmail(const char* email);
bool isValidPhoneNumber(const char* phoneNo);
bool isValidDOB(const char* dob);
void trim(char* str);
void display_cart();
void clearcart();

bool customer_login();
void viewallProducts();
void manualSearch();
void removeitems();
void addToCart();
bool isProductInCart(const char* productID);
void increaseProductQuantity(const char* productID);
void Product_Browsing_and_Search();
bool doesUserExist(const char* username);
bool compareStrings1(const char* str1, const char* str2);
void concatenateChars(char* dest, const char* src);
void copyChars(char* dest, const char* src);
bool search(int itemId);
void addwish(const char* username, int itemId);
void removeWish(const char* username, int itemId);
void updateWish(const char* username, int itemId, int newItemId);
void DisplayWishlist(const char* username);
void handlePromoCode();
void confirmPurchase();

void checkout();
void resizeArray(char**& arr, int& currentSize, int newSize);
void submitSupportRequest(char**& names, char**& emails, char**& inquiries, char**& descriptions, int& count, int& capacity);







void handlePromoCode();
void parseCartDetails(const char* cartLine, char* productID, char* productName, char* productCategory, char* quantityStr, char* priceStr);
void applyPromoCode(const char* promoCode, float& totalAmount);
void saveOrderSummary(const char* username, float totalAmount);
int stringToInt(const char* str);
bool isEqual2(const char* str1, const char* str2);




void Cart_Management();
void PurchaseAndCheckout();
void wishlist();
void Order_History_and_Feedback();
void Support_Requests();






void customer() {
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
    }
    else {
        char firstChar;
        rite.get(firstChar);
        if (rite.eof()) {
            rite.close();
            rite.open("customer.csv", ios::out);
            if (!rite) {
                cerr << "Error reopening file for writing!" << endl;
                return;
            }
            rite << "Username,Password,Email,PhoneNo,DOB\n";
        }
        rite.close();
    }

    int choice2;
    do {
        cout << "\t _____________________________________________\n";
        cout << "\t|                                             |\n";
        cout << "\t| 1. Login                                    |\n";
        cout << "\t| 2. Register                                 |\n";
        cout << "\t|_____________________________________________|\n";
        cout << "Enter your choice: ";
        cin >> choice2;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');  // Ignore invalid input
            cout << "Invalid input! Please enter a valid integer.\n";
            continue;
        }

        if (choice2 == 1) {
            int choice = 0, choice1;

            do {
                if (customer_login()) {
                    do {
                                      displayAnnouncements();//to display announcements
                        cout << "------------------------------------------" << endl;
                        cout << "|              Menu Options              |" << endl;
                        cout << "|----------------------------------------|" << endl;
                        cout << "| 1. Product Browsing and Search         |" << endl;
                        cout << "| 2. Cart Management                     |" << endl;
                        cout << "| 3. Purchase and Checkout               |" << endl;
                        cout << "| 4. Wishlist                            |" << endl;
                        cout << "| 5. Order History and Feedback          |" << endl;
                        cout << "| 6. Support Requests                    |" << endl;
                        cout << "| 7. Exit                                |" << endl;
                        cout << "------------------------------------------" << endl;

                        cout << "\nEnter your choice: ";
                        cin >> choice;

                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(10000, '\n');  // Ignore invalid input
                            cout << "Invalid input! Please enter a valid integer.\n";
                            continue;
                        }

                        switch (choice) {
                        case 1:
                            Product_Browsing_and_Search();
                            break;
                        case 2:
                            Cart_Management();
                            break;
                        case 3:
                            PurchaseAndCheckout();
                            break;
                        case 4:
                            wishlist();
                            break;
                        case 5:
                            Order_History_and_Feedback();
                            break;
                        case 6:
                            Support_Requests();
                            break;
                        case 7:
                            customer();


                        default:
                            cout << "Invalid input!" << endl;
                            cout << "Do you want to exit the customer portal?" << endl;
                            cout << "Press 1 to re-enter or 0 to exit: ";
                            cin >> choice1;

                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(10000, '\n');
                                cout << "Invalid input! Exiting portal.\n";
                                return;
                            }

                            if (choice1 == 0) {
                                return;
                            }
                        }
                    } while (true);
                }
            } while (choice == 0);
        }
        else if (choice2 == 2) {
            fstream customer;

            int usernameSize = 20, passwordSize = 20, emailSize = 20, phoneSize = 12, dobSize = 15;
            char* username = new char[usernameSize];
            char* password = new char[passwordSize];
            char* email = new char[emailSize];
            char* phoneNo = new char[phoneSize];
            char* dob = new char[dobSize];

            char input;
            int length = 0;

            customer.open("customer.csv", ios::out | ios::app);
            if (!customer) {
                cerr << "Error opening file!" << endl;
                return;
            }

            // Valid Username Input
            do {
                cout << "Enter Username: ";
                cin.ignore();
                length = 0;
                while ((input = cin.get()) != '\n') {
                    if (length >= usernameSize - 1) resizeArray(username, usernameSize);
                    username[length++] = input;
                }
                username[length] = '\0';
                if (isStringEmpty(username)) {
                    cout << "Username cannot be empty. Please try again.\n";
                }
                else {
                    break;
                }
            } while (true);

            // Valid Password Input
            do {
                cout << "Enter Password: ";
                length = 0;
                while ((input = cin.get()) != '\n') {
                    if (length >= passwordSize - 1) resizeArray(password, passwordSize);
                    password[length++] = input;
                }
                password[length] = '\0';
                if (isStringEmpty(password)) {
                    cout << "Password cannot be empty. Please try again.\n";
                }
                else if (!isStrongPassword(password)) {
                    cout << "Password is not strong enough. Please try again.\n";
                }
                else {
                    break;
                }
            } while (true);

            // Valid Email Input
            do {
                cout << "Enter Email: ";
                length = 0;
                while ((input = cin.get()) != '\n') {
                    if (length >= emailSize - 1) resizeArray(email, emailSize);
                    email[length++] = input;
                }
                email[length] = '\0';
                if (!isValidEmail(email)) {
                    cout << "Invalid email format. Please try again.\n";
                }
                else {
                    break;
                }
            } while (true);

            // Valid Phone Number Input
            do {
                cout << "Enter Phone No: ";
                length = 0;
                while ((input = cin.get()) != '\n') {
                    if (length >= phoneSize - 1) resizeArray(phoneNo, phoneSize);
                    phoneNo[length++] = input;
                }
                phoneNo[length] = '\0';
                if (!isValidPhoneNumber(phoneNo)) {
                    cout << "Invalid phone number. Please try again.\n";
                }
                else {
                    break;
                }
            } while (true);

            // Valid DOB Input
            do {
                cout << "Enter Date of Birth (DD-MM-YYYY): ";
                length = 0;
                while ((input = cin.get()) != '\n') {
                    if (length >= dobSize - 1) resizeArray(dob, dobSize);
                    dob[length++] = input;
                }
                dob[length] = '\0';
                if (!isValidDOB(dob)) {
                    cout << "Invalid DOB format. Please try again.\n";
                }
                else {
                    break;
                }
            } while (true);

            // Write to file
            customer << username << "," << password << "," << email << "," << phoneNo << "," << dob << endl;
            cout << "\n----Congratulations! You have been registered successfully!\n";

            // Free allocated memory
            delete[] username;
            delete[] password;
            delete[] email;
            delete[] phoneNo;
            delete[] dob;

            customer.close();
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice2 == 1 || choice2 == 2);
}






void resizeArray_Customer(char*& array, int& currentSize)
{
    int newSize = currentSize * 2;
    char* newArray = new char[newSize];
    for (int i = 0; i < currentSize; i++)
    {
        newArray[i] = array[i];
    }
    delete[] array;
    array = newArray;
    currentSize = newSize;
}





void resizeCustomer(char**& productNames, double*& prices, int*& quantities, int& capacity)
{
    int newCapacity = capacity * 2; 
    // products name ko resize krny ka liay agr user input br jay to 
    char** newProductNames = new char* [newCapacity];
    for (int i = 0; i < capacity; i++) 
    {
        newProductNames[i] = productNames[i];
    }
    delete[] productNames;
    productNames = newProductNames;

    // same resize
    double* newPrices = new double[newCapacity];
    for (int i = 0; i < capacity; i++) {
        newPrices[i] = prices[i];
    }
    delete[] prices;
    prices = newPrices;

    // same resizing)
    int* newQuantities = new int[newCapacity];
    for (int i = 0; i < capacity; i++) {
        newQuantities[i] = quantities[i];
    }
    delete[] quantities;
    quantities = newQuantities;

    // capacty ko update krny ka liay
    capacity = newCapacity;
}






 
void clear_input_buffer()
{
    char temp[100];
    cin.getline(temp, sizeof(temp));
}




void log_customer_login(const char* username, bool success)
{
    // logs.txt ko append mode mn open kia taka logs add hoty jainn
    fstream logFile("logs.txt", ios::out | ios::app);
    if (!logFile) {
        cerr << "Error: Unable to open log file.\n";
        return;
    }

    // Log the result of the login attempt
    if (success) {
        logFile << "Customer login successful for username: " << username << endl;
    }
    else {
        logFile << "Customer login failed for username: " << username << endl;
    }

    logFile.close();
}






bool customer_login()
{
    int nameSize = 20, passwordSize = 20, fileNameSize = 20, filePasswordSize = 20;
    int bufferSize = 100;

    char* name = new char[nameSize];
    char* password = new char[passwordSize];
    char* file_name = new char[fileNameSize];
    char* file_password = new char[filePasswordSize];
    char* buffer = new char[bufferSize];

    while (true)
    {
        // previous input ko clear krny ka liay
        for (int i = 0; i < nameSize; i++) name[i] = '\0';
        for (int i = 0; i < passwordSize; i++) password[i] = '\0';

        cout << "Enter customer username: ";
        cin.ignore();
        cin.getline(name, nameSize);

        cout << "Enter customer password: ";
        cin.getline(password, passwordSize);

        ifstream file("customer.csv");
        if (!file) {
            cerr << "Error: Unable to open the file 'customer.csv'.\n";
            delete[] name;
            delete[] password;
            delete[] file_name;
            delete[] file_password;
            delete[] buffer;
            return false;
        }

        bool loginSuccessful = false;
        file.getline(buffer, bufferSize); //headerfile ko skip krny ka liay



        //manaualy extraction krny ka liay har loop har field ko extract krta ha
        while (file.getline(buffer, bufferSize))
        {
          
            for (int i = 0; i < fileNameSize; i++) file_name[i] = '\0';
            for (int i = 0; i < filePasswordSize; i++) file_password[i] = '\0';

            int i = 0, j = 0;

            // Extract username
            while (buffer[i] != ',' && buffer[i] != '\0')
            {
                file_name[j++] = buffer[i++];
                if (j >= fileNameSize - 1) resizeArray_Customer(file_name, fileNameSize);
            }
            file_name[j] = '\0';

            if (buffer[i] == ',') i++;

            // Extract password
            j = 0;
            while (buffer[i] != ',' && buffer[i] != '\0')
            {
                file_password[j++] = buffer[i++];
                if (j >= filePasswordSize - 1) resizeArray_Customer(file_password, filePasswordSize);
            }
            file_password[j] = '\0';

            // Manual username comparison
            bool name_match = true;
            for (int k = 0; ; k++) 
            {
                if (name[k] == '\0' && file_name[k] == '\0') break;
                if (name[k] != file_name[k]) {
                    name_match = false;
                    break;
                }
                if (name[k] == '\0' || file_name[k] == '\0')
                {
                    name_match = false;
                    break;
                }
            }

            // Manual password comparison
            bool password_match = true;
            for (int k = 0; ; k++) 
            {
                if (password[k] == '\0' && file_password[k] == '\0') break;
                if (password[k] != file_password[k]) {
                    password_match = false;
                    break;
                }
                if (password[k] == '\0' || file_password[k] == '\0') {
                    password_match = false;
                    break;
                }
            }

            // If both match, login successful
            if (name_match && password_match)
            {
                loginSuccessful = true;
                break;
            }
        }

        file.close();

        // Log the customer login attempt (success or failure)
        log_customer_login(name, loginSuccessful);

        // Output result based on login attempt
        if (loginSuccessful)
        {
            cout << "Login successful!\n";
            delete[] name;
            delete[] password;
            delete[] file_name;
            delete[] file_password;
            delete[] buffer;
            return true;
        }
        else {
            cout << "Wrong credentials. Please try again.\n";
        }
    }

    // Cleanup in case the function exits unexpectedly
    delete[] name;
    delete[] password;
    delete[] file_name;
    delete[] file_password;
    delete[] buffer;
    return false;
}










bool isStringEmpty(const char* str)
{
    return str[0] == '\0';
}




bool isStrongPassword(const char* password)
{
    int length = 0;
    bool hasUpper = false, hasDigit = false;
    for (int i = 0; password[i] != '\0'; i++)
    {
        length++;
        if (password[i] >= 'A' && password[i] <= 'Z') hasUpper = true;
        if (password[i] >= '0' && password[i] <= '9') hasDigit = true;
    }
    return length >= 8 && hasUpper && hasDigit;
}






bool isValidEmail(const char* email)
{
    for (int i = 0; email[i] != '\0'; i++)
    {
        if (email[i] == '@') return true;
    }
    return false;
}




bool isValidPhoneNumber(const char* phoneNo)
{
    int length = 0;
    for (int i = 0; phoneNo[i] != '\0'; i++)
    {
        if (phoneNo[i] < '0' || phoneNo[i] > '9') return false;
        length++;
    }
    return length == 11;
}





bool isValidDOB(const char* dob)
{
    int length = 0, dashCount = 0;
    for (int i = 0; dob[i] != '\0'; i++)
    {
        if (dob[i] == '-') dashCount++;
        length++;
    }
    return length == 10 && dashCount == 2;
}




void trim(char* str)//manually spaces ko delete krny ka taka file reading mn easy ho sky
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

    //spaces remove krny ka liay string ko shift kia
    int j = 0;
    for (int i = start; i <= end; i++)
    {
        str[j++] = str[i];
    }
    str[j] = '\0';
}




void Product_Browsing_and_Search()
{
    int choice;

    do
    {
        cout << "------------------------------------------" << endl;
        cout << "|     Product Browsing and Search        |" << endl;
        cout << "|----------------------------------------|" << endl;
        cout << "| 1. View All Products                   |" << endl;
        cout << "| 2. Manual Search                       |" << endl;
        cout << "| 3. Exit                                |" << endl;
        cout << "------------------------------------------" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            viewallProducts();
            break;
        }
        case 2:
        {
            manualSearch();
        }
        case 3:
        {
            return;
        }
        default:
        {
            cout << "Invalid choice. Please try again.\n";
        }
        }


    } while (choice != 3);

}




void viewallProducts()
{
    int lineSize = 200, fieldSize = 30;

    char* line = new char[lineSize];
    char* productID = new char[fieldSize];
    char* name = new char[fieldSize];
    char* category = new char[fieldSize];
    char* stockQty = new char[fieldSize];
    char* price = new char[fieldSize];
    char* promocode = new char[fieldSize];
    char* promocodeType = new char[fieldSize];

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
        delete[] promocode;
        delete[] promocodeType;
        return;
    }

    cout << "--------------------------------------------------------------------------------------------------------\n";
    cout << "|  Product ID  |  Name            |  Category     | Stock Qty | Price     | Promo Code      | Promo Type |\n";
    cout << "--------------------------------------------------------------------------------------------------------\n";

    while (file.getline(line, lineSize)) {
        int i = 0, j = 0;

        // Parse Product ID
        j = 0;
        while (line[i] != ',' && line[i] != '\0') {
            if (j >= fieldSize - 1) resizeArray(productID, fieldSize);
            productID[j++] = line[i++];
        }
        productID[j] = '\0';
        trim(productID);
        if (line[i] == ',') i++;

        // Parse Name
        j = 0;
        while (line[i] != ',' && line[i] != '\0')
        {
            if (j >= fieldSize - 1) resizeArray(name, fieldSize);
            name[j++] = line[i++];
        }
        name[j] = '\0';
        trim(name);
        if (line[i] == ',') i++;

        // Parse Category
        j = 0;
        while (line[i] != ',' && line[i] != '\0')
        {
            if (j >= fieldSize - 1) resizeArray(category, fieldSize);
            category[j++] = line[i++];
        }
        category[j] = '\0';
        trim(category);
        if (line[i] == ',') i++;

        // Parse Stock Quantity
        j = 0;
        while (line[i] != ',' && line[i] != '\0')
        {
            if (j >= fieldSize - 1) resizeArray(stockQty, fieldSize);
            stockQty[j++] = line[i++];
        }
        stockQty[j] = '\0';
        trim(stockQty);
        if (line[i] == ',') i++;

        // Parse Price
        j = 0;
        while (line[i] != ',' && line[i] != '\0')
        {
            if (j >= fieldSize - 1) resizeArray(price, fieldSize);
            price[j++] = line[i++];
        }
        price[j] = '\0';
        trim(price);
        if (line[i] == ',') i++;

        // Parse Promo Code
        j = 0;
        while (line[i] != ',' && line[i] != '\0') {
            if (j >= fieldSize - 1) resizeArray(promocode, fieldSize);
            promocode[j++] = line[i++];
        }
        promocode[j] = '\0';
        trim(promocode);
        if (line[i] == ',') i++;

        // Parse Promo Code Type
        j = 0;
        while (line[i] != '\0' && line[i] != '\n') {
            if (j >= fieldSize - 1) resizeArray(promocodeType, fieldSize);
            promocodeType[j++] = line[i++];
        }
        promocodeType[j] = '\0';
        trim(promocodeType);

        // Display the data in a formatted way
        cout << "| " << left << setw(12) << productID
            << "| " << left << setw(16) << name
            << "| " << left << setw(14) << category
            << "| " << right << setw(10) << stockQty
            << "| " << right << setw(8) << price
            << "| " << left << setw(16) << promocode
            << "| " << left << setw(16) << promocodeType
            << " |\n";
    }

    cout << "--------------------------------------------------------------------------------------------------------\n";

    file.close();

    // Free dynamically allocated memory
    delete[] line;
    delete[] productID;
    delete[] name;
    delete[] category;
    delete[] stockQty;
    delete[] price;
    delete[] promocode;
    delete[] promocodeType;
}



 







bool manualStrcasecmp(const char* str1, const char* str2)
{
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0')
    {
        char char1 = str1[i];
        char char2 = str2[i];

        // manually lowercase mn convert krny ka liay
        if (char1 >= 'A' && char1 <= 'Z')
        {
            char1 += 'a' - 'A'; 
        }
        if (char2 >= 'A' && char2 <= 'Z')
        {
            char2 += 'a' - 'A'; 
        }

        if (char1 != char2) 
        {
            return false;
        }
        i++;
    }

    // dodno string ko same time pr end krny ka liay
    return (str1[i] == '\0' && str2[i] == '\0');
}




void manualSearch()
{
   
    int lineSize = 150, fieldSize = 30;

    char* line = new char[lineSize];
    char* productID = new char[fieldSize];
    char* name = new char[fieldSize];
    char* category = new char[fieldSize];
    char* stockQty = new char[fieldSize];
    char* price = new char[fieldSize];
    char* searchQuery = new char[fieldSize];

    ifstream file("products.csv");

    if (!file) {
        cout << "Error: Unable to open the file 'products.csv'.\n";
        delete[] line;
        delete[] productID;
        delete[] name;
        delete[] category;
        delete[] stockQty;
        delete[] price;
        delete[] searchQuery;
        return;
    }

    int choice = 0;
    while (true)
    {
        // Display menu
        cout << "\n--- Product Manual Search Menu ---\n";
        cout << "---> 1. Search by Product ID\n";
        cout << "---> 2. Search by Product Name\n";
        cout << "---> 3. Search by Product Category\n";
        cout << "---> 4. Exit\n";
        cout << "==Enter your choice: ";
        cin >> choice;
        cin.ignore(); // To clear the input buffer

        if (choice == 4) {
            cout << "Exiting Manual Search. Thank you!\n";
            break;
        }

        // Prompt user for input based on the selected criterion
        cout << "Enter your search query: ";
        cin.getline(searchQuery, fieldSize);
        trim(searchQuery);

        bool found = false;
        file.clear(); 
        file.seekg(0); // Reset to the beginning of the file

        cout << "--------------------------------------------------------------------------\n";
        cout << "|  Product ID  |  Name            |  Category     | Stock Qty | Price     |\n";
        cout << "--------------------------------------------------------------------------\n";

        while (file.getline(line, lineSize))
        {
            int i = 0, j = 0;

            // Parse Product ID
            j = 0;
            while (line[i] != ',' && line[i] != '\0')
            {
                if (j >= fieldSize - 1) resizeArray(productID, fieldSize);
                productID[j++] = line[i++];
            }
            productID[j] = '\0';
            trim(productID);
            if (line[i] == ',') i++;

            // Parse Name
            j = 0;
            while (line[i] != ',' && line[i] != '\0')
            {
                if (j >= fieldSize - 1) resizeArray(name, fieldSize);
                name[j++] = line[i++];
            }
            name[j] = '\0';
            trim(name);
            if (line[i] == ',') i++;

            // Parse Category
            j = 0;
            while (line[i] != ',' && line[i] != '\0')
            {
                if (j >= fieldSize - 1) resizeArray(category, fieldSize);
                category[j++] = line[i++];
            }
            category[j] = '\0';
            trim(category);
            if (line[i] == ',') i++;

            // Parse Stock Quantity
            j = 0;
            while (line[i] != ',' && line[i] != '\0')
            {
                if (j >= fieldSize - 1) resizeArray(stockQty, fieldSize);
                stockQty[j++] = line[i++];
            }
            stockQty[j] = '\0';
            trim(stockQty);
            if (line[i] == ',') i++;

            // Parse Price
            j = 0;
            while (line[i] != '\0' && line[i] != '\n')
            {
                if (j >= fieldSize - 1) resizeArray(price, fieldSize);
                price[j++] = line[i++];
            }
            price[j] = '\0';
            trim(price);

            // search query ko match krny ka liay
            bool matches = false;
            if (choice == 1) 
            { // Search by Product ID
                matches = strcmp(searchQuery, productID) == 0;
            }
            else if (choice == 2)
            { 
                matches = strcmp(searchQuery, name) == 0;
            }
            else if (choice == 3) 
            {
                matches = strcmp(searchQuery, category) == 0;
            }

            // Display matching record
            if (matches)
            {
                found = true;
                cout << "| " << left << setw(12) << productID
                    << "| " << left << setw(16) << name
                    << "| " << left << setw(14) << category
                    << "| " << right << setw(10) << stockQty
                    << "| " << right << setw(8) << price
                    << " |\n";
            }
        }

        if (!found) {
            cout << "No matching product found for your search query.\n";
        }

        cout << "--------------------------------------------------------------------------\n";
    }

    file.close();

    // Free dynamically allocated memory
    delete[] line;
    delete[] productID;
    delete[] name;
    delete[] category;
    delete[] stockQty;
    delete[] price;
    delete[] searchQuery;
}




void Cart_Management()
{

    cout << "=====================================\n";
    cout << "||   WELCOME TO CART MANAGEMENT!    ||\n";
    cout << "=====================================\n";
    cout << "  1--> VIEW CART\n";
    cout << "  2.--> ADD ITEMS TO CART\n";
    cout << "  3.--->  REMOVE ITEM FROM CART\n";
    cout << "  4.---->  CLEAR CART\n";
    cout << "  5.----->  BACK TO CUSTOMER MENU\n";
    cout << "-------------------------------------\n";
    cout << " --> Please enter your choice: ";

    int choice;
    do 
    {
        cin >> choice;
    } while (choice < 1 || choice>5);

    switch (choice) 
    {
    case 1:
        display_cart();
        cout << "Press any key to continue:";
        cin.ignore();
        cin.get();
        Cart_Management();
        break;
    case 2:
    {
        viewallProducts();
        char choice;

        cout << "Do you want to add item to cart (y/n):";
        cin >> choice;

        if (choice == 'y' || choice=='Y')
        {
            addToCart();
        }
        else if (choice == 'n' || choice == 'N')
        {
            Cart_Management();
        }
        else
        {
            cout << "Inavlid Input. Try Again" << endl;
            Cart_Management();

        }


        break;
    }
    case 3:
        display_cart();
        removeitems();
        Cart_Management();
        break;
    case 4:
        clearcart();
        Cart_Management();
        break;
    case 5:
        customer();
    }
}




void clearcart()
{
    ofstream cart("cart.txt", ios::trunc);
    if (cart.is_open()) {
        cout << "All items have been removed from the cart.\n";
    }
    else {
        cout << "ERROR: Could not clear the cart file.\n";
    }
    cart.close(); // Close the file
}





void removeitems() {
    cout << "\n======================================\n";
    cout << "||         REMOVE ITEM FROM CART    ||\n";
    cout << "======================================\n";

    // Dynamic allocation for product ID
    int size = 50; 
    char* productID = new char[size];

    cout << "ENTER THE PRODUCT ID YOU WANT TO REMOVE FROM CART: ";
    cin >> productID;

    ifstream cartFile("cart.txt");
    ofstream tempFile("temp.txt");

    if (!cartFile.is_open() || !tempFile.is_open())
    {
        cout << "ERROR: COULD NOT OPEN FILES.\n";
        delete[] productID;
        return;
    }

    // Buffers for reading lines and parsing fields
    char* buffer = new char[200];
    char* currentProductID = new char[size];

    bool productFound = false;

    while (cartFile.getline(buffer, 200))
    {
        int i = 0, j = 0;

        // Parse Product ID (up to the first comma)
        while (buffer[i] != ',' && buffer[i] != '\0')
        {
            if (j >= size - 1)
            {
                resizeArray(currentProductID, size);
            }
            currentProductID[j++] = buffer[i++];
        }
        currentProductID[j] = '\0';

        // Manual comparison of Product ID
        bool idsMatch = true;
        for (int k = 0; currentProductID[k] != '\0' || productID[k] != '\0'; ++k) {
            if (currentProductID[k] != productID[k]) {
                idsMatch = false;
                break;
            }
        }

        if (idsMatch)
        {
            productFound = true; // Mark product as found and skip writing to temp file
            continue;
        }

        // Write non-matching lines to the temp file
        tempFile << buffer << endl;
    }

    // Notify the user
    if (productFound)
    {
        cout << "PRODUCT WITH ID " << productID << " HAS BEEN REMOVED FROM THE CART.\n";
    }
    else 
    {
        cout << "NO PRODUCT WITH ID " << productID << " FOUND IN THE CART.\n";
    }

    // Close files and update cart file
    cartFile.close();
    tempFile.close();
    remove("cart.txt");
    rename("temp.txt", "cart.txt");

    // Clean up dynamically allocated memory
    delete[] productID;
    delete[] buffer;
    delete[] currentProductID;
}




void display_cart() 
{
    ifstream cart("cart.txt");
    if (!cart.is_open()) {
        cout << "ERROR: Could not open the cart file." << endl;
        return;
    }

    char* buffer = new char[200];  
    char* fileProductID = new char[50];
    char* fileName = new char[50];
    char* fileCategory = new char[50];
    char* fileQuantity = new char[50];
    char* filePrice = new char[50];

    bool isEmpty = true;  // Flag to check if the cart is empty

    cout << "\n======================================\n";
    cout << "||         CART ITEMS               ||\n";
    cout << "======================================\n";

    // Process each line in the cart file
    while (cart.getline(buffer, 200))
    {
        isEmpty = false;  // If we read at least one line, the cart is not empty
        int i = 0, j = 0;

        // Parse Product ID
        while (buffer[i] != ',' && buffer[i] != '\0') 
        {
            fileProductID[j++] = buffer[i++];
        }
        fileProductID[j] = '\0';
        i++; 

        // Parse Name
        j = 0;
        while (buffer[i] != ',' && buffer[i] != '\0')
        {
            fileName[j++] = buffer[i++];
        }
        fileName[j] = '\0';
        i++;

        // Parse Category
        j = 0;
        while (buffer[i] != ',' && buffer[i] != '\0')
        {
            fileCategory[j++] = buffer[i++];
        }
        fileCategory[j] = '\0';
        i++;

        // Parse Quantity
        j = 0;
        while (buffer[i] != ',' && buffer[i] != '\0')
        {
            fileQuantity[j++] = buffer[i++];
        }
        fileQuantity[j] = '\0';
        i++;

        // Parse Price
        j = 0;
        while (buffer[i] != '\0') {
            filePrice[j++] = buffer[i++];
        }
        filePrice[j] = '\0';

        // Display product information
        cout << "   Product ID: " << fileProductID << "\n"
            << "   Name: " << fileName << "\n"
            << "   Category: " << fileCategory << "\n"
            << "   Quantity: " << fileQuantity << "\n"
            << "   Price:  " << filePrice << "\n";
        cout << "--------------------------------------\n";
    }

    if (isEmpty) 
    {
        cout << "Your cart is empty.\n";
    }

    cout << "======================================\n";
    cout << " ---End of cart items ----\n";

    cart.close();

    // Free dynamically allocated memory
    delete[] buffer;
    delete[] fileProductID;
    delete[] fileName;
    delete[] fileCategory;
    delete[] fileQuantity;
    delete[] filePrice;
}



bool isProductInCart(char* pid) 
{
    ifstream cart("cart.txt");
    if (!cart.is_open()) {
        cout << "ERROR: COULD NOT OPEN THE CART FILE." << endl;
        return false;
    }

    // Allocate memory for dynamic Product ID storage
    int currentSize = 5;
    char* fileProductID = new char[currentSize];
    char buffer[200];

    // Read each line from the cart file
    while (cart.getline(buffer, 200)) {
        int i = 0, j = 0;

       
        while (buffer[i] != '|' && buffer[i] != '\0')
        {
            if (j >= currentSize - 1) {
                resizeArray_Customer(fileProductID, currentSize); 
            }
            fileProductID[j++] = buffer[i++];
        }
        fileProductID[j] = '\0'; 

        trim(fileProductID); 

        // Check if the product ID matches
        if (stringCompare(pid, fileProductID))
        {
            delete[] fileProductID; 
            cart.close();
            return true; 
        }
    }

    // Free allocated memory and close file if no match is found
    delete[] fileProductID;
    cart.close();
    return false;
}



void increaseProductQuantity(char* pid)
{
    ifstream cart("cart.txt");
    ofstream temp("temp.txt");

    if (!cart.is_open())
    {
        cout << "ERROR: COULD NOT OPEN THE CART FILE." << endl;
        return;
    }

    if (!temp.is_open())
    {
        cout << "ERROR: COULD NOT CREATE A TEMPORARY FILE." << endl;
        return;
    }

    // Initial sizes and allocations for dynamic arrays
    int sizePID = 10, sizeName = 50, sizeCategory = 50, sizeQuantity = 10, sizePrice = 20;
    char* fileProductID = new char[sizePID];
    char* fileName = new char[sizeName];
    char* fileCategory = new char[sizeCategory];
    char* fileQuantity = new char[sizeQuantity];
    char* filePrice = new char[sizePrice];
    char buffer[200];

    bool found = false;

    while (cart.getline(buffer, 200))
    {
        int i = 0, j = 0;

        // Parse Product ID
        while (buffer[i] != '|' && buffer[i] != '\0') 
        {
            if (j >= sizePID - 1) {
                resizeArray_Customer(fileProductID, sizePID);
            }
            fileProductID[j++] = buffer[i++];
        }
        fileProductID[j] = '\0';
        i++;

        // Parse Name
        j = 0;
        while (buffer[i] != '|' && buffer[i] != '\0')
        {
            if (j >= sizeName - 1) {
                resizeArray_Customer(fileName, sizeName);
            }
            fileName[j++] = buffer[i++];
        }
        fileName[j] = '\0';
        i++;

        // Parse Category
        j = 0;
        while (buffer[i] != '|' && buffer[i] != '\0')
        {
            if (j >= sizeCategory - 1) {
                resizeArray_Customer(fileCategory, sizeCategory);
            }
            fileCategory[j++] = buffer[i++];
        }
        fileCategory[j] = '\0';
        i++;

        // Parse Quantity
        j = 0;
        while (buffer[i] != '|' && buffer[i] != '\0')
        {
            if (j >= sizeQuantity - 1)
            {
                resizeArray_Customer(fileQuantity, sizeQuantity);
            }
            fileQuantity[j++] = buffer[i++];
        }
        fileQuantity[j] = '\0';
        i++;

        // Parse Price
        j = 0;
        while (buffer[i] != '\0') 
        {
            if (j >= sizePrice - 1)
            {
                resizeArray_Customer(filePrice, sizePrice);
            }
            filePrice[j++] = buffer[i++];
        }
        filePrice[j] = '\0';

        // Trim the parsed data
        trim(fileProductID);
        trim(fileName);
        trim(fileCategory);
        trim(fileQuantity);
        trim(filePrice);

        // Increase quantity if IDs match
        if (stringCompare(pid, fileProductID))
        {
            int quantity = atoi(fileQuantity);
            quantity++;  // Increment the quantity by 1
            temp << fileProductID << " | " << fileName << " | " << fileCategory << " | "
                << quantity << " | " << filePrice << endl;
            found = true;
        }
        else 
        {
            temp << fileProductID << " | " << fileName << " | " << fileCategory << " | "
                << fileQuantity << " | " << filePrice << endl;
        }
    }

    if (!found)
    {
        cout << "ERROR: PRODUCT NOT FOUND TO INCREASE QUANTITY." << endl;
    }
    else {
        cout << "PRODUCT QUANTITY UPDATED SUCCESSFULLY." << endl;
    }

    // Clean up and replace files
    delete[] fileProductID;
    delete[] fileName;
    delete[] fileCategory;
    delete[] fileQuantity;
    delete[] filePrice;

    cart.close();
    temp.close();

    remove("cart.txt");
    rename("temp.txt", "cart.txt");
}




void addToCart()
{
    cout << "\n   ADD ITEM TO CART\n";
    cout << "-------------------------------------\n";

    // Initial size for dynamic memory allocation
    int size = 50;
    char* productID = new char[size];
    char* line = new char[200];
    char* fileProductID = new char[size];
    char* name = new char[size];
    char* category = new char[size];
    char* stockQty = new char[size];
    char* price = new char[size];

    cout << "ENTER THE PRODUCT ID YOU WANT TO ADD TO CART: ";
    cin >> productID;
    cin.ignore();  
    trim(productID);

    ifstream productsFile("products.csv");
    if (!productsFile.is_open()) 
    {
        cout << "ERROR: COULD NOT OPEN THE PRODUCTS FILE.\n";
        delete[] productID;
        delete[] line;
        delete[] fileProductID;
        delete[] name;
        delete[] category;
        delete[] stockQty;
        delete[] price;
        return;
    }

    bool productFound = false;

    while (productsFile.getline(line, 200))
    {
        int i = 0, j = 0;

        // search product id krny ka liay
        while (line[i] != ',' && line[i] != '\0')
        {
            if (j >= size - 1) resizeArray(fileProductID, size);
            fileProductID[j++] = line[i++];
        }
        fileProductID[j] = '\0';
        trim(fileProductID);
        if (line[i] == ',') i++;

        // Parse Name
        j = 0;
        while (line[i] != ',' && line[i] != '\0') 
        {
            if (j >= size - 1) resizeArray(name, size);
            name[j++] = line[i++];
        }
        name[j] = '\0';
        trim(name);
        if (line[i] == ',') i++;

        // Parse Category
        j = 0;
        while (line[i] != ',' && line[i] != '\0')
        {
            if (j >= size - 1) resizeArray(category, size);
            category[j++] = line[i++];
        }
        category[j] = '\0';
        trim(category);
        if (line[i] == ',') i++;

        // Parse Stock Quantity
        j = 0;
        while (line[i] != ',' && line[i] != '\0')
        {
            if (j >= size - 1) resizeArray(stockQty, size);
            stockQty[j++] = line[i++];
        }
        stockQty[j] = '\0';
        trim(stockQty);
        if (line[i] == ',') i++;

        // Parse Price
        j = 0;
        while (line[i] != '\0' && line[i] != '\n') 
        {
            if (j >= size - 1) resizeArray(price, size);
            price[j++] = line[i++];
        }
        price[j] = '\0';
        trim(price);

        // Manual string comparison to check if the Product ID matches
        bool idsMatch = true;
        for (int k = 0; fileProductID[k] != '\0' || productID[k] != '\0'; ++k)
        {
            if (fileProductID[k] != productID[k]) 
            {
                idsMatch = false;
                break;
            }
        }

        if (idsMatch)
        {
            productFound = true;
            int availableQty = atoi(stockQty); // Convert stock quantity to integer
            if (availableQty <= 0) {
                cout << "\nERROR: The selected product is out of stock.\n";
                break;
            }

            int quantityToAdd;
            cout << "\nADDED TO CART:\n";
            cout << "Product ID: " << fileProductID << "\n";
            cout << "Name: " << name << "\n";
            cout << "Category: " << category << "\n";
            cout << "Price: " << price << "\n";
            cout << "Available Stock: " << stockQty << "\n";

            do {
                cout << "Enter the quantity to add (Max: " << availableQty << "): ";
                cin >> quantityToAdd;
                if (quantityToAdd > availableQty || quantityToAdd <= 0) {
                    cout << "Invalid quantity. Please enter a value between 1 and " << availableQty << ".\n";
                }
            } while (quantityToAdd > availableQty || quantityToAdd <= 0);

            // Append the product to the cart file
            ofstream cartFile("cart.txt", ios::app);
            if (cartFile.is_open()) {
                cartFile << fileProductID << "," << name << "," << category << "," << quantityToAdd << "," << price ;
                cartFile.close();
                cout << "\nSuccessfully added " << quantityToAdd << " item(s) of " << name << " to the cart.\n";
            }
            else {
                cout << "ERROR: COULD NOT OPEN THE CART FILE.\n";
            }
            break;
        }
    }

    if (!productFound)
    {
        cout << "\nNO MATCHES FOUND FOR PRODUCT ID '" << productID << "'.\n";
    }

    productsFile.close();

    // Free dynamically allocated memory
    delete[] productID;
    delete[] line;
    delete[] fileProductID;
    delete[] name;
    delete[] category;
    delete[] stockQty;
    delete[] price;

   
    char choice;
    cout << "\nDO YOU WANT TO ADD ANOTHER ITEM TO THE CART? (Y/N): ";
    cin >> choice;
    cin.ignore(); // Ignore the newline character

    if (choice == 'Y' || choice == 'y') {
        addToCart(); 
    }
    else {
        cout << "\nREDIRECTING TO THE MAIN MENU...\n";
    }
}



bool compareStrings1(const char* str1, const char* str2)
{
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0')
    {
        if (str1[i] != str2[i])
        {
            return false;
        }
        i++;
    }
    // Ensure both strings are terminated properly
    return (str1[i] == '\0' && str2[i] == '\0');
}



bool doesUserExist(const char* username)
{
    ifstream file("customer.csv");

    if (!file.is_open()) {
        cout << "Error opening customer file.\n";
        return false;
    }

    char line[200];
    char fileUsername[50];

    while (file.getline(line, 200)) {
        int i = 0, j = 0;

        // Extract Username (before the first comma)
        while (line[i] != ',' && line[i] != '\0') {
            fileUsername[j++] = line[i++];
        }
        fileUsername[j] = '\0';

        // Compare the input username with the file's username
        int k = 0;
        while (username[k] != '\0' && fileUsername[k] != '\0')
        {
            if (username[k] != fileUsername[k]) 
            {
                break;
            }
            k++;
        }

        if (username[k] == '\0' && fileUsername[k] == '\0')
        {
            file.close();
            return true; 
        }
    }

    file.close();
    return false; 
}



void wishlist()
{
    int choice;
    int itemId, newItemId;

    // Dynamically allocate memory for the username
    char* username = new char[50];

    cout << "------------------------------------------" << endl;
    cout << "|        Wish__List                      |" << endl;
    cout << "|----------------------------------------|" << endl;
    cout << "| 1. Add item to wishlist                |" << endl;
    cout << "| 2. Remove item from wishlist           |" << endl;
    cout << "| 3. Update wishlist                     |" << endl;
    cout << "| 4. Return to Customer Menu             |" << endl;
    cout << "------------------------------------------" << endl;

    cin >> choice;
    cin.ignore();




    if (choice == 1)
    {
        viewallProducts();
        cout << "Enter Username: ";
        cin.getline(username, 50);
        DisplayWishlist(username);
        cout << "Enter the Item ID to add: ";
        cin >> itemId;
        addwish(username, itemId);
        wishlist();
    }
    else if (choice == 2)
    {
        cout << "Enter Username: ";
        cin.getline(username, 50);
        DisplayWishlist(username);
        cout << "Enter the Item ID to remove: ";
        cin >> itemId;
        removeWish(username, itemId);  // Correctly passing the username and itemId
        wishlist();
    }
    else if (choice == 3)
    {
        cout << "Enter Username: ";
        cin.getline(username, 50);
        DisplayWishlist(username);
        cout << "Enter the Item ID to update: ";
        cin >> itemId;
        cout << "Enter the new Item ID: ";
        cin >> newItemId;
        updateWish(username, itemId, newItemId);  // Correctly passing the username, itemId, and newItemId
        wishlist();
    }
    else if (choice == 4)
    {

        return;
    }
    else
    {
        cout << "\nInvalid Choice. Try Again." << endl;
        wishlist();
    }


    delete[] username;

}





void addwish(const char* username, int itemId)
{
 
    if (doesUserExist(username))
    {
        

       
        char filename[100] = { 0 };
        copyChars(filename, username);  
        concatenateChars(filename, "_wishlist.txt");

       
        ofstream fileOut(filename, ios::app);
        if (!fileOut)
        {
            cout << "Error opening wishlist file.\n";
            return;
        }

        // Validate item ID
        if (itemId > 0) {
            if (search(itemId))
            {
                // Add item to wishlist file
                fileOut << "Item ID: " << itemId << endl;
                cout << "Item added to your wishlist.\n";
            }
            else {
                cout << "Item doesn't exist.\n";
            }
        }
        else {
            cout << "Invalid item ID.\n";
        }

        fileOut.close();
    }
    else {
        cout << "Username does not exist." << endl;
    }
}




void concatenateChars(char* dest, const char* src) 
{
    int i = 0;
  
    while (dest[i] != '\0') {
        i++;
    }

    int j = 0;
    
    while (src[j] != '\0') {
        dest[i++] = src[j++];
    }
    dest[i] = '\0';  
}



void copyChars(char* dest, const char* src)
{
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';  
}




bool search(int itemId)
{
    // product file open krny ka liay
    ifstream file("products.csv");

    if (!file.is_open()) {
        cout << "ERROR: Could not open the product file.\n";
        return false;
    }

    int productId;
    char* line = new char[200];
    char* fileProductId = new char[50];

    bool itemFound = false;

    // line by line read krny ka liay
    while (file.getline(line, 200)) {
        int i = 0, j = 0;

        //pahli line pr id find krny ka liay
        while (line[i] != ',' && line[i] != '\0') {
            fileProductId[j++] = line[i++];
        }
        fileProductId[j] = '\0';

        // id ko integer sure krny ka liay
        productId = 0;
        for (int k = 0; fileProductId[k] != '\0'; k++) {
            productId = productId * 10 + (fileProductId[k] - '0');
        }

       //check krna id match krti ya nahi
        if (productId == itemId) {
            itemFound = true;
            break;
        }
    }

    // Clean up dynamic memory
    delete[] line;
    delete[] fileProductId;

    file.close();

    return itemFound;
}



void removeWish(const char* username, int itemId) {
    char filename[50];
    int i = 0;
    while (username[i] != '\0') {
        filename[i] = username[i];
        i++;
    }
    filename[i++] = '_';
    filename[i++] = 'w';
    filename[i++] = 'i';
    filename[i++] = 's';
    filename[i++] = 'h';
    filename[i++] = 'l';
    filename[i++] = 'i';
    filename[i++] = 's';
    filename[i++] = 't';
    filename[i++] = '.';
    filename[i++] = 't';
    filename[i++] = 'x';
    filename[i++] = 't';
    filename[i] = '\0';  // Null terminate filename

    ifstream fileIn(filename);
    if (!fileIn.is_open()) {
        cout << "Error: Could not open wishlist file.\n";
        return;
    }

    ofstream fileOut("temp.txt");
    char* line = new char[200];
    bool itemRemoved = false;

    while (fileIn.getline(line, 200)) {
        int i = 0;
        int item = 0;

        // Skip the "Item ID: " part
        while (line[i] != ':' && line[i] != '\0') {
            i++;
        }

        // Move past the space after the colon
        if (line[i] == ':') {
            i++;
        }

        // Skip any leading spaces before the item ID
        while (line[i] == ' ') {
            i++;
        }

        // Convert the item ID part to an integer
        while (line[i] != '\0' && line[i] != ' ' && line[i] != '\n') {
            item = item * 10 + (line[i] - '0');
            i++;
        }

        // If the item matches the one to remove, skip it, otherwise copy it to the new file
        if (item != itemId) {
            fileOut << line << endl;
        }
        else {
            itemRemoved = true;
        }
    }

    fileIn.close();
    fileOut.close();

    // Check if the item was removed successfully
    if (itemRemoved) {
        remove(filename);
        rename("temp.txt", filename);
        cout << "Item " << itemId << " removed from wishlist.\n";
    }
    else {
        remove("temp.txt");
        cout << "Item " << itemId << " not found in wishlist.\n";
    }

    delete[] line;
}




void updateWish(const char* username, int itemId, int newItemId)
{
    char filename[50];
    int i = 0;
    while (username[i] != '\0') {
        filename[i] = username[i];
        i++;
    }
    filename[i++] = '_';
    filename[i++] = 'w';
    filename[i++] = 'i';
    filename[i++] = 's';
    filename[i++] = 'h';
    filename[i++] = 'l';
    filename[i++] = 'i';
    filename[i++] = 's';
    filename[i++] = 't';
    filename[i++] = '.';
    filename[i++] = 't';
    filename[i++] = 'x';
    filename[i++] = 't';
    filename[i] = '\0';  // Null-terminate filename

    ifstream fileIn(filename);
    if (!fileIn.is_open()) {
        cout << "Error: Could not open wishlist file.\n";
        return;
    }

    ofstream fileOut("temp.txt");
    char* line = new char[200];
    bool itemUpdated = false;

    while (fileIn.getline(line, 200))
    {
        int i = 0;
        int item = 0;


        while (line[i] != ':' && line[i] != '\0')
        {
            i++;
        }

       
        if (line[i] == ':')
        {
            i++;
        }

      
        while (line[i] == ' ') {
            i++;
        }

     
        while (line[i] != '\0' && line[i] != ' ' && line[i] != '\n') {
            item = item * 10 + (line[i] - '0');
            i++;
        }

        if (item == itemId) {
            fileOut << "Item ID: " << newItemId << endl;
            itemUpdated = true;
        }
        else {
            fileOut << line << endl;
        }
    }

    fileIn.close();
    fileOut.close();

   
    if (itemUpdated) {
        remove(filename);
        rename("temp.txt", filename);
        cout << "Item " << itemId << " updated to " << newItemId << " in wishlist.\n";
    }
    else {
        remove("temp.txt");
        cout << "Item " << itemId << " not found in wishlist.\n";
    }

    delete[] line;  // Free dynamically allocated memory
}




void DisplayWishlist(const char* username)
{
    char filename[100];
    int i = 0;
    while (username[i] != '\0') {
        filename[i] = username[i];
        i++;
    }
    filename[i++] = '_';
    filename[i++] = 'w';
    filename[i++] = 'i';
    filename[i++] = 's';
    filename[i++] = 'h';
    filename[i++] = 'l';
    filename[i++] = 'i';
    filename[i++] = 's';
    filename[i++] = 't';
    filename[i++] = '.';
    filename[i++] = 't';
    filename[i++] = 'x';
    filename[i++] = 't';
    filename[i] = '\0';  // Null-terminate the filename

    ifstream file(filename);
    if (!file) {
        cout << "Wishlist is empty or does not exist." << endl;
        return;
    }

    cout << "Your Wishlist:" << endl;
    char line[100];
    while (file.getline(line, 100)) {
        cout << line << endl;
    }
    file.close();
}



void resizeArray(char**& arr, int& currentSize, int newSize)
{
    char** temp = new char* [newSize];
    for (int i = 0; i < currentSize; i++) {
        temp[i] = arr[i];
    }
    delete[] arr;
    arr = temp;
    currentSize = newSize;
}


void submitSupportRequest(char**& names, char**& emails, char**& inquiries, char**& descriptions, int& count, int& capacity) {
    char tempName[50];
    char tempEmail[50];
    char tempInquiry[50];
    char tempDescription[200];

    // Prompt user for information
    cout << "\n---- Submit Support Request ----\n";
    cout << "Enter your name: ";
    cin.ignore();
    cin.getline(tempName, 50);

    // Check if customer exists
    if (!doesUserExist(tempName)) {
        cout << "Error: Customer does not exist. Please register first.\n";
        return;
    }

    cout << "Enter your email: ";
    cin.getline(tempEmail, 50);

    // Validate email
    if (!isValidEmail(tempEmail)) {
        cout << "Error: Invalid email address. Please enter a valid email containing '@'.\n";
        return;
    }

    cout << "What is the nature of your inquiry? (e.g., Product Information, Order Assistance): ";
    cin.getline(tempInquiry, 50);

    cout << "Please describe your issue in detail:\n";
    cin.getline(tempDescription, 200);

    // Resize arrays if necessary
    if (count >= capacity) {
        resizeArray(names, capacity, capacity * 2);
        resizeArray(emails, capacity, capacity * 2);
        resizeArray(inquiries, capacity, capacity * 2);
        resizeArray(descriptions, capacity, capacity * 2);
    }

    // Add data to arrays
    names[count] = new char[50];
    emails[count] = new char[50];
    inquiries[count] = new char[50];
    descriptions[count] = new char[200];

    copyChars(names[count], tempName);
    copyChars(emails[count], tempEmail);
    copyChars(inquiries[count], tempInquiry);
    copyChars(descriptions[count], tempDescription);

    count++;

    // Append the request to the Support.txt file
    ofstream supportFile("Support.txt", ios::app);

    if (!supportFile) {
        cout << "Error: Unable to open Support.txt for writing.\n";
        return;
    }

    supportFile << "Customer Name: " << tempName << endl;
    supportFile << "Email: " << tempEmail << endl;
    supportFile << "Inquiry Type: " << tempInquiry << endl;
    supportFile << "Description: " << tempDescription << endl;
    supportFile << "-------------------------------------\n";

    supportFile.close();

    // Confirmation message for the user
    cout << "\nThank you, " << tempName << ". Your support request has been submitted successfully.\n";
    cout << "Our support team will contact you at " << tempEmail << " soon.\n";
}



void Support_Requests()
{
    int choice;

    int capacity = 2; // Initial capacity
    int count = 0;    // Current number of requests

    char** names = new char* [capacity];
    char** emails = new char* [capacity];
    char** inquiries = new char* [capacity];
    char** descriptions = new char* [capacity];

    cout << "========Support Menu===========\n";
    cout << "||                            ||\n";
    cout << "||  1.Submit Support Request  ||\n";
    cout << "||  2.Exit                    ||\n";
    cout << "||                            ||\n";
    cout << "==============================||\n";

    cin >> choice;

    if (choice == 1)
    {
        submitSupportRequest(names, emails, inquiries, descriptions, count, capacity);
        customer();
    }
    else if (choice == 2)
    {
        customer();
    }
    else
    {
        customer();
    }
}




void PurchaseAndCheckout()
{
    int choice;
    float discount=0.0;

    cout << "------------------------------------------" << endl;
    cout << "|     Purchase and Checkout              |" << endl;
    cout << "|----------------------------------------|" << endl;
    cout << "| 1. View Cart                           |" << endl;
    cout << "| 2. Apply Promocode and checkout        |" << endl;
    cout << "| 3. Proceed to Checkout                 |" << endl;
    cout << "------------------------------------------" << endl;


    cin >> choice;

    if (choice == 1)
    {
        display_cart();
    }
    else if (choice == 2)
    {
        handlePromoCode();
    }
    else if (choice == 3)
    {
        confirmPurchase();
    }


}








bool isEqual2(const char* str1, const char* str2)
{
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return false;
        }
        i++;
    }
    return str1[i] == str2[i];
}





float parsePrice(const char* priceStr)
{
    float price = 0.0;
    bool isDecimal = false;
    float decimalPlace = 1.0;

    for (int i = 0; priceStr[i] != '\0'; i++) {
        if (priceStr[i] == '$') continue;

        if (priceStr[i] == '.') {
            isDecimal = true;
            continue;
        }

        if (priceStr[i] >= '0' && priceStr[i] <= '9') {
            if (isDecimal) {
                decimalPlace /= 10;
                price += (priceStr[i] - '0') * decimalPlace;
            }
            else {
                price = price * 10 + (priceStr[i] - '0');
            }
        }
    }

    return price;
}




int stringToInt(const char* str)
{
    int number = 0;
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            number = number * 10 + (str[i] - '0');
        }
        else {
            break; // Non-numeric character found
        }
        i++;
    }
    return number;
}




void parseCartDetails(const char* cartLine, char* productID, char* productName, char* productCategory, char* quantityStr, char* priceStr) 
{
    int i = 0, j = 0;

    // Extract Product ID
    while (cartLine[i] != ',' && cartLine[i] != '\0') productID[j++] = cartLine[i++];
    productID[j] = '\0'; i++;
    j = 0;

    // Extract Product Name
    while (cartLine[i] != ',' && cartLine[i] != '\0') productName[j++] = cartLine[i++];
    productName[j] = '\0'; i++;
    j = 0;

    // Skip Product Category
    while (cartLine[i] != ',' && cartLine[i] != '\0') productCategory[j++] = cartLine[i++];
    productCategory[j] = '\0'; i++;
    j = 0;

    // Extract Quantity
    while (cartLine[i] != ',' && cartLine[i] != '\0') quantityStr[j++] = cartLine[i++];
    quantityStr[j] = '\0'; i++;
    j = 0;

    // Extract Price
    while (cartLine[i] != '\0') priceStr[j++] = cartLine[i++];
    priceStr[j] = '\0';
}








void applyPromoCode(const char* promoCode, float& totalAmount)
{
    if (isEqual2(promoCode, "15off")) {
        if (totalAmount > 50) {
            totalAmount -= totalAmount * 0.15;  // 15% discount
            cout << "Discount applied! New Total: $" << fixed << setprecision(2) << totalAmount << endl;
        }
        else {
            cout << "Total amount too low for a discount.\n";
        }
    }
    else {
        cout << "Invalid promo code entered.\n";
    }
}



void saveOrderSummary(const char* username, float totalAmount)
{
    ifstream cartFile("cart.txt");
    if (!cartFile.is_open()) {
        cout << "ERROR: Unable to open cart file.\n";
        return;
    }

    ofstream orderFile("orders.txt", ios::app);
    if (!orderFile.is_open()) {
        cout << "ERROR: Unable to open order file.\n";
        return;
    }

    char cartLine[200];
    while (cartFile.getline(cartLine, 200)) {
        char productID[50], productName[50], productCategory[50], quantityStr[50], priceStr[50];
        parseCartDetails(cartLine, productID, productName, productCategory, quantityStr, priceStr);

        // Calculate total for this product
        int quantity = stringToInt(quantityStr);
        float price = parsePrice(priceStr);
        float totalProductPrice = quantity * price;

        // Write to orders.txt
        orderFile << "Username: " << username << ", Product ID: " << productID << ", Product Name: " << productName
            << ", Quantity: " << quantity << ", Price: $" << fixed << setprecision(2) << price
            << ", Total: $" << fixed << setprecision(2) << totalProductPrice << endl;
    }
    cartFile.close();

    // Write the total order amount
    orderFile << "Total Order Amount: $" << fixed << setprecision(2) << totalAmount << endl;
    orderFile << "--------------------------------------------------" << endl;

    orderFile.close();
}




void handlePromoCode() {
    char promoCode[50];
    char username[50];

    cout << "Enter Username: ";
    cin >> username;

    cout << "Enter Promo Code: ";
    cin >> promoCode;

    ifstream cartFile("cart.txt");
    if (!cartFile.is_open()) {
        cout << "ERROR: Unable to open cart file.\n";
        return;
    }

    // Calculate total amount from cart.txt
    float totalAmount = 0.0;
    char cartLine[200];
    while (cartFile.getline(cartLine, 200)) {
        char productID[50], productName[50], productCategory[50], quantityStr[50], priceStr[50];
        int i = 0, j = 0;

        // Extract Product ID
        while (cartLine[i] != ',' && cartLine[i] != '\0') {
            productID[j++] = cartLine[i++];
        }
        productID[j] = '\0';
        i++;

        // Extract Product Name
        j = 0;
        while (cartLine[i] != ',' && cartLine[i] != '\0') {
            productName[j++] = cartLine[i++];
        }
        productName[j] = '\0';
        i++;

        // Skip Product Category
        while (cartLine[i] != ',' && cartLine[i] != '\0') {
            i++;
        }
        i++;

        // Extract Quantity
        j = 0;
        while (cartLine[i] != ',' && cartLine[i] != '\0') {
            quantityStr[j++] = cartLine[i++];
        }
        quantityStr[j] = '\0';
        i++;

        // Extract Price
        j = 0;
        while (cartLine[i] != '\0') {
            priceStr[j++] = cartLine[i++];
        }
        priceStr[j] = '\0';

        // Debugging output
        cout << "Product ID: " << productID << ", Name: " << productName << ", Quantity: " << quantityStr << ", Price: " << priceStr << endl;

        // Calculate total for this product
        int quantity = stringToInt(quantityStr); // Manually convert quantity
        float price = parsePrice(priceStr);
        float totalProductPrice = quantity * price;
        totalAmount += totalProductPrice;

        // Debugging output for total amount
        cout << "Total Amount so far: $" << fixed << setprecision(2) << totalAmount << endl;
    }
    cartFile.close();

    cout << "Total Amount before Discount: $" << fixed << setprecision(2) << totalAmount << endl;

    // Validate promo code and apply discount
    if (isEqual2(promoCode, "15off")) {
        if (totalAmount > 50) {
            totalAmount -= totalAmount * 0.15;  // 15% discount
            cout << "Discount applied! New Total: $" << fixed << setprecision(2) << totalAmount << endl;
        }
        else {
            cout << "Total amount too low for a discount.\n";
        }
    }
    else {
        cout << "Invalid promo code entered.\n";
    }

    cout << "Amount to Pay: $" << fixed << setprecision(2) << totalAmount << endl;

    // Ask for order confirmation
    char confirm;
    cout << "Confirm Purchase and Proceed to Checkout? (Y/N): ";
    cin >> confirm;

    if (confirm == 'Y' || confirm == 'y') {
        // Proceed to store the order summary in order.txt
        ofstream orderFile("orders.txt", ios::app);
        if (!orderFile.is_open()) {
            cout << "ERROR: Unable to open order file.\n";
            return;
        }

        // Now let's also include the details of the items purchased
        ifstream cartFileDetails("cart.txt");
        if (!cartFileDetails.is_open()) {
            cout << "ERROR: Unable to open cart file for details.\n";
            return;
        }

        while (cartFileDetails.getline(cartLine, 200)) {
            char productID[50], productName[50], productCategory[50], quantityStr[50], priceStr[50];
            int i = 0, j = 0;

            // Extract Product ID
            while (cartLine[i] != ',' && cartLine[i] != '\0') {
                productID[j++] = cartLine[i++];
            }
            productID[j] = '\0';
            i++;

            // Extract Product Name
            j = 0;
            while (cartLine[i] != ',' && cartLine[i] != '\0') {
                productName[j++] = cartLine[i++];
            }
            productName[j] = '\0';
            i++;

            // Skip Category
            while (cartLine[i] != ',' && cartLine[i] != '\0') {
                i++;
            }
            i++;

            // Extract Quantity
            j = 0;
            while (cartLine[i] != ',' && cartLine[i] != '\0') {
                quantityStr[j++] = cartLine[i++];
            }
            quantityStr[j] = '\0';
            i++;

            // Extract Price
            j = 0;
            while (cartLine[i] != '\0') {
                priceStr[j++] = cartLine[i++];
            }
            priceStr[j] = '\0';

            // Calculate total for this product
            int quantity = stringToInt(quantityStr); // Manually convert quantity
            float price = parsePrice(priceStr);
            float totalProductPrice = quantity * price;

            // Write to orders.txt in a searchable format
            orderFile << "Username: " << username << ", Product ID: " << productID << ", Product Name: " << productName
                << ", Quantity: " << quantity << ", Price: $" << fixed << setprecision(2) << price
                << ", Total: $" << fixed << setprecision(2) << totalProductPrice << endl;
        }
        cartFileDetails.close();

        // Write the total order amount
        orderFile << "Total Order Amount: $" << fixed << setprecision(2) << totalAmount << endl;
        orderFile << "--------------------------------------------------" << endl;

        // Close the order file
        orderFile.close();

        cout << "Your order has been confirmed.Thank you for choosing secure Shop.\n";
    }
    else {
        cout << "Purchase cancelled. Returning to main menu.\n";
    }
}





float calculateTotalAndShowReceipt()
{
    ifstream cartFile("cart.txt");
    if (!cartFile.is_open()) {
        cout << "ERROR: Unable to open cart file.\n";
        return 0.0;
    }

    float totalAmount = 0.0;
    char cartLine[200];
    cout << "---------------------------- RECEIPT ----------------------------\n";
    cout << left << setw(15) << "Product ID" << setw(20) << "Name"
        << setw(10) << "Quantity" << setw(10) << "Price" << setw(10) << "Total\n";
    cout << "---------------------------------------------------------------\n";

    while (cartFile.getline(cartLine, 200)) {
        char productID[50], productName[50], productCategory[50], quantityStr[50], priceStr[50];
        int i = 0, j = 0;

        // Extract Product ID
        while (cartLine[i] != ',' && cartLine[i] != '\0') {
            productID[j++] = cartLine[i++];
        }
        productID[j] = '\0';
        i++;

        // Extract Product Name
        j = 0;
        while (cartLine[i] != ',' && cartLine[i] != '\0') {
            productName[j++] = cartLine[i++];
        }
        productName[j] = '\0';
        i++;

        // Skip Category
        while (cartLine[i] != ',' && cartLine[i] != '\0') {
            i++;
        }
        i++;

        // Extract Quantity
        j = 0;
        while (cartLine[i] != ',' && cartLine[i] != '\0') {
            quantityStr[j++] = cartLine[i++];
        }
        quantityStr[j] = '\0';
        i++;

        // Extract Price
        j = 0;
        while (cartLine[i] != '\0') {
            priceStr[j++] = cartLine[i++];
        }
        priceStr[j] = '\0';

        // Calculate total for this product
        int quantity = stringToInt(quantityStr); // Manually convert quantity
        float price = parsePrice(priceStr);
        float totalProductPrice = quantity * price;
        totalAmount += totalProductPrice;

        // Display product details
        cout << left << setw(15) << productID << setw(20) << productName
            << setw(10) << quantity << setw(10) << price << setw(10) << totalProductPrice << '\n';
    }
    cartFile.close();

    cout << "---------------------------------------------------------------\n";
    cout << "Total Amount: $" << fixed << setprecision(2) << totalAmount << endl;
    cout << "---------------------------------------------------------------\n";

    return totalAmount;
}




void intToString1(int num, char* str) {
    int i = 0;
    bool isNegative = false;

    // Handle negative numbers
    if (num < 0) {
        isNegative = true;
        num = -num;
    }

    // Extract digits in reverse order
    do {
        str[i++] = (num % 10) + '0';
        num /= 10;
    } while (num > 0);

    // Add negative sign if necessary
    if (isNegative) {
        str[i++] = '-';
    }

    // Null-terminate the string
    str[i] = '\0';

    // Reverse the string to get the correct order
    for (int j = 0; j < i / 2; ++j) {
        char temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
    }
}





void checkout() {
    char user[50];
    cout << "Enter Username: ";
    cin >> user;

    float total = calculateTotalAndShowReceipt();

    if (total == 0.0) {
        cout << "Cart is empty or an error occurred.\n";
        return;
    }

    cout << "Do you want to confirm the purchase? (yes/no): ";
    char confirm[10];
    cin >> confirm;

    if (!isEqual2(confirm, "yes")) {
        cout << "Purchase cancelled.\n";
        return;
    }

    ifstream cart("cart.txt");
    if (!cart.is_open()) {
        cout << "ERROR: Unable to open cart file.\n";
        return;
    }

    ifstream prod("products.csv");
    if (!prod.is_open()) {
        cout << "ERROR: Unable to open products file.\n";
        cart.close();
        return;
    }

    ofstream orders("orders.txt", ios::app);
    if (!orders.is_open()) {
        cout << "ERROR: Unable to open orders file.\n";
        cart.close();
        prod.close();
        return;
    }

    ofstream temp("temp.csv");
    if (!temp.is_open()) {
        cout << "ERROR: Unable to create temp file.\n";
        cart.close();
        prod.close();
        orders.close();
        return;
    }

    char cLine[200];
    while (cart.getline(cLine, 200)) {
        char cID[50], cName[50], cQtyStr[50], cPrice[50];
        int i = 0, j = 0;

        while (cLine[i] != ',' && cLine[i] != '\0') cID[j++] = cLine[i++];
        cID[j] = '\0'; i++; j = 0;
        while (cLine[i] != ',' && cLine[i] != '\0') cName[j++] = cLine[i++];
        cName[j] = '\0'; i++; while (cLine[i] != ',' && cLine[i] != '\0') i++; i++; j = 0;
        while (cLine[i] != ',' && cLine[i] != '\0') cQtyStr[j++] = cLine[i++];
        cQtyStr[j] = '\0'; i++; j = 0;
        while (cLine[i] != '\0') cPrice[j++] = cLine[i++];
        cPrice[j] = '\0';

        int cQty = stringToInt(cQtyStr);
        float price = parsePrice(cPrice);
        float totalPrice = cQty * price;

        orders << "User: " << user << ", Product ID: " << cID
            << ", Name: " << cName << ", Qty: " << cQty
            << ", Price: $" << fixed << setprecision(2) << price
            << ", Total: $" << fixed << setprecision(2) << totalPrice << endl;

        char pLine[200];
        while (prod.getline(pLine, 200)) {
            char pID[50], pName[50], pCat[50], pQtyStr[50], pPrice[50];
            int k = 0, l = 0;

            while (pLine[k] != ',' && pLine[k] != '\0') pID[l++] = pLine[k++];
            pID[l] = '\0'; k++; l = 0;
            while (pLine[k] != ',' && pLine[k] != '\0') pName[l++] = pLine[k++];
            pName[l] = '\0'; k++; while (pLine[k] != ',' && pLine[k] != '\0') k++; k++; l = 0;
            while (pLine[k] != ',' && pLine[k] != '\0') pQtyStr[l++] = pLine[k++];
            pQtyStr[l] = '\0'; k++; l = 0;
            while (pLine[k] != '\0') pPrice[l++] = pLine[k++];
            pPrice[l] = '\0';

            int pQty = stringToInt(pQtyStr);

            if (isEqual2(cID, pID)) {
                pQty -= cQty;
                if (pQty < 0) pQty = 0;
            }

            char pQtyUpdated[50];
            intToString1(pQty, pQtyUpdated);
            temp << pID << ',' << pName << ',' << pCat << ',' << pQtyUpdated
                << ',' << pPrice << endl;
        }

        prod.clear();
        prod.seekg(0, ios::beg);
    }

    orders << "Total Amount: $" << fixed << setprecision(2) << total << endl;
    orders << "-----------------------------------------" << endl;

    cart.close();
    prod.close();
    orders.close();
    temp.close();

    remove("products.csv");
    rename("temp.csv", "products.csv");

    ofstream clearCart("cart.txt", ios::trunc);
    clearCart.close();

    cout << "Purchase confirmed! Inventory updated, and cart cleared.\n";
}




void confirmPurchase()
{
    checkout();
}



void searchOrderByUsername(const char* username) {
    ifstream orderFile("orders.txt");
    if (!orderFile.is_open()) {
        cout << "ERROR: Unable to open orders file.\n";
        return;
    }

    char line[200];
    bool found = false;

    while (orderFile.getline(line, 200)) {
        if (strstr(line, username)) {
            cout << line << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No orders found for Username: " << username << endl;
    }

    orderFile.close();
}



void provideFeedback() {
    char username[50];
    cout << "Enter your Username: ";
    cin >> username;

    cout << "Searching your order...\n";
    searchOrderByUsername(username);

    char feedback[200];
    cout << "Please provide your feedback for this order: ";
    cin.ignore(); // To ignore any leftover newline character
    cin.getline(feedback, 200);

    ofstream feedbackFile("feedback.txt", ios::app);
    if (!feedbackFile.is_open()) {
        cout << "ERROR: Unable to open feedback file.\n";
        return;
    }

    // Declare line variable to read file
    char line[200];

    // Count the number of feedback entries
    int feedbackNumber = 1;
    ifstream countFile("feedback.txt");
    while (countFile.getline(line, 200)) {
        feedbackNumber++;
    }
    countFile.close();

    // Write feedback with a number
    feedbackFile << "Feedback #" << feedbackNumber << " for Username: " << username << "\n";
    feedbackFile << "Feedback: " << feedback << "\n";
    feedbackFile << "--------------------------------------------------\n";

    feedbackFile.close();

    cout << "Thank you for your feedback!\n";
}




void Order_History_and_Feedback() 
{
    int choice;
    while (true) {
        cout << "1. Search Order by Username\n";
        cout << "2. Provide Feedback\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            char username[50];
            cout << "Enter your Username to search your order: ";
            cin >> username;
            searchOrderByUsername(username);
        }
        else if (choice == 2) {
            provideFeedback();
        }
        else if (choice == 3) {
            cout << "Exiting...\n";
            break;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}










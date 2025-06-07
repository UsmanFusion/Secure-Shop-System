#include "admin.h"
#include "employee.h"
#include "customer.h"








int main()
{
    
    int choice, choice_for_while=0;
    do
    {
        cout << "---------------------------" << endl;
        cout << "|  Press 1 for Admin       |" << endl;
        cout << "|  Press 2 for Employee    |" << endl;
        cout << "|  Press 3 for Customer    |" << endl;
        cout << "|  Press 0 to Exit         |" << endl;
        cout << "---------------------------" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            admin();
            break;
        }
        case 2:
        {
            employee();
            break;
        }
        case 3:
        {
            customer();
            break;
        }
        case 0:
        {
            return 0;
        }
        default:
        {
            cout << "Invalid input ";
            cout << "do you want to try again ? " << endl;
            cout << "press 0 for exit or press any key to continue" << endl;
            cin >> choice_for_while;
            break;
        }
        }
    } while (choice_for_while != 0);


    return 0;
}
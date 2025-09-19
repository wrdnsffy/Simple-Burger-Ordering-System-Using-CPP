#include <iostream> //handle cin(), cout() function
#include <iomanip>  //setw, setfill, setprecision
#include <limits>   //no limit for error checking
#include <fstream>  //ifstream , ofstream
using namespace std;

// global declaration so all function can access output file stream
ofstream fout;

// structure Menu to store details of burgers and toppings
struct Menu
{
    // Burger Details
    string burger_type[3] = {"Benjo", "Ayam", "Daging"}; // used array datatype to avoid too much variable declared
    const double burger_price[3] = {3.0, 4.0, 4.50};
    int qty_burger[3] = {0, 0, 0}; // assign each burger & topping type to 0 to avoid logical error

    // Toppings Details
    string topping_type[3] = {"Cheese Slices", "Fried Egg", "Extra Patty"};
    const double topping_price[3] = {0.50, 1.00, 2.00};
    int qty_topping[3] = {0, 0, 0};
};

// function prototype (allows program to work even though actual function declared after main function)
void clearInputBuffer();
void MenuAndGetCustomerInfo(string &name, string &address);
void PromptBurgers(Menu &menu, string &choice);
void PromptToppings(Menu &menu, string &choice);
void GetPaymentAndCalculate(Menu menu, string payment_code, string &payment_message, double &total_cost, double &total_cost_after);
void DisplayReceipt(Menu menu, string customer_name, string customer_address, double total_cost_after, string payment, int order_counter);

int main()
{
    Menu menu; // declare variable name "menu" using structure type Menu

    string customer_name, customer_address;
    string choice, payment_code, payment; // string datatype to avoid complications in error checking
    double total_cost = 0, total_cost_after = 0;
    int order_counter = 1;

    fout.open("receipt.txt", ios::app); // open output file and set to append mode(will delete previous entry)

    do
    {
        // Call function to display menu ,get customer information, and display menu
        MenuAndGetCustomerInfo(customer_name, customer_address);

        // Call function to prompt user for burger choices, and quantity
        PromptBurgers(menu, choice);

        // Call function to prompt user for topping choices, and quantity
        PromptToppings(menu, choice);

        // Call function to get payment method and calculate total cost after special condition
        GetPaymentAndCalculate(menu, payment_code, payment, total_cost, total_cost_after);

        // Call function to display receipt
        DisplayReceipt(menu, customer_name, customer_address, total_cost_after, payment, order_counter);
        
        cout << "\nWould you like to order again (y/n)?: ";
        cin >> choice;
        if (choice == "y")
        {
            order_counter++;
        }

        clearInputBuffer();
    } while (choice == "y");

    fout.close(); // close receipt file
    return 0;
}

// function to clear and ignore input to certain condition(no limit of until next line)
void clearInputBuffer()
{
    cin.clear();                                         // ignore error flag
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear previous input until next line
}

// WELCOME AND CUSTOMER INFO DONE BY - DANIEL SYAZLIN
// Call function to display menu ,get customer information, and display menu
void MenuAndGetCustomerInfo(string &name, string &address)
{
    cout << setw(45) << setfill('=') << "" << endl;
    cout << "\t  Welcome to Burger Bites!" << endl;
    cout << setw(45) << setfill('=') << "" << endl;
    cout << setfill(' '); // reset setfill to default (SPACE)

    cout << "\nEnter your full name: ";
    getline(cin, name); // capture full name with spaces

    cout << "\nEnter your full address: ";
    getline(cin, address); // capture full address with spaces

    // menu list consist of burgers and toppings provided
    cout << "\nExplore our burger types and toppings below:" << endl;
    cout << "-----BURGER-----\t------TOPPINGS------" << endl;
    cout << "BENJO     RM3.00\tCHEESE SLICES RM0.50" << endl;
    cout << "AYAM      RM4.00\tFRIED EGG     RM1.00" << endl;
    cout << "DAGING    RM4.50\tEXTRA PATTY   RM2.00" << endl;
    cout << "----------------\t--------------------" << endl;
}

// BURGER SECTION DONE BY - WARDINA SAFFIYA
// Call function to prompt user for burger choices, and quantity
void PromptBurgers(Menu &menu, string &choice)
{
    // Loop through each burger type to prompt user for quantity
    for (int i = 0; i < 3; i++)
    {
        // Execute body first and keep looping if invalid input (y/n)
        do
        {
            cout << "\nWould you like " << menu.burger_type[i] << " Burger (y/n)?: ";
            cin >> choice;

            if (choice != "y" && choice != "n")
            {
                cout << "\nInvalid input! Please enter 'y' or 'n'.";
                clearInputBuffer();
            }
            else if (choice == "y")
            {
                cout << "Enter quantity: ";
                // Immediately check for input quantity validity that detect (non integer, negative number, decimal number)
                while (!(cin >> menu.qty_burger[i]) || menu.qty_burger[i] < 0 || cin.peek() != '\n')
                {
                    cout << "\nInvalid input! Enter quantity: ";
                    clearInputBuffer();
                }
            }
            else if (choice == "n")
            {
                menu.qty_burger[i] = 0;
            }
        } while (choice != "y" && choice != "n");
    }
}

// TOPPING SECTION  & CALCULATION DONE BY - DANISH HARITH
// Call function to prompt user for topping choices, and quantity
void PromptToppings(Menu &menu, string &choice)
{
    // Loop through each topping type to prompt user for quantity
    for (int j = 0; j < 3; j++)
    {
        // Execute body first and keep looping if invalid input (y/n)
        do
        {
            cout << "\nWould you like " << menu.topping_type[j] << " (y/n)?: ";
            cin >> choice;

            if (choice != "y" && choice != "n")
            {
                cout << "\nInvalid input! Please enter 'y' or 'n'.";
            }
            else if (choice == "y")
            {
                cout << "Enter quantity: ";
                // Immediately check for input quantity validity that detect (non integer, negative number, decimal number)
                while (!(cin >> menu.qty_topping[j]) || menu.qty_topping[j] < 0 || cin.peek() != '\n')
                {
                    cout << "\nInvalid input! Enter quantity: ";
                    clearInputBuffer();
                }
            }
            else
            {
                menu.qty_topping[j] = 0;
            }

        } while (choice != "y" && choice != "n");
    }
}

// PAYMENT METHOD DONE BY - DWAYNE
void GetPaymentAndCalculate(Menu menu, string payment_code, string &payment_message, double &total_cost, double &total_cost_after)
{
    // Calculate total cost based on burger and topping quantities
    total_cost = (menu.qty_burger[0] * menu.burger_price[0]) + (menu.qty_burger[1] * menu.burger_price[1]) + (menu.qty_burger[2] * menu.burger_price[2]) +
                 (menu.qty_topping[0] * menu.topping_price[0]) + (menu.qty_topping[1] * menu.topping_price[1]) + (menu.qty_topping[2] * menu.topping_price[2]);

    cout << "\nChoose your method of payment: " << endl;
    cout << "------------" << endl;
    cout << "A CASH" << endl;
    cout << "B QR PAY" << endl;
    cout << "C CARD" << endl;
    cout << "------------" << endl;

    // ask for payment code beforehand and repeat if input error (A, B ,C)
    do
    {
        cout << "\nPayment method code(eg. A): ";
        cin >> payment_code;

        if (payment_code != "A" && payment_code != "B" && payment_code != "C")
        {
            cout << "Invalid Code Entered! Please enter 'A' , 'B' or 'C'.";
        }
        else if (payment_code == "A")
        {
            payment_message = "Your money have been received via cash!\nNo charge or discount offered for your purchase.";
            total_cost_after = total_cost; // cash = no changes
        }
        else if (payment_code == "B")
        {
            payment_message = "Your money have been received via qr pay!\nDiscount 10% have been applied.";
            total_cost_after = total_cost - (0.1 * total_cost); // qr = 10% discount
        }
        else if (payment_code == "C")
        {
            payment_message = "Your money have been received via card!\nAdditional 5% of total cost charged. ";
            total_cost_after = total_cost + (0.05 * total_cost); // card = 5% charge
        }

    } while (payment_code != "A" && payment_code != "B" && payment_code != "C");
}

// RECEIPT DONE BY - SYUKRI FADHLI
void DisplayReceipt(Menu menu, string customer_name, string customer_address, double total_cost_after, string payment, int order_counter)
{
    // terminal output
    cout << "\nTotal Cost     : RM" << fixed << setprecision(2) << total_cost_after << endl; // 2 decimal places
    cout << payment << endl;                                                                 // payment method message
    cout << "\nCheck receipt file to view details" << endl;

    // detailed receipt for every new order displayed in Receipt.txt file
    fout << "\nOrder #" << order_counter;
    fout << "\n============================================" << endl;
    fout << "Customer Name  : " << customer_name << endl;
    fout << "Address        : " << customer_address << endl;

    fout << "\nBURGERS:" << endl; // display burgers ordered
    // loop through each burger type and display quantity
    for (int k = 0; k < 3; k++)
    {
        if (menu.qty_burger[k] > 0) // if quantity 0, dont show
        {
            fout << setw(15) << left << menu.burger_type[k];       // set 15 unit space and align elements to the left
            fout << setw(1) << ": " << menu.qty_burger[k] << endl; // set 1 unit and fill it with ':'
        }
    }

    fout << "\nTOPPINGS:" << endl; // display toppings ordered
    // loop through each topping type and display quantity
    for (int l = 0; l < 3; l++)
    {
        if (menu.qty_topping[l] > 0) // if quantity 0, dont show
        {
            fout << setw(15) << left << menu.topping_type[l];
            fout << setw(1) << ": " << menu.qty_topping[l] << endl;
        }
    }

    fout << "\nTotal Cost     : RM" << fixed << setprecision(2) << total_cost_after << endl; // set final cost to only have 2 decimal point in currency
    fout << payment << endl;                                                                 // payment method message
    fout << "\nThanks for ordering with us! Come again!" << endl;
    fout << "============================================" << endl;
}

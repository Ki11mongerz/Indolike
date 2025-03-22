#include <iostream>
#include <iomanip>
#include <string>
#include <unordered_map>

using namespace std;

double convertCurrency(double amount, const string& toCurrency, const unordered_map<string, double>& rates) {
    return amount / rates.at("INR") * rates.at(toCurrency);
}

int main() {
    unordered_map<string, double> rates = {
        {"INR", 1.0},
        {"USD", 0.012},
        {"EUR", 0.011},
        {"GBP", 0.009},
        {"JPY", 1.65},
        {"AUD", 0.017}
    };

    double amount;
    int choice;

    cout << "Welcome to the Currency Converter!" << endl;
    cout << "You can convert from INR to the following currencies:" << endl;
    cout << "1. USD" << endl;
    cout << "2. EUR" << endl;
    cout << "3. GBP" << endl;
    cout << "4. JPY" << endl;
    cout << "5. AUD" << endl;

    cout << "Enter the amount in INR: ";
    cin >> amount;

    cout << "Select the currency you want to convert to (1-5): ";
    cin >> choice;

    string toCurrency;
    switch (choice) {
        case 1: toCurrency = "USD"; break;
        case 2: toCurrency = "EUR"; break;
        case 3: toCurrency = "GBP"; break;
        case 4: toCurrency = "JPY"; break;
        case 5: toCurrency = "AUD"; break;
        default:
            cout << "Invalid choice." << endl;
            return 1;
    }

    double convertedAmount = convertCurrency(amount, toCurrency, rates);

    cout << fixed << setprecision(2);
    cout << amount << " INR is equal to " << convertedAmount << " " << toCurrency << endl;

    return 0;
}
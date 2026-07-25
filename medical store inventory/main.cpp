#include <bits/stdc++.h>
using namespace std;
#include <ctime>
float total = 0; // global
string getDate()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    string date = to_string(ltm->tm_mday) + "-" +
                  to_string(1 + ltm->tm_mon) + "-" +
                  to_string(1900 + ltm->tm_year);

    return date;
}


// Tablets
void readTablets()
{
    ifstream file("tablets.csv");

    if (!file)
    {
        cout << "Error opening file!\n";
        return;
    }

    string line;

    // Skip header
    getline(file, line);

    cout << "\n-------------------------------------------------------------\n";
    cout << "ID   Name        Dose    Expiry    Price   Stock   Supplier\n";
    cout << "-------------------------------------------------------------\n";

    while (getline(file, line))
    {
        stringstream ss(line);
        string id, name, dose, expiry, price, stock, supplier;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, dose, ',');
        getline(ss, expiry, ',');
        getline(ss, price, ',');
        getline(ss, stock, ',');
        getline(ss, supplier, ',');

        cout << id << "   "
             << name << "   "
             << dose << "   "
             << expiry << "   "
             << price << "   "
             << stock << "   "
             << supplier << endl;
    }
    file.close();
}

void addTablet()
{
    ofstream file("tablets.csv", ios::app); // append mode

    if (!file)
    {
        cout << "Error opening file!\n";
        return;
    }

    string id, name, dose, expiry, price, stock, supplier;

    cout << "\nEnter ID: ";
    cin >> id;

    cout << "Enter Name: ";
    // cin >> name;
    getline(cin >> ws, name);

    cout << "Enter Dose: ";
    cin >> dose;

    cout << "Enter Expiry: ";
    cin >> expiry;

    cout << "Enter Price: ";
    cin >> price;

    cout << "Enter Stock: ";
    cin >> stock;

    cout << "Enter Supplier: ";
    cin >> supplier;

    // write to CSV
    file << "\n"
         << id << ","
         << name << ","
         << dose << ","
         << expiry << ","
         << price << ","
         << stock << ","
         << supplier;

    file.close();
}

void searchTablet()
{
    ifstream file("tablets.csv");

    if (!file)
    {
        cout << "Error opening file!\n";
        return;
    }

    string searchName;
    cout << "\nEnter medicine name to search: ";
    // cin >> searchName;
    // getline(cin,searchName);
    getline(cin >> ws, searchName);

    string line;
    bool found = false;

    getline(file, line); // skip header

    while (getline(file, line))
    {
        stringstream ss(line);
        string id, name, dose, expiry, price, stock, supplier;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, dose, ',');
        getline(ss, expiry, ',');
        getline(ss, price, ',');
        getline(ss, stock, ',');
        getline(ss, supplier, ',');

        if (name == searchName)
        {
            cout << "\n✅ Medicine Found:\n";
            cout << id << " " << name << " " << dose << " "
                 << expiry << " " << price << " "
                 << stock << " " << supplier << endl;

            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\n❌ Medicine not found!\n";
    }

    file.close();
}

void updateTablet()
{
    ifstream file("tablets.csv");
    ofstream temp("temp.csv");

    if (!file || !temp)
    {
        cout << "Error opening file!\n";
        return;
    }

    string searchName;
    cout << "\nEnter Medicine Name to update: ";
    // cin >> searchName;
    // getline(cin,searchName);
    getline(cin >> ws, searchName);

    string line;
    bool found = false;

    getline(file, line);  // read header
    temp << line << "\n"; // copy header

    while (getline(file, line))
    {
        stringstream ss(line);
        string id, name, dose, expiry, price, stock, supplier;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, dose, ',');
        getline(ss, expiry, ',');
        getline(ss, price, ',');
        getline(ss, stock, ',');
        getline(ss, supplier, ',');

        if (name == searchName)
        {
            found = true;

            cout << "\nEnter new Price: ";
            cin >> price;

            cout << "Enter new Stock: ";
            cin >> stock;

            cout << "\n✅ Record Updated!\n";
        }

        temp << id << ","
             << name << ","
             << dose << ","
             << expiry << ","
             << price << ","
             << stock << ","
             << supplier << "\n";
    }

    file.close();
    temp.close();

    remove("tablets.csv");
    rename("temp.csv", "tablets.csv");

    if (!found)
    {
        cout << "\n❌ Medicine not found!\n";
    }
}

void deleteTablet()
{
    ifstream file("tablets.csv");
    ofstream temp("temp.csv");

    if (!file || !temp)
    {
        cout << "Error opening file!\n";
        return;
    }

    string searchName;
    cout << "\nEnter Medicine Name to delete: ";
    // cin >> searchName;
    // getline(cin,searchName);
    getline(cin >> ws, searchName);

    string line;
    bool found = false;

    getline(file, line);  // read header
    temp << line << "\n"; // copy header

    while (getline(file, line))
    {
        stringstream ss(line);
        string id, name, dose, expiry, price, stock, supplier;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, dose, ',');
        getline(ss, expiry, ',');
        getline(ss, price, ',');
        getline(ss, stock, ',');
        getline(ss, supplier, ',');

        if (name == searchName)
        {
            found = true;
            cout << "\n🗑️ Deleting: " << name << endl;
            continue; // ❌ skip writing (delete)
        }

        // write remaining records
        temp << id << ","
             << name << ","
             << dose << ","
             << expiry << ","
             << price << ","
             << stock << ","
             << supplier << "\n";
    }

    file.close();
    temp.close();

    remove("tablets.csv");
    rename("temp.csv", "tablets.csv");

    if (found)
        cout << "\n✅ Medicine deleted successfully!\n";
    else
        cout << "\n❌ Medicine not found!\n";
}

void checkLowStock()
{
    ifstream file("tablets.csv");

    if (!file)
    {
        cout << "Error opening file!\n";
        return;
    }

    string line;
    bool found = false;

    int threshold;
    cout << "Enter low stock limit: ";
    cin >> threshold;

    getline(file, line); // skip header

    cout << "\n⚠️ LOW STOCK MEDICINES:\n";
    cout << "----------------------------------------\n";
    cout << "ID   Name        Stock\n";
    cout << "----------------------------------------\n";

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        vector<string> cols;
        string value;

        while (getline(ss, value, ','))
            cols.push_back(value);

        // ✅ Check correct column size
        if (cols.size() < 7)
            continue;

        int stock = 0;

        // ✅ Safe conversion
        try
        {
            stock = stoi(cols[5]);
        }
        catch (...)
        {
            continue;
        }

        if (stock < threshold)
        {
            cout << cols[0] << "   " << cols[1] << "   " << stock << endl;
            found = true;
        }
    }

    if (!found)
        cout << "No low stock medicines 👍\n";

    file.close();
}
// Injections
void readInjections()
{
    ifstream file("injections.csv");

    if (!file)
    {
        cout << "Error opening file!\n";
        return;
    }

    string line;

    // Skip header
    getline(file, line);

    cout << "\n--------------------------------------------------------------------------\n";
    cout << "ID   Name        Volume   Type    Expiry    Price   Stock   Supplier\n";
    cout << "--------------------------------------------------------------------------\n";

    while (getline(file, line))
    {
        stringstream ss(line);
        string id, name, volume, type, expiry, price, stock, supplier;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, volume, ',');
        getline(ss, type, ',');
        getline(ss, expiry, ',');
        getline(ss, price, ',');
        getline(ss, stock, ',');
        getline(ss, supplier, ',');

        cout << id << "   "
             << name << "   "
             << volume << "   "
             << type << "   "
             << expiry << "   "
             << price << "   "
             << stock << "   "
             << supplier << endl;
    }
    file.close();
}

void addInjection()
{
    ofstream file("injections.csv", ios::app);

    if (!file)
    {
        cout << "Error opening file!\n";
        return;
    }

    string id, name, volume, type, expiry, price, stock, supplier;

    cout << "\nEnter ID: ";
    cin >> id;

    cout << "Enter Name: ";
    // cin >> name;
    // getline(cin,name);
    getline(cin >> ws, name);

    cout << "Enter Volume: ";
    cin >> volume;

    cout << "Enter Type(S/M/L): ";
    cin >> type;

    cout << "Enter Expiry: ";
    cin >> expiry;

    cout << "Enter Price: ";
    cin >> price;

    cout << "Enter Stock: ";
    cin >> stock;

    cout << "Enter Supplier: ";
    cin >> supplier;

    file << "\n"
         << id << ","
         << name << ","
         << volume << ","
         << type << ","
         << expiry << ","
         << price << ","
         << stock << ","
         << supplier;

    file.close();
}

void searchInjection()
{
    ifstream file("injections.csv");

    if (!file)
    {
        cout << "Error opening file!\n";
        return;
    }

    string searchName;
    cout << "\nEnter medicine name to search: ";
    // cin >> searchName;
    // getline(cin,searchName);
    getline(cin >> ws, searchName);

    string line;
    bool found = false;

    getline(file, line); // skip header

    while (getline(file, line))
    {
        stringstream ss(line);
        string id, name, volume, type, expiry, price, stock, supplier;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, volume, ',');
        getline(ss, type, ',');
        getline(ss, expiry, ',');
        getline(ss, price, ',');
        getline(ss, stock, ',');
        getline(ss, supplier, ',');

        if (name == searchName)
        {
            cout << "\n✅ Medicine Found:\n";
            cout << id << " " << name << " " << volume << " "
                 << type << " " << expiry << " "
                 << price << " " << stock << " "
                 << supplier << endl;

            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\n❌ Medicine not found!\n";
    }

    file.close();
}

void updateInjection()
{
    ifstream file("injections.csv");
    ofstream temp("temp.csv");

    if (!file || !temp)
    {
        cout << "Error opening file!\n";
        return;
    }

    string searchName;
    cout << "\nEnter Medicine Name to update: ";
    // cin >> searchName;
    // getline(cin,searchName);
    getline(cin >> ws, searchName);

    string line;
    bool found = false;

    getline(file, line);
    temp << line << "\n";

    while (getline(file, line))
    {
        stringstream ss(line);
        string id, name, volume, type, expiry, price, stock, supplier;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, volume, ',');
        getline(ss, type, ',');
        getline(ss, expiry, ',');
        getline(ss, price, ',');
        getline(ss, stock, ',');
        getline(ss, supplier, ',');

        if (name == searchName)
        {
            found = true;

            cout << "\nEnter new Price: ";
            cin >> price;

            cout << "Enter new Stock: ";
            cin >> stock;

            cout << "\n✅ Record Updated!\n";
        }

        temp << id << ","
             << name << ","
             << volume << ","
             << type << ","
             << expiry << ","
             << price << ","
             << stock << ","
             << supplier << "\n";
    }

    file.close();
    temp.close();

    remove("injections.csv");
    rename("temp.csv", "injections.csv");

    if (!found)
    {
        cout << "\n❌ Medicine not found!\n";
    }
}

void deleteInjection()
{
    ifstream file("injections.csv");
    ofstream temp("temp.csv");

    if (!file || !temp)
    {
        cout << "Error opening file!\n";
        return;
    }

    string searchName;
    cout << "\nEnter Medicine Name to delete: ";
    // cin >> searchName;
    // getline(cin,searchName);
    getline(cin >> ws, searchName);

    string line;
    bool found = false;

    getline(file, line);
    temp << line << "\n";

    while (getline(file, line))
    {
        stringstream ss(line);
        string id, name, volume, type, expiry, price, stock, supplier;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, volume, ',');
        getline(ss, type, ',');
        getline(ss, expiry, ',');
        getline(ss, price, ',');
        getline(ss, stock, ',');
        getline(ss, supplier, ',');

        if (name == searchName)
        {
            found = true;
            cout << "\n🗑️ Deleting: " << name << endl;
            continue;
        }

        temp << id << ","
             << name << ","
             << volume << ","
             << type << ","
             << expiry << ","
             << price << ","
             << stock << ","
             << supplier << "\n";
    }

    file.close();
    temp.close();

    remove("injections.csv");
    rename("temp.csv", "injections.csv");

    if (found)
        cout << "\n✅ Medicine deleted successfully!\n";
    else
        cout << "\n❌ Medicine not found!\n";
}
void checkLowStockInjection()
{
    ifstream file("injections.csv");

    if (!file)
    {
        cout << "Error opening file!\n";
        return;
    }

    string line;
    bool found = false;

    int threshold;
    cout << "Enter low stock limit: ";
    cin >> threshold;

    getline(file, line); // skip header

    cout << "\n⚠️ LOW STOCK INJECTIONS:\n";
    cout << "----------------------------------------\n";
    cout << "ID   Name        Stock\n";
    cout << "----------------------------------------\n";

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        vector<string> cols;
        string value;

        while (getline(ss, value, ','))
            cols.push_back(value);

        // ✅ Must be 8 columns
        if (cols.size() < 8)
            continue;

        int stock = 0;

        try
        {
            stock = stoi(cols[6]);
        }
        catch (...)
        {
            continue;
        }

        if (stock < threshold)
        {
            cout << cols[0] << "   " << cols[1] << "   " << stock << endl;
            found = true;
        }
    }

    if (!found)
        cout << "No low stock injections 👍\n";

    file.close();
}

// Syrups

void readSyrups()
{
    ifstream file("syrups.csv");

    if (!file)
    {
        cout << "Error opening file!\n";
        return;
    }

    string line;

    // Skip header
    getline(file, line);

    cout << "\n-----------------------------------------------------------------\n";
    cout << "ID   Name        Quantity   Expiry    Price   Stock   Supplier\n";
    cout << "-----------------------------------------------------------------\n";

    while (getline(file, line))
    {
        stringstream ss(line);
        string id, name, quantity, expiry, price, stock, supplier;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, quantity, ',');
        getline(ss, expiry, ',');
        getline(ss, price, ',');
        getline(ss, stock, ',');
        getline(ss, supplier, ',');

        cout << id << "   "
             << name << "   "
             << quantity << "   "
             << expiry << "   "
             << price << "   "
             << stock << "   "
             << supplier << endl;
    }
    file.close();
}
void addSyrup()
{
    ofstream file("syrups.csv", ios::app);

    if (!file)
    {
        cout << "Error opening file!\n";
        return;
    }

    string id, name, quantity, expiry, price, stock, supplier;

    cout << "\nEnter ID: ";
    cin >> id;

    cout << "Enter Name: ";
    // cin >> name;
    // getline(cin,name);
    getline(cin >> ws, name);

    cout << "Enter Quantity: ";
    cin >> quantity;

    cout << "Enter Expiry: ";
    cin >> expiry;

    cout << "Enter Price: ";
    cin >> price;

    cout << "Enter Stock: ";
    cin >> stock;

    cout << "Enter Supplier: ";
    cin >> supplier;

    file << "\n"
         << id << ","
         << name << ","
         << quantity << ","
         << expiry << ","
         << price << ","
         << stock << ","
         << supplier;

    file.close();
}

void searchSyrup()
{
    ifstream file("syrups.csv");

    if (!file)
    {
        cout << "Error opening file!\n";
        return;
    }

    string searchName;
    cout << "\nEnter medicine name to search: ";
    // cin >> searchName;
    // getline(cin,searchName);
    getline(cin >> ws, searchName);


    string line;
    bool found = false;

    getline(file, line); // skip header

    while (getline(file, line))
    {
        stringstream ss(line);
        string id, name, quantity, expiry, price, stock, supplier;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, quantity, ',');
        getline(ss, expiry, ',');
        getline(ss, price, ',');
        getline(ss, stock, ',');
        getline(ss, supplier, ',');

        if (name == searchName)
        {
            cout << "\n✅ Medicine Found:\n";
            cout << id << " " << name << " " << quantity << " "
                 << expiry << " " << price << " "
                 << stock << " " << supplier << endl;

            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\n❌ Medicine not found!\n";
    }

    file.close();
}
void updateSyrup()
{
    ifstream file("syrups.csv");
    ofstream temp("temp.csv");

    if (!file || !temp)
    {
        cout << "Error opening file!\n";
        return;
    }

    string searchName;
    cout << "\nEnter Medicine Name to update: ";
    // cin >> searchName;
    // getline(cin,searchName);
    getline(cin >> ws, searchName);


    string line;
    bool found = false;

    getline(file, line);
    temp << line << "\n";

    while (getline(file, line))
    {
        stringstream ss(line);
        string id, name, quantity, expiry, price, stock, supplier;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, quantity, ',');
        getline(ss, expiry, ',');
        getline(ss, price, ',');
        getline(ss, stock, ',');
        getline(ss, supplier, ',');

        if (name == searchName)
        {
            found = true;

            cout << "\nEnter new Price: ";
            cin >> price;

            cout << "Enter new Stock: ";
            cin >> stock;

            cout << "\n✅ Record Updated!\n";
        }

        temp << id << ","
             << name << ","
             << quantity << ","
             << expiry << ","
             << price << ","
             << stock << ","
             << supplier << "\n";
    }

    file.close();
    temp.close();

    remove("syrups.csv");
    rename("temp.csv", "syrups.csv");

    if (!found)
    {
        cout << "\n❌ Medicine not found!\n";
    }
}
void deleteSyrup()
{
    ifstream file("syrups.csv");
    ofstream temp("temp.csv");

    if (!file || !temp)
    {
        cout << "Error opening file!\n";
        return;
    }

    string searchName;
    cout << "\nEnter Medicine Name to delete: ";
    // cin >> searchName;
    // getline(cin,searchName);
    getline(cin >> ws, searchName);

    string line;
    bool found = false;

    getline(file, line);
    temp << line << "\n";

    while (getline(file, line))
    {
        stringstream ss(line);
        string id, name, quantity, expiry, price, stock, supplier;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, quantity, ',');
        getline(ss, expiry, ',');
        getline(ss, price, ',');
        getline(ss, stock, ',');
        getline(ss, supplier, ',');

        if (name == searchName)
        {
            found = true;
            cout << "\n🗑️ Deleting: " << name << endl;
            continue;
        }

        temp << id << ","
             << name << ","
             << quantity << ","
             << expiry << ","
             << price << ","
             << stock << ","
             << supplier << "\n";
    }

    file.close();
    temp.close();

    remove("syrups.csv");
    rename("temp.csv", "syrups.csv");

    if (found)
        cout << "\n✅ Medicine deleted successfully!\n";
    else
        cout << "\n❌ Medicine not found!\n";
}
void checkLowStockSyrup()
{
    ifstream file("syrups.csv");

    if (!file)
    {
        cout << "Error opening file!\n";
        return;
    }

    string line;
    bool found = false;

    int threshold;
    cout << "Enter low stock limit: ";
    cin >> threshold;

    getline(file, line); // skip header

    cout << "\n⚠️ LOW STOCK SYRUPS:\n";
    cout << "----------------------------------------\n";
    cout << "ID   Name        Stock\n";
    cout << "----------------------------------------\n";

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        vector<string> cols;
        string value;

        while (getline(ss, value, ','))
            cols.push_back(value);

        if (cols.size() < 7)
            continue;

        int stock = 0;

        try
        {
            stock = stoi(cols[5]);
        }
        catch (...)
        {
            continue;
        }

        if (stock < threshold)
        {
            cout << cols[0] << "   " << cols[1] << "   " << stock << endl;
            found = true;
        }
    }

    if (!found)
        cout << "No low stock syrups 👍\n";

    file.close();
}
// Miscilinous
#include <limits> // for numeric_limits

bool processFile(string filename, string searchName, int qty)
{
    ifstream file(filename);
    ofstream temp("temp.csv");
    ofstream sales("sales.csv", ios::app);

    if (!file || !temp || !sales)
    {
        cout << "File error!\n";
        return false;
    }

    string line;
    bool found = false;
    string today = getDate();

    getline(file, line); // header
    temp << line << "\n";

    while (getline(file, line))
    {
        stringstream ss(line);
        vector<string> cols;
        string value;

        while (getline(ss, value, ','))
        {
            cols.push_back(value);
        }

        // 🔴 Skip bad/corrupt rows
        if (cols.size() < 7)
            continue;

        string name = cols[1];
        float price = 0;
        int stock = 0;
        string supplier = cols.back();

        // ✅ FIX: correct column positions
        if (cols.size() == 7) // tablets or syrups
        {
            price = stof(cols[4]);
            stock = stoi(cols[5]);
        }
        else if (cols.size() == 8) // injections
        {
            price = stof(cols[5]);
            stock = stoi(cols[6]);
        }
        else
        {
            continue; // unknown format
        }

        if (name == searchName)
        {
            if (stock >= qty)
            {
                found = true;

                float cost = price * qty;
                total += cost;

                stock -= qty;

                cout << name << "  " << qty << " x " << price
                     << " = " << cost << endl;

                // ✅ FIX: safe newline handling
                sales.seekp(0, ios::end);
                if (sales.tellp() != 0)
                    sales << "\n";

                sales << name << "," << price << "," << qty << "," << today << "," << supplier;

                // ✅ FIX: correct stock update
                if (cols.size() == 7)
                    cols[5] = to_string(stock);
                else if (cols.size() == 8)
                    cols[6] = to_string(stock);
            }
            else
            {
                cout << "⚠️ Not enough stock for " << name << endl;
                found = true;
            }
        }

        // Write back row
        for (int i = 0; i < cols.size(); i++)
        {
            temp << cols[i];
            if (i != cols.size() - 1)
                temp << ",";
        }
        temp << "\n";
    }

    file.close();
    temp.close();
    sales.close();

    remove(filename.c_str());
    rename("temp.csv", filename.c_str());

    return found;
}

void billing()
{
    string name;
    int qty;
    char more;
    total = 0;

    cout << "\n----------- BILL -----------\n";

    do
    {
        cout << "\nEnter medicine name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ✅ FIX
        getline(cin, name);

        cout << "Enter quantity: ";
        cin >> qty;

        bool found = false;

        if (processFile("tablets.csv", name, qty))
            found = true;
        else if (processFile("syrups.csv", name, qty))
            found = true;
        else if (processFile("injections.csv", name, qty))
            found = true;

        if (!found)
        {
            cout << "❌ Not found or insufficient stock!\n";
        }

        cout << "\nAdd more? (y/n): ";
        cin >> more;

    } while (more == 'y' || more == 'Y');

    cout << "\nTOTAL = " << total << endl;
}
string getDate();
#include <limits>

void salesReport()
{
    ifstream file("sales.csv");

    if (!file)
    {
        cout << "Error opening sales file!\n";
        return;
    }

    int option;
    cout << "\n------ SALES REPORT ------";
    cout << "\n1. View All Sales";
    cout << "\n2. View Sales by Date";
    cout << "\n3. View Today's Sales";
    cout << "\nEnter choice: ";
    cin >> option;

    if (option < 1 || option > 3)
    {
        cout << "❌ Invalid option!\n";
        return;
    }

    string filterDate = "";

    if (option == 2)
    {
        cout << "Enter date (dd-mm-yyyy): ";
        cin >> filterDate;
    }
    else if (option == 3)
    {
        filterDate = getDate();
    }

    string line;
    float totalSales = 0;

    // ✅ Skip header
    getline(file, line);

    cout << "\n---------------------------------------------\n";
    cout << "Name\tPrice\tQty\tDate\t\tSupplier\n";
    cout << "---------------------------------------------\n";

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        string name, priceStr, qtyStr, date, supplier;

        getline(ss, name, ',');
        getline(ss, priceStr, ',');
        getline(ss, qtyStr, ',');
        getline(ss, date, ',');
        getline(ss, supplier); // last column

        // ✅ Filter logic
        if (!filterDate.empty() && date != filterDate)
            continue;

        try
        {
            float price = stof(priceStr);
            int qty = stoi(qtyStr);

            float total = price * qty;
            totalSales += total;

            cout << name << "\t"
                 << price << "\t"
                 << qty << "\t"
                 << date << "\t"
                 << supplier << endl;
        }
        catch (...)
        {
            cout << "⚠️ Skipping corrupted row\n";
        }
    }

    cout << "---------------------------------------------\n";
    cout << "Total Sales Amount = " << totalSales << endl;
    cout << "---------------------------------------------\n";

    file.close();

    // ✅ Proper pause
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

class Medicine
{
public:
    int choice, type;

    void showMenu()
    {
        cout << "==========================================================================" << endl;
        cout << "              MEDICAL STORE INVENTORY MANAGEMENT SYSTEM" << endl;
        cout << "==========================================================================" << endl;

        cout << "\n1.  View All Medicines";
        cout << "\n2.  Add New Medicine";
        cout << "\n3.  Search Medicine";
        cout << "\n4.  Update Medicine";
        cout << "\n5.  Delete Medicine";
        cout << "\n6.  Check Low Stock";
        cout << "\n7.  Billing / Sales";
        cout << "\n8.  Sales Report";
        cout << "\n9.  Supplier Management";
        cout << "\n10. Exit";

        cout << "\n\nEnter your choice: ";
    }

    void getInput()
    {
        cin >> choice;

        if (choice <= 0 || choice > 10)
        {
            cout << "\n❌ Invalid Choice!\n";
            return;
        }

        if (choice >= 1 && choice <= 6)
        {
            cout << "\n1. Tablets\n2. Injections\n3. Syrups\nEnter type: ";
            cin >> type;
        }
    }
};
class Tablets : public Medicine
{
public:
    void process()
    {
        if (type != 1)
            return;

        switch (choice)
        {
        case 1:
            readTablets();
            break;
        case 2:
            addTablet();
            break;
        case 3:
            searchTablet();
            break;
        case 4:
            updateTablet();
            break;
        case 5:
            deleteTablet();
            break;
        case 6:
            checkLowStock();
            break;
        }
    }
};
class Injections : public Medicine
{
public:
    void process()
    {
        if (type != 2)
            return;

        switch (choice)
        {
        case 1:
            readInjections();
            break;
        case 2:
            addInjection();
            break;
        case 3:
            searchInjection();
            break;
        case 4:
            updateInjection();
            break;
        case 5:
            deleteInjection();
            break;
        case 6:
            checkLowStockInjection();
            break;
        }
    }
};
class Syrups : public Medicine
{
public:
    void process()
    {
        if (type != 3)
            return;

        switch (choice)
        {
        case 1:
            readSyrups();
            break;
        case 2:
            addSyrup();
            break;
        case 3:
            searchSyrup();
            break;
        case 4:
            updateSyrup();
            break;
        case 5:
            deleteSyrup();
            break;
        case 6:
            checkLowStockSyrup();
            break;
        }
    }
};
int main()
{
    Medicine med;
    Tablets tab;
    Injections inj;
    Syrups syr;

    while (true)
    {
        med.showMenu();
        med.getInput();

        if (med.choice == 10)
        {
            cout << "\nExiting...\n";
            break;
        }

        // pass values to all objects
        tab.choice = inj.choice = syr.choice = med.choice;
        tab.type = inj.type = syr.type = med.type;

        // process type-based logic
        tab.process();
        inj.process();
        syr.process();

        // independent features
        if (med.choice == 7)
            billing();
        else if (med.choice == 8)
            salesReport();

        cout << "\nPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    return 0;
}
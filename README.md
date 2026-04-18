# 🏥 CLI-Based Medical Store Inventory System

## 📌 Overview

The **CLI-Based Medical Store Inventory System** is a command-line application developed to efficiently manage a medical store's day-to-day operations. It allows users to handle inventory, billing, sales tracking, and supplier management through a simple text-based interface.

This system also includes an **authentication module**, ensuring that only authorized users can access and manage their inventory securely.

---

## 🚀 Features

### 🔐 User Authentication System

* Secure login using **username and password**
* Restricts unauthorized access
* Each user can manage their own inventory securely

### 💊 Inventory Management

* Add new medicines (tablets, syrups, injections)
* Update existing stock details
* Delete expired or unwanted medicines
* View complete inventory records

### 🔍 Search Functionality

* Search medicines by name
* Quickly retrieve details like price, stock, and expiry

### 💵 Billing System

* Generate bills for customer purchases
* Automatically updates stock after each sale
* Stores billing data in records

### 📊 Sales Reporting

* View all sales transactions
* Analyze sales data from stored records

### 🚚 Supplier Management

* Store supplier details
* Track which supplier provides which medicines

---

## 🛠️ Technologies Used

* **Language:** C++
* **Interface:** Command Line Interface (CLI)
* **File Handling:** CSV files for data storage

---

## 📁 File Structure

```
├── tablets.csv        # Tablet records
├── syrups.csv         # Syrup records
├── injections.csv     # Injection records
├── sales.csv          # Sales and billing records
├── suppliers.csv      # Supplier details
├── users.csv          # User authentication data
├── main.cpp           # Main program file
```

---

## ⚙️ How It Works

1. **User Login**

   * User enters username and password
   * System verifies credentials from `users.csv`

2. **Menu-Driven CLI**

   * User selects operations from menu options
   * Example:

     ```
     1. Add Medicine
     2. Search Medicine
     3. Update Stock
     4. Billing
     5. Sales Report
     6. Supplier Management
     7. Exit
     ```

3. **Data Handling**

   * All data is stored and retrieved using CSV files
   * Real-time updates ensure consistency

4. **Billing Process**

   * User selects medicines and quantity
   * Total bill is calculated
   * Stock is reduced automatically
   * Sale is recorded in `sales.csv`

---

## 🔐 Authentication Flow

* User credentials stored in `users.csv`
* Login required before accessing system
* Ensures **data privacy and restricted access**

---

## ▶️ How to Run

1. Compile the program:

   ```
   g++ main.cpp -o medical_store
   ```

2. Run the executable:

   ```
   ./medical_store
   ```

3. Login with valid credentials to start using the system

---

## 📈 Future Enhancements

* Password encryption for better security
* Role-based access (Admin/User)
* GUI-based version
* Database integration (MySQL)
* Expiry alerts for medicines

---

## 🤝 Contribution

Feel free to fork this repository and improve the system by adding new features or optimizing existing ones.

---

## 📄 License

This project is open-source and available under the **MIT License**.

---

## 💡 Conclusion

This project demonstrates how a real-world medical store can be managed using a simple yet effective CLI-based system. With added authentication, it ensures both usability and security, making it a practical solution for small-scale inventory management.

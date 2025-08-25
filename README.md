# Contact Book (C++)

A console-based **Contact Book** implemented in C++ using a **self-referential structure (linked list)**.  
The program allows you to **store, search, update, and delete contacts**, while automatically maintaining them in **alphabetical order**.  
Contact data is saved to a file for persistence.

---

## **Features**
- **Add new contacts** (stored in alphabetical order by name)
- **Search contacts** by name
- **Update existing contacts**
- **Delete contacts**
- **Display all contacts** in alphabetical order
- **Persistent storage** (save and load from file)

---

## **Tech Stack**
- Language: **C++ (Standard Library only)**
- Data structures: **Self-referential structure (linked list)**
- File handling: **<fstream> standard library**
- No external dependencies

---

## **Getting Started**

### **1. Clone the repository**
```bash
git clone https://github.com/<your-username>/contact-book.git
cd contact-book
2. Compile the program
Use any C++ compiler:

bash
Copy
Edit
g++ contact_book.cpp -o contact_book
3. Run the program
bash
Copy
Edit
./contact_book
Menu Options
Add new contact

Display all contacts

Search for a contact

Update a contact

Delete a contact

Exit

How It Works
Adding a contact inserts it into the linked list in sorted order (by name).

Searching traverses the list and finds contacts efficiently.

Updating modifies details without breaking alphabetical order.

Deleting removes the node from the linked list.

File operations ensure that your contact list is loaded at startup and saved when the program exits.


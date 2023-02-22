#include <bits/stdc++.h>
#include<fstream>
using namespace std;
class Text_Editor
{
private:
    string text;
    int size;
    stack<string> undoStack;
    stack<string> redoStack;

public:
    // Create storage for data
    Text_Editor()
    {
        this->text = "";
        size = 0;
    }

    // returns text
    string getText()
    {
        return this->text;
    }

    // Update text with input data;
    void setText(string data)
    {
        this->text = data;
    }

    // return length of the text
    int getLength()
    {
        return this->size;
    }
    // Append data
    void append(string newText)
    {
        undoStack.push(this->text);
        this->text += newText;
        this->size = this->text.length();
        cout << "Data appended" << endl;
    }

    // Insert data
    void insert(int pos, string newText)
    {
        if (pos > this->size)
        {
            // cout << this->size << " " << pos << endl;
            cout << "Warning: Wrong Position-Data Not Inserted" << endl;
            return;
        }
        undoStack.push(text);
        this->text = text.substr(0, pos) + newText + text.substr(pos);
        this->size = this->text.length();
        cout << "Data Inserted" << endl;
    }

    // Update data
    void update(int pos, int length, string newText)
    {
        if (pos > this->size)
        {
            cout << this->size<< " " << pos << endl;
            cout << "Warning: Wrong Position-Data Not Updated" << endl;
            return;
        }
        undoStack.push(this->text);
        this->text = text.substr(0, pos) + newText + text.substr(pos + length);
        this->size = this->text.length();
        cout << "Data Updated" << endl;
    }

    // Search data
    int search(string searchText)
    {
        int pos = text.find(searchText);
        if (pos != string::npos)
        {
            cout << "Found " << searchText << " at position: " << pos<< endl;
            return pos;
        }
        else
        {
            cout << "Text not found." << endl;
            return -1;
        }
    }

    // Delete data
    void deleteData(int pos, int length)
    {
        undoStack.push(text);
        text = text.substr(0, pos) + text.substr(pos + length);
        this->size = this->text.length();    
    }

    // Display data on console
    void display()
    {
        cout<<"-------------------------------------------"<<endl;
        cout << text << endl;
        cout<<"-------------------------------------------"<<endl;
    }

    // Undo operation
    void undo()
    {
        if (!undoStack.empty())
        {
            redoStack.push(text);
            text = undoStack.top();
            undoStack.pop();
            this->size = this->text.length();
        }
        else
        {
            cout << "No more undo operations left." << endl;
        }
    }

    // Redo operation
    void redo()
    {
        if (!redoStack.empty())
        {
            undoStack.push(text);
            text = redoStack.top();
            redoStack.pop();
            this->size = this->text.length();
        }
        else
        {
            cout << "No more redo operations left." << endl;
        }
    }

    // Save data in permanent storage
    void save()
    {
        // Implementation of saving the data to a file
        ofstream file;
        string name;
        cout<<"Enter the name of your file"<<endl;
        cin.ignore();
        getline(cin,name);
        name+=".txt";
        file.open(name);
        file<<this->text;
        file.close();
        cout<<"File Saved"<<endl;
    }
};

int main()
{
    Text_Editor *editor;
    while (true)
    {
        // system("cls");
        cout << "*******************************************" << endl;
        cout << "Menu for Text editor in C++:" << endl;
        cout << "1. Create storage for your data" << endl;
        cout << "2. Append Data" << endl;
        cout << "3. Insert Data" << endl;
        cout << "4. Update Data" << endl;
        cout << "5. Search Data" << endl;
        cout << "6. Delete data" << endl;
        cout << "7. Display Data on console" << endl;
        cout << "8. Undo operation" << endl;
        cout << "9. Redo operation" << endl;
        cout << "10. Save data in permanent storage" << endl;
        cout << "11.Exit" << endl;
        cout << "*******************************************" << endl;
        cout << "Enter Your Choice" << endl;
        int ch;
        cin >> ch;

        if (ch == 1) // Create New Storage
        {
            editor = new Text_Editor();
            cout << "New Text Storage Created" << endl;
        }
        else if (ch == 2) // Append Data
        {
            string data;
            cin.ignore();
            cout << "Enter Data to append in the file" << endl;
            getline(cin, data);
            editor->append(data);
        }
        else if (ch == 3) // Insert Data
        {
            int pos;
            string data;
            cout << "Enter position to insert data" << endl;
            cin >> pos;
            cout << "Enter Data to insert in the Text" << endl;
            cin.ignore();
            getline(cin, data);
            editor->insert(pos, data);
        }
        else if (ch == 4) // Update Data
        {
            int pos, length;
            string data;

            cout << "Enter position to update data" << endl;
            cin >> pos;
            cout << "Enter length of data to  be updated" << endl;
            cin >> length;
            cout << "Enter the new data" << endl;
            cin.ignore();
            getline(cin, data);
            editor->update(pos, length, data);
        }
        else if (ch == 5) // Search Data
        {
            string data;
            cout << "Enter the data to search" << endl;
            cin.ignore();
            getline(cin,data);
            editor->search(data);
        }
        else if (ch == 6) // Delete Data
        {
            int pos, length;
            cout << "Enter position to delete data" << endl;
            cin >> pos;
            cout << "Enter length of data to  be deleted" << endl;
            cin >> length;
            editor->deleteData(pos, length);
        }
        else if (ch == 7) // Display Data on Console
        {
            editor->display();
        }
        else if (ch == 8) // Undo Operation
        {
            editor->undo();
        }
        else if (ch == 9) // Redo Operation
        {
            editor->redo();
        }
        else if (ch == 10) // Save Data in Permanent Storage
        {
            editor->save();
        }
        else if (ch == 11) // Exit
        {
            break;
        }
        else
        {
            cout << "Invalid Input" << endl;
        }
    }

    return 0;
}
#include <bits/stdc++.h>
#include<fstream>
using namespace std;
struct Node{
    string data;
    struct Node *next;
};

class Text_Editor
{
private:
    Node *head;
    stack<Node *> undoStack;
    stack<Node *> redoStack;

public:
    // Create storage for data
    Text_Editor()
    {
        head=NULL;


    }
    Node* CopyList()
    {
        Node *newlist=NULL,*temp=head,*l;
        while(temp!=NULL)
        {

            Node *newnode=new Node();
            newnode->data=temp->data;
            newnode->next=NULL;
            if(newlist==NULL)
            {
                newlist=newnode;
                l=newnode;
            }
            else{
                l->next=newnode;
                l=newnode;

            }
            temp=temp->next;
            
        }
        return newlist;


    }
    void append(string word)
    {
        undoStack.push(CopyList());
        Node *temp=head;
        Node *newnode=new Node();
        newnode->data=word;
        newnode->next=NULL;
        if(head==NULL)
        {
            head=newnode;
            return;
        }
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=newnode;
    }

    // Insert data
    void insert(int pos, string word)
    {
        undoStack.push(CopyList());
        Node *newnode=new Node();
        newnode->data=word;
        newnode->next=NULL;
        Node *temp=head,*prev=NULL;
        while(temp!=NULL and pos>1)
        {
            prev=temp;
            temp=temp->next;
            pos--;

        }
        if(prev==NULL and temp==NULL)
        {
            head=newnode;

        }
        else if(prev==NULL)
        {
            newnode->next=head;
            head=newnode;
        }
        else if(temp==NULL){
            prev->next=newnode;
            newnode->next=NULL;
        }
        else{
            newnode->next=prev->next;
            prev->next=newnode;
        }

    }
    

    // Update data
    void update(string data,string newword)
    {
        undoStack.push(CopyList());
        Node *temp=head;
        while(temp!=NULL and temp->data!=data)
        {
            temp=temp->next;
        }
        if(temp!=NULL)
        {
            temp->data=newword; 
        }
        else{
            cout<<"Data not found"<<endl;
        }
    }

    // Search data
    void search(string searchText)
    {
        int i=1;
        Node *temp=head;
        while(temp!=NULL)
        {
            if(temp->data==searchText)
            {
                cout<<"The data found at location: "<<i<<endl;
                return;
            }
            i++;
            temp=temp->next;
            
        }
        cout<<"Data Not Found"<<endl;
        return;
    }

    // Delete data
    void deleteData(string data)
    {
        undoStack.push(CopyList());
        Node *temp=head,*prev=NULL;
        if(head==NULL)
        {
            cout<<"No Data Found"<<endl;
            return;
        }
        while(temp!=NULL and temp->data!=data)
        {
            prev=temp;
            temp=temp->next;
        }
        if(temp==NULL)
        {
            cout<<"No  Data Found"<<endl;
        }
        else if(temp==head)
        {
            head=head->next;
        }
        else{
            prev->next=temp->next;
        }
            
    }

    // Display data on console
    void display()
    {
        cout<<"-------------------------------------------"<<endl;
        Node *temp=head;
        while(temp!=NULL)
        {
            cout<<temp->data<<" ";
            temp=temp->next;
        }
        cout<<endl;
        cout<<"-------------------------------------------"<<endl;
    }

    // Undo operation
    void undo()
    {
        if (!undoStack.empty())
        {
            redoStack.push(head);
            head = undoStack.top();
            undoStack.pop();

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
            undoStack.push(head);
            head = redoStack.top();
            redoStack.pop();
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
        string data;
        Node *temp=head;
        while(temp!=NULL)
        {
            data+=temp->data+" ";
            temp=temp->next;
        }
        string name;
        cout<<"Enter the name of your file"<<endl;
        cin.ignore();
        getline(cin,name);
        name+=".txt";
        file.open(name);
        file<<data;
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
            cin>>data;
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
            cin>>data;
            editor->insert(pos, data);
        }
        
        else if (ch == 4) // Update Data
        {
            string data,newword;
            cout << "Enter the word to update" << endl;
            cin.ignore();
            cin >> data;
            cout << "Enter the new word" << endl;
            cin.ignore();
            cin >> newword;
            editor->update(data,newword);
        }
        else if (ch == 5) // Search Data
        {
            string data;
            cout << "Enter the data to search" << endl;
            cin.ignore();
            cin>>data;
            editor->search(data);
        }
        else if (ch == 6) // Delete Data
        {
            string data;
            cout << "Enter the data to Delete" << endl;
            cin.ignore();
            cin>>data;
            editor->deleteData(data);
            
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

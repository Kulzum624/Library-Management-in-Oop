#include<iostream>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include<iomanip>
#include<conio.h>
#include<stdlib.h>


using namespace std;

void searchMenu();
void menu();
class Book;


class UserInterface 
{
	public:
		
		void issue();
		void displayissued();
		void issuance(char[], int);
		void heading();
		void searchByID();
		void searchByTitle();
		//void der(char[],int,int);
//		int department(int);
		void header ();
		friend void searchMenu();
	     		
}u;

class Admin:public virtual  UserInterface{
	public:
		char name[50];
	
		
		void password();
	
		void staffManagement();
		void modify(); 
		friend void menu();
		friend void searchMenu();
}a;


class Student: public virtual UserInterface{
	private:
		char name[50];
		char rollNo[10];
		
		
	public:
		void student();
		friend void menu ();
		friend void searchMenu ();
		
			
}s;



class Book: public Admin, public Student{
	public:
		char Title[50];
		char Author[50];
		char BookId[10];
		char Department[30];
		int q,B;
		Book(){
	   		strcpy(BookId,"");
	   		strcpy(Title,"");
	   		strcpy(Author,"");
	   		strcpy(Department,"");
	   		q=0;
	   		B=0;
		}	
	
		
		
		char* getID(){
			return BookId;
		}
 		char* getTitle(){
	 		return Title;
		}
  		char* getAuthor(){
	  		return Author;
		}
  		char* getDepartment(){
	  		return Department;
		}
		
		void getBook();
		void addBook();
		void showBook();
		void displayBooks();
		void listView();
		
		
}b;


void Book ::getBook()
{
	cout<<"\tEnter Book Id : ";
	//cin.get();
	//cin.getline(BookId,10);
	cin>>BookId;
	fflush(stdin);
	cout<<"\tEnter Book Title : ";
	//cin.get();
	cin>>Title;
	fflush(stdin);
//	cin.getline(Title,20);
	cout<<"\tEnter Book Author: ";
	//cin.get();
	cin>>Author;
	fflush(stdin);
	cout<<"\tEnter Book Department: ";
	cin.getline(Department,20);

	cout<<endl;
}

void Book ::listView()  ////i have to add the book class to student annd the admin with a has a relation ship 
{
	cout.setf(ios::left);
	cout<<setw(5)<<BookId
	<<setw(20)<<Title
	<<setw(20)<<Author
	<<setw(15)<<Department
	<<endl;
}



void Book :: showBook()
{
	cout<<endl;
	
	cout<<"Book ID      : "<<BookId<<endl;
	cout<<"Book Title   : "<<Title<<endl;
	cout<<"Author Name  : "<<Author<<endl;
	cout<<"Department   : "<<Department<<endl;
	
	cout<<endl;
}


void UserInterface ::header()
{
	cout.setf(ios::left);
	
	cout
	<<setw(5)<<"I.D."
	<<setw(20)<<"Book Title"
	<<setw(20)<<"Book Author"
	<<setw(15)<<"Department"
	<<endl;
	
	for(int i=1;i<=80;i++)
	  cout<<"=";
	cout<<endl;
}


void UserInterface :: heading()
{
	char symbol = '*';
	cout<<"\t";
 	for(int i=1;i<41;i++)
  		cout<<"-"<<symbol;
 	cout<<endl; 
	cout<<"\t|\t\t\tDigital Library Management \t\t\t\t|\n";
	cout<<"\t";
 	for(int i=1;i<41;i++)
  		cout<<"-"<<symbol;
 	cout<<endl; 
	 }

void Book :: addBook()
{
	system("cls");
	ofstream fout;
	fout.open("books.txt",ios::app);
	u.heading();
	cout<<endl<<endl<<endl;
	getBook();
	fout.write((char*)&b,sizeof(b));
	cout<<"Book data saved in file...\n";
	fout.close();
}



void Book :: displayBooks()
{
	system("cls");
	
	ifstream fin("books.txt");
	int rec=0;
	while(fin.read((char*)&b,sizeof(b)))
	{
	  	if(rec<1){
	   		u.header();}
	  	listView();
	  	rec++;
	}
	fin.close();
 	cout<<"\nTotal "<<rec<<" Records in file...\n";
}

void UserInterface ::searchByID()
{
	int flag=0;
	char id[10];
	ifstream fin("books.txt");
	cout<<"Enter Book ID : ";
	cin.get();
	cin.getline(id,10);
	while(fin.read((char*)&b,sizeof(b)))
	{
	 	if(strcmpi(id,b.getID())==0)
		{
	   		b.showBook();
	   		flag++;
	  	}
	}
	fin.close();
	if(flag==0)
		cout<<"Book Number with ID:"<<id<<" not available...\n";
}

//Fx for searching data from file.
void UserInterface ::searchByTitle()
{
	int flag=0;
	char title[20];
	ifstream fin("books.txt");
	cout<<"Enter Book Title : ";
	cin.ignore();
	cin.getline(title,30);
	while(fin.read((char*)&b,sizeof(b)))
	{
		if(strcmpi(title,b.getTitle())==0)
		{
	   		b.showBook();
	   		flag++;
	  	}
	}
	fin.close();
	if(flag==0)
		cout<<"Book with Title: "<<title<<" not available...\n";
}

void UserInterface::issue()
{
    
    int i,j,cont=0;
	
	system("cls");
	fflush(stdin);
	cout<<"\n\t\t->Please Enter Details :-\n";
    cout<<"\n\t\tEnter Book ID : ";
	cin.getline(b.BookId,10);
    
    issuance(b.BookId,1);
        
    ofstream outf("issued.dat",ios::binary|ios::app);
	outf.write((char*)this,sizeof(*this));
    outf.close();
	cout<<"\n\n\t\tIssue Successfully.\n";

}

void UserInterface::displayissued()
{
	int i;
	ifstream intf("issued.dat",ios::binary);
    system("cls");
	cout<<"\n\t\t->The Details are :-\n";
    intf.read((char*)this,sizeof(*this));
	i=0;
    while(!intf.eof())
    {
	    i++;
		cout<<"\n\t\t********** "<<i<<". ********** \n";
	    cout<<"\n\t\tBook's ID : "<<b.BookId<<"\n\t\tBook Name : "<<b.Title<<"\n\t\tBook Author : "<<b.Author<<"\n\t\tBook Category : "<<b.Department<<"\n";
	    intf.read((char*)this,sizeof(*this));
    }
   	intf.close();
}

void UserInterface :: issuance(char id[],int x)
{
    int i,q,cont=0;
    fstream fin("books.dat",ios::in|ios::out|ios::ate|ios::binary);
    fin.seekg(0);
    fin.read((char*)this,sizeof(*this));
    while(!fin.eof())
    {
        for(i=0; b.BookId[i] != '\0' && id[i] != '\0' && id[i] == b.BookId[i];i++);
        if(b.BookId[i] == '\0' && id[i] == '\0')
        {
            cont++;
            if(x==1)
            {
                q--;
            }
            else
            {
                q++;
            }
            fin.seekp(fin.tellp()-sizeof(*this));
            fin.write((char*)this,sizeof(*this));
            break;
        }
        fin.read((char*)this,sizeof(*this));
    }
    if(cont==0)
    {
        cout<<"\n\t\tBook not found.\n";
        cout<<"\n\n\t\tPress any key to continue.....";
        getch();
        system("cls");
        issue();
    }
    fin.close();
}

//FUNCTION FOR UPDATING BOOK DETAILS
void Admin :: modify()
{
	int flag=0,pos;
	char id[10];
	fstream fin("books.txt",ios::in|ios::out);
	cout<<"Enter Book ID : ";
	cin.get();
	cin.getline(id,10);
	while(fin.read((char*)&b,sizeof(b)))
	{
	 	if(strcmpi(id,b.getID())==0)
	  	{
	   		pos=fin.tellg();
		    cout<<"Following data will be edited...\n";
		    b.showBook();
		    flag++;
		    fin.seekg(pos-sizeof(b));
		    b.getBook();
		    fin.write((char*)&b,sizeof(b));
		    cout<<"\nData Modified successfully...\n";
		}
	 }
	 fin.close();
	 if(flag==0)
	  	cout<<"Book Number with ID:"<<id<<" not available...\n";
}

//MAIN FUNCTION FOR ADMIN USERS
void Admin ::staffManagement()
{
	int ch;
	do
	{
		system("cls");
		heading();
		cout<<endl;
		cout<<"\t\t0. EXIT.\n";
		cout<<"\t\t1. Add New Book\n";
		cout<<"\t\t2. Display All Books\n";
		cout<<"\t\t3. Search Books\n";
		cout<<"\t\t4. Issue Books\n";
		cout<<"\t\t5. Modify Details\n";
		cout<<"\t\t6. List of Issued Books\n";
		cout<<"\t\tEnter Your Choice : ";
		cin>>ch;
		system("cls");
		heading();
		switch(ch)
		{
	   		case 1: system("COLOR F4"); b.addBook(); break;
	   		case 2: system("COLOR F4"); b.displayBooks(); break;
	   		case 3: system("COLOR F4"); searchMenu(); break;
	   		case 4: system("COLOR F4"); issue(); break;
	   		case 5: system("COLOR F4"); b.modify(); break;
	   		case 6: system("COLOR F4"); displayissued(); break;
	  	}
	  	system("pause");
	}
	while(ch!=0);
}

//FUNCTION FOR STUDENTS USERS
void Student ::student()
{
	int i;
	do
	{
		system("cls");
		heading();
		cout<<endl;
		cout<<"\t\t0. Exit"<<endl;
		cout<<"\t\t1. Display All Books"<<endl;
		cout<<"\t\t2. Search Books"<<endl;
		cout<<"\t\t3. Issue Books"<<endl;
		cout<<"\t\t4. Go Back"<<endl;
		cout<<"\t\tEnter Your Choice : ";
		cin>>i;
		system("cls");
		heading();
		switch(i)
		{

	   		case 1: system("COLOR F4"); b.displayBooks(); break;
	   		case 2: system("COLOR F4"); searchMenu(); break;
	   		case 3: system("COLOR F4"); issue(); break;
	   		case 4: system("COLOR F4"); menu();
	  	}
	  	system("pause");
	}
	while(i!=0);
}


void menu()     ///changed the menu function to a friend function of user interface 
{ 

	do 
	{
			int i;
	
	
	system("cls");
	s.heading();
	
    cout<<"\n\t\t>>Please Choose Any Option To login \n";
    cout<<"\n\t\t1.Student\n\n\t\t2.Staff-Member\n\n\t\t3.Close Application\n";
    cout<<"\n\t\tEnter your choice : ";
    cin>>i;
   
    if(i==1)
    {
        system("cls");
        s.student();
        
    }
    else if(i==2)
        a.password();

    else if(i==3)
        exit(0);
    else
        {
 	    	cout<<"\n\t\tPlease enter correct option :(";
    		getch();
        	system("cls");
        
        }
}        while (1 );

}

//FUNCTION FOR PROTECTING ADMIN PART 
void Admin ::password()
{
    int i=0;
    char ch,p[21],ch1[21]={"fast"};
    cout<<"\n\t\tEnter Password : ";
    while(1)
    {
	    ch=getch();
	    if(ch==13)
	    {
	        p[i]='\0';
	        break;
	    }
	    else if(ch==8 && i>0)
	    {
	        i--;
	        cout<<"\b \b";
	    }
	    else
	    {
		    cout<<"*";
		    p[i]=ch;
		    i++;
	    }
    }
    ifstream fin("password.txt");
    fin>>ch1;
    fin.close();
    for(i = 0; p[i] == ch1[i] && p[i] != '\0' && ch1[i] != '\0'; i++);
    if(p[i] == '\0' && ch1[i] == '\0')
    {
        system("cls");
        staffManagement();
    }
    else
    {
        cout<<"\n\n\t\tWrong Password.\n\n\t\tEnter Again.....\n";
        getch();
        system("cls");
        menu();
    }
}




void searchMenu()      // made a friend function of both admin and student ,previosly it was a member of userinterface 
{
	int ch;
	do
	{
		system("cls");
		u.heading();
		cout<<"BOOK SEARCH OPTIONS\n";
		cout<<"0. Back\n";
		cout<<"1. By ID\n";
		cout<<"2. By Title\n";
		cout<<"Enter Your Choice : ";
		cin>>ch;
		system("cls");
		u.heading();
		switch(ch)
	  	{   
			case 1: system("COLOR F4"); u.searchByID(); break;
			case 2: system("COLOR F4"); u.searchByTitle(); break;
	
	   		default: cout<<"\a";
	  	}
	  	system("pause");
	}
	while(ch!=0);
}



int main()
{

 	system("COLOR F4");
 	menu();
 	return 0;
}


#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<conio.h>
#include<windows.h>

using namespace std;


class BOOK {
private:
	string name_of_book;
	string author;
	string IDbook;
	int status;// 1:dang muon; 0:dang ranh
public:
	//BOOK();
	string TakeName();//
	string TakeAuthor();//
	string TakeID();//
	int TakeStatus();//
	void SetName(string name);//
	void SetAuthor(string _author);//
	void SetID(string ID);//
	void SetStatus(int _status);
};

class MEMBER {
private:
	string name_of_member;
	string IDmember;
	vector<BOOK>borrowing;
public:
	//MEMBER();
	void Borrow(BOOK borrow_book);
	void Return(BOOK return_book);
	string TakeName();//
	string TakeID();//
	vector<BOOK>TakeBookBorrowing();//
	void SetName(string name);
	void SetID(string ID);
	void SetBorrowing(vector<BOOK>book);
};


class LIBRARY {
private:
	vector<MEMBER> member;
	vector<BOOK> book;

public:
	//LIBRARY();
	vector<MEMBER> ListMember();//
	vector<BOOK> ListBook();//
	void AddMember(MEMBER additon_member);//
	void AddBook(BOOK addition_book);//
	void ImportMemberFromFile(vector<BOOK>book);//
	void ImportBookFromFile();//
	void SetBook(vector<BOOK>new_book);
	void SetMember(vector<MEMBER>new_member);
};


int CountFile(string path);
vector<BOOK> ReadFileBook();
vector<MEMBER> ReadFileMember(vector<BOOK>list_book_available);
void InputMember(LIBRARY& lib);
void DisplayChoise(int choise);
void Menu(LIBRARY& lib);
#include"header.h"


// lay thong tin sach
string BOOK::TakeID() {
	return IDbook;
}
string BOOK::TakeName() {
	return name_of_book;
}
string BOOK::TakeAuthor() {
	return author;
}
int BOOK::TakeStatus() {
	return status;
}
// dat thong tin sach
void BOOK::SetName(string name) {
	name_of_book = name;
}
void BOOK::SetAuthor(string _author) {
	author = _author;
}
void BOOK::SetID(string ID) {
	IDbook = ID;
}
void BOOK::SetStatus(int _status) {
	status = _status;
}

vector<BOOK> LIBRARY::ListBook() {
	return book;
}

// lay thong tin thanh vien
string MEMBER::TakeName() {
	return name_of_member;
}
string MEMBER::TakeID() {
	return IDmember;
}
vector<BOOK> MEMBER::TakeBookBorrowing() {
	return borrowing;
}
// dat thong tin thanh vien
void MEMBER::SetName(string name) {
	name_of_member = name;
}
void MEMBER::SetID(string ID) {
	IDmember = ID;
}
void MEMBER::SetBorrowing(vector<BOOK>book) {
	borrowing = book;
}

// muon sach
void MEMBER::Borrow(BOOK borrow_book) {
	borrow_book.SetStatus(1);
	borrowing.push_back(borrow_book);
}

// tra sach
void MEMBER::Return(BOOK return_book) {
	return_book.SetStatus(0);
	for (int i = 0; i < borrowing.size(); i++) {
		if (return_book.TakeID() == borrowing[i].TakeID()) {
			borrowing.erase(borrowing.begin() + i);
		}
	}
}

// danh sach sach trong thu vien


// them thanh vien
void LIBRARY::AddMember(MEMBER addition_member) {
	member.push_back(addition_member);
}

// them sach
void LIBRARY::AddBook(BOOK addition_book) {
	book.push_back(addition_book);
}
// Danh sach thanh vien
vector<MEMBER> LIBRARY::ListMember() {
	return member;
}
void LIBRARY::SetBook(vector<BOOK>new_book) {
	book = new_book;
}
void LIBRARY::SetMember(vector<MEMBER>new_member) {
	member = new_member;
}



// dem so luong trong .txt
int CountFile(string path) {
	ifstream file(path, ios::in);
	int cnt = 0;
	while (!file.eof()) {
		string temp;
		getline(file, temp);
		if (temp == "")
			continue;
		cnt++;
	}
	return cnt - 1;
}
// doc thong tin sach trong book.txt
vector<BOOK> ReadFileBook() {
	vector<BOOK> book;
	ifstream file("book.txt", ios::in);
	int amount = CountFile("book.txt");
	string title;
	getline(file, title);
	for (int i = 0; i < amount; i++) {
		string temp_name, temp_author, temp_ID, temp_status;
		int status;
		getline(file, temp_name, ';');
		getline(file, temp_author, ';');
		getline(file, temp_ID, ';');
		getline(file, temp_status);
		status = stoi(temp_status);

		BOOK temp;
		temp.SetName(temp_name);
		temp.SetAuthor(temp_author);
		temp.SetID(temp_ID);
		temp.SetStatus(status);

		book.push_back(temp);
	}
	return book;
}

// doc thong tin thanh vien trong member.txt
vector<MEMBER> ReadFileMember(vector<BOOK>list_book_available) {
	vector<MEMBER> member;
	ifstream file("member.txt", ios::in);
	int amount = CountFile("member.txt");

	string title;
	getline(file, title);

	for (int i = 0; i < amount; i++) {
		string temp_name, temp_ID;
		vector<BOOK>borrwing;

		BOOK book;
		string list_book;
		getline(file, temp_name, ';');
		getline(file, temp_ID, ';');
		getline(file, list_book);
		stringstream ss(list_book);

		string each_book;
		while (getline(ss, each_book, ',')) {
			if (each_book == "khong") {
				book.SetName("khong");
				book.SetAuthor("0");
				book.SetID("0");
			}
			borrwing.push_back(book);
			break;
			for (int j = 0; j < list_book_available.size(); j++) {
				if (list_book_available[i].TakeName() == each_book) {
					book.SetName(list_book_available[i].TakeName());
					book.SetAuthor(list_book_available[i].TakeAuthor());
					book.SetID(list_book_available[i].TakeID());
				}
			}
			borrwing.push_back(book);
		}
		MEMBER temp_member;
		temp_member.SetName(temp_name);
		temp_member.SetID(temp_ID);
		temp_member.SetBorrowing(borrwing);
		member.push_back(temp_member);
	}
	return member;
}

// LIBRARY
void LIBRARY::ImportMemberFromFile(vector<BOOK>book) {
	member = ReadFileMember(book);
}
void LIBRARY::ImportBookFromFile() {
	book = ReadFileBook();
}

// Nhap thong tin thanh vien
void InputMember(LIBRARY& lib) {
	MEMBER member;
	string temp_name, temp_ID;
	vector<BOOK>book;

	cout << "Ho ten thanh vien : "; getline(cin, temp_name);
	cout << "Ma thanh vien     : "; getline(cin, temp_ID);
	cout << "Sach dang muon (Nhap 'khong' neu khong muon):\n";

	BOOK temp_book;
	string temp_book_borrowing;
	cout << "   "; getline(cin, temp_book_borrowing);
	temp_book.SetName(temp_book_borrowing);
	while (temp_book_borrowing != "khong") {
		cout << "   "; getline(cin, temp_book_borrowing);
		temp_book.SetName(temp_book_borrowing);
		book.push_back(temp_book);
	}
	member.SetName(temp_name);
	member.SetID(temp_ID);
	member.SetBorrowing(book);
	lib.AddMember(member);
}

//Nhap thong tin sach
void InputBook(LIBRARY& lib) {
	BOOK book;
	string temp_name, temp_author, temp_ID;
	cout << "Ten sach: "; getline(cin, temp_name);
	cout << "Tac gia: "; getline(cin, temp_author);
	cout << "ID sach: "; getline(cin, temp_ID);
	book.SetName(temp_name);
	book.SetAuthor(temp_author);
	book.SetID(temp_ID);
	book.SetStatus(0);
	lib.AddBook(book);
}

void BorrowingBook(LIBRARY& lib) {
	string IDmember;
	cout << "Ma thanh vien :";
	getline(cin, IDmember);

	string IDbook;
	cout << "Ma sach muon: ";
	getline(cin, IDbook);

	// Tim thong tin cua sach can muon va set trang thai sach dang duoc muon
	BOOK book_borrow;
	vector<BOOK>list_book = lib.ListBook();
	for (int i = 0; i < list_book.size(); i++) {
		if (list_book[i].TakeID() == IDbook) {
			book_borrow.SetName(list_book[i].TakeName());
			book_borrow.SetAuthor(list_book[i].TakeAuthor());
			book_borrow.SetID(list_book[i].TakeID());
			list_book[i].SetStatus(1);
		}
	}
	// cap nhat lai danh sach sach
	lib.SetBook(list_book);

	//kiem tra thanh vien da co muon sach hay chua, neu roi thi push
	vector<MEMBER> list_member = lib.ListMember();

	for (int i = 0; i < list_member.size(); i++) {
		if (list_member[i].TakeID() == IDmember) {// Tim thanh vien muon sach
			vector<BOOK>list_borrowing = list_member[i].TakeBookBorrowing();//Lay ra danh sach sach dang muon
			if (list_borrowing[0].TakeName() == "khong") {
				list_borrowing.clear();
			}
			list_borrowing.push_back(book_borrow);
			list_member[i].SetBorrowing(list_borrowing);
		}
	}
	lib.SetMember(list_member);

}





void DisplayChoise(int choise) {
	system("cls");
	cout << "\n =========MENU=========\n";
	if (choise == 1)
		cout << " > 1. Them sach\n";
	else
		cout << "   1. Them sach\n";
	if (choise == 2)
		cout << " > 2. Danh sach sach con\n";
	else
		cout << "   2. Danh sach sach con\n";
	if (choise == 3)
		cout << " > 3. Them thanh vien\n";
	else
		cout << "   3. Them thanh vien\n";
	if (choise == 4)
		cout << " > 4. Danh sach thanh vien\n";
	else
		cout << "   4. Danh sach thanh vien\n";
	if(choise == 5)
		cout << " > 5. Muon sach\n";
	else
		cout << "   5. Muon sach\n";
	if (choise == 6)
		cout << " > 6. Tra sach\n";
	else
		cout << "   6. Tra sach\n";
	if (choise == 7)
		cout << " > 7. Thoat\n";
	else
		cout << "   7. Thoat\n";
}

void Menu(LIBRARY& lib) {
	int choise = 1;
	DisplayChoise(choise);
	while (true) {
		if (_kbhit()) {
			char keylog = _getch();
			switch (keylog) {
			case 72: { // Xun
				if (choise > 1)
					choise--;
				break;
			}
			case 80: { // Len
				if (choise < 7)
					choise++;
				break;
			}
			case 13: {
				if (choise == 7) {
					cout << "\nThoat chuong trinh...\n";
					Sleep(500);
					return;
				}
				else {
					switch (choise) {
					case 1: {
						cout << "\n   1. Them sach\n";
						int amount;
						cout << "So luong sach muon them: "; cin >> amount;
						cin.ignore();
						for (int i = 0; i < amount; i++) {
							cout << " Sach " << i + 1 << ":\n";
							InputBook(lib);
						}
						cout << "  An phim bat ki de quay ve Menu...\n";
						_getch();
						break;
					}
					case 2: {
						cout << "\n   2. Danh sach sach con\n";
						vector<BOOK> book = lib.ListBook();
						int amount = book.size(); 
						cout << "Ten\tTac gia\tMa sach\n";
						for (int i = 0; i < amount; i++) {
							if (book[i].TakeStatus() == 0) {
								cout << book[i].TakeName() << "\t";
								cout << book[i].TakeAuthor() << "\t";
								cout << book[i].TakeID() << endl;
							}
						}

						cout << "\n  An phim bat ki de quay ve Menu...\n";
						_getch();
						break;
					}
					case 3: {
						cout << "\n   3. Them thanh vien\n";
						int amount;
						cout << "So luong thanh vien muon them: "; cin >> amount;
						cin.ignore();
						for (int i = 0; i < amount; i++) {
							
							cout << " Thanh vien " << i + 1 << ":\n";
							
							InputMember(lib);
						}
						cout << "  An phim bat ki de quay ve Menu...\n";
						_getch();
						break;
					}
					case 4: {
						cout << "\n   4. Danh sach thanh vien\n";
						vector<MEMBER> member = lib.ListMember();
						cout << "Ten\tMa thanh vien\n";
						for (int i = 0; i < member.size(); i++) {
							cout << member[i].TakeName() << "\t";
							cout << member[i].TakeID() << "\n";
						}
						cout << "  An phim bat ki de quay ve Menu...\n";
						_getch();
						break;
					}
					case 5: {
						cout << "\n   5. Muon sach\n";
						BorrowingBook(lib);
						cout << "  An phim bat ki de quay ve Menu...\n";
						_getch();
						break;
					}
					case 6: {
						cout << "\n   6. Tra sach\n";

						

						cout << "  An phim bat ki de quay ve Menu...\n";
						_getch();
						break;
					}

					}
				}
				break;
			}   
			}
			DisplayChoise(choise);
		}
	}
}
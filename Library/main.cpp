#include"header.h"

int main() {
	LIBRARY lib;
	lib.ImportBookFromFile();
	lib.ImportMemberFromFile(lib.ListBook());
	Menu(lib);
	return 0;
}
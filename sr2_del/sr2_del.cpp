#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

const int MAX_STUDENTS = 100;

bool sortById = true;

struct Student {
	int id;
	string name;

	void input() {
		cout << "Введите ID студента: ";
		cin >> id;

		cout << "Введите ФИО: ";
		cin >> name;
	}

	void print() {
		cout << "ID: " << id
			<< " Name: " << name << endl;
	}
};
struct TreeNodeID {
	int StudentID;
	int RecNum;

	TreeNodeID* left = nullptr;
	TreeNodeID* right = nullptr;
};
struct TreeNodeName {
	string StudentName;
	int RecNum;
	TreeNodeName* left = nullptr;
	TreeNodeName* right = nullptr;
};

#pragma region Global
int studentsNumber = 7;
Student students[MAX_STUDENTS] = {
	{4,"Ave",},
	{2,"Bib",},
	{3,"Cid",},
	{1,"Azi",},
	{7,"Dap"},
	{6,"Zon"},
	{5,"Lal"}
};
int* IndexArrayID = nullptr;
TreeNodeID* RootID = nullptr;

int* IndexArrayName = nullptr;
TreeNodeName* RootName = nullptr;
#pragma endregion

#pragma region ID
void rebuildIndexArray() {
	if (IndexArrayID != nullptr) {
		delete[] IndexArrayID;
	}
	IndexArrayID = new int[studentsNumber];
	for (int i = 0; i < studentsNumber; i++) {
		IndexArrayID[i] = i;
	}

	for (int i = 0; i < studentsNumber; ++i) {
		for (int j = i + 1; j < studentsNumber; ++j) {
			if (students[IndexArrayID[j]].id < students[IndexArrayID[i]].id) {
				int temp = IndexArrayID[i];
				IndexArrayID[i] = IndexArrayID[j];
				IndexArrayID[j] = temp;
			}
		}
	}
}

TreeNodeID* buildBalancedTreeID(int left, int right) {
	if (left > right) {
		return nullptr;
	}

	int mid = left + (right - left) / 2;
	TreeNodeID* node = new TreeNodeID;
	node->RecNum = IndexArrayID[mid];
	node->StudentID = students[IndexArrayID[mid]].id;
	node->left = buildBalancedTreeID(left, mid - 1);
	node->right = buildBalancedTreeID(mid + 1, right);

	return node;
}

void PrintTreeIncrease(TreeNodeID*& Node) {
	if (Node == nullptr) return;
	PrintTreeIncrease(Node->left);
	students[Node->RecNum].print();
	PrintTreeIncrease(Node->right);
}

int SearchID(TreeNodeID* Node, int id) {
	if (Node == nullptr) {
		cout << "Студента с таким ID не найдено" << endl;
		return -1;
	}
	if (id == Node->StudentID) {
		students[Node->RecNum].print();
		return Node->RecNum;
	}
	else if (id < Node->StudentID)
		return SearchID(Node->left, id);
	else
		return SearchID(Node->right, id);
}
#pragma endregion

#pragma region Name
void rebuildIndexArrayName() {
	if (IndexArrayName != nullptr) delete[] IndexArrayName;
	IndexArrayName = new int[studentsNumber];
	for (int i = 0; i < studentsNumber; i++)
		IndexArrayName[i] = i;
	for (int i = 0; i < studentsNumber; i++) {
		for (int j = i + 1; j < studentsNumber; j++) {
			if (students[IndexArrayName[j]].name < students[IndexArrayName[i]].name) {
				int temp = IndexArrayName[i];
				IndexArrayName[i] = IndexArrayName[j];
				IndexArrayName[j] = temp;
			}
		}
	}
}

TreeNodeName* buildBalancedTreeName(int left, int right) {
	if (left > right) return nullptr;
	int mid = left + (right - left) / 2;
	TreeNodeName* node = new TreeNodeName;
	node->RecNum = IndexArrayName[mid];
	node->StudentName = students[IndexArrayName[mid]].name;
	node->left = buildBalancedTreeName(left, mid - 1);
	node->right = buildBalancedTreeName(mid + 1, right);
	return node;
}

void PrintTreeDecreaseName(TreeNodeName* Node) {
	if (Node == nullptr) return;
	PrintTreeDecreaseName(Node->right);
	students[Node->RecNum].print();
	PrintTreeDecreaseName(Node->left);
}

int SearchName(TreeNodeName* Node, string name) {
	if (Node == nullptr) {
		cout << "Студента с таким ID не найдено" << endl;
		return -1;
	}
	if (name == Node->StudentName) {
		students[Node->RecNum].print();
		return Node->RecNum;
	}
	else if (name < Node->StudentName)
		return SearchName(Node->left, name);
	else
		return SearchName(Node->right, name);
}
#pragma endregion

void PrintStudents() {
	cout << "Список студентов\n";
	for (int i = 0; i < studentsNumber; i++) {
		students[i].print();
	}
	cout << endl;
}

void removeElement(int pos) {
	for (int i = pos; i < studentsNumber - 1; i++) {//перестраиваем массив студентов
		students[i] = students[i + 1];
	}
	studentsNumber--;

	rebuildIndexArray();//перестраиваем инд массив
	RootID = buildBalancedTreeID(0, studentsNumber - 1);// строим новое дерево по новому инд массиву
	PrintStudents();//выводим новый массив студентов}

	rebuildIndexArrayName();
	RootName = buildBalancedTreeName(0, studentsNumber - 1);
}


int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	//Ввод списка

	rebuildIndexArray();//построили инд массив по студенческим ид
	RootID = buildBalancedTreeID(0, studentsNumber - 1);//создали сбалансированное дерево

	rebuildIndexArrayName();
	RootName = buildBalancedTreeName(0, studentsNumber - 1);//аналог-но для имен

	PrintStudents();//вывели список

	bool exit = false;
	int choice = 0, subchoice = 0;
	int pos, id;
	string name;

	while (!exit) {
		cout << "Главное меню:\n";
		cout << "1. Вывести список студентов\n";
		cout << "2. Отсортировать список студентов по возрастанию ID\n3. Отсортировать список студентов по убыванию имени\n";
		cout << "4. Поиск студента по ID\n5. Поиск студента по ФИО\nВведите команду: ";
		cin >> choice;

		switch (choice) {
		case 1:
			PrintStudents();
			break;
		case 2:
			cout << "Cписок студентов по возрастанию ID\n";
			PrintTreeIncrease(RootID);
			break;
		case 3:
			cout << "Cписок студентов по убыванию имени\n";
			PrintTreeDecreaseName(RootName);
			break;
		case 4:
			cout << "Введите ID студента: ";
			cin >> id;
			pos = SearchID(RootID, id);
			if (pos == -1)break;
			cout << "1. Удалить запись\n2. Назад\nВведите команду: ";
			cin >> subchoice;
			if (subchoice == 2)break;
			removeElement(pos);
			break;
		case 5:
			cout << "Введите имя студента: ";
			cin >> name;
			pos = SearchName(RootName, name);
			if (pos == -1)break;
			cout << "1. Удалить запись\n2. Назад\nВведите команду: ";
			cin >> subchoice;
			if (subchoice == 2)break;
			removeElement(pos);
			break;
		case 6:
			exit = true;
			break;
		default:
			cout << "Неправильный ввод. Попробуйте еще)\n";
			break;
		}
	}
}
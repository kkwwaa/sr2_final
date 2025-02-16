#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

struct Student {
	int id;
	string name;  // ФИО в одной строке
	string submissionDate;
	string reviewDate;
	int gradeReport;
	int gradeDefense;
	string reviewer;
	string seminarist;

	void input() {
		cout << "Введите ID студента: ";
		cin >> id;
		cin.ignore();  // Игнорируем \n перед getline
		cout << "Введите ФИО: ";
		getline(cin, name);
		cout << "Введите дату сдачи (ДД.ММ.ГГГГ): ";
		cin >> submissionDate;
		cout << "Введите дату проверки (ДД.ММ.ГГГГ): ";
		cin >> reviewDate;
		cout << "Введите оценку за отчет: ";
		cin >> gradeReport;
		cout << "Введите оценку за защиту: ";
		cin >> gradeDefense;
		cin.ignore();
		cout << "Введите фамилию проверяющего: ";
		getline(cin, reviewer);
		cout << "Введите фамилию семинариста: ";
		getline(cin, seminarist);
	}


	void print() {
		cout << "ID: " << id << ", ФИО: " << name
			<< ", Дата сдачи: " << submissionDate
			<< ", Дата проверки: " << reviewDate
			<< ", Оценка за отчет: " << gradeReport
			<< ", Оценка за защиту: " << gradeDefense
			<< ", Проверяющий: " << reviewer
			<< ", Семинарист: " << seminarist << endl;
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
const int MAX_STUDENTS = 100;
int studentsNumber = 10;
Student students[MAX_STUDENTS] = {
	{3, "Борисова Екатерина Андреевна", "27.11.2024", "03.12.2024", 6, 9, "Долныкова", "Будин"},
	{5, "Дуров Павел Валерьевич", "01.12.2024", "10.12.2024", 4, 6, "Долныкова", "Цидвинцев"},
	{9, "Косвинцев Богдан Павлович", "01.12.2024", "10.12.2024", 6, 8, "Осока", "Цидвинцев"},
	{10, "Никитин Никита Никитич", "01.12.2024", "10.12.2024", 0, 0, "Долныкова", "Будин"},
	{1, "Петров Арсений Николаевич", "25.11.2024", "30.11.2024", 7, 9, "Долныкова", "Цидвинцев"},
	{8, "Понькина Татьяна Евгеньевна", "25.11.2024", "05.12.2024", 8, 8, "Осока", "Цидвинцев"},
	{2, "Семенов Евгений Александрович", "25.11.2024", "30.11.2024", 5, 8, "Долныкова", "Будин"},
	{6, "Симонов Антон Владимирович", "25.11.2024", "01.12.2024", 8, 8, "Осока", "Цидвинцев"},
	{4, "Юрьева София Юрьевна", "28.11.2024", "03.12.2024", 2, 9, "Долныкова", "Цидвинцев"},
	{7, "Янина Анна Владимировна", "25.11.2024", "01.12.2024", 7, 7, "Осока", "Цидвинцев"}
};
int* IndexArrayID = nullptr;
TreeNodeID* RootID = nullptr;

int* IndexArrayName = nullptr;
TreeNodeName* RootName = nullptr;

string normalize(const string& str) {
	string result = "";
	for (size_t i = 0; i < str.length(); i++) {
		char ch = str[i];

		// Приводим к нижнему регистру вручную
		if (ch >= 'А' && ch <= 'Я') {
			ch = ch + ('a' - 'A');
		}

		// Пропускаем пробелы
		if (ch != ' ') {
			result += ch;
		}
	}
	return result;
}
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
	if (left > right) return nullptr;
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

int SearchName(string name) {
	TreeNodeName* Node = RootName;
	while (Node != nullptr) {
		string NodeName = normalize(Node->StudentName);

		if (name == NodeName) {
			students[Node->RecNum].print();
			return Node->RecNum;
		}
		else if (name < NodeName)
			Node = Node->left;
		else
			Node = Node->right;
	}
	cout << "Студента с таким ФИО не найдено" << endl;
	return -1;
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

	bool exit = false;
	int choice = 0, subchoice = 0;
	int pos, id;
	string name;

	//Ввод списка
	cout << "Удалить исходные данные?\n1. Да\n2. Нет\nВведите команду: ";
	cin >> choice;
	if (choice == 1) {
		cout << "Введите количество значений для добавления: ";
		cin >> studentsNumber;
		for (int i = 0; i < studentsNumber; i++) {
			students[i].input();
		}
	}

	rebuildIndexArray();//построили инд массив по студенческим ид
	RootID = buildBalancedTreeID(0, studentsNumber - 1);//создали сбалансированное дерево

	rebuildIndexArrayName();
	RootName = buildBalancedTreeName(0, studentsNumber - 1);//аналог-но для имен

	PrintStudents();//вывели список

	while (!exit) {
		cout << "Главное меню:\n";
		cout << "1. Добавить запись\n2. Вывести список студентов\n";
		cout << "3. Отсортировать список студентов по возрастанию ID\n4. Отсортировать список студентов по убыванию имени\n";
		cout << "5. Поиск студента по ID\n6. Поиск студента по ФИО\nВведите команду: ";
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Введите количество значений для добавления: ";
			int n;
			cin >> n;
			studentsNumber += n;
			for (int i = studentsNumber-n; i < studentsNumber; i++) {
				students[i].input();
			}
			rebuildIndexArray();//построили инд массив по студенческим ид
			RootID = buildBalancedTreeID(0, studentsNumber - 1);//создали сбалансированное дерево

			rebuildIndexArrayName();
			RootName = buildBalancedTreeName(0, studentsNumber - 1);//аналог-но для имен

			PrintStudents();
			break;
		case 2:
			PrintStudents();
			break;
		case 3:
			cout << "Cписок студентов по возрастанию ID\n";
			PrintTreeIncrease(RootID);
			break;
		case 4:
			cout << "Cписок студентов по убыванию имени\n";
			PrintTreeDecreaseName(RootName);
			break;
		case 5:
			cout << "Введите ID студента: ";
			cin >> id;
			pos = SearchID(RootID, id);
			if (pos == -1)break;
			cout << "1. Удалить запись\n2. Назад\nВведите команду: ";
			cin >> subchoice;
			if (subchoice == 2)break;
			removeElement(pos);
			break;
		case 6:
			cout << "Введите ФИО студента: ";
			cin.ignore();
			getline(cin, name);
			pos = SearchName(normalize(name));
			if (pos == -1)break;
			cout << "1. Удалить запись\n2. Назад\nВведите команду: ";
			cin >> subchoice;
			if (subchoice == 2)break;
			removeElement(pos);
			break;
		case 7:
			exit = true;
			break;
		default:
			cout << "Неправильный ввод. Попробуйте еще)\n";
			break;
		}
	}
}
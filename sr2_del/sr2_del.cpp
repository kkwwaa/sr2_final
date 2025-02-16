#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

struct Student {
	int id;
	string name;  // ��� � ����� ������
	string submissionDate;
	string reviewDate;
	int gradeReport;
	int gradeDefense;
	string reviewer;
	string seminarist;

	void input() {
		cout << "������� ID ��������: ";
		cin >> id;
		cin.ignore();  // ���������� \n ����� getline
		cout << "������� ���: ";
		getline(cin, name);
		cout << "������� ���� ����� (��.��.����): ";
		cin >> submissionDate;
		cout << "������� ���� �������� (��.��.����): ";
		cin >> reviewDate;
		cout << "������� ������ �� �����: ";
		cin >> gradeReport;
		cout << "������� ������ �� ������: ";
		cin >> gradeDefense;
		cin.ignore();
		cout << "������� ������� ������������: ";
		getline(cin, reviewer);
		cout << "������� ������� �����������: ";
		getline(cin, seminarist);
	}


	void print() {
		cout << "ID: " << id << ", ���: " << name
			<< ", ���� �����: " << submissionDate
			<< ", ���� ��������: " << reviewDate
			<< ", ������ �� �����: " << gradeReport
			<< ", ������ �� ������: " << gradeDefense
			<< ", �����������: " << reviewer
			<< ", ����������: " << seminarist << endl;
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
	{3, "�������� ��������� ���������", "27.11.2024", "03.12.2024", 6, 9, "���������", "�����"},
	{5, "����� ����� ����������", "01.12.2024", "10.12.2024", 4, 6, "���������", "���������"},
	{9, "��������� ������ ��������", "01.12.2024", "10.12.2024", 6, 8, "�����", "���������"},
	{10, "������� ������ �������", "01.12.2024", "10.12.2024", 0, 0, "���������", "�����"},
	{1, "������ ������� ����������", "25.11.2024", "30.11.2024", 7, 9, "���������", "���������"},
	{8, "�������� ������� ����������", "25.11.2024", "05.12.2024", 8, 8, "�����", "���������"},
	{2, "������� ������� �������������", "25.11.2024", "30.11.2024", 5, 8, "���������", "�����"},
	{6, "������� ����� ������������", "25.11.2024", "01.12.2024", 8, 8, "�����", "���������"},
	{4, "������ ����� �������", "28.11.2024", "03.12.2024", 2, 9, "���������", "���������"},
	{7, "����� ���� ������������", "25.11.2024", "01.12.2024", 7, 7, "�����", "���������"}
};
int* IndexArrayID = nullptr;
TreeNodeID* RootID = nullptr;

int* IndexArrayName = nullptr;
TreeNodeName* RootName = nullptr;

string normalize(const string& str) {
	string result = "";
	for (size_t i = 0; i < str.length(); i++) {
		char ch = str[i];

		// �������� � ������� �������� �������
		if (ch >= '�' && ch <= '�') {
			ch = ch + ('a' - 'A');
		}

		// ���������� �������
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
		cout << "�������� � ����� ID �� �������" << endl;
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
	cout << "�������� � ����� ��� �� �������" << endl;
	return -1;
}
#pragma endregion

void PrintStudents() {
	cout << "������ ���������\n";
	for (int i = 0; i < studentsNumber; i++) {
		students[i].print();
	}
	cout << endl;
}

void removeElement(int pos) {
	for (int i = pos; i < studentsNumber - 1; i++) {//������������� ������ ���������
		students[i] = students[i + 1];
	}
	studentsNumber--;

	rebuildIndexArray();//������������� ��� ������
	RootID = buildBalancedTreeID(0, studentsNumber - 1);// ������ ����� ������ �� ������ ��� �������
	PrintStudents();//������� ����� ������ ���������}

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

	//���� ������
	cout << "������� �������� ������?\n1. ��\n2. ���\n������� �������: ";
	cin >> choice;
	if (choice == 1) {
		cout << "������� ���������� �������� ��� ����������: ";
		cin >> studentsNumber;
		for (int i = 0; i < studentsNumber; i++) {
			students[i].input();
		}
	}

	rebuildIndexArray();//��������� ��� ������ �� ������������ ��
	RootID = buildBalancedTreeID(0, studentsNumber - 1);//������� ���������������� ������

	rebuildIndexArrayName();
	RootName = buildBalancedTreeName(0, studentsNumber - 1);//������-�� ��� ����

	PrintStudents();//������ ������

	while (!exit) {
		cout << "������� ����:\n";
		cout << "1. �������� ������\n2. ������� ������ ���������\n";
		cout << "3. ������������� ������ ��������� �� ����������� ID\n4. ������������� ������ ��������� �� �������� �����\n";
		cout << "5. ����� �������� �� ID\n6. ����� �������� �� ���\n������� �������: ";
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "������� ���������� �������� ��� ����������: ";
			int n;
			cin >> n;
			studentsNumber += n;
			for (int i = studentsNumber-n; i < studentsNumber; i++) {
				students[i].input();
			}
			rebuildIndexArray();//��������� ��� ������ �� ������������ ��
			RootID = buildBalancedTreeID(0, studentsNumber - 1);//������� ���������������� ������

			rebuildIndexArrayName();
			RootName = buildBalancedTreeName(0, studentsNumber - 1);//������-�� ��� ����

			PrintStudents();
			break;
		case 2:
			PrintStudents();
			break;
		case 3:
			cout << "C����� ��������� �� ����������� ID\n";
			PrintTreeIncrease(RootID);
			break;
		case 4:
			cout << "C����� ��������� �� �������� �����\n";
			PrintTreeDecreaseName(RootName);
			break;
		case 5:
			cout << "������� ID ��������: ";
			cin >> id;
			pos = SearchID(RootID, id);
			if (pos == -1)break;
			cout << "1. ������� ������\n2. �����\n������� �������: ";
			cin >> subchoice;
			if (subchoice == 2)break;
			removeElement(pos);
			break;
		case 6:
			cout << "������� ��� ��������: ";
			cin.ignore();
			getline(cin, name);
			pos = SearchName(normalize(name));
			if (pos == -1)break;
			cout << "1. ������� ������\n2. �����\n������� �������: ";
			cin >> subchoice;
			if (subchoice == 2)break;
			removeElement(pos);
			break;
		case 7:
			exit = true;
			break;
		default:
			cout << "������������ ����. ���������� ���)\n";
			break;
		}
	}
}
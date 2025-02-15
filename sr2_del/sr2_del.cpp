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
		cout << "������� ID ��������: ";
		cin >> id;

		cout << "������� ���: ";
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
	if (Node->left == nullptr) {
		students[Node->RecNum].print();
		if (Node->right != nullptr) PrintTreeIncrease(Node->right);
	}
	else {
		PrintTreeIncrease(Node->left);
		students[Node->RecNum].print();
		if (Node->right != nullptr) PrintTreeIncrease(Node->right);
	}
}

int SearchID() {
	int value;
	cout << "������� ID ��������: ";
	cin >> value;

	int pos = -1;
	for (int i = 0; i < studentsNumber; i++) {//������� ������ ��������
		if (students[i].id == value) {
			pos = i;
			break;
		}
	}
	if (pos == -1) {
		cout << "������� " << value << " �� ������." << endl;
	}
	else students[pos].print();
	return pos;
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

void PrintTreeDecreaseName(TreeNodeName* node) {
	if (node == nullptr) return;
	PrintTreeDecreaseName(node->right);
	students[node->RecNum].print();
	PrintTreeDecreaseName(node->left);
}

int SearchName() {
	string value;
	cout << "������� ��� ��������: ";
	cin >> value;
	int pos = -1;
	for (int i = 0; i < studentsNumber; i++) {
		if (students[i].name == value) {
			pos = i;
			break;
		}
	}
	if (pos == -1)
		cout << "������� " << value << " �� ������." << endl;
	else students[pos].print();
	return pos;
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

	//���� ������

	rebuildIndexArray();//��������� ��� ������ �� ����������� ��
	RootID = buildBalancedTreeID(0, studentsNumber - 1);//������� ���������������� ������

	rebuildIndexArrayName();
	RootName = buildBalancedTreeName(0, studentsNumber - 1);//������-�� ��� ����

	PrintStudents();//������ ������

	bool exit = false;
	int choice = 0, subchoice = 0;
	int pos;

	while (!exit) {
		cout << "������� ����:\n";
		cout << "1. ������� ������ ���������\n";
		cout << "2. ������������� ������ ��������� �� ����������� ID\n3. ������������� ������ ��������� �� �������� �����\n";
		cout << "4. ����� �������� �� ID\n5. ����� �������� �� ���\n������� �������: ";
		cin >> choice;

		switch (choice) {
		case 1:
			PrintStudents();
			break;
		case 2:
			cout << "C����� ��������� �� ����������� ID\n";
			PrintTreeIncrease(RootID);
			break;
		case 3:
			cout << "C����� ��������� �� �������� �����\n";
			PrintTreeDecreaseName(RootName);
			break;
		case 4:
			pos = SearchID();
			if (pos == -1)break;
			cout << "1. ������� ������\n2. �����\n������� �������: ";
			cin >> subchoice;
			if (subchoice == 2)break;
			removeElement(pos);
			break;
		case 5:
			pos = SearchName();
			if (pos == -1)break;
			cout << "1. ������� ������\n2. �����\n������� �������: ";
			cin >> subchoice;
			if (subchoice == 2)break;
			removeElement(pos);
			break;
		case 6:
			exit = true;
			break;
		default:
			cout << "������������ ����. ���������� ���)\n";
			break;
		}
	}
}

//����
//�����
//�����
//��������
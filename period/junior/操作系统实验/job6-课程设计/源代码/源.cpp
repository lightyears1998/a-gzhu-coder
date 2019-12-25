// ģ��ʱ��Ƭ��ת��

#include "util.hpp"
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
using namespace std;


// ���̿��ƿ�
struct PCB {
	string name;  // ��������
	int arrivedAt;  // ����ʱ��
	int remainTime;  // ��������ʱ��

public:
	PCB(const string& name, int arrivedAt, int remainTime) {
		this->name = name;
		this->arrivedAt = arrivedAt;
		this->remainTime = remainTime;
	}


	// ������ʱ��ǽ�������ıȽϺ�����
	bool operator < (const PCB& oth) const {
		return this->arrivedAt < oth.arrivedAt;
	}
};


int systemClock;  // ϵͳʱ��
int processCount;  // ϵͳ�еĽ��̸���
vector<PCB> processToRun; // ϵͳ�е������Ѱ�������δ����Ľ���
deque<PCB> processQueue; // ���̶���
vector<PCB> finishedProcess;  // ������еĽ���


// ��ʾϵͳ�������Ѱ��ŵĽ��̡�
void showProcessToRun() {
	cout << "�Ѱ��ŵĽ��̡�����ʱ���Ԥ�Ƴ���ʱ�䣺" << endl;
	for (PCB pcb : processToRun) {
		cout << pcb.name << '\t' << "" << pcb.arrivedAt << '\t' << pcb.remainTime << endl;
	}
	cout << "========" << endl;
}


// �������������Ϣ��
void randomProcessInfo() {
	srand(unsigned(time(nullptr)));

	for (int i = 1; i <= processCount; ++i) {
		string name = "P" + to_string(i);
		int arriveAt = rand() % 10;
		int remainTime = 1 + rand() % 10;
		processToRun.push_back(PCB(name, arriveAt, remainTime));
	}
	sort(processToRun.begin(), processToRun.end());  // �����̵���ʱ������
	cout << "========" << endl;
}


// ���������Ϣ��
void inputProcessInfo(IOHelper &helper) {
	for (int i = 1; i <= processCount; ++i) {
		cout << "���������" << i << "�����̵���Ϣ��" << endl;
		
		string name = helper.getline("��������");
		int arriveAt = helper.nextInt("����ʱ��");
		int remainTime = helper.nextInt("Ԥ������ʱ��");
		
		vector<string> failReasons;
		if (name.empty()) {
			failReasons.push_back("����������Ϊ�գ�");
		}
		if (arriveAt < 0) {
			failReasons.push_back("���̵���ʱ�������ڻ����0��");
		}
		if (remainTime < 1) {
			failReasons.push_back("���̱�����������1��ʱ�䵥λ��");
		}

		if (failReasons.empty()) {
			processToRun.push_back(PCB(name, arriveAt, remainTime));
		}
		else {
			for (string reason : failReasons) {
				cout << reason;
			}
			cout << "���������������Ϣ��" << endl;
			
			--i;
		}
	}
	sort(processToRun.begin(), processToRun.end());  // �����̵���ʱ������
	cout << "========" << endl;
}


// ģ��������С�
void Simulate() {
	while (!processToRun.empty() || !processQueue.empty()) {
		cout << "ϵͳʱ�䣺" << systemClock << endl;

		// ѡ��������ж��׽������С�
		PCB* runProcess = !processQueue.empty() ? &processQueue.front() : nullptr;

		if (runProcess != nullptr) {
			runProcess->remainTime -= 1;  // ģ���������
			if (runProcess->remainTime > 0) {
				cout << "����" << runProcess->name << "���У�ʣ������ʱ�䣺" << runProcess->remainTime << "��" << endl;
			}
			else {
				cout << "����" << runProcess->name << "������ϡ�" << endl;
			}
		}
		else {
			cout << "ϵͳ��ת��" << endl;
		}

		// ���̵��ﲢ����������ж�β��
		while (!processToRun.empty() && processToRun.front().arrivedAt == systemClock) {
			PCB pcb = processToRun.front();
			processToRun.erase(processToRun.begin());
			processQueue.push_back(pcb);

			cout << "����" << pcb.name << "���Ԥ������ʱ�䣺" << pcb.remainTime << "��" << endl;
		}

		// ���Ѿ����й��Ķ��׽��̽����β��
		if (runProcess != nullptr) {
			if (runProcess->remainTime > 0) {
				processQueue.push_back(*runProcess);
			}
			else {
				finishedProcess.push_back(*runProcess);
			}
			processQueue.pop_front();
		}

		// ��ʾ��������״̬��
		if (!processQueue.empty()) {
			cout << "���������еĽ��̺�Ԥ������ʱ�䣺";
			for (auto it = processQueue.begin(); it != processQueue.end(); ++it) {
				cout << it->name << "(" << it->remainTime << ") ";
			}
			cout << endl;
		}
		else {
			cout << "��������Ϊ�ա�" << endl;
		}
		
		// ��ʾ����ɵĽ��̡�
		if (!finishedProcess.empty()) {
			cout << "����ɵĽ��̣�";
			for (auto it = finishedProcess.begin(); it != finishedProcess.end(); ++it) {
				cout << it->name << " ";
			}
			cout << endl;
		}

		// ��ʾ��δ����Ľ���
		if (!processToRun.empty()) {
			cout << "��δ����Ľ��̵Ľ�������Ԥ�Ƶ���ʱ�䣺";
			for (auto it = processToRun.begin(); it != processToRun.end(); ++it) {
				cout << it->name << "(" << it->arrivedAt << ") ";
			}
			cout << endl;
		}

		systemClock += 1;
		cout << "========" << endl;
	}
}


int main() {
	IOHelper helper(cin, cout);

	do {
		processCount = helper.nextInt("��������Խ��̵ĸ���");
		if (processCount <= 0) {
			cout << "���̵ĸ����������0�����������롣" << endl;
		}
	} while (processCount <= 0);
	
	bool isRandom = helper.question("������������ɻ����ֶ����룿");
	if (isRandom) {
		randomProcessInfo();
	}
	else {
		inputProcessInfo(helper);
	}
	showProcessToRun();
	Simulate();
}

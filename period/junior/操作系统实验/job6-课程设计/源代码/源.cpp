// 模拟时间片轮转法

#include "util.hpp"
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
using namespace std;


// 进程控制块
struct PCB {
	string name;  // 进程名称
	int arrivedAt;  // 到达时间
	int remainTime;  // 估计运行时间

public:
	PCB(const string& name, int arrivedAt, int remainTime) {
		this->name = name;
		this->arrivedAt = arrivedAt;
		this->remainTime = remainTime;
	}


	// 按到达时间非降序排序的比较函数。
	bool operator < (const PCB& oth) const {
		return this->arrivedAt < oth.arrivedAt;
	}
};


int systemClock;  // 系统时钟
int processCount;  // 系统中的进程个数
vector<PCB> processToRun; // 系统中的所有已安排且尚未到达的进程
deque<PCB> processQueue; // 进程队列
vector<PCB> finishedProcess;  // 完成运行的进程


// 显示系统中所有已安排的进程。
void showProcessToRun() {
	cout << "已安排的进程、到达时间和预计持续时间：" << endl;
	for (PCB pcb : processToRun) {
		cout << pcb.name << '\t' << "" << pcb.arrivedAt << '\t' << pcb.remainTime << endl;
	}
	cout << "========" << endl;
}


// 随机产生进程信息。
void randomProcessInfo() {
	srand(unsigned(time(nullptr)));

	for (int i = 1; i <= processCount; ++i) {
		string name = "P" + to_string(i);
		int arriveAt = rand() % 10;
		int remainTime = 1 + rand() % 10;
		processToRun.push_back(PCB(name, arriveAt, remainTime));
	}
	sort(processToRun.begin(), processToRun.end());  // 按进程到达时间排序。
	cout << "========" << endl;
}


// 输入进程信息。
void inputProcessInfo(IOHelper &helper) {
	for (int i = 1; i <= processCount; ++i) {
		cout << "正在输入第" << i << "个进程的信息：" << endl;
		
		string name = helper.getline("进程名称");
		int arriveAt = helper.nextInt("到达时间");
		int remainTime = helper.nextInt("预计运行时间");
		
		vector<string> failReasons;
		if (name.empty()) {
			failReasons.push_back("进程名不能为空；");
		}
		if (arriveAt < 0) {
			failReasons.push_back("进程到达时间必须大于或等于0；");
		}
		if (remainTime < 1) {
			failReasons.push_back("进程必须运行至少1个时间单位；");
		}

		if (failReasons.empty()) {
			processToRun.push_back(PCB(name, arriveAt, remainTime));
		}
		else {
			for (string reason : failReasons) {
				cout << reason;
			}
			cout << "请重新输入进程信息。" << endl;
			
			--i;
		}
	}
	sort(processToRun.begin(), processToRun.end());  // 按进程到达时间排序。
	cout << "========" << endl;
}


// 模拟进程运行。
void Simulate() {
	while (!processToRun.empty() || !processQueue.empty()) {
		cout << "系统时间：" << systemClock << endl;

		// 选择就绪队列队首进程运行。
		PCB* runProcess = !processQueue.empty() ? &processQueue.front() : nullptr;

		if (runProcess != nullptr) {
			runProcess->remainTime -= 1;  // 模拟进程运行
			if (runProcess->remainTime > 0) {
				cout << "进程" << runProcess->name << "运行，剩余运行时间：" << runProcess->remainTime << "。" << endl;
			}
			else {
				cout << "进程" << runProcess->name << "运行完毕。" << endl;
			}
		}
		else {
			cout << "系统空转。" << endl;
		}

		// 进程到达并加入就绪队列队尾。
		while (!processToRun.empty() && processToRun.front().arrivedAt == systemClock) {
			PCB pcb = processToRun.front();
			processToRun.erase(processToRun.begin());
			processQueue.push_back(pcb);

			cout << "进程" << pcb.name << "到达，预计运行时间：" << pcb.remainTime << "。" << endl;
		}

		// 将已经运行过的队首进程接入队尾。
		if (runProcess != nullptr) {
			if (runProcess->remainTime > 0) {
				processQueue.push_back(*runProcess);
			}
			else {
				finishedProcess.push_back(*runProcess);
			}
			processQueue.pop_front();
		}

		// 显示就绪队列状态。
		if (!processQueue.empty()) {
			cout << "就绪队列中的进程和预计运行时间：";
			for (auto it = processQueue.begin(); it != processQueue.end(); ++it) {
				cout << it->name << "(" << it->remainTime << ") ";
			}
			cout << endl;
		}
		else {
			cout << "就绪队列为空。" << endl;
		}
		
		// 显示已完成的进程。
		if (!finishedProcess.empty()) {
			cout << "已完成的进程：";
			for (auto it = finishedProcess.begin(); it != finishedProcess.end(); ++it) {
				cout << it->name << " ";
			}
			cout << endl;
		}

		// 显示尚未到达的进程
		if (!processToRun.empty()) {
			cout << "尚未到达的进程的进程名和预计到达时间：";
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
		processCount = helper.nextInt("请输入测试进程的个数");
		if (processCount <= 0) {
			cout << "进程的个数必须大于0，请重新输入。" << endl;
		}
	} while (processCount <= 0);
	
	bool isRandom = helper.question("数据是随机生成还是手动输入？");
	if (isRandom) {
		randomProcessInfo();
	}
	else {
		inputProcessInfo(helper);
	}
	showProcessToRun();
	Simulate();
}

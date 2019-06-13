// LineSimulation.cpp
// 模拟银行排队队列。

// 约束条件：
// 银行服务时间取09:00至11:30。
// 银行有5个服务窗口，分别为1号窗口~5号窗口。
// 取1分钟为单位时间，单位时间内有不超过2名新顾客到来。
// 每位顾客办理业务的时间不超过8分钟。
// 第一个顾客的顺序号为1。

#include <iostream>
#include <sstream>
#include <queue>
#include <vector>

using namespace std;

// 用数字表示时间
// eg. 928表示09:28
using Moment = int;

// 客户
struct Client {
    int minutes_left_to_finish;  // 业务剩余需要花费的时间
    Moment arrived_moment;       // 到达的时刻
    Moment served_moment = 0;    // 开始办理业务的时刻
};


// 银行窗口
struct Window {
    int serving_client_seqnum = 0;    // 正在被服务的客户的ID；为0表示窗口空闲。
    int served_client_count   = 0;    // 已完成服务的顾客数量
};


const Moment bank_opens_moment = 900, bank_close_moment = 1130;  // 银行的开门时间和关门时间
Moment current_moment;      // 当前时间
vector<Client> wait_queue;  // 顾客的等待队列；WaitQueue[0]表示第一位来银行的客户（其顺序号为1）。
vector<Window> windows;     // 银行的窗口；Windows[0]表示银行的1号窗口。
int next_client_seqnum;     // 下一个等待的客户的顺序号


// 显示moment时刻。
void ShowMoment(Moment moment) {
    int hh = moment / 100 % 100;
    int mm = moment % 100;
    cout << "== ";
    cout << (hh < 10 ? to_string(0) + to_string(hh) : to_string(hh));
    cout << ":";
    cout << (mm < 10 ? to_string(0) + to_string(mm) : to_string(mm));
    cout << " ==";
}


// 显示顺序号为seqnum的顾客的信息。
void ShowClient(int seqnum) {
    Client &client = wait_queue[seqnum - 1];
    cout << "[顾客" << seqnum << "] ";
    cout << "(剩余" << client.minutes_left_to_finish << "min) ";
    if (client.served_moment == 0) {  // 尚未轮到该客户办理业务。
        cout << "(等待" << current_moment - client.arrived_moment << "min)";
    } else {  // 客户正在办理业务或已经完成业务。
        cout << "(等待" << client.served_moment - client.arrived_moment << "min)";
    }
}


// 显示第winnum号窗口的情况。
void ShowWindow(int winnum) {
    Window & window = windows[winnum - 1];
    cout << "{窗口" << winnum <<  "} ";
    if (window.serving_client_seqnum == 0) {  // 窗口空闲
        cout << "空闲";
    } else {
        ShowClient(window.serving_client_seqnum);
    }
    cout << endl;
}


// 显示等待队列
void ShowWaitQueue() {
    for (int i = next_client_seqnum - 1; i < wait_queue.size(); ++i) {
        ShowClient(i + 1); cout << endl;
    }
}


// 显示程序的输出格式约定等帮助信息。
void Introduction() {
    cout << "银行营业时间：",
    ShowMoment(bank_opens_moment), cout << "-", ShowMoment(bank_close_moment),
    cout << endl << endl;

    cout << "程序的输出格式为：" << endl;
    cout << "小时:分钟" << endl;
    cout << "{窗口号} [正在办理业务的顾客的顺序号] (得到服务前等待的时间数)" << endl;
    cout << "正在等待的顾客数：(数量)"  << endl;
    cout << "[等待办理业务的顾客的顺序号] (得到服务前等待的时间数)" << endl;
}


// 银行开门（初始化全局变量）。
void OpenBank() {
    current_moment = bank_opens_moment;
    wait_queue.clear();
    windows.clear();
    next_client_seqnum = 1;
    for (int i = 0; i < 5; ++i) {  // 开启5个窗口。
        windows.push_back(Window());
    }
}


// 判断银行是否在营业时间内。
bool BankIsOpen() {
    return current_moment <= bank_close_moment; 
}


// 推进一个单位时间。
void ProceedToNextMoment() {
    ++current_moment;
}


// 新客户到达。
void NewClientsArrive() {
    int new_client_count = rand() % 3;  // 限定单位时间新到达的客户不超过2人。
    while (new_client_count--) {
        int minute_to_finish = rand() % 8 + 1;  // 限定每位顾客的业务时间不超过8分钟。
        int arrived_moment = current_moment;
        wait_queue.push_back(Client{minute_to_finish, arrived_moment, 0});  // 将新到达的客户加入等待队列。
    }
}


// 窗口处理客户信息
void WindowsDealWithClients() {
    for (int i = 0; i < 5; ++i) {  // 遍历窗口
        Window & window = windows[i];
        if (window.serving_client_seqnum != 0) {  // 窗口忙
            Client & serving_client = wait_queue[window.serving_client_seqnum - 1];
            serving_client.minutes_left_to_finish -= 1;  // 剩余需要花费的业务办理时间减1

            if (serving_client.minutes_left_to_finish == 0) {  // 客户已办理完业务
                window.serving_client_seqnum = 0;
                window.served_client_count += 1;
            }
        }
        if (window.serving_client_seqnum == 0) {  // 窗口空闲
            if (next_client_seqnum - 1 < wait_queue.size()) {  // 若有顾客正在等待办理业务
                window.serving_client_seqnum = next_client_seqnum;
                wait_queue[next_client_seqnum - 1].served_moment = current_moment;
                next_client_seqnum += 1;
            }
        }
    }
}


// 显示实时信息，
// 包括：显示每个窗口正在办理业务的顾客的顺序号、
// 目前等待的顾客人数以及每个顾客在得到服务之前已经等待的分钟数。
void ShowRealtimeStatus() {
    ShowMoment(current_moment); cout << endl;;
    
    for (int i = 1; i <= 5; ++i) {
        ShowWindow(i);
    }

    cout << "正在等待的客户数量：" << (int(wait_queue.size()) - next_client_seqnum + 1) << endl;
    ShowWaitQueue();
}


// 显示最终统计数据，
// 包括：顾客的平均等待时间和每个窗口服务的顾客数。
void ShowOverallStatistics() {
    // 统计顾客的平均等待时间
    double total_wait_time = 0;
    for (int i = 0; i < wait_queue.size(); ++i) {
        Client & client = wait_queue[i];
        total_wait_time += (
            client.served_moment != 0 ? 
                client.served_moment - client.arrived_moment
                : current_moment - client.arrived_moment
        );
    }
    double average_wait_time = total_wait_time / wait_queue.size();
    cout << "顾客平均等待时间：" << average_wait_time << "min" << endl;

    for (int i = 1; i <= 5; ++i) {  // 遍历5个窗口，显示每个窗口服务的顾客数量
        cout << i << "号窗口服务的顾客数量：" << windows[i-1].served_client_count << endl;
    }
}


// 返回所有的客户是否都办理完了业务。
bool AllClientsAreDone() {
    for (int i = 0; i < 5; ++i) {
        if (windows[i].serving_client_seqnum != 0) return false;
    }
    return true;
}


int main() {
    Introduction();

    cout << "--------------------------------" << endl;
    OpenBank();
    cout << "银行上班。" << endl;
    
    cout << "--------------------------------" << endl;
    while (BankIsOpen() || !AllClientsAreDone())
    {
        if (BankIsOpen()) NewClientsArrive();
        WindowsDealWithClients();
        ShowRealtimeStatus();
        ProceedToNextMoment();
        cout << endl;
    }
    cout << "银行下班。" << endl;
    
    cout << "--------------------------------" << endl;
    ShowOverallStatistics();
}

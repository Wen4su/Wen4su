#include<iostream>
#include<queue>
#include<map>
using namespace std;
//进程控制块
struct PCB {
	string ID;//进程ID
	double arrivalTime;//到达处理机时间
	double remainTime;//剩余服务时间
	double priority;//优先级(越小优先级越高)
	//其他信息省略...
};
//短作业优先调度类(SJF)[非抢占式]
class SJF :private Base {
public:
	SJF(PCB* pcbs, int len) {
		run(pcbs,len);
	}
	void run(PCB* pcbs, int len) {
		double curTime = 0.0;//当前时间
		int i = 0;//pcbs的下标
		while (!pq.empty() || i < len) {//①当优先队列不为空或还有进程没运行
			//每个进程运行期间可能有其他进程加入
			//因此需要将运行期间加入的进程放入优先队列中
			for (; i < len; ++i) {
				if (pcbs[i].arrivalTime <= curTime) {//②进程到达时间小于等于当前时间
					pq.push(&amp;pcbs[i]);
				}
				else {
					break;
				}
			}
			//如果当前优先队列中没有进程
			//说明在当前时间运行完了已到达的进程
			//但是可能后续还有进程
			//当前时间就要跳到后续进程的到达时间
			if (pq.empty()) {//③
				if (i == len) {
					//说明运行结束,可以退出了
					break;
				}
				else {//后续还有进程到来
					curTime = pcbs[i].arrivalTime;
				}
			}
			//可能同时有多个进程到来
			//多以需要便利加入
			for (; i < len; ++i) {//④
				if (curTime == pcbs[i].arrivalTime) {
					pq.push(&amp;pcbs[i]);
				}
				else {
					break;
				}
			}

			PCB* curRun = pq.top();//⑤
			pq.pop();
			times[curRun->ID] = { curTime - curRun->arrivalTime,curRun->remainTime };//⑥
			curTime += curRun->remainTime;
		}
	}
	void show() {
		this->printTime();
	}
};
void sjf() {
	cout << "短作业优先算法:" << endl;
/*
	由于在设计优先队列对比的优先级是根据pcb中的优先级对比的,
	但是这里需要根据时间来对比优先级,
	将剩余时间直接赋值给优先级用于对比
*/
	PCB pcbs[4] = { {"1号",8.0,2.0,2.0},{"2号",8.4,1.0,1.0},{"3号",8.8,0.5,0.5},{"4号",9.0,0.2,0.2} };
	SJF sjf(pcbs,4);
	sjf.show();
}
int main() {
	sjf();
}


#include<iostream>
#include<queue>
#include<map>
using namespace std;
//���̿��ƿ�
struct PCB {
	string ID;//����ID
	double arrivalTime;//���ﴦ���ʱ��
	double remainTime;//ʣ�����ʱ��
	double priority;//���ȼ�(ԽС���ȼ�Խ��)
	//������Ϣʡ��...
};
//����ҵ���ȵ�����(SJF)[����ռʽ]
class SJF :private Base {
public:
	SJF(PCB* pcbs, int len) {
		run(pcbs,len);
	}
	void run(PCB* pcbs, int len) {
		double curTime = 0.0;//��ǰʱ��
		int i = 0;//pcbs���±�
		while (!pq.empty() || i < len) {//�ٵ����ȶ��в�Ϊ�ջ��н���û����
			//ÿ�����������ڼ�������������̼���
			//�����Ҫ�������ڼ����Ľ��̷������ȶ�����
			for (; i < len; ++i) {
				if (pcbs[i].arrivalTime <= curTime) {//�ڽ��̵���ʱ��С�ڵ��ڵ�ǰʱ��
					pq.push(&amp;pcbs[i]);
				}
				else {
					break;
				}
			}
			//�����ǰ���ȶ�����û�н���
			//˵���ڵ�ǰʱ�����������ѵ���Ľ���
			//���ǿ��ܺ������н���
			//��ǰʱ���Ҫ�����������̵ĵ���ʱ��
			if (pq.empty()) {//��
				if (i == len) {
					//˵�����н���,�����˳���
					break;
				}
				else {//�������н��̵���
					curTime = pcbs[i].arrivalTime;
				}
			}
			//����ͬʱ�ж�����̵���
			//������Ҫ��������
			for (; i < len; ++i) {//��
				if (curTime == pcbs[i].arrivalTime) {
					pq.push(&amp;pcbs[i]);
				}
				else {
					break;
				}
			}

			PCB* curRun = pq.top();//��
			pq.pop();
			times[curRun->ID] = { curTime - curRun->arrivalTime,curRun->remainTime };//��
			curTime += curRun->remainTime;
		}
	}
	void show() {
		this->printTime();
	}
};
void sjf() {
	cout << "����ҵ�����㷨:" << endl;
/*
	������������ȶ��жԱȵ����ȼ��Ǹ���pcb�е����ȼ��Աȵ�,
	����������Ҫ����ʱ�����Ա����ȼ�,
	��ʣ��ʱ��ֱ�Ӹ�ֵ�����ȼ����ڶԱ�
*/
	PCB pcbs[4] = { {"1��",8.0,2.0,2.0},{"2��",8.4,1.0,1.0},{"3��",8.8,0.5,0.5},{"4��",9.0,0.2,0.2} };
	SJF sjf(pcbs,4);
	sjf.show();
}
int main() {
	sjf();
}


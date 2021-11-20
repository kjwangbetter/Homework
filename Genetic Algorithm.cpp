#include <iostream>
#include<cmath>
#include<vector>
#include <cstdlib>
using namespace std;

class group;
class individual;

class individual {
	friend group;
private:
	double fx;
	double fitness;
	double x;
public:
	int chromosome[16];
	individual();
	void recal();
	void operator=(const individual& ind) {
		for (int i = 0; i < 16; i++) {
			this->chromosome[i] = ind.chromosome[i];
		}
		this->x = ind.x;
		this->fx = ind.fx;
		this->fitness = ind.fitness;
	}    //重载取代操作
	~individual() {};
};		//个体类

individual::individual() {
	for (int i = 0; i < 16; i++) {
		chromosome[i] = int(rand()) % 2;
	}
	double tmp = 0;
	for (int i = 15; i >= 0; i--) {
		tmp = chromosome[i] + tmp / 2;
	}
	tmp = tmp * 8;
	this->x = tmp - 1;
	this->fx = x * sin(x);
	this->fitness = exp(fx);
}   //利用随机数，随机创建个体

void individual::recal() {
	double tmp = 0;
	for (int i = 15; i >= 0; i--) {
		tmp = chromosome[i] + tmp / 2;
	}
	tmp = tmp * 8;
	this->x = tmp - 1;
	this->fx = x * sin(x);
	this->fitness = exp(fx);
}     //在每次个体染色体发生变化时，重新计算x与fx与fitness

class group {
private:
	individual individuals[10];
	double reproductionrate = 0.8, mutationrate = 0.1;
public:
	group() {};
	void reproduction();
	void mutation();
	void selection(individual* children, int childrennum);
	void crossover(individual* children, int fathernum, int mothernum, int i);
	void coutvalue(int i);
	~group() {};
};  //群体类


void group::reproduction() {
	vector<int> reproductionnum;
	for (int i = 0; i < 10; i++) {
		if (rand() / RAND_MAX <= reproductionrate) {
			reproductionnum.push_back(i);
		}
	}  //生殖个体选择
	individual children[10];
	for (int i = 0; i < reproductionnum.size() / 2; i++) {
		int fathernum = reproductionnum[2 * i];
		int mothernum = reproductionnum[2 * i + 1];
		crossover(children, fathernum, mothernum, i);
	}
	int tmpsize = reproductionnum.size() / 2;
	selection(children, tmpsize * 2);
}

void exchange(individual& father, individual& mother, int lcross, int rcross) {
	if (lcross == rcross) return;
	int tmp[16];
	for (int i = lcross; i <= rcross; i++) {
		tmp[i] = father.chromosome[i];
		father.chromosome[i] = mother.chromosome[i];
		mother.chromosome[i] = tmp[i];
	}
	father.recal();
	mother.recal();
}//完成随机染色体交互换

void group::crossover(individual* children, int fathernum, int mothernum, int i) {
	int lcross, rcross;
	int tmp1 = int(rand()) % 16;
	int tmp2 = int(rand()) % 16;
	lcross = min(tmp1, tmp2);
	rcross = max(tmp1, tmp2);
	children[2 * i] = this->individuals[fathernum];
	children[2 * i + 1] = this->individuals[mothernum];
	exchange(children[2 * i], children[2 * i + 1], lcross, rcross);

}//完成繁殖过程

void group::selection(individual* children, int childrennum) {
	double sumfit = 0;
	int groupnum = 10 + childrennum;
	for (int i = 0; i < 10; i++) {
		sumfit += individuals[i].fitness;
	}
	for (int i = 0; i < childrennum; i++) {
		sumfit += children[i].fitness;
	}
	double pinterval[20];;
	double tmp = 0;
	bool selectflag[20];
	for (int i = 0; i < 10; i++) {
		if (i == 0) {
			pinterval[i] = this->individuals[i].fitness / sumfit;
			tmp = pinterval[i];
			selectflag[i] = false;
			continue;
		}
		pinterval[i] = individuals[i].fitness / sumfit + tmp;
		tmp = pinterval[i];
		selectflag[i] = false;
	}
	for (int i = 0; i < childrennum; i++) {
		pinterval[10 + i] = children[i].fitness / sumfit + tmp;
		tmp = pinterval[10 + i];
		selectflag[10 + i] = false;
	}
	int tmpgroupnum = groupnum;
	while (groupnum > 10) {
		double selectrate = rand() / double(RAND_MAX);
		for (int i = 0; i < tmpgroupnum; i++) {
			if (i == 0 && pinterval[i] > selectrate && selectflag[i] == false) {
				selectflag[i] = true;
				groupnum--;
				break;
			}
			if (i!=0&&pinterval[i] > selectrate && pinterval[i - 1] <= selectrate && selectflag[i] == false) {
				selectflag[i] = true;
				groupnum--;
				break;
			}
		}
	}
	int winnum = 10;
	for (int i = 0; i < 10; i++) {
		if (selectflag[i]) {
			while (selectflag[winnum]&& winnum < tmpgroupnum) {
				winnum++;
			}
			if (winnum >= tmpgroupnum) break;
			individuals[i] = children[winnum - 10];
			winnum++;
		}
	}//选择淘汰个体

}

void group::mutation() {
	vector<int> mutationnum;
	for (int i = 0; i < 10; i++) {
		if (rand() / double(RAND_MAX) <= mutationrate) {
			mutationnum.push_back(i);
		}
	}  //变异个体选择
	for (int i = 0; i < mutationnum.size(); i++) {
		int num = mutationnum[i];
		int nummut = int(rand()) % 16;
		this->individuals[num].chromosome[nummut] = (this->individuals[num].chromosome[nummut] == 0) ? 1 : 0;
		this->individuals[num].recal();
	}
}

void group::coutvalue(int i) {
	//for (int i = 0; i < 10; i++) {
		//cout << "后代" << i << "号的X值为" << this->individuals[i].x << '\n';
		//cout << "对应函数值为" << this->individuals[i].fx << endl;
		
	//}
	double tmp=100;
	int tmpnum;
	for (int i = 0; i < 10; i++) {
		if (tmp > this->individuals[i].fx) {
			tmp = this->individuals[i].fx;
			tmpnum = i;
		}
	}
	cout <<"the individual "<<this->individuals[tmpnum].x<<" with the best fitness score in "<< i <<" generation" << endl;
}//输出各代最优对象

int main() {
	group example;
	srand(time(0));
	for (int i = 0; i < 50; i++) {
		example.mutation();
		example.reproduction();
		example.coutvalue(i);
	}
	return 0;
}
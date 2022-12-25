#ifndef BS_MOORE_SCHEDULER_H
#define BS_MOORE_SCHEDULER_H
#include "process.h"

extern const int PAGE_SIZE;
extern const int FRAME_TABLE_SIZE;
extern const int MAX_VIRTUAL_ADDRESS;

extern vector<char> RAM;
extern vector<vector<char>> HDD;
extern vector<pair<Page*, Process*>> LOOK_UP_TABLE;

class Scheduler {
public:
	Scheduler();
	vector<Process*> getBlockedProcesses() const;
	vector<Process*> getReadyProcesses() const;
	bool existsRunningProcess();
	void blockRunningProcess(Process* process);
	void deleteRunningProcess(Process* process);
	void deleteBlockedProcess(Process* process);
	void startProcess();
	void updateWait();
	int stopProcess(Process* process);
	Process* getLastBlockedProcess();
	Process* getRunningProcess();
	void loadNewProcess(string fileName);
	~Scheduler();

private:
	vector<Process*> blockedProcesses;
	vector<Process*> readyProcesses;
};


#endif //BS_MOORE_SCHEDULER_H

#ifndef BS_MOORE_SCHEDULER_H
#define BS_MOORE_SCHEDULER_H
#include "process.h"

class Scheduler {
public:
	Scheduler();
	vector<Process*> getBlockedProcesses() const;
	vector<Process*> getReadyProcesses() const;
	void blockRunningProcess();
	void deleteRunningProcess();
	void deleteBlockedProcess(Process* process);
	void startRunningProcess();
	void updateWait();
	Process* getRunningProcess();
	Process* loadNewProcess(string &fileName);
	~Scheduler();

private:
	vector<Process*> blockedProcesses;
	vector<Process*> readyProcesses;
};


#endif //BS_MOORE_SCHEDULER_H

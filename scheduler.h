#ifndef BS_MOORE_SCHEDULER_H
#define BS_MOORE_SCHEDULER_H
#include "process.h"

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

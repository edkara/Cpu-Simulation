#ifndef BS_MOORE_CPU_H
#define BS_MOORE_CPU_H
#include "scheduler.h"

class Cpu {
public:
	Cpu();
	Cpu(int accumulator, int programCounter, int tact);
	void setAccumulator(int accumulator);
	int getAccumulator();
	void setProgramCounter(int programCounter);
	int getProgramCounter();
	void setTact(int tact);
	int getTact();
	pair<string,string> parseCommand(string command);

	void load(int n);
	void add(int n);
	void subtract(int n);
	void init(Scheduler* scheduler, string fileName);
	void peripheral(Scheduler* scheduler, Process* process);
	void execute(Scheduler* scheduler, Process* process);
	void stop(Scheduler* scheduler);
	~Cpu();
private:
	int accumulator;
	int programCounter;
	int tact;
};


#endif //BS_MOORE_CPU_H

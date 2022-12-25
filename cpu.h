#ifndef BS_MOORE_CPU_H
#define BS_MOORE_CPU_H
#include "scheduler.h"
#include "mmu.h"

class Cpu {
public:
	Cpu();
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
	void read(int n);
	void write(int n);
	void init(Scheduler* scheduler, string fileName);
	void peripheral(Scheduler* scheduler, Process* process);
	void execute(Scheduler* scheduler, MMU* mmu);
	~Cpu();
private:
	int accumulator;
	int programCounter;
	int tact;
};

void updateAccessTime();
void updateDisk();



#endif //BS_MOORE_CPU_H

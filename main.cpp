#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "cpu.h"


int main() {
	Cpu* cpu = new Cpu();
	Scheduler* scheduler = new Scheduler();
	string fileName = "init";
	cpu->init(scheduler, fileName);
	return 0;
}
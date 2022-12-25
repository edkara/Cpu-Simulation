#ifndef BS_MOORE_MMU_H
#define BS_MOORE_MMU_H
#include <iostream>
#include "process.h"
#include "scheduler.h"

using namespace std;

class MMU {
public:
	MMU() = default;
	int getPhysicalAddressWhenNotPresent(Process* process, Page* page, int offset, int pageId, bool modified);
	int convertToPhysicalAddress(const string &address, Process* process, bool modified = false);
	~MMU() = default;
private:
};

int swap(bool accessed, bool modified);
int NRU();
void loadInRAM(pair<Page*, Process*> toLoad, int pageId);



#endif //BS_MOORE_MMU_H

#include "mmu.h"


//TODO: W100 out of range - wenn all frames inside physical - NRU check
int MMU::getPhysicalAddressWhenNotPresent(Process* process, Page* page, int offset, int pageId ,bool modified) {
	int tmp = 0;
	if(LOOK_UP_TABLE.size() < FRAME_TABLE_SIZE) {				// See if enough place in physical
		int pageFrameNumber = LOOK_UP_TABLE.size();
		page->setPresentBit(true);
		page->setReferencedBit(true);
		page->setPageFrameId(pageFrameNumber );
		page->setAccessTime(0);
		page->setModifiedBit(modified);
		LOOK_UP_TABLE.push_back(make_pair(page, process));
		tmp = ( pageFrameNumber * PAGE_SIZE ) + offset;
	} else {
		int indexOfSwapped = NRU();								// I could swap only inside lookup table
		if(indexOfSwapped < FRAME_TABLE_SIZE) {
			LOOK_UP_TABLE.at(indexOfSwapped).first = page;
			LOOK_UP_TABLE.at(indexOfSwapped).second = process;
			pair<Page*, Process*> tmpSwapped = LOOK_UP_TABLE.at(indexOfSwapped);
			loadInRAM(tmpSwapped, pageId);
			page->setPresentBit(true);
			page->setReferencedBit(true);
			page->setPageFrameId(indexOfSwapped);
			page->setAccessTime(0);
			page->setModifiedBit(modified);
			tmp = page->getPageFrameId() * PAGE_SIZE + offset;
		} else {
			cout << "I wanted to swap frame, " << indexOfSwapped << " which was not in look up table!" << endl;
		}
	}
	return tmp;
}


//TODO: see if works
int MMU::convertToPhysicalAddress(const string &address, Process* process, bool modified) {
	int physicalAddress = 0;
	int virtualAddress = stoul(address, 0, 16);			// convert given hex. string to int address
																		// 3ff will be 1023 = max address
	if(virtualAddress <= MAX_VIRTUAL_ADDRESS) {							// valid address
		int pageId = virtualAddress / PAGE_SIZE;						// 1024 / 64 = 16 -> pageId => outside; 960 / 64 = 15 -> pageId => inside
		int offset = virtualAddress % PAGE_SIZE;						// take position inside page table
		Page* page = process->getPageTable().at(pageId);

		if(page->isPresent()) {											// Page in RAM
			page->setReferencedBit(true);						// 0, 1, 2, 3 in physical
			page->setAccessTime(0);
			page->setModifiedBit(modified);
			physicalAddress = page->getPageFrameId() * PAGE_SIZE + offset;
		} else {														// Page does not exist
			physicalAddress = getPhysicalAddressWhenNotPresent(process, page, offset, pageId, modified);
		}
	} else {
		cout << "The given address was not valid!" << endl;
	}
	return physicalAddress;
}

//TODO: see if works
int swap(bool accessed, bool modified) {
	int pageIndex = 0;
	vector<pair<Page*, Process*>>::iterator it;
	for (it = LOOK_UP_TABLE.begin(); it != LOOK_UP_TABLE.end(); ) {
		Page* page = (*it).first;
		if(page->isReferenced() == accessed && page->isModified() == modified ) {
			Process* process = (*it).second;
			for(int j = 0; j < PAGE_SIZE; j++) {
				HDD.at(process->getIndex()).at(page->getPageFrameId() * PAGE_SIZE + j) =
						RAM.at(page->getPageFrameId() * PAGE_SIZE + j );
			}
			page->setPresentBit(false);
			page->setReferencedBit(false);
			pageIndex = distance(LOOK_UP_TABLE.begin(), it);
			return pageIndex;
		}
		else {
			++it;
		}
	}
	return 99999;
}

int NRU() {
	int index = swap(false, false);
	if (index < FRAME_TABLE_SIZE){
		return index;
	}
	index = swap(false, true);
	if (index < FRAME_TABLE_SIZE){
		return index;
	}
	index = swap(true, false);
	if (index < FRAME_TABLE_SIZE) {
		return index;
	}
	index = swap(true, true);
	if (index < FRAME_TABLE_SIZE) {
		return index;
	}
	return 9999;
}

void loadInRAM(pair<Page*, Process*> toLoad, int pageId) {
	Page* page = toLoad.first;
	Process* process = toLoad.second;
	//virtual addresse - in HDD. statt pageFrameId - pageID
	for(int j = 0; j < PAGE_SIZE; j++) {
		RAM.at(page->getPageFrameId() * PAGE_SIZE + j) =
				HDD.at(process->getIndex()).at( pageId * PAGE_SIZE + j);
	}
}

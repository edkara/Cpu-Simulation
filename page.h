#ifndef BS_MOORE_PAGE_H
#define BS_MOORE_PAGE_H


class Page {
public:
	Page();
	int getPageFrameId();
	void setPageFrameId(int index);
	bool isModified();
	void setModifiedBit(bool modified);
	bool isPresent();
	void setPresentBit(bool present);
	bool isReferenced();
	void setReferencedBit(bool accessed);
	~Page();
private:
	int pageFrameId; 		//where in ram
	bool modified;			//dirty bit = when write => 1. When 1, Page frame in hdd, otherwise (when 0) overwrite
	bool present;			//when present = 1, otherwise = 0. When 0 and access => page error
	bool referenced;		//when write or load (every time) => 1.
};


#endif //BS_MOORE_PAGE_H

#include "page.h"

Page::Page() {
	this->pageFrameId = 0;
	this->present = 0;
	this->modified = 0;
	this->referenced = 0;
    this->pageError = 0;
}

int Page::getPageFrameId() {
	return this->pageFrameId;
}

void Page::setPageFrameId(int index) {
	this->pageFrameId = index;
}


bool Page::isModified() {
	return this->modified;
}

void Page::setModifiedBit(bool modified) {
	this->modified = modified;
}

bool Page::isPresent() {
	return this->present;
}

void Page::setPresentBit(bool present) {
	this->present = present;
}

bool Page::isReferenced() {
	return this->referenced;
}

void Page::setReferencedBit(bool accessed) {
	this->referenced = accessed;
}

int Page::getPageError() {
    return this->pageError;
}

void Page::setPageError(int n) {
    this->pageError = n;
}

Page::~Page() {

}

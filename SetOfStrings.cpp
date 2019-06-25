#include "SetOfStrings.h"
/*
 * Deliverable 2
 * */
using namespace std;

bool SetOfStrings::isEmpty() {
	if (setv.empty())
		return true;
	else
		return false;
}

int SetOfStrings::size() {
	return (int) setv.size();
}

bool SetOfStrings::isMember(string s) {
	p = setv.begin();
	while (p != setv.end()) {
		if (*p == s)
			return true;
		++p;
	}
	return false;
}

void SetOfStrings::insertElement(string s) {
	if (!isMember(s)) {
		setv.push_back(s);
	}
}

int SetOfStrings::Find(string s) {
	int position = -1;
	for (unsigned int i = 0; i < setv.size(); i++) {
		if (setv.at(i) == s) {
			position = i;
		}
	}
	return position;
}

void SetOfStrings::removeElement(string s) {
	int pos = Find(s);
	if (pos != -1) {
		setv.erase(setv.begin() + pos);
	}
}

SetOfStrings *SetOfStrings::setUnion(SetOfStrings *s) {
	SetOfStrings *s1 = new SetOfStrings();
	if (!s) {
		throw 10;
	} else {
		for (unsigned int i = 0; i < setv.size(); i++) {
			s1->insertElement(setv.at(i));
		}
		for (int i = 0; i < s->size(); i++) {
			s1->insertElement(s->returnElement(i));
		}

		return s1;
	}
}

string SetOfStrings::returnElement(int index) {
	int i = 0;
	if (index > size())
		return "\n";
	p = setv.begin();
	while (p != setv.end()) {
		if (i == index)
			return *p;
		else {
			++i;
			++p;
		}
	}
	return "\n";
}

bool SetOfStrings::isEqual(SetOfStrings *s) {
	if (!s) {
			throw 10;//error code for null pointer as input
		} else {
			if (setv.size() != (unsigned)s->size()) {
				return false;
			}

			for (unsigned int i = 0; i < setv.size(); i++) {
				if (!(s->isMember(setv.at(i)))) {
					return false;
				}
			}
			return true;
		}
}

bool SetOfStrings::subset(SetOfStrings *s) {
	if (!s) {
		throw 10;
	} else {
		if ((unsigned)s->size() > setv.size()) {
			return false;
		}

		for (int i = 0; i < s->size(); i++) {
			if (!isMember(s->returnElement(i))) {//check if element exists in the set being compared to
				return false;
			}
		}
		return true;
	}
}

SetOfStrings *SetOfStrings::product(SetOfStrings *s) {
		if (!s) {
			throw 10;
		} else {
			string element;
			SetOfStrings *out = new SetOfStrings();
			for (unsigned int i = 0; i < setv.size(); i++) {
				for (int j = 0; j < s->size(); j++) {
					element = setv.at(i);
					element += ",";
					element += s->returnElement(j);
					out->insertElement(element);//add product to set to return
				}
			}

			return out;
		}
}

SetOfStrings *SetOfStrings::setIntersection(SetOfStrings *set1) {
	SetOfStrings *s1 = new SetOfStrings();
	if (!set1) {
		throw 10;
	} else {
		for (int i = 0; i < set1->size(); i++) {
			if (isMember(set1->returnElement(i))) {
				s1->insertElement(set1->returnElement(i));//set with intersection
			}
		}
		return s1;
	}
}


#ifndef STRINGRELATION_H_
#define STRINGRELATION_H_
#include "SetOfStrings.h"
#include <sstream>

class StringRelation : public SetOfStrings{
	private:
		// the set over which the relation is created
		SetOfStrings *set1;
	    vector<int> weight; // weight vector
	    vector<bool> BFSVisited;
		string path; // string for dijkstra's path

		// String splitter, which is a helper function
		vector<string> makeTokens(string input);
		//given string "a,b" return string "b,a"
		string computeDual(string);
		//given "a", returns "a,a"
		string createReflexiveElement(string s);
		//return true if s is of the form "a,a"
		bool isReflexiveElement(string s);
		//return true if s1 is the first component of s2
		//e.g. s1=a and s2=a,b
		bool isFirstComponent(string s1, string s2);
		//Return the second component of the string "a,b" as b
		string returnSecondComponent(string s);
		//This function converts the product of set1 with itself passed as "s" into
		//A relation called "n". This is so that we can print the elements of the

		// Return the weight of an edge
		int getWeight(string s);

		string createElement(string s, string s1);

		SetOfStrings* directlyConnected(string element);

	public:
		void setInput(SetOfStrings *s);
		//creates a relation that is identical to the product set of set1
		bool isValid();
		bool isValidElement(string s);
		bool isReflexive();
		bool isSymmetric();
		bool isTransitive();
		bool isEquivalence();
		bool addWeight(string element, int weight);
		SetOfStrings *computeEquivalenceClass(string element);
		void insertElement(string s, int weight);

		// Finding the shortest path
		int computeShortest(string source, string destination);

		SetOfStrings *getSet();

		int returnWeight(int index);
		bool Reachable(string first, string second);
		vector<string> bestPath(string start, string end);
};
#endif

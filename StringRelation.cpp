//deliverable 2
#include "StringRelation.h"
#define INF 32766

//will be used for calling the ColourText() method in print() functions
SetOfStrings *S = new SetOfStrings();

//This helps by assigning the composition member
//s is the pointer to the input set
//and R \subseteq s \times s
void StringRelation::setInput(SetOfStrings *s) {
	set1 = s;
	//if (!isValid()) {
	//set1 = 0;
	//throw "invalid relation";
	//}
}

//check if the relation provided as input is a
//valid relation i.e., R \subseteq S \times S
//Return true when valid; false otherwise
bool StringRelation::isValid() {
	//Create the product of set1 with itself
	//out= set1 /times set1
	SetOfStrings *out = new SetOfStrings();	//needs to be deleted
	if (!set1) {
		throw 10; //error code
	} else {
		out = set1->product(set1);
		if (out->subset(this)) {
			return true;
		} else {
			return false;
		}
	}
	//Overloaded printRelation method used for printing the relation that is
	//equal to the product set
	//printRelation(out);
	//this->printRelation();

}

bool StringRelation::isValidElement(string s) {
	//Create the product of set1 with itself
	//out= set1 /times set1
	//SetOfStrings *out = new SetOfStrings();
	SetOfStrings * out;	//needs to be deleted
	if (!set1) {
		throw 10; //error code
	} else {
		out = set1->product(set1);
		if (out->isMember(s)) {
			return true;
		} else {
			return false;
		}
	}
	//Overloaded printRelation method used for printing the relation that is
	//equal to the product set
	//printRelation(out);
	//this->printRelation();

}

//This is one of the main helper function provided as a
//tokenizer to parse relational elements and separate them into components
//This takes a relation element in the form "a,b" and returns
//a string vector containing "a" and "b"
vector<string> StringRelation::makeTokens(string next) {
	vector<string> out;
	vector<string>::iterator p;
	char *a = new char[next.length() + 1];
	strcpy(a, next.c_str());
	char* token = std::strtok(a, ",");
	int index = 0;
	while (token != NULL) {
		out.push_back(token);
		token = std::strtok(NULL, ",");
		index++;
	}
	return out;
}

//helper function that returns the string "a,a" when input is "a"
string StringRelation::createReflexiveElement(string s) {
	string next, next1;
	next = s;
	next1 = next;
	next.append(",");
	next.append(next1);
	return next;
}
//helper function that returns creates an element out of 2 inputs
string StringRelation::createElement(string s, string s1) {
	string next, next1;
	next = s;
	next1 = s1;
	next.append(",");
	next.append(next1);
	return next;
}

//helper function that creates a dual of "a,b" as "b,a"
string StringRelation::computeDual(string s) {

	vector<string> tokens = makeTokens(s);
	vector<string>::iterator p;
	p = tokens.begin();
	string other, other1;
	while (p != tokens.end() - 1) {
		other = *p;
		other1 = *(p + 1);
		other1.append(",");
		other1.append(other);
		++p;
	}
	return other1;
}

//return "b" if s is of the form "a,b"
string StringRelation::returnSecondComponent(string s) {
	vector<string> tokens;
	vector<string>::iterator p;
	tokens = makeTokens(s);
	p = tokens.begin();
	return *(p + 1);
}

//check if s is of the form "a,a" and return true if so
//return false otherwise
bool StringRelation::isReflexiveElement(string s) {
	//string first = s.at(0);
	vector<string> tokens = makeTokens(s);
	if (tokens.at(0) == tokens.at(1)) {
		return true;
	} else {
		return false;
	}
}

//check if the relation is reflexive
//if for all s \in set1, (s,s) \in r then reflexive
bool StringRelation::isReflexive() {
	if (!set1) {
		throw 10; //error code
	} else {
		for (int i = 0; i < set1->size(); i++) {
			if (!isMember(createReflexiveElement(set1->returnElement(i)))) {
				return false;
			}
		}
		return true;
	}
}
//check if the relation is symmetric
//if for any s1,s2 \in set1, (s1,s2) \in R implies (s2,s1) \in R
bool StringRelation::isSymmetric() {
	for (unsigned int i = 0; i < setv.size(); i++) {
		if (!isReflexiveElement(setv.at(i))) {
			if (!isMember(computeDual(setv.at(i)))) {
				return false;
			}
		}
	}
	return true;
}

//s1 is of the form "a" while s2 is of the form "p,q"
//if a==p then return true
bool StringRelation::isFirstComponent(string s1, string s2) {
	if (s1.at(0) == s2.at(0)) {
		return true;
	} else {
		return false;
	}
}

//check if the relation is transitive
// for all x,y,z \in set1, (x -> y AND y -> z) implies x -> z
//in other words if (a,b) & (a,c) then (c,b) must be true for the set to be transitive
bool StringRelation::isTransitive() {
//You are required to implement this
	string tmpConnected;
	SetOfStrings tmpSet;
	for (unsigned int i = 0; i < setv.size(); i++) {
		if (!isReflexiveElement(setv.at(i))) {
			if (!isMember(computeDual(setv.at(i)))) {
				tmpSet.insertElement(setv.at(i));
			}
		}
	}

	vector<string> tokens;
	SetOfStrings tmpSetOfSingles;

	//make a set of connected nodes
	for (int i = 0; i < tmpSet.size(); i++) {
		tokens = makeTokens(tmpSet.returnElement(i));
		tmpSetOfSingles.insertElement(tokens.at(0));
		tmpSetOfSingles.insertElement(tokens.at(1));
	}

	//check for connection if not connected return false
	for (int i = 0; i < tmpSetOfSingles.size(); i++) {
		if (i == (tmpSetOfSingles.size() - 1)) {
			if (!(tmpSet.isMember(
					createElement(tmpSetOfSingles.returnElement(i),
							tmpSetOfSingles.returnElement(0)))
					|| tmpSet.isMember(
							computeDual(
									createElement(
											tmpSetOfSingles.returnElement(i),
											tmpSetOfSingles.returnElement(0)))))) {
				return false;
			}
		} else {
			if (!(tmpSet.isMember(
					createElement(tmpSetOfSingles.returnElement(i),
							tmpSetOfSingles.returnElement(i + 1)))
					|| tmpSet.isMember(
							computeDual(
									createElement(
											tmpSetOfSingles.returnElement(i),
											tmpSetOfSingles.returnElement(
													i + 1)))))) {
				return false;
			}
		}
	}

	return true;
}

//return true if the relation is an equivalence relation
//return false otherwise
bool StringRelation::isEquivalence() {

	if (isReflexive() && isSymmetric() && isTransitive()) {
		return true;
	} else {
		return false;
	}

}

//Given a member of set1, this function determine the equivalence class
//for this element s1 i.e. {s| (s,s1) \in R and R is a equivalence relation} (can a set have an equivalence class without being equivalent)
SetOfStrings* StringRelation::computeEquivalenceClass(string element) {
	SetOfStrings *out = new SetOfStrings();
	vector<string> tokens;
	SetOfStrings tmpSetOfSingles;

	if (!isEquivalence()) {
		throw "is Equivalence is false";
	} else {

		//int posOfElement;

		for (unsigned int i = 0; i < setv.size(); i++) {
			tokens = makeTokens(returnElement(i));
			tmpSetOfSingles.insertElement(tokens.at(0));
			tmpSetOfSingles.insertElement(tokens.at(1));
		}

		//posOfElement = tmpSetOfSingles.Find(element);
		if (isMember(createReflexiveElement(element))) {
			out->insertElement(element);
		}

		for (int i = 0; i < tmpSetOfSingles.size(); i++) {
			if (isMember(
					createElement(element, tmpSetOfSingles.returnElement(i)))//checks whether an element with the input element is a memeber of the function
					|| isMember(
							computeDual(
									createElement(element,
											tmpSetOfSingles.returnElement(
													i))))) {
				out->insertElement(tmpSetOfSingles.returnElement(i));//add the connected element to the equivalence class
			}
		}

		return out;
	}
}

//insert element and it's related weight
void StringRelation::insertElement(string s, int w) {
	if (!isMember(s)) {
		setv.push_back(s);
		weight.push_back(w);
	}
}

SetOfStrings * StringRelation::getSet() {

	return set1;
}

int StringRelation::returnWeight(int index) {

	return weight.at(index);

}

//find directly connected nodes
SetOfStrings* StringRelation::directlyConnected(string element) {

	SetOfStrings *out = new SetOfStrings();
	vector<string> tokens;
	SetOfStrings tmpSetOfSingles;

	//int posOfElement;
	//make an array of all elements in the SetOfStrings (not needed?)
	for (unsigned int i = 0; i < setv.size(); i++) {
		tokens = makeTokens(returnElement(i));
		tmpSetOfSingles.insertElement(tokens.at(0));
		tmpSetOfSingles.insertElement(tokens.at(1));
	}

	//find if the element is connected to itself
	//posOfElement = tmpSetOfSingles.Find(element);
	if (isMember(createReflexiveElement(element))) {
		out->insertElement(element);
	}

	//searches for elements connected to the element
	for (int i = 0; i < tmpSetOfSingles.size(); i++) {
		if (isMember(
				createElement(element, tmpSetOfSingles.returnElement(i)))) {
			out->insertElement(tmpSetOfSingles.returnElement(i));//inset node in set with directly connected nodes
		}
	}
	return out;//return set of neighbors/ directly connected
}

bool StringRelation::Reachable(string first, string second) {
	if (!set1) {
		throw "no set found";
	} else {
		if (!(set1->isMember(first)) || !(set1->isMember(second))) {
			throw "Value 1 does not exist in set";
		} else {
			SetOfStrings * connectedNodes = new SetOfStrings;
			SetOfStrings * directlyConnectedNodes; //needs to be deleted
			directlyConnectedNodes = directlyConnected(first);
			//add directly connected nodes to the list of connetedNodes
			for (int i = 0; i < directlyConnectedNodes->size(); i++) {
				connectedNodes->insertElement(
						directlyConnectedNodes->returnElement(i));
			}

			//loop through all the directly connected nodes to find the directly connected nodes
			//of those connected nodes until there are no more nodes to add
			for (int i = 0; i < connectedNodes->size(); i++) {
				directlyConnectedNodes = directlyConnected(
						connectedNodes->returnElement(i));
				for (int j = 0; j < directlyConnectedNodes->size(); j++) {
					connectedNodes->insertElement(
							directlyConnectedNodes->returnElement(j));
				}
			}
			//check if the second input is a member of the connected nodes setOfStrings
			if (connectedNodes->isMember(second)) {
				delete connectedNodes;
				delete directlyConnectedNodes;//delete objects on the heap
				return true;
			} else {
				delete connectedNodes;
				delete directlyConnectedNodes;
				return false;
			}
		}
	}
}

//Dijktras algorithm for find the best path
vector<string> StringRelation::bestPath(string start, string end) {
	if(set1->isMember(start) && set1->isMember(end)){
	vector<string> path;
	vector<int> distance; //of all vertices
	vector<int> previous;
	vector<bool> isVisited;
	vector<string> out;//vector with distance information and the path travelled

	SetOfStrings neighbors;

	SetOfStrings notVisited = *set1;

	//initialize
	//set distance to all nodes to inf and set all previous to null
	for (int i = 0; i < notVisited.size(); i++) {
		distance.push_back(INF);
		isVisited.push_back(false);
		previous.push_back(0);
	}
		distance.at(notVisited.Find(start)) = 0;	//set start distance to 0


	int min = INF + 1;
	int currentNode = notVisited.Find(start);
	int tentD = 0;

	int unvisitedSize = 1;//set size of visited needs to be bigger than 0

	while (unvisitedSize > 0) {

		min = INF + 1;//higher than infinity so that there aren't any undefined connections

		for (int i = 0; i < notVisited.size(); i++) {
			if (!isVisited.at(i)) {
				//check is smallest
				if (distance.at(i) < min) {
					min = distance.at(i);	//save Min
					currentNode = i;	//save node with the min value
				}
			}
		}
		//set currentNode isVisited to true
		isVisited.at(currentNode) = true;
		neighbors = *directlyConnected(notVisited.returnElement(currentNode));

		//for all neighbors of currentNode
		for (int i = 0; i < neighbors.size(); i++) {
			tentD = distance.at(currentNode)+ returnWeight(Find(createElement(notVisited.returnElement(currentNode),neighbors.returnElement(i))));
			//if alt dist < than dist[v]
			if (tentD < distance.at(notVisited.Find(neighbors.returnElement(i)))) {
				distance.at(notVisited.Find(neighbors.returnElement(i))) = tentD;
				previous.at(notVisited.Find(neighbors.returnElement(i))) = currentNode;//update the previously visited nodes
			}
		}
		//check the number of unvisited nodes
		unvisitedSize = 0;
		for (unsigned int i = 0; i < isVisited.size(); i++) {
			if (isVisited.at(i) == false) {
				unvisitedSize++;
			}
		}
		if (end == set1->returnElement(currentNode)) {

			stringstream ss;
			ss << distance.at(notVisited.Find(end));
			if(distance.at(notVisited.Find(end)) == INF){
				return out;
			}
			string w = ss.str();

			out.push_back(w);
			int tmpCurrent = currentNode;
			while(tmpCurrent != notVisited.Find(start)){
				out.push_back(notVisited.returnElement(tmpCurrent));
				if(tmpCurrent != previous.at(tmpCurrent)){
				tmpCurrent = previous.at(tmpCurrent);
				}else {
					return out;
				}
			}

			out.push_back(start);
			return out;
		}
	}

	return out;
	}else{
		throw "Value 1 does not exist in set";
	}
}


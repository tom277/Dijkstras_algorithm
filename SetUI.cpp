//deliverable 2
#include "SetUI.h"

SetUI::SetUI() {
	TopicScreen();
}

// Greet the user and shows the developer name.
void SetUI::TopicScreen() {
	system("clear");
	cout
			<< "----------------------------------------------------------------------"
			<< endl; // Replace the name with yours
	cout << "\033[1;31mSet Calculator\033[0m\nDeveloper Name: "
			<< "\033[1;34m Tomas Antunes (tant836, 684726671)\033[0m\n";
	cout << "To know available commands, please type 'help'" << endl;
	cout
			<< "---------------------------------------------------------------------"
			<< endl;
}

//Read from from the file
bool SetUI::ReadFromFile(string filename, SetOfStrings *ss, StringRelation *sr,
		bool verbose) {

	string line;
	ifstream infile(filename.c_str());

	//return false if the file does not exist
	if (!infile.good())
		return false;

	getline(infile, line); // Get the first line to extract set members
	line.erase(0, 2); // Remove '//' in the line

	vector<string> element;
	int i = 0;
	size_t found;
	while ((found = line.find(",", i)) != std::string::npos) {
		element.push_back(line.substr(i, found - i));
		i = found + 1;
	}
	if (verbose && line.size() > 0) {
		cout << line << endl;
	}
	element.push_back(line.substr(i));

	//add elements into ss set of strings
	for (unsigned int j = 0; j < element.size(); j++) {
		ss->insertElement(element.at(j));
	}
	sr->setInput(ss);

	getline(infile, line); // To bypass the second line
	//read the rest of the file.
	while (getline(infile, line)) {

		if (verbose && line.size() > 0) {
			cout << line << endl;
		}
		//erase spaces
		line.erase(remove(line.begin(), line.end(), ' '), line.end());

		//check if the line is empty
		if (line.size() == 0) {

		} else {

			// find } as the finisher for file reading
			if (line.find("}") != string::npos)
				break;
			// fetch set and relation in the line
			if (line.size() < 2) {

				print("File reading was successful", GREEN);
				print(
						"Please type 'list' to view the members and relations defined in the graph",
						GREEN);
				return true;
			} else {
				if (!getFromLine(ss, sr, line)) {
					return false;
				}
			}
		}
	}
	infile.close();

	print("File reading was successful", GREEN);
	print(
			"Please type 'list' to view the members and relations defined in the graph",
			GREEN);
	return true;

}

//get information from the line
bool SetUI::getFromLine(SetOfStrings *ss, StringRelation *sr, string line) {

	vector<string> element;
	int i = 0;
	size_t found;
	while ((found = line.find("->", i)) != std::string::npos) {
		element.push_back(line.substr(i, found - i));
		i = found + 2;
	}
	element.push_back(line.substr(i, line.find("[", i) - i));

	if (element.size() < 2) {
		return true;
	} else {
		string pair(element.at(0) + "," + element.at(1));

		//extract weight information
		string temp = "";

		int weight = 0;
		int pos2 = 0;
		for (unsigned int j = 0; j < line.length(); j++) {
			if (line.at(j) == 34) {
				pos2 = j;
				break;
			}
		}

		for (unsigned int x = pos2 + 1; x < line.length(); x++) {

			if (line.at(x) == 34) {
				break;
			} else if (line.at(x) != ' ') {
				temp += line.at(x);
			}

		}

		stringstream tmpSS(temp);
		tmpSS >> weight;

		//if the element is valid add to the SetOfStrings else return false
		if (sr->isValidElement(pair)) {
			sr->insertElement(pair, weight);
			return true;
		} else {
			return false;
		}
	}

}

void SetUI::printError(string reason) {
	// error message if the command cannot be understood
	if (reason.compare("command") == 0) {
		cout
				<< ColorText(
						"Command cannot be understood. \n Please enter help to see the available commands\n",
						RED);
	}
	// error message if the command argument is incorrect
	else if (reason.compare("argument") == 0) {
		cout << ColorText("Incorrect command arguments!\n", RED);
		cout
				<< ColorText(
						"Please type help to know about the command arguments\n",
						RED);
	} else if (reason.compare("reading from file") == 0) {

		cout
				<< ColorText(
						"Error reading from file!\n There might not be a file with that name or the relation is invalid",
						RED);

	} else if (reason.compare("no set to list") == 0) {

		cout << ColorText("There is no set to list!\n", RED);

	} else if (reason.compare("not reachable") == 0) {

		cout << ColorText("Not reachable\n", RED);

	} else if (reason.compare("Value 1 does not exist in set") == 0) {

		cout << ColorText("One or more values do not exist in set", RED);

	} else if (reason.compare("Value 2 does not exist in set") == 0) {

		cout << ColorText("One or more values do not exist in set", RED);

	} else if (reason.compare("invalidSet") == 0) {

		cout << ColorText("This set is invalid", RED);

	} else if (reason.compare("start not found") == 0) {

		cout << ColorText("The starting node has not been found", RED);

	} else if (reason.compare("no set found") == 0) {

		cout << ColorText("There is no set", RED);

	}
	cout << endl;
}

string SetUI::GetCommand() {
	string commandInput;
	cout << ">> ";

	getline(cin, commandInput);
	return commandInput;
}

//prints the help message (Completed)
void SetUI::Help() {
	cout << "Currently available commands:\n";
	cout
			<< "Anything inside <> bracket is an optional argument, while [] bracket contains a must argument.\n\n";
	cout << left << setw(45) << ColorText("	help", RED) << left << setw(50)
			<< "Show help." << endl << endl;
	cout << left << setw(45) << ColorText("	ls <path> ", RED) << left
			<< setw(50)
			<< "Identical to the ls shell command. If a path is given, then"
			<< endl;
	cout << left << setw(41) << "" << left << setw(50)
			<< "the program returns all the files in that path." << endl
			<< endl;
	cout << left << setw(45) << ColorText("	clear ", RED) << left << setw(50)
			<< "Identical to the clear shell command. Clear the screen." << endl
			<< endl;
	cout << left << setw(45) << ColorText("	open [file_path] <-v>", RED) << left
			<< setw(50)
			<< "Open a file. If the file does not exist, then program returns"
			<< endl;
	cout << left << setw(41) << "" << left << setw(50)
			<< "an error message. If -v (verbose) option is enabled (e.g., open a.txt -v),"
			<< endl;
	cout << left << setw(41) << "" << left << setw(50)
			<< "then each line in the file is printed on console while reading."
			<< endl << endl;
	cout << left << setw(45) << ColorText("	list", RED) << left << setw(50)
			<< "List all the members of set and relation." << endl << endl;
	cout << left << setw(45) << ColorText("	check [OPTION] ", RED) << left
			<< setw(50)
			<< "Check the relation. The option has to be provided. Options are:"
			<< endl;
	cout << left << setw(41) << "" << left << setw(50) << "-r (reflexive)"
			<< endl;
	cout << left << setw(41) << "" << left << setw(50) << "-s (symmetric)"
			<< endl;
	cout << left << setw(41) << "" << left << setw(50) << "-t (transtivie)"
			<< endl;
	cout << left << setw(41) << "" << left << setw(50)
			<< "-e (equivalence relation)" << endl << endl;
	cout << left << setw(45) << ColorText("	eqclass [VALUE]", RED) << left
			<< setw(50)
			<< "Show equivalence class of the given [VALUE = Set member]."
			<< endl;
	cout << left << setw(41) << "" << left << setw(50)
			<< "If VALUE is not a member of set, then the program returns"
			<< endl;
	cout << left << setw(41) << "" << left << setw(50) << "an error message."
			<< endl << endl;
	cout << left << setw(45) << ColorText("	reachable [VALUE1] [VALUE2]", RED)
			<< left << setw(50)
			<< "This command checks if two given members are connected to each other"
			<< endl;
	cout << left << setw(41) << "" << left << setw(50)
			<< "If any of VALUE1 and VALUE2 is not a member of the set, then it"
			<< endl;
	cout << left << setw(41) << "" << left << setw(50)
			<< "returns an error message." << endl << endl;
	cout << left << setw(45) << ColorText("	path [VALUE1] [VALUE2]", RED)
			<< left << setw(50)
			<< "Apply Dijkstra algorithm to find the shortest path." << endl;
	cout << left << setw(41) << "" << left << setw(50)
			<< "VALUE1 and VALUE2 are members of the set. VALUE1 is the starting node, and VALUE2 is the destination."
			<< endl << endl;
	cout << left << setw(45) << ColorText("	exit", RED) << left << setw(50)
			<< "Terminate the program." << endl;
	cout << "\n\n";
}

/*
 void SetUI::printShortestPath(int distance, string path) {
 cout << "  The shortest path distance: "
 << ColorText(std::to_string(distance), GREEN) << endl;
 cout << "  The path is: " << ColorText(path, BLUE) << endl;
 }*/

string SetUI::ColorText(string s, COLOR color) {
	string temp;
	switch (color) {
	case RED:
		temp = "\033[1;31m" + s + "\033[0m";
		break;
	case BLUE:
		temp = "\033[1;34m" + s + "\033[0m";
		break;
	case YELLOW:
		temp = "\033[1;33m" + s + "\033[0m";
		break;
	case GREEN:
		temp = "\033[1;32m" + s + "\033[0m";
		break;
	case WHITE:
		temp = "\033[1;37m" + s + "\033[0m";
		break;
	default:
		temp = "\033[0m" + s;
		break;
	}
	return temp;
}

//Pring function for the String realation
void SetUI::print(StringRelation *s) {
	cout << "The elements of the set: " << endl;

	SetOfStrings * temp;

	int weight = 0;

	temp = s->getSet();

	int i = 0, j = 0;
	j = temp->size();
	while (i < j) {
		string next;
		next = temp->returnElement(i);
		if (i != j - 1) {
			cout << ColorText("(", BLUE) << ColorText(next, BLUE)
					<< ColorText(")", BLUE) << ColorText(", ", BLUE);
			++i;
		} else {
			cout << ColorText("(", BLUE) << ColorText(next, BLUE)
					<< ColorText(")", BLUE);
			++i;
		}
	}

	cout << endl << endl;

	cout << "The elements of the relation that is equal to the product set are:"
			<< endl << ColorText("{", BLUE);
	i = 0, j = 0;
	j = s->size();
	while (i < j) {
		string next;
		next = s->returnElement(i);
		weight = s->returnWeight(i);
		if (i != j - 1) {
			cout << ColorText("(", BLUE) << ColorText(next, BLUE)
					<< ColorText(")", BLUE) << ColorText("[", WHITE) << weight
					<< ColorText("] ", WHITE) << ColorText(", ", BLUE);
			++i;
		} else {
			cout << ColorText("(", BLUE) << ColorText(next, BLUE)
					<< ColorText(")", BLUE) << ColorText("[", WHITE) << weight
					<< ColorText("] ", WHITE);
			++i;
		}
	}
	cout << ColorText("}", BLUE) << "\n";
	//delete temp;
}

//list the members of the string relation
int SetUI::ListMembers(StringRelation* model) {
	if (model != 0) {
		cout << ColorText("The members of the ", WHITE)
				<< ColorText("sets", BLUE) << ColorText(" are:", WHITE) << endl;

		SetOfStrings * temp;

		int weight = 0;

		temp = model->getSet();

		int i = 0, j = 0;
		j = temp->size();

		cout << ColorText("{", WHITE);
		while (i < j) {
			string next;
			next = temp->returnElement(i);
			if (i != j - 1) {
				cout << ColorText(next, BLUE) << ColorText(", ", WHITE);
				++i;
			} else {
				cout << ColorText(next, BLUE);
				++i;
			}
		}
		cout << ColorText("}", WHITE) << endl;

		cout << ColorText("The members of the ", WHITE)
				<< ColorText("relations", YELLOW) << ColorText(" are:", WHITE)
				<< endl;
		i = 0, j = 0;
		j = model->size();

		cout << ColorText("=> {", WHITE);
		while (i < j) {
			string next;
			next = model->returnElement(i);
			weight = model->returnWeight(i);
			if (i != j - 1) {
				cout << ColorText("(", WHITE) << ColorText(next, YELLOW)
						<< ColorText(")", WHITE) << ColorText(", ", YELLOW);
				++i;
			} else {
				cout << ColorText("(", WHITE) << ColorText(next, YELLOW)
						<< ColorText(")", WHITE);
				++i;
			}
		}
		cout << ColorText("}", WHITE) << "\n";

		cout << ColorText("The associated ", WHITE)
				<< ColorText("weights", WHITE) << ColorText(" are:", WHITE)
				<< endl;
		i = 0, j = 0;
		j = model->size();

		cout << ColorText("=> {", WHITE);
		while (i < j) {
			weight = model->returnWeight(i);
			if (i != j - 1) {
				cout << weight << ColorText(", ", WHITE);
				++i;
			} else {
				cout << weight;
				++i;
			}
		}
		cout << ColorText("}", WHITE) << "\n";

		return 1;
	} else {
		printError("no set to list");
		return 1;
	}
}

//print a message with a set of strings
void SetUI::print(SetOfStrings *s, string message) {
	cout << message << ": " << endl;
	if (s != 0) {
		int i = 0, j = 0;
		j = s->size();
		while (i < j) {
			string next;
			next = s->returnElement(i);
			if (i != j - 1) {
				cout << ColorText("(", BLUE) << ColorText(next, BLUE)
						<< ColorText(")", BLUE) << ColorText(", ", BLUE);
				++i;
			} else {
				cout << ColorText("(", BLUE) << ColorText(next, BLUE)
						<< ColorText(")", BLUE);
				++i;
			}
		}

		cout << endl << endl;
	} else {
		printError("no set to list");		//make an error message
	}
}

//simple print function
void SetUI::print(string s, COLOR color) {

	cout << ColorText(s, color) << "\n";

}

//find the reflexivity
void SetUI::reflexive(StringRelation *s) {
	if (s != 0) {
		if (s->isReflexive()) {
			print("=> This Set is Reflexive", GREEN);
		} else {
			print("=> This Set NOT is Reflexive", RED);
		}
	} else {
		printError("no set found");
	}
}

//find symmetry
void SetUI::symmetric(StringRelation *s) {
	if (s != 0) {
		if (s->isSymmetric()) {
			print("=> This Set is Symmetric", GREEN);
		} else {
			print("=> This Set NOT is Symmetric", RED);
		}
	} else {
		printError("no set found");
	}
}

//find transitivity
void SetUI::transtivie(StringRelation *s) {
	if (s != 0) {
		if (s->isTransitive()) {
			print("=> This Set is Transtivie", GREEN);
		} else {
			print("=> This Set NOT is Transtivie", RED);
		}
	} else {
		printError("no set found");
	}
}

//find the equivalence relation
void SetUI::equivalence_relation(StringRelation *s) {
	if (s != 0) {
		if (s->isEquivalence()) {
			print("=> This Set is Equivalence", GREEN);
		} else {
			print("=> This Set is NOT an equivalence set", RED);
		}
	} else {
		printError("no set found");
	}
}

//find and print the equivalence relation
void SetUI::equivalence_relation(StringRelation *s, string element) {//eqclass
	SetOfStrings * eqClass = 0;
	if (s != 0) {
		try {
			eqClass = s->computeEquivalenceClass(element);
			//string message("Equivalence Class");
			print(eqClass, "Equivalence Class");
		} catch (const char * e) {
			print("This Set is NOT an equivalence set", RED);//is Equivalence is false
		}
	} else {
		printError("no set found");
	}
}

//call is reachable in StringRelation and print out whether the points are reachable or not
void SetUI::isReachable(StringRelation *s, string first, string second) {
	if (s != 0) {
		try {
			if (s->Reachable(first, second)) {
				print(first + " is reachable from " + second, GREEN);
			} else {
				print(first + " is NOT reachable from " + second, RED);
			}
		} catch (const char * e) {
			printError(e);
		}
	} else {
		printError("no set found");
	}
}

//call the best path function in StringRelation and print out the path
void SetUI::Path(StringRelation *s, string first, string second) {
	if (s != 0) {
		try {
			vector<string> in = s->bestPath(first, second);
			if (in.size() > 0) {
				string distance = in.at(0);

				cout << endl << "The shortest path distance: "
						<< ColorText(distance, GREEN) << endl;

				cout << "The path is: ";
				for (unsigned int i = in.size() - 1; i > 1; i--) {
					cout << ColorText(in.at(i), BLUE) << " => ";
				}
				cout << ColorText(in.at(1), BLUE) << endl;

			} else {
				print("No path found", RED);
			}
		} catch (const char * e) {
			printError(e);
		}
	} else {
		printError("no set found");
	}
}

//clear the screen
void SetUI::Clear() {
	printf("\033c");
	TopicScreen();
}

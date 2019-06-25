/* This is the controller part for your program.
 * In this file, students are required to complete the "control" logic.
 * The controller accepts keyboard inputs from the user through View, and manipulate data in Model.
 * Then, the result from Model is sent back to user through View.
 * Think about the design before the actual implementation.
 */
#include "SetControl.h"

SetControl::SetControl() {
	cout << "Initializing the calculator, please wait! ... \n" << endl;

	//instansiate all members
	setUI = new SetUI();
}

SetControl::~SetControl() {
	//dispose all members missing stuff
	delete setUI;
}

bool SetControl::Run() {
	string command;
	string tmpCommand;

	StringRelation * sr = 0;

	//invoke the main user interaction
	while (true) {

		//show the menu and get user command
		command = "";
		tmpCommand = setUI->GetCommand();

		unsigned int j = 0;
		while (j < tmpCommand.size() && (tmpCommand.at(j)) == ' ') {
			j++;
		}

		//only add the command without the spaces
		for (unsigned int x = j; x < tmpCommand.size(); x++) {
			command += tmpCommand.at(x);
		}

		int argc = 0;

		// string tokenizer to split string by using " " as the separator.
		// stores the values in argv array while the number of argument is argc.
		vector<string> argv;
		int i = 0;
		size_t found;
		while ((found = command.find(" ", i)) != std::string::npos) {
			argv.push_back(command.substr(i, found - i));
			i = found + 1;
		}
		argv.push_back(command.substr(i));

		argc = argv.size();
		// if enter is pressed
		if (argc == 0)
			continue;

		//help command execution (Completed)
		if (argv.at(0).compare("help") == 0) {
			setUI->Help();
		}
		//ls command execution (Completed)
		else if (argv.at(0).compare("ls") == 0) {
			if (!(argc == 1 || argc == 2)) {
				setUI->printError("argument");
				continue;
			}
			if (argc == 2) {
				string cmd(argv[1]);
				cmd = "ls " + cmd;
				system(cmd.c_str());
			} else
				system("ls");
		} else if (argv.at(0).compare("open") == 0) {
			bool verbose = false;
			if (!(argc == 2 || argc == 3)) {
				setUI->printError("argument");
				continue;
			}
			SetOfStrings *temps = new SetOfStrings();
			StringRelation *tempr = new StringRelation();
			if (argc == 2)
				if (setUI->ReadFromFile(argv.at(1), temps, tempr, verbose)) {
					sr = tempr;	//save the tempr String Relation to a more permanent variable
				} else {
					setUI->printError("reading from file");
				}

			else {
				//if the file cannot be read
				if (!setUI->ReadFromFile(argv.at(1), temps, tempr,
						(argv.at(2).compare("-v") == 0) ? true : false)) {
					setUI->printError("reading from file");
					continue;
				} else {
					sr = tempr;	//save the tempr String Relation to a more permanent variable
				}
			}
		} else if (argv.at(0).compare("list") == 0) {
			if (!sr) {
				setUI->printError("no set to list");
			} else {
				setUI->ListMembers(sr);
			}
		} else if (argv.at(0).compare("clear") == 0) {
			setUI->Clear();
		} else if (argv.at(0).compare("check") == 0) {
			if (argv.size() == 2) {		//check arguments
				if (argv.at(1).compare("-r") == 0) {
					if (!sr) {
						setUI->printError("no set found");
					} else {
						setUI->reflexive(sr);
					}
				} else if (argv.at(1).compare("-s") == 0) {
					if (!sr) {
						setUI->printError("no set found");
					} else {
						setUI->symmetric(sr);
					}
				} else if (argv.at(1).compare("-t") == 0) {
					if (!sr) {
						setUI->printError("no set found");
					} else {
						setUI->transtivie(sr);
					}
				} else if (argv.at(1).compare("-e") == 0) {
					if (!sr) {
						setUI->printError("no set found");
					} else {
						setUI->equivalence_relation(sr);
					}
				} else {
					setUI->printError("command");
				}
			} else {
				setUI->printError("argument");//wrong arguments
			}
		} else if (argv.at(0).compare("eqclass") == 0) {
			if (!sr) {		//check null pointer
				setUI->print("no set to list", RED);
			} else {
				if (argv.size() == 2) {
					string element = argv.at(1);
					setUI->equivalence_relation(sr, element);
				} else {
					setUI->printError("command");
				}
			}
		} else if (argv.at(0).compare("reachable") == 0) {
			if (argv.size() == 3) {
				if (!sr) {
					setUI->print("no set to list", RED);
				} else {
					string first = argv.at(1);
					string second = argv.at(2);

					setUI->isReachable(sr, first, second);
				}
			} else {
				setUI->printError("command");
			}
		} else if (argv.at(0).compare("path") == 0) {
			if (!sr) {
				setUI->print("no set to list", RED);
			} else {
				if (argv.size() == 3) {
					string first = argv.at(1);
					string second = argv.at(2);
					setUI->Path(sr, first, second);
				} else {
					setUI->printError("command");
				}
			}
		}

		else if (argv.at(0).find("exit") != string::npos) {
			exit(0);
		}
		// Command is invalid 
		else {
			setUI->printError("command");
		}

	}

	return true;
}


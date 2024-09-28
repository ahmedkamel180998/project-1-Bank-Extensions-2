#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;
const string clientsFileName = "clients.txt", usersFileName = "users.txt";
void showMainMenuScreen();
void showTransactionsMenuScreen();
void showLoginScreen();
void showManageUsersMenuScreen();

// Bank Project Original Version Before Update

enum enMainMenuOptions
{
	showClientList = 1,
	newClient = 2,
	deleteClient = 3,
	updateClientInfo = 4,
	findClient = 5,
	transaction = 6,
	manageUsers = 7,
	logout = 8
};

struct stClientData
{
	string accountNumber;
	string pinCode;
	string name;
	string phone;
	double accountBalance = 0;
	bool markForDeletion = false;
	bool markForUpdate = false;
};

string readString(string message)
{
	string userText;
	cout << message;
	getline(cin >> ws, userText);
	return userText;
}

char readCharacter(string message)
{
	char userCharacter;
	do
	{
		cout << message;
		cin >> userCharacter;
	} while (userCharacter != 'Y' && userCharacter != 'y' && userCharacter != 'N' && userCharacter != 'n');
	return userCharacter;
}

short readNumberInRange(string message, short from, short to)
{
	short userNumber = 0;
	do
	{
		cout << message;
		cin >> userNumber;
	} while (userNumber < from || userNumber > to);
	return userNumber;
}

stClientData updateClientDataExceptAccountNumber(stClientData client)
{
	cout << "Please Update Client Data:" << endl;
	client.accountNumber = client.accountNumber;
	client.pinCode = readString("\nEnter PinCode ? ");
	client.name = readString("\nEnter Name ? ");
	client.phone = readString("\nEnter Phone ? ");
	cout << "\nEnter Balance ? ";
	cin >> client.accountBalance;
	return client;
}

vector<string> split(string client, string delimiter = "#//#")
{
	vector<string> splitWords;
	string splitWord = "";
	size_t delimiterPosition = 0;

	while ((delimiterPosition = client.find(delimiter)) != client.npos)
	{
		splitWord = client.substr(0, delimiterPosition);
		if (splitWord != "")
			splitWords.push_back(splitWord);
		client.erase(0, delimiterPosition + delimiter.length());
	}
	if (client != "")
		splitWords.push_back(client);
	return splitWords;
}

stClientData saveVectorToStructure(vector<string> splitWords)
{
	stClientData client;
	client.accountNumber = splitWords[0];
	client.pinCode = splitWords[1];
	client.name = splitWords[2];
	client.phone = splitWords[3];
	client.accountBalance = stod(splitWords[4]);
	return client;
}

vector<stClientData> loadClientsDataFromFile(string fileName)
{
	vector<stClientData> clients;

	fstream myFile;
	myFile.open(fileName, ios::in);
	if (myFile.is_open())
	{
		string client = "";
		while (getline(myFile, client))
		{
			if (client != "")
				clients.push_back(saveVectorToStructure(split(client)));
		}
		myFile.close();
	}
	return clients;
}

void printClientData(stClientData client)
{
	cout << "\nThe Following Are The Client Details :" << endl;
	cout << "\nAccount Number  | " << client.accountNumber;
	cout << "\nPinCode         | " << client.pinCode;
	cout << "\nName            | " << client.name;
	cout << "\nPhone           | " << client.phone;
	cout << "\nAccount Balance | " << client.accountBalance << endl;
}

void printClientListScreenHeader(vector<stClientData> clients)
{
	cout << "\t\t\t\t\tClient List (" << clients.size() << ") Client(s)" << endl;
	cout << "-------------------------------------------------------------------------------------------------------" << endl;
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "PinCode";
	cout << "| " << left << setw(40) << "Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Account Balance" << endl;
	cout << "-------------------------------------------------------------------------------------------------------" << endl;
}

void printClientListScreenBodyClient(stClientData client)
{
	cout << "| " << left << setw(15) << client.accountNumber;
	cout << "| " << left << setw(10) << client.pinCode;
	cout << "| " << left << setw(40) << client.name;
	cout << "| " << left << setw(12) << client.phone;
	cout << "| " << left << setw(12) << client.accountBalance << endl;
}

void showClientListScreen()
{
	vector<stClientData> clients = loadClientsDataFromFile(clientsFileName);

	printClientListScreenHeader(clients);
	for (stClientData& c : clients)
		printClientListScreenBodyClient(c);
}

void printGeneralHeader(string message)
{
	cout << "=======================================================================================================" << endl;
	cout << "\t\t\t\t\t" << message << endl;
	cout << "=======================================================================================================" << endl;
}

stClientData readNewClient(vector<stClientData> clients)
{
	stClientData newClient;
	newClient.accountNumber = readString("\nPlease Enter Your Account Number ?  ");
	for (stClientData& c : clients)
	{
		if (c.accountNumber == newClient.accountNumber)
		{
			do
			{
				cout << "\nClient With [" << newClient.accountNumber << "] Already Exists, ";
				newClient.accountNumber = readString("Please Enter Another Account Number ?  ");
			} while (c.accountNumber == newClient.accountNumber);
		}
	}

	newClient.pinCode = readString("\nPlease Enter Your PinCode ?  ");
	newClient.name = readString("\nPlease Enter Your Name ?  ");
	newClient.phone = readString("\nPlease Enter Your Phone ?  ");
	cout << "\nPlease Enter Your Account Balance ?  ";
	cin >> newClient.accountBalance;
	return newClient;
}

string convertClientStructureToRecord(stClientData client, string delimiter = "#//#")
{
	string record = "";
	record += client.accountNumber + delimiter;
	record += client.pinCode + delimiter;
	record += client.name + delimiter;
	record += client.phone + delimiter;
	record += to_string(client.accountBalance);
	return record;
}

void saveRecordToFile(string fileName, string record)
{
	fstream myFile;
	myFile.open(fileName, ios::out | ios::app);
	if (myFile.is_open())
	{
		myFile << record << endl;
	}
	myFile.close();
}

void addNewClient()
{
	vector<stClientData> clients = loadClientsDataFromFile(clientsFileName);
	stClientData client = readNewClient(clients);
	saveRecordToFile(clientsFileName, convertClientStructureToRecord(client));
}

void showAddNewClientScreen()
{
	char addAgain = 'Y';
	do
	{
		system("cls");
		printGeneralHeader("Adding New Client Screen");
		cout << "\nAdding New Client :" << endl;
		addNewClient();
		addAgain = readCharacter("\nClient Added Successfully, Do You Want To Add More Clients ? [Y/N] ?  ");
	} while (toupper(addAgain) == 'Y');
}

bool findClientByAccountNumber(string accountNumber, vector<stClientData> clients, stClientData& client)
{
	for (stClientData& c : clients)
	{
		if (c.accountNumber == accountNumber)
		{
			client = c;
			return true;
		}
	}
	return false;
}

void markClientForDeletionByAccountNumber(string accountNumber, vector<stClientData>& clients)
{
	for (stClientData& c : clients)
	{
		if (c.accountNumber == accountNumber)
		{
			c.markForDeletion = true;
			break;
		}
	}
}

void saveClientsToFile(vector<stClientData>& clients)
{
	fstream myFile;
	myFile.open(clientsFileName, ios::out);
	if (myFile.is_open())
	{
		string client = "";
		for (stClientData& c : clients)
		{
			if (c.markForDeletion == false)
			{
				client = convertClientStructureToRecord(c);
				myFile << client << endl;
			}
		}
		myFile.close();
	}
}

void deleteClientByAccountNumber(string accountNumber, vector<stClientData>& clients)
{
	stClientData client;
	char deleteAgain = 'N';
	if (findClientByAccountNumber(accountNumber, clients, client))
	{
		printClientData(client);

		deleteAgain = readCharacter("\nAre You Sure You Want To Delete Client/ " + client.name + " ? [Y / N] ? ");
		if (toupper(deleteAgain) == 'Y')
		{
			markClientForDeletionByAccountNumber(accountNumber, clients);
			saveClientsToFile(clients);

			// Refresh Clients list
			clients = loadClientsDataFromFile(clientsFileName);
			cout << "\nClient Deleted Successfully!" << endl;
		}
	}
	else
	{
		cout << "\nClient With Account Number (" << accountNumber << ") Not Found!" << endl;
	}
}

void showDeleteClientScreen()
{
	printGeneralHeader("Delete Client Screen");

	vector<stClientData> clients = loadClientsDataFromFile(clientsFileName);
	string accountNumber = readString("\nPlease Enter Your Account Number ?  ");
	deleteClientByAccountNumber(accountNumber, clients);
}

void markClientForUpdateByAccountNumber(string accountNumber, vector<stClientData>& clients)
{
	for (stClientData& c : clients)
	{
		if (c.accountNumber == accountNumber)
		{
			c.markForUpdate = true;
			break;
		}
	}
}

void saveClientsToFileAfterUpdate(vector<stClientData>& clients)
{
	fstream myFile;
	myFile.open(clientsFileName, ios::out);
	if (myFile.is_open())
	{
		string client = "";
		for (stClientData& c : clients)
		{
			if (c.markForUpdate == true)
			{
				c = updateClientDataExceptAccountNumber(c);
				break;
			}
		}
		saveClientsToFile(clients);
		myFile.close();
	}
}

void updateClientByAccountNumber(string accountNumber, vector<stClientData>& clients)
{
	stClientData client;
	char updateAgain = 'N';

	if (findClientByAccountNumber(accountNumber, clients, client))
	{
		printClientData(client);

		updateAgain = readCharacter("\nAre You Sure You Want To Update Client/ " + client.name + " ? [Y / N] ? ");
		if (toupper(updateAgain) == 'Y')
		{
			markClientForUpdateByAccountNumber(accountNumber, clients);
			saveClientsToFileAfterUpdate(clients);
			cout << "\nClient Updated Successfully!" << endl;
		}
	}
	else
		cout << "\nClient With Account Number (" << accountNumber << ") Not Found!" << endl;
}

void showUpdateClientInfoScreen()
{
	printGeneralHeader("Update Client Info Screen");

	vector<stClientData> clients = loadClientsDataFromFile(clientsFileName);
	string accountNumber = readString("\nPlease Enter Your Account Number ?  ");
	updateClientByAccountNumber(accountNumber, clients);
}

void showFindClientScreen()
{
	printGeneralHeader("Find Client Screen");

	vector<stClientData> clients = loadClientsDataFromFile(clientsFileName);
	stClientData client;
	string accountNumber = readString("\nPlease Enter Your Account Number ?  ");

	if (findClientByAccountNumber(accountNumber, clients, client))
	{
		printClientData(client);
	}
	else
		cout << "\nClient With Account Number (" << accountNumber << ") Not Found!" << endl;
}

// Update => Bank Project Extension 1

enum enTransactionsMenuOptions
{
	deposit = 1,
	withdraw = 2,
	totalBalances = 3,
	mainMenu = 4
};

double getDepositOrWithdraw(string message)
{
	double amountOfMoney = 0;
	do
	{
		cout << message;
		cin >> amountOfMoney;
	} while (amountOfMoney <= 0);
	return amountOfMoney;
}

void validateDeposit(vector<stClientData>& clients)
{
	stClientData client;
	char checkTransaction = 'Y';

	string accountNumber = readString("\nPlease Enter Account Number ?  ");
	while (!(findClientByAccountNumber(accountNumber, clients, client)))
	{
		cout << "\nClient With Account Number [" << accountNumber << "] Not Exists." << endl;
		accountNumber = readString("\nPlease Enter Another Account Number ?  ");
	}
	printClientData(client);

	double deposit = getDepositOrWithdraw("\nPlease Enter Deposit Amount ?  ");
	checkTransaction = readCharacter("\nAre You Sure You Want To Perform This Transaction ? [Y/N] ?  ");
	if (toupper(checkTransaction) == 'Y')
	{
		for (stClientData& c : clients)
		{
			if (c.accountNumber == client.accountNumber)
			{
				c.accountBalance += deposit;
				client = c;
				break;
			}
		}
	}
	// update File After Deposit
	saveClientsToFile(clients);

	cout << "\nDone Successfully, Your Balance After Deposit = " << client.accountBalance << endl;
}

void validateWithdraw(vector<stClientData>& clients)
{
	stClientData client;
	char checkTransaction = 'Y';

	string accountNumber = readString("\nPlease Enter Account Number ?  ");
	while (!(findClientByAccountNumber(accountNumber, clients, client)))
	{
		cout << "\nClient With Account Number [" << accountNumber << "] Not Exists." << endl;
		accountNumber = readString("\nPlease Enter Another Account Number ?  ");
	}
	printClientData(client);

	double withdraw = getDepositOrWithdraw("\nPlease Enter Withdraw Amount ?  ");
	while (withdraw > client.accountBalance)
	{
		cout << "Amount Exceeds The Balance, You Can Withdraw Up To : " << client.accountBalance << endl;
		withdraw = getDepositOrWithdraw("Please Enter Another Amount ?  ");
	}

	checkTransaction = readCharacter("Are You Sure You Want To Perform This Transaction ? [Y/N] ?  ");
	if (toupper(checkTransaction) == 'Y')
	{
		for (stClientData& c : clients)
		{
			if (c.accountNumber == client.accountNumber)
			{
				c.accountBalance += (withdraw * -1);
				client = c;
				break;
			}
		}
	}
	// Update File After Withdraw
	saveClientsToFile(clients);

	cout << "\nYour Balance After Withdraw = " << client.accountBalance << endl;
}

void showDepositScreen()
{
	printGeneralHeader("Deposit Screen");

	vector<stClientData> clients = loadClientsDataFromFile(clientsFileName);
	validateDeposit(clients);
}

void showWithdrawScreen()
{
	printGeneralHeader("Withdraw Screen");

	vector<stClientData> clients = loadClientsDataFromFile(clientsFileName);
	validateWithdraw(clients);
}

void printBalancesListScreenHeader(vector<stClientData> clients)
{
	cout << "\t\t\t\t\tBalances List (" << clients.size() << ") Client(s)" << endl;
	cout << "-------------------------------------------------------------------------------------------------------" << endl;
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(40) << "Name";
	cout << "| " << left << setw(12) << "Account Balance" << endl;
	cout << "-------------------------------------------------------------------------------------------------------" << endl;
}

void printBalancesListScreenBodyClient(stClientData client)
{
	cout << "| " << left << setw(15) << client.accountNumber;
	cout << "| " << left << setw(40) << client.name;
	cout << "| " << left << setw(12) << client.accountBalance << endl;
}

void showTotalBalancesScreen()
{
	double totalBalances = 0;
	vector<stClientData> clients = loadClientsDataFromFile(clientsFileName);
	printBalancesListScreenHeader(clients);

	for (stClientData& c : clients)
	{
		printBalancesListScreenBodyClient(c);
		totalBalances += c.accountBalance;
	}
	cout << "-------------------------------------------------------------------------------------------------------" << endl;
	cout << "\t\t\t\t\tTotal Balances = " << totalBalances << endl;
}

void goBackToTransactionsMenu()
{
	cout << "\nPress Any Key to go back to The Previous Menu...  ";
	system("pause >nul");
	system("cls");
	showTransactionsMenuScreen();
}

void goBackToMainMenu()
{
	cout << "\nPress Any Key to go back to The Main Menu...  ";
	system("pause >nul");
	system("cls");
	showMainMenuScreen();
}

void printTransactionsMenuScreenBody()
{
	cout << "\t\t[1] Deposit." << endl;
	cout << "\t\t[2] Withdraw." << endl;
	cout << "\t\t[3] Total Balances." << endl;
	cout << "\t\t[4] Main Menu." << endl;
	cout << "=======================================================================================================" << endl;
}

void performTransactionsMenuScreen()
{
	enTransactionsMenuOptions transactionsOptions = (enTransactionsMenuOptions)readNumberInRange("\nChoose What Do You want To do ? [1 to 4] ?  ", 1, 4);
	switch (transactionsOptions)
	{
	case enTransactionsMenuOptions::deposit:
		system("cls");
		showDepositScreen();
		goBackToTransactionsMenu();
		break;
	case enTransactionsMenuOptions::withdraw:
		system("cls");
		showWithdrawScreen();
		goBackToTransactionsMenu();
		break;
	case enTransactionsMenuOptions::totalBalances:
		system("cls");
		showTotalBalancesScreen();
		goBackToTransactionsMenu();
		break;
	case enTransactionsMenuOptions::mainMenu:
		system("cls");
		goBackToMainMenu();
		break;
	}
}

void showTransactionsMenuScreen()
{
	printGeneralHeader("Transactions Menu Screen");
	printTransactionsMenuScreenBody();
	performTransactionsMenuScreen();
}

// Update => Bank Project Extension 2

enum enManageUsersMenuOptions
{
	listUsers = 1,
	addNewUserManage = 2,
	deleteUser = 3,
	updateUser = 4,
	findUser = 5,
	mainMenuManage = 6
};

struct stUserData
{
	string userName;
	string password;
	short permissions = 0;
	bool markForDeletion = false;
	bool markForUpdate = false;
};
stUserData loginUser;

stUserData saveUserVectorToStructure(vector<string> splitWords)
{
	stUserData user;
	user.userName = splitWords[0];
	user.password = splitWords[1];
	user.permissions = stoi(splitWords[2]);
	return user;
}

vector<stUserData> loadUsersDataFromFile(string fileName)
{
	vector<stUserData> users;
	fstream myFile;
	myFile.open(fileName, ios::in);
	if (myFile.is_open())
	{
		string user = "";
		while (getline(myFile, user))
		{
			if (user != "")
				users.push_back(saveUserVectorToStructure(split(user)));
		}
		myFile.close();
	}
	return users;
}

bool findUserByUserNameAndPassword(string userName, string password, vector<stUserData> users, stUserData& loginUser)
{
	for (stUserData& u : users)
	{
		if (userName == u.userName)
		{
			if (password == u.password)
			{
				loginUser = u;
				return true;
			}
		}
	}
	return false;
}

stUserData validateUserLogin()
{
	system("cls");
	printGeneralHeader("Login Screen");
	vector<stUserData> users = loadUsersDataFromFile(usersFileName);
	stUserData loginUser;

	string userName = readString("Enter Your User Name ?   ");
	string password = readString("Enter Your Password ?   ");
	while (!findUserByUserNameAndPassword(userName, password, users, loginUser))
	{
		cout << "\nUser [" << userName << "] is invalid, Please Enter Another One!" << endl;
		userName = readString("Enter A Valid User Name ?   ");
		password = readString("Enter A Valid Password ?   ");
	}
	system("cls");
	return loginUser;
}

void showAccessDeniedScreen()
{
	system("cls");
	cout << "\n--------------------------------------------" << endl;
	cout << "Access Denied," << endl;
	cout << "You Don't Have Permission To Do This Action," << endl;
	cout << "Please Contact Your Admin." << endl;
	cout << "--------------------------------------------" << endl;
	goBackToMainMenu();
}

enMainMenuOptions validateUserPermission(stUserData loginUser)
{
	short userOption = readNumberInRange("\nChoose What Do You Want To Do ? [1 to 8] ?  ", 1, 8);
	if (userOption == 8) // No Check Permission For Logout Option
		return (enMainMenuOptions)userOption;
	/*
	  permissions
		showClientsList = 1 << 0;	       1
		AddNewClient    = 1 << 1;          2
		DeleteClient    = 1 << 2;          4
		UpdateClient	= 1 << 3;          8
		FindClient		= 1 << 4;         16
		Transactions	= 1 << 5;         32
		ManageUsers		= 1 << 6;         64
		FullAccess		= (1 << 7) - 1;  127
	*/
	short checkUserOptionPermission = 1 << (userOption - 1);
	while (!(loginUser.permissions & checkUserOptionPermission))
		showAccessDeniedScreen();
	return (enMainMenuOptions)userOption;
}

void goBackToManageUsersMenuScreen()
{
	cout << "\nPress Any Key to go back to The Previous Menu...  ";
	system("pause >nul");
	system("cls");
	showManageUsersMenuScreen();
}

// 1 - list users screen

void printUsersListScreenHeader(vector<stUserData> users)
{
	cout << "\t\t\t\t\tUsers List (" << users.size() << ") Users(s)" << endl;
	cout << "-------------------------------------------------------------------------------------------------------" << endl;
	cout << "| " << left << setw(15) << "User Name";
	cout << "| " << left << setw(12) << "Password";
	cout << "| " << left << setw(12) << "Permissions" << endl;
	cout << "-------------------------------------------------------------------------------------------------------" << endl;
}

void printUsersListScreenBodyUser(stUserData user)
{
	cout << "| " << left << setw(15) << user.userName;
	cout << "| " << left << setw(12) << user.password;
	cout << "| " << left << setw(12) << user.permissions << endl;
}

void showUsersListScreen()
{
	vector<stUserData> users = loadUsersDataFromFile(usersFileName);

	printUsersListScreenHeader(users);
	for (stUserData& u : users)
		printUsersListScreenBodyUser(u);
}

// 2 - add new user

short setPermissionsForNewUser()
{
	short permissions = 0;
	if (toupper(readCharacter("\nDo You Want To Give Full Access ?  [Y/N] ?   ") == 'Y'))
	{
		return 127;
	}
	cout << "\n===========================================================" << endl;
	string permissionQuestion[7] = { "[Show Client List]", "[Add New Client]", "[Delete Client]", "[Update Client]", "[Find Client]", "[TransActions]", "[Manage Users]" };
	char answer;
	for (short i = 0; i <= 6; i++)
	{
		answer = toupper(readCharacter("\nDo You Want To Give Access To  ?  " + permissionQuestion[i] + "  [Y / N] ? "));
		if (answer == 'Y')
			permissions += (1 << i);
	}
	return permissions;
}

stUserData readNewUser(vector<stUserData> users)
{
	stUserData newUser;
	newUser.userName = readString("\nPlease Enter Your User Name ?  ");
	for (stUserData& u : users)
	{
		if (u.userName == newUser.userName)
		{
			do
			{
				cout << "\nClient With [" << newUser.userName << "] Already Exists, ";
				newUser.userName = readString("Please Enter Another User Name ?  ");
			} while (u.userName == newUser.userName);
		}
	}

	newUser.password = readString("\nPlease Enter Your Password ?  ");
	newUser.permissions = setPermissionsForNewUser();
	return newUser;
}

string convertUserStructureToRecord(stUserData user, string delimiter = "#//#")
{
	string record = "";
	record += user.userName + delimiter;
	record += user.password + delimiter;
	record += to_string(user.permissions);
	return record;
}

void addNewUser()
{
	vector<stUserData> users = loadUsersDataFromFile(usersFileName);
	stUserData user = readNewUser(users);
	saveRecordToFile(usersFileName, convertUserStructureToRecord(user));
}

void showAddNewUserScreen()
{
	char addAgain = 'Y';
	do
	{
		system("cls");
		printGeneralHeader("Adding New User Screen");
		cout << "\nAdding New User :" << endl;
		addNewUser();
		addAgain = readCharacter("\nUser Added Successfully, Do You Want To Add More Users ? [Y/N] ?  ");
	} while (toupper(addAgain) == 'Y');
}

// 3 - delete user

bool findUserByUserName(string userName, vector<stUserData> users, stUserData& loginUser)
{
	for (stUserData& u : users)
	{
		if (userName == u.userName)
		{
			loginUser = u;
			return true;
		}
	}
	return false;
}

void markUserForDeletionByUserName(string userName, vector<stUserData>& users)
{
	for (stUserData& u : users)
	{
		if (u.userName == userName)
		{
			u.markForDeletion = true;
			break;
		}
	}
}

void printUserData(stUserData user)
{
	cout << "\nThe Following Are The User Details :" << endl;
	cout << "\nUserName         | " << user.userName;
	cout << "\nPassword         | " << user.password;
	cout << "\nPermissions      | " << user.permissions << endl;
}

void saveUsersToFile(vector<stUserData> users)
{
	fstream myFile;
	myFile.open(usersFileName, ios::out);
	if (myFile.is_open())
	{
		string user = "";
		for (stUserData& u : users)
		{
			if (u.markForDeletion == false)
			{
				user = convertUserStructureToRecord(u);
				myFile << user << endl;
			}
		}
		myFile.close();
	}
}

void deleteUserByUserName(string userName, vector<stUserData>& users)
{
	stUserData user;
	char deleteAgain = 'N';
	bool findedUser = findUserByUserName(userName, users, user);
	if (findedUser == true && user.userName == "Admin")
	{
		cout << "\nYou Cannot Delete This User." << endl;
		goBackToManageUsersMenuScreen();
	}
	if (findedUser)
	{
		printUserData(user);

		deleteAgain = readCharacter("\nAre You Sure You Want To Delete User/ " + user.userName + " ? [Y / N] ? ");
		if (toupper(deleteAgain) == 'Y')
		{
			markUserForDeletionByUserName(userName, users);
			saveUsersToFile(users);
			cout << "\nClient Deleted Successfully!" << endl;
		}
	}
	else
	{
		cout << "\nUser With UserName (" << userName << ") Not Found!" << endl;
	}
}

void showDeleteUserScreen()
{
	printGeneralHeader("Delete User Screen");

	vector<stUserData> users = loadUsersDataFromFile(usersFileName);
	string userName = readString("\nPlease Enter Your UserName ?  ");
	deleteUserByUserName(userName, users);
}

// 4 - update user

void markUserForUpdateByUserName(string userName, vector<stUserData>& users)
{
	for (stUserData& u : users)
	{
		if (u.userName == userName)
		{
			u.markForUpdate = true;
			break;
		}
	}
}

stUserData updateUserDataExceptuserName(stUserData user)
{
	cout << "Please Update User Data:" << endl;
	user.userName = user.userName;
	user.password = readString("\nEnter New Password ? ");
	user.permissions = setPermissionsForNewUser();
	return user;
}

void saveUsersToFileAfterUpdate(vector<stUserData>& users)
{
	fstream myFile;
	myFile.open(usersFileName, ios::out);
	if (myFile.is_open())
	{
		string user = "";
		for (stUserData& u : users)
		{
			if (u.markForUpdate == true)
			{
				u = updateUserDataExceptuserName(u);
				break;
			}
		}
		saveUsersToFile(users);
		myFile.close();
	}
}

void updateUserByUserName(string userName, vector<stUserData>& users)
{
	stUserData user;
	char updateAgain = 'N';

	if (findUserByUserName(userName, users, user))
	{
		printUserData(user);

		updateAgain = readCharacter("\nAre You Sure You Want To Update User/ " + user.userName + " ? [Y / N] ? ");
		if (toupper(updateAgain) == 'Y')
		{
			markUserForUpdateByUserName(userName, users);
			saveUsersToFileAfterUpdate(users);
			cout << "\nUser Updated Successfully!" << endl;
		}
	}
	else
		cout << "\nUser With User Name (" << userName << ") Not Found!" << endl;
}

void showUpdateUserInfoScreen()
{
	printGeneralHeader("Update User Info Screen");

	vector<stUserData> users = loadUsersDataFromFile(usersFileName);
	string userName = readString("\nPlease Enter Your UserName?  ");
	updateUserByUserName(userName, users);
}

// 5 - find user

void showFindUserScreen()
{
	printGeneralHeader("Find User Screen");

	vector<stUserData> users = loadUsersDataFromFile(usersFileName);
	stUserData user;
	string userName = readString("\nPlease Enter Your UserName ?  ");

	if (findUserByUserName(userName, users, user))
	{
		printUserData(user);
	}
	else
		cout << "\nUser With UserName (" << userName << ") Not Found!" << endl;
}

// Manage Users Homepage

void printManageUsersMenuScreenBody()
{
	cout << "\t\t[1] List Users." << endl;
	cout << "\t\t[2] Add New User." << endl;
	cout << "\t\t[3] Delete User." << endl;
	cout << "\t\t[4] Update User." << endl;
	cout << "\t\t[5] Find User." << endl;
	cout << "\t\t[6] Main Menu." << endl;
	cout << "=======================================================================================================" << endl;
}

void performManageUsersMenuScreen()
{
	enManageUsersMenuOptions manageUsersOption = (enManageUsersMenuOptions)readNumberInRange("\nChoose What Do You Want To Do ? [1 to 6] ? ", 1, 6);
	switch (manageUsersOption)
	{
	case enManageUsersMenuOptions::listUsers:
		system("cls");
		showUsersListScreen();
		goBackToManageUsersMenuScreen();
		break;
	case enManageUsersMenuOptions::addNewUserManage:
		system("cls");
		showAddNewUserScreen();
		goBackToManageUsersMenuScreen();
		break;
	case enManageUsersMenuOptions::deleteUser:
		system("cls");
		showDeleteUserScreen();
		goBackToManageUsersMenuScreen();
		break;
	case enManageUsersMenuOptions::updateUser:
		system("cls");
		showUpdateUserInfoScreen();
		goBackToManageUsersMenuScreen();
		break;
	case enManageUsersMenuOptions::findUser:
		system("cls");
		showFindUserScreen();
		goBackToManageUsersMenuScreen();
		break;
	case enManageUsersMenuOptions::mainMenuManage:
		system("cls");
		goBackToMainMenu();
		break;
	}
}

void showManageUsersMenuScreen()
{
	printGeneralHeader("Manage Users Menu Screen");
	printManageUsersMenuScreenBody();
	performManageUsersMenuScreen();
}

// Main Menu Homepage

void printMainMenuScreenBody()
{
	cout << "\t\t[1] Show Client List." << endl;
	cout << "\t\t[2] Add New Client." << endl;
	cout << "\t\t[3] Delete Client." << endl;
	cout << "\t\t[4] Update Client Info." << endl;
	cout << "\t\t[5] Find Client." << endl;
	cout << "\t\t[6] Transactions." << endl;
	cout << "\t\t[7] Manage Users." << endl;
	cout << "\t\t[8] Logout." << endl;
	cout << "=======================================================================================================" << endl;
}

void performMainMenuOptions(enMainMenuOptions mainMenuOptions)
{
	switch (mainMenuOptions)
	{
	case enMainMenuOptions::showClientList:
		system("cls");
		showClientListScreen();
		goBackToMainMenu();
		break;
	case enMainMenuOptions::newClient:
		system("cls");
		showAddNewClientScreen();
		goBackToMainMenu();
		break;
	case enMainMenuOptions::deleteClient:
		system("cls");
		showDeleteClientScreen();
		goBackToMainMenu();
		break;
	case enMainMenuOptions::updateClientInfo:
		system("cls");
		showUpdateClientInfoScreen();
		goBackToMainMenu();
		break;
	case enMainMenuOptions::findClient:
		system("cls");
		showFindClientScreen();
		goBackToMainMenu();
		break;
	case enMainMenuOptions::transaction:
		system("cls");
		showTransactionsMenuScreen();
		goBackToMainMenu();
		break;
	case enMainMenuOptions::manageUsers:
		system("cls");
		showManageUsersMenuScreen();
		goBackToMainMenu();
		break;
	case enMainMenuOptions::logout:
		system("cls");
		showLoginScreen();
		break;
	default:
		break;
	}
}

void showMainMenuScreen()
{
	printGeneralHeader("Main Menu Screen");
	printMainMenuScreenBody();
	performMainMenuOptions(validateUserPermission(loginUser));
}

// Login Screen Homepage

void showLoginScreen()
{
	loginUser = validateUserLogin();
	showMainMenuScreen();
}

int main()
{
	showLoginScreen();
	system("pause>nul");
	return 0;
}
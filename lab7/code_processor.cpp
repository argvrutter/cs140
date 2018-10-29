#include "code_processor.h"
/**
 * Author: Aiden Rutter
 * CS140 Lab 7: Code processing
 * Description: Implement code processor.h
 * Notes: 2 week lab, partial submission date:
 * Partial cases: 1-3, 6, 10-13, 15, 18, 20, 21
 * 23, 26, 29-31
 */
/**
 * @brief This creates a new prize and puts it into Prizes. Due for 
 * partial submission 
 * @param  id          string, prize id.
 * @param  description string, description of prize.
 * @param  points      int, >= 0, representing points cost of prize.
 * @param  quantity    number of prizes available
 * @return             0 if OK, or -1 if: Already a prize with given id, points <= 0
 * or quantity <= 0
 */
int Code_Processor::New_Prize(string id, string description, int points, int quantity)
{
	// error checking
	if(points <= 0 || quantity <= 0) return -1;
	if(Prizes.find(id) != Prizes.end()) return -1;
	Prize* p = new Prize;
	p->id = id;
	p->description = description;
	p->points = points;
	p->quantity = quantity;
	Prizes[id] = p;
	return 0;
}
/**
 * This creates a new user with the given information, and puts it into Names. 
 * The user will start with no registered phone numbers. Due for partial
 * @param  username        string, username
 * @param  realname        string, full name
 * @param  starting_points int > 0 
 * @return                 0 if all is OK, -1 if there is already user w/ that 
 * username or starting_points < 0
 */
int Code_Processor::New_User(string username, string realname, int starting_points)
{
	if(starting_points < 0) return -1;
	if(Names.find(username) != Names.end()) return -1;
	User* usr = new User;
	usr->username = username; 
	usr->realname = realname;
	usr->points = starting_points;
	Names[username] = usr;
	return 0;
}
/**
 * This should erase the user from Names, and it should erase all of the user's 
 * phone numbers from Phones. After that, it should call delete on the user's 
 * pointer. 
 * @param  username string, username.
 * @return          0 if OK, -1 if username not in names.
 */
int Code_Processor::Delete_User(string username)
{
	// erase from name
	auto it = Names.find(username);
	if(it == Names.end()) return -1;
	// deletes for both phones & names;
	for(const string& pnum : it->second->phone_numbers) Phones.erase(Phones.find(pnum));
	delete it->second;
	Names.erase(it);
	return 0;
}
/**
 * This should register the given phone string with the user. That means putting 
 * the phone on both the Phones map, and on the user's phone_numbers set.
 * Due for partial
 * @param  username string, username
 * @param  phone    string, phone number.
 * @return          0 if OK, -1 if no user with that username, or phone #
 * is already registered.
 */
int Code_Processor::Add_Phone(string username, string phone)
{
	if(Phones.find(phone) != Phones.end()) return -1;
	if(Names.find(username) == Names.end()) return -1;
	Names[username]->phone_numbers.emplace(phone);
	Phones[phone] = Names[username];
	return 0;
}
/**
 * This should remove the phone from the system -- both from Phones and from 
 * the user's phone_numbers set. Due for partial
 * @param  username string, username
 * @param  phone    string, phone
 * @return          0 if OK, -1 if there is no user with that username or no matching
 * phone number, or if the phone number is registered to a different user.
 */
int Code_Processor::Remove_Phone(string username, string phone)
{
	auto nait = Names.find(username);
	auto phit = Phones.find(phone);
	if(nait == Names.end()) return -1;
	if(phit == Phones.end()) return -1;
	// pointer comparison; should work b/c Phones & Names share <3
	if(Phones[phone] != Names[username]) return -1;
	// deyeet from Names
	auto it = Names[username]->phone_numbers.find(phone);
	Names[username]->phone_numbers.erase(it);
	// delete from Phones
	Phones.erase(phit);
	return 0;
}
/**
 * This should return a string containing all of that user's phone numbers, 
 * in lexicographic order, each separated by a newline. There should be a newline 
 * at the end of the string too. Due for partial
 * @param  username string, username
 * @return          the string, or if non-existant user, "BAD USER". if no phones, 
 * return an empty string.
 */
string Code_Processor::Show_Phones(string username)
{
	string ret;
	if(Names.find(username) == Names.end()) return "BAD USER";
	// phone numbers should already be sorted
	for(const string& pnum : Names[username]->phone_numbers) {
		ret += pnum;
		ret += "\n";
	}
	return ret;
}
/**
 * This is called when a user enters a code. You need to first check the Codes 
 * set to see if the code has been entered before. If it has, or if the user 
 * doesn't exist, return -1. Otherwise, you need to check to see if the code is 
 * valid: A valid code's djbhash() must either be divisible by 17 or 13. If 
 * divisible by 17, then it is worth ten points. Otherwise, if it is divisible by
 * 13, then it is worth three points. If the code is valid, then add it to Codes, 
 * increment the user's account 
 * @param  username [description]
 * @param  code     [description]
 * @return          number of points added, or 0 if invalid code. -1 if code
 * has been entered before or if user doesn't exist.
 */
int Code_Processor::Enter_Code(string username, string code)
{
	return -1;

}
/**
 * This should work just like Enter_Code(), except the user's account is 
 * identified by the phone number. If the phone number doesn't exist, return -1. 
 * Otherwise, this should work just like Enter_Code().
 * @param  phone [description]
 * @param  code  [description]
 * @return       -1 if phone # doesn't exist
 */
int Code_Processor::Text_Code(string phone, string code)
{
	return -1;

}
/**
 * This is called to mark a code as used, even though no user is entering it. 
 * This is used to help rebuild the server from a saved state (see Write() below).
 * If the code is not valid or it is already in Codes, return -1. Otherwise, add 
 * it to Codes and return 0.
 * @param  code [description]
 * @return      -1 for invalid code or already in codes, or 0 if OK
 */
int Code_Processor::Mark_Code_Used(string code)
{
	return -1;

}
/**
 * This should return the user's points. If the user doesn't exist, return -1.
 * Due for partial deadline
 * @param  username string, username
 * @return          -1 if user doesn't exist, 0 if OK
 */
int Code_Processor::Balance(string username)
{
	if(Names.find(username) == Names.end()) return -1;
	return Names[username]->points;
}
/**
 * This is called when a user wants to redeem a prize. The prize is identified by 
 * its id. If the user or prize don't exist, or if the user doesn't have enough 
 * points, return -1. Otherwise, decrement the points from the user's account, 
 * and decrement the prize's quantity by one. If the prize's quantity is zero, 
 * remove the prize from the system (which should involve a delete call).
 * @param  username [description]
 * @param  prize    [description]
 * @return          -1 if user doesn't have enough points or prize doesn't 
 * exist, or user doesn't exist, 0 otherwise
 */
int Code_Processor::Redeem_Prize(string username, string prize)
{
	return -1;

}
/**
 * calls delete on all the users and prizes.
 */
Code_Processor::~Code_Processor()
{
	for(auto& user : Names) delete user.second;
	for(auto& prize : Prizes) delete prize.second;
}
/**
 * Partially due for partial. Writes prizes, users, phone numbers to file. 
 * ADD_USER, PRIZE, ADD_PHONE and MARK_USED
 * @param  file c_string, file descriptor.
 * @return      0 if success, -1 if error
 */
int Code_Processor::Write(const char *file)
{
	ofstream fout;
	fout.open(file);
	if(!fout.is_open()) return -1;
	// PRIZE id points quantity description
	for(auto& prize : Prizes) {
		fout << "PRIZE " << prize.first << " " << prize.second->points << " ";
		fout << prize.second->quantity << " " << prize.second->description << endl;
	}
	// "ADD_USER username starting_points realname"
	for(auto& user : Names) {
		fout << "ADD_USER " << user.second->username << " " << user.second->points;
		fout << " " << user.second->realname << endl;
	}
	// ADD_PHONE username phone-number
	for(auto& pnum : Phones) {
		fout << "ADD_PHONE " << pnum.second->username << " " << pnum.first << endl;
	} 
	// MARK_USED
	fout.close();
	return 0;
}

#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool isNumeric(const string &str)
{
  for (char c : str)
  {
    if (!isdigit(c))
    {
      return false;
    }
  }
  return true;
}

void getContactInfo(vector<string> &contactInfo)
{
  cout << "Please provide your contact information so we can assist you further." << endl;
  cout << "Phone number: ";
  string phoneNumber;
  cin >> phoneNumber;
  while (!isNumeric(phoneNumber))
  {
    cout << "Invalid phone number. Please enter again: ";
    cin >> phoneNumber;
  }
  contactInfo.push_back(phoneNumber);
}

void provideHelp(const string &helpOption)
{
  if (helpOption == "product")
  {
    cout << "Here is some information about our products:\n";
    cout << "- Product A: Description of product A.\n";
    cout << "- Product B: Description of product B.\n";
  }
  else if (helpOption == "billing")
  {
    cout << "Here is some information about billing:\n";
    cout << "- Payment methods: Description of available payment methods.\n";
    cout << "- Invoices: Explanation of how to access and understand invoices.\n";
  }
  else if (helpOption == "technical")
  {
    cout << "Here is some technical support:\n";
    cout << "- Troubleshooting: Steps to troubleshoot common technical issues.\n";
    cout << "- Software updates: Information about latest software updates.\n";
  }
  else
  {
    cout << "Sorry, I couldn't understand that option.\n";
  }
}

// Main function to handle user queries
void handleQuery(const string &query)
{
  if (query == "menu")
  {
    cout << "Here are some commands you can try:\n";
    cout << "- 'help': Display this help message.\n";
    cout << "- 'contact': Provide your contact information to talk to a customer service representative.\n";
    cout << "- 'exit': Quit the program.\n";
  }
  else if (query == "help")
  {
    cout << "What type of help do you need?\n";
    cout << "1. Product information\n";
    cout << "2. Billing assistance\n";
    cout << "3. Technical support\n";
    string helpOption;
    cin >> helpOption;
    provideHelp(helpOption);
  }
  else if (query == "contact")
  {
    vector<string> contactInfo;
    getContactInfo(contactInfo);
    cout << "Thank you! A customer service representative will contact you shortly.\n";
  }
  else if (query == "exit")
  {
    cout << "Goodbye! Have a great day.\n";
    exit(0);
  }
  else
  {
    cout << "Sorry, I didn't understand that. Type 'help' for available commands.\n";
  }
}

int main()
{
  cout << "Welcome! How can I assist you today?" << endl;
  cout << "Type 'menu' for available commands." << endl;

  string userInput;
  while (true)
  {
    cout << "> ";
    cin >> userInput;
    handleQuery(userInput);
  }

  return 0;
}

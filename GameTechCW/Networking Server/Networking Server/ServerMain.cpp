#include "Server.h"
using namespace std;

//template <typename T> char * convertToCharStar(T& a) {
//	string temp = std::to_string(a);
//	char *result = new char[a.length() + 1];
//	//memset(result, a, sizeof(a));
//	strcpy_s(result, sizeof(temp), temp.c_str());
//	return result;
//}

int main(void) {

Server *server = new Server();
server->run();

//std::queue<std::string>* messages = server->getMessageQueue();

delete server;
}
#include "Network.h"
#include <sstream>
#include <vector>
#include "mainwindow.h"
#include <ncltech\Player.h>
#include <time.h>


class Client : public Network {
	friend class MainWindow;
public:
	Client(Scene* newscene);
	~Client();
	void run();
	void initial_run();
	std::string getIP();
	bool _stdcall connection();
	void _stdcall receiveMessage(SOCKET sock);
	int get_Min();
	SOCKET getListeningSocket();
	SOCKET getIncSocket();
private:
	Scene *scene;
	static vector<Player*> IncomingPlayers;
	bool start = false;
	SOCKET inc = NULL;
	sockaddr_storage inc_addr;
	socklen_t inc_size = sizeof(inc_addr);
	int min;
	std::string ip;
};
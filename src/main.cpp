#include "TcpServer.h"
#include<locale.h>  
#include <iostream>

int main() {
	setlocale(LC_ALL, "RUS");

	TcpServer Serv1(12345);
	Serv1.start();
	
	std::cout<<Serv1.receiveData()<<std::endl;

	Serv1.stop();
}
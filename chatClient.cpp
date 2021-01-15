#include <thread>// std::this_thread::sleep_for
#include <memory>//lidar com threads
#include <iostream>
#include <vector>
#include <string>
#include <boost/asio.hpp> //MULTIPLAYER
using boost::asio::ip::udp;

class UDPSystemClient{
public:
std::vector<std::string> HostDados;

boost::asio::io_service io_service;
udp::endpoint local_endpoint;
udp::endpoint remote_endpoint;
udp::socket my_socket;


UDPSystemClient();

void receiveAndStoreData();

void sendOneDataToHost(std::string dadoEnviar);


};

UDPSystemClient::UDPSystemClient():local_endpoint(udp::v4(), 0), remote_endpoint(udp::v4(), 9001), my_socket(io_service){

my_socket = udp::socket (io_service, // io service
  local_endpoint); // endpoint
	boost::asio::ip::address ip_remoto;
  std::string IPHOST;
  std::cout << "¸¸♬·¯·♪·¯·♫¸¸ Check In¸¸♫·¯·♪¸♩·¯·♬¸¸" << std::endl;
	std::cout << "Digite o IP do host do hotel:";
	std::cin >> IPHOST;


	// Encontrando IP remoto
	ip_remoto = boost::asio::ip::address::from_string(IPHOST);
	this->remote_endpoint = udp::endpoint (ip_remoto, 9001);

  std::cout << "IP aceito." << std::endl;

	std::cout << "Iniciando hotel..." << std:: endl;
}

void UDPSystemClient::receiveAndStoreData(){

  char v[6000];
  std::string dado;
  bool repetido = 0;


my_socket.receive_from(boost::asio::buffer(v,6000), // Local do buffer
                        remote_endpoint); // Confs. do Cliente


dado.assign(v, std::strlen(v) + 1);



this->HostDados.push_back(dado);





}



void UDPSystemClient::sendOneDataToHost(std::string dadoEnviar){




      my_socket.send_to(boost::asio::buffer(dadoEnviar), remote_endpoint);





}


int main(int argc, char* args[]){
UDPSystemClient chat;

for(int n = 0; n < 4; n++){

  std::thread send(&UDPSystemClient::sendOneDataToHost, &chat, "Estouaquibemaqui junto.");




send.join();


  std::thread receive(&UDPSystemClient::receiveAndStoreData, &chat);
    receive.join();


}

std::cout << "n:" << chat.HostDados.size() << "DADOS:" << chat.HostDados[0] << std::endl;

return 0;


}

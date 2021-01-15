////g++ -ochatHost chatHost.cpp -lpthread



#include <thread>// std::this_thread::sleep_for
#include <memory>//lidar com threads
#include <iostream>
#include <vector>
#include <string>
#include <boost/asio.hpp> //MULTIPLAYER
using boost::asio::ip::udp;

class UDPSystem{
private:
std::vector<boost::asio::ip::udp::endpoint> clientes;
std::vector<std::string> clienteDados;
public:
boost::asio::io_service io_service;
udp::endpoint local_endpoint;
udp::endpoint remote_endpoint;
udp::socket my_socket;
int clientesConectados;

UDPSystem();
void sendAllDataToAllClients();
void receiveAndStoreDataAndClients();



};

UDPSystem::UDPSystem():local_endpoint(udp::v4(), 9001), remote_endpoint(udp::v4(), 0), my_socket(io_service){

my_socket = udp::socket (io_service, // io service
  local_endpoint); // endpoint

clientesConectados = 0;

}

void UDPSystem::receiveAndStoreDataAndClients(){
char v[120];
bool repetido = 0;
std::cout << "A";
my_socket.receive_from(boost::asio::buffer(v,120), // Local do buffer
                      remote_endpoint); // Confs. do Cliente
std::cout << "B";
for(int n; n < clientes.size(); n++){
  if(remote_endpoint == clientes[n]){
    repetido = 1;
  }
}

if(!repetido){
  clientes.push_back(remote_endpoint);
  clientesConectados++;
}

}

void UDPSystem::sendAllDataToAllClients(){

}



int main(int argc, char* args[]){
UDPSystem chat;

std::cout << "Clientes:" << chat.clientesConectados << std::endl;

chat.receiveAndStoreDataAndClients();


std::cout << "Clientes:" << chat.clientesConectados << std::endl;

return 0;


}

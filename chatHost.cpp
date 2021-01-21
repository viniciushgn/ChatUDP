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
std::vector<udp::endpoint> clientes;
std::vector<std::string> clientesDados;
public:
boost::asio::io_service io_service;
udp::endpoint local_endpoint;
udp::endpoint remote_endpoint;
udp::socket my_socket;
int clientesConectados;
std::string dadosAtualizados;
std::string meuDado;

UDPSystem();
void sendAllDataToAllClients();
void receiveAndStoreDataAndClients();
void sendOneDataToAllClients(std::string dadoEnviar);
void atualizarMeuDado(std::string myData);

};

void UDPSystem::atualizarMeuDado(std::string myData){
this->meuDado = myData;

}

UDPSystem::UDPSystem():local_endpoint(udp::v4(), 9001), remote_endpoint(udp::v4(), 0), my_socket(io_service){

my_socket = udp::socket (io_service, // io service
  local_endpoint); // endpoint

clientesConectados = 0;

}

void UDPSystem::receiveAndStoreDataAndClients(){

  char v[6000];
  std::string dado;
  bool repetido = 0;


    my_socket.receive_from(boost::asio::buffer(v,6000), // Local do buffer
                        remote_endpoint); // Confs. do Cliente


dado.assign(v, std::strlen(v) + 1);


for(int n = 0; n < clientes.size(); n++){
  if(remote_endpoint.address() == clientes[n].address() || dado == clientesDados[n]){
    repetido = 1;
    clientesDados[n] = dado;
    clientes[n] = remote_endpoint;
  }
}


if(!repetido){

  clientes.push_back(remote_endpoint);
  std::cout << clientes[0] << "<y" << std::endl;
  clientesConectados++;
  this->clientesDados.push_back(dado);
  repetido = 0;
}

this->dadosAtualizados.clear();
this->dadosAtualizados += this->meuDado;

for (const auto &piece : this->clientesDados) this->dadosAtualizados += piece;



}

void UDPSystem::sendAllDataToAllClients(){


for(int n = 0; n < clientesDados.size(); n++){

  for(int m = 0; m < clientes.size(); m++){
    my_socket.send_to(boost::asio::buffer(clientesDados[n]), clientes[m]);
  }

}


}

void UDPSystem::sendOneDataToAllClients(std::string dadoEnviar){




    for(int m = 0; m < clientes.size(); m++){
      my_socket.send_to(boost::asio::buffer(dadoEnviar), clientes[m]);
    }




}


int main(int argc, char* args[]){
UDPSystem chat;

chat.atualizarMeuDado("KestoguP");

for(int n = 0; n < 4; n++){
  std::thread receive(&UDPSystem::receiveAndStoreDataAndClients, &chat);
    receive.join();
  std::thread send(&UDPSystem::sendOneDataToAllClients, &chat, chat.dadosAtualizados );




send.join();


}



return 0;


}

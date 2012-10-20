/* 
 Uses the SimGear SGSocket class: http://simgear.sourceforge.net/doxygen/classSGSocket.html
 TODO:
 - make mpserver address and port configurable
 - make update rate configurable
 - write a little parser for the response (see fgms)
 - use code from fgms to put everything into data structures
 - provide a means to filter the reponse by range
 - copy response to property tree
 
 */

#include <string>
#include <iostream>

#include "traffic.hxx"

struct PlayerInfo {
  
};

FGMultiplayerTraffic::FGMultiplayerTraffic() {
/*
 SGPropertyNode* p = ApplicationProperties::Properties;
 std::string mpserver = p->getNode( "/startup/mpserver-address", true )->getStringValue("mpserver01.flightgear.org");
 std::string port = p->getNode( "/startup/mpserver-port", true )->getStringValue("5001");
*/
 _client=new SGSocket("mpserver01.flightgear.org", "5001", "tcp"); 
 _client->set_timeout(1);
}

FGMultiplayerTraffic::~FGMultiplayerTraffic() {
  delete _client; //FIXME: use smart pointer here!
}

void
FGMultiplayerTraffic::update(double dt) {
  const int MAX_LINE_LENGTH=512;
  char response[MAX_LINE_LENGTH];
  std::string data;
  std::cout << "Updating FGMultiplayerTraffic subsystem... (stub)" << std::endl;
  if (!_client->open( SG_IO_OUT )) throw("Could not open socket!");
  while( _client->read(response, MAX_LINE_LENGTH))
  	data += response;
  //TODO: parse response - see: https://gitorious.org/fgms/fgms-0-x/blobs/master/src/server/fg_server.cxx#line543
  std::cout << data << std::endl;
  _client->close();
}


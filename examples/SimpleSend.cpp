/* 
    Simple example of sending an OSC message using oscpack.
*/

#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"
#include "json.hpp"
#include <iostream>

using json = nlohmann::json;

#define ADDRESS "127.0.0.1"
#define PORT 5555

#define OUTPUT_BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
  (void)argc; // suppress unused parameter warnings
  (void)argv; // suppress unused parameter warnings

  UdpTransmitSocket transmitSocket(IpEndpointName(ADDRESS, PORT));

  char buffer[OUTPUT_BUFFER_SIZE];
  osc::OutboundPacketStream p(buffer, OUTPUT_BUFFER_SIZE);

  // json config = {
  //     {"id", 0},
  //     {"port", 8000},
  //     {"location", {
  //             {"x", 0}, {"y", 0}, {"z", 0}
  //         }
  //     },
  //     {"rotation", {
  //             {"x", 0}, {"y", 0}, {"z", 0}
  //         }
  //     }
  // };

  //std::string configSerialized = config.dump();

  if (argc >= 3)
  {
    std::string spawningAddress = std::string("/spawn/") + argv[1];
    std::string configSerialized = argv[2];

    // Sending configuration for Spawning
    p << osc::BeginBundle();
    p << osc::BeginMessage(spawningAddress.c_str())
      << osc::Blob(configSerialized.c_str(), configSerialized.length()) << osc::EndMessage
      << osc::EndBundle;

    transmitSocket.Send(p.Data(), p.Size());
  } else
  {
    std::cout << "ERROR: Not enough arguments have been passed!" << "\n"
              << "USAGE: ./SimpleSend ADDRESS SPAWN_JSON" << std::endl;
  }
  
}

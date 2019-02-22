/* 
    Example of two different ways to process received OSC messages using oscpack.
    Receives the messages from the SimpleSend.cpp example.
*/

#include <iostream>
#include <cstring>

#if defined(__BORLANDC__) // workaround for BCB4 release build intrinsics bug
namespace std
{
using ::__strcmp__; // avoid error: E2316 '__strcmp__' is not a member of 'std'.
}
#endif

#include "osc/OscReceivedElements.h"
#include "osc/OscPacketListener.h"
#include "ip/UdpSocket.h"

#define PORT 8000

class ExamplePacketListener : public osc::OscPacketListener
{
  protected:
    virtual void ProcessMessage(const osc::ReceivedMessage &m,
                                const IpEndpointName &remoteEndpoint)
    {
        (void)remoteEndpoint; // suppress unused parameter warning

        try
        {
            if (std::strcmp(m.AddressPattern(), "/agent/0/pos") == 0)
            {
                osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
                float x, y, z;
                args >> x >> y >> z >> osc::EndMessage;

                std::cout << "pos from /agent/0: "
                             "x = " << x << " y = " << y << " z = " << z << "\n";
            }
            else if (std::strcmp(m.AddressPattern(), "/agent/0/rot") == 0)
            {
                osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
                float x, y, z;
                args >> x >> y >> z >> osc::EndMessage;

                std::cout << "rot from /agent/0: "
                             "x = " << x << " y = " << y << " z = " << z << "\n";
            }
        }
        catch (osc::Exception &e)
        {
            // any parsing errors such as unexpected argument types, or
            // missing arguments get thrown as exceptions.
            std::cout << "error while parsing message: "
                      << m.AddressPattern() << ": " << e.what() << "\n";
        }
    }
};

int main(int argc, char *argv[])
{
    (void)argc; // suppress unused parameter warnings
    (void)argv; // suppress unused parameter warnings

    ExamplePacketListener listener;
    UdpListeningReceiveSocket s(
        IpEndpointName(IpEndpointName::ANY_ADDRESS, PORT),
        &listener);

    std::cout << "press ctrl-c to end\n";

    s.RunUntilSigInt();

    return 0;
}

/*----------------------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved. https://github.com/piot/conclave-client-udp
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------------------*/
#include <conclave-client-udp/client.h>
#include <udp-client/udp_client.h>

static int udpClientSocketInfoSend(void* _self, const uint8_t* data, size_t size)
{
    UdpClientSocketInfo* self = (UdpClientSocketInfo*)_self;

    return udpClientSend(self->clientSocket, data, size);
}

static ssize_t udpClientSocketInfoReceive(void* _self, uint8_t* data, size_t size)
{
    UdpClientSocketInfo* self = (UdpClientSocketInfo*)_self;

    return udpClientReceive(self->clientSocket, data, size);
}

/// Initialize a conclave client with udp client transport
/// @param self client
/// @param memory memory to use for allocating guise client
/// @param name host name to connect to
/// @param port port number to connect to (usually 27004)
/// @param guiseUserSessionId guiseUserSessionId
/// @return negative on error,
int clvClientUdpInit(ClvClientUdp* self, struct ImprintAllocator* memory, const char* name,
    uint16_t port, GuiseSerializeUserSessionId guiseUserSessionId)
{
    self->transport.receive = udpClientSocketInfoReceive;
    self->transport.send = udpClientSocketInfoSend;
    self->transport.self = &self->socketInfo;

    udpClientInit(&self->socket, name, port);

    self->socketInfo.clientSocket = &self->socket;

    Clog conclaveClientLog;
    conclaveClientLog.config = &g_clog;
    conclaveClientLog.constantPrefix = "conclaveClient";

    clvClientInit(
        &self->conclaveClient, memory, &self->transport, guiseUserSessionId, conclaveClientLog);
    //conclaveClientReInit(&self->conclaveClient, &self->transport, secret->userId, secret->passwordHash);

    return 0;
}

/// Updates the client
/// @param self client
/// @param now the current monotonic time
/// @return negative on error
int clvClientUdpUpdate(ClvClientUdp* self, MonotonicTimeMs now)
{
    return clvClientUpdate(&self->conclaveClient, now);
}

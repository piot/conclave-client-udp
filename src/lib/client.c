/*----------------------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved. https://github.com/piot/conclave-client-udp
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------------------*/
#include <conclave-client-udp/client.h>
#include <udp-client/udp_client.h>

static int udpClientSocketInfoSend(void* _self, const uint8_t* data, size_t size)
{
    ClvUdpClientSocketInfo* self = (ClvUdpClientSocketInfo*)_self;

    return udpClientSend(self->clientSocket, data, size);
}

static ssize_t udpClientSocketInfoReceive(void* _self, uint8_t* data, size_t size)
{
    ClvUdpClientSocketInfo* self = (ClvUdpClientSocketInfo*)_self;

    return udpClientReceive(self->clientSocket, data, size);
}

/// Initialize a conclave client with udp client transport
/// @param self client
/// @param name host name to connect to
/// @param port port number to connect to (usually 27004)
/// @param guiseUserSessionId guiseUserSessionId
/// @return negative on error,
int clvClientUdpInit(ClvClientUdp* self, const char* name, uint16_t port,
    const GuiseSerializeUserSessionId guiseUserSessionId, Clog log)
{
    self->transport.receive = udpClientSocketInfoReceive;
    self->transport.send = udpClientSocketInfoSend;
    self->transport.self = &self->socketInfo;

    udpClientInit(&self->socket, name, port);

    self->socketInfo.clientSocket = &self->socket;

    tc_snprintf(self->subLog, 32, "%s/realize", log.constantPrefix);
    Clog conclaveClientLog;
    conclaveClientLog.config = log.config;
    conclaveClientLog.constantPrefix = self->subLog;

    ClvClientRealizeSettings settings;
    settings.transport = self->transport;
    settings.guiseUserSessionId = guiseUserSessionId;
    settings.log = conclaveClientLog;
    //conclaveClientReInit(&self->conclaveClient, &self->transport, secret->userId, secret->passwordHash);
    return clvClientRealizeInit(&self->conclaveClient, &settings);
}

/// Updates the client
/// @param self client
/// @param now the current monotonic time
/// @return negative on error
int clvClientUdpUpdate(ClvClientUdp* self, MonotonicTimeMs now)
{
    return clvClientRealizeUpdate(&self->conclaveClient, now);
}

int clvClientUdpCreateRoom(ClvClientUdp* self, const ClvSerializeRoomCreateOptions* roomOptions)
{
    clvClientRealizeCreateRoom(&self->conclaveClient, roomOptions);
    return 0;
}

/*----------------------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved. https://github.com/piot/conclave-client-udp
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------------------*/
#ifndef CONCLAVE_CLIENT_UDP_H
#define CONCLAVE_CLIENT_UDP_H

#include <clog/clog.h>
#include <conclave-client/client.h>
#include <datagram-transport/transport.h>
#include <udp-client/udp_client.h>

typedef struct UdpClientSocketInfo {
    struct UdpClientSocket* clientSocket;
} UdpClientSocketInfo;

typedef struct ClvClientUdp {
    ClvClient conclaveClient;
    DatagramTransport transport;
    UdpClientSocketInfo socketInfo;
    UdpClientSocket socket;
    Clog log;
} ClvClientUdp;

int clvClientUdpInit(ClvClientUdp* self, struct ImprintAllocator* memory, const char* name,
    uint16_t port, GuiseSerializeUserSessionId guiseUserSessionId);

int clvClientUdpUpdate(ClvClientUdp* self, MonotonicTimeMs now);

#endif

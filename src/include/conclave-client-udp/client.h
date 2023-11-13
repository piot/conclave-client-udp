/*----------------------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved. https://github.com/piot/conclave-client-udp
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------------------*/
#ifndef CONCLAVE_CLIENT_UDP_H
#define CONCLAVE_CLIENT_UDP_H

#include <clog/clog.h>
#include <conclave-client/network_realizer.h>
#include <datagram-transport/transport.h>
#include <udp-client/udp_client.h>

struct ClvSerializeRoomCreateOptions;

typedef struct ClvUdpClientSocketInfo {
    struct UdpClientSocket* clientSocket;
} ClvUdpClientSocketInfo;

typedef struct ClvClientUdp {
    ClvClientRealize conclaveClient;
    DatagramTransport transport;
    ClvUdpClientSocketInfo socketInfo;
    UdpClientSocket socket;
    Clog log;
} ClvClientUdp;

int clvClientUdpInit(ClvClientUdp* self, struct ImprintAllocator* memory, const char* name,
    uint16_t port, GuiseSerializeUserSessionId guiseUserSessionId);

int clvClientUdpUpdate(ClvClientUdp* self, MonotonicTimeMs now);
int clvClientUdpCreateRoom(ClvClientUdp* self, const struct ClvSerializeRoomCreateOptions* roomOptions);

#endif

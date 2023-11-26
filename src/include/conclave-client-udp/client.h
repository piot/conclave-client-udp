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

struct ClvSerializeRoomCreateOptions;
struct ImprintAllocatorWithFree;

typedef struct ClvUdpClientSocketInfo {
    struct UdpClientSocket* clientSocket;
} ClvUdpClientSocketInfo;

typedef struct ClvClientUdp {
    ClvClient conclaveClient;
    DatagramTransport transport;
    ClvUdpClientSocketInfo socketInfo;
    UdpClientSocket socket;
    char subLog[32];
    Clog log;
} ClvClientUdp;

int clvClientUdpInit(ClvClientUdp* self, const char* name, uint16_t port,
    GuiseSerializeUserSessionId guiseUserSessionId, MonotonicTimeMs now,
    struct ImprintAllocatorWithFree* allocator, Clog log);

int clvClientUdpUpdate(ClvClientUdp* self, MonotonicTimeMs now);
int clvClientUdpCreateRoom(
    ClvClientUdp* self, const struct ClvSerializeRoomCreateOptions* roomOptions);

#endif

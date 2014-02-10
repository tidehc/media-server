#ifndef _rtp_transport_h_
#define _rtp_transport_h_

#include "rtp.h"
#include "rtcp.h"
#include "sys/sock.h"
#include "aio-socket.h"

#define MAX_UDP_BYTES		8192
#define PERFECT_UDP_BYTES	512

typedef unsigned char byte_t;

struct rtp_transport
{
	aio_socket_t socket;
	void* data;

	time_t st; // last send timestamp
	time_t rt; // last receive timestamp
	size_t bytes; // receive bytes
};

struct rtcp_transport
{
	aio_socket_t socket;
	byte_t data[MAX_UDP_BYTES];
};

struct rtp_context
{
	void* queue;
	struct rtp_transport rtp;
	struct rtcp_transport rtcp;
};

void rtcp_input(struct rtp_context *ctx, const void* data, int bytes);

void rtcp_sender_report(struct rtp_context *ctx, void* data, int bytes);

void rtcp_receiver_report(struct rtp_context *ctx, void* data, int bytes);

#endif /* !_rtp_transport_h_ */
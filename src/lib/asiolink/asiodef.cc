// File created from asiodef.msg on Mon Feb 28 17:15:30 2011

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace asiolink {

extern const isc::log::MessageID ASIO_FETCHCOMP = "FETCHCOMP";
extern const isc::log::MessageID ASIO_FETCHSTOP = "FETCHSTOP";
extern const isc::log::MessageID ASIO_OPENSOCK = "OPENSOCK";
extern const isc::log::MessageID ASIO_RECVSOCK = "RECVSOCK";
extern const isc::log::MessageID ASIO_RECVTMO = "RECVTMO";
extern const isc::log::MessageID ASIO_SENDSOCK = "SENDSOCK";
extern const isc::log::MessageID ASIO_UNKORIGIN = "UNKORIGIN";
extern const isc::log::MessageID ASIO_UNKRESULT = "UNKRESULT";

} // namespace asiolink

namespace {

const char* values[] = {
    "FETCHCOMP", "upstream fetch to %s(%d) has now completed",
    "FETCHSTOP", "upstream fetch to %s(%d) has been stopped",
    "OPENSOCK", "error %d opening %s socket to %s(%d)",
    "RECVSOCK", "error %d reading %s data from %s(%d)",
    "RECVTMO", "receive timeout while waiting for data from %s(%d)",
    "SENDSOCK", "error %d sending data using %s to %s(%d)",
    "UNKORIGIN", "unknown origin for ASIO error code %d (protocol: %s, address %s)",
    "UNKRESULT", "unknown result (%d) when IOFetch::stop() was executed for I/O to %s(%d)",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

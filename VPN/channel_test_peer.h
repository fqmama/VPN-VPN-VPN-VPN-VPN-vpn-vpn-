

#ifndef GRPCPP_TEST_CHANNEL_TEST_PEER_H
#define GRPCPP_TEST_CHANNEL_TEST_PEER_H

#include <grpcpp/channel.h>

namespace grpc {
namespace testing {

/// A test-only class to access private members of Channel.
class ChannelTestPeer {
 public:
  explicit ChannelTestPeer(Channel* channel) : channel_(channel) {}

  /// Provide the gRPC Core channel
  grpc_channel* channel() const { return channel_->c_channel_; }
  int registered_calls() const;
  int registration_attempts() const;

 private:
  Channel* channel_;  // not owned
};

}  // namespace testing
}  // namespace grpc

#endif  // GRPCPP_TEST_CHANNEL_TEST_PEER_H

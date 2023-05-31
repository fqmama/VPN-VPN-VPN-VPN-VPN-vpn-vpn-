

#ifndef GRPCPP_TEST_CLIENT_CONTEXT_TEST_PEER_H
#define GRPCPP_TEST_CLIENT_CONTEXT_TEST_PEER_H

#include <map>

#include <grpcpp/client_context.h>

namespace grpc {
namespace testing {

/// A test-only class to access private members and methods of ClientContext.
class ClientContextTestPeer {
 public:
  explicit ClientContextTestPeer(ClientContext* const ctx) : ctx_(ctx) {}

  /// Inject metadata to the ClientContext for the test. The test peer
  /// must be alive when a ClientContext::GetServerInitialMetadata is called.
  void AddServerInitialMetadata(const std::string& key,
                                const std::string& value) {
    server_initial_metadata_storage_.insert(
        std::pair<std::string, std::string>(key, value));
    ctx_->initial_metadata_received_ = true;
    ctx_->recv_initial_metadata_.map()->clear();
    for (const auto& item : server_initial_metadata_storage_) {
      ctx_->recv_initial_metadata_.map()->insert(
          std::pair<grpc::string_ref, grpc::string_ref>(
              item.first.c_str(),
              grpc::string_ref(item.second.data(), item.second.size())));
    }
  }

  std::multimap<std::string, std::string> GetSendInitialMetadata() const {
    return ctx_->send_initial_metadata_;
  }

 private:
  ClientContext* const ctx_;  // not owned
  std::multimap<std::string, std::string> server_initial_metadata_storage_;
};

}  // namespace testing
}  // namespace grpc

#endif  // GRPCPP_TEST_CLIENT_CONTEXT_TEST_PEER_H

#include <gtest/gtest.h>
extern "C" {
    #include "client.h"
    #include "config.h"
}

// Mock config for testing
CLIENT_CONFIG mockConfig = {
    .ip = "127.0.0.1",
    .port = 9090
};

CLIENT_CONFIG* GetClientConfig() {
    return &mockConfig;  // override real function
}

TEST(ClientTest, InitializeClientValidConfig) {
    int sockfd;
    struct sockaddr_in* addr = InitializeClient(&sockfd);

    ASSERT_NE(addr, nullptr);                // should succeed
    EXPECT_EQ(addr->sin_family, AF_INET);    // family set
    EXPECT_EQ(ntohs(addr->sin_port), 9090);  // port set
    EXPECT_EQ(sockfd >= 0, true);            // socket valid

    free(addr); // cleanup malloc
    CleanupClient(sockfd);
}

TEST(ClientTest, CleanupClientValidSocket) {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    ASSERT_GE(sockfd, 0);

    int result = CleanupClient(sockfd);
    EXPECT_EQ(result, SUCCESS);
}

TEST(ClientTest, CleanupClientInvalidSocket) {
    int result = CleanupClient(-1); // invalid fd
    EXPECT_EQ(result, FAILURE);
}

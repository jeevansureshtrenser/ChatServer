#include <gtest/gtest.h>
extern "C" {
    #include "server.h"
    #include "config.h"
}

// Mock config for testing
SERVER_CONFIG mockConfig = {
    .ip = "127.0.0.1",
    .port = 9090
};

SERVER_CONFIG* GetServerConfig() {
    return &mockConfig;  // override real function
}

TEST(ServerTest, InitializeServerValidConfig) {
    int sockfd;
    struct sockaddr_in* addr = InitializeServer(&sockfd);

    ASSERT_NE(addr, nullptr);                // should succeed
    EXPECT_EQ(addr->sin_family, AF_INET);    // family set
    EXPECT_EQ(ntohs(addr->sin_port), 9090);  // port set
    EXPECT_EQ(sockfd >= 0, true);            // socket valid

    free(addr); // cleanup malloc
    CleanupServer(sockfd);
}

TEST(ServerTest, CleanupServerValidSocket) {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    ASSERT_GE(sockfd, 0);

    int result = CleanupServer(sockfd);
    EXPECT_EQ(result, SUCCESS);
}

TEST(ServerTest, CleanupServerInvalidSocket) {
    int result = CleanupServer(-1); // invalid fd
    EXPECT_EQ(result, FAILURE);
}

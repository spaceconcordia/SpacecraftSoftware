#include <gtest/gtest.h>
#include <unistd.h>

#define BUFFER 256

TEST(HelloTest, Hostname) {
	char hostname[BUFFER];
	gethostname(hostname, sizeof(hostname));

	ASSERT_STREQ(hostname, "Buildroot");
}

#include "gtest/gtest.h"

TEST(Testsuit, test_c){
	EXPECT_EQ(3, 2);
}

int main(int argc, char **argv){
    
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();


}

#include "controller_tests.hpp"

namespace
{
TEST_F(ControllerTest, InitCreatesCaptureAndAppliesRulesTest)
{
    EXPECT_CALL(*mockCapture_, setBerkeleyRule(testing::_)).Times(testing::AtLeast(0));
    EXPECT_CALL(*mockCapture_, setNIC(testing::_)).Times(testing::AtLeast(0));
    EXPECT_CALL(*mockCapture_, setFileLength(testing::_)).Times(testing::AtLeast(0));
    EXPECT_CALL(*mockCapture_, setFileAmount(testing::_)).Times(testing::AtLeast(0));

    controller_->init();
}

TEST_F(ControllerTest, ApplyRulesAppliesCorrectRulesTest)
{
    modifyFileLengthInRuleList(std::regex(R"(BERKELEY:\S+)"), "BERKELEY:udp");
    modifyFileLengthInRuleList(std::regex(R"(FILE_LENGTH:\d+)"), "FILE_LENGTH:11");

    EXPECT_CALL(*mockCapture_, setBerkeleyRule("udp")).Times(1);
    EXPECT_CALL(*mockCapture_, setFileLength(11)).Times(1);

    controller_->applyRules();
}

} // namespace

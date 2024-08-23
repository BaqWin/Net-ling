#include "controller_tests.hpp"

namespace
{
TEST_F(ControllerTest, InitCreatesCaptureAndAppliesRulesTest)
{
    EXPECT_CALL(*mockCapture, setBerkeleyRule(testing::_)).Times(testing::AtLeast(0));
    EXPECT_CALL(*mockCapture, setNIC(testing::_)).Times(testing::AtLeast(0));
    EXPECT_CALL(*mockCapture, setFileLength(testing::_)).Times(testing::AtLeast(0));
    EXPECT_CALL(*mockCapture, setFileAmount(testing::_)).Times(testing::AtLeast(0));

    controller->init();
}

TEST_F(ControllerTest, ApplyRulesAppliesCorrectRulesTest)
{
    modifyFileLengthInRuleList(std::regex(R"(BERKELEY:\S+)"), "BERKELEY:udp");
    modifyFileLengthInRuleList(std::regex(R"(FILE_LENGTH:\d+)"), "FILE_LENGTH:11");

    EXPECT_CALL(*mockCapture, setBerkeleyRule("udp")).Times(1);
    EXPECT_CALL(*mockCapture, setFileLength(11)).Times(1);

    controller->applyRules();
}

} // namespace

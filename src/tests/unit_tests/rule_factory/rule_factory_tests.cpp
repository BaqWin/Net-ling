#include "rule_factory_tests.hpp"

namespace
{

TEST_F(RuleFactoryTest, EmptyFileTest)
{
    std::string filePath = createTempFile({}, filePath_);
    auto rules = ruleFactory_.getRules(filePath);
    EXPECT_TRUE(rules.empty());
}

TEST_F(RuleFactoryTest, ValidRulesTest)
{
    std::string filePath = createTempFile({"BERKELEY:42", "FILE_LENGTH:some_text"}, filePath_);

    auto rules = ruleFactory_.getRules(filePath);

    ASSERT_EQ(rules.size(), 2);
    EXPECT_EQ(rules[0].first, RuleType::BERKELEY);
    EXPECT_EQ(std::get<int>(rules[0].second), 42);
    EXPECT_EQ(rules[1].first, RuleType::FILE_LENGTH);
    EXPECT_EQ(std::get<std::string>(rules[1].second), "some_text");
}

TEST_F(RuleFactoryTest, MalformedLineTest)
{
    std::string filePath = createTempFile({"BERKELEY 42"}, filePath_);

    auto rules = ruleFactory_.getRules(filePath);

    EXPECT_TRUE(rules.empty());
}

TEST_F(RuleFactoryTest, ValidNonIntegerRuleTest)
{
    std::string filePath = createTempFile({"NIC:network_card"}, filePath_);

    auto rules = ruleFactory_.getRules(filePath);

    ASSERT_EQ(rules.size(), 1);
    EXPECT_EQ(rules[0].first, RuleType::NIC);
    EXPECT_EQ(std::get<std::string>(rules[0].second), "network_card");
}

TEST_F(RuleFactoryTest, CaseInsensitiveRuleTypeTest)
{
    std::string filePath = createTempFile({"berkeley:42", "file_length:1024", "Nic:network_card"}, filePath_);

    auto rules = ruleFactory_.getRules(filePath);

    ASSERT_EQ(rules.size(), 3);
    EXPECT_EQ(rules[0].first, RuleType::BERKELEY);
    EXPECT_EQ(std::get<int>(rules[0].second), 42);
    EXPECT_EQ(rules[1].first, RuleType::FILE_LENGTH);
    EXPECT_EQ(std::get<int>(rules[1].second), 1024);
    EXPECT_EQ(rules[2].first, RuleType::NIC);
    EXPECT_EQ(std::get<std::string>(rules[2].second), "network_card");
}

TEST_F(RuleFactoryTest, UnknownRuleTypeTest)
{
    std::string filePath = createTempFile({"unknown_type:42"}, filePath_);

    auto rules = ruleFactory_.getRules(filePath);

    ASSERT_EQ(rules.size(), 1);
    EXPECT_EQ(rules[0].first, RuleType::UNKNOWN);
    EXPECT_EQ(std::get<int>(rules[0].second), 42);
}

} // namespace

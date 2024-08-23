#include "integration_tests.hpp"

namespace{

TEST_F(IntegrationTestFixture, IntegrationSuccessTest)
{
    setTestRuleFilePath(createTempFile({
        "BERKELEY:udp", 
        "FILE_LENGTH:5", 
        "NIC:127.0.0.1", 
        "LOOP_RULE:2"}, 
        ruleFilePath_));
    std::thread pythonThread([this](){
        std::this_thread::sleep_for(std::chrono::seconds(timeout_duration_seconds));
        std::string command = "python3 " + scriptPath_;
        std::system(command.c_str());
    });
    pythonThread.detach();

    Controller::getInstance().init();

    std::size_t fileCount = 0;
    for (const auto& entry : std::filesystem::directory_iterator(tempDir_)) {
            if (std::filesystem::is_regular_file(entry)) {
                ++fileCount;
            }
        }
    
    EXPECT_GT(fileCount, 0);
}

} // namespace

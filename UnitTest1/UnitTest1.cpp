#include "pch.h"
#include "CppUnitTest.h"
#include "../src/word_list.h"
#include "../src/word_list.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    void test(char* words[], int len, const char* ans[], int ans_len,
        char headChar, char tailChar, char rejectChar, bool enable_loop) {
        static char buffer[MAX_NUM][MAX_LENGTH];
        memset(buffer, 0, sizeof(buffer));
        char* result[MAX_LENGTH];
        for (int i = 0; i < ans_len; i++) {
            result[i] = buffer[i];
        }
        int my_len = Core::gen_chain_word(words, len, result, headChar, tailChar, rejectChar, enable_loop);
        Assert::AreEqual(ans_len, my_len);
        for (int i = 0; i < ans_len; i++) {
            if (result != nullptr) {
                Assert::AreEqual(strcmp(ans[i], result[i]), 0);
            }
        }
    }
   
	TEST_CLASS(UnitTest1)
	{
	public:
		
        TEST_METHOD(test_w) {
            char* words[] = { "algebra", "apple", "cool", "element", "ur", "fox", "dog", "cat", "leaf", "trick", "pm" };
            const char* ans[] = { "algebra", "apple", "element", "trick" };
            test(words, 11, ans, 4, 0, 0, 0, false);
        }
        TEST_METHOD(test_w_h) {
            char* words[] = { "algebra", "apple", "cool", "element", "ur", "fox", "dog", "cat", "leaf", "trick", "pm" };
            const char* ans[] = { "cool", "leaf", "fox" };
            test(words, 11, ans, 3, 'c', 0, 0, false);
        }
        TEST_METHOD(test_w_t) {
            char* words[] = { "algebra", "apple", "cool", "element", "ur", "fox", "dog", "cat", "leaf", "trick", "pm" };
            const char* ans[] = { "cool", "leaf", "fox" };
            test(words, 11, ans, 3, 0, 'x', 0, false);
        }
        TEST_METHOD(test_w_h_t) {
            char* words[] = { "algebra", "apple", "cool", "element", "ur", "fox", "dog", "cat", "leaf", "trick", "pm", "zyx", "xuv" };
            const char* ans[] = { "zyx", "xuv" };
            test(words, 13, ans, 2, 'z', 'v', 0, false);
        }
	};
}

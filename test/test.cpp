#include "pch.h"
#include "CppUnitTest.h"
#include "../src/word_list.cpp"
#include "../src/word_list.h"
#include <cassert>
#include <algorithm>
#include <stdexcept>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test_gen_chain_word_correct {
    void test(char*words[], int len, const char* ans[], int ans_len,
              char headChar, char tailChar, char rejectChar, bool enable_loop){
        char** result = (char**)malloc(10000);
        int my_len = gen_chain_word( words, len, result, headChar, tailChar, rejectChar, enable_loop);
        Assert::AreEqual(ans_len, my_len);
        for(int i = 0; i < ans_len; i++){
            if(result != nullptr){
                Assert::AreEqual(strcmp(ans[i], result[i]), 0);
            }
        }
    }

	TEST_CLASS(test_gen_chain_word_correct)
	{
	public:
		TEST_METHOD(test_w) {
            char* words[] = { "algebra", "apple", "cool", "element", "ur", "fox", "dog", "cat", "leaf", "trick", "pm" };
            const char* ans[] = { "algebra", "apple", "element", "trick" };
            test(words, 11, ans, 4, 0, 0, 0, false);
		}
        TEST_METHOD(test_w_h) {
            char* words[] = { "algebra", "apple", "cool", "element", "ur", "fox", "dog", "cat", "leaf", "trick", "pm" };
            const char* ans[] = { "cat", "trick" };
            test(words, 11, ans, 2, 'c', 0, 0, false);
        }
        TEST_METHOD(test_w_t) {
            char* words[] = { "algebra", "apple", "cool", "element", "ur", "fox", "dog", "cat", "leaf", "trick", "pm" };
            const char* ans[] = { "cat", "trick" };
            test(words, 11, ans, 2, 0, 'k', 0, false);
        }
        TEST_METHOD(test_w_h_t) {
            char* words[] = { "algebra", "apple", "cool", "element", "ur", "fox", "dog", "cat", "leaf", "trick", "pm", "zyx", "xvu" };
            const char* ans[] = { "zyx", "xuv" };
            test(words, 13, ans, 2, 'v', 'z', 0, false);
        }
	};
}

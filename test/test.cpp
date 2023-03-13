#include "pch.h"
#include "CppUnitTest.h"
#include "../src/Core.h"
#include <cassert>
#include <algorithm>
#include <stdexcept>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test_gen_chai_word_correct
{
    void test(const char*words[], int len, const char* ans[], int ans_len,
              char headChar, char tailChar, char rejectChar, bool enable_loop){
        char** result = (char**)malloc(10000);
        int my_len = gen_chain_word(words, len, result, headChar, tailChar, rejectChar, enable_loop);
        Assert::AreEqual(ans_len, my_len);
        for(int i = 0; i < ans_len; i++){
            if(result != nullptr){
                Assert::AreEqual(strcmp(ans[i], result[i]), 0);
            }
        }
    }

	TEST_CLASS(test_gen_chai_word_correct)
	{
	public:
		
		TEST_METHOD(test_w) {
		}
        TEST_METHOD(test_w_h) {

        }
        TEST_METHOD(test_w_t) {

        }
        TEST_METHOD(test_w_h_t) {

        }
	};
}

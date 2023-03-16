#include "pch.h"
#include "CppUnitTest.h"
#include "../src/word_list.h"
#include "../src/word_list.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    void test_word(char* words[], int len, const char* ans[], int ans_len,
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

    void test_char(char* words[], int len, const char* ans[], int ans_len,
        char headChar, char tailChar, char rejectChar, bool enable_loop) {
        static char buffer[MAX_NUM][MAX_LENGTH];
        memset(buffer, 0, sizeof(buffer));
        char* result[MAX_LENGTH];
        for (int i = 0; i < ans_len; i++) {
            result[i] = buffer[i];
        }
        int my_len = Core::gen_chain_char(words, len, result, headChar, tailChar, rejectChar, enable_loop);
        Assert::AreEqual(ans_len, my_len);
        for (int i = 0; i < ans_len; i++) {
            if (result != nullptr) {
                Assert::AreEqual(strcmp(ans[i], result[i]), 0);
            }
        }
    }

    void test_all (char* words[], int len, const char* ans[], int ans_len) {
        static char buffer[MAX_NUM][MAX_LENGTH];
        memset(buffer, 0, sizeof(buffer));
        char* result[MAX_LENGTH];
        for (int i = 0; i < ans_len; i++) {
            result[i] = buffer[i];
        }
        int my_len = Core::gen_chains_all(words, len, result);
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
		
        //W no ring
        TEST_METHOD(test_w) {
            char* words[] = { "algebra", "apple", "cool", "element", "ur", "fox", "dog", "cat", "leaf", "trick", "paaaam" };
            const char* ans[] = { "algebra", "apple", "element", "trick" };
            test_word(words, 11, ans, 4, 0, 0, 0, false);
        }
        TEST_METHOD(test_w_h) {
            char* words[] = { "algebra", "apple", "cool", "element", "ur", "fox", "dog", "cat", "leaf", "trick", "pm" };
            const char* ans[] = { "cool", "leaf", "fox" };
            test_word(words, 11, ans, 3, 'c', 0, 0, false);
        }
        TEST_METHOD(test_w_t) {
            char* words[] = { "algebra", "apple", "cool", "element", "ur", "fox", "dog", "cat", "leaf", "trick", "pm" };
            const char* ans[] = { "cool", "leaf", "fox" };
            test_word(words, 11, ans, 3, 0, 'x', 0, false);
        }
        TEST_METHOD(test_w_h_t) {
            char* words[] = { "algebra", "apple", "cool", "element", "ur", "fox", "dog", "cat", "leaf", "trick", "pm", "zyx", "xuv" };
            const char* ans[] = { "zyx", "xuv" };
            test_word(words, 13, ans, 2, 'z', 'v', 0, false);
        }
        TEST_METHOD(test_w_j) {
            char* words[] = { "algebra", "apple", "cool", "element", "ur", "fox", "dog", "cat", "leaf", "trick", "pm", "zyx", "xuv" };
            const char* ans[] = { "cool","leaf","fox","xuv" };
            test_word(words, 13, ans, 4, 0, 0, 'a', false);
        }

        
 
        //W ring 
        TEST_METHOD(test_w_r_r) {
            char* words[] = { "element", "heaven", "table", "teach", "talk" };
            const char* ans[] = { "table", "element", "teach", "heaven" };
            test_word(words, 5, ans, 4, 0, 0, 0, true);
        }
        

        TEST_METHOD(test_w_r_h) {
            char* words[] = { "element", "heaven", "table", "teach", "talk" };
            const char* ans[] = { "element", "teach", "heaven" };
            test_word(words, 5, ans, 3, 'e', 0, 0, true);
        }

        TEST_METHOD(test_w_r_t) {
            char* words[] = { "element", "heaven", "table", "teach", "talk" };
            const char* ans[] = { "table", "element", "teach" };
            test_word(words, 5, ans, 3, 0, 'h', 0, true);
        }

        TEST_METHOD(test_w_r_h_t) {
            char* words[] = { "element", "heaven", "table", "teach", "talk" };
            const char* ans[] = { "element", "teach" };
            test_word(words, 5, ans, 2, 'e', 'h', 0, true);
        }

        TEST_METHOD(test_w_r_j) {
            char* words[] = { "element", "heaven", "table", "teach", "talk" };
            const char* ans[] = {"teach", "heaven" };
            test_word(words, 5, ans, 2, 0, 0, 'e', true);
        }

        //C no ring
        TEST_METHOD(test_c) {
            char* words[] = { "algebra", "app", "cool", "element", "ur", "fox", "dog", "cat", "leaf", "trick", "paaaaaaaaaaaaaaaaaaam" };
            const char* ans[] = { "algebra", "app", "paaaaaaaaaaaaaaaaaaam"};
            test_char(words, 11, ans, 3, 0, 0, 0, false);
        }
        TEST_METHOD(test_c_h) {
            char* words[] = { "algebra", "app", "cool", "element", "ur", "fox", "dog", "cat", "leaf", "trick", "paaaaaaaaaaaaaaaaaaam" };
            const char* ans[] = { "cool", "leaf", "fox" };
            test_char(words, 11, ans, 3, 'c', 0, 0, false);
        }
        TEST_METHOD(test_c_t) {
            char* words[] = { "algebra", "app", "cool", "element", "ur", "fox", "dog", "cat", "leaf", "trick", "paaaaaaaaaaaaaaaaaaam" };
            const char* ans[] = { "cool", "leaf", "fox" };
            test_char(words, 11, ans, 3, 0, 'x', 0, false);
        }
        TEST_METHOD(test_c_h_t) {
            char* words[] = { "algebra", "apple", "cool", "element", "ur", "fox", "dog", "cat", "leaf", "trick", "pm", "zyx", "xuv" };
            const char* ans[] = { "zyx", "xuv" };
            test_char(words, 13, ans, 2, 'z', 'v', 0, false);
        }
        TEST_METHOD(test_c_j) {
            char* words[] = { "algebra", "app", "cool", "element", "ur", "fox", "dog", "cat", "leaf", "trick", "paaaaaaaaaaaaaaaaaaam" };
            const char* ans[] = { "element","trick" };
            test_char(words, 11, ans, 2, 0, 0, 'p', false);
        }
        
        
        //C ring
        TEST_METHOD(test_c_r) {
            char* words[] = { "element", "heaven", "table", "teach", "talkkkkkkkkkkkkkkkkk", "kaaaaaaa"};
            const char* ans[] = { "table","element", "talkkkkkkkkkkkkkkkkk", "kaaaaaaa" };
            test_char(words, 6, ans, 4, 0, 0, 0, true);
        }


        TEST_METHOD(test_c_r_h) {
            char* words[] = { "element", "heaven", "table", "teach", "talkkkkkkkkkkkkkkkkk", "kaaaaaaa" };
            const char* ans[] = { "element", "talkkkkkkkkkkkkkkkkk", "kaaaaaaa" };
            test_char(words, 6, ans, 3, 'e', 0, 0, true);
        }


        TEST_METHOD(test_c_r_t) {
            char* words[] = { "element", "heaven", "table", "teach", "talkkkkkkkkkkkkkkkkk", "kaaaaaaa" };
            const char* ans[] = { "table","element", "talkkkkkkkkkkkkkkkkk" };
            test_char(words, 6, ans, 3, 0, 'k', 0, true);
        }


        TEST_METHOD(test_c_r_ht) {
            char* words[] = { "element", "heaven", "table", "teach", "talkkkkkkkkkkkkkkkkk", "kaaaaaaa" };
            const char* ans[] = { "element", "talkkkkkkkkkkkkkkkkk" };
            test_char(words, 6, ans, 2, 'e', 'k', 0, true);
        }


        TEST_METHOD(test_c_r_j) {
            char* words[] = { "element", "heaven", "table", "teach", "talkkkkkkkkkkkkkkkkk", "kaaaaaaa" };
            const char* ans[] = { "talkkkkkkkkkkkkkkkkk", "kaaaaaaa" };
            test_char(words, 6, ans, 2, 0, 0, 'e', true);
        }

        

        //N
        TEST_METHOD(test_n) {
            char* words[] = { "woo", "oom", "moon", "noox" };
            const char* ans[] = { "moon noox", "oom moon", "oom moon noox", "woo oom", "woo oom moon", "woo oom moon noox" };
            test_all(words, 4, ans, 6);
        }
        //Exception:has ring
        
        //Exception:no chain

        /*参数过少*/

        TEST_METHOD(lack_arguments) {
            char* args[] = { "word-list.exe" };
            int ret =main_serve(1, args);
            Assert::AreEqual(NOT_TXT, ret);
        }

    };
}

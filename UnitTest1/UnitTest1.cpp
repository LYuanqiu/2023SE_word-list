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

    void init() {
        head = 0;
        tail = 0;
        reject = 0;
        isRing = false;
        option = Option::DEFAULT;
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
            init();
            char* words[] = { "woo", "oom", "moon", "noox" };
            const char* ans[] = { "moon noox", "oom moon", "oom moon noox", "woo oom", "woo oom moon", "woo oom moon noox" };
            test_all(words, 4, ans, 6);
        }
        //Exception:has ring
        
        //Exception:no chain

        /*参数过少*/


        TEST_METHOD(unkonwn_option) {
            init();
            char* args[] = { "word-list.exe", "-m", "test.txt" };
            int ret = main_serve(3, args);
            Assert::AreEqual(UNKNOWN_OP, ret);
        }

        TEST_METHOD(conflict_option) {
            init();
            char* args[] = { "word-list.exe", "-n", "-c", "test.txt" };
            int ret = main_serve(4, args);
            Assert::AreEqual(CONFLICT_OP, ret);
        }


        TEST_METHOD(no_such_file) {
            init();
            char* args[] = { "word-list.exe", "-n", "no.txt" };
            int ret = main_serve(3, args);
            Assert::AreEqual(OPEN_FAILED, ret);
        }

        // todo 不知道怎么打不开文件
        TEST_METHOD(open_failed_file) {
            init();
            char* args[] = { "word-list.exe", "-n", "unopen.txt" };
            int ret = main_serve(3, args);
            Assert::AreEqual(OPEN_FAILED, ret);
        }

        TEST_METHOD(no_words_file) {
            init();
            char* args[] = { "word-list.exe", "-n", "no_words.txt" };
            ofstream output;
            output.open("no_words.txt", ios::out | ios::binary | ios::trunc);
            output.close();
            int ret = main_serve(3, args);
            Assert::AreEqual(NO_WORDS, ret);
        }

        // todo 不知道怎么fail_output
        /*
        TEST_METHOD(fail_output_file) {
            char* args[] = { "word-list.exe", "-n", "test.txt"};
            int ret =main_serve(3, args);
            Assert::AreEqual(NO_WORDS, ret);
        }
        */
        TEST_METHOD(missing_filename) {
            init();
            char* args[] = { "word-list.exe", "-n" };
            int ret = main_serve(2, args);
            Assert::AreEqual(NOT_TXT, ret);
        }

        TEST_METHOD(h_no_alpha) {
            init();
            char* args[] = { "word-list.exe", "-w", "-h", "test.txt" };
            int ret = main_serve(4, args);
            Assert::AreEqual(H_NO_ALPHA, ret);
        }

        TEST_METHOD(t_no_alpha) {
            init();
            char* args[] = { "word-list.exe","-w","-t", "test.txt" };
            int ret = main_serve(4, args);
            Assert::AreEqual(T_NO_ALPHA, ret);
        }



        TEST_METHOD(lack_arguments) {
            init();
            char* args[] = { "word-list.exe" };
            int ret = main_serve(1, args);
            Assert::AreEqual(NOT_TXT, ret);
        }

        TEST_METHOD(j_no_alpha) {
            init();
            char* args[] = { "word-list.exe", "-w", "-j","test.txt" };
            int ret = main_serve(4, args);
            Assert::AreEqual(J_NO_ALPHA, ret);
        }

        TEST_METHOD(h_long_alpha) {
            init();
            char* args[] = { "word-list.exe", "-w", "-h", "ab","test.txt" };
            int ret = main_serve(5, args);
            Assert::AreEqual(H_LONG_ALPHA, ret);
        }

        TEST_METHOD(t_long_alpha) {
            init();
            char* args[] = { "word-list.exe", "-w", "-t", "ab","test.txt" };
            int ret = main_serve(5, args);
            Assert::AreEqual(T_LONG_ALPHA, ret);
        }

        TEST_METHOD(j_long_alpha) {
            init();
            char* args[] = { "word-list.exe", "-w", "-j", "ab","test.txt" };
            int ret = main_serve(5, args);
            Assert::AreEqual(J_LONG_ALPHA, ret);
        }

        TEST_METHOD(lack_command) {
            init();
            char* args[] = { "word-list.exe", "test.txt" };
            int ret = main_serve(2, args);
            Assert::AreEqual(LACK_COMMAND, ret);
        }

        TEST_METHOD(no_chain_n) {
            init();
            try {
                ofstream output;
                output.open("no_chain.txt", ios::out | ios::binary | ios::trunc);
                output << "aaa" << endl;
                output << "bbb" << endl;
                output.close();
                char* args[] = { "word-list.exe", "-n", "no_chain.txt" };
                main_serve(3, args);
            }
            catch (runtime_error const& e) {
                Assert::AreEqual(0, strcmp("There is no chain in the file!", e.what()));
                return;
            }
            Assert::Fail();
        }

        TEST_METHOD(no_chain_w) {
            init();
            try {
                ofstream output;
                output.open("no_chain.txt", ios::out | ios::binary | ios::trunc);
                output << "aaa" << endl;
                output << "bbb" << endl;
                output.close();
                char* args[] = { "word-list.exe", "-w", "no_chain.txt" };
                main_serve(3, args);
            }
            catch (runtime_error const& e) {
                Assert::AreEqual(0, strcmp("There is no chain in the file!", e.what()));
                return;
            }
            Assert::Fail();
        }

        TEST_METHOD(no_chain_w_r) {
            init();
            try {
                ofstream output;
                output.open("no_chain.txt", ios::out | ios::binary | ios::trunc);
                output << "aaa" << endl;
                output << "bbb" << endl;
                output.close();
                char* args[] = { "word-list.exe", "-w", "-r", "no_chain.txt" };
                main_serve(4, args);
            }
            catch (runtime_error const& e) {
                Assert::AreEqual(0, strcmp("There is no chain in the file!", e.what()));
                return;
            }
            Assert::Fail();
        }

        TEST_METHOD(no_chain_c_h) {
            init();
            try {
                ofstream output;
                output.open("no_chain.txt", ios::out | ios::binary | ios::trunc);
                output << "aaa" << endl;
                output << "aac" << endl;
                output << "bbb" << endl;
                output.close();
                char* args[] = { "word-list.exe", "-c", "-h", "b","no_chain.txt" };
                main_serve(5, args);
            }
            catch (runtime_error const& e) {
                Assert::AreEqual(0, strcmp("There is no chain in the file!", e.what()));
                return;
            }
            Assert::Fail();
        }

        TEST_METHOD(no_chain_c_h_r) {
            init();
            try {
                ofstream output;
                output.open("no_chain.txt", ios::out | ios::binary | ios::trunc);
                output << "aaa" << endl;
                output << "aac" << endl;
                output << "bbb" << endl;
                output.close();
                char* args[] = { "word-list.exe", "-c", "-r", "-h", "b","no_chain.txt" };
                main_serve(6, args);
            }
            catch (runtime_error const& e) {
                Assert::AreEqual(0, strcmp("There is no chain in the file!", e.what()));
                return;
            }
            Assert::Fail();
        }

        TEST_METHOD(has_ring_n) {
            init();
            try {
                ofstream output;
                output.open("has_ring.txt", ios::out | ios::binary | ios::trunc);
                output << "aaa" << endl;
                output << "aabb" << endl;
                output << "bbb" << endl;
                output << "bbaa" << endl;
                output.close();
                char* args[] = { "word-list.exe", "-n", "has_ring.txt" };
                main_serve(3, args);
            }
            catch (runtime_error const& e) {
                Assert::AreEqual(0, strcmp("There are rings in the file!", e.what()));
                return;
            }
            Assert::Fail();
        }

        TEST_METHOD(has_ring_w) {
            init();
            try {
                ofstream output;
                output.open("has_ring.txt", ios::out | ios::binary | ios::trunc);
                output << "aaa" << endl;
                output << "aabb" << endl;
                output << "bbb" << endl;
                output << "bbaa" << endl;
                output.close();
                char* args[] = { "word-list.exe",  "-w", "has_ring.txt" };
                main_serve(3, args);
            }
            catch (runtime_error const& e) {
                Assert::AreEqual(0, strcmp("There are rings in the file!", e.what()));
                return;
            }
            Assert::Fail();
        }

        TEST_METHOD(has_ring_c_j) {
            init();
            try {
                ofstream output;
                output.open("has_ring.txt", ios::out | ios::binary | ios::trunc);
                output << "aaa" << endl;
                output << "aabb" << endl;
                output << "bbb" << endl;
                output << "bbaa" << endl;
                output.close();
                char* args[] = { "word-list.exe", "-c", "-j", "b","has_ring.txt" };
                main_serve(5, args);
            }
            catch (runtime_error const& e) {
                Assert::AreEqual(0, strcmp("There are rings in the file!", e.what()));
                return;
            }
            Assert::Fail();
        }
    };
}

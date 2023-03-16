#include "pch.h"
#include "CppUnitTest.h"
#include "../src/word_list.h"
#include "../src/word_list.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestException
{

	TEST_CLASS(UnitTestException)
	{
	public:


        TEST_METHOD(unkonwn_option) {
            char* args[] = { "word-list.exe", "-m", "test.txt"};
            int ret =main_serve(3, args);
            Assert::AreEqual(UNKNOW_OP, ret);
        }

        TEST_METHOD(conflict_option) {
            char* args[] = { "word-list.exe", "-n", "-c", "test.txt"};
            int ret =main_serve(4, args);
            Assert::AreEqual(CONFLICT_OP, ret);
        }

        TEST_METHOD(conflict_option) {
            char* args[] = { "word-list.exe", "-n", "-c", "test.txt"};
            int ret =main_serve(4, args);
            Assert::AreEqual(CONFLICT_OP, ret);
        }

        TEST_METHOD(no_such_file) {
            char* args[] = { "word-list.exe", "-n", "no.txt"};
            int ret =main_serve(3, args);
            Assert::AreEqual(NO_SUCH_FILE, ret);
        }

        // todo 不知道怎么打不开文件
        TEST_METHOD(open_failed_file) {
            char* args[] = { "word-list.exe", "-n", "unopen.txt"};
            int ret =main_serve(3, args);
            Assert::AreEqual(OPEN_FAILED, ret);
        }

        TEST_METHOD(no_words_file) {
            char* args[] = { "word-list.exe", "-n", "no_words.txt"};
            int ret =main_serve(3, args);
            Assert::AreEqual(NO_WORDS, ret);
        }

        // todo 不知道怎么fail_output
        TEST_METHOD(fail_output_file) {
            char* args[] = { "word-list.exe", "-n", "test.txt"};
            int ret =main_serve(3, args);
            Assert::AreEqual(NO_WORDS, ret);
        }

        TEST_METHOD(missing_filename) {
            char* args[] = { "word-list.exe", "-n"};
            int ret =main_serve(2, args);
            Assert::AreEqual(MISSING_FILE, ret);
        }

        TEST_METHOD(h_no_alpha) {
            char* args[] = { "word-list.exe", "-h", "test.txt"};
            int ret =main_serve(3, args);
            Assert::AreEqual(H_NO_ALPHA , ret);
        }

        TEST_METHOD(t_no_alpha) {
            char* args[] = { "word-list.exe", "-t", "test.txt"};
            int ret =main_serve(3, args);
            Assert::AreEqual(T_NO_ALPHA , ret);
        }



    TEST_METHOD(lack_arguments) {
            char* args[] = { "word-list.exe" };
            int ret =main_serve(1, args);
            Assert::AreEqual(NOT_TXT, ret);
        }

        TEST_METHOD(j_no_alpha) {
            char* args[] = { "word-list.exe", "-w", "-j","test.txt"};
            int ret = main_serve(4, args);
            Assert::AreEqual(J_NO_ALPHA, ret);
        }

        TEST_METHOD(h_long_alpha) {
            char* args[] = { "word-list.exe", "-w", "-h", "ab","test.txt"};
            int ret = main_serve(5, args);
            Assert::AreEqual(H_LONG_ALPHA, ret);
        }

        TEST_METHOD(t_long_alpha) {
            char* args[] = { "word-list.exe", "-w", "-t", "ab","test.txt"};
            int ret = main_serve(5, args);
            Assert::AreEqual(T_LONG_ALPHA, ret);
        }

        TEST_METHOD(j_long_alpha) {
            char* args[] = { "word-list.exe", "-w", "-j", "ab","test.txt"};
            int ret = main_serve(5, args);
            Assert::AreEqual(J_LONG_ALPHA, ret);
        }

        TEST_METHOD(lack_command) {
            char* args[] = { "word-list.exe", "test.txt"};
            int ret = main_serve(2, args);
            Assert::AreEqual(LACK_COMMAND, ret);
        }

        TEST_METHOD(no_chain_n) {
            try{
				ofstream output;
				output.open("no_chain.txt", ios::out | ios::binary | ios::trunc);
                output << "aaa" << endl;
                output << "bbb" << endl;
				output.close();
				char* args[] = {"word-list.exe", "-n", "no_chain.txt"};
				main_serve(3, args);
			}catch(runtime_error const& e){
				Assert::AreEqual(0, strcmp("There is no chain in the file!", e.what()));
				return;
			}
			Assert::Fail();
        }
        
        TEST_METHOD(no_chain_w) {
            try{
				ofstream output;
				output.open("no_chain.txt", ios::out | ios::binary | ios::trunc);
                output << "aaa" << endl;
                output << "bbb" << endl;
				output.close();
				char* args[] = {"word-list.exe", "-w", "no_chain.txt"};
				main_serve(3, args);
			}catch(runtime_error const& e){
				Assert::AreEqual(0, strcmp("There is no chain in the file!", e.what()));
				return;
			}
			Assert::Fail();
        }

        TEST_METHOD(no_chain_w_r) {
            try{
				ofstream output;
				output.open("no_chain.txt", ios::out | ios::binary | ios::trunc);
                output << "aaa" << endl;
                output << "bbb" << endl;
				output.close();
				char* args[] = {"word-list.exe", "-w", "-r", "no_chain.txt"};
				main_serve(4, args);
			}catch(runtime_error const& e){
				Assert::AreEqual(0, strcmp("There is no chain in the file!", e.what()));
				return;
			}
			Assert::Fail();
        }

        TEST_METHOD(no_chain_c_h) {
            try{
				ofstream output;
				output.open("no_chain.txt", ios::out | ios::binary | ios::trunc);
                output << "aaa" << endl;
                output << "aac" << endl;
                output << "bbb" << endl;
				output.close();
				char* args[] = {"word-list.exe", "-c", "-h", "b","no_chain.txt"};
				main_serve(5, args);
			}catch(runtime_error const& e){
				Assert::AreEqual(0, strcmp("There is no chain in the file!", e.what()));
				return;
			}
			Assert::Fail();
        }

        TEST_METHOD(no_chain_c_h_r) {
            try{
				ofstream output;
				output.open("no_chain.txt", ios::out | ios::binary | ios::trunc);
                output << "aaa" << endl;
                output << "aac" << endl;
                output << "bbb" << endl;
				output.close();
				char* args[] = {"word-list.exe", "-c", "-r", "-h", "b","no_chain.txt"};
				main_serve(6, args);
			}catch(runtime_error const& e){
				Assert::AreEqual(0, strcmp("There is no chain in the file!", e.what()));
				return;
			}
			Assert::Fail();
        }

        TEST_METHOD(has_ring_n) {
            try{
				ofstream output;
				output.open("has_ring.txt", ios::out | ios::binary | ios::trunc);
                output << "aaa" << endl;
                output << "aabb" << endl;
                output << "bbb" << endl;
                output << "bbaa" << endl;
				output.close();
				char* args[] = {"word-list.exe", "-n", "has_ring.txt"};
				main_serve(3, args);
			}catch(runtime_error const& e){
				Assert::AreEqual(0, strcmp("There are rings in the file!", e.what()));
				return;
			}
			Assert::Fail();
        }

        TEST_METHOD(has_ring_w) {
            try{
				ofstream output;
				output.open("has_ring.txt", ios::out | ios::binary | ios::trunc);
                output << "aaa" << endl;
                output << "aabb" << endl;
                output << "bbb" << endl;
                output << "bbaa" << endl;
				output.close();
				char* args[] = {"word-list.exe",  "-w", "has_ring.txt"};
				main_serve(3, args);
			}catch(runtime_error const& e){
				Assert::AreEqual(0, strcmp("There are rings in the file!", e.what()));
				return;
			}
			Assert::Fail();
        }

        TEST_METHOD(has_ring_c_j) {
            try{
				ofstream output;
				output.open("has_ring.txt", ios::out | ios::binary | ios::trunc);
                output << "aaa" << endl;
                output << "aabb" << endl;
                output << "bbb" << endl;
                output << "bbaa" << endl;
				output.close();
				char* args[] = {"word-list.exe", "-c", "-j", "b","has_ring.txt"};
				main_serve(5, args);
			}catch(runtime_error const& e){
				Assert::AreEqual(0, strcmp("There are rings in the file!", e.what()));
				return;
			}
			Assert::Fail();
        }
	};
}

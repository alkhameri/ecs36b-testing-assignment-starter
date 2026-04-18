#include <cstdlib>
#include <string>
#include "gtest/gtest.h"
#include "formatting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

auto word_generator() {
    /* Creates a generator for a string made up of
     * characters from [a - z]
     */
    return rc::gen::container<std::string>(rc::gen::inRange('a', (char)('z' + 1)));
}

auto vector_of_ints_to_vector_of_strings(const std::vector<int>& numbers) {
    /* Create a vector of strings from a vector of ints
     */
    std::vector<std::string> result;
    for (int num : numbers) {
        result.push_back(std::to_string(num));
    }
    return result;
}


TEST(ParseArgsTests, SimpleCheckArgumentsParsedSuccessfully) {
    /*
     * Check that you parse the command line arguments correctly.
     * (ar_out and len_out are set to the right values).
     * Don't forget to free any memory that was dynamically allocated as part of your test.'
     */
    int argc = 4;
    char prog[] = "program";
    char arg1[] = "1";
    char arg2[] = "2";
    char arg3[] = "3";
    char* argv[] = {prog, arg1, arg2, arg3};

    int ar_out[3];
    int len_out = 0;

    parse_args(argc, argv, ar_out, &len_out);

    ASSERT_EQ(len_out, 3);
    ASSERT_EQ(ar_out[0], 1);
    ASSERT_EQ(ar_out[1], 2);
    ASSERT_EQ(ar_out[2], 3);
}

TEST(ParseArgsTests, SimpleCheckParseNoArgs) {
    /*
     * Check that you parse you can successfully parse "no" command line arguments.
     */
    int argc = 1;
    char prog[] = "program";
    char* argv[] = {prog};

    int len_out = 0;
    int* ar_out = NULL;

    parse_args(argc, argv, ar_out, &len_out);

    ASSERT_EQ(len_out, 0);
}


RC_GTEST_PROP(ParseArgsTests,
              PropertyCheckArgumentsParsedSuccessfully,
              (std::vector<int> numbers)
) {
    /* Check that we can correctly parse the command line
     * arguments when we receive 1 or more arguments.
     * Don't forget to free any memory that was dynamically allocated as part of this test
     */
    RC_PRE(!numbers.empty());

    auto str_numbers = vector_of_ints_to_vector_of_strings(numbers);

    std::vector<char*> argv;
    std::string prog_name = "program";
    argv.push_back(&prog_name[0]);
    for (auto& s : str_numbers) {
        argv.push_back(&s[0]);
    }

    int argc = argv.size();
    int* ar_out = new int[numbers.size()];
    int len_out = 0;

    parse_args(argc, argv.data(), ar_out, &len_out);

    RC_ASSERT(len_out == (int)numbers.size());
    for (int i = 0; i < len_out; ++i) {
        RC_ASSERT(ar_out[i] == numbers[i]);
    }

    delete[] ar_out;
}

RC_GTEST_PROP(ParseArgsTests,
              PropertyCheckParseNoArgs,
              ()
) {
    /*
     * Check that you parse you can successfully parse "no" command line arguments.
     */
    int argc = 1;
    char program[] = "program";
    char* argv[] = {program};

    int len_out = 0;
    int* ar_out = NULL;

    parse_args(argc, argv, ar_out, &len_out);
    RC_ASSERT(len_out == 0);
}

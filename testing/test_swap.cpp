#include <cstdlib>
#include <vector>
#include <algorithm>
#include "test_helpers.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "sorting.h"
#include "rapidcheck/gtest.h"


TEST(SwapTests, SimpleSwapTwoValues) {
    /*
     * Swap two values and see if the swap was successful.
     */
    int a = 1;
    int b = 2;

    swap(&a, &b);
    ASSERT_EQ(a, 2);
    ASSERT_EQ(b, 1);
}

TEST(SwapTests, SimpleSwapValuesInArray) {
    /*
     * Swap a few values in an array.
     * Check that the ones that swapped did swap and the ones that didn't swap
     * are still at the same locations
     */
    int ar[4] = {1, 2, 3, 4};
    swap(&ar[0], &ar[1]);

    int check[4] = {2, 1, 3, 4};
    for (int i = 0; i < 4; ++i) {
        ASSERT_EQ(check[i], ar[i]);
    }
}

RC_GTEST_PROP(SwapTests,
              PropertySwapTwoValues,
              (int a_start, int b_start)
) {
    /*
     * Swap two values and see if the swap was successful.
     */
    int a = a_start;
    int b = b_start;
    swap(&a, &b);
    RC_ASSERT(a == b_start);
    RC_ASSERT(b == a_start);
}


RC_GTEST_PROP(SwapTests,
              PropertySwapValuesInArray,
              (const std::vector<int>& values)
) {
    /*
     * Swap two values in an array. See that they swapped and the others did not
     */
    RC_PRE((int)values.size() >= 2);
    int len = values.size();
    int* ar = new int[len];
    for (int i = 0; i < len; ++i) {
        ar[i] = values[i];
    }

    swap(&ar[0], &ar[1]);

    RC_ASSERT(ar[0] == values[1]);
    RC_ASSERT(ar[1] == values[0]);
    for (int i = 2; i < len; ++i) {
        RC_ASSERT(ar[i] == values[i]);
    }

    delete[] ar;
}

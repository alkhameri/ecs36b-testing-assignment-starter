#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "rapidcheck/gtest.h"
#include "sorting.h"

TEST(MinIndexOfArrayTests, SimpleMinIndexAtFrontOfArray) {
    /*
     * See if we can find the index of the minimum value when it is at the front of the array
     */
    int ar[5] = {1, 3, 5, 7, 9};
    int result = min_index_of_array(ar, 5);
    ASSERT_EQ(result, 0);
}

TEST(MinIndexOfArrayTests, SimpleMinIndexAtEndOfArray) {
    /*
     * See if we can find the index of the minimum value when it is at the end of the array
     */
    int ar[5] = {9, 7, 5, 3, 1};
    int result = min_index_of_array(ar, 5);
    ASSERT_EQ(result, 4);
}

TEST(MinIndexOfArrayTests, SimpleMinIndexAtMiddleOfArray) {
    /*
     * See if we can find the index of the minimum value when it is somewhere
     * in the "middle" of the array.
     */
    int ar[5] = {5, 3, 1, 7, 9};
    int result = min_index_of_array(ar, 5);
    ASSERT_EQ(result, 2);
}

TEST(MinIndexOfArrayTests, SimpleDuplicateMinimums) {
    /*
     * See if we return the index of the first minimum in the array
     * When there are multiple values that are the minimum.
     */
    int ar[5] = {3, 1, 5, 1, 9};
    int result = min_index_of_array(ar, 5);
    ASSERT_EQ(result, 1);
}

TEST(MinIndexOfArrayTests, SimpleArrayDoesNotChange) {
    /*
     * Check that finding the minimum of the array did not change the contents of the array.
     */
    int ar[5] = {5, 3, 1, 7, 9};
    int check[5] = {5, 3, 1, 7, 9};
    min_index_of_array(ar, 5);
    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(ar[i], check[i]);
    }
}


RC_GTEST_PROP(MinIndexOfArrayTests,
              PropertyFindMinIndex,
              (std::vector<int> values)) {
    /* Check that the value at the location of the minimum index
     * is not larger than any of the other values in the array
     */
    RC_PRE(!values.empty());
    int len = values.size();
    int* ar = new int[len];
    for (int i = 0; i < len; ++i) {
        ar[i] = values[i];
    }

    int min_idx = min_index_of_array(ar, len);

    for (int i = 0; i < len; ++i) {
        RC_ASSERT(ar[min_idx] <= ar[i]);
    }

    delete[] ar;
}

RC_GTEST_PROP(MinIndexOfArrayTests,
              PropertyArrayDoesNotChange,
              (std::vector<int> values)) {
    /*
     * Check that finding the minimum of the array did not change the contents of the array.
     */
    RC_PRE(!values.empty());
    int len = values.size();
    int* ar = new int[len];
    for (int i = 0; i < len; ++i) {
        ar[i] = values[i];
    }

    min_index_of_array(ar, len);

    for (int i = 0; i < len; ++i) {
        RC_ASSERT(ar[i] == values[i]);
    }

    delete[] ar;
}

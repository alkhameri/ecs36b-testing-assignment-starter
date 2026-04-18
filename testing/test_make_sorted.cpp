#include <cstdlib>
#include <vector>
#include "gtest/gtest.h"
#include "sorting.h"
#include "rapidcheck/gtest.h"
#include "test_helpers.h"

TEST(MakeSortedTests, SimpleSortSortedArray) {
    /*
     * Check that we can sort an array that is already sorted.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int len = 4;
    int* ar = new int[len]{2, 4, 6, 7};
    make_sorted(ar, len);

    int check[4] = {2, 4, 6, 7};
     for (int i = 0; i < 4; ++i) {
         ASSERT_EQ(check[i], ar[i]);
     }

    delete[] ar;
}

TEST(MakeSortedTests, SimpleSortReverseSortedArray) {
    /*
     * Check that we can sort an array that is reverse sorted order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int len = 4;
    int* ar = new int[len]{7, 6, 4, 2};
    make_sorted(ar, len);

    int check[4] = {2, 4, 6, 7};
    for (int i = 0; i < 4; ++i) {
        ASSERT_EQ(check[i], ar[i]);
    }

    delete[] ar;

}


TEST(MakeSortedTests, SimpleSortAverageArray) {
    /*
     * Check that we can sort an array where the elements in it are in random order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int len = 4;
    int* ar = new int[len]{4, 2, 7, 6};
    make_sorted(ar, len);

    int check[4] = {2, 4, 6, 7};
    for (int i = 0; i < 4; ++i) {
        ASSERT_EQ(check[i], ar[i]);
    }

    delete[] ar;
}

TEST(MakeSortedTests, SimpleSortArrayWithDuplicates) {
    /*
     * Check that we can sort an array where there are duplicate elements in it.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int len = 4;
    int* ar = new int[len]{4, 2, 4, 6};
    make_sorted(ar, len);

    int check[4] = {2, 4, 4, 6};
    for (int i = 0; i < 4; ++i) {
        ASSERT_EQ(check[i], ar[i]);
    }

    delete[] ar;
}

RC_GTEST_PROP(MakeSortedTests,
              PropertyAfterSortingValuesAreInAscendingOrder,
              ( std::vector<int> values)
) {
    /* Test that after sorting an array, the values are in ascending order
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int len = values.size();
    int* ar = new int[len];

    for (int i = 0; i < len; ++i) {
        ar[i] = values[i];
    }
    make_sorted(ar, len);

    for (int i = 1; i < len; ++i) {
        RC_ASSERT(ar[i - 1] <= ar[i]);
    }
    delete[] ar;
}

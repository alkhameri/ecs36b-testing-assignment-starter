#include <cstdlib>
#include "gtest/gtest.h"
#include "sorting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

TEST(GetSortedTests, SimpleSortSortedArray) {
    /*
     * Check that we can sort an array that is already sorted.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int len = 4;
    int* ar = new int[len]{2, 4, 6, 7};
    int* sorted = get_sorted(ar, len);

    int check[4] = {2, 4, 6, 7};
    for (int i = 0; i < len; ++i) {
        ASSERT_EQ(sorted[i], check[i]);
    }

    delete[] ar;
    delete[] sorted;
}

TEST(GetSortedTests, SimpleSortReverseSortedArray) {
    /*
     * Check that we can sort an array that is reverse sorted order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int len = 4;
    int* ar = new int[len]{7, 6, 4, 2};
    int* sorted = get_sorted(ar, len);

    int check[4] = {2, 4, 6, 7};
    for (int i = 0; i < len; ++i) {
        ASSERT_EQ(sorted[i], check[i]);
    }

    delete[] ar;
    delete[] sorted;
}

TEST(GetSortedTests, SimpleSortAverageArray) {
    /*
     * Check that we can sort an array where the elements in it are in random order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int len = 4;
    int* ar = new int[len]{4, 2, 7, 6};
    int* sorted = get_sorted(ar, len);

    int check[4] = {2, 4, 6, 7};
    for (int i = 0; i < len; ++i) {
        ASSERT_EQ(sorted[i], check[i]);
    }

    delete[] ar;
    delete[] sorted;
}

TEST(GetSortedTests, SimpleSortArrayWithDuplicates) {
    /*
     * Check that we can sort an array where there are duplicate elements in it.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int len = 4;
    int* ar = new int[len]{4, 2, 4, 6};
    int* sorted = get_sorted(ar, len);

    int check[4] = {2, 4, 4, 6};
    for (int i = 0; i < len; ++i) {
        ASSERT_EQ(sorted[i], check[i]);
    }

    delete[] ar;
    delete[] sorted;
}

TEST(GetSortedTests, SimpleOriginalDoesNotChange) {
    /*
     * Check that the original array was not modified.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int len = 4;
    int* ar = new int[len]{4, 2, 7, 6};
    int check[4] = {4, 2, 7, 6};
    int* sorted = get_sorted(ar, len);

    for (int i = 0; i < len; ++i) {
        ASSERT_EQ(ar[i], check[i]);
    }

    delete[] ar;
    delete[] sorted;
}

TEST(GetSortedTests, SimpleCopyWasMade) {
    /*
     * Check that the sorted array is copy of the original array in sorted order.
     * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int len = 4;
    int* ar = new int[len]{4, 2, 7, 6};
    int* sorted = get_sorted(ar, len);

    ASSERT_NE(ar, sorted);
    for (int i = 0; i < len; ++i) {
        ASSERT_NE(&ar[i], &sorted[i]);
    }

    delete[] ar;
    delete[] sorted;
}


RC_GTEST_PROP(GetSortedTests,
              PropertyAfterSortingValuesAreInAscendingOrder,
              ( std::vector<int> values)
) {
    /* Check that after sorting an array, the values are in ascending order
     * Don't forget to free any memory that was dynamically allocated as part of this test
     */
    int len = values.size();
    int* ar = new int[len];
    for (int i = 0; i < len; ++i) {
        ar[i] = values[i];
    }

    int* sorted = get_sorted(ar, len);

    for (int i = 1; i < len; ++i) {
        RC_ASSERT(sorted[i - 1] <= sorted[i]);
    }

    delete[] ar;
    delete[] sorted;
}

RC_GTEST_PROP(GetSortedTests,
              PropertyOriginalDoesNotChange,
              (const std::vector<int>&values)
) {
    /*
     * Check that the original array was not modified.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int len = values.size();
    int* ar = new int[len];
    for (int i = 0; i < len; ++i) {
        ar[i] = values[i];
    }

    int* sorted = get_sorted(ar, len);

    for (int i = 0; i < len; ++i) {
        RC_ASSERT(ar[i] == values[i]);
    }

    delete[] ar;
    delete[] sorted;
}

RC_GTEST_PROP(GetSortedTests,
              PropertyCopyWasMade,
              (const std::vector<int>&values)
) {
    /*
     * Check that the sorted array is copy of the original array in sorted order.
     * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    RC_PRE(!values.empty());
    int len = values.size();
    int* ar = new int[len];
    for (int i = 0; i < len; ++i) {
        ar[i] = values[i];
    }

    int* sorted = get_sorted(ar, len);

    RC_ASSERT(ar != sorted);
    for (int i = 0; i < len; ++i) {
        RC_ASSERT(&ar[i] != &sorted[i]);
    }

    delete[] ar;
    delete[] sorted;
}












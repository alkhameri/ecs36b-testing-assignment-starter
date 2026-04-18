#include <cstdlib>
#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "sorting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

TEST(CopyArrayTests, SimpleValuesAreSame) {
    /*
     * Check that the values in the copy are the same as the values in the original array.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int len = 7;
    int* ar = new int[len]{1, 3, 4, 5, 5, 3, 7};
    int* ar_copy = copy_array(ar, len);

    for (int i = 0; i < len; ++i) {
        ASSERT_EQ(ar[i], ar_copy[i]);
    }

    delete[] ar;
    delete[] ar_copy;

}

TEST(CopyArrayTests, SimpleOriginalDoesNotChange) {
    /*
     * Check that the  values in the original array did not change.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int len = 7;
    int* ar = new int[len]{1, 3, 4, 5, 5, 3, 7};

    int* ar_copy = copy_array(ar, len);
    ar_copy[0] = ar_copy[0] + 1;
    int check[7] = {1, 3, 4, 5, 5, 3, 7};

    for (int i = 0; i < len; ++i) {
        ASSERT_EQ(ar[i], check[i]);
    }


    delete[] ar;
    delete[] ar_copy;
}


TEST(CopyArrayTests, SimpleCopyWasMade) {
    /*
     * Check that a copy was actually made
     * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int len = 7;
    int* ar = new int[len]{1, 3, 4, 5, 5, 3, 7};
    int* ar_copy = copy_array(ar, len);

    EXPECT_NE(ar_copy, ar);
    for (int i = 0; i < len; ++i) {
        ASSERT_NE(&ar[i], &ar_copy[i]);
    }

    delete[] ar;
    delete[] ar_copy;


}


RC_GTEST_PROP(CopyArrayTests,
              PropertyValuesAreSame,
              (const std::vector<int>& values)
) {
    /*
     * Check that the values in the copy are the same as the values in the original array.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int len = values.size();
    int* ar = new int[len];
    for (int i = 0; i < len; ++i) {
        ar[i] = values[i];
    }

    int* ar_copy = copy_array(ar, len);
    for (int i = 0; i < len; ++i) {
        RC_ASSERT(ar[i] == ar_copy[i]);
    }

    delete[] ar;
    delete[] ar_copy;

}

RC_GTEST_PROP(CopyArrayTests,
              PropertyOriginalDoesNotChange,
              (const std::vector<int>&values)
) {
    /*
     * Check that the  values in the original array did not change.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int len = values.size();
    int* ar = new int[len];

    for (int i = 0; i < len; ++i) {
        ar[i] = values[i];
    }

    int* ar_copy = copy_array(ar, len);

    if (len>0) {
        ar_copy[0] = ar_copy[0] +1;
    }

    for (int i = 0; i < len; ++i) {
        RC_ASSERT(ar[i] == values[i]);
    }

    delete[] ar;
    delete[] ar_copy;
}



RC_GTEST_PROP(CopyArrayTests,
              PropertyCopyWasMade,
              (const std::vector<int>&values)
) {
    /*
  * Check that a copy was actually made
  * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
  * Don't forget to free any memory that was dynamically allocated as part of your test.
  */

    int len = values.size();
    int* ar = new int[len];

    for (int i = 0; i < len; ++i) {
        ar[i] = values[i];
    }

    int* ar_copy = copy_array(ar, len);
    RC_PRE(!values.empty());
    RC_ASSERT(ar_copy[0] == ar[0]);

    for (int i = 0; i < len; ++i) {
        RC_ASSERT(ar[i] == ar_copy[i]);
    }
    delete[] ar;
    delete[] ar_copy;

}




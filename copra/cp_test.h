//
//  cp_test.h
//  simulator
//
//  Created by cHong on 2017/12/3.
//

#ifndef cp_test_h
#define cp_test_h

#include<vector>

namespace copra {
    class Test{
    public:
        static void staticTestFunc();
        Test();
        int getCount();
        void print();
        int getArrayLength(const std::vector<int>& list);
        
        int seq_id;
    };
}

#endif /* cp_test_h */

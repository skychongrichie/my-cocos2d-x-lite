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
    class TestDelegate{
    public:
        virtual void Fight()=0;
    };
    
    class Test{
    public:
        static void staticTestFunc();
        Test();
        int getCount();
        void print();
        void fight();
        void setDelegate(TestDelegate* delegate);
        int getArrayLength(const std::vector<int>& list);
        
        
        int seq_id;
    private:
        TestDelegate* delegate_;
    };
}

#endif /* cp_test_h */

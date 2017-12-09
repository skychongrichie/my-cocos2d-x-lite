//
//  cp_test.cpp
//  simulator
//
//  Created by cHong on 2017/12/3.
//

#include <stdio.h>
#include "cocos2d.h"
#include "cp_test.h"

using namespace std;

namespace copra {
    Test::Test():seq_id(10){}
    
    void Test::staticTestFunc(){
        CCLOG("static function");
    }

    int Test::getCount(){
        return 3;
    }
    
    void Test::print(){
        CCLOG("hello world");
    }
    
    int Test::getArrayLength(const vector<int>& list){
        return static_cast<int>(list.size()) ;
    }
}

#pragma once

#include "serialization_cv.h"
#include "serialization_rv.h"
#include "serialization_qv.h"

/*
    序列化设计原则: 如非必要,优选选用非侵入式序列化方案;
    如果考虑到对数据的保护或者其他原因,方考虑侵入式序列化方案;

    而在本Library之中,考虑到方便Node的派生类的自动推导,以及对后续插件化自动加载技术的扩展,
        所有的Node的派生类都采用侵入式设计方案;
    同理,flowUnit也是选择侵入式方案;
    
    至于其他数据结构,选择在 serialization_qv.h 进行非侵入式定义;
*/
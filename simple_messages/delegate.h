#pragma once
// Original source [RU]: http://www.rsdn.ru/article/cpp/delegates.xml

#include <list>

#define SUFFIX          1
#define TEMPLATE_PARAMS , class TP1
#define TEMPLATE_ARGS   , TP1
#define PARAMS          TP1 p1
#define ARGS            p1

#include "delegate_impl.h"

#undef SUFFIX
#undef TEMPLATE_PARAMS
#undef TEMPLATE_ARGS
#undef PARAMS
#undef ARGS


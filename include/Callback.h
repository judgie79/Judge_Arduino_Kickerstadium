
#ifndef __CALLBACK_H
#define __CALLBACK_H

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <memory>
#include <vector>

template<class ... Arguments>
class Callback
{
    using Function = std::function<void(Arguments ...)>;
    using FunctionPtr = std::shared_ptr<Function>;
    using Functions = std::vector<FunctionPtr>;

public:

    FunctionPtr addListener(Function f) {
        FunctionPtr fp = std::make_shared<Function>(f);
        _functions.push_back(fp);
        return fp;
    }

    void removeListener(FunctionPtr fp){
        _functions.erase(std::find(_functions.begin(), _functions.end(), fp));
    }

    void operator()(Arguments ... args) const{
        for (auto & f : _functions)
            f.get()->operator()( args ... );
    }

private:
    Functions _functions;
};

#endif
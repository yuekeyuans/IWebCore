#pragma once

template<typename Ts>
struct IBeanTraitInterface
{
//    static constexpr bool IS_USE_EXCEPTION(){
//        if constexpr
//    }
};

struct IBeanDefaultTrait : public IBeanTraitInterface<IBeanDefaultTrait>
{

};

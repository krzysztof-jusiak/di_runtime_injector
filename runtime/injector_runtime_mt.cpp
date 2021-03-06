//
// Copyright (c) 2014 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//#include "boost/di/injector.hpp"
#include "boost/di/aux_/memory.hpp"
#include "common/data.hpp"
#include "runtime/injector.hpp"
#include <boost/mpl/string.hpp>

namespace boost {
namespace di {

void check(const c8& c8_) {
    //BOOST_CHECK(c8_.c1_ == c8_.c7_->c6_->c5_.c1_);
    //BOOST_CHECK(c8_.c7_->c6_->c4_->c3_ == c8_.c7_->c6_->c3_);
    //BOOST_CHECK(c8_.c7_->if0_ != c8_.c7_->c6_->c5_.if0_);

    //BOOST_CHECK(dynamic_cast<c1if0*>(c8_.c7_->c6_->c5_.if0_.get()));
    //BOOST_CHECK(dynamic_cast<c2if0*>(c8_.c7_->if0_.get()));

    //BOOST_CHECK_EQUAL(2, c8_.i);
    //BOOST_CHECK_EQUAL(3, c8_.c7_->c6_->c4_->i1);
    //BOOST_CHECK_EQUAL(4, c8_.c7_->c6_->c4_->i2);
    //BOOST_CHECK_EQUAL(1, c8_.c7_->c6_->c3_->i);
    //BOOST_CHECK_EQUAL(5, c8_.c7_->c6_->c5_.c2_->i);
    //BOOST_CHECK_EQUAL(0.0, c8_.c7_->c6_->c5_.c2_->d);
    //BOOST_CHECK_EQUAL(0, c8_.c7_->c6_->c5_.c2_->c);
}

} // namespace di
} // namespace boost

using namespace boost;
using namespace boost::di;

int main() {
    di::injector<> inj;

    inj.install(
        di::shared<
            c3
        >()
      , di::unique<
            //c0if0//!!! compile error
            di::bind<if0, c0if0>
          , di::bind<if0, c1if0>::when<di::call_stack<c6, c5>>
          , di::bind<if0, c2if0>::when<di::call_stack<c7>>
          , di::bind_int<1>
          , di::bind_int<2>::when<di::call_stack<c8>>
          , di::bind_int<3>::named<mpl::string<'1'>>::when<di::call_stack<c7, c6, c4>>
          , di::bind_int<4>::named<mpl::string<'2'>>::when<di::call_stack<c7, c6, c4>>
          , di::bind_int<5>::when<di::call_stack<c2>>
        >()
    );

    check(inj.create<c8>());
}


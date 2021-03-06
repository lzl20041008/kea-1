// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <string>
#include <ostream>

#include <gtest/gtest.h>

#include <exceptions/exceptions.h>

#include <dns/rcode.h>
#include <dns/tsigerror.h>

using namespace std;
using namespace isc;
using namespace isc::dns;

namespace {
TEST(TSIGErrorTest, constructFromErrorCode) {
    // These are pretty trivial, and also test getCode();
    EXPECT_EQ(0, TSIGError(0).getCode());
    EXPECT_EQ(18, TSIGError(18).getCode());
    EXPECT_EQ(65535, TSIGError(65535).getCode());
}

TEST(TSIGErrorTest, constructFromRcode) {
    // We use RCODE for code values from 0-15.
    EXPECT_EQ(0, TSIGError(Rcode::NOERROR()).getCode());
    EXPECT_EQ(15, TSIGError(Rcode(15)).getCode());

    // From error code 16 TSIG errors define a separate space, so passing
    // corresponding RCODE for such code values should be prohibited.
    EXPECT_THROW(TSIGError(Rcode(16)).getCode(), OutOfRange);
}

TEST(TSIGErrorTest, constants) {
    // We'll only test arbitrarily chosen subsets of the codes.
    // This class is quite simple, so it should be suffice.

    EXPECT_EQ(TSIGError::BAD_SIG_CODE, TSIGError(16).getCode());
    EXPECT_EQ(TSIGError::BAD_KEY_CODE, TSIGError(17).getCode());
    EXPECT_EQ(TSIGError::BAD_TIME_CODE, TSIGError(18).getCode());

    EXPECT_EQ(0, TSIGError::NOERROR().getCode());
    EXPECT_EQ(9, TSIGError::NOTAUTH().getCode());
    EXPECT_EQ(14, TSIGError::RESERVED14().getCode());
    EXPECT_EQ(TSIGError::BAD_SIG_CODE, TSIGError::BAD_SIG().getCode());
    EXPECT_EQ(TSIGError::BAD_KEY_CODE, TSIGError::BAD_KEY().getCode());
    EXPECT_EQ(TSIGError::BAD_TIME_CODE, TSIGError::BAD_TIME().getCode());
}

TEST(TSIGErrorTest, equal) {
    EXPECT_TRUE(TSIGError::NOERROR() == TSIGError(Rcode::NOERROR()));
    EXPECT_TRUE(TSIGError(Rcode::NOERROR()) == TSIGError::NOERROR());
    EXPECT_TRUE(TSIGError::NOERROR().equals(TSIGError(Rcode::NOERROR())));
    EXPECT_TRUE(TSIGError::NOERROR().equals(TSIGError(Rcode::NOERROR())));

    EXPECT_TRUE(TSIGError::BAD_SIG() == TSIGError(16));
    EXPECT_TRUE(TSIGError(16) == TSIGError::BAD_SIG());
    EXPECT_TRUE(TSIGError::BAD_SIG().equals(TSIGError(16)));
    EXPECT_TRUE(TSIGError(16).equals(TSIGError::BAD_SIG()));
}

TEST(TSIGErrorTest, nequal) {
    EXPECT_TRUE(TSIGError::BAD_KEY() != TSIGError(Rcode::NOERROR()));
    EXPECT_TRUE(TSIGError(Rcode::NOERROR()) != TSIGError::BAD_KEY());
    EXPECT_TRUE(TSIGError::BAD_KEY().nequals(TSIGError(Rcode::NOERROR())));
    EXPECT_TRUE(TSIGError(Rcode::NOERROR()).nequals(TSIGError::BAD_KEY()));
}

TEST(TSIGErrorTest, toText) {
    // TSIGError derived from the standard Rcode
    EXPECT_EQ("NOERROR", TSIGError(Rcode::NOERROR()).toText());

    // Well known TSIG errors
    EXPECT_EQ("BADSIG", TSIGError::BAD_SIG().toText());
    EXPECT_EQ("BADKEY", TSIGError::BAD_KEY().toText());
    EXPECT_EQ("BADTIME", TSIGError::BAD_TIME().toText());

    // Unknown (or not yet supported) codes.  Simply converted as numeric.
    EXPECT_EQ("19", TSIGError(19).toText());
    EXPECT_EQ("65535", TSIGError(65535).toText());
}

TEST(TSIGErrorTest, toRcode) {
    // TSIGError derived from the standard Rcode
    EXPECT_EQ(Rcode::NOERROR(), TSIGError(Rcode::NOERROR()).toRcode());

    // Well known TSIG errors
    EXPECT_EQ(Rcode::NOTAUTH(), TSIGError::BAD_SIG().toRcode());
    EXPECT_EQ(Rcode::NOTAUTH(), TSIGError::BAD_KEY().toRcode());
    EXPECT_EQ(Rcode::NOTAUTH(), TSIGError::BAD_TIME().toRcode());

    // Unknown (or not yet supported) codes are treated as SERVFAIL.
    EXPECT_EQ(Rcode::SERVFAIL(), TSIGError(19).toRcode());
    EXPECT_EQ(Rcode::SERVFAIL(), TSIGError(65535).toRcode());
}

// test operator<<.  We simply confirm it appends the result of toText().
TEST(TSIGErrorTest, LeftShiftOperator) {
    ostringstream oss;
    oss << TSIGError::BAD_KEY();
    EXPECT_EQ(TSIGError::BAD_KEY().toText(), oss.str());
}
} // end namespace

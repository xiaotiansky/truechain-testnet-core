//------------------------------------------------------------------------------
/*
    This file is part of skywelld: https://github.com/skywell/skywelld
    Copyright (c) 2015 Skywell Labs Inc.

    Permission to use, copy, modify, and/or distribute this software for any
    purpose  with  or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.

    THE  SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH  REGARD  TO  THIS  SOFTWARE  INCLUDING  ALL  IMPLIED  WARRANTIES  OF
    MERCHANTABILITY  AND  FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY  SPECIAL ,  DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER  RESULTING  FROM  LOSS  OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION  OF  CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================

#ifndef SKYWELL_SHAMAP_FAMILY_H_INCLUDED
#define SKYWELL_SHAMAP_FAMILY_H_INCLUDED

#include <cstdint>
#include <common/shamap/FullBelowCache.h>
#include <common/shamap/TreeNodeCache.h>
#include <data/nodestore/Database.h>

namespace truechain {
namespace shamap {

class Family
{
public:
    virtual ~Family() = default;

    virtual
    FullBelowCache&
    fullbelow() = 0;

    virtual
    FullBelowCache const&
    fullbelow() const = 0;

    virtual
    TreeNodeCache&
    treecache() = 0;

    virtual
    TreeNodeCache const&
    treecache() const = 0;

    virtual
    NodeStore::Database&
    db() = 0;

    virtual
    NodeStore::Database const&
    db() const = 0;

    virtual
    void
    missing_node (std::uint32_t refNum) = 0;
};

} // shamap
} // truechain

#endif

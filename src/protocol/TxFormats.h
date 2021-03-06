//------------------------------------------------------------------------------
/*
	Copyright (c) 2012, 2013 Skywell Labs Inc.
	Copyright (c) 2017-2018 TrueChain Foundation.

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

#ifndef SKYWELL_PROTOCOL_TXFORMATS_H_INCLUDED
#define SKYWELL_PROTOCOL_TXFORMATS_H_INCLUDED

#include <protocol/KnownFormats.h>

namespace truechain {

/** Transaction type identifiers.

    These are part of the binary message format.

    @ingroup protocol
*/
enum TxType
{
    ttINVALID           = -1,

    ttPAYMENT           = 0,
    ttCLAIM             = 1, // open
    ttWALLET_ADD        = 2, // unused
    ttACCOUNT_SET       = 3,
    ttPASSWORD_FUND     = 4, // open
    ttREGULAR_KEY_SET   = 5,
    ttNICKNAME_SET      = 6, // open
    ttOFFER_CREATE      = 7,
    ttOFFER_CANCEL      = 8,
    no_longer_used      = 9,
    ttTICKET_CREATE     = 10,
    ttTICKET_CANCEL     = 11,
    ttACCOUNT_MERGE     = 12,

    ttTRUST_SET         = 20,
    ttREL_SET           = 21,
    ttREL_DEL           = 22,

    ttAMENDMENT         = 100,
    ttFEE               = 101,
    
    ttMNGFEE            = 200,
    ttBLKLISTSET        = 201,
    ttBLKLISTRMV        = 202,
    ttMNGISSUER         = 203,

    ttOPERATION         = 300,

	ttSIGN_SET          = 400,
    
    ttMESSAGE           = 500,
};

/** Manages the list of known transaction formats.
*/
class TxFormats : public KnownFormats <TxType>
{
private:
    void addCommonFields (Item& item);

public:
    /** Create the object.
        This will load the object will all the known transaction formats.
    */
    TxFormats ();

    static TxFormats const& getInstance ();
};

} // truechain

#endif

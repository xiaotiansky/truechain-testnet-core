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

#ifndef SKYWELL_NET_INFOSUB_H_INCLUDED
#define SKYWELL_NET_INFOSUB_H_INCLUDED

#include <common/base/CountedObject.h>
#include <common/json/json_value.h>
#include <protocol/SkywellAddress.h>
#include <protocol/Book.h>
#include <network/resource/Consumer.h>
#include <beast/threads/Stoppable.h>
#include <mutex>

namespace truechain {

// Operations that clients may wish to perform against the network
// Master operational handler, server sequencer, network tracker

class PathRequest;

/** Manages a client's subscription to data feeds.
*/
class InfoSub
    : public CountedObject <InfoSub>
{
public:
    static char const* getCountedObjectName () { return "InfoSub"; }

    typedef std::shared_ptr<InfoSub>          pointer;

    //  TODO Standardize on the names of weak / strong pointer typedefs.
    typedef std::weak_ptr<InfoSub>            wptr;

    typedef const std::shared_ptr<InfoSub>&   ref;

    typedef Resource::Consumer Consumer;

public:
    /** Abstracts the source of subscription data.
    */
    class Source : public beast::Stoppable
    {
    protected:
        Source (char const* name, beast::Stoppable& parent);

    public:

        // For some reason, these were originally called "rt"
        // for "real time". They actually refer to whether
        // you get transactions as they occur or once their
        // results are confirmed
        virtual void subAccount (ref ispListener,
            const hash_set<SkywellAddress>& vnaAccountIDs,
            bool realTime) = 0;

        // for normal use, removes from InfoSub and server
        virtual void unsubAccount (ref isplistener,
            const hash_set<SkywellAddress>& vnaAccountIDs,
            bool realTime) = 0;

        // for use during InfoSub destruction
        // Removes only from the server
        virtual void unsubAccountInternal (std::uint64_t uListener,
            const hash_set<SkywellAddress>& vnaAccountIDs,
            bool realTime) = 0;

        //  TODO Document the bool return value
        virtual bool subLedger (ref ispListener, Json::Value& jvResult) = 0;
        virtual bool unsubLedger (std::uint64_t uListener) = 0;

        virtual bool subServer (ref ispListener, Json::Value& jvResult,
            bool admin) = 0;
        virtual bool unsubServer (std::uint64_t uListener) = 0;

        virtual bool subBook (ref ispListener, Book const&) = 0;
        virtual bool unsubBook (std::uint64_t uListener, Book const&) = 0;

        virtual bool subTransactions (ref ispListener) = 0;
        virtual bool unsubTransactions (std::uint64_t uListener) = 0;

        virtual bool subRTTransactions (ref ispListener) = 0;
        virtual bool unsubRTTransactions (std::uint64_t uListener) = 0;

        //  TODO Remove
        //             This was added for one particular partner, it
        //             "pushes" subscription data to a particular URL.
        //
        virtual pointer findRpcSub (std::string const& strUrl) = 0;
        virtual pointer addRpcSub (std::string const& strUrl, ref rspEntry) = 0;
    };

public:
    InfoSub (Source& source, Consumer consumer);

    virtual ~InfoSub ();

    Consumer& getConsumer();

    virtual void send (Json::Value const& jvObj, bool broadcast) = 0;

    // virtual so that a derived class can optimize this case
    virtual void send (
        Json::Value const& jvObj, std::string const& sObj, bool broadcast);

    std::uint64_t getSeq ();

    void onSendEmpty ();

    void insertSubAccountInfo (
        SkywellAddress addr,
        bool rt);

    void deleteSubAccountInfo (
        SkywellAddress addr,
        bool rt);

    void clearPathRequest ();

    void setPathRequest (const std::shared_ptr<PathRequest>& req);

    std::shared_ptr <PathRequest> const& getPathRequest ();

protected:
    typedef std::mutex LockType;
    typedef std::lock_guard <LockType> ScopedLockType;
    LockType mLock;

private:
    Consumer                      m_consumer;
    Source&                       m_source;
    hash_set <SkywellAddress>      mSubAccountInfo_t; // real time subscriptions
    hash_set <SkywellAddress>      mSubAccountInfo_f; // normal subscriptions
    hash_set <SkywellAddress>      mSubAccountTransaction;
    std::shared_ptr <PathRequest> mPathRequest;
    std::uint64_t                 mSeq;
};

} // truechain

#endif

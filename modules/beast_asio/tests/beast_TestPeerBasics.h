//------------------------------------------------------------------------------
/*
    This file is part of Beast: https://github.com/vinniefalco/Beast
    Copyright 2013, Vinnie Falco <vinnie.falco@gmail.com>

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

#ifndef BEAST_TESTPEERBASICS_H_INCLUDED
#define BEAST_TESTPEERBASICS_H_INCLUDED

/** Common declarations for TestPeer.

    @see TestPeer
*/
class TestPeerBasics
{
public:
    /** Identifies if the peer is a client or a server. */
    struct Role
    {
        enum role_t
        {
            client,
            server
        };

        Role (role_t role);
        String name () const noexcept;
        bool operator== (role_t role) const noexcept;
        operator Socket::handshake_type () const noexcept;

    private:
        role_t m_role;
    };

    //--------------------------------------------------------------------------

    /** Selects between synchronous or asynchronous networking i/o usage. */
    struct Model
    {
        enum model_t
        {
            sync,
            async
        };

        Model (model_t model);
        String name () const noexcept;
        bool operator== (model_t model) const noexcept;

    private:
        model_t m_model;
    };

    //--------------------------------------------------------------------------

    // Custom error codes for distinguishing test conditions
    struct errc
    {
        enum errc_t
        {
            none = 0,
            timeout,        // The peer join timeout expired
            unexpected,     // An expected condition was false
            exceptioned,    // An exception occurred
            skipped         // Test skipped due to previous errors
        };
    };

    /** Returns the category that represents TestPeer errors.
    */
    static boost::system::error_category const& test_category () noexcept;

    /** Creates a test error_code from the give code value.
    */
    static boost::system::error_code make_error (errc::errc_t ev) noexcept;

    /** Sets the passed error_code to a test error and returns it.
    */
    static boost::system::error_code make_error (errc::errc_t ev,
        boost::system::error_code& ec) noexcept;

    /** Returns true if the error code indicates success.
    */
    static bool success (boost::system::error_code const& ec, bool eofIsOkay = false) noexcept;

    /** Returns false if the error code indicates failure.
    */
    static bool failure (boost::system::error_code const& ec, bool eofIsOkay = false) noexcept;

    /** Set the error based on a failed condition and return the success.
    */
    static bool expected (bool condition, boost::system::error_code& ec) noexcept;

    /** Set the error based on a passed condition and return the success.
    */
    static bool unexpected (bool condition, boost::system::error_code& ec) noexcept;
};

#endif

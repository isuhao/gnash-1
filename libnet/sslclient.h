// 
//   Copyright (C) 2007, 2008, 2009 Free Software Foundation, Inc.
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//

#ifndef GNASH_LIBNET_SSL_H
#define GNASH_LIBNET_SSL_H

#ifdef HAVE_CONFIG_H
#include "gnashconfig.h"
#endif

#include <string>
#include <boost/array.hpp>
#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/scoped_array.hpp>
#include <boost/cstdint.hpp>
#include <sstream>

#ifdef HAVE_OPENSSL_SSL_H
#include <openssl/ssl.h>
#include <openssl/err.h>
#endif

#include "cque.h"
#include "network.h"
#include "buffer.h"

namespace gnash
{

const char *ROOTPATH = "/etc/pki/tls";
const char *HOST    = "localhost";
const char *CA_LIST = "root.pem";
const char *RANDOM  = "random.pem";
const char *KEYFILE  = "client.pem";
const size_t SSL_PASSWD_SIZE = 1024;

class DSOEXPORT SSLClient : public gnash::Network
{
public:
    SSLClient();
    ~SSLClient();

    // Read bytes from the already opened SSL connection
    int sslRead(amf::Buffer &buf);
    int sslRead(boost::uint8_t *buf, size_t length);
    int sslRead(std::string &buf);

    // Write bytes to the already opened SSL connection
    int sslWrite(amf::Buffer &buf);
    int sslWrite(boost::uint8_t *buf, size_t length);
    int sslWrite(std::string &buf);

    // Setup the Context for this connection
    bool sslSetupCTX();
    bool sslSetupCTX(std::string &keyfile, std::string &cafile);
    
    // Shutdown the Context for this connection
    bool sslShutdown();

    // sslConnect() is how the client connects to the server 
    bool sslConnect();
    bool sslConnect(std::string &hostname);

    // sslAccept() is how the server waits for connections for clients
    size_t sslAccept();

    void setKeyfile(std::string filespec) { _keyfile = filespec; };
    std::string &getKeyfile() { return _keyfile; };
    
    void setCAlist(std::string filespec) { _calist = filespec; };
    std::string &getCAlist() { return _calist; };
    
    void setPassword(std::string pw);
    std::string &getPassword();
    
    void setCert(std::string filespec) { _cert = filespec; };
    std::string &getCert() { return _cert; };
    
    void setRootPath(std::string filespec) { _rootpath = filespec; };
    std::string &getRootPath() { return _rootpath; };
    
    void setPem(std::string filespec) { _pem = filespec; };
    std::string &getPem() { return _pem; };
    
    void setHostname(std::string name) { _hostname = name; };
    std::string &getHostname() { return _hostname; };
    
    void setServerAuth(bool flag) { _need_server_auth = flag; };
    bool getServerAuth() { return _need_server_auth; };
    
    // Check a certificate
    bool checkCert();
    bool checkCert(std::string &hostname);

    void dump();
 private:
    boost::scoped_ptr<SSL> _ssl;
    boost::scoped_ptr<SSL_CTX> _ctx;
    boost::scoped_ptr<BIO> _bio;
    boost::scoped_ptr<BIO> _bio_error;
    std::string		_hostname;
    std::string		_calist;
    std::string		_keyfile;
    std::string		_cert;
    std::string		_pem;
    std::string		_rootpath;
    bool		_need_server_auth;
};

extern "C" {
    // This is the callback required when setting up the password
    int password_cb(char *buf, int size, int rwflag, void *userdata);
}


} // end of gnash namespace

// end of _SSL_H_
#endif


// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:

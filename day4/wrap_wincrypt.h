#pragma once

#include <windows.h>
#include <Wincrypt.h>
#include "include/thrower.h"


namespace WinCrypt
{

struct Provider
{
    Provider()
    {
        if (!CryptAcquireContext(&provider,NULL,NULL,PROV_RSA_FULL,CRYPT_VERIFYCONTEXT))
        {
            throw_system_error("CryptAcquireContext");
        }
    }

    ~Provider()
    {
        CryptReleaseContext(provider,0);
    }

    operator HCRYPTPROV() const
    {
        return provider;
    }

private:    
    HCRYPTPROV provider;
};


struct Hash
{
    Hash()
    {
        if(!CryptCreateHash(provider, CALG_MD5, 0, 0, &hash))
        {
            throw_system_error("CryptCreateHash");
        }
    }

    ~Hash()
    {
        CryptDestroyHash(hash);
    }

    operator HCRYPTHASH ()
    {
        return hash;
    }


    void append(std::string const &s)
    {
        if (!CryptHashData(hash, reinterpret_cast<BYTE const *>(s.data()), static_cast<DWORD>(s.size()), 0))
        {
            throw_system_error("CryptHashData");
        }
    }

    std::string digest()
    {
        std::array<BYTE,16> bytes{};
        auto                read=static_cast<DWORD>(bytes.size());

        if (!CryptGetHashParam(hash, HP_HASHVAL, bytes.data(), &read, 0))
        {
            throw_system_error("CryptGetHashParam");
        }

        std::string  digest;

        for(auto b : bytes)
        {
            digest+= std::format("{:02x}",b);
        }

        return digest;
    }


private:    
    
    static inline Provider provider;

    HCRYPTHASH  hash;
};



}

#pragma once
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <array>

constexpr std::size_t IPv4_SIZE = 4;
constexpr std::size_t IPv6_SIZE = 16;

template <std::size_t Ver>
class IP {
    private:

    char c;
    uint16_t u;
    using Type = decltype(Ver == IPv4_SIZE ? c : u);
    std::array<Type, Ver> addr;

    public:
    IP() = delete;

    IP(char ip_address_string[])
    {
        if constexpr (Ver == IPv4_SIZE) {

            if (strlen(ip_address_string) == IPv4_SIZE)
            {
                for (size_t i = 0; i < addr.size(); ++i) {
                    addr.at(i) = ip_address_string[i];
                }
            } else {
                //throw std::invalid_argument( "Invalid IPv4 address: ", ip_address_string);
                std::cerr << "Invalid IPv4 address";
                if (strlen(ip_address_string) < 256) std::cerr << " : " << ip_address_string;
                std::cerr << "\n";
            }            
        } 

        if constexpr (Ver == IPv6_SIZE) {
            if (strlen(ip_address_string) == IPv6_SIZE)
            {
                for (size_t i = 0; i < addr.size() / 2; ++i) {
                    addr.at(i) = (ip_address_string[2 * i] << 8) & ip_address_string[2 * i + 1];
                }
            } else {
                //throw std::invalid_argument( "Invalid IPv6 address: ", ip_address_string);
                std::cerr << "Invalid IPv6 address";
                if (strlen(ip_address_string) < 256) std::cerr << " : " << ip_address_string;
                std::cerr << "\n";
            }            
        }        
    }

    IP(std::vector<std::string> ip_strings)
    {
        if constexpr (Ver == IPv4_SIZE)
        {

            if (ip_strings.size() == IPv4_SIZE)
            {
                for (size_t i = 0; i < IPv4_SIZE; ++i)
                {
                    int ip_part = std::stoi(ip_strings.at(i));

                    if (!(ip_part >= 0 && ip_part < 256)) {
                        throw std::invalid_argument("Invalid IPv4 address part");
                    }

                    addr.at(i) = ip_part;
                }
            } 
            else 
            {
                //throw std::invalid_argument( "Invalid IP address: ", ip_address_string);
                std::cerr << "Invalid IPv4 address";            
                std::cerr << "\n";

            }            
        } 
        else if constexpr (Ver == IPv6_SIZE) 
        {
            if (ip_strings.size() <= IPv6_SIZE)
            {
                for (size_t i = IPv6_SIZE - 1; i >= 0; --i)
                {
                    int ip_part;

                    if (ip_strings.at(i).empty() || i > ip_strings.size() - 1)
                    {
                        ip_part = 0;
                    } 
                    else
                    {
                        ip_part = std::stoi(ip_strings.at(i), nullptr, 16);                
                    }

                    if (!(ip_part >= 0 && ip_part < 65536)) {
                        throw std::invalid_argument( "Invalid IPv6 address part");
                    }
                    
                    addr.at(i) = ip_part;
                }
            }
            else 
            {
                //throw std::invalid_argument( "Invalid IP address: ", ip_address_string);
                std::cerr << "Invalid IPv6 address";            
                std::cerr << "\n";
            }                                    
        }        
    }

    std::size_t getVersion()
    {
        return addr.size();
    }

    template<typename R = Type>
    std::array<R, Ver> getAddr() const
    {
        return addr;
    }

    template<typename R = Type>
    bool operator < (const IP& b) const
    {
        std::array<R, Ver> other_addr = b.getAddr();

        for (auto it = std::make_pair(addr.begin(), other_addr.begin()); it.first != addr.end(); ++it.first, ++it.second)
        {
            if (*it.first < *it.second)
            {
                return true;
            } else if ((*it.first > *it.second)) {
                return false;
            }
        }

        return true;
    }

    template<typename R = Type>    
    bool reverse_less_then(const IP& b) const
    {
        std::array<R, Ver> other_addr = b.getAddr();

        for (auto it = std::make_pair(addr.begin(), other_addr.begin()); it.first != addr.end(); ++it.first, ++it.second)
        {
            if (*it.first > *it.second)
            {
                return true;
            } else if (*it.first < *it.second) {
                return false;
            }
        }

        return true;
    }

    template<typename R = Type>
    bool comparePart(std::size_t N, Type part)
    {
        if (N < Ver)
        {
            if (addr.at(N) == part) return true;
            else return false;
        }
        else
        {
            throw std::invalid_argument( "Invalid address part position");
        }
    }

    template<typename R = Type>
    bool comparePart(Type part)
    {
        for (std::size_t i = 0; i < Ver; ++i)
        {
            if (addr.at(i) == part) return true;
        }

        return false;

    }    

    template<typename R = Type>
    Type getPart(size_t N)
    {
        if (N < Ver)
        {
            return addr.at(N);
        }            
        else
        {
            throw std::invalid_argument( "Invalid address part position");
        }
        
    }
};
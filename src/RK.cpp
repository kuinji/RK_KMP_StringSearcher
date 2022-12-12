#include <string>
#include <vector>
#include <iostream>

#include <chrono>

class RabinKarp
{
    const std::string& text;
    const std::string& substring;
    size_t alphabetSize = 256;
    size_t mod = 10007;
    int h;
public:
    RabinKarp(const std::string& _text, const std::string& _substring, size_t _alphabetSize = 256) :
        text(_text), substring(_substring), alphabetSize(_alphabetSize)
    {
        hInit();
    }


    std::vector<int> search()
    {
        if (text.length() < substring.length()) return std::vector<int>(-1);

        size_t strLen = substring.length();
        size_t textLen = text.length();

        int strHash = initHash(substring);
        int textHash = initHash(text);

        std::vector<int> searchIndxs;

        for (int k = 0; k <= (textLen - strLen); k++)
        {
            if (strHash == textHash)
                if(compareText(text, k))
                    searchIndxs.push_back(k);

            if (k == (textLen - strLen))
                break;

            textHash = ringHash(text, textHash, k);
        }

        return searchIndxs;
    }
private:
    void hInit()
    {
        h = 1;
        for (int i = 1; i < substring.length(); i++)
            h = (h * alphabetSize) % mod;
    }

    int initHash(const std::string& str)
    {
        int hash = (int)str[0] % mod;
        for (int i = 1; i < substring.length(); i++)
        {
            hash = (alphabetSize * hash + (int)str[i]) % mod;
        }
        return hash;
    }
    int ringHash(const std::string& str, int prevHash, int offset)
    {
        int hash = ((prevHash - (((int)str[offset] * h) % mod) + mod) *
                     alphabetSize + (int)str[offset + substring.length()]) % mod;

        return hash;

    }

    bool compareText(const std::string& text, size_t k)
    {
        for (int i = 0; i < substring.length(); i++)
            if (substring[i] != text[k + i])
                return false;

        return true;
    }
};

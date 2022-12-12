#include <string>
#include <vector>

class KMP
{
    const std::string& text;
    const std::string& substring;

public:
    KMP(const std::string& _text, const std::string& _substring) :
        text(_text), substring(_substring)
    { }

    std::vector<int> search()
    {
        std::vector<int> pref = prefix(substring);
        std::vector<int> searchIndxs;
        for (int i = 0, j = 0; i < text.length(); i++)
        {
            if (text[i] == substring[j])
            {
                if (++j == substring.length()) {
                    searchIndxs.push_back(i - j + 1);
                }
            }
            else if (j > 0)
            {
                j = pref[j - 1];
                i--;
            }
        }
        return searchIndxs;
    }

private:
    std::vector<int> prefix(const std::string& string)
    {
        std::vector<int> res = std::vector<int>(string.length(), 0);

        for (int i = 1; i < string.length(); i++)
        {
            int j = res[i - 1];

            while (j > 0 && string[j] != string[i])
                j = res[j - 1];

            if (string[j] == string[i])
                res[i] = j + 1;
            else
                res[i] = j;
        }
        return res;
    }
};
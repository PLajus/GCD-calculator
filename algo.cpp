#include <iostream>
#include <string>
#include <algorithm>

bool string1_is_smaller(std::string s1, std::string s2)
{
    int len_s1 = s1.length();
    int len_s2 = s2.length();

    if (len_s1 < len_s2)
        return true;
    if (len_s1 > len_s2)
        return false;

    // Tikrina po stringo chara, jei bent vienas charas didesnis ir ilgiai vienodi, vadinasi tas stringas didesnis
    for (int i = 0; i < len_s1; i++)
    {
        if (s1[i] < s2[i])
            return true;
        else if (s1[i] > s2[i])
            return false;
    }
    return false;
}

std::string string_diff(std::string s1, std::string s2)
{
    std::string sub_res = ""; // Naudojamas saugoti atimties rezultatui
    int carry = 0;
    int diff_in_length = s1.length() - s2.length();

    // Is galo atimineti s1-s2 stulpeliu
    for (int i = s2.length() - 1; i >= 0; i--)
    {
        int subtracted = ((s1[i + diff_in_length] - '0') - (s2[i] - '0') - carry);
        if (subtracted < 0)
        {
            subtracted += 10;
            carry = 1;
        }
        else
            carry = 0;

        sub_res.push_back(subtracted + '0');
    }
    // Iraso likusius ilgesnio stringo elementus
    for (int i = s1.length() - s2.length() - 1; i >= 0; i--)
    {
        if (s1[i] == '0' && carry)
        {
            sub_res.push_back('9');
            continue;
        }
        int subtracted = ((s1[i] - '0') - carry);
        sub_res.push_back(subtracted + '0');
        carry = 0;
    }
    reverse(sub_res.begin(), sub_res.end());
    if (sub_res.length() >= 2)
        sub_res.erase(0, sub_res.find_first_not_of('0'));
    return sub_res;
}

std::string string_div_by2(std::string num)
{
    std::string div_ans = "";

    // Dideli skaiciu dalina dalimis, dalybos stulpeliu principu
    int iter = 0;
    int part_to_divide = num[0] - '0';

    // Gauti pirmus skaitmenis kuries butu galima dalinti is 2
    while (2 > part_to_divide)
    {
        iter++;
        part_to_divide = part_to_divide * 10 + (num[iter] - '0');
    }
    // Dalina kol praeina per visa skaiciu
    while (num.size() > iter)
    {
        iter++;
        div_ans += (part_to_divide / 2) + '0';
        part_to_divide = (part_to_divide % 2) * 10 + num[iter] - '0'; // Ima kita sk. (part_to_divide % 2) - gauti liekana
    }
    if (div_ans.length() == 0)
        return "0";
    return div_ans;
}

std::string string_mul_by2(std::string num)
{
    std::string mul_res = "";
    int carry = 0;
    // Daugina stulpelio principu
    for (int i = num.length() - 1; i >= 0; i--)
    {
        int multiplied = (num[i] - '0') * 2 + carry;

        if (multiplied > 9)
        {
            multiplied -= 10;
            carry = 1;
        }
        else
            carry = 0;

        mul_res.push_back(multiplied + '0');
    }
    if (carry)
        mul_res.push_back(carry + '0');

    reverse(mul_res.begin(), mul_res.end());

    return mul_res;
}

std::string GCD(std::string s1, std::string s2)
{
    if (s1 == s2)
        return s1;
    if (s1 == "0")
        return s2;
    if (s2 == "0")
        return s1;

    int s1back = s1.back() - '0';
    int s2back = s2.back() - '0';

    if (s1back % 2 == 0 && s2back % 2 == 0)
    {
        return string_mul_by2(GCD(string_div_by2(s1), string_div_by2(s2)));
    }

    else if (s1back % 2 == 0 && s2back % 2 != 0)
    {
        return GCD(string_div_by2(s1), s2);
    }

    else if (s1back % 2 != 0 && s2back % 2 == 0)
    {
        return GCD(s1, string_div_by2(s2));
    }

    else if (!string1_is_smaller(s1, s2))
    {
        return GCD(string_div_by2(string_diff(s1, s2)), s2);
    }

    else
    {
        return GCD(s1, string_div_by2(string_diff(s2, s1)));
    }
}

int main()
{
    int T = 0;
    std::string x, y = "";

    std::cin >> T;
    for (int i = 0; i < T; i++)
    {
        std::cin >> x >> y;
        std::cout << GCD(x, y) << std::endl;
    }

    return 0;
}
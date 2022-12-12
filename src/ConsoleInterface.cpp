#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include "RK.cpp"
#include "KMP.cpp"


class ConsoleInterface
{
public:

	void show()
	{
		std::cout << "Enter alphabet size k:" << std::endl;
		std::cin >> alphabetSize;
		system("cls");

		std::vector<std::reference_wrapper<std::string>> words;
		words.push_back(text);
		words.push_back(substring);

		for (auto& word : words)
		{
			generateWord(word);
			system("cls");
		}

		std::vector<double> timeResults;
		timeResults = testSearchers();
		std::cout << "Results:" << std::endl;
		std::cout << "---KMP-- | " << timeResults[0] << std::endl;
		std::cout << "---RK--- | " << timeResults[1] << std::endl;
	}


	void makeExp1()
	{
		std::vector<double> timeResult;

		size_t maxK = 301;
		size_t stepK = 10;
		size_t multText = 1000;

		std::ofstream out;
		out.open("../resource/exp1.csv");

		for (int k = 1; k <= maxK; k += stepK)
		{
			text = genWordType2("ab", multText * k);
			substring = genWordType2("ab", k);
			timeResult = testSearchers();
			out << std::to_string(k) + "," +
				std::to_string(multText * k) + "," +
				std::to_string(timeResult[0]) + "," +
				std::to_string(timeResult[1]) << std::endl;
		}

		out.close();
	}

	void makeExp2()
	{
		std::vector<double> timeResult;

		size_t maxM = 10'000'001;
		size_t stepM = 10'000;

		std::ofstream out;
		out.open("../resource/exp2.csv");

		text = genWordType3("ab", maxM);

		for (int m = 1; m <= maxM; m += stepM)
		{
			substring = genWordType2("a", m);
			timeResult = testSearchers();
			out << std::to_string(m) + "," +
				std::to_string(maxM) + "," +
				std::to_string(timeResult[0]) + "," +
				std::to_string(timeResult[1]) << std::endl;
		}

		out.close();
	}

	void makeExp3()
	{
		std::vector<double> timeResult;

		size_t maxH = 10'000'001;
		size_t stepH = 10'000;

		std::ofstream out;
		out.open("../resource/exp3.csv");

		substring = "aaaaa";

		for (int h = 1; h <= maxH; h += stepH)
		{
			text = genWordType2("aaaaab", h);
			timeResult = testSearchers();
			out << std::to_string(5) + "," +
				std::to_string(6 * h) + "," +
				std::to_string(timeResult[0]) + "," +
				std::to_string(timeResult[1]) << std::endl;
		}

		out.close();
	}

private:

	std::string text = "text";
	std::string substring = "substring";
	size_t alphabetSize;

	void generateWord(std::string& word)
	{
		std::cout << "Generate the " << word << std::endl;
		std::cout << "1) Enter the word" << std::endl;
		std::cout << "2) Generate (B1 B2 ... Bs)^k word" << std::endl;
		std::cout << "3) Generate (A)^m word from A = {a1, a2, ..., as}" << std::endl;
		std::cout << "Enter you choose: ";

		size_t choose;
		std::cin >> choose;

		word = "";
		if (choose == 1)
		{
			std::cout << "Enter the word:" << std::endl;
			std::cin >> word;
		}
		else if (choose == 2)
		{
			std::string subWord;
			std::cout << "Enter word (B1 B2 … Bs):" << std::endl;
			std::cin >> subWord;

			size_t k;
			std::cout << "Enter k:" << std::endl;
			std::cin >> k;

			word = genWordType2(subWord, k);
		}
		else if (choose == 3)
		{
			std::string letters;
			std::cout << "Enter letters for A = {a1, a2, ..., as}:" << std::endl;
			std::cin >> letters;

			size_t m;
			std::cout << "Enter m:" << std::endl;
			std::cin >> m;

			word = genWordType3(letters, m);
		}
	}

	std::string genWordType2(std::string subWord, size_t k)
	{
		std::string word;
		for (int i = 0; i < k; i++) {
			word += subWord;
		}
		return word;
	}

	std::string genWordType3(std::string letters, size_t m)
	{
		std::string word;
		std::random_device rd;
		std::mt19937 mt(rd());
		for (int i = 0; i < m; i++)
		{
			size_t randInd = mt() % letters.length();
			word += letters[randInd];
		}
		return word;
	}


	std::vector<double> testSearchers()
	{
		std::vector<int> resRK;
		std::vector<int> resKMP;

		KMP kmp = KMP(text, substring);
		auto startTime = std::chrono::system_clock::now();
		resKMP = kmp.search();
		auto endTime = std::chrono::system_clock::now();
		std::chrono::duration<double> timeTestKMP = endTime - startTime;

		RabinKarp rk = RabinKarp(text, substring, alphabetSize);
		startTime = std::chrono::system_clock::now();
		resRK = rk.search();
		endTime = std::chrono::system_clock::now();
		std::chrono::duration<double> timeTestRK = endTime - startTime;

		return std::vector<double>{timeTestKMP.count(), timeTestRK.count()};
	}
};
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <climits>

using PI = std::pair<int, int>;
using VI = std::vector<int>;
using VVI = std::vector<VI>;
using VP = std::vector<PI>;
using MI = std::unordered_map<int, int>;


class WordsCounter : public MI {
  public:
    void add(int word_idx) {
        if (MI::find(word_idx) == MI::end()) {
            MI::insert({word_idx, 1});
        } else {
            MI::at(word_idx)++;
        }
    }

    void remove(int word_idx) {
        if (MI::find(word_idx) != MI::end()) {
            MI::at(word_idx)--;
            if (MI::at(word_idx) == 0) {
                MI::erase(word_idx);
            }
        }
    }

    bool is_full(int word_size) {
        return MI::size() == word_size;
    }
};

void testcase() {
    int n; std::cin >> n;
    VI freqs(n);  // frequency of each word
    VP words;  // word postition and its index
    for (int i = 0; i < n; i++)
        std::cin >> freqs[i];

    for (int word_idx = 0; word_idx < n; word_idx++) {  // i: word index
        int freq = freqs[word_idx];
        for (int j = 0; j < freq; j++) {
            int pos; std::cin >> pos;
            words.push_back({pos, word_idx});
        }
    }
    int pos_size = (int) words.size();

    std::sort(words.begin(), words.end());  // sort by position

    int left = 0, right = 0;
    int min_length = INT_MAX;
    WordsCounter words_seen;

    while (right < pos_size) {
        // expand window size
        while (!words_seen.is_full(n) && right < pos_size) {
            int word_idx = words[right].second;
            words_seen.add(word_idx);
            right++;
        }
        // words full
        if (words_seen.is_full(n)) {
            // shrink window size
            while (words_seen.is_full(n) && left < right) {
                int word_idx = words[left].second;
                words_seen.remove(word_idx);
                left++;
            }
            min_length = std::min(min_length, words[right - 1].first - words[left - 1].first + 1);
        }
    }

    std::cout << min_length << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    while (t--)
        testcase();

    return 0;
}
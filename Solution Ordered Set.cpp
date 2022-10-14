
#include <map>
#include <unordered_map>
using namespace std;

class StockPrice {
    
    unordered_map<int, int> timestampToPrice;
    map<int, int, greater<>> priceToFrequency;
    int mostRecentTimestamp{};
    
public:
    StockPrice() = default;

    void update(int timestamp, int price) {

        //C++20: timestampToPrice.contains(timestamp)
        if (timestampToPrice.find(timestamp) != timestampToPrice.end()) {
            int previousPriceForTimestamp = timestampToPrice[timestamp];
            int updatedFrequencyForPreviousPrice = priceToFrequency[previousPriceForTimestamp] - 1;

            if (updatedFrequencyForPreviousPrice == 0) {
                priceToFrequency.erase(previousPriceForTimestamp);
            } else {
                priceToFrequency[previousPriceForTimestamp] = updatedFrequencyForPreviousPrice;
            }
        }

        ++priceToFrequency[price];
        timestampToPrice[timestamp] = price;
        mostRecentTimestamp = max(mostRecentTimestamp, timestamp);
    }

    int current() {
        return timestampToPrice[mostRecentTimestamp];
    }

    int maximum() {
        return priceToFrequency.begin()->first;
    }

    int minimum() {
        return priceToFrequency.rbegin()->first;
    }
};

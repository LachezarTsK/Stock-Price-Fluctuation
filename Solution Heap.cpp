
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;

class StockPrice {

    struct StockData {
        int timestamp{};
        int price{};
        StockData(int timestamp, int price) : timestamp{timestamp}, price{price}{}
    };

    struct ComparatorMinPriceOnTop {
        bool operator()(const StockData& x, const StockData& y) const {return x.price > y.price;}
    };
    priority_queue < StockData, vector<StockData>, ComparatorMinPriceOnTop> minHeapForPrice;

    struct ComparatorMaxPriceOnTop {
        bool operator()(const StockData& x, const StockData& y) const {return x.price < y.price;}
    };
    priority_queue<StockData, vector<StockData>, ComparatorMaxPriceOnTop> maxHeapForPrice;

    unordered_map<int, int> timestampToPrice;
    int mostRecentTimestamp{};

public:
    StockPrice() = default;

    void update(int timestamp, int price) {
        timestampToPrice[timestamp] = price;
        mostRecentTimestamp = max(mostRecentTimestamp, timestamp);
        minHeapForPrice.emplace(StockData(timestamp, price));
        maxHeapForPrice.emplace(StockData(timestamp, price));
    }

    int current() {
        return timestampToPrice[mostRecentTimestamp];
    }

    int maximum() {
        //lazy update
        while (maxHeapForPrice.top().price != timestampToPrice[maxHeapForPrice.top().timestamp]) {
            maxHeapForPrice.pop();
        }
        return maxHeapForPrice.top().price;
    }

    int minimum() {
        //lazy update
        while (minHeapForPrice.top().price != timestampToPrice[minHeapForPrice.top().timestamp]) {
            minHeapForPrice.pop();
        }
        return minHeapForPrice.top().price;
    }
};

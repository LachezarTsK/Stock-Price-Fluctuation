
import java.util.HashMap;
import java.util.Map;
import java.util.TreeMap;

public class StockPrice {

    private final Map<Integer, Integer> timestampToPrice;
    private final TreeMap<Integer, Integer> priceToFrequency;
    private int mostRecentTimestamp;

    public StockPrice() {
        timestampToPrice = new HashMap<>();
        priceToFrequency = new TreeMap<>();
    }

    public void update(int timestamp, int price) {
        if (timestampToPrice.containsKey(timestamp)) {
            int previousPriceForTimestamp = timestampToPrice.get(timestamp);
            int updatedFrequencyForPreviousPrice = priceToFrequency.get(previousPriceForTimestamp) - 1;

            if (updatedFrequencyForPreviousPrice == 0) {
                priceToFrequency.remove(previousPriceForTimestamp);
            } else {
                priceToFrequency.put(previousPriceForTimestamp, updatedFrequencyForPreviousPrice);
            }
        }

        priceToFrequency.put(price, priceToFrequency.getOrDefault(price, 0) + 1);
        timestampToPrice.put(timestamp, price);
        mostRecentTimestamp = Math.max(mostRecentTimestamp, timestamp);
    }

    public int current() {
        return timestampToPrice.get(mostRecentTimestamp);
    }

    public int maximum() {
        return priceToFrequency.lastKey();
    }

    public int minimum() {
        return priceToFrequency.firstKey();
    }
}

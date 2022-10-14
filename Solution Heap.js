
const {PriorityQueue} = require('@datastructures-js/priority-queue');

function StockData(timestamp, price) {
    this.timestamp = timestamp;
    this.price = price;
}

class StockPrice {

    constructor() {
        this.timestampToPrice = new Map();//Map<number,number>
        this.minHeapForPrice = new MinPriorityQueue({compare: (x, y) => x.price - y.price});//MinPriorityQueue<StockData>
        this.maxHeapForPrice = new MaxPriorityQueue({compare: (x, y) => y.price - x.price});//MaxPriorityQueue<StockData>
        this.mostRecentTimestamp = 0;
    }

    /** 
     * @param {number} timestamp 
     * @param {number} price
     * @return {void}
     */
    update(timestamp, price) {
        this.timestampToPrice.set(timestamp, price);
        this.mostRecentTimestamp = Math.max(this.mostRecentTimestamp, timestamp);
        this.minHeapForPrice.enqueue(new StockData(timestamp, price));
        this.maxHeapForPrice.enqueue(new StockData(timestamp, price));
    }

    /**
     * @return {number}
     */
    current() {
        return this.timestampToPrice.get(this.mostRecentTimestamp);
    }

    /**
     * @return {number}
     */
    maximum() {
        //lazy update
        while (this.maxHeapForPrice.front().price !== this.timestampToPrice.get(this.maxHeapForPrice.front().timestamp)) {
            this.maxHeapForPrice.dequeue();
        }
        return this.maxHeapForPrice.front().price;
    }

    /**
     * @return {number}
     */
    minimum() {
        //lazy update
        while (this.minHeapForPrice.front().price !== this.timestampToPrice.get(this.minHeapForPrice.front().timestamp)) {
            this.minHeapForPrice.dequeue();
        }
        return this.minHeapForPrice.front().price;
    }
}

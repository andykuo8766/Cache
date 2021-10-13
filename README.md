# Cache Simulator

## Author
| GitHub 帳號 | 姓名 | Email |
| ----------- | --- | --- |
| `andykuo8766` | `郭紘安` | andykuo8766@gapp.nthu.edu.tw |

## Caches Introduction
A CPU cache is a hardware cache used by the central processing unit (CPU) of a computer to reduce the average cost (time or energy) to access data from the main memory.
* Random Access Memory (RAM) :
Random Access Memory (RAM) is used to store the programs and data being used by the CPU in real-time. The data on the random access memory can be read, written, and erased any number of times. RAM is a hardware element where the data being currently used is stored. It is a volatile memory. Two types of RAM are Static RAM, or (SRAM) and Dynamic RAM, or (DRAM).
* Cache Memory :
Cache is a smaller and fast memory component in the computer which is inserted between the CPU and the main memory. To make this arrangement effective. The cache needs to be much faster than main memory. This approach is more economical than the use of fast memory devices to implement the entire main memory.
* Difference between RAM and Cache :
<style>
table th:first-of-type {
    width: 50%;
}
table th:nth-of-type(2) {
    width: 50%;
}
</style>
| RAM | CACHE | 
| --- | ----- |
| RAM is a volatile memory which could store the data as long as the power is supplied. | Cache is a smaller and fast memory component in the computer. |



## Cache Placement Policies
![image](https://github.com/andykuo8766/Cache-Simulator/blob/main/cache-associativity.jpg)
* Directed Mapped
* Set Associative
* Fully Associative




## Reference
* **[Cache placement policies](https://en.wikipedia.org/wiki/Cache_placement_policies)**
* **[ananthamapod/Cache-Simulator](https://github.com/ananthamapod/Cache-Simulator)**
* **[Cache Simulations](http://www.csbio.unc.edu/mcmillan/index.py?run=Wiki&page=%24Comp411S12.Lab+9)**
* **[cache-3-associativity-handout](http://csillustrated.berkeley.edu/PDFs/handouts/cache-3-associativity-handout.pdf)**
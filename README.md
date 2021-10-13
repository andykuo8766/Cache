# Cache Simulator

## Author
| GitHub 帳號 | 姓名 | Email |
| :-----------: | :---: | :---: |
| `andykuo8766` | `郭紘安` | andykuo8766@gapp.nthu.edu.tw |

## Caches Introduction
A CPU cache is a hardware cache used by the central processing unit (CPU) of a computer to reduce the average cost (time or energy) to access data from the main memory.

## RAM VS Cache
![image](https://github.com/andykuo8766/Cache-Simulator/blob/main/Pictures/CACHE.png)
* Random Access Memory (RAM) :
Random Access Memory (RAM) is used to store the programs and data being used by the CPU in real-time. The data on the random access memory can be read, written, and erased any number of times. RAM is a hardware element where the data being currently used is stored. It is a volatile memory. Two types of RAM are Static RAM, or (SRAM) and Dynamic RAM, or (DRAM).
* Cache Memory :
Cache is a smaller and fast memory component in the computer which is inserted between the CPU and the main memory. To make this arrangement effective. The cache needs to be much faster than main memory. This approach is more economical than the use of fast memory devices to implement the entire main memory.
* Difference between RAM and Cache :

| RAM | Cache | 
| --- | ----- |
| RAM is a volatile memory which could store the data as long as the power is supplied. | Cache is a smaller and fast memory component in the computer. | Cache is a smaller and fast memory component in the computer.|
| The size of ram is greater. | The size of cache memory is less. |
| It is not expensive. | It is expensive. |
| It holds programs and data that are currently executed by the CPU. | It holds frequently used data by the CPU. |
| It is not fastest as compared to cache. | 	It is faster. |
| RAM is faster than a hard disk, floppy disk, compact disk, or just any form of secondary storage media. | Cache memory increase the accessing speed of CPU. |
| CPU reads Cache Memory data before reading RAM. | CPU reads RAM data after reading Cache Memory. |
| It can be internal and external both. | It is generally internal. |

## Different levels of CPU Cache
![image](https://github.com/andykuo8766/Cache-Simulator/blob/main/Pictures/I-Cache%26D-Cache.jpg)
* L1 Cache (I-Cache, D-Cache)
	* D-Cache : L1 Cache for Data
	* I-Cache : L1 Cache for Instruction
* L2 Cache
* L3 Cache
## Cache features of Cortex-A series processors
|     | Cortex-A7 | Cortex-A9 | Cortex-A15 | Cortex-A53 | 
| Cache Implementation (Data) | PIPT | PIPT | PIPT | PIPT | 
| Cache Implementation (Instruction) | VIPT | VIPT | PIPT | VIPT | 
| L1 Cache size (data) | 8KB~64KB | 16KB/32KB/64KB | 32KB | 8KB~64KB | 
| L1 Cache Structure | 2-way set associative (Inst) 4-way set associative (Data) | 4-way set associative (Inst) 4-way set associative (Data) | 2-way set associative (Inst) 2-way set associative (Data) | 2-way set associative (Inst) 4-way set associative (Data) | 
| Cache line | 64Bytes | 32Bytes | 64Bytes | 64 bytes |  
* **[ARM Cortex-A7 MPCore Processor Technical Reference Manual](https://documentation-service.arm.com/static/602cf701083323480d479d18?token=)**
* **[ARM Cortex-A9 MPCore Processor Technical Reference Manual](https://documentation-service.arm.com/static/5e7e1f4fb2608e4d7f0a369f?token=)**
* **[ARM Cortex-A15 MPCore Processor Technical Reference Manual](https://documentation-service.arm.com/static/5e8ecc3ec5ee7d4a00694112?token=)**
* **[ARM Cortex-A53 MPCore Processor Technical Reference Manual](https://documentation-service.arm.com/static/6040c321ee937942ba301626?token=)**

## L1 Cache architecture in ARM

* VIVT (virtual indexed vritual tagged)


* VIPT(virtual indexed physical tagged)

* PIPT(physical indexed physical tagged)

## Cache Structure
![image](https://github.com/andykuo8766/Cache-Simulator/blob/main/Pictures/cache-associativity.jpg)
* Directed Mapped
![image](https://github.com/andykuo8766/Cache-Simulator/blob/main/Pictures/Direct-Mapped_Cache_Snehal_Img.png)
* Set Associative
![image](https://github.com/andykuo8766/Cache-Simulator/blob/main/Pictures/Set-Associative_Cache_Snehal_Img.png)
* Fully Associative
![image](https://github.com/andykuo8766/Cache-Simulator/blob/main/Pictures/Fully-Associative_Cache_Snehal_Img.png)

## How to run

* To complie the program

>make

* To run the program

>./sim <cache size\> <associativity\> <block size\> <replacement algorithm\> <write policy\> <tracefile.txt\>

* Example
![image](https://github.com/andykuo8766/Cache-Simulator/blob/main/Pictures/simulator.png)

## Reference
* **[Cache placement policies](https://en.wikipedia.org/wiki/Cache_placement_policies)**
* **[ananthamapod/Cache-Simulator](https://github.com/ananthamapod/Cache-Simulator)**
* **[Cache Simulations](http://www.csbio.unc.edu/mcmillan/index.py?run=Wiki&page=%24Comp411S12.Lab+9)**
* **[cache-3-associativity-handout](http://csillustrated.berkeley.edu/PDFs/handouts/cache-3-associativity-handout.pdf)**
* **[Difference between RAM and Cache](https://www.geeksforgeeks.org/difference-between-ram-and-cache/)**



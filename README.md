# Cache Simulator

## Author
| GitHub 帳號 | 姓名 | Email |
| :-----------: | :---: | :---: |
| `andykuo8766` | `郭紘安` | andykuo8766@gapp.nthu.edu.tw |

## Caches Introduction
A CPU cache is a hardware cache used by the central processing unit (CPU) of a computer to reduce the average cost (time or energy) to access data from the main memory.
-----
## RAM VS Cache
![image](https://github.com/andykuo8766/Cache-Simulator/blob/main/Pictures/CACHE.png)
### Random Access Memory (RAM) :
Random Access Memory (RAM) is used to store the programs and data being used by the CPU in real-time. The data on the random access memory can be read, written, and erased any number of times. RAM is a hardware element where the data being currently used is stored. It is a volatile memory. Two types of RAM are Static RAM, or (SRAM) and Dynamic RAM, or (DRAM).
### Cache Memory :
Cache is a smaller and fast memory component in the computer which is inserted between the CPU and the main memory. To make this arrangement effective. The cache needs to be much faster than main memory. This approach is more economical than the use of fast memory devices to implement the entire main memory.
### Difference between RAM and Cache :

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
-----
## Different levels of CPU Cache
![image](https://github.com/andykuo8766/Cache-Simulator/blob/main/Pictures/I-Cache%26D-Cache.jpg)
* L1 Cache (I-Cache, D-Cache)
	* D-Cache : L1 Cache for Data
	* I-Cache : L1 Cache for Instruction
* L2 Cache
* L3 Cache
-----
## Cache features of Cortex-A series processors
|     | Cortex-A7 | Cortex-A9 | Cortex-A15 | Cortex-A53 | 
|---| --- | --- | --- | --- | 
| Cache Implementation (Data) | PIPT | PIPT | PIPT | PIPT | 
| Cache Implementation (Instruction) | VIPT | VIPT | PIPT | VIPT | 
| L1 Cache size (Data) | 8KB~64KB | 16KB/32KB/64KB | 32KB | 8KB~64KB | 
| L1 Cache Structure | 2-way set associative (Inst) 4-way set associative (Data) | 4-way set associative (Inst) 4-way set associative (Data) | 2-way set associative (Inst) 2-way set associative (Data) | 2-way set associative (Inst) 4-way set associative (Data) | 
| Cache line | 64Bytes | 32Bytes | 64Bytes | 64 bytes |  
* **[ARM Cortex-A7 MPCore Processor Technical Reference Manual](https://documentation-service.arm.com/static/602cf701083323480d479d18?token=)**
* **[ARM Cortex-A9 MPCore Processor Technical Reference Manual](https://documentation-service.arm.com/static/5e7e1f4fb2608e4d7f0a369f?token=)**
* **[ARM Cortex-A15 MPCore Processor Technical Reference Manual](https://documentation-service.arm.com/static/5e8ecc3ec5ee7d4a00694112?token=)**
* **[ARM Cortex-A53 MPCore Processor Technical Reference Manual](https://documentation-service.arm.com/static/6040c321ee937942ba301626?token=)**
-----
## L1 Cache architecture in ARM
![image](https://github.com/andykuo8766/Cache-Simulator/blob/main/Pictures/Cache_Organizations.png)
###  PIPT(physical indexed physical tagged) : 
First, PIPT caches use only physical addresses for cache access. Hence, virtual-to-physical address translation should be performed, via a TLB, prior to cache access. This is a power and energy hungry operation, which contributes considerably to the power dissipation of modern processors. In addition, the TLBs are hotspots in a processor because of the high power dissipation. The operation also adds latency to the cache access.
###  PIVT(physical indexed virtual tagged) :
With a PIVT cache, a physical address is employed to decide a set index of a cache, and thus the address translation via a TLB is also needed prior to cache access, like PIPT caches. Hence, PIVT caches have overheads which are similar to those PTPT caches have in terms of address translation via a TLB. However, the use of a virtual tag could lead to synonym issues in the same set. That is, it is possible for the same data to be cached with different virtual addresses in the same set.
###  VIPT(virtual indexed physical tagged) :
VIPT caches use virtual addresses for indexing a cache, while tag matching employs physical addresses. Hence, TLB lookup does not have to be performed prior to cache lookup, unlike physically indexed caches (i.e., PIPT and PIVT caches). Consulting a TLB can be performed in parallel with the cache indexing with a virtual address generated by a processor, and the corresponding physical address obtained from the TLB is used to do tag comparison. Doing so removes TLB accesses on a critical path of memory access, which hides the latency overhead due to TLB lookups, making them a very popular choice in ubiquitous commercial designs. However, VIPT caches still consume power and energy due to TLB lookups for tag comparison on cache accesses. In addition, this design also has a design constraint on the cache geometry. Due to indexing with virtual addresses, it is possible for the same data be cached with different virtual addresses in different sets in the cache. 
###  VIVT (virtual indexed vritual tagged) :
Different from the other cache designs discussed above, VIVT caches use only virtual addresses for cache access. They have potentially lower access latency and energy consumption than the physical caches described above because a TLB is consulted only for cache misses. In addition, VIVT caches allow a flexible cache geometry by removing the large associativity constraint of a VIPT cache design. This can be more power and energy efficient for cache accesses. However, the use of virtual addresses for cache accesses leads to synonym problems, which complicates the cache design.
* **[REDUCING ADDRESS TRANSLATION OVERHEADS WITHVIRTUAL CACHING](https://www.semanticscholar.org/paper/Reducing-address-translation-overheads-with-virtual-Yoon/5ea9787782bde3ddcb6632a75a2480417a6282b4)**


-----
## Cache Structure
![image](https://github.com/andykuo8766/Cache-Simulator/blob/main/Pictures/cache-associativity.jpg)
* Directed Mapped
![image](https://github.com/andykuo8766/Cache-Simulator/blob/main/Pictures/Direct-Mapped_Cache_Snehal_Img.png)
* Set Associative
![image](https://github.com/andykuo8766/Cache-Simulator/blob/main/Pictures/Set-Associative_Cache_Snehal_Img.png)
* Fully Associative
![image](https://github.com/andykuo8766/Cache-Simulator/blob/main/Pictures/Fully-Associative_Cache_Snehal_Img.png)
-----
## How to run

* To complie the program

>make

* To run the program

>./sim <cache size\> <associativity\> <block size\> <replacement algorithm\> <write policy\> <tracefile.txt\>

* Example
![image](https://github.com/andykuo8766/Cache-Simulator/blob/main/Pictures/simulator.png)
-----
## Reference
* **[Cache placement policies](https://en.wikipedia.org/wiki/Cache_placement_policies)**
* **[ananthamapod/Cache-Simulator](https://github.com/ananthamapod/Cache-Simulator)**
* **[Cache Simulations](http://www.csbio.unc.edu/mcmillan/index.py?run=Wiki&page=%24Comp411S12.Lab+9)**
* **[cache-3-associativity-handout](http://csillustrated.berkeley.edu/PDFs/handouts/cache-3-associativity-handout.pdf)**
* **[Difference between RAM and Cache](https://www.geeksforgeeks.org/difference-between-ram-and-cache/)**
* **[Cache features of Cortex-A series processors](https://developer.arm.com/documentation/den0013/d/Caches/Cache-architecture/Virtual-and-physical-tags-and-indexes)**

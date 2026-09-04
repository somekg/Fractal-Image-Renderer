Mandelbrot-Fractal Explorer
------------------------
A high-resolution, mathematically precise fractal rendering engine built in modern C++17 that allows for easy exploration of the fractal. 
This project generates extremely detailed 4K visualizations of the Mandelbrot set by calculating millions of points on the complex plane.

## 📊 Performance Optimization & ⏱️ Benchmarking

This engine was optimized in two phases—algorithmic improvements and OpenMP parallelization—reducing 4K render time from over 3.5 minutes to ~1 second.

### 1. Algorithmic Enhancements
* **Removed `std::complex` & `sqrt()`:** Replaced with primitive `double` arithmetic, cutting render time by >50% (211s down to 100s).
* **Trigonometry Decoupling:** Calculated color once per pixel instead of 4 times (for 2x2 SSAA), reducing expensive `cos()` calls by 75%.

### 2. Multi-Core Parallelization (OpenMP)
Fractals are highly parallelizable (99.40% of execution time). We modeled the maximum performance gain using **Amdahl's Law** for $P = 0.994$ on $N = 12$ threads:

$$
S(12) = \frac{1}{(1 - 0.994) + \frac{0.994}{12}} \approx 11.26
$$

After some benchmarking in within a Zoomed section of the fractal were every pixel is within the set to trigger max iteration range the empirical gain 
was:
> Note: We can confirm the speedup correctly approaches the expected theoretical optimistic limit assuming OS overhead slowed it down a little while benchmarking.

$$Empirical\_Speedup = \frac{101.333\text{ s}}{11.000\text{ s}} \approx \mathbf{9.21\times}$$

*Figure 1: Baseline to OpenMP scaling.*

<img width="800" height="600" alt="performance_graph1" src="https://github.com/user-attachments/assets/392bb333-a180-4cfc-bd10-319c0badeefe" />


### 3. OpenMP Scheduling & Load Imbalance
Empty space computes instantly, while the black Mandelbrot center requires the maximum 1,000 iterations, creating massive CPU load imbalance. 

* **`schedule(static)` & `auto`:** Fast threads finish empty space instantly and sit idle, bottlenecking performance.
* **`schedule(dynamic)`:** Threads process small pixel chunks and immediately request more work. No thread sits idle, preventing starvation and achieving the final ~1s render time.

*Figure 2: Dynamic scheduling prevents thread starvation, massively outperforming static allocation.*

<img width="800" height="600" alt="performance_graph2" src="https://github.com/user-attachments/assets/0adf5227-7b8b-445f-8d3a-3aff039a345e" />

## 🖼️ Samples

<video src="https://github.com/user-attachments/assets/8260dd04-c55e-4c95-9bb1-91a72477b62b" width="320" height="240" controls></video>



<img width="2944" height="1656" alt="frame_000_optimized_10000" src="https://github.com/user-attachments/assets/e99c41c7-7e08-4e90-a99c-0f1f4a460825" />
<img width="3840" height="2160" alt="fractal_4k" src="https://github.com/user-attachments/assets/a3ab12ff-b67f-438a-a894-5c1b04b671e2" />
<img width="2944" height="1656" alt="fractal_4k_optimized_10000" src="https://github.com/user-attachments/assets/586db860-20c0-4c45-ac70-f58fea11261a" />
<img width="3840" height="2160" alt="fractal_4k" src="https://github.com/user-attachments/assets/7982b840-8fd1-4eeb-baf1-9d867f35efd3" />
<img width="3840" height="2160" alt="fractal_4k" src="https://github.com/user-attachments/assets/607ee2fe-e8a7-46f0-8956-c921dcf838e9" />
<img width="2944" height="1656" alt="fractal_4k_1_optimized_10000" src="https://github.com/user-attachments/assets/a4c120c2-b514-4b8e-9897-88ed6eba19d7" />






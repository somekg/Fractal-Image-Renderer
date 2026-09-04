Mandelbrot Fractal Viewer
------------------------
A high-resolution, mathematically precise fractal rendering engine built in modern C++17. 
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
![Normal](https://github.com/user-attachments/assets/51ea77a8-30c9-4a6a-b5ce-ecfa11a74d38)
![zoom1](https://github.com/user-attachments/assets/8df34d36-5230-4c6c-97f2-b1fea0f8c913)
![zoom2](https://github.com/user-attachments/assets/0b1a3fa1-db33-41ac-bfd4-e955e8912f68)
![cool](https://github.com/user-attachments/assets/83a32724-d640-4f27-bd4c-d1f175a8fe14)
![blue](https://github.com/user-attachments/assets/37b81f37-e12b-49f9-8a73-e59dcda52955)
![vortex](https://github.com/user-attachments/assets/a8fd1cd8-72aa-4ea1-aa0b-bac9b7cb3520)
![orange](https://github.com/user-attachments/assets/68c5f5a5-8914-4508-bb8a-cfa5c766e8f0)
![redcurves](https://github.com/user-attachments/assets/3c7808cc-6da1-4749-927a-3c479731fb72)
![sword](https://github.com/user-attachments/assets/6eecb2f4-380b-42f9-a886-a1d9efc15f52)
![Red](https://github.com/user-attachments/assets/656df4ec-4e46-4105-a60a-b2eae93ff0a0)
![oranger](https://github.com/user-attachments/assets/79a59f8b-2c03-4d5f-b787-765cb569d18a)
![Toasty](https://github.com/user-attachments/assets/50876fda-98ed-4ef6-abf7-39e8467b403f)

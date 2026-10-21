# Bentley-Ottmann-algorithm
## Algorithms for Reporting and Counting Geometric Intersections
#### JON L. BENTLEY, MEMBER, IEEE, AND THOMAS A. OTTMANN

# Project Team

- [Ankita Behera](https://github.com/rxndom266/)
- [Durba Satpathi](https://github.com/durba-s)
- [Prakhar Agarwal](https://github.com/PrAkHaR-BitsPilani)

```cpp
/**
 * Ankita Behera 2019A7PS0075H
 * Durba Satpathi 2019A7PS0972H
 * Prakhar Agarwal 2019A7PS0174H
 **/
```

# CS F364 Design And Analysis of Algorithms
## Assignment-1
---

### Problem Statement
Consider a set `S` of `n` line segments `{s1, s2, s3...., sn}`. Each line segment `si` (`1 ≤ i ≤ n`) is associated with a pair of points, its lower end-point and its upper end-point. We have to find and report the intersection points of these line segments.

**Assumption:** No overlapping line segments.

---

### Overview of the Algorithm
The algorithm uses a sweep line (we have used a horizontal sweep line), which sweeps over the 2D plane passing through all possible event points. An event point is either the lower endpoint of a line or an upper endpoint of a line or the intersection point. The algorithm uses the fact that 2 adjacent/neighbouring line segments must intersect first before intersecting other line segments. 

In this algorithm, we repeatedly check immediate neighbouring line segments for intersections. Neighbours are decided based on the x-coordinates of the point of intersections of the line segment with the sweep line. This ordering of the line segments is stored in another balanced binary search tree called the status queue. We have used 3 main functions to implement the algorithm:

* **FindIntersections(S)**: The segment endpoints are inserted into an event Queue (which is a balanced binary tree) ordered by decreasing order of their y-coordinates. If the y-coordinates are the same, they are ordered in increasing order of x-coordinates. The max-point (largest y-coordinate / smallest x-coordinate while comparing 2 points with the same y-coordinate) is removed from the event Queue till it is empty and a call is made to the `HandleEventPoint` function passing `p` as the parameter.
* **HandleEventPoint(p)**: This function updates the status queue and reports a point as an intersection point (if it is, along with the corresponding line segments). Each point is associated with 3 sets: `L(p)` [stores segments of which `p` is a lower end point], `U(p)` [stores segments of which `p` is an upper end point] and `C(p)` [stores segments which are in `T` and contain `p`]. A point is an intersection point iff `|L(p) U U(p) U C(p)| > 1`. 
  * If the point is an *upper endpoint*, the corresponding segment is inserted into the queue and the resulting 2 neighbouring pairs (left and right Neighbours of the inserted segment now become immediate Neighbours with the inserted segment) are checked for intersections. 
  * If the point is a *lower endpoint*, the corresponding segment is removed from the queue and the resulting neighbouring pair (left and right Neighbours of the removed segment now become immediate Neighbours with each other) is checked for intersections. 
  * If the point is an *intersection point*, the ordering of the segments in the queue is swapped. While checking for intersections between 2 segments, the function `FindNewEventPoints(s1,s2,p)` is called.
* **FindNewEventPoints(s1,s2,p)**: This function checks if the segments intersect with each other. If the segments do intersect and their intersection point is below or to the right of the sweep line, the intersection point is inserted into the status queue.

---

### Data Structures and Classes
* **Event Queue:** A BBST storing the event points.
* **Status Queue:** A BBST storing the segments intersecting the status queue.
* **Vector:** `std::vector` used for storing sets of segments, `L(p)`, `U(p)`, `C(p)`.
* **Pair:** Used to store an ordered pair.
* **Segment:** A segment data structure consists of 2 pairs, namely its lower and upper end points.
* **Point:** An event point data structure consists of its x-coordinate, y-coordinate, and the 3 sets associated with it (i.e., `L(p)`, `U(p)` and `C(p)`).

---

### Algorithm Visualization

<details>
<summary><b>Click to expand Algorithm Visualization (Sweep Line Steps)</b></summary>
<br>

![Step 1](./algo/a1.png)
![Step 2](./algo/a2.png)
![Step 3](./algo/a3.png)
![Step 4](./algo/a4.png)
![Step 5](./algo/a5.png)
![Step 6](./algo/a6.png)
![Step 7](./algo/a7.png)
![Step 8](./algo/a8.png)
![Step 9](./algo/a9.png)
![Step 10](./algo/a10.png)

</details>

---

### Theoretical Timing Analysis
The theoretical time complexity of the algorithm is `O(i log n + n log n)`, where `i` is the number of intersection points and `n` is the number of line segments.

---

### Timing Analysis - Plots

**`i` vs `t` plot (with n = 1e6)**<br>
![i vs t plot](./ivst.png)

**`n log n` vs `t` plot**<br>
![nlogn vs t plot](./nvst1.png)

---

### Test Cases

#### Primary Test Case
**Visualization:**

![Plot 1](./plot1.png)

**Input:**
```text
3
1 3 4 2
3 3 1 1
1 4 2 1
```

**Output:**
```text
[Intersection] 1
1.375,2.875
[SEG]: 2,1 and 1,4
[SEG]: 4,2 and 1,3
[Intersection] 2
2.5,2.5
[SEG]: 4,2 and 1,3
[SEG]: 1,1 and 3,3
[Intersection] 3
1.75,1.75
[SEG]: 2,1 and 1,4
[SEG]: 1,1 and 3,3
```

#### Other Test Cases - Visualizations

| | |
|:---:|:---:|
| ![Plot 2](./plot2.png) | ![Plot 3](./plot3.png) |
| ![Plot 7](./plot7.png) | ![Plot 8](./plot8.png) |

---

### Degeneracies - Plots

![Degeneracies Plot](./plot6.png)

When the points are too close to each other due to floating point precision limits, we sometimes capture fewer than the true number of intersection points.

# Point Cloud Toolkit

## Reconstruct image format for unordered point cloud

Many lidar sensors have multiple lasers taking measurements, which have a small offset to each other.
This leads to the point cloud being recorded from multiple point of views, which can distort a naive
projection onto a grid. The goal of this algorithm is to take this effect into account as good as possible.

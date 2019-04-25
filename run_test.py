# point PYTHONPATH towards the compiled custom library
import sys
import os
sys.path.append(os.path.join(os.getcwd(), "cmake-build-debug"))

# loading custom library
from pcl_toolkit import reconstruct_lidar_image


# load a sample point cloud
try:
    sys.path.append("/mnt/c/Users/usr/PycharmProjects/untitled1")
    from data.kitti_loader import KittiLoader
    kitti_path = os.path.expanduser("/mnt/c/Users/usr/Downloads/KITTI/training")
    data_loader = KittiLoader(kitti_path)
    pcl, bboxes = data_loader.get_raw_data(8)
except ImportError:
    import numpy as np
    pcl = np.random.uniform(0, 10, (100, 3))

print(pcl.shape)

# test custom C++ function
reconstruct_lidar_image(pcl)

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <cmath>
#include <iostream>
#include <vector>

std::vector<double> to_spherical(double *pcl, size_t pcl_len) {
    // transforms a point cloud into spherical coordinates
    // accepts 1d vectors in format [x1, y1, z1, x2, y2, z2, ...],
    // returns the vector with the same format: [r1, az1, el1, r2, az2, el2, ...]
    std::vector<double> pcl_spherical;
    pcl_spherical.reserve(pcl_len);
    double x, y, z, distance, azimuth, elevation;

    for (size_t n = 0; n < pcl_len; n += 3) {
        x = pcl[n + 0];
        y = pcl[n + 1];
        z = pcl[n + 2];

        distance = sqrt(x * x + y * y + z * z);
        azimuth = atan2(y, x);
        elevation = acos(z / distance);

        pcl_spherical[n + 0] = distance;
        pcl_spherical[n + 1] = azimuth;
        pcl_spherical[n + 2] = elevation;
    }
    return pcl_spherical;
}


namespace py = pybind11;

py::array_t<double> reconstruct_lidar_image(py::array_t<double> pcl) {
    // Getting infos about python numpy array for accessing it
    py::buffer_info buffer = pcl.request();
    size_t shape_x = buffer.shape[0];
    // size_t shape_y = buffer.shape[1];
    size_t size = buffer.size;
    auto pcl_ptr = (double *) buffer.ptr;

    std::vector<double> pcl_spherical = to_spherical(pcl_ptr, size);

    // just print numpy array to terminal for now
    for (size_t n = 0; n < size; n+=3) {
        std::cout << pcl_ptr[n] << " " << pcl_ptr[n + 1] << " " << pcl_ptr[n + 2] << std::endl;
    }
}

PYBIND11_MODULE(pcl_toolkit, m) {
    m.def("reconstruct_lidar_image", &reconstruct_lidar_image, py::return_value_policy::move);
}
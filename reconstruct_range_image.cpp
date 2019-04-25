#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <cmath>
#include <iostream>
#include <vector>

namespace py = pybind11;

py::array_t<double> reconstruct_lidar_image(py::array_t<double> pcl)
{
    // Getting infos about python numpy array for accessing it
    py::buffer_info buffer = pcl.request();
    size_t shape_x = buffer.shape[0];
    size_t shape_y = buffer.shape[1];
    size_t size = buffer.size;
    auto pcl_ptr = (double *)buffer.ptr;

    // just print numpy array to terminal for now
    size_t idx;
    for (size_t n = 0; n < shape_x; n++)
    {
        for (size_t m = 0; m < shape_y; m++)
        {
            idx = n * shape_y;
            std::cout << pcl_ptr[idx] << " " << pcl_ptr[idx + 1] << " " << pcl_ptr[idx + 2] << std::endl;
        }
    }
}

PYBIND11_MODULE(pcl_toolkit, m)
{
    m.def("reconstruct_lidar_image", &reconstruct_lidar_image, py::return_value_policy::move);
}
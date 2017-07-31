#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <lawrap/blas.h>
#include <string>
#include <iostream>

namespace py = pybind11;

py::array_t<double> getJK_np(py::array_t<double> g,
                            py::array_t<double> D)
{
    py::buffer_info g_info = g.request();
    py::buffer_info D_info = D.request();

    if(g_info.ndim != 4)
        throw std::runtime_error("g is not a four-tensor");

    if(D_info.ndim != 2)
        throw std::runtime_error("D is not a matrix");

    if(g_info.shape[0] != D_info.shape[0])
        throw std::runtime_error("Dimensions not match");

    size_t nbas = g_info.shape[0];
    size_t nbas3 = nbas * nbas * nbas;
    size_t nbas2 = nbas * nbas;
    size_t s1 = g_info.strides[0] / sizeof(double);
    size_t s2 = g_info.strides[1] / sizeof(double);
    size_t s3 = g_info.strides[2] / sizeof(double);
    size_t s4 = g_info.strides[3] / sizeof(double);

    const double* g_data = static_cast<double*>(g_info.ptr);
    const double* D_data = static_cast<double*>(D_info.ptr);
    std::vector<double> J_data(nbas * nbas);

    for(size_t i = 0; i < nbas; i++)
    for(size_t j = 0; j <= i; j++)
    {
        double val = LAWrap::dot(nbas * nbas, D_data, 1,
            &g_data[i * s1 + j * s2], 1);
        /*double val = 0.;
        int ind = i * s1 + j * s2;
        for (size_t k = 0; k < nbas; k++)
        for (size_t l = 0; l <= k; l++)
        {
            double fac = (k == l) ? (1.) : (2.);
            val += fac * g_data[ind + k * s3 + l * s4]
                * D_data[k * nbas + l];
        }*/
        J_data[i * nbas + j] = J_data[j * nbas + i] = val;
    }

    py::buffer_info J_buf =
    {
        J_data.data(),
        sizeof(double),
        py::format_descriptor<double>::format(),
        2,
        {nbas, nbas},
        {sizeof(double) * nbas, sizeof(double)}
    };

    return py::array_t<double>(J_buf);
}

py::array_t<double> getJ_np(py::array_t<double> g,
                            py::array_t<double> D)
{
    py::buffer_info g_info = g.request();
    py::buffer_info D_info = D.request();

    if(g_info.ndim != 4)
        throw std::runtime_error("g is not a four-tensor");

    if(D_info.ndim != 2)
        throw std::runtime_error("D is not a matrix");

    if(g_info.shape[0] != D_info.shape[0])
        throw std::runtime_error("Dimensions not match");

    size_t nbas = g_info.shape[0];
    size_t nbas3 = nbas * nbas * nbas;
    size_t nbas2 = nbas * nbas;
    size_t s1 = g_info.strides[0] / sizeof(double);
    size_t s2 = g_info.strides[1] / sizeof(double);
    size_t s3 = g_info.strides[2] / sizeof(double);
    size_t s4 = g_info.strides[3] / sizeof(double);

    const double* g_data = static_cast<double*>(g_info.ptr);
    const double* D_data = static_cast<double*>(D_info.ptr);
    std::vector<double> J_data(nbas * nbas);

    for(size_t i = 0; i < nbas; i++)
    for(size_t j = 0; j <= i; j++)
    {
        double val = 0., fac = 0.;
        int ind = i * s1 + j * s2;
        for (size_t k = 0; k < nbas; k++)
        for (size_t l = 0; l <= k; l++)
        {
            fac = (k == l) ? (1.) : (2.);
            val += fac * g_data[ind + k * s3 + l * s4]
                * D_data[k * nbas + l];
        }
        J_data[i * nbas + j] = J_data[j * nbas + i] = val;
    }

    py::buffer_info J_buf =
    {
        J_data.data(),
        sizeof(double),
        py::format_descriptor<double>::format(),
        2,
        {nbas, nbas},
        {sizeof(double) * nbas, sizeof(double)}
    };

    return py::array_t<double>(J_buf);
}

py::array_t<double> getK_np(py::array_t<double> g,
                            py::array_t<double> D)
{
    py::buffer_info g_info = g.request();
    py::buffer_info D_info = D.request();

    if(g_info.ndim != 4)
        throw std::runtime_error("g is not a four-tensor");

    if(D_info.ndim != 2)
        throw std::runtime_error("D is not a matrix");

    if(g_info.shape[0] != D_info.shape[0])
        throw std::runtime_error("Dimensions not match");

    size_t nbas = g_info.shape[0];
    size_t nbas3 = nbas * nbas * nbas;
    size_t nbas2 = nbas * nbas;
    size_t s1 = g_info.strides[0] / sizeof(double);
    size_t s2 = g_info.strides[1] / sizeof(double);
    size_t s3 = g_info.strides[2] / sizeof(double);
    size_t s4 = g_info.strides[3] / sizeof(double);

    const double* g_data = static_cast<double*>(g_info.ptr);
    const double* D_data = static_cast<double*>(D_info.ptr);
    std::vector<double> J_data(nbas * nbas);

    for(size_t i = 0; i < nbas; i++)
    for(size_t j = 0; j <= i; j++)
    {
        double val = 0., fac = 0.;
        int ind = i * s1 + j * s2;
        for (size_t k = 0; k < nbas; k++)
        for (size_t l = 0; l < nbas; l++)
            val += g_data[ind + k * s3 + l * s4]
                * D_data[k * nbas + l];
        J_data[i * nbas + j] = J_data[j * nbas + i] = val;
    }

    py::buffer_info J_buf =
    {
        J_data.data(),
        sizeof(double),
        py::format_descriptor<double>::format(),
        2,
        {nbas, nbas},
        {sizeof(double) * nbas, sizeof(double)}
    };

    return py::array_t<double>(J_buf);
}

PYBIND11_PLUGIN(jk)
{
    py::module m("jk", "Hongzhou's basic module");

    m.def("getJK_np", &getJK_np, "homemade get J and K");
    m.def("getJ_np", &getJ_np, "homemade get J");
    m.def("getK_np", &getK_np, "homemade get K");

    return m.ptr();
}
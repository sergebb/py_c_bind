#include <Python.h>
#include <string>
#include <boost/python.hpp>
#include <stdio.h>
#include <iostream>
#include <numpy/ndarrayobject.h> // ensure you include this header
using namespace boost::python;

namespace { // Avoid cluttering the global namespace.

    // A couple of simple C++ functions that we want to expose to Python.
    std::string greet() { return "hello, world"; }
    int square(int number) { return number * number; }

    void CorrealateLine(float* data,float* newdata,int size){
        float sum;
        int i,j,p;
        for ( i=0; i<size; i++ ){
            sum=0;
            for ( j=0; j<size; j++ ){
                p = (i+j)%size;
                sum+=data[j]*data[p];
            }
            newdata[i]=sum;
        }
    }

    void Correalate( boost::python::numeric::array& data )
    {
        // boost::python::object shape = data.attr("shape");
        // int rows = extract<int>(shape[0]);
        // int cols = extract<int>(shape[1]);
        // float* line = new float[cols];
        // float* newline = new float[cols];

        // for ( int n=0; n<rows; n++ ){
        //     for ( int i=0; i<cols; i++ ){
        //         line[i] = extract<float>(data[make_tuple(n,i)]);
        //     }
        //     CorrealateLine(line,newline,cols);
        //     for ( int i=0; i<cols; i++ ){
        //         data[make_tuple(n,i)] = newline[i];
        //     }
        // }

        // delete[] line;
        // delete[] newline;

        PyArrayObject *ptr = (PyArrayObject *)data.ptr();
        if (ptr == NULL) {
            std::cerr << "Could not get NP array." << std::endl;
        }
        const int dims =  PyArray_NDIM(ptr);
        if (dims != 2)
        {
            std::cerr << "Wrong dimension on array." << std::endl;
        }
        int rows = *(PyArray_DIMS(ptr));
        int cols = *(PyArray_DIMS(ptr)+1);


        if (ptr->descr->elsize != sizeof(float))
        {
            std::cerr << "Must be numpy.float32 ndarray" << std::endl;
        }
        std::cerr << rows << " " << cols << std::endl;

        float* newline = new float[cols];
        for ( int n=0; n<rows; n++ ){
            float *line = static_cast<float*> PyArray_GETPTR2(ptr, n, 0);
            CorrealateLine(line,newline,cols);
            for ( int i=0; i<cols; i++ ){
                line[i] = newline[i];
            }
        }

        delete[] newline;

        return;
        
    }
}


BOOST_PYTHON_MODULE(libcorr)
{
    numeric::array::set_module_and_type( "numpy", "ndarray");
    // Add regular functions to the module.
    def("greet", greet);
    def("square", square);
    def("Correlate", Correalate);
}
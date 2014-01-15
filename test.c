#include <Python.h>
#include <string>
#include <boost/python.hpp>
#include <stdio.h>
#include <numpy/ndarrayobject.h> // ensure you include this header
using namespace boost::python;

namespace { // Avoid cluttering the global namespace.

    // A couple of simple C++ functions that we want to expose to Python.
    std::string greet() { return "hello, world"; }
    int square(int number) { return number * number; }

    void CorrealateLine(float* data,float* newdata,int size){
        float sum;
        for ( int i=0; i<size; i++ ){
            sum=0;
            for ( int j=0, p; j<size; j++ ){
                p = (i+j)%size;
                sum+=data[j]*data[p];
            }
            newdata[i]=sum;
        }
    }

    boost::python::object Correalate( boost::python::numeric::array data )
    {
        boost::python::object shape = data.attr("shape");
        int rows = extract<int>(shape[0]);
        int cols = extract<int>(shape[1]);
        float* line = new float[cols];
        float* newline = new float[cols];

        for ( int n=0; n<rows; n++ ){
            for ( int i=0; i<cols; i++ ){
                line[i] = extract<float>(data[make_tuple(n,i)]);
            }
            CorrealateLine(line,newline,cols);
            for ( int i=0; i<cols; i++ ){
                data[make_tuple(n,i)] = newline[i];
            }
        }

        delete[] line;
        delete[] newline;

        //  // const_cast is rather horrible but we need a writable pointer
        //   double * data = size ? const_cast<double *>(&vec[0]) : static_cast<double *>(NULL);
        // // create a PyObject * from pointer and data 
        //   PyObject * pyObj = PyArray_SimpleNewFromData( 1, &size, NPY_DOUBLE, data );
        //   boost::python::handle<> handle( pyObj );
        //   boost::python::numeric::array arr( handle );

        // /* The problem of returning arr is twofold: firstly the user can modify
        //   the data which will betray the const-correctness 
        //   Secondly the lifetime of the data is managed by the C++ API and not the lifetime
        //   of the numpy array whatsoever. But we have a simply solution..
        //  */

        return data.copy(); // copy the object. numpy owns the copy now.
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
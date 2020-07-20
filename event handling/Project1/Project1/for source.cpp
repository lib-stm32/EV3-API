#include <Python.h>
#include <boost/python.hpp>
BOOST_PYTHON_MODULE(example)
{
    class_<Some>("Some")
        .def(init<int, string>(args("some_id", "name")))
        ;
}
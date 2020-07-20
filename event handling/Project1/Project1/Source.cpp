#include <boost/python.hpp>

using namespace boost::python;


BOOST_PYTHON_MODULE(example)
{
    Some::Some()
        : mID(NOT_AN_IDENTIFIER)
    {
    }

    Some::Some(int some_id, string const& name)
        : mID(some_id), mName(name)
    {
    }
}
## Return value optimization

Using ++x instead of x++ avoids temporaries. Using the explicit keyword helps avoid hidden temporaries.

Here's one more tip for avoiding temporaries. It's called return value optimization. The best way of showing how it works is through an example. Mult multiplies two complex values and returns the result.

complex<double> Mult(const complex<double>& a, const complex<double>& b)
    {
    complex<double> c;
    double i = (a.real() * b.imag()) + (a.imag() * b.real());
    double r = (a.real() * b.real()) - (a.imag() * b.imag());
    c.imag(i);
    c.real(r);
    return (c);
    }

The code is correct, but it could be more efficient. We already know we can improve the efficiency by initializing the complex value when it's constructed:

complex<double> Mult(const complex<double>& a, const complex<double>& b)
    {
    complex<double> c((a.real() * b.real()) - (a.imag() * b.imag()), 
	              (a.real() * b.imag()) + (a.imag() * b.real()));
    return (c);
    }

Now let's take it one step further:

complex<double> Mult(const complex<double>& a, const complex<double>& b)
    {
    return (complex<double>((a.real() * b.real()) + (a.imag() * b.imag()), 
	                    (a.real() * b.imag()) - (a.imag() * b.real())));
    }

At this point, the compiler can work a little magic. It can omit creating the temporary object that holds the function return value, because that object is unnamed. It can construct the object defined by the return expression inside the memory of the object that is receiving the result.

Return value optimization is another way of saying return constructor arguments instead of named objects. What kind of gains can you expect from this optimization? Here are some trivial example functions I used to evaluate potential performance improvements.

template <class T> T Original(const T& tValue)
    {
    T tResult; // named object; probably can't be optimized away
    tResult = tValue;
    return (tResult);
    }

template <class T> T Optimized(const T& tValue)
    {
    return (T(tValue)); // unnamed object; optimization potential high
    }




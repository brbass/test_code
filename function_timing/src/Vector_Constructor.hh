#ifndef Vector_Constructor_hh
#define Vector_Constructor_hh

class Vector_Constructor_1
{
public:
    Vector_Constructor_1(std::vector<double> const &data):
        data_(data)
    {
    }
private:
    std::vector<double> data_;
};

class Vector_Constructor_2
{
public:
    Vector_Constructor_2(std::vector<double> data):
        data_(data)
    {
    }
private:
    std::vector<double> data_;
};

class Vector_Constructor_3
{
public:
    Vector_Constructor_3(std::vector<double> &data):
        data_(data)
    {
    }
private:
    std::vector<double> &data_;
};

std::vector<double> get_vector(int size)
{
    std::vector<double> data;
    data.assign(size, 0.);

    return data;
}

void change_vector(int size,
                   std::vector<double> &data)
{
    data.assign(size, 0.);
}

#endif

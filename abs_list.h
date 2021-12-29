//
// abstract class
//

#ifndef abs_list_H
#define abs_list_H


template<class T>
class abs_list
{
public:
    // operators
    virtual bool is_empty() const = 0;
    virtual void insert(T, int) = 0;
    virtual void cancel(int) = 0;
};

#endif //abs_list_H

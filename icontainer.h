#ifndef ICONTAINER_H
#define ICONTAINER_H

template <typename T>
class IContainer {
public:
    virtual ~IContainer() {} // Необходим для полиморфизма
    virtual void addElement(const T& value) = 0;
    virtual T removeElement() = 0;
    virtual bool isEmpty() const noexcept = 0;
};

#endif // ICONTAINER_H
#ifndef FACTORY_H
#define FACTORY_H

#include "graphs.h"
#include <map>

class TFactory {
    class TImpl;
    std::unique_ptr<const TImpl> Impl;
public:
    TFactory();
    ~TFactory();
    std::unique_ptr<TGraph> Create(const std::string& type, std::unique_ptr<arguments>&& args) const;
};

#endif
#include <iostream>
#include <typeinfo>
#include "factory.h"

class TFactory::TImpl{
    class ICreator{
    public:
        virtual ~ICreator(){}
        virtual std::unique_ptr<TGraph> Create(std::unique_ptr<arguments>&& args) const = 0;
    };
    using TCreatorPtr = std::shared_ptr<ICreator>;
    using TRegisteredCreators = std::map<std::string, TCreatorPtr>;
    TRegisteredCreators RegisteredCreators;
public:
    template <class TCurrentObject>
    class TCreator: public ICreator{
        std::unique_ptr<TGraph> Create(std::unique_ptr<arguments> && args) const override{
            auto curr_args = dynamic_cast<typename TCurrentObject::arg_type*>(args.get());
            args.release();
            try{
                std::string new_type = typeid(*curr_args).name();
            }
            catch (std::exception &e){
                throw std::invalid_argument("wrong args");
            }
            return std::make_unique<TCurrentObject>(std::unique_ptr<typename TCurrentObject::arg_type>(curr_args));
        }
    };

    TImpl(){RegisterAll();}

    template <typename T>
    void RegisterCreator(const std::string& type){
        RegisteredCreators[type] = std::make_shared<TCreator<T>>();
    }
    void RegisterAll() {
        RegisterCreator<bipartite_graph>("bipartite");
        RegisterCreator<complete_graph>("complete");
        RegisterCreator<simple_graph>("simple");
        RegisterCreator<weighted_graph>("weighted");
    }
    std::unique_ptr<TGraph> CreateObject(const std::string& type, std::unique_ptr<arguments>&& args) const{
        auto creator = RegisteredCreators.find(type);
        if (creator == RegisteredCreators.end()){
            throw std::invalid_argument("wrong args");
        }
        std::unique_ptr<TGraph> res;
        return creator->second->Create(std::move(args));
    }
    // std::vector<std::string> GetAvailableObjects() const{
    //     std::vector<std::string> result;
    //     for (const auto& creatorPair : RegisteredCreators) {
    //         result.push_back(creatorPair.first);
    //     }
    //     return result;
    // }
};

TFactory::TFactory() : Impl(std::make_unique<TFactory::TImpl>()){}
TFactory::~TFactory(){}

std::unique_ptr<TGraph> TFactory::Create(const std::string& type, std::unique_ptr<arguments>&& args) const
{
    return Impl->CreateObject(type, std::move(args));
}
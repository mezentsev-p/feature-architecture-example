#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include <typeindex>

namespace DI {

class Container {
public:
    template<typename T>
    void Add( std::function<std::shared_ptr<T>()> factory ) {
        _creators[typeid(T)] = [factory]() { return factory(); };
    }

    template<typename T>
    std::shared_ptr<T> Resolve() {
        auto it = _creators.find( typeid(T) );
        return it != _creators.end() ? std::any_cast<std::shared_ptr<T>>( it->second() ) : nullptr;
    }

private:
    std::unordered_map<std::type_index, std::function<std::any()>> _creators;
};

} // namespace DI
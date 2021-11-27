#ifndef GenericFunction_H
#define GenericFunction_H

#include "TypedDagNode.h"
#include <boost/mp11.hpp>

namespace RevBayesCore
{
    class DagNode;
    template <class valueType> class TypedDagNode;

    template <class R, class ...Args>
    class GenericFunction : public TypedFunction<R>
    {
        // This keeps the types, but is harder to iterate over.
        std::tuple<const TypedDagNode<Args>*...>  arguments;

        // This is easier to iterate, but loses the types.
        std::vector<const DagNode*> arguments2;

        // The function we are wrapping.
        R (*func)(Args...);

    public:

        GenericFunction(R (*f)(Args...), const TypedDagNode<Args>*... args):
            TypedFunction<R>(new R),
            arguments({args...}),
            arguments2({args...}),
            func(f)
        {
            boost::mp11::tuple_for_each(arguments, [this](const auto& arg) {this->TypedFunction<R>::addParameter(arg);});
        }

        GenericFunction<R, Args...>*  clone(void) const
        {
            return new GenericFunction<R, Args...>(*this);
        }

        void update(void)
        {
            using namespace boost::mp11;

            auto values = tuple_transform([](auto& node) {return node->getValue();}, arguments);
            *TypedFunction<R>::value = tuple_apply(*func, values);
        }

    protected:
        void swapParameterInternal(const DagNode *oldP, const DagNode *newP)
        {
            auto F2 = [=](auto& arg) {
                using TDN = typename std::remove_reference<decltype(arg)>::type;
                if (arg == oldP)
                    // We have to cast from `const DagNode*` to `const TypedDagNode<T>*`
                    arg = static_cast<TDN>(newP);
            };
            boost::mp11::tuple_for_each(arguments, F2);
        }

    };

    template <class R, class ...Args>
    GenericFunction<R,Args...> generic_function(R (*f)(Args...), const TypedDagNode<Args>*... args)
    {
        return GenericFunction<R,Args...>(f, args...);
    }

    template <class R, class ...Args>
    GenericFunction<R,Args...>* generic_function_ptr(R (*f)(Args...), const TypedDagNode<Args>*... args)
    {
        return new GenericFunction<R,Args...>(f, args...);
    }
}


#endif

#include <coroutine>
#include <iostream>

struct count_to_ten
{
    struct promise_type
    {
        count_to_ten get_return_object() { return {}; };
        std::suspend_always initial_suspend() noexcept { return {}; };
        std::suspend_always final_suspend() noexcept { return {}; };
        void return_void() noexcept { return; }; // so we just return this when we can't return anything else
        void unhandled_exception() { throw; }; // we just throw stuf up the stack
    };
    
    using handle_type = std::coroutine_handle<promise_type>;

    count_to_ten() = default; // just a default constructor;
    //moving needs to be defined
    count_to_ten(count_to_ten&& other) noexcept : handle(other.handle) {
        other.handle = nullptr;
    };
    count_to_ten& operator =(count_to_ten&& other) noexcept {
        if (handle) {
            handle.destroy();
        }

        handle = other.handle;
        other.handle = nullptr;
        return *this;
    }

    ~count_to_ten() {
        if (handle) {
            handle.destroy();
        }
    }

    bool resume() const noexcept {
        if (!handle.done()) {
            handle.resume();
        }
        return !handle.done();
    }

    handle_type handle;

};

// we need a function that uses the counter (which is the generator I belive .. will see later)
count_to_ten count() {
    for (int i = 1; i <= 10; i++) {
        std::cout << "Number: " << i << '\n';
        co_yield i;
    }
};

int main() {

}

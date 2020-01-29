#include <functional>
#include <mutex>

template <typename FUNCTION>
class lazy_val {
private:
  FUNCTION computation;
  mutable bool cache_initialized;
  mutable decltype(computation()) cache;
  mutable std::mutex cache_mutex;

public:
  lazy_val(FUNCTION computation)
    : computation(computation), 
    cache_initialized(false) {}

  lazy_val(lazy_val &&other)
    : computation(std::move(other.computation))
  {}

  operator auto() const -> decltype(computation()) {
    std::unique_lock<std::mutex>lock{ cache_mutex };

    if (!cache_initialized) {
      cache = computation();
      cache_initialized = true;
    }

    return cache;
  }
};

template <typename FUNCTION>
inline lazy_val<FUNCTION> make_lazy_val(FUNCTION &&computation) {
  return lazy_val<FUNCTION>(std::forward<FUNCTION>(computation));
}

struct _make_lazy_val_helper {
  template <typename FUNCTION>
  auto operator - (FUNCTION &&function) const {
    return lazy_val<FUNCTION>(function);
  }
} make_lazy_val_helper;

#define lazy make_lazy_val_helper - [=]
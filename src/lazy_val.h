#include <functional>
#include <string>
#include <iostream>
#include <mutex>
//#include <optional>

template <typename F>
class lazy_val {
private:
  F m_computation;
  mutable bool m_cache_initialized;
  mutable decltype(m_computation()) m_cache;
  mutable std::mutex m_cache_mutex;

public:
  lazy_val(F computation)
    : m_computation(computation)
    , m_cache_initialized(false)
  {
  }

  lazy_val(lazy_val &&other)
    : m_computation(std::move(other.m_computation))
  {
  }

  operator auto() const -> decltype(m_computation()) 
  {
    std::unique_lock<std::mutex>lock{ m_cache_mutex };

    if (!m_cache_initialized) {
      m_cache = m_computation();
      m_cache_initialized = true;
    }

    return m_cache;
  }

  //operator const decltype(m_computation())& F () const
  //{
  //  std::unique_lock<std::mutex>lock{ m_cache_mutex };

  //  if (!m_cache_initialized) {
  //    m_cache = m_computation();
  //    m_cache_initialized = true;
  //  }

  //  return m_cache;
  //}
};

template <typename F>
inline lazy_val<F> make_lazy_val(F &&function)
{
  return lazy_val<F>(std::forward<F>(function));
}

struct _make_lazy_val_helper {
  template <typename F>
  auto operator - (F &&function) const
  {
    return lazy_val<F>(function);
  }
} make_lazy_val_helper;

#define lazy make_lazy_val_helper - [=]
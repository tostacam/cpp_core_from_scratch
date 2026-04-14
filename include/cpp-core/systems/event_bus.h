class event_bus {
public:
  template <typename Event, typename Func>
  void subscribe(Func&& f);

  template <typename Event>
  void emit(const Event& e);
};

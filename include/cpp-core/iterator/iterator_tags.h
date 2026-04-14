// std::iterator_tags
// - https://saco-evaluator.org.za/docs/cppreference/en/cpp/iterator/iterator_tags.html

#pragma once

namespace cpp_core{

/* tag hierarchy */
struct input_iterator_tag {};
struct forward_iterator_tag : input_iterator_tag {};
struct bidirectional_iterator_tag : forward_iterator_tag {};
struct random_access_iterator_tag : bidirectional_iterator_tag {};

}

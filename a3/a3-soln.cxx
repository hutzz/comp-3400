#include <algorithm>
#include <iostream>   
#include <istream>
#include <iterator>
#include <optional>   
#include <ostream>    
#include <random>
#include <ranges>
#include <vector>
#include "a2-soln.hxx"
#include "a2-soln.hxx"

using cards = std::vector<card>;

struct all_card_faces_begin_t final { };
constexpr all_card_faces_begin_t all_card_faces_begin{};
struct all_card_suits_begin_t final { };
constexpr all_card_suits_begin_t all_card_suits_begin{};

class all_card_faces_iterator {
    private:
        std::optional<card_face> f_;
    public:
        using value_type = card_face const;
        using reference = value_type&;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::input_iterator_tag;

        all_card_faces_iterator() = default;
        all_card_faces_iterator(all_card_faces_begin_t) : f_(card_face::ace) {};
        all_card_faces_iterator(const all_card_faces_iterator&) = default;
        all_card_faces_iterator& operator=(const all_card_faces_iterator&) = default;
        std::strong_ordering operator<=> (const all_card_faces_iterator&) const noexcept = default;

        reference operator*() const {
            return *f_;
        }
        all_card_faces_iterator operator++(int) {
            all_card_faces_iterator tmp(*this);
            this->operator++();
            return tmp;
        }
        all_card_faces_iterator& operator++() {
            if (f_.has_value()) {
                if (f_ == card_face::king) {
                    f_ = std::nullopt;
                } else {
                    using int_type = std::underlying_type<card_face>::type;
                    auto f_value = static_cast<int_type>(*f_);
                    f_value++;
                    f_ = static_cast<card_face>(f_value);
                }
            }
            return *this;
        }
}; 
static_assert(std::input_iterator<all_card_faces_iterator>);

class all_card_faces {
    public:
        all_card_faces_iterator begin() const {
            return all_card_faces_iterator{all_card_faces_begin};
        }
        all_card_faces_iterator end() const {
            return all_card_faces_iterator{};
        }
};
static_assert(std::ranges::range<all_card_faces>);

class all_card_suits_iterator {
    private:
        std::optional<card_suit> s_;
    public:
        using value_type = card_suit const;
        using reference = value_type&;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::input_iterator_tag;
        
        all_card_suits_iterator() = default;
        all_card_suits_iterator(all_card_suits_begin_t) : s_(card_suit::clubs) {};
        all_card_suits_iterator(const all_card_suits_iterator&) = default;
        all_card_suits_iterator& operator=(const all_card_suits_iterator&) = default;
        std::strong_ordering operator<=> (const all_card_suits_iterator&) const noexcept = default;

        reference operator*() const {
            return *s_;
        }
        all_card_suits_iterator& operator++() {
            if (s_.has_value()) {
                if (s_ == card_suit::diamonds) {
                    s_ = std::nullopt;
                } else {
                    using int_type = std::underlying_type<card_suit>::type;
                    auto f_value = static_cast<int_type>(*s_);
                    f_value++;
                    s_ = static_cast<card_suit>(f_value);
                }
            }
            return *this;
        }
        all_card_suits_iterator operator++(int) {
            all_card_suits_iterator tmp(*this);
            this->operator++();
            return tmp;
        }
}; 
static_assert(std::input_iterator<all_card_suits_iterator>);

class all_card_suits {
    public:
        all_card_suits_iterator begin() const {
            return all_card_suits_iterator{all_card_suits_begin};
        }
        all_card_suits_iterator end() const {
            return all_card_suits_iterator{};
        }
};

cards generate_full_deck() {
    cards retval;
    for (card_face f : all_card_faces{})
        for (card_suit s : all_card_suits{})
            retval.push_back(card{ f, s });
    return retval;
}

cards generate_different_deck() {
    cards retval;
    for (card_face f : all_card_faces{}) {
        if (f == card_face::two || f == card_face::three || f == card_face::four || f == card_face::five || f == card_face::six) {
            continue;
        }
        for (card_suit s : all_card_suits{}) {
            retval.push_back(card{ f, s });
        }
    }
    return retval;
}

std::ostream& operator<<(std::ostream& os, cards const& d) {
    for (const card& c : d) {
        os << c.face << c.suit << ' ';
    }
    return os;
}

bool is_red(const card& c) {
    return c.suit == card_suit::hearts || c.suit == card_suit::diamonds;
}

bool is_club(const card& c) {
    return c.suit == card_suit::clubs;
}

cards select_n(cards const& cs, std::size_t n) {
    static auto rand_eng = std::default_random_engine(std::random_device{}());
    cards retval;
    std::sample(cs.begin(), cs.end(), std::back_inserter(retval), n, rand_eng);
    return retval;
}

int main() {
    std::cout << generate_full_deck() << '\n';
    std::cout << generate_different_deck() << '\n';
}


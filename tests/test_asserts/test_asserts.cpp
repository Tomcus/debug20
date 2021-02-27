#include "debug20/assert.hpp"
#include <cassert>
#include <cstring>
#include <compare>

struct modern_comparable {
    int a;
    auto operator<=>(const modern_comparable& other) const = default;
};

template <typename A, typename B>
void test_equality(const A& a, const B& b) {
    d20::assert_equals(a, b, "This shouldn't cause problems");
    int line = 0;
    try {
        line = __LINE__; d20::assert_not_equals(a, b, "This should be thrown");
        assert(false);
    } catch (const d20::exception& e) {
        #ifndef SOURCE_LOCATION_DUMMY
        assert(e.where().line() == line);
        #endif//SOURCE_LOCATION_DUMMY
        assert(strcmp(e.what(), "This should be thrown") == 0);
    } catch (const std::exception& e) {
        assert(strcmp(e.what(), "This should be thrown") == 0);
    }
}

template <typename A, typename B>
void test_not_equality(const A& a, const B& b) {
    d20::assert_not_equals(a, b, "This shouldn't cause problems");
    int line = 0;
    try {
        line = __LINE__; d20::assert_equals(a, b, "This should be thrown");
        assert(false);
    } catch (const d20::exception& e) {
        #ifndef SOURCE_LOCATION_DUMMY
        assert(e.where().line() == line);
        #endif//SOURCE_LOCATION_DUMMY
        assert(strcmp(e.what(), "This should be thrown") == 0);
    } catch (const std::exception& e) {
        assert(strcmp(e.what(), "This should be thrown") == 0);
    }
}

template <typename A, typename B>
void test_lesser_then(const A& a, const B& b) {
    d20::assert_lesser_then(a, b, "This shouldn't cause problems");
    int line = 0;
    try {
        line = __LINE__; d20::assert_greater_equal(a, b, "This should be thrown");
        assert(false);
    } catch (const d20::exception& e) {
        #ifndef SOURCE_LOCATION_DUMMY
        assert(e.where().line() == line);
        #endif//SOURCE_LOCATION_DUMMY
        assert(strcmp(e.what(), "This should be thrown") == 0);
    } catch (const std::exception& e) {
        assert(strcmp(e.what(), "This should be thrown") == 0);
    }
}

template <typename A, typename B>
void test_greater_then(const A& a, const B& b) {
    d20::assert_greater_then(a, b, "This shouldn't cause problems");
    int line = 0;
    try {
        line = __LINE__; d20::assert_lesser_equal(a, b, "This should be thrown");
        assert(false);
    } catch (const d20::exception& e) {
        #ifndef SOURCE_LOCATION_DUMMY
        assert(e.where().line() == line);
        #endif//SOURCE_LOCATION_DUMMY
        assert(strcmp(e.what(), "This should be thrown") == 0);
    } catch (const std::exception& e) {
        assert(strcmp(e.what(), "This should be thrown") == 0);
    }
}

void test_strings() {
    std::string a{"Testing string"};
    test_equality(a, a);

    test_not_equality(a, std::string("Different String"));
}

template<typename T>
void test_ints(T a) {
    test_equality(a, a);
    if (a != 0)
        test_not_equality(a, -a);
    else
        test_not_equality(a, a+1);
    test_lesser_then(a, a + 10);
    test_greater_then(a, a - 10);
}

template<typename T>
void test_floats(T a) {
    test_lesser_then(a, a + 10.0);
    test_greater_then(a, a - 10.0l);
}

template<typename A, typename B>
void test_structs() {
    test_equality(A{15}, B{15});
    test_not_equality(A{30}, B{-7});
    test_lesser_then(A{80}, B{81});
    test_greater_then(A{97}, B{13});
    test_equality(B{15}, A{15});
    test_not_equality(B{30}, A{-7});
    test_lesser_then(B{80}, A{81});
    test_greater_then(B{97}, A{13});
}

int main() {
    test_strings();
    test_ints<int>(42);
    test_ints<int8_t>(0);
    test_ints<uint64_t>(69);
    test_ints<int16_t>(-420);
    test_floats<double>(0.0);
    test_floats<double>(-20.0);
    test_floats<float>(20.0);
    test_structs<modern_comparable, modern_comparable>();
}
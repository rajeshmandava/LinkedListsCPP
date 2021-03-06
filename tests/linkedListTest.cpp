/*

File: linkedListTest.cpp

Copyright (c) 2018 Alexander DuPree

This software is released as open source through the MIT License

Authors: Alexander DuPree, Jacob Bickle

https://github.com/AlexanderJDupree/LinkedListsCPP

*/

#include <vector>
#include "catch.hpp"
#include "linkedList.hpp"

TEST_CASE("Constructing Nodes", "[node], [constructors]")
{
    SECTION("Default Construction")
    {
        Node<int> node;

        REQUIRE(*node.data() == int());
        REQUIRE(node.next() == nullptr);
    }
    SECTION("Overloaded Construction")
    {
        Node<char> node('n');

        REQUIRE(*node.data() == 'n');
        REQUIRE(node.next() == nullptr);
    }
    SECTION("Copy construction")
    {
        Node<int> node1(5);
        Node<int> node2(node1);

        REQUIRE(*node2.data() == 5);
        REQUIRE(node2.next() == nullptr);
    }
}

TEST_CASE("Using Mutators to manipulate members", "[node], [mutators]")
{
    SECTION("Manipulate data member")
    {
        Node<float> node1;
        Node<char>  node2;
        Node<int>   node3;

        node1.data(3.545);
        node2.data('A');
        node3.data(77);

        REQUIRE(*node1.data() == float(3.545));
        REQUIRE(*node2.data() == 'A');
        REQUIRE(*node3.data() == 77);
    }
    SECTION("Manipulate next Node member")
    {
        Node<int> node1;
        Node<int> node2;

        node1.next(&node2);

        REQUIRE(node1.next() == &node2);
    }
}

TEST_CASE("Link Nodes and access linked data members", "[node], [linked]")
{
    SECTION("Traverse a link to access a different Nodes data")
    {
        Node<int> node1(1);
        Node<int> node2(7);

        node1.next(&node2);

        REQUIRE(*node1.next()->data() == 7);
    }
}

TEST_CASE("Constructing Linked Lists instances", "[linkedLists], [constructors]")
{
    SECTION("Default Construction")
    {
        LinkedList<int> list;

        REQUIRE(list.empty() == true);
    }
    SECTION("Fill Construction")
    {
        LinkedList<int> list(4, 100);

        REQUIRE(list.size() == 4);
        for (auto& element : list)
        {
            REQUIRE(element == 100);
        }
    }
    SECTION("Copy construction")
    {
        LinkedList<int> origin(4, 100);
        LinkedList<int> copy(origin);

        REQUIRE(origin == copy);
    }
    SECTION("Copy construction on empty list")
    {
        LinkedList<int> origin;
        LinkedList<int> copy(origin);

        REQUIRE(copy.empty() == true);
    }
    SECTION("Initializer List construction")
    {
        LinkedList<int> list {1, 2, 3, 4, 5};

        int i = 1;
        for (auto& element : list)
        {
            REQUIRE(element == i);
            ++i;
        }
    }
    SECTION("Empty initializer list")
    {
        LinkedList<int> list {};

        REQUIRE(list.empty());
    }
    SECTION("Range based construction")
    {
        std::vector<int> nums = { 1, 2, 3, 4, 5 };
        LinkedList<int> list(nums.begin(), nums.end());

        int i = 1;
        for (auto& element : list)
        {
            REQUIRE(element == i);
            ++i;
        }
    }
    SECTION("Ranged based construction on empty vector")
    {
        std::vector<int> nums;
        LinkedList<int> list(nums.begin(), nums.end());

        REQUIRE(list.empty());
    }
}

TEST_CASE("Pushing elements to the front of the list", "[linkedLists], [modifiers], [iterators]")
{
    SECTION("Push one element")
    {
        LinkedList<int> list;

        list.push_front(9);

        REQUIRE(*list.begin() == 9);

    }
    SECTION("Push multiple elements")
    {
        LinkedList<char> list;

        list.push_front('A');
        list.push_front('B');
        list.push_front('C');

        REQUIRE(*list.begin() == 'C');
    }
}

TEST_CASE("Pushing elements to the end of the list", "[linkedLists], [modifiers], [iterators]")
{
    SECTION("Push one element")
    {
        LinkedList<int> list;

        list.push_back(5);

        REQUIRE(*list.begin() == 5);
        
    }

    SECTION("Push Multiple elements")
    {
        LinkedList<char> list;
        
        list.push_back('X');
        list.push_back('Y');
        list.push_back('Z');

        char character = 'X';
        for (auto& element : list)
        {
            REQUIRE(element == character);
            character++;
        }
    }
}

TEST_CASE("Popping front elements")
{
    SECTION("Pop front of populated list")
    {
        LinkedList<int> list {1, 2, 3, 4};
        list.pop_front();

        int i = 2;
        for (auto& element : list)
        {
            REQUIRE(i == element);
            ++i;
        }

    }
    SECTION("Pop front of populated list with argument")
    {
        LinkedList<int> list {1, 2, 3, 4};

        int x(0);
        list.pop_front(x);

        REQUIRE(x == 1);
        
        x = 2;
        for (auto& element : list)
        {
            REQUIRE(x == element);
            ++x;
        }
    }
    SECTION("Pop front of empty list")
    {
        LinkedList<int> list;

        list.pop_front();

        REQUIRE(list.empty());
    }
    SECTION("Pop front of empty list with arguement")
    {
        LinkedList<int> list;

        int x = 2;
        list.pop_front(x);

        REQUIRE(list.empty());
        REQUIRE(x == 2);
    }
}

TEST_CASE("Popping back elements")
{
    SECTION("Pop back of populated list")
    {
        LinkedList<int> list {1, 2, 3, 4};
        list.pop_back();

        int i = 1;
        for (auto& element : list)
        {
            REQUIRE(i == element);
            ++i;
        }
        REQUIRE(i != 5);

    }
    SECTION("Pop back of populated list with argument")
    {
        LinkedList<int> list {1, 2, 3, 4};

        int x(0);
        list.pop_back(x);

        REQUIRE(x == 4);
        
        x = 1;
        for (auto& element : list)
        {
            REQUIRE(x == element);
            ++x;
        }
    }
    SECTION("Pop back of empty list")
    {
        LinkedList<int> list;

        list.pop_back();

        REQUIRE(list.empty());
    }
    SECTION("Pop back of empty list with arguement")
    {
        LinkedList<int> list;

        int x = 2;
        list.pop_back(x);

        REQUIRE(list.empty());
        REQUIRE(x == 2);
    }
}

TEST_CASE("Inserting an element in the list", "[linkedLists], [modifiers], [iterators]")
{
    SECTION("Inserting in the middle (at index 2) of a populated list")
    {
        LinkedList<int> list {2, 9, 6, 10};

        LinkedList<int>::iterator It = list.begin();
        
        It += 2;

        list.insert(It, 5);
        It = list.begin();

        It += 3;
       
        REQUIRE(*It == 5);
    }
    SECTION("Inserting at the end of a populated list")
    {
        LinkedList<int> list {2, 9};
        
        LinkedList<int>::iterator It = list.begin();

        ++It;

        list.insert(It, 5);

        ++It;

        REQUIRE(*It == 5);
    }
    SECTION("Inserting at the beginning of a populated list")
    {
        LinkedList<int> list {2, 3, 4};

        LinkedList<int>::iterator It = list.begin();

        list.insert(It, 1);

        ++It;

        REQUIRE(*It == 1);
    }
    SECTION("Inserting into an empty list")
    {
        LinkedList<char> list;

        LinkedList<char>::iterator It = list.begin();

        list.insert(It, 'Z');

        REQUIRE(*list.begin() == 'Z');
    }
    SECTION("Inserting using a ranged based iterator")
    {
        std::vector<int> nums { 2, 3, 4 };
        LinkedList<int> list { 1, 5 };

        list.insert(list.cbegin(), nums.begin(), nums.end());

        int i = 1;
        for (auto& element : list)
        {
            REQUIRE(element == i);
            ++i;
        }

    }
    SECTION("Inserting using fill method")
    {
        LinkedList<char> list;
        list.insert(list.cbegin(), 4, 'Z');

        for(auto& element : list)
        {
            REQUIRE(element == 'Z');
        }
    }
}

TEST_CASE("Using multiple modifiers on a list", "[linkedLists], [modifiers], [iterators]")
{
    SECTION("push back and push front")
    {
        LinkedList<int> list;

        list.push_back(2);
        list.push_back(3);
        list.push_front(1);

        int i = 1;
        for (auto& it : list)
        {
            REQUIRE(it == i);
            ++i;
        }
    }
}

TEST_CASE("Erasing portions of a list", "[linkedLists], [modifiers], [iterators]")
{
    SECTION("Erase one element of a populated list")
    {
        LinkedList<char> list { 'A', 'B', 'C', 'D'};

        LinkedList<char>::iterator It = list.begin();

        ++It;

        It = list.erase(It);

        REQUIRE(list.size() == 3);
        REQUIRE(*It == 'C');
    }
    SECTION("Erase the last element of a populated list")
    {
        LinkedList<char> list { 'A', 'B', 'C'};
        LinkedList<char>::iterator It;

        It = list.begin();
        ++It;
        ++It;
        list.erase(It);

        REQUIRE(list.size() == 2);
        REQUIRE(It == list.end());
    }
    SECTION("Erase the only element in a list")
    {
        LinkedList<char> list;

        list.push_back('A');

        LinkedList<char>::iterator It = list.begin();

        It = list.erase(It);

        REQUIRE(list.empty());
        REQUIRE(It == list.end());
    }
    SECTION("Erase an empty list")
    {
        LinkedList<char> list;

        LinkedList<char>::iterator it = list.begin();
        list.erase(it);

        REQUIRE(list.empty());
    }
    SECTION("Erase multiple elements of a populated list")
    {
        LinkedList<char> list { 'A', 'B', 'C', 'D'};
        LinkedList<char>::iterator It1,
                                   It2;

        It1 = list.begin();
        It2 = list.begin();
        ++It2;
        ++It2;

        It1 = list.erase(It1, It2);

        REQUIRE(list.size() == 2);
        REQUIRE(*It1 == 'C');
        REQUIRE(*It2 == 'C');
    }
    SECTION("Erase the entire list")
    {
        LinkedList<char> list { 'A', 'B', 'C'};
        LinkedList<char>::iterator It1,
                                   It2;

        It1 = list.begin();
        It2 = list.end();

        list.erase(It1, It2);

        REQUIRE(list.empty());
        REQUIRE(It1 == list.end());
        REQUIRE(It2 == list.end());
    }
    SECTION("Erase a portion of list with two of the same iterator")
    {
        LinkedList<char> list { 'A', 'B', 'C', 'D'};
        LinkedList<char>::iterator it1,
                                   it2;
        
        it1 = list.begin();
        ++it1;
        
        it2 = list.begin();
        ++it2;

        it1 = list.erase(it1, it2);

        REQUIRE(*it1 == 'B');
        REQUIRE(*it2 == 'B');
    }
    SECTION("Erase an empty list with iterators begin() and end()")
    {
        LinkedList<char> list;
        LinkedList<char>::iterator first,
                                  last;
        first = list.begin();
        last = list.end();

        list.erase(first, last);

        REQUIRE(list.empty());
    }
}

TEST_CASE("Clearing the list", "[linkedLists], [modifiers]")
{
    SECTION("Clearing a populated list")
    {
        LinkedList<int> list {1, 2, 3};

        list.clear();
        REQUIRE(list.empty());
    }
    SECTION("Clearing a list with one element")
    {
        LinkedList<int> list;

        list.push_back(1);

        list.clear();
        REQUIRE(list.empty());
    }
    SECTION("Clearing an empty list")
    {
        LinkedList<int> list;

        list.clear();
        REQUIRE(list.empty());
    }
}

TEST_CASE("Using iterators for iteration", "[linkedLists], [iterators]")
{
    SECTION("Standard for loop with prefix increment")
    {
        LinkedList<int> list { 0, 1, 2 };

        int i = 0;
        LinkedList<int>::iterator it;

        for (it = list.begin(); it != list.end(); ++it)
        {
            REQUIRE(*it == i);
            ++i;
        }
       
    }
    SECTION("Standard for loop with postfix increment")
    {
        LinkedList<int> list { 0, 1, 2 };

        int i = 0;
        LinkedList<int>::iterator it;

        for (it = list.begin(); it != list.end(); it++)
        {
            REQUIRE(*it == i);
            ++i;
        }
    }
    SECTION("Ranged based for loop")
    {
        LinkedList<int> list { 0, 1, 2 };

        int i = 0;
        for(auto iter : list)
        {
            REQUIRE(iter == i);
            ++i;
        }
    }
    SECTION("Using const_iterator in standard for loop with prefix increment")
    {
        const LinkedList<int> list(4, 100);

        LinkedList<int>::const_iterator it = list.cbegin();

        for (it = list.cbegin(); it != list.cend(); ++it)
        {
            REQUIRE(*it == 100);
        }
    }
    SECTION("Using const_iterator in standard for loop with postfix increment")
    {
        const LinkedList<int> list(4, 100);

        LinkedList<int>::const_iterator it = list.cbegin();

        for (it = list.cbegin(); it != list.cend(); it++)
        {
            REQUIRE(*it == 100);
        }
    }
    SECTION("Using ranged based for loop on const linkedlist")
    {
        const LinkedList<int> list(5,25);

        for (const auto& element : list)
        {
            REQUIRE(element == 25);
        }
    }
}

TEST_CASE("Using iterator arithmetic on iterators", "[iterators]")
{
    SECTION("Using the += operator to for incrementation")
    {
        LinkedList<int> list { 1, 2, 3 };
        
        LinkedList<int>::iterator it = list.begin();

        it += 2;

        REQUIRE(*it == 3);
    }
}

TEST_CASE("Test size() function", "[linkedLists], [size], [capacity]")
{
    SECTION("Empty linked list")
    {
        LinkedList<int> list;

        REQUIRE(list.size() == 0);
    }
    SECTION("A populated linked list")
    {
        LinkedList<char> list { 'A', 'B', 'C' };

        REQUIRE(list.size() == 3);
    }
   
}

TEST_CASE("Test comparison operators", "[linkedLists], [comparison], [operators]")
{
    SECTION("Two identical linked lists")
    {
        LinkedList<int> left(5, 20);
        LinkedList<int> right(5, 20);

        REQUIRE(left == right);
    }
    SECTION("Two different linked lists")
    {
        LinkedList<int> left(5, 20);
        LinkedList<int> right;

        REQUIRE(left != right);
    }
}

TEST_CASE("Test assignment operator", "[linkedLists], [comparison], [operators]")
{
    SECTION("Two unique lists")
    {
        LinkedList<int> origin { 1, 2, 3, 4, 5 };
        LinkedList<int> copy { 6, 7, 8 };

        copy = origin;

        REQUIRE(copy == origin); 
    }
    SECTION("Two empty lists")
    {
        LinkedList<int> origin;
        LinkedList<int> copy;

        copy = origin;

        REQUIRE(copy == origin);
    }
}

TEST_CASE("Reversing the order of a list", "[linkedLists], [operations], [reverse]")
{
    SECTION("A populated list")
    {
        LinkedList<int> list { 5, 4, 3, 2, 1 };

        list.reverse();

        int i = 1;

        for(auto& element : list)
        {
            REQUIRE(element == i);
            ++i;
        }
    }
    SECTION("A list with one element")
    {
        LinkedList<int> list {1};

        list.reverse();

        for (auto& element : list)
        {
            REQUIRE(element == 1);
        }
    }
    SECTION("An empty list")
    {
        LinkedList<int> list;

        list.reverse();

        REQUIRE(list.empty());
    }
}

TEST_CASE("Using unique() to remove duplicate elements", "[linkedLists], [operations], [unique]")
{
    SECTION("A populated list")
    {
        LinkedList<int> list { 1, 2, 1, 3, 3, 4, 5, 4, 6, 5, 5 };

        list.unique();

        int i = 1;
        for (auto& element : list)
        {
            REQUIRE(element == i);
            ++i;
        }
    }
    SECTION("An empty list")
    {
        LinkedList<int> list;

        list.unique();

        REQUIRE(list.empty());
    }
}

TEST_CASE("Using remove to erase specific elements", "[linkedLists], [operations], [remove]")
{
    SECTION("A populated list")
    {
        LinkedList<char> list { 'A', 'Z', 'Z', 'B', 'Z', 'C', 'Z' };

        list.remove('Z');

        char letter = 'A';
        for (auto& element : list)
        {
            REQUIRE(element == letter);
            ++letter;
        }
    }
    SECTION("An empty list")
    {
        LinkedList<int> list;

        list.remove(0);

        REQUIRE(list.empty());
    }
}

TEST_CASE("Using remove_if to erase elements fulfilling a predicate", "[linkedLists], [operations], [remove]")
{
    SECTION("A populated list")
    {
        LinkedList<int> list { 1, 7, 2, 3, 9, 10, 6, 6, 4, 5 };

        list.remove_if([](const int& value) { return value > 5; });

        int i = 1;
        for(auto& element : list)
        {
            REQUIRE(element == i);
            ++i;
        }

    }
    SECTION("An empty list")
    {
        LinkedList<int> list;

        list.remove_if([](const int& value) { return value > 5; });

        REQUIRE(list.empty());
    }
}

TEST_CASE("Using find to locate a specific element", "[linkedLists], [operations], [find]")
{
    SECTION("A populated list")
    {
        LinkedList<int> list { 1, 2, 3, 4, 5 };

        REQUIRE(*list.find(3) == 3);
    }
    SECTION("An empty list")
    {
        LinkedList<int> list;
        REQUIRE(list.find(3) == list.end());
    }
}

TEST_CASE("Sorting a list", "[linkedLists], [operations], [sort]")
{
    SECTION("A sorted list")
    {
        LinkedList<int> list {1, 2, 3, 4, 5, 6, 7, 8, 9};

        list.sort();

        int i = 1;
        for(auto& element : list)
        {
            REQUIRE(element == i);
            ++i;
        }
    }
    SECTION("An unsorted list")
    {
        LinkedList<int> list {9, 8, 7, 6, 5, 4, 3, 2, 1};

        list.sort();

        int i = 1;
        for(auto& element : list)
        {
            REQUIRE(element == i);
            ++i;
        }
    }
    SECTION("An empty list")
    {
        LinkedList<int> list;
        list.sort();
        REQUIRE(list.empty());
    }
}

TEST_CASE("Sorting a list with a special comparator", "[linkedLists], [operations], [sort]")
{
    SECTION("A sorted list, and a reverse comparator")
    {
        LinkedList<int> list {1, 2, 3, 4, 5, 6, 7, 8, 9};

        list.sort([](const int& val1, const int& val2){return val1 > val2;});

        int i = 9;
        for(auto& element : list)
        {
            REQUIRE(element == i);
            --i;
        }
    }
    SECTION("An unsorted list, and a reverse comparator")
    {
        LinkedList<int> list {9, 8, 7, 6, 5, 4, 3, 2, 1};

        list.sort([](const int& val1, const int& val2){return val1 > val2;});

        int i = 9;
        for(auto& element : list)
        {
            REQUIRE(element == i);
            --i;
        }
    }
    SECTION("An empty list")
    {
        LinkedList<int> list;

        list.sort([](const int& val1, const int& val2){return val1 > val2;});

        REQUIRE(list.empty());
    }
}

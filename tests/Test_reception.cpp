/*
** EPITECH PROJECT, 2020
** undefined
** File description:
** Test
*/

#include "Tests.hpp"

Test(test_recepetion, reception)
{
    Reception test;

    cr_assert_eq(test.createKitchen(), 0);
    cr_assert_eq(test.createKitchen(), 1);
    cr_assert_eq(test.createKitchen(), 2);
}
RPG Lab #1

# Purpose

Inheritance is a powerful and integral component of object-oriented programming. Hierarchies existing in the real world can be easily modeled using inheritance; this practice can greatly simplify code.

This, and all 235 assignments will be verified by a TA-written test driver.

# Key Reading

CS 142 Text

# Background

A major part of modern computer use is video games, and it's all fun and games until someone has to program them. Even the most simple video games, like the ancient Pong, require a lot of code to work properly. Many of the most basic concepts in programming appear in simple text-based role playing games, or RPGs.

For old time's sake, a friend has hired you to help write just such a game for his new company. Your first assignment is to implement the fighters awaiting battle at an arena. With three kinds of fighters and many stats for each fighter, you will need all of your previous programming experience to do well and keep your new job.

If terms like "hit points", "stats", or "damage" are unfamiliar within an RPG setting, please speak with a TA.

# Requirements

## Overview

You will need the files in this c9.io workspace to complete this lab:

## Part 1 - Construct the Arena (3 points)

* Make a class Arena that inherits from the ArenaInterface provided; the arena is simply a collection of fighters, each with a unique name.  You should fill in each of the virtual methods included in the ArenaInterface class.
* For Part 1 only, you may assume all strings passed to the arena's adding method will be of the correct format
* For Part 1 only, you may assume all strings passed to the arena's getting and removing methods will be names already existing in the arena

## Part 2 - Let the Battle Begin (3 points)

* Make a class that inherits from the FighterInterface provided; details about abilities, stats, and more can be found in the FighterInterface
* For Part 2, the test driver will not call your useAbility() or regenerate() methods, so it is possible to receive credit for Part 2 without these methods being complete
* Completion of Part 1 is required to submit Part 2

## Part 3 - Fortify the Walls (2 points)

* Make adding new fighters to your arena robust; this involves rejecting any string that is not of the correct format or that would add a duplicate name to the arena
* Make getting and removing existing fighters in your arena robust
* Completion of Part 1 is required to submit Part 3

## Part 4 - Let Me Show You My True Form... (6 points, 2 points per fighter type)

* Add functionality to the useAbility() method and the regenerate() method for each fighter type
* Completion of Parts 1 and 2 is required to submit Part 4

## UML design document. (1 point)

* Refer to page 113 in the book for an example.
* Please bring when asking TAs questions.
* You must bring a HARD COPY to the TAs when you pass off. (There is a printer upstairs if you made a digital copy)

# Requirement Notes

## General

* You are required to write a seperate '.cpp' and '.h' for each class you implement.
* You are required to use inheritance to implement the three kinds of fighters. * The TAs reserve the right to deny pass off to programs utilizing inheritance incorrectly or that do not have the expected inheritance hierarchy.
Unless otherwise instructed, use standard integer division for all division operations specified. This means all fractional results should be rounded down (ex: 17/10 = 1).
* You should not call a Fighter's useAbility() function in the getDamage() function, the test driver will handle all function calls for the Fighters.
It is highly recommended to use the standard vector as the underlying representation for the Arena class. You are welcome to use other underlying structures, but those will be covered later in the course.

## Fighter String Format

* Fighters are represented as strings when added to the arena. The following format is expected:
** (name) (type) (maximum hit points) (strength) (speed) (magic)
** Example: Xephos A 200 13 21 10

* The name is a single word; the type is a single capital letter ((R)obot, (A)rcher, or (C)leric); the remaining four stats are positive integers.
Fighting




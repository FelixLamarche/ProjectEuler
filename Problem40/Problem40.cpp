// Problem 40  Champernowne's Constant
// When concatanating all integers like 12345678910111213...
// What is the product of the 1st, 10th, 100th, 1000th, 10000th, 100000th, 1000000th digit

// I calculated this manually
// d1 = 1,
// d10 = 1,
// d100 = 5,
// d1000 = 3
// d10000 = 7
// d100000 = 2
// d1000000 = 1

// Digits are divided as such:
// 1..9 -> digits [1, 9]
// 10..99 -> digits [10, 189]
// 100..999 -> digits [190, 2889]
// 1000..9999 -> digits [2890, 38889]
// 10000..99999 -> digits [38890, 488889]
// 100000..999999 -> digits [488890, 5888889]

// The digits can calculated by adding the required amount of digits to reach what number contains the correct digit.
// Then just multiply all of them.
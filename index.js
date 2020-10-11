/*
This is the javascript file that will include natice addon
written in c (simple but illustrative of the core concept)
*/

const addOn = require('./build/Release/module');
const valueToBeMultipliedBy17 = 100;

const resultFromAddOn = addOn.my_function(valueToBeMultipliedBy17);
console.log('--- Result ----- ', resultFromAddOn);

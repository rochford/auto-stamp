var plate = require('bindings')('plate');

plate.initialize();

console.log("plate.calculate('AA', 0, 0, 2, 2)");
var buf = plate.calculate("AA", 0, 0, 2, 2);
console.log("result: " + buf.toString());

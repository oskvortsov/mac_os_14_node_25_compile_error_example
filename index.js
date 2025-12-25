// Load the compiled native module
const addon = require('./build/Release/addon');

console.log('=== NAN Module Usage Examples ===\n');

// 1. Simple Hello World function
console.log('1. Hello World:');
console.log(addon.hello());
console.log();

// 2. Synchronous addition of numbers
console.log('2. Adding two numbers (5 + 3):');
console.log('Result:', addon.add(5, 3));
console.log();

// 3. Using MyObject class
console.log('3. Working with MyObject class:');
const obj = new addon.MyObject(42);
console.log('Initial value:', obj.getValue());
obj.setValue(100);
console.log('After modification:', obj.getValue());
console.log();

// 4. Asynchronous operation
console.log('4. Asynchronous operation (waiting 1 second):');
console.log('Starting async operation...');
addon.asyncOperation(1000, (err, result) => {
  if (err) {
    console.error('Error:', err);
  } else {
    console.log('Result:', result);
  }
  console.log('\n=== All examples completed ===');
});


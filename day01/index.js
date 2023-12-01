import { open } from 'node:fs/promises';

const numbersAsStrings = ['0', '1', '2', '3', '4', '5', '6' , '7', '8', '9', 'zero', 'one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine'];

function findMatchAtIndex(input, index) {
  for (let i = 0; i < numbersAsStrings.length; i++) {
    const ns = numbersAsStrings[i];

    const substr = input.substring(index, Math.min(input.length, index + ns.length));
    if (substr === ns) {
      if (i < 10) {
        return ns;
      } else {
        return numbersAsStrings[i - 10];
      }
    }
  }
}

function calculateNumberFromLine(input) {
  let numberAsStr = "";

  for (let i = 0; i < input.length; i++) {
    const match = findMatchAtIndex(input, i);
    if (match) {
      numberAsStr += match;
      break;
    }
  }

  for (let i = input.length - 1; i >= 0; i--) {
    const match = findMatchAtIndex(input, i);
    if (match) {
      numberAsStr += match;
      break;
    }
  }

  return parseInt(numberAsStr, 10);
}

(async function doIt() {
  let total = 0;

  const file = await open(process.argv[2]);

  for await (const line of file.readLines()) {
    total += calculateNumberFromLine(line);
  }

  console.log(total);
})();

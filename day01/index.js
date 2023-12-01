import { open } from 'node:fs/promises';

function calculateNumberFromLine(input) {
  let numberAsStr = "";

  for (let i = 0; i < input.length; i++) {
    if (input[i].match(/\d/)) {
      numberAsStr += input[i];
      break;
    }
  }

  for (let i = input.length - 1; i >= 0; i--) {
    if (input[i].match(/\d/)) {
      numberAsStr += input[i];
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


import { open } from 'node:fs/promises';

// which games would have been possible if the bag contained only 12 red cubes, 13 green cubes, and 14 blue cubes
const validCounts = {
  red: 12,
  green: 13,
  blue: 14
};

export function parseGameNumberForLine(line) {
  return line.match(/Game (?<gameNumber>\d+):/).groups.gameNumber;
}

export function gameIsValid(line) {
  let runs = line.replace(/Game \d+: /, "").split(";");
  for (const run of runs) {
    for (const color of Object.keys(validCounts)) {
      const r = new RegExp(`(?<count>\\d+) ${color}`);

      const currentCount = run.match(r)?.groups?.count ?? 0;

      if (currentCount > validCounts[color]) {
        // console.log(`invalid because ${currentCount} ${color} balls is greater than the possible count of ${validCounts[color]} ${color} balls`);
        return false;
      }
    }
  }

  return true;
}

async function doIt() {
  let total = 0;

  const file = await open(process.argv[2]);

  for await (const line of file.readLines()) {
    if (gameIsValid(line)) {
      total += parseInt(
        parseGameNumberForLine(line),
        10
      );
    }
  }

  console.log(total);
};

const colors = ["red", "green", "blue"];

export function calculateMinCubes(line) {
  let runs = line.replace(/Game \d+: /, "").split(";");

  let minCubes = {
    red: 0,
    green: 0,
    blue: 0
  }

  for (const run of runs) {
    for (const color of colors) {
      const r = new RegExp(`(?<count>\\d+) ${color}`);
      const currentCount = run.match(r)?.groups?.count ?? 0;

      minCubes[color] = Math.max(currentCount, minCubes[color]);
    }
  }

  return minCubes;
}

export function calculatePower(line) {
  const minCubes = calculateMinCubes(line);

  return minCubes["red"] * minCubes["green"] * minCubes["blue"];
}

async function part2() {
  let total = 0;

  const file = await open(process.argv[2]);

  for await (const line of file.readLines()) {
    total += calculatePower(line);
  }

  console.log(total);
}

// doIt();
part2();

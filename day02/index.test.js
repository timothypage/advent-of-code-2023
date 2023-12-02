import { describe, it } from 'node:test';
import assert from 'node:assert';

import { parseGameNumberForLine, gameIsValid } from "./index.js";

const game1 = "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green";
const game12 = "Game 12: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green"
const game3 = "Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red"

describe("parseGameNumberForLine", () => {
  it("should parse game number 1", () => {
    assert.equal(1, parseGameNumberForLine(game1));
  });

  it("should parse game number 12", () => {
    assert.equal(12, parseGameNumberForLine(game12));
  });
});

describe("gameIsValid", () => {
  it("should find game 1 valid", () => {
    assert.equal(true, gameIsValid(game1));
  });

  it("should find game 3 invalid", () => {
    assert.equal(false, gameIsValid(game3));
  })
});



